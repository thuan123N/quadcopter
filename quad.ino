  /************* Flight Control Code Full Self-Level by HiepleVN ***************
 *  Code tham khảo từ nhiều nguồn và đọc tài liệu nước ngoài
 *  Phần cứng như sơ đồ nguyên lý
 *  Trong sơ đồ nguyên lý không có 2 led debug, user tự thêm vào
 *  Code chỉ sử dụng thư viện Wire.h để giao tiếp I2C với MPU-6050
 *  
 */
#include <Wire.h>  

#define roll_axis           1 // định nghĩa trục roll
#define pitch_axis          2
#define yaw_axis            3
#define mpu_i2c_address  0x68 // địa chỉ của module MPU 6050

//xxxxxxxxxxxxxxxxxxxxxxxxxxxx common var xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
int throtlle;
float battery_voltage;
int calib_counter, quadrotor_status;
unsigned long timer_1, timer_2, timer_3, timer_4, timer_5, current_time;
unsigned long loop_timer;
//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx struct varixxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
struct PID{
  float pid_input;
  float pid_output;
  float pid_setpoint;
  float pid_error;
  float pid_pre_error;
  float pid_p_part;
  float pid_i_part;
  float pid_d_part;
  float pid_p_gain;
  float pid_i_gain;
  float pid_d_gain;
  int   pid_limit;
};

struct ANGLE{
  float pitch;
  float roll;
  float pitch_acc;
  float roll_acc;
  float pitch_correct;
  float roll_correct;
};

struct RX{
  char pre_stt_channel[7];
  volatile int raw_signal_channel[7];
  int standard_signal_channel[7];
  int throttle;
};

struct MPU{
  double gyro_pitch, gyro_roll, gyro_yaw;
  long acc_pitch, acc_roll, acc_yaw, acc_total;
  float acc_pitch_offset,acc_roll_offset,acc_yaw_offset;
  double gyro_x_raw, gyro_y_raw, gyro_z_raw;
  int acc_x_raw, acc_y_raw, acc_z_raw;
  double gyro_x_offset, gyro_y_offset, gyro_z_offset;
  float temperature;
};

struct ESC{
  int motor[5];
  unsigned long timer[5];
  unsigned long loop_timer;
};

PID roll, pitch, yaw, altitude;
ANGLE angle;
RX rx;
MPU mpu;
ESC esc;
//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

void initial_pid_gain(){
   roll.pid_p_gain = 0.75;        
  roll.pid_i_gain = 0.001;                   // Ki thực = 0.05/0.005 = 10.0
  roll.pid_d_gain = 15 ;                 // Kd thực = 15.0/200 = 0.075
  
  pitch.pid_p_gain = roll.pid_p_gain;                   
  pitch.pid_i_gain = roll.pid_i_gain;                  // giống PID của roll
  pitch.pid_d_gain = roll.pid_d_gain;

  yaw.pid_p_gain =1.0;
  yaw.pid_i_gain = 0.02;                    // Ki thực = 0.02/0.005 = 4.0
  yaw.pid_d_gain = 0.0;
  
  roll.pid_limit     = 400.0;               // giới hạn cho các hệ số PID để không bị vọt lố quá mức
  pitch.pid_limit    = 400.0;
  yaw.pid_limit      = 400.0;
}

void setup() {  
  Serial.begin(200000);
  initial_pid_gain();
  
  Wire.begin();                                                       // Init giao tiếp I2C với arduino UNO là master
  TWBR = 12;                                                          // Setup tần số giữ nhịp I2C trên chân SCL là 400 Khz
                                                                      // SCL clock frequency = CPU clock frequency / (16 + 2*TWBR*4^TWPS)       

  DDRD |= B11110100;                                                  // Set chân 2 4 5 6 7 trên arduino là ngõ ra (4 chân xuất PWM cho 4 ESC điều khiển 4 motor) và 1 chân số 2 làm led debug
  DDRB |= B00000000;                                                  // các chân 8 9 10 11 là ngõ vào
  DDRC |= B00000010;                                                  // Cho chân A1 là ngõ ra - led đỏ
  pinMode(12,OUTPUT);
  digitalWrite(12,HIGH);                                               // Cho led debug sáng báo hiệu bắt đầu setup
  
  PORTC |= B00000010;                                                 // Cho led đỏ sáng báo hiệu bắt đầu khởi tạo MPU
  delay(200);
  gy521_mpu6050_init();                                               // Khởi tạo mpu6050 (setup các thanh ghi)
  PORTC &= B11111101;                                                 // Tắt led đỏ khi đã khởi tạo mpu thành công
  
  for (calib_counter = 0; calib_counter < 2000 ; calib_counter ++){   // Xuất xung ra ESC để ESC setup đều nhau
    PORTD |= B11110000;                                                     
    delayMicroseconds(1000);                                                
    PORTD &= B00001111;                                                     
    delayMicroseconds(4000);                                          
  
  }
  
  gyro_get_offset();      // Lấy offset của gyro 
  acc_get_offset();     

       


  
  PCICR &= 0x00;          // Set bit PCIE0 = 1 trong thanh ghi PCICR để kích hoạt ngắt thay đổi trạng thái ở các chân B0,1,2,3,4,5,6,7 trên atmega328P
  PCICR |= 0x01;

  PCMSK0 &= 0x00;         // Set bit PCINT0,1,2,3 = 1 trong thanh ghi PCMSK0 để kích hoạt ngắt thay đổi trạng thái trên chân B0,1,2,3 của atmega328 (chân 8,9,10,11 trên arduino) 
  PCMSK0 |= B00001111;


  while(rx.standard_signal_channel[3] > 1050 || rx.standard_signal_channel[4] < 1450 ){
  
    rx.standard_signal_channel[3] = rx.raw_signal_channel[3];               
    rx.standard_signal_channel[4] = rx.raw_signal_channel[4];         // Kiểm tra độ rộng xung kênh 3 nếu trên 1050 hoặc kênh 4 nếu dưới 1450 thì không cho vào main để bay      
    quadrotor_status++;                                               // Nghĩa là nếu cấp điện cho quad mà cần ga trên TX chưa về min hoặc cần yaw trên TX chưa về giữa thì ko cho bay
    PORTD |= B11110000;                                        
    delayMicroseconds(1000);                                  
    PORTD &= B00001111;                                        
    delayMicroseconds(3000);                                                  
    if(quadrotor_status == 100){                                          
      digitalWrite(12, !digitalRead(12));                      
      quadrotor_status = 0;                                               
    }
  }
  
  battery_voltage = (float)(analogRead(0) + 55) * 1.2317;             // Từ 12.6 V (max) từ pin li-po 3S qua diode còn ~12V qua cầu phân áp 2 điện trở 1.5k 1.0k để lấy điện áp ~5V đưa 
                                                                      // vào chân Analog 0 của arduino để đọc dung lượng pin 
                                                                      // Chân analog của arduino đọc giá trị analog có độ phân giải 10 bit (0 - 1023) và chỉ chịu được điện áp tối đa 5V
                                                                      // Pin thực sự là 12.6 V max muốn chuyển thành 5V đưa vào chân analog arduino phải quy đổi 
                                                                      // Nếu chân analog đọc đc giá trị 1023 thì điện áp đưa vào là 5V tương ứng với 12V khi qua diode
                                                                      // Vậy phải chuyển đổi để khi đọc 1023 thì tương ứng với điện áp pin là 12.6V
                                                                      // 12.6 ~~ 1023 ~~ 5V (A0)
                                                                      // 12.6 / 1023 = 0.012317
                                                                      // phải bù thêm 1 lượng 55 + với giá trị đọc từ chân analog 0 để đủ với 12.6V pin
                                                                       
  quadrotor_status = 0;                                               // Reset biến trạng thái của quadrotor về 0 (stand by)
  digitalWrite(12,LOW);                                                // Tắt led để báo hiệu vào hàm main 
  loop_timer = micros();                                              // Reset loop timer (sampling time)
}

