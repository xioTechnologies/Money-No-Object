using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Reflection;
using System.IO.Ports;
using Rug.Osc;
using System.Net;

namespace Wireless_RIFID_Reader_Console
{
    class Program
    {
        const string serialPortName = "COM3";
        const string ipAddress = "255.255.255.255";
        const ushort udpPort = 5667;

        static void Main(string[] args)
        {
            Console.WriteLine(Assembly.GetExecutingAssembly().GetName().Name + " " + Assembly.GetExecutingAssembly().GetName().Version.Major.ToString() + "." + Assembly.GetExecutingAssembly().GetName().Version.Minor.ToString());
            Console.WriteLine("Press Esc at any time to exit.");
            Console.WriteLine();
            OscSender oscSender = null;
            SerialPort serialPort = null;
            do
            {
                try
                {
                    // Open OSC sender
                    Console.WriteLine("Connecting to OSC sender \"" + ipAddress + "\" (" + udpPort.ToString() + ").");
                    oscSender = new OscSender(IPAddress.Parse(ipAddress), udpPort);
                    oscSender.Connect();

                    // Open serial port
                    Console.WriteLine("Opening serial port \"" + serialPortName + "\"" + ".");
                    serialPort = new SerialPort(serialPortName, 115200, Parity.None, 8, StopBits.One);
                    serialPort.Open();

                    // Serial port DataReceived event
                    string rxString = "";
                    int count = 0;
                    serialPort.DataReceived += new SerialDataReceivedEventHandler(delegate(object sender, SerialDataReceivedEventArgs e)
                    {
                        // Fetch bytes from serial port
                        int bytesToRead = serialPort.BytesToRead;
                        byte[] readBuffer = new byte[bytesToRead];
                        serialPort.Read(readBuffer, 0, bytesToRead);

                        // Process bytes one by one
                        foreach (byte b in readBuffer)
                        {
                            if ((char)b == '\n')
                            {
                                Console.WriteLine("Data received: \"" + rxString + "\", Count: " + (++count).ToString());
                                try
                                {
                                    string[] csv = rxString.Split(',');
                                    if (csv.Length != 3)
                                    {
                                        throw new Exception("String does not contain expected separated values.");
                                    }
                                    oscSender.Send(new OscMessage("/pay", int.Parse(csv[0]), csv[1], float.Parse(csv[2])));
                                }
                                catch (Exception ex)
                                {
                                    Console.WriteLine("Error (" + ex.Message + ")");
                                }
                                rxString = ""; // clear buffer
                            }
                            else
                            {
                                rxString += (char)b;
                            }
                        }
                    });
                    Console.WriteLine("Waiting to receive data.");
                }
                catch (Exception e)
                {
                    Console.WriteLine("Failed (" + e.Message + ")");
                }
            }
            while (Console.ReadKey(true).Key != ConsoleKey.Escape);
            try
            {
                oscSender.Close();
            }
            catch { }
            try
            {
                serialPort.Close();
            }
            catch { }
        }
    }
}
