using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;
using System.Windows.Forms;

namespace ResourcePacker
{
    /// <summary>
    /// Lógica de interacción para MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        private PackageManager _packer;

        public MainWindow()
        {
            InitializeComponent();
        }

        private void folderButton_Click(object sender, RoutedEventArgs e)
        {
            FolderBrowserDialog fbDlg = new FolderBrowserDialog();
            DialogResult dlgRes = fbDlg.ShowDialog();

            if (dlgRes == System.Windows.Forms.DialogResult.OK)
            {
                string targetFolder = fbDlg.SelectedPath;
                _packer = new PackageManager(targetFolder);
                RefreshFileList();
            }
        }

        public void RefreshFileList()
        {
            List<ResourceEntry> ent = _packer.GetFilesInDirectory();
            filesListBox.Items.Clear();

            foreach (ResourceEntry et in ent)
            {
                filesListBox.Items.Add(et.Filename);
            }
        }

        private void filesListBox_SelectionChanged(object sender, SelectionChangedEventArgs e)
        {
            if (filesListBox.SelectedIndex != -1)
            {
                List<ResourceEntry> ent = _packer.GetFilesInDirectory();
                int i = filesListBox.SelectedIndex;

                nameLabel.Content = "Name: " + ent[i].Filename;
                sizeLabel.Content = "Length: " + ent[i].Length.ToString() + " bytes";
                offsetLabel.Content = "Offset: " + ent[i].Offset.ToString() + " bytes";

                typeLabel.Content = "Type: ";

                warningImage.Visibility = Visibility.Hidden;
                warnFormatLabel.Visibility = Visibility.Hidden;

                switch (ent[i].Type)
                {
                    case ResourceType.Binary:
                        typeLabel.Content += "Generic binary";
                        break;

                    case ResourceType.AudioPCM:
                        typeLabel.Content += "PCM (Uncompressed) audio";
                        break;

                    case ResourceType.AudioVorbis:
                        typeLabel.Content += "Ogg Vorbis (Compressed) audio";
                        break;

                    case ResourceType.MeshAnimatedSkeletal:
                        typeLabel.Content += "Skeleton / animated mesh (Autodesk FBX)";
                        break;

                    case ResourceType.MeshStatic:
                        typeLabel.Content += "Static mesh (Wavefront OBJ)";
                        break;

                    case ResourceType.TexturePvr:
                        typeLabel.Content += "Dreamcast compressed texture (PVRTC)";
                        warningImage.Visibility = Visibility.Visible;
                        warnFormatLabel.Visibility = Visibility.Visible;
                        warnFormatLabel.Content = "PVRTC Textures are not supported yet";
                        break;

                    case ResourceType.TextureRaw:
                        typeLabel.Content += "RAW (Uncompressed) texture";
                        break;
                }
            }
        }
    }
}
