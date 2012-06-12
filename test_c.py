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


result = run_sys_command("./sha1 10 20 30 40")
reslut = result.split("\n")
print  reslut
for enum in reslut:
  print enum