void loop() {
  rx.standard_signal_channel[1] = 3000-rx.raw_signal_channel[1];           // Đọc độ rộng xung của kênh 1 - Roll    (từ ngắt thay đổi trạng thái của chân 8 trên arduino)
  rx.standard_signal_channel[2] = rx.raw_signal_channel[2];           // Đọc độ rộng xung của kênh 2 - Pitch   (từ ngắt thay đổi trạng thái của chân 9 trên arduino)
  rx.standard_signal_channel[3] = rx.raw_signal_channel[3];           // Đọc độ rộng xung của kênh 3 - Throttle(từ ngắt thay đổi trạng thái của chân 10 trên arduino)
  rx.standard_signal_channel[4] = rx.raw_signal_channel[4];           // Đọc độ rộng xung của kênh 4 - Yaw     (từ ngắt thay đổi trạng thái của chân 11 trên arduino)

  read_mpu_data();                                                    // Đọc dữ liệu accel và gyro thô từ mpu6050                                   
  calib_gyro_3_axis();                                                // Calib lại dữ liệu gyro thô
  correct_roll_pitch_yaw_data();                                      // Quy đổi chiều của gyro và accel 3 trục roll pitch yaw
  low_pass_filter_pid_input();                                        // Lọc input gyro cho pid
  check_quadrotor_status();                                           // Kiểm tra trạng thái quadrotor  
  calculate_angle_roll_pitch();                                       // Tính các góc roll và pitch của quadrotor


  

  calculate_pid_setpoint();                                           // Tính toán setpoint cho bộ điều khiển PID     
 

 
 
    
                                                                                                                 
  roll.pid_output  = calculate_pid(roll_axis);                        // Tính toán ngõ ra bộ PID cho trục roll
  pitch.pid_output = calculate_pid(pitch_axis);                       // Tính toán ngõ ra bộ PID cho trục pitch
  yaw.pid_output   = calculate_pid(yaw_axis);                         // Tính toán ngõ ra bộ PID cho trục yaw
  calculate_pwm_for_esc();                                            // Tính toán xung PPM cho 4 ESC 


  battery_voltage = battery_voltage * 0.92 + (analogRead(0) + 55) * 0.09853;  


 
 
   
    
    

  while(micros() - loop_timer < 5000);                                // Nếu thực thi tất cả công việc mà thời gian vòng lặp vẫn chưa hết 5ms thì chờ và không làm gì nữa                      
  loop_timer = micros();                                              // Khi sang vòng lặp lấy mẫu mới thì cập nhật biến loop_timer    
  pwm_esc_output();
   sentdatatostm();
  
}

