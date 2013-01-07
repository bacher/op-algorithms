using System;
using System.Collections.Generic;
using System.IO;
using System.Text;

namespace Permutation2_Test
{
    class Program
    {
        static void Main(string[] args)
        {
            var v = new StreamReader(new BufferedStream(new FileStream(@"permut2.out", FileMode.Open)));

            HashSet<string> set = new HashSet<string>();

            string str;
            StringBuilder sb = new StringBuilder();
            int line = 0;

            while (!v.EndOfStream)
            {
                line++;
                str = v.ReadLine();
                if (set.Contains(str))
                {
                    sb.AppendLine(string.Format("{0}: {1}", line, str));
                }
                else
                {
                    set.Add(str);
                }
            }

            var o = new StreamWriter(new BufferedStream(new FileStream(@"permut2-results.out", FileMode.Create)));

            o.Write(sb.ToString());
        }
    }
}
