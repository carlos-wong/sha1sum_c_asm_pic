#!/usr/bin/python
import os
import sys
import time
import string
import commands

def run_sys_command(command):
  status,output_file = commands.getstatusoutput(command.strip())
  if(status != 0):
    print command.strip(),"return error!!! we only do to is exit"
    sys.exit()
  return output_file

i = 0
a = 0
b = 0
c = 0
d = 0
while a <= 0xffffffff:
  print "step a is ",a
  b = 0
  while b <= 0xffffffff:
    c = 0
    while c <= 0xffffffff:
      d = 0
      while d <= 0xffffffff:
        command = "./sha1 %d %d %d %d"%(a,b,c,d)
        print command
        result = run_sys_command(command)
        d = d + 1
      c = c +1
    b = b + 1
  a = a+1
#reslut = result.split("\n")
#temp = 0
#for enum in reslut:
#  print enum,"atoi is %x"%(int(enum,16))
#  temp = temp + int(enum,16)
#print temp