ISR(PCINT0_vect){                                                       // Hàm ngắt thay đổi trạng thái của 4 chân 8,9,10,11,12 trên arduino để đọc xung từ TX đến RX
  current_time = micros();                                              // Khi có ngắt thay đổi trạng thái ở bất kì chân nào trong 4 chân 8 9 10 11 12 thì sẽ vào ngắt
                                                                        // Lưu lại mốc thời gian khi xảy ra ngắt
  //XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX Kênh Roll XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
  if(PINB & B00000001){                                                 // Kiểm tra chân 8 nếu ở mức 1
    if(rx.pre_stt_channel[1] == 0){                                     // Nếu trước đó chân 8 ở mức 0 (xét xung cạnh lên)
      rx.pre_stt_channel[1] = 1;                                        // Cho biến trạng thái chân 8 = 1
      timer_1 = current_time;                                           // Lưu thời điểm bắt đầu lên mức 1 vào biến timer_1
    }
  }
  else if(rx.pre_stt_channel[1] == 1){                                  // Kiểm tra chân 8 nếu ở mức 0 và trước đó là mức 1
    rx.pre_stt_channel[1] = 0;                                          // Cho biến trạng thái chân 8 = 0
    rx.raw_signal_channel[1] =  (current_time - timer_1)*1.004016064+92.3695;        
    // Tính ra độ rộng xung kênh roll = thời điểm bắt đầu xuống mức 0 trừ cho thời điểm bắt đầu lên mức 1
  }
  //XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX Kênh Pitch XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
  if(PINB & B00000010 ){                                                // Kiểm tra chân 9 nếu ở mức 1
    if(rx.pre_stt_channel[2] == 0){                                     // Nếu trước đó chân 9 ở mức 0 (xét xung cạnh lên)
      rx.pre_stt_channel[2] = 1;                                        // Cho biến trạng thái chân 9 = 1
      timer_2 = current_time;                                           // Lưu thời điểm bắt đầu lên mức 1 vào biến timer_2
    }
  }
  else if(rx.pre_stt_channel[2] == 1){                                  // Kiểm tra chân 9 nếu ở mức 0 và trước đó là mức 1
    rx.pre_stt_channel[2] = 0;                                          // Cho biến trạng thái chân 9 = 0
    rx.raw_signal_channel[2] = (current_time - timer_2)*1.0080645-44.354838;               // Tính ra độ rộng xung kênh pitch = thời điểm bắt đầu xuống mức 0 trừ cho thời điểm bắt đầu lên mức 1  
  }
  //XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX Kênh Throttle XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
  if(PINB & B00000100 ){                                                // Kiểm tra chân 10 nếu ở mức 1
    if(rx.pre_stt_channel[3] == 0){                                     // Nếu trước đó chân 10 ở mức 0 (xét xung cạnh lên)
      rx.pre_stt_channel[3] = 1;                                        // Cho biến trạng thái chân 10 = 1
      timer_3 = current_time;                                           // Lưu thời điểm bắt đầu lên mức 1 vào biến timer_3
    }
  }
  else if(rx.pre_stt_channel[3] == 1){                                  // Kiểm tra chân 10 nếu ở mức 0 và trước đó là mức 1
    rx.pre_stt_channel[3] = 0;                                          // Cho biến trạng thái chân 10 = 0
    rx.raw_signal_channel[3] = (current_time - timer_3)*1.004-98;                  // Tính ra độ rộng xung kênh throttle = thời điểm bắt đầu xuống mức 0 trừ cho thời điểm bắt đầu lên mức 1 
  }
  //XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX Kênh Yaw XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
  if(PINB & B00001000 ){                                                // Kiểm tra chân 11 nếu ở mức 1
    if(rx.pre_stt_channel[4] == 0){                                     // Nếu trước đó chân 11 ở mức 0 (xét xung cạnh lên)
      rx.pre_stt_channel[4] = 1;                                        // Cho biến trạng thái chân 11 = 1
      timer_4 = current_time;                                           // Lưu thời điểm bắt đầu lên mức 1 vào biến timer_4
    }
  }
  else if(rx.pre_stt_channel[4] == 1){                                  // Kiểm tra chân 11 nếu ở mức 0 và trước đó là mức 1
    rx.pre_stt_channel[4] = 0;                                          // Cho biến trạng thái chân 11 = 0
    rx.raw_signal_channel[4] =  (current_time - timer_4)*1.004+113.4497;                  // Tính ra độ rộng xung kênh yaw = thời điểm bắt đầu xuống mức 0 trừ cho thời điểm bắt đầu lên mức 1 
  }
}


void gy521_mpu6050_init(){
  Wire.beginTransmission(mpu_i2c_address);                            // Tạo trạng thái Start I2C và gửi địa chỉ slave I2C 0x68 đến mpu 
  Wire.write(0x6B);                                                   // Gửi địa chỉ thanh ghi muốn ghi dữ liệu vào là 0x6B
  Wire.write(0x00);                                                   // Ghi 0x00 vào thanh ghi 0x6B để reset mp6050, tắt chế độ sleep công suất thấp và đánh thức mpu6050
  Wire.endTransmission();                                             // Tạo trạng thái Stop I2C 
  
  Wire.beginTransmission(mpu_i2c_address);                            // Tạo trạng thái Start I2C và gửi địa chỉ slave I2C 0x68 đến mpu 
  Wire.write(0x1B);                                                   // Gửi địa chỉ thanh ghi muốn ghi dữ liệu vào là 0x1B
  Wire.write(0x08);                                                   // Ghi 0x08 vào thanh ghi 0x1B để chọn scale cho gyro là +- 500 deg/sec
  Wire.endTransmission();                                             // Tạo trạng thái Stop I2C

  Wire.beginTransmission(mpu_i2c_address);                            // Tạo trạng thái Start I2C và gửi địa chỉ slave I2C 0x68 đến mpu 
  Wire.write(0x1C);                                                   // Gửi địa chỉ thanh ghi muốn ghi dữ liệu vào là 0x1C      
  Wire.write(0x10);                                                   // Ghi 0x10 vào thanh ghi 0x1C để chọn scale cho accel là +/- 8g       
  Wire.endTransmission();                                             // Tạo trạng thái Stop I2C

  Wire.beginTransmission(mpu_i2c_address);                            // Tạo trạng thái Start I2C và gửi địa chỉ slave I2C 0x68 đến mpu 
  Wire.write(0x1A);                                                   // Gửi địa chỉ thanh ghi muốn ghi dữ liệu vào là 0x1A
  Wire.write(0x03);                                                   // Ghi 0x03 vào thanh ghi 0x1A để chọn tần số bộ lọc thông thấp khoảng 43 Hz để lọc gyro và accel
  Wire.endTransmission();                                             // Tạo trạng thái Stop I2C

  
  Wire.beginTransmission(mpu_i2c_address);                            // Tạo trạng thái Start I2C và gửi địa chỉ slave I2C 0x68 đến mpu 
  Wire.write(0x6B);                                                   // Gửi địa chỉ thanh ghi muốn đọc dữ liệu là 0x6B
  Wire.endTransmission();                                             // Tạo trạng thái Stop I2C
  Wire.requestFrom(mpu_i2c_address, 1);                               // Yêu cầu mpu trả về 1 byte data
  while(Wire.available() < 1);                                        // Chờ tới khi nào có 1 byte data gửi về
  if(Wire.read() != 0x00) goto error_init;                            // Nếu đọc lại mà khác 0x00 
  

  Wire.beginTransmission(mpu_i2c_address);                            // Tạo trạng thái Start I2C và gửi địa chỉ slave I2C 0x68 đến mpu 
  Wire.write(0x1B);                                                   // Gửi địa chỉ thanh ghi muốn đọc dữ liệu là 0x1B
  Wire.endTransmission();                                             // Tạo trạng thái Stop I2C
  Wire.requestFrom(mpu_i2c_address, 1);                               // Yêu cầu mpu trả về 1 byte data
  while(Wire.available() < 1);                                        // Chờ tới khi nào có 1 byte data gửi về
  if(Wire.read() != 0x08) goto error_init;                            // Nếu đọc lại mà khác 0x08 

                                    
  Wire.beginTransmission(mpu_i2c_address);                            // Tạo trạng thái Start I2C và gửi địa chỉ slave I2C 0x68 đến mpu 
  Wire.write(0x1C);                                                   // Gửi địa chỉ thanh ghi muốn đọc dữ liệu là 0x1C
  Wire.endTransmission();                                             // Tạo trạng thái Stop I2C
  Wire.requestFrom(mpu_i2c_address, 1);                               // Yêu cầu mpu trả về 1 byte data
  while(Wire.available() < 1);                                        // Chờ tới khi nào có 1 byte data gửi về
  if(Wire.read() != 0x10) goto error_init;                            // Nếu đọc lại mà khác 0x10 

  
  Wire.beginTransmission(mpu_i2c_address);                            // Tạo trạng thái Start I2C và gửi địa chỉ slave I2C 0x68 đến mpu 
  Wire.write(0x1A);                                                   // Gửi địa chỉ thanh ghi muốn đọc dữ liệu là 0x1C
  Wire.endTransmission();                                             // Tạo trạng thái Stop I2C
  Wire.requestFrom(mpu_i2c_address, 1);                               // Yêu cầu mpu trả về 1 byte data
  while(Wire.available() < 1);                                        // Chờ tới khi nào có 1 byte data gửi về
  if(Wire.read() != 0x03){                                            // Nếu đọc lại mà khác 0x10 
    error_init:
    while(1) {
      PORTC |= B00000010;
      delay(200);
      PORTC &= B11111101;                                        
      delay(200);
    }                                        
  }
}

