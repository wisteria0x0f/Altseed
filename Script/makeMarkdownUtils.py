﻿#!/usr/bin/env python
#coding: UTF-8

import os.path
import aceutils
import re

sample_ss_dir = r'../Sample_SS/'
basic_sample_dir = r'../Sample/BasicSample/'
application_sample_dir = r'../Sample/ApplicationSample/'

included_ss_paths = []

def include_sample(ls,relCodePath,pattern,sampleDir,ssDir,sampleDirPrefix,mode=''):
    """
    ls コードの内容
    relCodePath コードファイルへのルートからの相対パス
    ssDir SSの保存ディレクトリ
	sampleDirPrefix サンプルdirへのリンクの前に追加される文字列
    mode 表示モード(cpp,cs,java)
    """

    #includeの実装
    ls_included = []
    includePattern = r'\* ' + pattern + ' (.+)'
    includer = re.compile(includePattern)
    
    for s in ls:
        m = includer.search(s.replace('\r','').replace('\n',''))
        if m != None:
            sampleNames = m.group(1).split('+')
            sampleName = sampleNames[0]
            searchedTargetDir = sampleDir
            
            files = []
            for f in aceutils.get_files(searchedTargetDir):
                basename = os.path.basename(f)
                name = os.path.splitext(basename)[0]
                if name in sampleNames:
                    files.append(f)
      
            ss_files = []
            for f in aceutils.get_files(sample_ss_dir):
                basename = os.path.basename(f)
                name = os.path.splitext(basename)[0]
                if name in sampleNames:
                    ss_files.append(f)
      
            # コードの検索
            def getFiles(ext):
                files_ = [f for f in files if os.path.splitext(f)[1]==ext]
                if len(files_) > 0:
                    return files_
                return None

            cpp_targetPath = getFiles('.cpp')
            cs_targetPath = getFiles('.cs')
            java_targetPath = getFiles('.java')

            # SSの表示
            if len(ss_files) > 0:
                ss_file = ss_files[0]
                rel_ss_file = os.path.relpath(ssDir+os.path.basename(ss_file), start=os.path.dirname(relCodePath))
                rel_ss_file = rel_ss_file.replace('\\','/')
                ls_included.append('![SS](' + sampleDirPrefix + rel_ss_file + ')\n\n')
                included_ss_paths.append(ss_files[0])
                #print(relCodePath + ' : ' + ssDir+os.path.basename(ss_file) + ' : ' + rel_ss_file)

            def includeFile(targetPaths):
                if targetPaths==None:
                    print('include not found : ' + sampleName )
                    return

                ext = os.path.splitext(targetPaths[0])[1]

                if ext=='.cpp':
                    ls_included.append(r'<h3 class="cpp">C++</h3>'+'\n')
                    ls_included.append('```cpp\n')
                elif ext=='.cs':
                    ls_included.append(r'<h3 class="csharp">C#</h3>'+'\n')
                    ls_included.append('```cs\n')
                elif ext=='.java':
                    ls_included.append(r'<h3 class="java">Java</h3>'+'\n')
                    ls_included.append('```java\n')
                else:
                    ls_included.append('```\n')

                for targetPath in targetPaths:
                    print('include : ' + targetPath)

                    # コードの編集
                    with open(targetPath, mode='r', encoding='utf-8-sig') as f:
                        for fl in f.readlines():
                            if ext=='.cpp':
                                fl = fl.replace(r'void ' + sampleName + '()',r'int main()')
                                fl = fl.replace(r'return;',r'return 0;')

                            if ext=='.cs':
                                fl = fl.replace(r'public void Run()','[System.STAThread]\r\n\tstatic void Main(string[] args)')
                                fl = fl.replace(r' : ISample','')
                                if 'Recorder.TakeScreenShot' in fl:
                                    continue
                                if 'Recorder.CaptureScreen' in fl:
                                    continue

                            if ext=='.java':
                                fl = fl.replace(r'public void Run()','public static void main(String args[])')
                                fl = fl.replace(r'implements ISample','')
                                if 'Recorder.TakeScreenShot' in fl:
                                    continue
                                if 'Recorder.CaptureScreen' in fl:
                                    continue

                            ls_included.append(fl)
                    
                ls_included.append('\n```\n')

            if mode == 'all':
                includeFile(cpp_targetPath)
                includeFile(cs_targetPath)
                includeFile(java_targetPath)
            if mode == 'cs':
                includeFile(cs_targetPath)
            elif mode == 'cpp':
                includeFile(cpp_targetPath)
            elif mode == 'java':
                includeFile(java_targetPath)
        else:
            ls_included.append(s)

    return ls_included

def include_basic_sample(ls,relCodePath,ssDir,mode=''):
    return include_sample(ls,relCodePath,'include_basic_sample',basic_sample_dir,ssDir,'./',mode)

def include_basic_sample_web(ls,relCodePath,ssDir,mode=''):
    return include_sample(ls,relCodePath,'include_basic_sample',basic_sample_dir,ssDir,'/Doc/',mode)

def include_application_sample(ls,relCodePath,ssDir,mode=''):
    return include_sample(ls,relCodePath,'include_application_sample',application_sample_dir,ssDir,'./',mode)

def include_application_sample_web(ls,relCodePath,ssDir,mode=''):
    return include_sample(ls,relCodePath,'include_application_sample',application_sample_dir,ssDir,'/Doc/',mode)