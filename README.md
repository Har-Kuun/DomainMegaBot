# DomainMegaBot
A domain name bulk search bot with support of over 200 top-level domains.

Usage:
This script is written in C. It's been successfully compiled on several Linux distributions, but it's not meant to work in Windows environments.
Simply run:
~~~~
gcc -o DomainMegaBot DomainMegaBot.c
./DomainMegaBot
Please specify TLD: com
Please specify dictionary file: 2letter
~~~~
1000w means 1000 words we usually use, 2letter means all the combinations with two letters, 3en means some combinations with three letters, 3py means some PINGYINs in chinese, 3x means all the combinations with three letters or two letters and one number.

Domain extentions database file TLD_DATA should be put in same directory with DomainMegaBot. The domain prefix dictionary should be a pure UNIX-based text file with one string each line. You can play with our demostration dictionaries to see how the program works.
When the program asks you to specify a domain extention, only type in the letters, for example, 'com'. Please do not type any sort of punctuations as that will end up an error.

Known issues: There are known issues that when bulk searching .cn and .vc domain names, the program will end up "Segmentation Fault" error after it finishes tens of searches. So if you insist using this program for .cn or .vc domains, you may wanna separate your dictionary file into parts.


# DomainMegaBot
DomainMegaBot是一款支持超过200个顶级域名的域名扫描工具。

使用方法：
此工具是用C语言写成，可以运行在任何Linux系统上（可能会因为指令集而出现差异），但无法在Windows中运行。
首次使用时，需要编译程序，运行中需要指定域名和字典。

例如：
~~~~
gcc -o DomainMegaBot DomainMegaBot.c
./DomainMegaBot
Please specify TLD: com
Please specify dictionary file: 2letter
~~~~

1000w代表1000个常用单词/字母，2letter代表所有的2字母组合， 3en代表一些常见的3字母组合，3x代表所有的3字母组合以及2字母和1个数字的组合。

域名数据表为TLD_DATA，此数据表必须和DomainMegaBot处于相同的文件夹。字典每行只能有一个带测的“域名”，具体实现可以直接浏览源代码查看。
所有的输入都只支持英文，严禁输入任何标点符号。

部分域名，如.cn和.vc在扫描中会出现“Segmentation Fault”，这是服务商禁止了连续扫描功能，如果你需要查询此类域名，可以尝试将几点拆分成多份。
