QT -= core gui #No qt

#Building static library
#CBE_CONFIG += staticlib

contains(CBE_CONFIG, staticlib) {
	CONFIG += staticlib
	DEFINES += CBE_LIB
	TEMPLATE = lib
} else {
	CONFIG += console
	TEMPLATE = app
}
CONFIG += thread

win32 {
	staticlib {
		# Disable security warnings
		DEFINES += _CRT_SECURE_NO_WARNINGS
		QMAKE_CXXFLAGS_DEBUG += -Zc:wchar_t -Zc:forScope -MP -W3 -EHsc -MDd -Zi
		QMAKE_CXXFLAGS_RELEASE += -Zc:wchar_t -Zc:forScope -MP -W3 -MD -EHsc -GL -Ox

		# Add some flags to CFLAGS too
		QMAKE_CFLAGS_DEBUG += -MDd -Zc:wchar_t -Zi
		QMAKE_CFLAGS_RELEASE += -MD -Zc:wchar_t -Ox

		contains(CBE_CONFIG,optimized_debug) {
			#DEFINES += VC_USE_FORCEINLINE
			QMAKE_LFLAGS_RELEASE += -DEBUG
			QMAKE_CXXFLAGS_RELEASE += -Zi
			QMAKE_CFLAGS_RELEASE += -Zi
		} else {
			# Compiler flags:
			#  - Enable whole program optimization
			#  - Catch C++ exceptions only and tell the compiler to assume that
			#    extern C functions never throw a C++ exception
			QMAKE_CXXFLAGS_RELEASE += -GL -EHsc
			DEFINES += VC_USE_FORCEINLINE
		}
	} else {
		# Remove some automatically generated compiler flags
		QMAKE_CFLAGS = -nologo
		QMAKE_CXXFLAGS = -nologo
		QMAKE_CFLAGS_WARN_ON =
		QMAKE_CXXFLAGS_WARN_ON =
		QMAKE_CFLAGS_RELEASE =
		QMAKE_CXXFLAGS_RELEASE =
		QMAKE_CFLAGS_RELEASE_WITH_DEBUGINFO =
		QMAKE_CXXFLAGS_RELEASE_WITH_DEBUGINFO =
		QMAKE_CFLAGS_DEBUG =
		QMAKE_CXXFLAGS_DEBUG =
		QMAKE_CFLAGS_LTCG =
		QMAKE_CXXFLAGS_LTCG =
		QMAKE_CFLAGS_MP =
		QMAKE_CXXFLAGS_MP =

		# Compiler flags and their meanings in order of appending
		#  - Make wchar_t a native type
		#  - Use standard scope behavior with for-loops
		#  - Compile multiple source files by using multiple processes
		#  - Set warning level to 3
		#  - Catch C++ exceptions only and tell the compiler to assume that extern C functions never throw a C++ exception.
		#  - Create single threaded executable (with and without debug)
		# Debug only:
		#  - Generate complete debugging information
		# Release only:
		#  - Enable whole program optimization
		#  - Use maximum optimization (/Ob2gity /Gs)
		QMAKE_CXXFLAGS_DEBUG = -Zc:wchar_t -Zc:forScope -MP -W3 -EHsc -MDd -Zi
		QMAKE_CXXFLAGS_RELEASE = -Zc:wchar_t -Zc:forScope -MP -W3 -MD -EHsc -GL -Ox

		# Add some flags to CFLAGS too
		QMAKE_CFLAGS_DEBUG += -MDd -Zc:wchar_t -Zi
		QMAKE_CFLAGS_RELEASE += -MD -Zc:wchar_t -Ox

		# Disable security warnings
		DEFINES += _CRT_SECURE_NO_WARNINGS

		contains(CBE_CONFIG,optimized_debug) {
			#DEFINES += VC_USE_FORCEINLINE
			QMAKE_LFLAGS_RELEASE += -DEBUG
			QMAKE_CXXFLAGS_RELEASE += -Zi
			QMAKE_CFLAGS_RELEASE += -Zi
		} else {
			# Compiler flags:
			#  - Enable whole program optimization
			#  - Catch C++ exceptions only and tell the compiler to assume that
			#    extern C functions never throw a C++ exception
			QMAKE_CXXFLAGS_RELEASE += -GL -EHsc
			DEFINES += VC_USE_FORCEINLINE
		}
	}

	# Support only Win2K and above
	DEFINES += _WIN32_WINNT=0x0500
	CONFIG(release, debug|release){ #release build
		LIBS += -L"$$(ALLEGRO_LIB)" -lallegro-5.0.9-static -lallegro_ttf-5.0.9-static -lallegro_primitives-5.0.9-static -lallegro_image-5.0.9-static -lallegro_memfile-5.0.9-static -lallegro_font-5.0.9-static -lallegro_dialog-5.0.9-static -lallegro_audio-5.0.9-static -lallegro_acodec-5.0.9-static
		LIBS += -llibvorbisfile_static-1.3.3 -lOpenAL32_static-1.1.5.1 -lzlib_static-1.2.7 -llibogg_static-1.3.0 -llibFLAC_static-1.2.1 -lfreetype_static-2.4.11 -ldumb_static-0.9.3 -llibvorbis_static-1.3.3
		DEFINES += NDEBUG
	}
	else {
		LIBS += -L"$$(ALLEGRO_LIB)" -lallegro-5.0.9-debug-static -lallegro_ttf-5.0.9-debug-static -lallegro_primitives-5.0.9-debug-static -lallegro_image-5.0.9-debug-static -lallegro_memfile-5.0.9-debug-static -lallegro_font-5.0.9-debug-static -lallegro_dialog-5.0.9-debug-static -lallegro_audio-5.0.9-debug-static -lallegro_acodec-5.0.9-debug-static
		LIBS += -llibvorbisfile_static-1.3.3-debug -lOpenAL32_static-1.1.5.1-debug -lzlib_static-1.2.7-debug -llibogg_static-1.3.0-debug -llibFLAC_static-1.2.1-debug -lfreetype_static-2.4.11-debug -ldumb_static-0.9.3-debug -llibvorbis_static-1.3.3-debug
		DEFINES += CBE_MEMBLOCK_BOUNDS_CHECK CBE_ARRAY_BOUNDS_CHECK
	}
	LIBS += -lkernel32 -luser32 -lgdi32 -lwinspool -lcomdlg32 -ladvapi32 -lshell32 -lole32 -loleaut32 -luuid -lodbc32 -lodbccp32 -lopengl32 -lPsapi -lWinmm -lShlwapi -lgdiplus
	INCLUDEPATH += "$$(BOOST_INCLUDE)" "$$(ALLEGRO_INCLUDE)"

}


