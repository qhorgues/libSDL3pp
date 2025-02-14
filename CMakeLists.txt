cmake_minimum_required(VERSION 3.16 FATAL_ERROR)

# meta
project(libSDL3pp LANGUAGES CXX VERSION 0.0.1)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED YES)
set(CMAKE_CXX_EXTENSIONS NO)

if(CMAKE_SOURCE_DIR STREQUAL PROJECT_SOURCE_DIR)
	option(SDL3PP_WITH_IMAGE "Enable SDL3_image support" ON)
	option(SDL3PP_WITH_TTF "Enable SDL3_ttf support" ON)
	option(SDL3PP_WITH_MIXER "Enable SDL3_mixer support" ON)

	option(SDL3PP_WITH_EXAMPLES "Build examples" ON)
	option(SDL3PP_WITH_TESTS "Build tests" ON)
	option(SDL3PP_ENABLE_LIVE_TESTS "Enable live tests (require X11 display and audio device)" ON)
	option(SDL3PP_STATIC "Build static library instead of shared one" OFF)
else()
	# please set SDL3PP_WITH_IMAGE, SDL3PP_WITH_TTF, SDL3PP_WITH_MIXER in parent project as needed
endif()

# depends
find_package(SDL3 QUIET)
if (NOT SDL3_FOUND)

	include(FetchContent)
	
	message(STATUS "Download SDL3 library")

	FetchContent_Declare(SDL
		GIT_REPOSITORY "https://github.com/libsdl-org/SDL.git"
		GIT_TAG "release-3.2.0"
		SOURCE_DIR "SDL3"
	)
	FetchContent_MakeAvailable(SDL)

	include_directories( ${CMAKE_BINARY_DIR}/SDL3/include)
	set (SDL3_DIR ${CMAKE_BINARY_DIR}/SDL3)

	set(CMAKE_PREFIX_PATH ${CMAKE_PREFIX_PATH}:${CMAKE_BINARY_DIR})

	link_directories(${CMAKE_BINARY_DIR})
endif (NOT SDL3_FOUND)

set(SDL3_ALL_LIBRARIES SDL3::SDL3)
set(SDL3_ALL_PKGCONFIG_MODULES sdl3)

if(MINGW)
	set(MINGW32_LIBRARY "mingw32" CACHE STRING "mingw32 library")
	set(SDL3PP_EXTRA_LIBRARIES ${MINGW32_LIBRARY} ${SDL3PP_EXTRA_LIBRARIES})
	set(SDL3PP_EXTRA_PKGCONFIG_LIBRARIES "-l${MINGW32_LIBRARY} ${SDL3PP_EXTRA_PKGCONFIG_LIBRARIES}")
endif()

if(SDL3PP_WITH_IMAGE)
	find_package(SDL3_image QUIET)
	if (NOT SDL3_image_FOUND)

		include(FetchContent)
		
		message(STATUS "Download SDL3 image library")

		FetchContent_Declare(SDL_image
			GIT_REPOSITORY "https://github.com/libsdl-org/SDL_image.git"
			GIT_TAG "release-3.2.0"
			SOURCE_DIR "SDL3_image"
		)
		FetchContent_MakeAvailable(SDL_image)

		include_directories( ${CMAKE_BINARY_DIR}/SDL3_image/include)
		set (SDL3_image_DIR ${CMAKE_BINARY_DIR}/SDL3_image)

		set(CMAKE_PREFIX_PATH ${CMAKE_PREFIX_PATH}:${CMAKE_BINARY_DIR})

		link_directories(${CMAKE_BINARY_DIR})
	endif (NOT SDL3_image_FOUND)

	set(SDL3_ALL_LIBRARIES ${SDL3_ALL_LIBRARIES} SDL3_image::SDL3_image)
	set(SDL3_ALL_PKGCONFIG_MODULES "${SDL3_ALL_PKGCONFIG_MODULES} SDL3_image")
else()
	message(STATUS "SDL3_image support disabled")
endif()

