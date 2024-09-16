using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using ZedGraph;
using System.IO.Ports;
using System.Threading;
using GMap.NET.MapProviders;
using GMap.NET;
using GMap.NET.WindowsForms.Markers;
using GMap.NET.WindowsForms;


namespace gui
{
    public partial class Form1 : Form
    {

        delegate void serialcallback(string val);
        int tickstart, intmode=1;
        public Form1()
        {
            InitializeComponent();
        }
        string[] baud = { "1200", "2400", "4800", "9600", "115200","2500000" };
        string[] databit = { "5", "6", "7", "8" };
        double lat;
        double lng;

        private void Form1_Load(object sender, EventArgs e)
        {

         
            btnvisual.Text = "GET";
            btnvisual.BackColor = Color.Green;

            GraphPane myPane = zedGraphControl1.GraphPane;
            myPane.Title.Text = "góc pitch và roll của quadcopter";
            myPane.XAxis.Title.Text = "Thời gian (s)";
            myPane.YAxis.Title.Text = "Dữ liệu";
            RollingPointPairList list1 = new RollingPointPairList(60000);
            RollingPointPairList list2 = new RollingPointPairList(60000);
           

            //tao khung thong bap
            LineItem curve1 = myPane.AddCurve("anglepitch", list1, Color.Red, SymbolType.None);
            LineItem curve2 = myPane.AddCurve("angleroll", list2, Color.Green, SymbolType.None);
           

            //tao scale x ,y

            myPane.XAxis.Scale.Min = 0;
            myPane.XAxis.Scale.Max = 10;
            myPane.XAxis.Scale.MinorStep = 10;

            myPane.XAxis.Scale.MajorStep = 0.1;
            myPane.YAxis.Scale.Min = -50;
            myPane.YAxis.Scale.Max = 50;

            zedGraphControl1.AxisChange();
            tickstart = Environment.TickCount;

            string[] myport = SerialPort.GetPortNames();
            portname.Items.AddRange(myport);
            portbaud.Items.AddRange(baud);
            portdatabit.Items.AddRange(databit);

            // set up gmap
            map.DragButton = MouseButtons.Left;
            map.MapProvider = GMapProviders.GoogleMap;
            map.MinZoom = 1;
            map.MaxZoom = 100;
            map.Zoom = 10;

        }
     
        public void draw(string setpoint1, string setoint2)
        {
           double intsetpoint1;
            double intsetpoint2;
           
            double.TryParse(setpoint1, out intsetpoint1);
            double.TryParse(setoint2, out intsetpoint2);
         
            if (zedGraphControl1.GraphPane.CurveList.Count <= 0)
                return ;
            LineItem cuver1 = zedGraphControl1.GraphPane.CurveList[0] as LineItem;
            LineItem cuver2 = zedGraphControl1.GraphPane.CurveList[1] as LineItem;
            
            if (cuver1 == null)
                return;
            if (cuver2 == null)
                return;
            IPointListEdit list1 = cuver1.Points as IPointListEdit;
            IPointListEdit list2 = cuver2.Points as IPointListEdit;
            

            if (list1 == null)
                return;
            if (list2 == null)
                return;
            double time = (Environment.TickCount - tickstart) / 1000.0;
            list1.Add(time, intsetpoint1);
            list2.Add(time, intsetpoint2);
           
            Scale Xscale = zedGraphControl1.GraphPane.XAxis.Scale;
           
            if(time>Xscale.Max-Xscale.MajorStep)
            {
                if(intmode==1)
                {
                    Xscale.Max = time + Xscale.MajorStep;
                    Xscale.Min = time - 30.0;
                }
                else
                {
                    Xscale.Max = time + Xscale.MajorStep;
                    Xscale.Min =0;
                }
            }
            zedGraphControl1.AxisChange();
            zedGraphControl1.Invalidate();


        }

        private void button1_Click(object sender, EventArgs e)
        {
            //hide usecontrol 23
            listBox1.Items.Clear();

        }

        private void button2_Click(object sender, EventArgs e)
        {
            Invoke(new MethodInvoker(() =>

             serialPort1.Close()));

            Invoke(new MethodInvoker(() =>

                Close()));
        }

        private void button3_Click(object sender, EventArgs e)
        {
            if (ptnINPUT.Text == "RUN")
            {
                intmode = 1;
                ptnINPUT.Text = "STOP";
                timer1.Enabled = true;
            }
            else
            {
                ptnINPUT.Text = "RUN";
                intmode = 0;
                timer1.Enabled = false;
            }
          
        }

