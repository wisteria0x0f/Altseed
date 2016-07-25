import aceutils

path = r'https://github.com/glfw/glfw/archive/'
zipname = 'f7006f64fb12e21f30a99351d7c854ea75b5c3eb.zip'
pathname = 'glfw-f7006f64fb12e21f30a99351d7c854ea75b5c3eb'

path = r'https://github.com/altseed/glfw/archive/'
zipname = 'ed451ea6823380af9ea1ced320182fbcfb176c64.zip'
pathname = 'glfw-ed451ea6823380af9ea1ced320182fbcfb176c64'

aceutils.cdToScript()
aceutils.cd(r'../')
aceutils.rm(zipname)
aceutils.rmdir(pathname)

aceutils.wget(path + zipname)
aceutils.unzip(zipname)

aceutils.editCmakeForACE(pathname + r'/CMakeLists.txt')

aceutils.rmdir(r"glfw_bin")
aceutils.rmdir(r"glfw_bin_x64")

aceutils.mkdir(r"glfw_bin")
aceutils.mkdir(r"glfw_bin_x64")

aceutils.cd(r"glfw_bin")

if aceutils.isWin():
	aceutils.call(aceutils.cmd_cmake+r'-D USE_MSVC_RUNTIME_LIBRARY_DLL:BOOL=OFF -D USE_INTERNAL_LOADER:BOOL=OFF ../' + pathname + '/')
	aceutils.call(aceutils.cmd_compile + r'ALL_BUILD.vcxproj /p:configuration=Debug')
	aceutils.call(aceutils.cmd_compile + r'ALL_BUILD.vcxproj /p:configuration=Release')
elif aceutils.isMac():
	aceutils.call(r'cmake -G "Unix Makefiles" -D BUILD_SHARED_LIBS:BOOL=OFF -D CMAKE_INSTALL_PREFIX:PATH=../Dev "-DCMAKE_OSX_ARCHITECTURES=x86_64;i386" ../' + pathname + '/')
	aceutils.call(r'make install')
else:
	aceutils.call(r'cmake -G "Unix Makefiles" -D BUILD_SHARED_LIBS:BOOL=OFF -D CMAKE_INSTALL_PREFIX=../Dev ../' + pathname + '/')
	aceutils.call(r'make install')

aceutils.cd(r"../")

aceutils.cd(r"glfw_bin_x64")

if aceutils.isWin():
	aceutils.call(aceutils.cmd_cmake_x64+r'-D USE_MSVC_RUNTIME_LIBRARY_DLL:BOOL=OFF -D USE_INTERNAL_LOADER:BOOL=OFF ../' + pathname + '/')
	aceutils.call(aceutils.cmd_compile + r'ALL_BUILD.vcxproj /p:configuration=Debug')
	aceutils.call(aceutils.cmd_compile + r'ALL_BUILD.vcxproj /p:configuration=Release')

aceutils.cd(r"../")

aceutils.mkdir(r"Dev/include/GLFW/")

if aceutils.isWin():

	aceutils.mkdir(r'Dev/lib/x86/')
	aceutils.mkdir(r'Dev/lib/x86/Debug')
	aceutils.mkdir(r'Dev/lib/x86/Release')

	aceutils.mkdir(r'Dev/lib/x64/')
	aceutils.mkdir(r'Dev/lib/x64/Debug')
	aceutils.mkdir(r'Dev/lib/x64/Release')

	aceutils.copy(pathname + r'/include/GLFW/glfw3.h', r'Dev/include/GLFW/')
	aceutils.copy(pathname + r'/include/GLFW/glfw3native.h', r'Dev/include/GLFW')

	aceutils.copy(r'glfw_bin/src/Debug/glfw3.lib', r'Dev/lib/x86/Debug/')
	aceutils.copy(r'glfw_bin/src/Release/glfw3.lib', r'Dev/lib/x86/Release/')

	aceutils.copy(r'glfw_bin_x64/src/Debug/glfw3.lib', r'Dev/lib/x64/Debug/')
	aceutils.copy(r'glfw_bin_x64/src/Release/glfw3.lib', r'Dev/lib/x64/Release/')

else:
	aceutils.copy(pathname + r'/include/GLFW/glfw3.h', r'Dev/include/GLFW/')
	aceutils.copy(pathname + r'/include/GLFW/glfw3native.h', r'Dev/include/GLFW')