if(SDL3PP_WITH_TTF)
	find_package(SDL3_ttf QUIET)
	if (NOT SDL3_ttf_FOUND)

		include(FetchContent)
		
		message(STATUS "Download SDL3 ttf library")

		FetchContent_Declare(SDL_ttf
			GIT_REPOSITORY "https://github.com/libsdl-org/SDL_ttf.git"
			GIT_TAG "preview-3.1.0"
			SOURCE_DIR "SDL3_ttf"
		)
		FetchContent_MakeAvailable(SDL_ttf)

		include_directories( ${CMAKE_BINARY_DIR}/SDL3_ttf/include)
		set (SDL3_ttf_DIR ${CMAKE_BINARY_DIR}/SDL3_ttf)

		set(CMAKE_PREFIX_PATH ${CMAKE_PREFIX_PATH}:${CMAKE_BINARY_DIR})

		link_directories(${CMAKE_BINARY_DIR})
	endif (NOT SDL3_ttf_FOUND)
	set(SDL3_ALL_LIBRARIES ${SDL3_ALL_LIBRARIES} SDL3_ttf::SDL3_ttf)
	set(SDL3_ALL_PKGCONFIG_MODULES "${SDL3_ALL_PKGCONFIG_MODULES} SDL3_ttf")
else()
	message(STATUS "SDL3_ttf support disabled")
endif()

if(SDL3PP_WITH_MIXER)
	find_package(SDL3_mixer QUIET)
	if (NOT SDL3_mixer_FOUND)

		include(FetchContent)
		
		message(STATUS "Download SDL3 mixer library")

		FetchContent_Declare(SDL_mixer
			GIT_REPOSITORY "https://github.com/libsdl-org/SDL_mixer.git"
			GIT_TAG "main"
			SOURCE_DIR "SDL3_mixer"
		)
		FetchContent_MakeAvailable(SDL_mixer)

		include_directories( ${CMAKE_BINARY_DIR}/SDL3_mixer/include)
		set (SDL3_mixer_DIR ${CMAKE_BINARY_DIR}/SDL3_mixer)

		set(CMAKE_PREFIX_PATH ${CMAKE_PREFIX_PATH}:${CMAKE_BINARY_DIR})

		link_directories(${CMAKE_BINARY_DIR})
	endif (NOT SDL3_mixer_FOUND)
	set(SDL3_ALL_LIBRARIES ${SDL3_ALL_LIBRARIES} SDL3_mixer::SDL3_mixer)
	set(SDL3_ALL_PKGCONFIG_MODULES "${SDL3_ALL_PKGCONFIG_MODULES} SDL3_mixer")
else()
	message(STATUS "SDL3_mixer support disabled")
endif()

# compiler flags & definitions
#if(MSVC)
#	set(SDL3PP_WARNINGS "${SDL3PP_WARNINGS} /W3")
#else()
#	set(SDL3PP_WARNINGS "${SDL3PP_WARNINGS} -Wall -Wextra -pedantic")
#
#	if(CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
#		set(SDL3PP_WARNINGS "${SDL3PP_WARNINGS} -Wmissing-prototypes -Wtautological-compare -Wshorten-64-to-32")
#
#		# For adventurous
#		#set(SDL3PP_WARNINGS "${SDL3PP_WARNINGS} -Weverything -Wno-c++98-compat -Wno-padded")
#	endif()
#endif()

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${SDL3PP_WARNINGS}")

# config.h
configure_file(
	SDL3pp/Config.hpp.in
	SDL3pp/Config.hpp
)

# sources
set(LIBRARY_SOURCES
)

set(LIBRARY_INLINE_SOURCES
)

set(LIBRARY_HEADERS
)

set(LIBRARY_INLINE_SOURCES
)

# optional sources
if(SDL3PP_WITH_TTF)
	set(LIBRARY_SOURCES
		${LIBRARY_SOURCES}
		SDL3pp/SDLTTF.cpp
		SDL3pp/Font.cpp
	)
	set(LIBRARY_HEADERS
		${LIBRARY_HEADERS}
		SDL3pp/SDLTTF.hpp
		SDL3pp/Font.hpp
	)
endif()

if(SDL3PP_WITH_IMAGE)
	set(LIBRARY_SOURCES
		${LIBRARY_SOURCES}
		SDL3pp/SDLImage.cpp
	)
	set(LIBRARY_HEADERS
		${LIBRARY_HEADERS}
		SDL3pp/SDLImage.hpp
	)
endif()

