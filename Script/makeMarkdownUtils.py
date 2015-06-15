﻿#!/usr/bin/env python
#coding: UTF-8

import os.path
import aceutils
import re

sample_ss_dir = r'../Sample_SS/'
basic_sample_dir = r'../Sample/BasicSample/'

included_ss_paths = []

def include_basic_sample(ls,relCodePath,ssDir,mode=''):
    """
    ls コードの内容
    relCodePath コードファイルへのルートからの相対パス
    ssDir SSの保存ディレクトリ
    mode 表示モード(cpp,cs)
    """

    #includeの実装
    ls_included = []
    includePattern = r'\* include_basic_sample (.+)'
    includer = re.compile(includePattern)
    
    for s in ls:
        m = includer.search(s.replace('\r','').replace('\n',''))
        if m != None:
            sampleName = m.group(1)
            searchedTargetDir = basic_sample_dir
            
            files = []
            for f in aceutils.get_files(searchedTargetDir):
                basename = os.path.basename(f)
                name = os.path.splitext(basename)[0]
                if name == sampleName:
                    files.append(f)
      
            ss_files = []
            for f in aceutils.get_files(sample_ss_dir):
                basename = os.path.basename(f)
                name = os.path.splitext(basename)[0]
                if name == sampleName:
                    ss_files.append(f)
      
            # コードの検索
            def getFile(ext):
                files_ = [f for f in files if os.path.splitext(f)[1]==ext]
                if len(files) > 0:
                    return files_[0]
                return None

            cpp_targetPath = getFile('.cpp')
            cs_targetPath = getFile('.cs')

            # SSの表示
            if len(ss_files) > 0:
                ss_file = ss_files[0]
                rel_ss_file = os.path.relpath(ssDir+os.path.basename(ss_file), start=os.path.dirname(relCodePath))
                rel_ss_file = rel_ss_file.replace('\\','/')
                ls_included.append('![SS](' + rel_ss_file + ')\n\n')
                included_ss_paths.append(ss_files[0])
                #print(relCodePath + ' : ' + ssDir+os.path.basename(ss_file) + ' : ' + rel_ss_file)

            def includeFile(targetPath):
                print('include : ' + targetPath)

                ext = os.path.splitext(targetPath)[1]
            
                if ext=='.cpp':
                    ls_included.append('```cpp\n')
                elif ext=='.cs':
                    ls_included.append('```cs\n')
                else:
                    ls_included.append('```\n')

                with open(targetPath, mode='r', encoding='utf-8') as f:
                    for fl in f.readlines():
                        if ext=='.cpp':
                            fl = fl.replace(r'void ' + sampleName + '()',r'int main()')
                            fl = fl.replace(r'return;',r'return 0;')

                        if ext=='.cs':
                            fl = fl.replace(r'public void Run()','[System.STAThread]\r\n\tstatic void Main(string[] args)')
                            fl = fl.replace(r' : ISample','')

                        ls_included.append(fl)
                
                ls_included.append('\n```\n')

            if mode == 'all':
                includeFile(cpp_targetPath)
                includeFile(cs_targetPath)
            if mode == 'cs':
                includeFile(cs_targetPath)
            elif mode == 'cpp':
                includeFile(cpp_targetPath)

        else:
            ls_included.append(s)

    return ls_included
