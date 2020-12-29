using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

using System.IO;
using System.Diagnostics;

namespace lab4
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
            _words = new List<string>();
        }

        private List<string> _words;

        private void buttonOpenFile_Click(object sender, EventArgs e)
        {
            if (openFileDialog1.ShowDialog() == DialogResult.OK)
            {
                labelSearchTime.Text = "Time taken to find word: ";

                Stopwatch stopwatch = new Stopwatch();
                stopwatch.Start();

                string fileText = File.ReadAllText(openFileDialog1.FileName);

                _words.Clear();
                foreach (string word in fileText.Split(' '))
                {
                    if (!_words.Contains(word))
                    {
                        _words.Add(word);
                    }
                }

                stopwatch.Stop();
                labelSplitTime.Text = String.Format("Time taken to split file: {0:0.00} s", stopwatch.Elapsed.Seconds);
            }
        }

        private void buttonFindWord_Click(object sender, EventArgs e)
        {
            labelSearchTime.Text = "Word not found!";

            string wordToFind = textBoxWordSearch.Text;

            if (!string.IsNullOrEmpty(wordToFind))
            {
                if (!listBoxFoundWords.Items.Contains(wordToFind))
                {
                    Stopwatch stopwatch = new Stopwatch();
                    stopwatch.Start();

                    foreach (string word in _words)
                    {
                        if (word.Contains(wordToFind))
                        {
                            listBoxFoundWords.BeginUpdate();
                            listBoxFoundWords.Items.Add(wordToFind);
                            listBoxFoundWords.EndUpdate();

                            stopwatch.Stop();
                            labelSearchTime.Text = String.Format("Time taken to find word: {0:0.00} ms", stopwatch.Elapsed.Milliseconds);
                            break;
                        }
                    }
                }

                else
                {
                    labelSearchTime.Text = "Word has already been found!";
                }
            }
        }

        

        private void textBoxWordSearch_TextChanged(object sender, EventArgs e)
        {
        }
    }
}
