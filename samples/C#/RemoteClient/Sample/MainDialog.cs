using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using Lib;

namespace Sample
{
    public partial class MainDialog : Form
    {
        private RequestBuilder requestBuilder;
        private RequestSender requestSender;

        public MainDialog()
        {
            InitializeComponent();
            cboLevel.SelectedIndex = 1; // INFO
            requestBuilder = new RequestBuilder(txtUsername.Text, txtPassword.Text);
            requestSender = new RequestSender(txtIp.Text, Int32.Parse(txtPort.Text));
        }

        private void btnWriteLog_Click(object sender, EventArgs e)
        {
            writeLog();
        }

        private void writeLog()
        {
            Int32 level = 0;
            switch (cboLevel.SelectedIndex)
            {
                case 0: level = 2; break;
                case 1: level = 4; break;
                case 2: level = 8; break;
                case 3: level = 16; break;
                case 4: level = 32; break;
                case 5: level = 64; break;
                case 6: level = 128; break;
                default: level = 0; break;
            }
            requestSender.send(requestBuilder.buildWriteLogsRequest(level, txtLogLine.Text, Int32.Parse(spnVerboseLevel.Value.ToString())));
        }

        private void cboLevel_SelectedIndexChanged(object sender, EventArgs e)
        {
            if (cboLevel.SelectedIndex == 5) // Verbose
            {
                spnVerboseLevel.Visible = true;
                cboLevel.Width = 128;
            }
            else
            {
                spnVerboseLevel.Visible = false;
                cboLevel.Width = 178;
            }
        }

        private void btnUpdate_Click(object sender, EventArgs e)
        {
            requestBuilder = new RequestBuilder(txtUsername.Text, txtPassword.Text);
            requestSender = new RequestSender(txtIp.Text, Int32.Parse(txtPort.Text));
        }
    }
}