void read_mpu_data(){
  Wire.beginTransmission(mpu_i2c_address);                                  // Tạo trạng thái Start I2C và gửi địa chỉ slave I2C 0x68 đến mpu 
  Wire.write(0x3B);                                                         // Gửi địa chỉ thanh ghi muốn đọc dữ liệu là 0x3B
  Wire.endTransmission();                                                   // Tạo trạng thái Stop I2C
  Wire.requestFrom(mpu_i2c_address,14);                                     // Yêu cầu mpu trả về 14 byte data
  while(Wire.available() < 14);                                             // Chờ tới khi nào có đủ 14 byte data gửi về
  mpu.acc_x_raw    = Wire.read()<<8|Wire.read();                            // Đọc 8 bit cao trước rồi nối với 8 bit thấp để ra dữ liệu accel trục X 16 bit
  mpu.acc_y_raw    = Wire.read()<<8|Wire.read();                            // Đọc 8 bit cao trước rồi nối với 8 bit thấp để ra dữ liệu accel trục Y 16 bit
  mpu.acc_z_raw    = Wire.read()<<8|Wire.read();                            // Đọc 8 bit cao trước rồi nối với 8 bit thấp để ra dữ liệu accel trục Z 16 bit
  mpu.temperature  = Wire.read()<<8|Wire.read();                            // Đọc 8 bit cao trước rồi nối với 8 bit thấp để ra dữ liệu nhiệt độ 16 bit
  mpu.gyro_x_raw   = Wire.read()<<8|Wire.read();                            // Đọc 8 bit cao trước rồi nối với 8 bit thấp để ra dữ liệu gyro trục X 16 bit
  mpu.gyro_y_raw   = Wire.read()<<8|Wire.read();                            // Đọc 8 bit cao trước rồi nối với 8 bit thấp để ra dữ liệu gyro trục Y 16 bit
  mpu.gyro_z_raw   = Wire.read()<<8|Wire.read();                            // Đọc 8 bit cao trước rồi nối với 8 bit thấp để ra dữ liệu gyro trục Z 16 bit
}

//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx Bộ điều khiển PID rời rạc xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
// Với dt = 5ms = 0.005 s
// Fs = 200 Hz
// PID output  = Kp*e + Ki*∫edt + Kd*(de/dt)   ---    liên tục
// Chuyển PID sang rời rạc để nhúng vào vi điều khiển
//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx


//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx Rời rạc bộ điều khiển xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
// de/dt =(e(k) – e(k-1))/h  
// Vì thời gian lấy mẫu cho các bộ điều khiển thường rất bé nên có thể xấp xỉ đạo hàm bằng sự thay đổi của e trong 2 lần lấy mẫu liên tiếp.
// e(k) là giá trị hiện tại của e, e(k-1) là giá trị của e trong lần lấy mẫu trước đó và h là khoảng thời gian lấy mẫu (h là hằng số).


// ∫edt = ∑e(k)*h
// Dùng phương pháp xấp xỉ
// Dùng phương pháp cộng dồn cho thành phần I
// I(k) = I(k-1) + e(k)*h
// Với I(k) là thành phần tích phân hiện tại và I(k-1) là thành phần tích phân trước đó. 
//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx


