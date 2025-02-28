add_definitions(-DTESTDATA_DIR="${PROJECT_SOURCE_DIR}/testdata")

set(EXAMPLES
	window
)

if(SDL3PP_WITH_IMAGE)
	set(EXAMPLES ${EXAMPLES}
	)
endif()

if(SDL3PP_WITH_MIXER)
	set(EXAMPLES ${EXAMPLES}
	)
endif()

if(SDL3PP_WITH_TTF)
	set(EXAMPLES ${EXAMPLES}
	)
endif()

foreach(EXAMPLE ${EXAMPLES})
	add_executable(${EXAMPLE} ${EXAMPLE}.cpp)
	target_link_libraries(${EXAMPLE} SDL3pp::SDL3pp)
endforeach()
