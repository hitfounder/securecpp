function(CheckSELinux)
    if (UNIX)
        # use pkg-config to get the directories
        find_package(PkgConfig)
        pkg_check_modules(PC_SELINUX libselinux)
        set(SELINUX_DEFINITIONS ${PC_SELINUX_CFLAGS_OTHER})

        find_path(SELINUX_INCLUDE_DIR selinux/selinux.h
            HINTS
            ${PC_SELINUX_INCLUDEDIR}
            ${PC_SELINUX_INCLUDE_DIRS}
            )

        find_library(SELINUX_LIBRARIES selinux libselinux
            HINTS
            ${PC_SELINUX_LIBDIR}
            ${PC_SELINUX_LIBRARY_DIRS}
            )

        include(FindPackageHandleStandardArgs)

        # handle the QUIETLY and REQUIRED arguments and set SELINUX_FOUND
        # to TRUE if all listed variables are TRUE
        find_package_handle_standard_args (SELinux DEFAULT_MSG
            SELINUX_INCLUDE_DIR
            SELINUX_LIBRARIES
            )

        if (DEFINED SELINUX_FOUND)
            set(SELINUX_FOUND ${SELINUX_FOUND} PARENT_SCOPE) 
        endif()

        mark_as_advanced(SELINUX_INCLUDE_DIR SELINUX_LIBRARIES)
    endif (UNIX)
endfunction()