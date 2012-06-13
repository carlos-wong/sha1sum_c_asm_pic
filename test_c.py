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
data_list = [0]
cal = [0]

while a <= 0xffff:
  command = "./sha1 %d"%(a)
  if a%300 == 0:
    print command
  result = run_sys_command(command)
  a = a+1
  reslut = result.split("\n")
  temp = 0
  for enum in reslut:
    temp = temp + int(enum,16)
  i = 0
  get_data = 0
  for enum_data in data_list:
    if temp == enum_data:
      cal[i] = cal[i]+1
      get_data = 1
      break
    i = i + 1
  if get_data == 0:
    cal[i:] = [1]
    data_list[i:] = [temp]
i = 0
for enum_data in data_list:
  if cal[i] > 1:
    print enum_data
    print cal[i]
  i = i + 1


