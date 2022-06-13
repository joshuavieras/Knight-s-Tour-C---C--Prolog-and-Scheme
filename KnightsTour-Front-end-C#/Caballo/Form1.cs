using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Diagnostics;
using System.Drawing;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace Caballo
{
    public partial class Form1 : Form
    {
        private bool firstMoveChosen;
        private int PosicionX;
        private int PosicionY;
        private int movimientos = -1;
        int[,] solucion;
        int cont = 1;

        public Form1()
        {
            InitializeComponent();

            firstMoveChosen = false;
            /*solucion = new int[,] { 
                { 1, 48, 31, 50, 33, 16, 63, 18 },
                { 30, 51, 46, 3, 62, 19, 14, 35 },
                { 47, 2, 49, 32, 15, 34, 17, 64 },
                { 52, 29, 4, 45, 20, 61, 36, 13 },
                { 5, 44, 25, 56, 9, 40, 21, 60 },
                { 28, 53, 8, 41, 24, 57, 12, 37 },
                { 43, 6, 55, 26, 39, 10, 59, 22 },
                { 54, 27, 42, 7, 58, 23, 38, 11 }
            };*/
        }

        private void tableLayoutPanel1_CellPaint(object sender, TableLayoutCellPaintEventArgs e)
        {
            if ((e.Column + e.Row) % 2 == 1)
                e.Graphics.FillRectangle(Brushes.Black, e.CellBounds);
            else
                e.Graphics.FillRectangle(Brushes.White, e.CellBounds);
        }
         private int[,] LeerMatrizLinea()
        {
            int[,] array = new int[8, 8];
            int contlines = 0;
            var lines = File.ReadAllLines("C:/Users/joshu/Desktop/Proyecto-ced-117830351-118160545/KnightsTour-Front-end-C#/solucion.txt");

            for (int i = 0; i < 8; i++)
            {
                for (int j = 0; j < 8; j++)
                {
                    array[i, j]= int.Parse(lines[contlines]);
                    this.tableLayoutPanel2.Controls.Add(new Label() { Text = lines[contlines], Font = new Font("Arial", 6), BackColor = Color.Transparent, ForeColor = Color.Red }, j, i);
                    contlines++;
                }
            }
            return array;
        }
        private bool IsNumeric(string line)
        {
            foreach (char c in line)
                if (!"0123456789 ".Contains(c))
                    return false;

            return true;
        }
        private async void CambiarPosicion()
        {

            //this.tableLayoutPanel1.Controls.Add(this.pictureBox1, j, i);
            //await Task.Delay(500);
           for(int i = 0; i < 8; i++)
            {
                for(int j = 0; j < 8; j++)
                {
                    if (solucion[0, 0] == cont)
                    {
                        tableLayoutPanel1.Controls.Remove(this.pictureBox1);
                        this.tableLayoutPanel1.Controls.Add(this.pictureBox1, 0, 0);
                        movimientos++;
                        label4.Text = movimientos.ToString();
                        await Task.Delay(500);
                        tableLayoutPanel1.Controls.Remove(this.pictureBox1);
                        tableLayoutPanel1.Controls.Remove(this.pictureBox1);
                        tableLayoutPanel1.Controls.Remove(tableLayoutPanel1.GetControlFromPosition(0, 0));
                        this.tableLayoutPanel1.Controls.Add(new Label() { Text = solucion[0, 0].ToString(), Font = new Font("Arial", 15), BackColor = Color.Transparent, ForeColor = Color.Red }, 0, 0);
                        j = 0;
                        i = 0;
                        cont++;
                    }
                       else if (solucion[i, j] == cont)
                    {
                        tableLayoutPanel1.Controls.Remove(this.pictureBox1);
                        this.tableLayoutPanel1.Controls.Add(this.pictureBox1, j, i);
                        movimientos++;
                        label4.Text = movimientos.ToString();
                        await Task.Delay(500);
                        tableLayoutPanel1.Controls.Remove(this.pictureBox1);
                        tableLayoutPanel1.Controls.Remove(this.pictureBox1);
                        tableLayoutPanel1.Controls.Remove(this.pictureBox1);
                        this.tableLayoutPanel1.Controls.Add(new Label() { Text = solucion[i, j].ToString(), Font = new Font("Arial", 15), BackColor = Color.Transparent, ForeColor = Color.Red }, j, i);
                        j = 0;
                        i = 0;
                        cont++;
                        
                    }
                }
            }
        }

        private void tableLayoutPanel1_Paint(object sender, PaintEventArgs e)
        {

        }

        private void tableLayoutPanel1_MouseClick(object sender, MouseEventArgs e)
        {
            if(!firstMoveChosen)
            {
                var cellPos = GetRowColIndex(
                    tableLayoutPanel1,
                    tableLayoutPanel1.PointToClient(Cursor.Position)
                );

                firstMoveChosen = !firstMoveChosen;
                PosicionX = cellPos.Value.X;
                PosicionY = cellPos.Value.Y;
                this.tableLayoutPanel1.Controls.Add(this.pictureBox1, cellPos.Value.X, cellPos.Value.Y);
                this.tableLayoutPanel1.Cursor = System.Windows.Forms.Cursors.Default;
                label1.Text = "Knight's Tour";
                this.label1.Font = new System.Drawing.Font("Segoe UI Semibold", 20.75F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point);
                this.label1.Location = new Point(551, 40);
                string[] lines = { cellPos.Value.X.ToString(), cellPos.Value.Y.ToString()};
                File.WriteAllLines("posicion.txt", lines);
                 Process p = new Process();
                 ProcessStartInfo info = new ProcessStartInfo();
                 info.FileName = "cmd.exe";
                 info.RedirectStandardInput = true;
                 p.StartInfo = info;
                 p.Start();
                StreamWriter sw = p.StandardInput;
                sw.WriteLine("swipl");
                sw.WriteLine("consult('c:/Users/joshu/Desktop/Proyecto-ced-117830351-118160545/KnightsTour-Back-end-Prolog/PaseoCaballo.pl').");
                sw.WriteLine("tell('C:/Users/joshu/Desktop/Proyecto-ced-117830351-118160545/KnightsTour-Front-end-C#/solucion.txt').");
                sw.WriteLine("recorrido("+cellPos.Value.Y.ToString()+","+cellPos.Value.X.ToString()+").");
                sw.WriteLine("."); 
                sw.WriteLine("told.");
                sw.WriteLine("recorrido(" + cellPos.Value.Y.ToString() + "," + cellPos.Value.X.ToString() + ").");
                this.button1.Enabled = true;
                this.button1.Visible = true;
            }
        }

        Point? GetRowColIndex(TableLayoutPanel tlp, Point point)
        {
            if (point.X > tlp.Width || point.Y > tlp.Height)
                return null;

            int w = tlp.Width;
            int h = tlp.Height;
            int[] widths = tlp.GetColumnWidths();

            int i;
            for (i = widths.Length - 1; i >= 0 && point.X < w; i--)
                w -= widths[i];
            int col = i + 1;

            int[] heights = tlp.GetRowHeights();
            for (i = heights.Length - 1; i >= 0 && point.Y < h; i--)
                h -= heights[i];

            int row = i + 1;

            return new Point(col, row);
        }

        private void label2_Click(object sender, EventArgs e)
        {

        }

        private void button1_Click(object sender, EventArgs e)
        {
            this.button1.Enabled = false;
            string text = new StreamReader("solucion.txt").ReadToEnd();
            //solucion = LeerMatriz(text);
            solucion = LeerMatrizLinea();
            CambiarPosicion();

        }
    }



}
