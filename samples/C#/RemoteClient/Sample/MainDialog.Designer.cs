namespace Sample
{
    partial class MainDialog
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
            this.btnWriteLog = new System.Windows.Forms.Button();
            this.txtLogLine = new System.Windows.Forms.TextBox();
            this.cboLevel = new System.Windows.Forms.ComboBox();
            this.spnVerboseLevel = new System.Windows.Forms.NumericUpDown();
            this.grpServer = new System.Windows.Forms.GroupBox();
            this.txtPort = new System.Windows.Forms.TextBox();
            this.label3 = new System.Windows.Forms.Label();
            this.txtIp = new System.Windows.Forms.TextBox();
            this.label4 = new System.Windows.Forms.Label();
            this.txtPassword = new System.Windows.Forms.TextBox();
            this.label2 = new System.Windows.Forms.Label();
            this.txtUsername = new System.Windows.Forms.TextBox();
            this.label1 = new System.Windows.Forms.Label();
            this.btnUpdate = new System.Windows.Forms.Button();
            ((System.ComponentModel.ISupportInitialize)(this.spnVerboseLevel)).BeginInit();
            this.grpServer.SuspendLayout();
            this.SuspendLayout();
            // 
            // btnWriteLog
            // 
            this.btnWriteLog.Location = new System.Drawing.Point(607, 204);
            this.btnWriteLog.Name = "btnWriteLog";
            this.btnWriteLog.Size = new System.Drawing.Size(175, 60);
            this.btnWriteLog.TabIndex = 2;
            this.btnWriteLog.Text = "Write Log";
            this.btnWriteLog.UseVisualStyleBackColor = true;
            this.btnWriteLog.Click += new System.EventHandler(this.btnWriteLog_Click);
            // 
            // txtLogLine
            // 
            this.txtLogLine.Location = new System.Drawing.Point(12, 223);
            this.txtLogLine.Name = "txtLogLine";
            this.txtLogLine.Size = new System.Drawing.Size(405, 22);
            this.txtLogLine.TabIndex = 0;
            this.txtLogLine.Text = "My log line";
            // 
            // cboLevel
            // 
            this.cboLevel.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.cboLevel.FormattingEnabled = true;
            this.cboLevel.Items.AddRange(new object[] {
            "DEBUG",
            "INFO",
            "WARNING",
            "ERROR",
            "FATAL",
            "VERBOSE",
            "TRACE"});
            this.cboLevel.Location = new System.Drawing.Point(423, 221);
            this.cboLevel.Name = "cboLevel";
            this.cboLevel.Size = new System.Drawing.Size(178, 24);
            this.cboLevel.TabIndex = 1;
            this.cboLevel.SelectedIndexChanged += new System.EventHandler(this.cboLevel_SelectedIndexChanged);
            // 
            // spnVerboseLevel
            // 
            this.spnVerboseLevel.Location = new System.Drawing.Point(557, 221);
            this.spnVerboseLevel.Maximum = new decimal(new int[] {
            9,
            0,
            0,
            0});
            this.spnVerboseLevel.Minimum = new decimal(new int[] {
            1,
            0,
            0,
            0});
            this.spnVerboseLevel.Name = "spnVerboseLevel";
            this.spnVerboseLevel.Size = new System.Drawing.Size(44, 22);
            this.spnVerboseLevel.TabIndex = 3;
            this.spnVerboseLevel.Value = new decimal(new int[] {
            1,
            0,
            0,
            0});
            // 
            // grpServer
            // 
            this.grpServer.Controls.Add(this.btnUpdate);
            this.grpServer.Controls.Add(this.txtPassword);
            this.grpServer.Controls.Add(this.txtPort);
            this.grpServer.Controls.Add(this.label2);
            this.grpServer.Controls.Add(this.label3);
            this.grpServer.Controls.Add(this.txtUsername);
            this.grpServer.Controls.Add(this.label1);
            this.grpServer.Controls.Add(this.txtIp);
            this.grpServer.Controls.Add(this.label4);
            this.grpServer.Location = new System.Drawing.Point(12, 13);
            this.grpServer.Name = "grpServer";
            this.grpServer.Size = new System.Drawing.Size(770, 141);
            this.grpServer.TabIndex = 8;
            this.grpServer.TabStop = false;
            this.grpServer.Text = "Server";
            // 
            // txtPort
            // 
            this.txtPort.Location = new System.Drawing.Point(496, 25);
            this.txtPort.Name = "txtPort";
            this.txtPort.Size = new System.Drawing.Size(134, 22);
            this.txtPort.TabIndex = 11;
            this.txtPort.Text = "1592";
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(412, 28);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(38, 17);
            this.label3.TabIndex = 10;
            this.label3.Text = "Port:";
            // 
            // txtIp
            // 
            this.txtIp.Location = new System.Drawing.Point(225, 25);
            this.txtIp.Name = "txtIp";
            this.txtIp.Size = new System.Drawing.Size(156, 22);
            this.txtIp.TabIndex = 9;
            this.txtIp.Text = "192.168.1.7";
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Location = new System.Drawing.Point(140, 24);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(70, 17);
            this.label4.TabIndex = 8;
            this.label4.Text = "Server IP:";
            // 
            // txtPassword
            // 
            this.txtPassword.Location = new System.Drawing.Point(496, 58);
            this.txtPassword.Name = "txtPassword";
            this.txtPassword.PasswordChar = '*';
            this.txtPassword.Size = new System.Drawing.Size(134, 22);
            this.txtPassword.TabIndex = 11;
            this.txtPassword.Text = "pass";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(412, 61);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(73, 17);
            this.label2.TabIndex = 10;
            this.label2.Text = "Password:";
            // 
            // txtUsername
            // 
            this.txtUsername.Location = new System.Drawing.Point(225, 58);
            this.txtUsername.Name = "txtUsername";
            this.txtUsername.Size = new System.Drawing.Size(156, 22);
            this.txtUsername.TabIndex = 9;
            this.txtUsername.Text = "mkhan";
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(142, 61);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(77, 17);
            this.label1.TabIndex = 8;
            this.label1.Text = "Username:";
            // 
            // btnUpdate
            // 
            this.btnUpdate.Location = new System.Drawing.Point(640, 98);
            this.btnUpdate.Name = "btnUpdate";
            this.btnUpdate.Size = new System.Drawing.Size(124, 27);
            this.btnUpdate.TabIndex = 12;
            this.btnUpdate.Text = "Update";
            this.btnUpdate.UseVisualStyleBackColor = true;
            this.btnUpdate.Click += new System.EventHandler(this.btnUpdate_Click);
            // 
            // MainDialog
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(8F, 16F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(794, 318);
            this.Controls.Add(this.grpServer);
            this.Controls.Add(this.spnVerboseLevel);
            this.Controls.Add(this.cboLevel);
            this.Controls.Add(this.txtLogLine);
            this.Controls.Add(this.btnWriteLog);
            this.Name = "MainDialog";
            this.Text = "Easylogging++ Remote Client Sample";
            ((System.ComponentModel.ISupportInitialize)(this.spnVerboseLevel)).EndInit();
            this.grpServer.ResumeLayout(false);
            this.grpServer.PerformLayout();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Button btnWriteLog;
        private System.Windows.Forms.TextBox txtLogLine;
        private System.Windows.Forms.ComboBox cboLevel;
        private System.Windows.Forms.NumericUpDown spnVerboseLevel;
        private System.Windows.Forms.GroupBox grpServer;
        private System.Windows.Forms.TextBox txtPort;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.TextBox txtIp;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.TextBox txtPassword;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.TextBox txtUsername;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Button btnUpdate;
    }
}

