using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.IO;
using System.Net.Sockets;

namespace Lib
{
    public class RequestSender
    {
        public RequestSender(String server, Int32 port)
        {
            this.server = server;
            this.port = port;
        }

        public void send(String message)
        {
            try
            {
                TcpClient tcpClient = new TcpClient(server, port);
                Byte[] data = System.Text.Encoding.ASCII.GetBytes(message);

                NetworkStream stream = tcpClient.GetStream();

                stream.Write(data, 0, data.Length);
                data = new Byte[256];

                String responseData = String.Empty;

                Int32 bytes = stream.Read(data, 0, data.Length);
                responseData = System.Text.Encoding.ASCII.GetString(data, 0, bytes);
                Console.WriteLine("Received: {0}", responseData);
                stream.Flush();
            }
            catch (ArgumentNullException ex)
            {
                Console.WriteLine("ArgumentNullException: {0}", ex);
            }
            catch (SocketException ex)
            {
                Console.WriteLine("SocketException: {0}", ex);
            }
            catch (IOException ex)
            {
                Console.WriteLine("IOException: {0}", ex);
            }
        }

        private String server;
        private Int32 port;
    }
}