        private void button4_Click(object sender, EventArgs e)
        {
            BTNCONECT.Enabled = false;
            BTDISCONNECT.Enabled = true;
            if (!serialPort1.IsOpen)
            {
                try
                {
                    serialPort1.PortName = portname.Text;
                    serialPort1.BaudRate = int.Parse(portbaud.Text);
                    serialPort1.DataBits = int.Parse(portdatabit.Text);
                    serialPort1.Open();
                    

                   
                }
                catch (Exception ex)
                {
                    MessageBox.Show(ex.Message);

                }
            }
        }

        private void BTDISCONNECT_Click(object sender, EventArgs e)
        {
            BTNCONECT.Enabled = true;
            BTDISCONNECT.Enabled = false;
            try
            {
                
                serialPort1.Close();
               


            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message);

            }
        }
        string data = "";
        
        string[] data11= new string[14];

       
       
      
        private void serialPort1_DataReceived(object sender, SerialDataReceivedEventArgs e)
        {


            
            data = serialPort1.ReadLine();
            data11 = data.Split(' ');
           
           // length.Text = a.ToString();
            Invoke(new MethodInvoker(() =>


              listBox1.Items.Add(data)));
            




            if (listBox1.Items.Count> 200)
            {
               



                //Invoke(new MethodInvoker(() => 


                //  acess()));;
                
                    Invoke(new MethodInvoker(() =>

                   listBox1.Items.Clear()));
                 

                
               

            }
          

        }

        private void button3_Click_1(object sender, EventArgs e)
        {
          
                lat = Convert.ToDouble(txtlat.Text);
                lng = Convert.ToDouble(txtlong.Text);
                map.Position = new PointLatLng();

                PointLatLng point = new PointLatLng(lat, lng);
                GMapMarker marker = new GMarkerGoogle(point, GMarkerGoogleType.blue);
                //creat Gmap overlay
                GMapOverlay markers = new GMapOverlay("markers");
                markers.Markers.Add(marker);
                // cover map with overplay
                map.Overlays.Add(markers);
            
         




        }
        
        private void timer2_Tick(object sender, EventArgs e)
        {   if(data11[10]!=null)
                
               
            Invoke(new MethodInvoker(() =>

             lbthrottle.Text = data11[10]));
            if (data11[11] != null)
            {
             

                Invoke(new MethodInvoker(() =>

                 lbpower.Text =data11[11]));
            }
            
            if (data11[4]!=null | data11[5] != null)
            {
               

                Invoke(new MethodInvoker(() =>

                 txtlat.Text = data11[5]));
                Invoke(new MethodInvoker(() =>

                txtlong.Text = data11[4]));
            }
            if (data11[12] != null)
            {
                label2.Text = data11[12];
                if (data11[12] == "1")
                {
                    Invoke(new MethodInvoker(() =>

                  lbstatic.Text = "ready"));
                    Invoke(new MethodInvoker(() =>

                 lbstatic.BackColor = Color.Yellow));


                }
                else if (data11[12] == "2")
                {
                    lbstatic.Text = "ON";
                    lbstatic.BackColor = Color.Green;

                }
                else if (data11[12] == "0")
                {
                    lbstatic.Text = "Off";
                    lbstatic.BackColor = Color.Red;

                }
            
            }
            if(data11[6]!=null)
                {
                    sealt.Text = data11[6];
                }
                if (data11[1] != null)
                {
                    sealevel.Text = data11[1];
                }
                if (data11[2] != null)
                {
                    time.Text = data11[2];
                }
            if(data11[8]!=null|data11[9]!=null)
            {
                pitch.Text = data11[8];
                roll.Text = data11[9];
            }

            

        }

        private void splitContainer2_Panel1_Paint(object sender, PaintEventArgs e)
        {

        }

        private void button4_Click_1(object sender, EventArgs e)
        {
            timer2.Enabled = !timer2.Enabled;
            if (timer2.Enabled == false)
            {
                btnvisual.Text = "GET";
                btnvisual.BackColor = Color.Green;
            }
            else
            {
                btnvisual.Text = "STOP";
                btnvisual.BackColor = Color.Red;
            }
        }

        private void label8_Click(object sender, EventArgs e)
        {

        }

        private void timer3_Tick(object sender, EventArgs e)
        {
           
        }

        private void sealevel_Click(object sender, EventArgs e)
        {

        }

        private void timer1_Tick(object sender, EventArgs e)
        {
            Invoke(new MethodInvoker(() =>
     
            draw(data11[8], data11[9])));
         
        }
     
    }   
}
