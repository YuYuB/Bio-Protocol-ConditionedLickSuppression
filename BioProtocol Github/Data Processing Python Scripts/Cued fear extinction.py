#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Fri Aug 16 15:15:22 2019

@author: nishitani
"""

## Libraries
import csv
import re
import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
from scipy import stats
import seaborn as sns
import glob

## Get all .csv files in current directly
for FileE in glob.glob('*.csv'):
    
    rowNum    = np.array(0)
    row0 = np.array([])
    row1 = np.array([])
    row2 = np.array([])
    row3 = np.array([])
    row4 = np.array([])
    row5 = np.array([])
    row6 = np.array([])
    row7 = np.array([])
    row8 = np.array([])
        
    ## open file and store data
    with open(FileE, 'r') as f:
        #l_data = [s.strip() for s in re.split('\n', f.read())]
        reader    = csv.reader(f)
        header    = next(reader)      # Skip header (first line)
        for row in reader:    
            r0   = float(row[0])
            r1   = float(row[1])
            r2   = float(row[2])
            r3   = float(row[3])
            r4   = float(row[4])
            r5   = float(row[5])
            r6   = float(row[6])
            r7   = float(row[7])
            r8   = float(row[8])
            row0 = np.append(row0, r0)
            row1 = np.append(row1, r1)
            row2 = np.append(row2, r2)
            row3 = np.append(row3, r3)
            row4 = np.append(row4, r4)
            row5 = np.append(row5, r5)
            row6 = np.append(row6, r6)
            row7 = np.append(row7, r7)
            row8 = np.append(row8, r8)
            rowNum = rowNum + 1
    
    if row0.size == 1:
        ## SAVE 
            header4 = ['No entry']
            FileE_mod1 = FileE.strip('.csv') + '_event.csv'
            with open(FileE_mod1, "w") as output:
                writer = csv.writer(output, lineterminator='\n')
                writer.writerow(header4)
    else:
        ### For Event table
        ## extract data and store as array
        CS_on_time = row0[np.where(row7 > 0)]
        CS_off_time = row0[np.where(row8 > 0)]
        CS_on_index = np.where(row7 > 0)[0]
        CS_off_index = np.where(row8 > 0)[0]
        eventNum_dur_CS = CS_off_index - (CS_on_index - 1)
        CS_first_leave_time = np.unique(row4[row4 > 0])/1000
        noexit_flag = 0
        if len(CS_first_leave_time) != len(CS_on_time):
            CS_first_leave_time = np.append(CS_first_leave_time, row0[-1])
        
        
        ## make event table by each CS (CS# x 2 x event#)
        Table_each_event = np.full((CS_on_index.size, 2, max(eventNum_dur_CS +1)), -1.0)
        for i in range(CS_on_time.size):
            row0_each = row0[min(min(np.where(row0 == CS_on_time[i]))):
                min(min(np.where(row0 == CS_off_time[i])))+1]
            row3_each = row3[min(min(np.where(row0 == CS_on_time[i]))):
                min(min(np.where(row0 == CS_off_time[i])))+1]
            Table_each_event[i,0,:row0_each.size] = row0_each
            Table_each_event[i,1,:row3_each.size] = row3_each
        
        ### For in magazine duration
        ## Calculate in magazine duration (Tone on ~ Tone off)
        enter_time = np.array([])
        exit_time = np.array([])
        duration_in_tone = np.array([])
        duration_each_tone = np.array([])
        enter_flag = 0
        exit_flag = 0
        for i in range(Table_each_event.shape[0]):  # Repeat by tone number
            for j in range(Table_each_event.shape[2]):
                #print(j)
                if enter_flag == 0 and Table_each_event[i, 1, j] == 1:
                    enter_time = Table_each_event[i, 0, j]
                    enter_flag = 1
                    exit_flag = 0
                
                elif enter_flag != 0 and Table_each_event[i, 1, j] == 1:  # delete if no errors
                    pass
                
                elif exit_flag == 0 and Table_each_event[i, 1, j] == 0:
                    exit_time = Table_each_event[i, 0, j]
                    duration_in_tone = np.append(duration_in_tone, exit_time - enter_time)
                    enter_flag = 0
                    exit_flag = 1
                
                elif exit_flag != 0 and Table_each_event[i, 1, j] == 0:  # delete if no errors
                    pass
                
                elif Table_each_event[i, 1, j] == -1:
                    if exit_flag == 0:
                        exit_time = Table_each_event[i, 0, j-1]
                        duration_in_tone = np.append(duration_in_tone, exit_time - enter_time)
                        enter_flag = 0
                        exit_flag = 1
                    
                    duration_each_tone = np.append(duration_each_tone, np.sum(duration_in_tone))
                    duration_in_tone = 0
                    break
                
                else:
                    print("Error!")
        
        duration_each_tone = np.where(duration_each_tone > 10, 10, duration_each_tone)
        
        ## Calculate first leave latency
        CS_first_leave_latency = CS_first_leave_time - CS_on_time
        CS_first_leave_latency = np.where(CS_first_leave_latency >= 10, 'No exit!', CS_first_leave_latency)
        

        ### For licking
        ## lick# during CS on
        pre_lick = row1[np.where(row7 > 0)]
        post_lick = row1[np.where(row8 > 0)]
        lickNum = post_lick - pre_lick
        
        ## lick# during 5s back from CS on
        if row0[0] > CS_on_time[0] -5:
            pre_lick_5s_back = np.array([row0[0]])
            for i in range(1, CS_on_time.size):
                pre_lick_5s_back = np.append(pre_lick_5s_back,
                                             row1[max(max(np.where(row0 <= CS_on_time[i] -5)))])
            lickNum_5s_back = pre_lick - pre_lick_5s_back
        else:
            pre_lick_5s_back = np.array([])
            for i in range(CS_on_time.size):
                pre_lick_5s_back = np.append(pre_lick_5s_back,
                                             row1[max(max(np.where(row0 <= CS_on_time[i] -5)))])
            lickNum_5s_back = pre_lick - pre_lick_5s_back
        
        ## lick# during 5s forward from CS on
        post_lick_5s_forward = np.array([])
        for i in range(CS_on_time.size):
            post_lick_5s_forward = np.append(post_lick_5s_forward,
                                         row1[min(min(np.where(row0 >= CS_on_time[i] +10)))])
        lickNum_5s_forward = post_lick_5s_forward - pre_lick
        
        ## Calculate Suppression ratio
        Suppression_ratio = (lickNum_5s_back - lickNum_5s_forward) / (lickNum_5s_back + lickNum_5s_forward)

        ## transform to Tables
        Table = []
        Table.append(list(range(1, CS_on_time.size+1)))
        Table.append(list(CS_on_time))
        Table.append(list(CS_off_time))
        Table.append(list(duration_each_tone))
        Table.append(list(lickNum))
        Table.append(list(lickNum_5s_back))
        Table.append(list(lickNum_5s_forward))
        Table.append(list(Suppression_ratio))
        Table.append(list(CS_first_leave_time))
        Table.append(list(CS_first_leave_latency))
        t_Table = list(map(list, zip(*Table))) # Transposed

        ## SAVE 
        header1 = ['Tone #', 'Tone on time', 'Tone off time', 'In Mag Dur', 'Lick #',
                  'Lick # 5s back', 'Lick # 5s', 'Supression ratio', '1st leave time',
                  '1st leave latency']
        FileE_mod1 = FileE.strip('.csv') + '_analysed.csv'
        with open(FileE_mod1, "w") as output:
            writer = csv.writer(output, lineterminator='\n')
            writer.writerow(header1)
            writer.writerows(t_Table)