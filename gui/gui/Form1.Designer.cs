
namespace gui
{
    partial class Form1
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.components = new System.ComponentModel.Container();
            this.splitContainer1 = new System.Windows.Forms.SplitContainer();
            this.splitContainer2 = new System.Windows.Forms.SplitContainer();
            this.label8 = new System.Windows.Forms.Label();
            this.label7 = new System.Windows.Forms.Label();
            this.label6 = new System.Windows.Forms.Label();
            this.label5 = new System.Windows.Forms.Label();
            this.label1 = new System.Windows.Forms.Label();
            this.pictureBox1 = new System.Windows.Forms.PictureBox();
            this.tabcontroll = new System.Windows.Forms.TabControl();
            this.tabPage1 = new System.Windows.Forms.TabPage();
            this.roll = new System.Windows.Forms.Label();
            this.pitch = new System.Windows.Forms.Label();
            this.ptnINPUT = new System.Windows.Forms.Button();
            this.zedGraphControl1 = new ZedGraph.ZedGraphControl();
            this.tabPage2 = new System.Windows.Forms.TabPage();
            this.sealt = new System.Windows.Forms.Label();
            this.sealevel = new System.Windows.Forms.Label();
            this.time = new System.Windows.Forms.Label();
            this.button3 = new System.Windows.Forms.Button();
            this.txtlong = new System.Windows.Forms.TextBox();
            this.longtidude = new System.Windows.Forms.Label();
            this.txtlat = new System.Windows.Forms.TextBox();
            this.latitude = new System.Windows.Forms.Label();
            this.map = new GMap.NET.WindowsForms.GMapControl();
            this.tabPage3 = new System.Windows.Forms.TabPage();
            this.length = new System.Windows.Forms.Label();
            this.button1 = new System.Windows.Forms.Button();
            this.listBox1 = new System.Windows.Forms.ListBox();
            this.panel2 = new System.Windows.Forms.Panel();
            this.BTDISCONNECT = new System.Windows.Forms.Button();
            this.BTNCONECT = new System.Windows.Forms.Button();
            this.portdatabit = new System.Windows.Forms.ComboBox();
            this.portbaud = new System.Windows.Forms.ComboBox();
            this.portname = new System.Windows.Forms.ComboBox();
            this.panel1 = new System.Windows.Forms.Panel();
            this.btnvisual = new System.Windows.Forms.Button();
            this.label4 = new System.Windows.Forms.Label();
            this.label3 = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.lbthrottle = new System.Windows.Forms.Label();
            this.lbpower = new System.Windows.Forms.Label();
            this.lbstatic = new System.Windows.Forms.Label();
            this.button2 = new System.Windows.Forms.Button();
            this.serialPort1 = new System.IO.Ports.SerialPort(this.components);
            this.timer1 = new System.Windows.Forms.Timer(this.components);
            this.timer2 = new System.Windows.Forms.Timer(this.components);
            this.timer3 = new System.Windows.Forms.Timer(this.components);
            ((System.ComponentModel.ISupportInitialize)(this.splitContainer1)).BeginInit();
            this.splitContainer1.Panel1.SuspendLayout();
            this.splitContainer1.Panel2.SuspendLayout();
            this.splitContainer1.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.splitContainer2)).BeginInit();
            this.splitContainer2.Panel1.SuspendLayout();
            this.splitContainer2.Panel2.SuspendLayout();
            this.splitContainer2.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox1)).BeginInit();
            this.tabcontroll.SuspendLayout();
            this.tabPage1.SuspendLayout();
            this.tabPage2.SuspendLayout();
            this.tabPage3.SuspendLayout();
            this.panel2.SuspendLayout();
            this.panel1.SuspendLayout();
            this.SuspendLayout();
            // 
            // splitContainer1
            // 
            this.splitContainer1.Dock = System.Windows.Forms.DockStyle.Fill;
            this.splitContainer1.Location = new System.Drawing.Point(0, 0);
            this.splitContainer1.Name = "splitContainer1";
            // 
            // splitContainer1.Panel1
            // 
            this.splitContainer1.Panel1.BackColor = System.Drawing.SystemColors.Info;
            this.splitContainer1.Panel1.Controls.Add(this.splitContainer2);
            // 
            // splitContainer1.Panel2
            // 
            this.splitContainer1.Panel2.BackColor = System.Drawing.SystemColors.ActiveCaption;
            this.splitContainer1.Panel2.Controls.Add(this.panel2);
            this.splitContainer1.Panel2.Controls.Add(this.panel1);
            this.splitContainer1.Size = new System.Drawing.Size(1205, 746);
            this.splitContainer1.SplitterDistance = 987;
            this.splitContainer1.SplitterWidth = 10;
            this.splitContainer1.TabIndex = 0;
            // 
            // splitContainer2
            // 
            this.splitContainer2.Dock = System.Windows.Forms.DockStyle.Fill;
            this.splitContainer2.Location = new System.Drawing.Point(0, 0);
            this.splitContainer2.Name = "splitContainer2";
            this.splitContainer2.Orientation = System.Windows.Forms.Orientation.Horizontal;
            // 
            // splitContainer2.Panel1
            // 
            this.splitContainer2.Panel1.BackColor = System.Drawing.SystemColors.GradientInactiveCaption;
            this.splitContainer2.Panel1.Controls.Add(this.label8);
            this.splitContainer2.Panel1.Controls.Add(this.label7);
            this.splitContainer2.Panel1.Controls.Add(this.label6);
            this.splitContainer2.Panel1.Controls.Add(this.label5);
            this.splitContainer2.Panel1.Controls.Add(this.label1);
            this.splitContainer2.Panel1.Controls.Add(this.pictureBox1);
            this.splitContainer2.Panel1.Paint += new System.Windows.Forms.PaintEventHandler(this.splitContainer2_Panel1_Paint);
            // 
            // splitContainer2.Panel2
            // 
            this.splitContainer2.Panel2.BackColor = System.Drawing.SystemColors.Info;
            this.splitContainer2.Panel2.Controls.Add(this.tabcontroll);
            this.splitContainer2.Size = new System.Drawing.Size(987, 746);
            this.splitContainer2.SplitterDistance = 186;
            this.splitContainer2.SplitterWidth = 10;
            this.splitContainer2.TabIndex = 0;
            // 
            // label8
            // 
            this.label8.AutoSize = true;
            this.label8.Font = new System.Drawing.Font("Microsoft Sans Serif", 9F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label8.Location = new System.Drawing.Point(665, 148);
            this.label8.Name = "label8";
            this.label8.Size = new System.Drawing.Size(322, 22);
            this.label8.TabIndex = 5;
            this.label8.Text = "SV: LƯƠNG CAO THUẦN 1814218";
            this.label8.Click += new System.EventHandler(this.label8_Click);
            // 
            // label7
            // 
            this.label7.AutoSize = true;
            this.label7.Font = new System.Drawing.Font("Times New Roman", 9F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label7.Location = new System.Drawing.Point(689, 124);
            this.label7.Name = "label7";
            this.label7.Size = new System.Drawing.Size(254, 20);
            this.label7.TabIndex = 4;
            this.label7.Text = "GVHD TS.HOÀNG MINH TRÍ";
            // 
            // label6
            // 
            this.label6.AutoSize = true;
            this.label6.Font = new System.Drawing.Font("Microsoft Sans Serif", 14F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label6.Location = new System.Drawing.Point(297, 46);
            this.label6.Name = "label6";
            this.label6.Size = new System.Drawing.Size(562, 32);
            this.label6.TabIndex = 3;
            this.label6.Text = "Bộ môn kĩ thuật điều khiển -Tự động hóa";
            // 
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.Font = new System.Drawing.Font("Times New Roman", 16F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label5.Location = new System.Drawing.Point(203, 9);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(689, 36);
            this.label5.TabIndex = 2;
            this.label5.Text = "TRƯỜNG ĐẠI HỌC BÁCH KHOA HỒ CHÍ MINH";
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Font = new System.Drawing.Font("Times New Roman", 18F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label1.ForeColor = System.Drawing.Color.FromArgb(((int)(((byte)(0)))), ((int)(((byte)(0)))), ((int)(((byte)(192)))));
            this.label1.Location = new System.Drawing.Point(297, 78);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(463, 41);
            this.label1.TabIndex = 1;
            this.label1.Text = "MONITOR QUADCOPTER";
            // 
            // pictureBox1
            // 
            this.pictureBox1.Image = global::gui.Properties.Resources.loggo3;
            this.pictureBox1.Location = new System.Drawing.Point(0, 0);
            this.pictureBox1.Name = "pictureBox1";
            this.pictureBox1.Size = new System.Drawing.Size(131, 136);
            this.pictureBox1.SizeMode = System.Windows.Forms.PictureBoxSizeMode.Zoom;
            this.pictureBox1.TabIndex = 0;
            this.pictureBox1.TabStop = false;
            // 
            // tabcontroll
            // 
            this.tabcontroll.Controls.Add(this.tabPage1);
            this.tabcontroll.Controls.Add(this.tabPage2);
            this.tabcontroll.Controls.Add(this.tabPage3);
            this.tabcontroll.Cursor = System.Windows.Forms.Cursors.No;
            this.tabcontroll.Location = new System.Drawing.Point(3, 3);
            this.tabcontroll.Name = "tabcontroll";
            this.tabcontroll.SelectedIndex = 0;
            this.tabcontroll.Size = new System.Drawing.Size(899, 536);
            this.tabcontroll.TabIndex = 3;
            // 
            // tabPage1
            // 
            this.tabPage1.Controls.Add(this.roll);
            this.tabPage1.Controls.Add(this.pitch);
            this.tabPage1.Controls.Add(this.ptnINPUT);
            this.tabPage1.Controls.Add(this.zedGraphControl1);
            this.tabPage1.Location = new System.Drawing.Point(4, 29);
            this.tabPage1.Name = "tabPage1";
            this.tabPage1.Padding = new System.Windows.Forms.Padding(3);
            this.tabPage1.Size = new System.Drawing.Size(891, 503);
            this.tabPage1.TabIndex = 0;
            this.tabPage1.Text = "ANGLE";
            this.tabPage1.UseVisualStyleBackColor = true;
            // 
            // roll
            // 
            this.roll.AutoSize = true;
            this.roll.Font = new System.Drawing.Font("Times New Roman", 10F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.roll.ForeColor = System.Drawing.Color.FromArgb(((int)(((byte)(0)))), ((int)(((byte)(192)))), ((int)(((byte)(0)))));
            this.roll.Location = new System.Drawing.Point(760, 177);
            this.roll.Name = "roll";
            this.roll.Size = new System.Drawing.Size(83, 23);
            this.roll.TabIndex = 4;
            this.roll.Text = "angleroll";
            // 
            // pitch
            // 
            this.pitch.AutoSize = true;
            this.pitch.Font = new System.Drawing.Font("Times New Roman", 10F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.pitch.ForeColor = System.Drawing.Color.Red;
            this.pitch.Location = new System.Drawing.Point(761, 125);
            this.pitch.Name = "pitch";
            this.pitch.Size = new System.Drawing.Size(96, 23);
            this.pitch.TabIndex = 3;
            this.pitch.Text = "anglepitch";
            // 
            // ptnINPUT
            // 
            this.ptnINPUT.Location = new System.Drawing.Point(753, 26);
            this.ptnINPUT.Name = "ptnINPUT";
            this.ptnINPUT.Size = new System.Drawing.Size(100, 49);
            this.ptnINPUT.TabIndex = 2;
            this.ptnINPUT.Text = "RUN";
            this.ptnINPUT.UseVisualStyleBackColor = true;
            this.ptnINPUT.Click += new System.EventHandler(this.button3_Click);
            // 
            // zedGraphControl1
            // 
            this.zedGraphControl1.Location = new System.Drawing.Point(14, 9);
            this.zedGraphControl1.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
            this.zedGraphControl1.Name = "zedGraphControl1";
            this.zedGraphControl1.ScrollGrace = 0D;
            this.zedGraphControl1.ScrollMaxX = 0D;
            this.zedGraphControl1.ScrollMaxY = 0D;
            this.zedGraphControl1.ScrollMaxY2 = 0D;
            this.zedGraphControl1.ScrollMinX = 0D;
            this.zedGraphControl1.ScrollMinY = 0D;
            this.zedGraphControl1.ScrollMinY2 = 0D;
            this.zedGraphControl1.Size = new System.Drawing.Size(739, 481);
            this.zedGraphControl1.TabIndex = 0;
            this.zedGraphControl1.UseExtendedPrintDialog = true;
            // 
            // tabPage2
            // 
            this.tabPage2.Controls.Add(this.sealt);
            this.tabPage2.Controls.Add(this.sealevel);
            this.tabPage2.Controls.Add(this.time);
            this.tabPage2.Controls.Add(this.button3);
            this.tabPage2.Controls.Add(this.txtlong);
            this.tabPage2.Controls.Add(this.longtidude);
            this.tabPage2.Controls.Add(this.txtlat);
            this.tabPage2.Controls.Add(this.latitude);
            this.tabPage2.Controls.Add(this.map);
            this.tabPage2.Font = new System.Drawing.Font("Times New Roman", 14F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.tabPage2.Location = new System.Drawing.Point(4, 29);
            this.tabPage2.Name = "tabPage2";
            this.tabPage2.Padding = new System.Windows.Forms.Padding(3);
            this.tabPage2.Size = new System.Drawing.Size(891, 503);
            this.tabPage2.TabIndex = 1;
            this.tabPage2.Text = "MAP";
            this.tabPage2.UseVisualStyleBackColor = true;
            // 
            // sealt
            // 
            this.sealt.AutoSize = true;
            this.sealt.Location = new System.Drawing.Point(730, 427);
            this.sealt.Name = "sealt";
            this.sealt.Size = new System.Drawing.Size(68, 32);
            this.sealt.TabIndex = 8;
            this.sealt.Text = "sealt";
            // 
            // sealevel
            // 
            this.sealevel.AutoSize = true;
            this.sealevel.Font = new System.Drawing.Font("Times New Roman", 14F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.sealevel.ForeColor = System.Drawing.SystemColors.ControlText;
            this.sealevel.Location = new System.Drawing.Point(730, 371);
            this.sealevel.Name = "sealevel";
            this.sealevel.Size = new System.Drawing.Size(105, 32);
            this.sealevel.TabIndex = 7;
            this.sealevel.Tag = "";
            this.sealevel.Text = "sealevel";
            this.sealevel.Click += new System.EventHandler(this.sealevel_Click);
            // 
            // time
            // 
            this.time.AutoSize = true;
            this.time.Font = new System.Drawing.Font("Times New Roman", 14F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.time.ForeColor = System.Drawing.SystemColors.ControlText;
            this.time.Location = new System.Drawing.Point(730, 315);
            this.time.Name = "time";
            this.time.Size = new System.Drawing.Size(65, 32);
            this.time.TabIndex = 6;
            this.time.Tag = "thoigian";
            this.time.Text = "time";
            // 
            // button3
            // 
            this.button3.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.button3.Font = new System.Drawing.Font("Times New Roman", 9F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.button3.Location = new System.Drawing.Point(760, 225);
            this.button3.Name = "button3";
            this.button3.Size = new System.Drawing.Size(120, 59);
            this.button3.TabIndex = 5;
            this.button3.Text = "Load into MAP";
            this.button3.UseVisualStyleBackColor = true;
            this.button3.Click += new System.EventHandler(this.button3_Click_1);
            // 
            // txtlong
            // 
            this.txtlong.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.txtlong.Location = new System.Drawing.Point(736, 174);
            this.txtlong.Name = "txtlong";
            this.txtlong.Size = new System.Drawing.Size(149, 40);
            this.txtlong.TabIndex = 4;
            // 
            // longtidude
            // 
            this.longtidude.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.longtidude.AutoSize = true;
            this.longtidude.Font = new System.Drawing.Font("Times New Roman", 9F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.longtidude.Location = new System.Drawing.Point(770, 136);
            this.longtidude.Name = "longtidude";
            this.longtidude.Size = new System.Drawing.Size(88, 20);
            this.longtidude.TabIndex = 3;
            this.longtidude.Text = "longtitude";
            // 
            // txtlat
            // 
            this.txtlat.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.txtlat.Location = new System.Drawing.Point(736, 74);
            this.txtlat.Name = "txtlat";
            this.txtlat.Size = new System.Drawing.Size(149, 40);
            this.txtlat.TabIndex = 2;
            // 
            // latitude
            // 
            this.latitude.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.latitude.AutoSize = true;
            this.latitude.Font = new System.Drawing.Font("Times New Roman", 10F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.latitude.Location = new System.Drawing.Point(770, 36);
            this.latitude.Name = "latitude";
            this.latitude.Size = new System.Drawing.Size(74, 23);
            this.latitude.TabIndex = 1;
            this.latitude.Text = "latitude";
            // 
            // map
            // 
            this.map.Bearing = 0F;
            this.map.CanDragMap = true;
            this.map.EmptyTileColor = System.Drawing.Color.Navy;
            this.map.GrayScaleMode = false;
            this.map.HelperLineOption = GMap.NET.WindowsForms.HelperLineOptions.DontShow;
            this.map.LevelsKeepInMemmory = 5;
            this.map.Location = new System.Drawing.Point(3, 6);
            this.map.MarkersEnabled = true;
            this.map.MaxZoom = 2;
            this.map.MinZoom = 2;
            this.map.MouseWheelZoomEnabled = true;
            this.map.MouseWheelZoomType = GMap.NET.MouseWheelZoomType.MousePositionAndCenter;
            this.map.Name = "map";
            this.map.NegativeMode = false;
            this.map.PolygonsEnabled = true;
            this.map.RetryLoadTile = 0;
            this.map.RoutesEnabled = true;
            this.map.ScaleMode = GMap.NET.WindowsForms.ScaleModes.Integer;
            this.map.SelectedAreaFillColor = System.Drawing.Color.FromArgb(((int)(((byte)(33)))), ((int)(((byte)(65)))), ((int)(((byte)(105)))), ((int)(((byte)(225)))));
            this.map.ShowTileGridLines = false;
            this.map.Size = new System.Drawing.Size(713, 486);
            this.map.TabIndex = 0;
            this.map.Zoom = 0D;
            // 
            // tabPage3
            // 
            this.tabPage3.Controls.Add(this.length);
            this.tabPage3.Controls.Add(this.button1);
            this.tabPage3.Controls.Add(this.listBox1);
            this.tabPage3.Location = new System.Drawing.Point(4, 29);
            this.tabPage3.Name = "tabPage3";
            this.tabPage3.Padding = new System.Windows.Forms.Padding(3);
            this.tabPage3.Size = new System.Drawing.Size(891, 503);
            this.tabPage3.TabIndex = 2;
            this.tabPage3.Text = "RECEIVE";
            this.tabPage3.UseVisualStyleBackColor = true;
            // 
            // length
            // 
            this.length.AutoSize = true;
            this.length.Font = new System.Drawing.Font("Times New Roman", 10F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.length.Location = new System.Drawing.Point(771, 142);
            this.length.Name = "length";
            this.length.Size = new System.Drawing.Size(62, 23);
            this.length.TabIndex = 3;
            this.length.Text = "length";
            // 
            // button1
            // 
            this.button1.Location = new System.Drawing.Point(746, 46);
            this.button1.Name = "button1";
            this.button1.Size = new System.Drawing.Size(107, 53);
            this.button1.TabIndex = 0;
            this.button1.Text = "CLEAR";
            this.button1.UseVisualStyleBackColor = true;
            this.button1.Click += new System.EventHandler(this.button1_Click);
            // 
            // listBox1
            // 
            this.listBox1.FormattingEnabled = true;
            this.listBox1.ItemHeight = 20;
            this.listBox1.Location = new System.Drawing.Point(6, 6);
            this.listBox1.Name = "listBox1";
            this.listBox1.Size = new System.Drawing.Size(741, 464);
            this.listBox1.TabIndex = 2;
            // 
            // panel2
            // 
            this.panel2.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(128)))), ((int)(((byte)(255)))), ((int)(((byte)(128)))));
            this.panel2.Controls.Add(this.BTDISCONNECT);
            this.panel2.Controls.Add(this.BTNCONECT);
            this.panel2.Controls.Add(this.portdatabit);
            this.panel2.Controls.Add(this.portbaud);
            this.panel2.Controls.Add(this.portname);
            this.panel2.Location = new System.Drawing.Point(13, 20);
            this.panel2.Name = "panel2";
            this.panel2.Size = new System.Drawing.Size(157, 267);
            this.panel2.TabIndex = 1;
            // 
            // BTDISCONNECT
            // 
            this.BTDISCONNECT.Location = new System.Drawing.Point(20, 217);
            this.BTDISCONNECT.Name = "BTDISCONNECT";
            this.BTDISCONNECT.Size = new System.Drawing.Size(116, 40);
            this.BTDISCONNECT.TabIndex = 4;
            this.BTDISCONNECT.Text = "DISCONECT";
            this.BTDISCONNECT.UseVisualStyleBackColor = true;
            this.BTDISCONNECT.Click += new System.EventHandler(this.BTDISCONNECT_Click);
            // 
            // BTNCONECT
            // 
            this.BTNCONECT.Location = new System.Drawing.Point(18, 155);
            this.BTNCONECT.Name = "BTNCONECT";
            this.BTNCONECT.Size = new System.Drawing.Size(119, 47);
            this.BTNCONECT.TabIndex = 3;
            this.BTNCONECT.Text = "CONNECT";
            this.BTNCONECT.UseVisualStyleBackColor = true;
            this.BTNCONECT.Click += new System.EventHandler(this.button4_Click);
            // 
            // portdatabit
            // 
            this.portdatabit.FormattingEnabled = true;
            this.portdatabit.Location = new System.Drawing.Point(17, 104);
            this.portdatabit.Name = "portdatabit";
            this.portdatabit.Size = new System.Drawing.Size(121, 28);
            this.portdatabit.TabIndex = 2;
            // 
            // portbaud
            // 
            this.portbaud.FormattingEnabled = true;
            this.portbaud.Location = new System.Drawing.Point(17, 66);
            this.portbaud.Name = "portbaud";
            this.portbaud.Size = new System.Drawing.Size(121, 28);
            this.portbaud.TabIndex = 1;
            // 
            // portname
            // 
            this.portname.FormattingEnabled = true;
            this.portname.Location = new System.Drawing.Point(15, 19);
            this.portname.Name = "portname";
            this.portname.Size = new System.Drawing.Size(121, 28);
            this.portname.TabIndex = 0;
            // 
            // panel1
            // 
            this.panel1.BackColor = System.Drawing.Color.PaleGoldenrod;
            this.panel1.Controls.Add(this.btnvisual);
            this.panel1.Controls.Add(this.label4);
            this.panel1.Controls.Add(this.label3);
            this.panel1.Controls.Add(this.label2);
            this.panel1.Controls.Add(this.lbthrottle);
            this.panel1.Controls.Add(this.lbpower);
            this.panel1.Controls.Add(this.lbstatic);
            this.panel1.Controls.Add(this.button2);
            this.panel1.Location = new System.Drawing.Point(13, 283);
            this.panel1.Name = "panel1";
            this.panel1.Size = new System.Drawing.Size(157, 421);
            this.panel1.TabIndex = 0;
            // 
            // btnvisual
            // 
            this.btnvisual.BackColor = System.Drawing.Color.PapayaWhip;
            this.btnvisual.Font = new System.Drawing.Font("Microsoft Sans Serif", 16F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.btnvisual.Location = new System.Drawing.Point(3, 281);
            this.btnvisual.Name = "btnvisual";
            this.btnvisual.Size = new System.Drawing.Size(154, 52);
            this.btnvisual.TabIndex = 8;
            this.btnvisual.Text = "GET";
            this.btnvisual.UseVisualStyleBackColor = false;
            this.btnvisual.Click += new System.EventHandler(this.button4_Click_1);
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.BackColor = System.Drawing.Color.OldLace;
            this.label4.Font = new System.Drawing.Font("Microsoft Sans Serif", 10F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label4.Location = new System.Drawing.Point(12, 185);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(78, 25);
            this.label4.TabIndex = 7;
            this.label4.Text = "throttle";
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.BackColor = System.Drawing.Color.PaleGreen;
            this.label3.Font = new System.Drawing.Font("Microsoft Sans Serif", 8F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label3.Location = new System.Drawing.Point(6, 102);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(118, 20);
            this.label3.TabIndex = 6;
            this.label3.Text = "battery power";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.BackColor = System.Drawing.Color.PaleTurquoise;
            this.label2.Font = new System.Drawing.Font("Microsoft Sans Serif", 10F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label2.Location = new System.Drawing.Point(7, 16);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(63, 25);
            this.label2.TabIndex = 5;
            this.label2.Text = "static";
            // 
            // lbthrottle
            // 
            this.lbthrottle.AutoSize = true;
            this.lbthrottle.BackColor = System.Drawing.Color.Chartreuse;
            this.lbthrottle.Font = new System.Drawing.Font("Microsoft Sans Serif", 20F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.lbthrottle.ForeColor = System.Drawing.SystemColors.ControlText;
            this.lbthrottle.Location = new System.Drawing.Point(4, 210);
            this.lbthrottle.Name = "lbthrottle";
            this.lbthrottle.Size = new System.Drawing.Size(150, 46);
            this.lbthrottle.TabIndex = 4;
            this.lbthrottle.Text = "throttle";
            // 
            // lbpower
            // 
            this.lbpower.AutoSize = true;
            this.lbpower.BackColor = System.Drawing.Color.Blue;
            this.lbpower.Font = new System.Drawing.Font("Microsoft Sans Serif", 20F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.lbpower.Location = new System.Drawing.Point(2, 122);
            this.lbpower.Name = "lbpower";
            this.lbpower.Size = new System.Drawing.Size(125, 46);
            this.lbpower.TabIndex = 3;
            this.lbpower.Text = "100%";
            // 
            // lbstatic
            // 
            this.lbstatic.AutoSize = true;
            this.lbstatic.BackColor = System.Drawing.Color.Red;
            this.lbstatic.Font = new System.Drawing.Font("Microsoft Sans Serif", 22F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.lbstatic.Location = new System.Drawing.Point(1, 41);
            this.lbstatic.Name = "lbstatic";
            this.lbstatic.Size = new System.Drawing.Size(130, 52);
            this.lbstatic.TabIndex = 2;
            this.lbstatic.Text = "static";
            // 
            // button2
            // 
            this.button2.BackColor = System.Drawing.Color.Gray;
            this.button2.Location = new System.Drawing.Point(20, 351);
            this.button2.Name = "button2";
            this.button2.Size = new System.Drawing.Size(122, 43);
            this.button2.TabIndex = 1;
            this.button2.Text = "EXIT";
            this.button2.UseVisualStyleBackColor = false;
            this.button2.Click += new System.EventHandler(this.button2_Click);
            // 
            // serialPort1
            // 
            this.serialPort1.DataReceived += new System.IO.Ports.SerialDataReceivedEventHandler(this.serialPort1_DataReceived);
            // 
            // timer1
            // 
            this.timer1.Interval = 1;
            this.timer1.Tick += new System.EventHandler(this.timer1_Tick);
            // 
            // timer2
            // 
            this.timer2.Interval = 500;
            this.timer2.Tick += new System.EventHandler(this.timer2_Tick);
            // 
            // timer3
            // 
            this.timer3.Interval = 500;
            this.timer3.Tick += new System.EventHandler(this.timer3_Tick);
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(9F, 20F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(1205, 746);
            this.Controls.Add(this.splitContainer1);
            this.Name = "Form1";
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
            this.Text = "Form1";
            this.Load += new System.EventHandler(this.Form1_Load);
            this.splitContainer1.Panel1.ResumeLayout(false);
            this.splitContainer1.Panel2.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)(this.splitContainer1)).EndInit();
            this.splitContainer1.ResumeLayout(false);
            this.splitContainer2.Panel1.ResumeLayout(false);
            this.splitContainer2.Panel1.PerformLayout();
            this.splitContainer2.Panel2.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)(this.splitContainer2)).EndInit();
            this.splitContainer2.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox1)).EndInit();
            this.tabcontroll.ResumeLayout(false);
            this.tabPage1.ResumeLayout(false);
            this.tabPage1.PerformLayout();
            this.tabPage2.ResumeLayout(false);
            this.tabPage2.PerformLayout();
            this.tabPage3.ResumeLayout(false);
            this.tabPage3.PerformLayout();
            this.panel2.ResumeLayout(false);
            this.panel1.ResumeLayout(false);
            this.panel1.PerformLayout();
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.SplitContainer splitContainer1;
        private System.Windows.Forms.SplitContainer splitContainer2;
        private System.Windows.Forms.PictureBox pictureBox1;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Panel panel2;
        private System.Windows.Forms.Panel panel1;
        private System.Windows.Forms.Button ptnINPUT;
        private System.Windows.Forms.Button button2;
        private System.Windows.Forms.Button button1;
        private System.Windows.Forms.TabControl tabcontroll;
        private System.Windows.Forms.TabPage tabPage1;
        private System.Windows.Forms.TabPage tabPage2;
        private System.Windows.Forms.TabPage tabPage3;
        private ZedGraph.ZedGraphControl zedGraphControl1;
        private System.Windows.Forms.ComboBox portname;
        private System.IO.Ports.SerialPort serialPort1;
        private System.Windows.Forms.ComboBox portbaud;
        private System.Windows.Forms.ComboBox portdatabit;
        private System.Windows.Forms.Button BTNCONECT;
        private System.Windows.Forms.Button BTDISCONNECT;
        private System.Windows.Forms.ListBox listBox1;
        private System.Windows.Forms.Timer timer1;
        private GMap.NET.WindowsForms.GMapControl map;
        private System.Windows.Forms.Button button3;
        private System.Windows.Forms.TextBox txtlong;
        private System.Windows.Forms.Label longtidude;
        private System.Windows.Forms.TextBox txtlat;
        private System.Windows.Forms.Label latitude;
        private System.Windows.Forms.Label lbstatic;
        private System.Windows.Forms.Timer timer2;
        private System.Windows.Forms.Label lbthrottle;
        private System.Windows.Forms.Label lbpower;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Button btnvisual;
        private System.Windows.Forms.Label label6;
        private System.Windows.Forms.Label label5;
        private System.Windows.Forms.Label label8;
        private System.Windows.Forms.Label label7;
        private System.Windows.Forms.Timer timer3;
        private System.Windows.Forms.Label sealt;
        private System.Windows.Forms.Label sealevel;
        private System.Windows.Forms.Label time;
        private System.Windows.Forms.Label roll;
        private System.Windows.Forms.Label pitch;
        private System.Windows.Forms.Label length;
    }
}

