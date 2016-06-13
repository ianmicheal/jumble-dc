using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ResourcePacker
{
    public struct ResourceEntry
    {
        public ResourceType Type;
        public string Filename;
        public string CompleteFilename;
        public UInt32 Length;
        public UInt32 Offset;
    }

    public enum ResourceType : byte
    {
        Binary = 0x00,
        TextureRaw,
        TexturePvr,
        MeshStatic,
        MeshAnimatedSkeletal,
        AudioPCM,
        AudioVorbis
    }

    public enum ResourceVersion
    {
        Uncompressed = 0x00,
        ZLIB
    }

    public class PackageManager
    {
        private string _directory;
        private List<ResourceEntry> _fileList;

        public PackageManager(string directory)
        {
            _directory = directory;
            _fileList = new List<ResourceEntry>();

            RefreshFileList();
        }

        public void RefreshFileList()
        {
            // Get all the files in the directory
            string[] files = Directory.GetFiles(_directory);

            // For each file: fetch its size, type and
            // calculate its offset in the package
            UInt32 currentOffset = 0;

            for (int i = 0; i < files.Length; i++)
            {
                FileInfo fInfo = new FileInfo(files[i]);
                ResourceEntry ent = new ResourceEntry();
                string ext = fInfo.Extension.ToLower();

                if (ext.Contains("png") || ext.Contains("jpg") || ext.Contains("jpeg") || ext.Contains("bmp") ||
                    ext.Contains("tif") || ext.Contains("tiff") || ext.Contains("gif"))
                {
                    ent.Type = ResourceType.TextureRaw;
                }
                else if (ext.Contains("pvr"))
                {
                    ent.Type = ResourceType.TexturePvr;
                }
                else if (ext.Contains("ogg"))
                {
                    ent.Type = ResourceType.AudioVorbis;
                }
                else if (ext.Contains("wav"))
                {
                    ent.Type = ResourceType.AudioPCM;
                }
                else if (ext.Contains("obj"))
                {
                    ent.Type = ResourceType.MeshStatic;
                }
                else if (ext.Contains("fbx"))
                {
                    ent.Type = ResourceType.MeshAnimatedSkeletal;
                }
                else
                {
                    ent.Type = ResourceType.Binary;
                }

                ent.Filename = fInfo.Name.Split('.')[0];
                ent.CompleteFilename = fInfo.FullName;
                ent.Length = (UInt32)fInfo.Length;
                ent.Offset = currentOffset;

                _fileList.Add(ent);

                currentOffset += (UInt32)fInfo.Length;
            }
        }

        public List<ResourceEntry> GetFilesInDirectory()
        {
            return _fileList;
        }
    }
}
