
namespace lab4
{
    partial class Form1
    {
        /// <summary>
        /// Обязательная переменная конструктора.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Освободить все используемые ресурсы.
        /// </summary>
        /// <param name="disposing">истинно, если управляемый ресурс должен быть удален; иначе ложно.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Код, автоматически созданный конструктором форм Windows

        /// <summary>
        /// Требуемый метод для поддержки конструктора — не изменяйте 
        /// содержимое этого метода с помощью редактора кода.
        /// </summary>
        private void InitializeComponent()
        {
            this.buttonOpenFile = new System.Windows.Forms.Button();
            this.labelSplitTime = new System.Windows.Forms.Label();
            this.buttonFindWord = new System.Windows.Forms.Button();
            this.listBoxFoundWords = new System.Windows.Forms.ListBox();
            this.textBoxWordSearch = new System.Windows.Forms.TextBox();
            this.openFileDialog1 = new System.Windows.Forms.OpenFileDialog();
            this.labelSearchTime = new System.Windows.Forms.Label();
            this.SuspendLayout();
            // 
            // buttonOpenFile
            // 
            this.buttonOpenFile.Anchor = System.Windows.Forms.AnchorStyles.None;
            this.buttonOpenFile.Location = new System.Drawing.Point(115, 12);
            this.buttonOpenFile.Name = "buttonOpenFile";
            this.buttonOpenFile.Size = new System.Drawing.Size(159, 62);
            this.buttonOpenFile.TabIndex = 1;
            this.buttonOpenFile.Text = "Open file";
            this.buttonOpenFile.UseVisualStyleBackColor = true;
            this.buttonOpenFile.Click += new System.EventHandler(this.buttonOpenFile_Click);
            // 
            // labelSplitTime
            // 
            this.labelSplitTime.AutoSize = true;
            this.labelSplitTime.Location = new System.Drawing.Point(138, 93);
            this.labelSplitTime.Name = "labelSplitTime";
            this.labelSplitTime.Size = new System.Drawing.Size(112, 13);
            this.labelSplitTime.TabIndex = 2;
            this.labelSplitTime.Text = "Time taken to split file:";
            // 
            // buttonFindWord
            // 
            this.buttonFindWord.Anchor = System.Windows.Forms.AnchorStyles.None;
            this.buttonFindWord.Location = new System.Drawing.Point(115, 138);
            this.buttonFindWord.Name = "buttonFindWord";
            this.buttonFindWord.Size = new System.Drawing.Size(159, 62);
            this.buttonFindWord.TabIndex = 3;
            this.buttonFindWord.Text = "Find word in list";
            this.buttonFindWord.UseVisualStyleBackColor = true;
            this.buttonFindWord.Click += new System.EventHandler(this.buttonFindWord_Click);
            // 
            // listBoxFoundWords
            // 
            this.listBoxFoundWords.FormattingEnabled = true;
            this.listBoxFoundWords.Location = new System.Drawing.Point(118, 284);
            this.listBoxFoundWords.Name = "listBoxFoundWords";
            this.listBoxFoundWords.Size = new System.Drawing.Size(156, 69);
            this.listBoxFoundWords.TabIndex = 4;
            // 
            // textBoxWordSearch
            // 
            this.textBoxWordSearch.Location = new System.Drawing.Point(125, 206);
            this.textBoxWordSearch.Name = "textBoxWordSearch";
            this.textBoxWordSearch.Size = new System.Drawing.Size(140, 20);
            this.textBoxWordSearch.TabIndex = 5;
            this.textBoxWordSearch.TextChanged += new System.EventHandler(this.textBoxWordSearch_TextChanged);
            // 
            // openFileDialog1
            // 
            this.openFileDialog1.FileName = "openFileDialog1";
            this.openFileDialog1.Filter = "Text files (*.txt)|*.txt";
            this.openFileDialog1.Title = "Select a text file";
            // 
            // labelSearchTime
            // 
            this.labelSearchTime.AutoSize = true;
            this.labelSearchTime.Location = new System.Drawing.Point(138, 252);
            this.labelSearchTime.Name = "labelSearchTime";
            this.labelSearchTime.Size = new System.Drawing.Size(121, 13);
            this.labelSearchTime.TabIndex = 6;
            this.labelSearchTime.Text = "Time taken to find word:";
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.BackColor = System.Drawing.SystemColors.Window;
            this.ClientSize = new System.Drawing.Size(402, 427);
            this.Controls.Add(this.labelSearchTime);
            this.Controls.Add(this.textBoxWordSearch);
            this.Controls.Add(this.listBoxFoundWords);
            this.Controls.Add(this.buttonFindWord);
            this.Controls.Add(this.labelSplitTime);
            this.Controls.Add(this.buttonOpenFile);
            this.Name = "Form1";
            this.Text = "File Opening";
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion
        private System.Windows.Forms.Label labelSplitTime;
        private System.Windows.Forms.Button buttonFindWord;
        private System.Windows.Forms.ListBox listBoxFoundWords;
        private System.Windows.Forms.TextBox textBoxWordSearch;
        private System.Windows.Forms.OpenFileDialog openFileDialog1;
        private System.Windows.Forms.Button buttonOpenFile;
        private System.Windows.Forms.Label labelSearchTime;
    }
}

