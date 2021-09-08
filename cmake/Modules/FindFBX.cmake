

if(WIN32)
    find_path(FBX_ROOT NAMES include/fbxsdk.h HINTS
        "$ENV{FBX_ROOT}"
        "$ENV{FBX_SDK_ROOT}"
        "$ENV{FBX_DIR}"
    )
    message("FBX_ROOT is ${FBX_ROOT}")
elseif(UNIX)
else()
endif()




find_path(FBX_INCLUDE_DIRS NAMES fbxsdk.h HINTS "${FBX_ROOT}/include/")


#
# only for 2017.1 version
#

set(FBX_LIBNAME libfbxsdk)
if(WIN32)
	#
	# release only
	#
	set(FBX_RELEASE_LIBRARY_DIR "${FBX_ROOT}/lib/vs2015/x64/release")
	find_library(FBX_LIBRARY_RELEASE_1 "${FBX_LIBNAME}" HINTS ${FBX_RELEASE_LIBRARY_DIR})
	#find_library(FBX_LIBRARY_RELEASE_2 "${FBX_LIBNAME}-mt" HINTS ${FBX_RELEASE_LIBRARY_DIR})
	#find_library(FBX_LIBRARY_RELEASE_3 "${FBX_LIBNAME}-md" HINTS ${FBX_RELEASE_LIBRARY_DIR})
	#find_library(FBX_LIBRARY_DEBUG)
endif()

foreach(I "1" "2" "3")
	set(FBX_LIBS ${FBX_LIBS} ${FBX_LIBRARY_RELEASE_${I}})
endforeach()

message("FBX_LIBS are ${FBX_LIBS}")

if(FBX_ROOT AND FBX_LIBS)
	set(FBX_FOUND 1)
endif() 