float calculate_pid(char axis) {                                                                  // Hàm bộ điều khiển PID
  static float pid_output;
  switch(axis) {
    case roll_axis: {                                                                             // case 1 là trục roll
      roll.pid_error  =  roll.pid_input-roll.pid_setpoint;                                      // error roll = input roll - setpoint roll

      roll.pid_p_part =  roll.pid_p_gain * roll.pid_error;                                        // Thành phần P roll
      roll.pid_i_part += roll.pid_i_gain * roll.pid_error;                                        // Thành phần I roll
      roll.pid_d_part =  roll.pid_d_gain * (roll.pid_error - roll.pid_pre_error);                 // Thành phần D roll
      if(roll.pid_i_part > roll.pid_limit)roll.pid_i_part = roll.pid_limit;                       // Giới hạn thành phần I roll vì cộng dồn
      else if(roll.pid_i_part < roll.pid_limit * -1)roll.pid_i_part = roll.pid_limit * -1;
  
      pid_output = roll.pid_p_part + roll.pid_i_part + roll.pid_d_part;                           // Ngõ ra bộ điều khiển PID roll = thành phần P roll + thành phần I roll + thành phần D roll
      if(pid_output > roll.pid_limit)pid_output = roll.pid_limit;
      else if(pid_output < roll.pid_limit * -1)pid_output = roll.pid_limit * -1;
      
      roll.pid_pre_error = roll.pid_error;                                                        // Gán sai số trước đó = sai số hiện tại để lần lấy mẫu kế tiếp tính toán tiếp
      return pid_output;
      break; 
    }
    case pitch_axis: {                                                                            // case 2 là trục pitch
      pitch.pid_error  =  pitch.pid_input - pitch.pid_setpoint;                                   // error pitch = input pitch - setpoint pitch
      
      pitch.pid_p_part =  pitch.pid_p_gain * pitch.pid_error;                                     // Thành phần P pitch
      pitch.pid_i_part += pitch.pid_i_gain * pitch.pid_error;                                     // Thành phần I pitch
      pitch.pid_d_part =  pitch.pid_d_gain * (pitch.pid_error - pitch.pid_pre_error);             // Thành phần D pitch
      if(pitch.pid_i_part > pitch.pid_limit)pitch.pid_i_part = pitch.pid_limit;                   // Giới hạn thành phần I pitch vì cộng dồn
      else if(pitch.pid_i_part < pitch.pid_limit * -1)pitch.pid_i_part = pitch.pid_limit * -1;
  
      pid_output = pitch.pid_p_part + pitch.pid_i_part + pitch.pid_d_part;                        // Ngõ ra bộ điều khiển PID pitch = thành phần P pitch + thành phần I pitch + thành phần D pitch
      if(pid_output > pitch.pid_limit)pid_output = pitch.pid_limit;
      else if(pid_output < pitch.pid_limit * -1)pid_output = pitch.pid_limit * -1;
      
      pitch.pid_pre_error = pitch.pid_error;                                                      // Gán sai số trước đó = sai số hiện tại để lần lấy mẫu kế tiếp tính toán tiếp
      return pid_output;
      break; 
    }
    case yaw_axis: {                                                                              // case 3 là trục yaw
      yaw.pid_error  =  yaw.pid_input - yaw.pid_setpoint;                                         // error yaw = input yaw - setpoint yaw
      
      yaw.pid_p_part =  yaw.pid_p_gain * yaw.pid_error;                                           // Thành phần P yaw
      yaw.pid_i_part += yaw.pid_i_gain * yaw.pid_error;                                           // Thành phần I yaw
      yaw.pid_d_part =  yaw.pid_d_gain * (yaw.pid_error - yaw.pid_pre_error);                     // Thành phần D yaw
      if(yaw.pid_i_part > yaw.pid_limit)yaw.pid_i_part = yaw.pid_limit;                           // Giới hạn thành phần I yaw vì cộng dồn
      else if(yaw.pid_i_part < yaw.pid_limit * -1)yaw.pid_i_part = yaw.pid_limit * -1;
  
      pid_output = yaw.pid_p_part + yaw.pid_i_part + yaw.pid_d_part;                              // Ngõ ra bộ điều khiển PID yaw = thành phần P yaw + thành phần I yaw + thành phần D yaw
      if(pid_output > yaw.pid_limit)pid_output = yaw.pid_limit;
      else if(pid_output < yaw.pid_limit * -1)pid_output = yaw.pid_limit * -1;
      
      yaw.pid_pre_error = yaw.pid_error;                                                          // Gán sai số trước đó = sai số hiện tại để lần lấy mẫu kế tiếp tính toán tiếp
      return pid_output;                              
      break; 
    }
    default : {
      break;
    }
  }
}

//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx


void pwm_esc_output() {
  PORTD |= B11110000;                                                   // Cho 4 chân 4 5 6 7 lên mức 1     
  esc.timer[1] = esc.motor[1] + loop_timer;                             // Cộng độ rộng xung ESC 1 với loop_timer 
  esc.timer[2] = esc.motor[2] + loop_timer;                             // Cộng độ rộng xung ESC 2 với loop_timer  
  esc.timer[3] = esc.motor[3] + loop_timer;                             // Cộng độ rộng xung ESC 3 với loop_timer  
  esc.timer[4] = esc.motor[4] + loop_timer;                             // Cộng độ rộng xung ESC 4 với loop_timer  
  
  while(PORTD >= 16){                                                   // Kiểm tra xem 4 chân 4 5 6 7 đã xuống mức 0 hết chưa nếu chưa thì vẫn tiếp tục thực hiện trong while    
    esc.loop_timer = micros();                                          // Cập nhật thời gian vòng lặp   
    if(esc.timer[1] <= esc.loop_timer)PORTD &= B11101111;               // Khi chân 4 lên mức 1 đủ thời gian độ rộng xung ESC 1 thì cho chân 4 xuống mức 0  
    if(esc.timer[2] <= esc.loop_timer)PORTD &= B11011111;               // Khi chân 5 lên mức 1 đủ thời gian độ rộng xung ESC 2 thì cho chân 5 xuống mức 0  
    if(esc.timer[3] <= esc.loop_timer)PORTD &= B10111111;               // Khi chân 6 lên mức 1 đủ thời gian độ rộng xung ESC 3 thì cho chân 6 xuống mức 0  
    if(esc.timer[4] <= esc.loop_timer)PORTD &= B01111111;               // Khi chân 7 lên mức 1 đủ thời gian độ rộng xung ESC 4 thì cho chân 7 xuống mức 0  
  }
}


void correct_roll_pitch_yaw_data() {
  mpu.gyro_roll  = mpu.gyro_x_raw;                                           // quy đổi chiều dương gyro_roll là chiều dương gyro_x;
  mpu.gyro_pitch = mpu.gyro_y_raw * -1;                                      // quy đổi chiều dương gyro_pitch là chiều âm gyro_y;
  mpu.gyro_yaw   = mpu.gyro_z_raw * -1;                                      // quy đổi chiều dương gyro_yaw là chiều âm gyro_z;

  mpu.acc_pitch = mpu.acc_x_raw;                                             // quy đổi chiều dương accel_pitch là chiều dương accel_x;
  mpu.acc_roll  = mpu.acc_y_raw * -1;                                        // quy đổi chiều dương accel_roll là chiều âm accel_y; 
  mpu.acc_yaw   = mpu.acc_z_raw * -1;                                        // quy đổi chiều dương accel_yaw là chiều âm accel_z;

  /*
                    <--------------- Y ---------------- 
                               ------------
                               | MPU-6050 |
                               ------------  
                                    / \                              
                                     |
                                     | X
                                     |
                                     |
  */
}

