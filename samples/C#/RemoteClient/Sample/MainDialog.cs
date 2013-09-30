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
            btnWriteLog.Enabled = false;
            Int32 level = 1 << (cboLevel.SelectedIndex + 1);
            for (int i = 1; i < 100; ++i)
            {
                writeLog(level, txtLogLine.Text + i);   
            }
            btnWriteLog.Enabled = true;
        }

        private void writeLog(int level, String txt)
        {
            requestSender.send(requestBuilder.buildWriteLogsRequest(level, txt, Int32.Parse(spnVerboseLevel.Value.ToString())));
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
