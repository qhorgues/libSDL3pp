function (set_sanitizer)
	if (NOT MINGW)		
		if ((${CMAKE_BUILD_TYPE} MATCHES "Debug") OR (${CMAKE_BUILD_TYPE} MATCHES "RelWithDebInfo" ))
		
			option(ENEABLE_SANITIZER "Use sanitizer in Debug and RelWithDebInfo build type" TRUE)
			if (ENEABLE_SANITIZER)
				if (MSVC)
					list (APPEND CMAKE_EXE_LINKER_FLAGS /fsanitize=address /analyse)
				else()

					set(SANITIZE 
						-fsanitize=address
						-fsanitize=pointer-compare
						-fsanitize=pointer-subtract
						-fsanitize=leak
						-fsanitize=undefined
						# -fsanitize=bounds-strict
						-fsanitize=float-divide-by-zero
						-fsanitize=float-cast-overflow
					)

					list (APPEND CMAKE_EXE_LINKER_FLAGS ${SANITIZE})
					add_link_options(${SANITIZE})
				endif (MSVC)
			endif (ENEABLE_SANITIZER)

		endif ()
	else ()
		list (APPEND CMAKE_EXE_LINKER_FLAGS -fstack-protector -lssp)
	endif (NOT MINGW)
endfunction (set_sanitizer)


function(set_target_warnings target)
    option(WARNINGS_AS_ERRORS "Treat compiler warnings as errors" TRUE)

	if (NOT MINGW)		
		if ((${CMAKE_BUILD_TYPE} MATCHES "Debug") OR (${CMAKE_BUILD_TYPE} MATCHES "RelWithDebInfo" ))
			
			option(ENEABLE_SANITIZER "Use sanitizer in Debug and RelWithDebInfo build type" TRUE)
			if (ENEABLE_SANITIZER)
				message(STATUS "Sanitizer active ${BUILD_DEBUG}")
				if (NOT MSVC)
					set(SANITIZE 
						-fsanitize=address
						-fsanitize=pointer-compare
						-fsanitize=pointer-subtract
						-fsanitize=leak
						-fsanitize=undefined
						# -fsanitize=bounds-strict
						-fsanitize=float-divide-by-zero
						-fsanitize=float-cast-overflow
						)	
				elseif (NOT MSVC)		
					set (FORTIFY -D_FORTIFY_SOURCE=2 -fstack-protector-strong -fstack-clash-protection -fPIE)
					set (CMAKE_C_FLAGS_DEBUG "-g -O2" CACHE INTERNAL "debug flags")
				endif (NOT MSVC)
			endif (ENEABLE_SANITIZER)
		else()
			set(SANITIZE "")
		endif ()
	endif (NOT MINGW)

    set (GCC_WARNINGS
		-Wall
	    -Wextra
	    -Wpedantic
	    -Wformat=2
	    -Wformat-overflow=2
	    -Wformat-truncation=2
	    -Wformat-security
	    -Wnull-dereference
	    -Wstack-protector
	    -Wtrampolines
	    -Walloca
	    -Wvla
	    -Warray-bounds=2
	    -Wimplicit-fallthrough=3
	    -Wshift-overflow=2
	    -Wcast-qual
	    -Wstringop-overflow=4
	    -Wconversion
	    -Warith-conversion
	    -Wlogical-op
	    -Wduplicated-cond
	    -Wduplicated-branches
	    -Wformat-signedness
	    -Wshadow
	    -Wstrict-overflow=4 # 2
	    -Wundef
	    -Wswitch-default
	    -Wswitch-enum
	    -Wstack-usage=1000000
	    -Wcast-align=strict

	    ${FORTIFY}

	    -Wl,-z,relro
	    -Wl,-z,now
	    -Wl,-z,noexecstack
	    -Wl,-z,separate-code
		
        -Wold-style-cast # warn for c-style casts
        -Wnon-virtual-dtor # warn the user if a class with virtual functions has a non-virtual destructor. This helps catch hard to track down memory errors
        -Woverloaded-virtual # warn if you overload (not override) a virtual function
        -Wsuggest-override # warn when 'override' could be used on a member function overriding a virtual function
    
	)

    set (CLANG_WARNINGS
    	-Walloca
	    -Wcast-qual
	    -Wconversion
	    -Wformat=2
	    -Wformat-security
	    -Wnull-dereference
	    -Wstack-protector
	    -Wvla
	    -Warray-bounds
	    -Wnull-pointer-arithmetic
	    -Wassign-enum
	    -Wbad-function-cast
	    -Wconditional-uninitialized
	    -Wconversion
	    -Wfloat-equal
	    -Wformat-type-confusion
	    -Widiomatic-parentheses 
	    -Wimplicit-fallthrough
	    -Wloop-analysis
	    -Wpointer-arith
	    -Wshift-sign-overflow
	    -Wshorten-64-to-32
	    -Wswitch-enum
	    -Wtautological-constant-in-range-compare
	    -Wunreachable-code-aggressive
	    -Wthread-safety
	    -Wthread-safety-beta
	    -Wcomma
	    
	    ${FORTIFY}
		
	    #-fsanitize=safe-stack
	    

	    # -Wl,-z,relro
	    # -Wl,-z,now
	    # -Wl,-z,noexecstack
	    # -Wl,-z,separate-code

        -Wold-style-cast # warn for c-style casts
        -Wnon-virtual-dtor # warn the user if a class with virtual functions has a non-virtual destructor. This helps catch hard to track down memory errors
        -Woverloaded-virtual # warn if you overload (not override) a virtual function
        -Wsuggest-override # warn when 'override' could be used on a member function overriding a virtual function
    )

    set (MSVC_WARNINGS
	    /Wall
	    /sdl
	    /guard:cf
	    /guard:ehcont
	    /CETCOMPAT
    )

    if(WARNINGS_AS_ERRORS)
        set(CLANG_WARNINGS ${CLANG_WARNINGS} -Werror)
        set(GCC_WARNINGS ${GCC_WARNINGS} -Werror)
        set(MSVC_WARNINGS ${MSVC_WARNINGS} /WX)
    endif()

    if(MSVC)
        set(FILE_WARNINGS ${MSVC_WARNINGS})
    elseif(CMAKE_CXX_COMPILER_ID MATCHES ".*Clang")
        set(FILE_WARNINGS ${CLANG_WARNINGS})
    elseif(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
        set(FILE_WARNINGS ${GCC_WARNINGS})
    else()
        message(AUTHOR_WARNING "No compiler warnings set for '${CMAKE_CXX_COMPILER_ID}' compiler.")
    endif()

    target_compile_options(${target} PRIVATE ${FILE_WARNINGS} ${SANITIZE})
endfunction()