void calib_gyro_3_axis() {
  mpu.gyro_x_raw -= mpu.gyro_x_offset;                                             // Trừ gyro_x cho offset ban đầu đã tìm được
  mpu.gyro_y_raw -= mpu.gyro_y_offset;                                             // Trừ gyro_y cho offset ban đầu đã tìm được
  mpu.gyro_z_raw -= mpu.gyro_z_offset;                                             // Trừ gyro_z cho offset ban đầu đã tìm được
}

void check_quadrotor_status() {
  if(rx.standard_signal_channel[3] < 1050 && rx.standard_signal_channel[4] < 1050)    quadrotor_status = 1;   // Để cần ga min và gạt cần yaw qua trái max
                                                                                                              // Set biến trạng thái quadrotor = 1
  if(quadrotor_status == 1 && rx.standard_signal_channel[3] < 1050 && rx.standard_signal_channel[4] > 1450){  // Sau đó giữ cần ga min và thả cần Yaw về giữa thì cho biến quadrotor = 2
    quadrotor_status = 2;                                                                                     // Lúc này 4 motor quay với độ rộng xung cấp cho ESC là 1100 us để chờ cất cánh
    roll.pid_i_part = 0.0;                                                                                    // Đồng thời reset các thành phần của bộ điều khiển PID về 0.0
    pitch.pid_i_part = 0.0;
    yaw.pid_i_part = 0.0;
    roll.pid_pre_error = 0.0;
    pitch.pid_pre_error = 0.0;    
    yaw.pid_pre_error = 0.0;
    altitude.pid_pre_error = 0.0;
    angle.pitch = angle.pitch_acc;
    angle.roll = angle.roll_acc;
  }
  if(quadrotor_status == 2 && rx.standard_signal_channel[3] < 1050 && rx.standard_signal_channel[4] > 1950) quadrotor_status = 0;  
  // Nếu muốn dừng motor thì giữ cần ga min và gạt cần Yaw qua phải max  
}

void low_pass_filter_pid_input(){  
  roll.pid_input  = (roll.pid_input * 0.8)  + ((mpu.gyro_roll / 65.5) * 0.2);            // ngõ vào bộ pid trục roll đổi sang deg/sec và qua 1 bộ lọc thông thấp với alpha = 0.8 để lọc nhiễu 
  pitch.pid_input = (pitch.pid_input * 0.8) + ((mpu.gyro_pitch / 65.5) * 0.2);           // ngõ vào bộ pid trục pitch đổi sang deg/sec và qua 1 bộ lọc thông thấp với alpha = 0.8 để lọc nhiễu 
  yaw.pid_input   = (yaw.pid_input * 0.8)   + ((mpu.gyro_yaw / 65.5) * 0.2);             // ngõ vào bộ pid trục yaw đổi sang deg/sec và qua 1 bộ lọc thông thấp với alpha = 0.8 để lọc nhiễu   
}

void calculate_pid_setpoint() {
  angle.pitch_correct = angle.pitch * 15.0;
  angle.roll_correct = angle.roll * 15.0;
  
  roll.pid_setpoint = 0.0;              // Chọn setpoint trục roll là 0.0 deg/sec
  pitch.pid_setpoint = 0.0;             // Chọn setpoint trục pitch là 0.0 deg/sec
  yaw.pid_setpoint = 0.0;               // Chọn setpoint trục yaw là 0.0 deg/sec
  
  if(rx.standard_signal_channel[1] > 1498) roll.pid_setpoint = rx.standard_signal_channel[1] - 1498;
  else if(rx.standard_signal_channel[1] < 1458) roll.pid_setpoint = rx.standard_signal_channel[1] - 1458;
  roll.pid_setpoint -= angle.roll_correct;
  roll.pid_setpoint /= 3.0;
  // Muốn thay đổi góc roll của Quad thì gạt cần roll tương ứng qua trái hoặc phải
  // Cần tạo 1 khoảng an toàn với độ rộng xung của kênh roll (32 us) để khi cần roll ở giữa thì quad giữ trạng thái cân bằng trước đó 
  // Khi gạt cần roll và độ rộng xung kênh roll > 1516 hoặc < 1484 thì lấy độ rộng xung kênh roll trừ cho 1516 hoặc 1484 rồi trừ cho góc roll x 15 
  // và chia 3.0 (càng lớn thì góc nghiêng càng nhỏ) để tạo setpoint gyro 
  
  if(rx.standard_signal_channel[2] > 1515) pitch.pid_setpoint = rx.standard_signal_channel[2] - 1515;
  else if(rx.standard_signal_channel[2] < 1477) pitch.pid_setpoint = rx.standard_signal_channel[2] - 1475;
  pitch.pid_setpoint -= angle.pitch_correct;
  pitch.pid_setpoint /= 3.0;  
  // Muốn thay đổi góc pitch của Quad thì gạt cần pitch tương ứng lên hoặc xuống
  // Cần tạo 1 khoảng an toàn với độ rộng xung của kênh pitch (32 us) để khi cần pitch ở giữa thì quad giữ trạng thái cân bằng trước đó 
  // Khi gạt cần pitch và độ rộng xung kênh pitch > 1516 hoặc < 1484 thì lấy độ rộng xung kênh pitch trừ cho 1516 hoặc 1484 rồi trừ cho góc pitch x 15 
  // và chia 3.0 (càng lớn thì góc nghiêng càng nhỏ) để tạo setpoint 



  if(rx.standard_signal_channel[3] > 1100){ 
    if(rx.standard_signal_channel[4] > 1527) yaw.pid_setpoint = (rx.standard_signal_channel[4] - 1527)/3.0;
    else if(rx.standard_signal_channel[4] < 1487) yaw.pid_setpoint = (rx.standard_signal_channel[4] - 1487)/3.0;
  }  
  // Nếu độ rộng xung kênh ga > 1100 us thì mới cho xoay Quadrotor
  // Muốn thay đổi góc yaw của Quad thì gạt cần yaw tương ứng qua trái hoặc phải
  // Cần tạo 1 khoảng an toàn với độ rộng xung của kênh yaw (32 us) để khi cần yaw ở giữa thì quad giữ trạng thái cân bằng trước đó 
  // Khi gạt cần yaw và độ rộng xung kênh yaw > 1516 hoặc < 1484 thì lấy độ rộng xung kênh yaw trừ cho 1516 hoặc 1484 rồi chia 4.0 (càng lớn thì góc nghiêng càng nhỏ) để tạo setpoint 
}


