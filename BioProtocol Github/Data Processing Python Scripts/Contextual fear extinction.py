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
time_bin = 1800 
for FileE in glob.glob('*.csv'):
    
    rowNum    = np.array(0)
    row0 = np.array([])
    row1 = np.array([])
    row2 = np.array([])
    row3 = np.array([])
    row4 = np.array([])
    row5 = np.array([])
    row6 = np.array([])
        
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
            row0 = np.append(row0, r0)
            row1 = np.append(row1, r1)
            row2 = np.append(row2, r2)
            row3 = np.append(row3, r3)
            row4 = np.append(row4, r4)
            row5 = np.append(row5, r5)
            row6 = np.append(row6, r6)
            rowNum = rowNum + 1
    
    ### For Event table
    ## extract data and store as array
    mag_entry_time = row0[np.where(row5 == 1)]
    
    mag_exit_time = row0[np.where(row4 == 1)]
    if len(mag_entry_time) != len(mag_exit_time):
        mag_exit_time = np.append(mag_exit_time, 1800)
    
    pre_lickNum = row1[np.where(row5 == 1)]
    post_lickNum = row1[np.where(row4 == 1)]
    
    ## calculation
    in_mag_dur = mag_exit_time - mag_entry_time
    
    out_mag_dur = mag_entry_time[1:] - mag_exit_time[:-1]
    out_mag_dur = np.insert(out_mag_dur, 0, mag_entry_time[0])
    
    if post_lickNum.size != pre_lickNum.size:
        post_lickNum = np.append(post_lickNum, post_lickNum[-1])
    
    lickNum_sum = post_lickNum - pre_lickNum
    
    
    ### For Duration table
    ## get index to split by time bin
    split_index = np.array([])
    for i in list(range(time_bin, 1800, time_bin)):  #time bin = 300
        if row0[1] < i:
            split_index = np.append(split_index, max(max(np.where(row0 < i))))
        else:
            pass
    split_index = np.append(split_index, rowNum-2)
    
    ## add split time to the rows
    for i in range(split_index.size):
        row0 = np.insert(row0, int(split_index[i])+1+i, time_bin*(i+1))
        row4 = np.insert(row4, int(split_index[i])+1+i, 1)
        row5 = np.insert(row5, int(split_index[i])+1+i, 1)
        
    ## extract data and store as array
    mag_entry_time_split = row0[np.where(row5 == 1)]
    
    lickNum = np.array([])
    for i in map(int, split_index):
        lickNum = np.append(lickNum, row1[i])
    lickNum_back = np.array(0)
    lickNum_back = np.append(lickNum_back, lickNum[:-1])
    lickNum_bin = lickNum-lickNum_back
    
    mag_exit_time_split = row0[np.where(row4 == 1)]
    if len(mag_entry_time_split) != len(mag_exit_time_split):
        mag_exit_time_split = np.append(mag_exit_time_split, 1800)
    
    ## duration calculation
    in_mag_dur_split = mag_exit_time_split - mag_entry_time_split
    out_mag_dur_split = mag_entry_time_split[1:] - mag_exit_time_split[:-1]
    out_mag_dur_split = np.insert(out_mag_dur_split, 0, mag_entry_time_split[0])
    
    ## get index to split dur array
    dur_split_index = np.array([])
    for i in range(1, split_index.size+1):
        dur_split_index = np.append(dur_split_index,
                                    np.where(mag_entry_time_split == time_bin*i))
    
    ## sum by time_bin
    in_mag_dur_bin = np.array([])
    for i, j in zip(map(int, dur_split_index), np.arange(len(split_index))):
        in_mag_dur_bin = np.append(in_mag_dur_bin, np.sum(in_mag_dur_split[0:i+1]))
    in_mag_dur_bin = np.insert(in_mag_dur_bin[1:] - in_mag_dur_bin[:-1], 0,
                               in_mag_dur_bin[0])
    #print(np.sum(in_mag_dur_split))
    #print(np.sum(in_mag_dur_bin))
    
    out_mag_dur_bin = np.array([])
    for i, j in zip(map(int, dur_split_index), np.arange(len(split_index))):
        out_mag_dur_bin = np.append(out_mag_dur_bin, np.sum(out_mag_dur_split[0:i+1]))
    out_mag_dur_bin = np.insert(out_mag_dur_bin[1:] - out_mag_dur_bin[:-1], 0,
                               out_mag_dur_bin[0])
    #print(np.sum(out_mag_dur_split))
    #print(np.sum(out_mag_dur_bin))
    
    #print(np.sum(out_mag_dur_split)+np.sum(in_mag_dur_split))
    
    ## transform to Tables
    Table_event = []
    Table_bin = []
    Table_event.append(list(range(1, lickNum_sum.size+1)))
    Table_event.append(list(mag_entry_time))
    Table_event.append(list(mag_exit_time))
    Table_event.append(list(in_mag_dur))
    Table_event.append(list(lickNum_sum))
    Table_event.append(list(out_mag_dur))
    Table_bin.append(list(range(1, dur_split_index.size+1)))
    Table_bin.append(list(in_mag_dur_bin))
    Table_bin.append(list(lickNum_bin))
    Table_bin.append(list(out_mag_dur_bin))
    t_Table_event = list(map(list, zip(*Table_event))) # Transposed
    t_Table_bin = list(map(list, zip(*Table_bin)))
                              
    ## SAVE 
    header1 = ['Mag entry #', 'Mag entry time', 'Mag exit time', 'In Mag dur', 'Lick #',
               'Out Mag dur']
    FileE_mod1 = FileE.strip('.csv') + '_event.csv'
    with open(FileE_mod1, "w") as output:
        writer = csv.writer(output, lineterminator='\n')
        writer.writerow(header1)
        writer.writerows(t_Table_event)
    
    header2 = ['Bin #', 'In Mag dur', 'Lick #', 'Out Mag dur']
    #header3 = ['Event #', 'Stay >5s duration', 'Stay >5s Lick #']
    FileE_mod2 = FileE.strip('.csv') + '_bin.csv'
    with open(FileE_mod2, "w") as output:
        writer = csv.writer(output, lineterminator='\n')
        writer.writerow(header2)
        writer.writerows(t_Table_bin)
        #writer.writerow(header3)
        #writer.writerows(t_Table_5s)
        
