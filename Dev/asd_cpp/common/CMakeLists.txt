
# Debug or Release
set(CMAKE_CONFIGURATION_TYPES Debug Release CACHE TYPE INTERNAL FORCE )

# Minimum
cmake_minimum_required(VERSION 2.8)

# Set project
project(asd_common)

# Add codes
FILE(GLOB_RECURSE cpps *.cpp)
FILE(GLOB_RECURSE hs *.h)
list(APPEND common_src ${cpps} ${hs})

foreach(FILE ${common_src}) 
    # Get the directory of the source file
    get_filename_component(PARENT_DIR "${FILE}" DIRECTORY)

    # Remove common directory prefix to make the group
    string(REPLACE "${CMAKE_CURRENT_SOURCE_DIR}" "" GROUP "${PARENT_DIR}")

    # Make sure we are using windows slashes
    string(REPLACE "/" "\\" GROUP "${GROUP}")

    # Group into "Source Files" and "Header Files"
    if ("${FILE}" MATCHES ".*\\.cpp")
       set(GROUP "Files${GROUP}")
    elseif("${FILE}" MATCHES ".*\\.h")
       set(GROUP "Files${GROUP}")
    endif()

    source_group("${GROUP}" FILES "${FILE}")
endforeach()

# Set MSVC Flags
if (MSVC)
	if (NOT USE_MSVC_RUNTIME_LIBRARY_DLL)
		foreach (flag CMAKE_C_FLAGS
			CMAKE_C_FLAGS_DEBUG
			CMAKE_C_FLAGS_RELEASE
			CMAKE_CXX_FLAGS
			CMAKE_CXX_FLAGS_DEBUG
			CMAKE_CXX_FLAGS_RELEASE)

			if (${flag} MATCHES "/MD")
				string(REGEX REPLACE "/MD" "/MT" ${flag} "${${flag}}")
			endif()
			if (${flag} MATCHES "/MDd")
				string(REGEX REPLACE "/MDd" "/MTd" ${flag} "${${flag}}")
			endif()
		endforeach()
	endif()
endif()

add_library( asd_common STATIC ${common_src} )

set_target_properties(asd_common PROPERTIES ARCHIVE_OUTPUT_DIRECTORY "../../lib/" )
set_target_properties(asd_common PROPERTIES LIBRARY_OUTPUT_DIRECTORY "../../lib/" )

if (MSVC)
set_target_properties(asd_common PROPERTIES OUTPUT_NAME_DEBUG "asd_common" )
set_target_properties(asd_common PROPERTIES OUTPUT_NAME_RELEASE "asd_common" )
else()
set_target_properties(asd_common PROPERTIES OUTPUT_NAME "asd_common" )
endif()