void check_battery_voltage() {
  battery_voltage = battery_voltage * 0.92 + (analogRead(0) + 55) * 0.09853;         // Lọc dữ liệu pin để chống nhiễu khi điều khiển động cơ có sụt áp
  //if(battery_voltage <= 1100&battery_voltage >500) digitalWrite(12, HIGH);      // Nếu dung lượng pin <= 11 V thì cho led xanh sáng
}

void calculate_pwm_for_esc() {
  rx.throttle = rx.standard_signal_channel[3];         // Lưu lại độ rộng xung kênh Rx.throttle ở mỗi lần lấy mẫu để độ rộng xung kênh ga ko thay đổi trong lúc điều khiển ở mỗi vòng lặp 
                                                         // Vì đọc độ rộng xung bằng ngắt nên nếu không lưu lại vào 1 biến thì có thể khi tính xung cho động cơ 1 thì ga giá trị này
                                                         // còn tính xung cho động cơ 2 thì ga giá trị khác
  if (rx.throttle > 1800) rx.throttle = 1800;            // Giới hạn kênh ga nếu độ rộng xung > 1700 us thì cho = 1700 us                     
                                                      
  if (quadrotor_status == 2){                            // Nếu biến trạng thái Quadrotor = 2 nghĩa là quad đang sẵn sàng bay và 4 motor quay                                     
    esc.motor[1] = rx.throttle + pitch.pid_output- roll.pid_output + yaw.pid_output;             // Tính xung cho ESC 1 CounterClockWise (motor 1 quay ngược chiều kim đồng hồ)
    //Serial.println(esc.motor[1]); 
    //Serial.println(esc.motor[1]); 
    esc.motor[2] = rx.throttle - pitch.pid_output - roll.pid_output- yaw.pid_output;             // Tính xung cho ESC 2 ClockWise (motor 2 quay cùng chiều kim đồng hồ)
    
    esc.motor[3] = rx.throttle - pitch.pid_output + roll.pid_output + yaw.pid_output;             // Tính xung cho ESC 3 CounterClockWise (motor 3 quay ngược chiều kim đồng hồ)
    esc.motor[4] = rx.throttle + pitch.pid_output + roll.pid_output- yaw.pid_output;             // Tính xung cho ESC 4 ClockWise (motor 4 quay cùng chiều kim đồng hồ)

    /*
    phần cứng
          motor_4 CW (pin 7)   front    motor_1 CCW(pin 4)
                   \\                         //
                    \\                       //
          left       = = = = = = = = = = = = =     right
                    //                       \\
                   //                         \\
          motor_3 CCW (pin 6)   back    motor_2 CW (pin 5)
    */
    if (battery_voltage < 1240 && battery_voltage > 800){                   
      esc.motor[1] += esc.motor[1] * ((1240 - battery_voltage)/(float)3500);              
      esc.motor[2] += esc.motor[2] * ((1240 - battery_voltage)/(float)3500);              
      esc.motor[3] += esc.motor[3] * ((1240 - battery_voltage)/(float)3500);              
      esc.motor[4] += esc.motor[4] * ((1240 - battery_voltage)/(float)3500);              
    } 
    
    if (esc.motor[1] < 1100) esc.motor[1] = 1100;                   // Giới hạn độ rộng xung ESC 1 nếu < 1100 us thì cho = 1100 us                       
    if (esc.motor[2] < 1100) esc.motor[2] = 1100;                   // Giới hạn độ rộng xung ESC 2 nếu < 1100 us thì cho = 1100 us                     
    if (esc.motor[3] < 1100) esc.motor[3] = 1100;                   // Giới hạn độ rộng xung ESC 3 nếu < 1100 us thì cho = 1100 us                      
    if (esc.motor[4] < 1100) esc.motor[4] = 1100;                   // Giới hạn độ rộng xung ESC 4 nếu < 1100 us thì cho = 1100 us                     
    
    if (esc.motor[1] > 2000) esc.motor[1] = 2000;                   // Giới hạn độ rộng xung ESC 1 nếu > 2000 us thì cho = 2000 us                        
    if (esc.motor[2] > 2000) esc.motor[2] = 2000;                   // Giới hạn độ rộng xung ESC 2 nếu > 2000 us thì cho = 2000 us                      
    if (esc.motor[3] >2000) esc.motor[3] = 2000;                   // Giới hạn độ rộng xung ESC 3 nếu > 2000 us thì cho = 2000 us                      
    if (esc.motor[4] > 2000) esc.motor[4] = 2000;                   // Giới hạn độ rộng xung ESC 4 nếu > 2000 us thì cho = 2000 us                      
  }
  
  else{                                                             // Nếu biến trạng thái Quadrotor khác 2 nghĩa là quad hạ cánh và 4 motor dừng
    esc.motor[1] = 1000;                                            // Set độ rộng xung ESC 1 = 1000 us để motor 1 dừng                      
    esc.motor[2] = 1000;                                            // Set độ rộng xung ESC 2 = 1000 us để motor 2 dừng                      
    esc.motor[3] = 1000;                                            // Set độ rộng xung ESC 3 = 1000 us để motor 3 dừng                      
    esc.motor[4] = 1000;                                            // Set độ rộng xung ESC 4 = 1000 us để motor 4 dừng                      
  }
}


