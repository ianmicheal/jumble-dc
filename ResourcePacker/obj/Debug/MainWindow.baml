   M S B A M L   `   `   `  ����I  EResourcePacker, Version=1.0.0.0, Culture=neutral, PublicKeyToken=null/clr-namespace:ResourcePackerResourcePacker  5   	       ResourcePacker.MainWindow   5   	   \ XPresentationFramework, Version=4.0.0.0, Culture=neutral, PublicKeyToken=31bf3856ad364e35R NWindowsBase, Version=4.0.0.0, Culture=neutral, PublicKeyToken=31bf3856ad364e35W SPresentationCore, Version=4.0.0.0, Culture=neutral, PublicKeyToken=31bf3856ad364e35D 9http://schemas.microsoft.com/winfx/2006/xaml/presentation    5   	   R NSystem.Xaml, Version=4.0.0.0, Culture=neutral, PublicKeyToken=b77a5c561934e089:x,http://schemas.microsoft.com/winfx/2006/xaml     5   	   @d2http://schemas.microsoft.com/expression/blend/2008     5   	   Jmc;http://schemas.openxmlformats.org/markup-compatibility/2006     5   	   .localclr-namespace:ResourcePacker     5   	     � Title$  Resource Packer��5   	   $��363.347��6!   $��547.987��62    � 
ResizeMode$ NoResize=�6B   .��5	      �  � ColumnDefinitions 5
   
   �� 5      $
��291* �6   �� 5      $
��251* �6   .+�5   
   �� -   5         ��Name$ folderButton��5      $��Select Directory��6'   $
��Left=�6B   $��
10,294,0,0q�6]   $	��Top=�6q   $	��111��6�   $��20��6�   6�   �� 5   
   -   5        $ generateButton��5      $��Generate Package��6)   $
��Left=�6D   $��126,294,0,0q�6_   $	��Top=�6t   $	��129��6�   $��20��6�   �� 5   
   
���   �$��1q�6%   $
��Left=�69   $	��268��6T   $��	10,10,0,0q�6a   $	��Top=�6t   $	��271��6�   ._�5      �� -   5         ��Name$ filesListBox��5      6,   5      �� 5   
   -   5         ��Name$ 	nameLabel��5      $��Name:��6#   $��1��63   $
��Left=�6C   $��	10,10,0,0q�6^   $	��Top=�6q   $	��231��6�   �� 5   
   -   5        $ 	sizeLabel��5      $��Size: 0 bytes��6#   $��1��6;   $
��Left=�6K   $��	10,41,0,0q�6f   $	��Top=�6y   $	��231��6�   �� 5   
   -   5        $ offsetLabel��5      $��Offset: 0 bytes��6%   $��1��6?   $
��Left=�6O   $��	10,72,0,0q�6j   $	��Top=�6}   $	��231��6�   �� 5   
   -   5        $ 	typeLabel��5      $��Type:��6#   $��1��63   $
��Left=�6C   $��
10,103,0,0q�6^   $	��Top=�6r   $	��231��6�   � 5   
   -   5         �Name$ progressBarGenerate��5      $��1��63   $
��Left=�6C   $��20��6^   $��
10,294,0,0q�6j   $	��Top=�6~   $	��231��6�    � LargeChange$ 0Q�6�    � SmallChange$ 1Q�6�   �� 5   
   -	   5        	 ��Name$	 warningImage��5      $��1��6&   $��0,0,209,157q�66   $��Warning.png��6K   $
��Fill=�6`   $��32��6o   $��32��6z   $��Right=�6�   $��Bottom=�6�   �� 5   
   -
   5        $ warnFormatLabel��5      $��Format is unsupported!��6)   $��1��6J   $
��Left=�6Z   $��
47,140,0,0q�6u   $	��Top=�6�   $	��194��6�   $��29��6�   5      5      