contains(CBE_CONFIG, release_debug) {
	DEFINES += VC_USE_FORCEINLINE
	DEFINES += CBE_ARRAY_BOUNDS_CHECK
	DEFINES += LOG_LEVEL_DEBUG LOG_LEVEL_INFO LOG_LEVEL_FIXME LOG_LEVEL_STUB
	contains(CBE_CONFIG, no_testing) {
		TARGET = CBCompiler
	}
} else {
	contains (CBE_CONFIG, release) {
		DEFINES += VC_USE_FORCEINLINE
		contains(CBE_CONFIG, no_testing) {
			TARGET = CBCompiler
		}
	}
}

contains(CBE_CONFIG,optimized_debug) {
	DEFINES += LOG_LEVEL_DEBUG LOG_LEVEL_INFO LOG_LEVEL_FIXME LOG_LEVEL_STUB
} else {
	!contains(CBE_CONFIG,full_optimization) {
		CONFIG += precompiled_header
		DEFINES += LOG_LEVEL_DEBUG LOG_LEVEL_INFO LOG_LEVEL_FIXME LOG_LEVEL_STUB
	}
}

contains(CBE_CONFIG,debug_hc) {
	DEFINES += LOG_LEVEL_HCDEBUG
}



HEADERS += $$files(../src/*.h)

SOURCES += $$files(../src/*.cpp)


PRECOMPILED_HEADER = ../src/precomp.h
DEFINES += ALLEGRO_STATICLINK

!contains(CBE_CONFIG,no_testing) {
	DEFINES += TEST
}