void gyro_get_offset() {
  for (calib_counter = 0; calib_counter < 2000 ; calib_counter++){    // Đọc giá trị gyro 2000 lần và cộng dồn lại    
    if(calib_counter % 20 == 0)digitalWrite(12, !digitalRead(12));   
    read_mpu_data();                                      
    mpu.gyro_x_offset += mpu.gyro_x_raw;                          
    mpu.gyro_y_offset += mpu.gyro_y_raw;                          
    mpu.gyro_z_offset += mpu.gyro_z_raw;           

    PORTD |= B11110000;                                        
    delay(1);                                  
    PORTD &= B00001111;                                       
    delay(3);   
  }
  mpu.gyro_x_offset /= 2000;                                               // Chia giá trị gyro_x_calib cho 2000 để lấy offset cho gyro trục X (để thực hiện LPF)
  mpu.gyro_y_offset /= 2000;                                               // Chia giá trị gyro_y_calib cho 2000 để lấy offset cho gyro trục Y (để thực hiện LPF)
  mpu.gyro_z_offset /= 2000;                                               // Chia giá trị gyro_z_calib cho 2000 để lấy offset cho gyro trục Z (để thực hiện LPF)
}

void calculate_angle_roll_pitch() {
  angle.pitch += mpu.gyro_pitch * 0.00007634;                              // 0.00007634 = 1 / (200Hz / 65.5)      
  angle.roll  += mpu.gyro_roll * 0.00007634;                                     
  
  angle.pitch -= angle.roll * sin(mpu.gyro_yaw * 0.000001332);             // 0.000001332 = 0.00007634 * (3.142(PI) / 180)
  angle.roll  += angle.pitch * sin(mpu.gyro_yaw * 0.000001332);           

  mpu.acc_total = sqrt((mpu.acc_roll*mpu.acc_roll)+(mpu.acc_pitch*mpu.acc_pitch)+(mpu.acc_yaw*mpu.acc_yaw));                                              
  if(abs(mpu.acc_pitch) < mpu.acc_total) angle.pitch_acc = asin((float)mpu.acc_pitch/mpu.acc_total)* 57.296;          
  if(abs(mpu.acc_roll) < mpu.acc_total) angle.roll_acc = asin((float)mpu.acc_roll/mpu.acc_total)* -57.296;          
      
  angle.pitch_acc -= mpu.acc_pitch_offset;                                                  // offset này thì phải debug để trừ hoặc cộng lại cho về 0  
  angle.roll_acc -= mpu.acc_roll_offset;                                                  // vì MPU gá trên Quad ko bao giờ nằm phẳng 1 góc 0độ đc nên phải tự canh chỉnh lại làm sao 
                                                                           // cho góc pitch và roll của gia tốc về 0 khi để Quad nằm yên
                                                                           // ở đây trừ 4.8độ cho góc pitch và cộng 1độ cho góc roll
  
  angle.pitch = angle.pitch * 0.9995 + angle.pitch_acc * 0.0005;           // hệ số 0.9995 và 0.0005 thì xem tài liệu nước ngoài về bộ lọc bù có giới hạn về hệ số này 
  angle.roll = angle.roll * 0.9995 + angle.roll_acc * 0.0005;     
}
void calculate_angle_roll_pitch2() {
  angle.pitch += mpu.gyro_pitch * 0.00007634;                              // 0.00007634 = 1 / (200Hz / 65.5)      
  angle.roll  += mpu.gyro_roll * 0.00007634;                                     
  
  angle.pitch -= angle.roll * sin(mpu.gyro_yaw * 0.000001332);             // 0.000001332 = 0.00007634 * (3.142(PI) / 180)
  angle.roll  += angle.pitch * sin(mpu.gyro_yaw * 0.000001332);           

  mpu.acc_total = sqrt((mpu.acc_roll*mpu.acc_roll)+(mpu.acc_pitch*mpu.acc_pitch)+(mpu.acc_yaw*mpu.acc_yaw));                                              
  if(abs(mpu.acc_pitch) < mpu.acc_total) angle.pitch_acc = asin((float)mpu.acc_pitch/mpu.acc_total)* 57.296;          
  if(abs(mpu.acc_roll) < mpu.acc_total) angle.roll_acc = asin((float)mpu.acc_roll/mpu.acc_total)* -57.296;          
      
                                                 // cho góc pitch và roll của gia tốc về 0 khi để Quad nằm yên
                                                                           // ở đây trừ 4.8độ cho góc pitch và cộng 1độ cho góc roll
  
  angle.pitch = angle.pitch * 0.9995 + angle.pitch_acc * 0.0005;           // hệ số 0.9995 và 0.0005 thì xem tài liệu nước ngoài về bộ lọc bù có giới hạn về hệ số này 
  angle.roll = angle.roll * 0.9995 + angle.roll_acc * 0.0005;     
}
void  acc_get_offset(){
   for (calib_counter = 0; calib_counter < 100 ; calib_counter++){    // Đọc giá trị gyro 2000 lần và cộng dồn lại    
    if(calib_counter % 20 == 0)digitalWrite(12, !digitalRead(12));   
read_mpu_data();                                                    // Đọc dữ liệu accel và gyro thô từ mpu6050                                   
  calib_gyro_3_axis();                                                // Calib lại dữ liệu gyro thô
  correct_roll_pitch_yaw_data();                                      // Quy đổi chiều của gyro và accel 3 trục roll pitch yaw
                                       // Lọc input gyro cho pid
                                          // Kiểm tra trạng thái quadrotor  
  calculate_angle_roll_pitch();                                       // Tính các góc roll và pitch của quadrotor
   
  mpu.acc_pitch_offset+=angle.pitch_acc;
  mpu.acc_roll_offset+=angle.roll_acc;


    }
    mpu.acc_pitch_offset= mpu.acc_pitch_offset/100.0;
    mpu.acc_roll_offset=mpu.acc_roll_offset/100.0;
  
    


}
void sentdatatostm(){
  
    if(rx.throttle<1000)
    throtlle=1000;
    else
     throtlle=rx.throttle;
    String data = "D "  +String( angle.pitch)+" "+ String( angle.roll)+" " +String( throtlle)+" "+ String(battery_voltage) +" "+String(quadrotor_status)+" "+String(rx.standard_signal_channel[2])+" "+String(rx.standard_signal_channel[4] );
   Serial.println(data);
}
