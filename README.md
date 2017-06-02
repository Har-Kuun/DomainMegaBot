# DomainMegaBot
A domain name bulk search bot with support of over 200 top-level domains.

Usage:
This script is written in C. It's been successfully compiled on several Linux distributions, but it's not meant to work in Windows environments.
Simply run:

~~~~
gcc -o DomainMegaBot DomainMegaBot.c
./DomainMegaBot
~~~~
Domain extentions database file TLD_DATA should be put in same directory with DomainMegaBot. The domain prefix dictionary should be a pure UNIX-based text file with one string each line. You can play with our demostration dictionaries to see how the program works.
When the program asks you to specify a domain extention, only type in the letters, for example, 'com'. Please do not type any sort of punctuations as that will end up an error.

Known issues: There are known issues that when bulk searching .cn and .vc domain names, the program will end up "Segmentation Fault" error after it finishes tens of searches. So if you insist using this program for .cn or .vc domains, you may wanna separate your dictionary file into parts.