if(SDL3PP_WITH_MIXER)
	set(LIBRARY_SOURCES
		${LIBRARY_SOURCES}
		SDL3pp/Chunk.cpp
		SDL3pp/Mixer.cpp
		SDL3pp/Music.cpp
		SDL3pp/SDLMixer.cpp
	)
	set(LIBRARY_HEADERS
		${LIBRARY_HEADERS}
		SDL3pp/Chunk.hpp
		SDL3pp/Mixer.hpp
		SDL3pp/Music.hpp
		SDL3pp/SDLMixer.hpp
	)
endif()

# targets
include(GenerateExportHeader)

if(SDL3PP_STATIC)
	add_library(SDL3pp STATIC ${LIBRARY_SOURCES} ${LIBRARY_HEADERS})
	set_target_properties(SDL3pp PROPERTIES
		POSITION_INDEPENDENT_CODE ON
	)
else()
	add_library(SDL3pp SHARED ${LIBRARY_SOURCES} ${LIBRARY_HEADERS})
	set_target_properties(SDL3pp PROPERTIES
		VERSION 8.3.0
		SOVERSION 8
		C_VISIBILITY_PRESET hidden
	)
endif()
target_include_directories(SDL3pp PUBLIC
	$<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}>
	$<BUILD_INTERFACE:${PROJECT_BINARY_DIR}>
	$<INSTALL_INTERFACE:include>
)
target_link_libraries(SDL3pp PUBLIC ${SDL3_ALL_LIBRARIES})
generate_export_header(SDL3pp EXPORT_FILE_NAME SDL3pp/Export.hpp)

add_library(SDL3pp::SDL3pp ALIAS SDL3pp)

if(CMAKE_SOURCE_DIR STREQUAL PROJECT_SOURCE_DIR)
	# examples and tests
	if(SDL3PP_WITH_EXAMPLES)
		add_subdirectory(examples)
	endif()

	if(SDL3PP_WITH_TESTS)
		enable_testing()
		add_subdirectory(tests)
	endif()

	# doxygen
	find_package(Doxygen)
	if(DOXYGEN_FOUND)
		configure_file(${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile.in ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile @ONLY)
		add_custom_target(doxygen
			${DOXYGEN_EXECUTABLE} ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile
			WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
			COMMENT "Generating API documentation with Doxygen" VERBATIM
		)
	endif()

	# install
	include(GNUInstallDirs)

	if(SDL3PP_WITH_IMAGE AND NOT SDL3_image_FOUND)
	install(TARGETS SDL3_image-shared
		EXPORT SDL3pp-targets
		RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
		LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
		ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
	)
	endif(SDL3PP_WITH_IMAGE AND NOT SDL3_image_FOUND)

	if(SDL3PP_WITH_TTF AND NOT SDL3_ttf_FOUND)
	install(TARGETS SDL3_ttf-shared
		EXPORT SDL3pp-targets
		RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
		LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
		ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
	)
	endif(SDL3PP_WITH_TTF AND NOT SDL3_ttf_FOUND)

	if(SDL3PP_WITH_MIXER AND NOT SDL3_mixer_FOUND)
	install(TARGETS SDL3_mixer-shared
		EXPORT SDL3pp-targets
		RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
		LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
		ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
	)
	endif(SDL3PP_WITH_MIXER AND NOT SDL3_mixer_FOUND)

	install(TARGETS SDL3pp
		EXPORT SDL3pp-targets
		RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
		LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
		ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
	)
	install(
		FILES
			${LIBRARY_HEADERS}
			${PROJECT_BINARY_DIR}/SDL3pp/Config.hpp
			${PROJECT_BINARY_DIR}/SDL3pp/Export.hpp
		DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/SDL3pp
	)

	configure_file(sdl3pp.pc.in sdl3pp.pc @ONLY)
	install(
		FILES
			${PROJECT_BINARY_DIR}/sdl3pp.pc
		DESTINATION ${CMAKE_INSTALL_LIBDIR}/pkgconfig
	)

	configure_file(cmake/SDL3ppConfig.cmake.in cmake/SDL3ppConfig.cmake @ONLY)
	install(EXPORT SDL3pp-targets
		FILE SDL3ppTargets.cmake
		NAMESPACE SDL3pp::
		DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/SDL3pp
	)
	install(FILES ${PROJECT_BINARY_DIR}/cmake/SDL3ppConfig.cmake DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/SDL3pp)
endif()
