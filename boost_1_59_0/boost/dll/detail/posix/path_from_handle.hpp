// Copyright 2014-2015 Renato Tegon Forti, Antony Polukhin.
// Copyright Antony Polukhin, 2016-2022.
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt
// or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_DLL_DETAIL_POSIX_PATH_FROM_HANDLE_HPP
#define BOOST_DLL_DETAIL_POSIX_PATH_FROM_HANDLE_HPP

#include <boost/dll/config.hpp>
#include <boost/dll/detail/system_error.hpp>
#include <boost/dll/detail/posix/program_location_impl.hpp>
#include <boost/predef/os.h>

#ifdef BOOST_HAS_PRAGMA_ONCE
# pragma once
#endif

#if BOOST_OS_MACOS || BOOST_OS_IOS

#   include <mach-o/dyld.h>
#   include <mach-o/nlist.h>
#   include <cstddef> // for std::ptrdiff_t

namespace boost { namespace dll { namespace detail {
    inline void* strip_handle(void* handle) BOOST_NOEXCEPT {
        return reinterpret_cast<void*>(
            (reinterpret_cast<std::ptrdiff_t>(handle) >> 2) << 2
        );
    }

    inline boost::dll::fs::path path_from_handle(void* handle, boost::dll::fs::error_code &ec) {
        handle = strip_handle(handle);

        // Iterate through all images currently in memory
        // https://developer.apple.com/library/mac/documentation/Darwin/Reference/ManPages/man3/dyld.3.html
        const std::size_t count = _dyld_image_count(); // not thread safe: other thread my [un]load images
        for (std::size_t i = 0; i <= count; ++i) {
            // on last iteration `i` is equal to `count` which is out of range, so `_dyld_get_image_name`
            // will return NULL. `dlopen(NULL, RTLD_LAZY)` call will open the current executable.
            const char* image_name = _dyld_get_image_name(i);

            // dlopen/dlclose must not affect `_dyld_image_count()`, because libraries are already loaded and only the internal counter is affected
            void* probe_handle = dlopen(image_name, RTLD_LAZY);
            dlclose(probe_handle);

            // If the handle is the same as what was passed in (modulo mode bits), return this image name
            if (handle == strip_handle(probe_handle)) {
                boost::dll::detail::reset_dlerror();
                return image_name;
            }
        }

        boost::dll::detail::reset_dlerror();
        ec = boost::dll::fs::make_error_code(
            boost::dll::fs::errc::bad_file_descriptor
        );

        return boost::dll::fs::path();
    }

}}} // namespace boost::dll::detail

#elif BOOST_OS_ANDROID

#include <boost/dll/runtime_symbol_info.hpp>

namespace boost { namespace dll { namespace detail {

    struct soinfo {
        // if defined(__work_around_b_24465209__), then an array of char[128] goes here.
        // Unfortunately, __work_around_b_24465209__ is visible only during compilation of Android's linker
        const void* phdr;
        size_t      phnum;
        void*       entry;
        void*       base;
        // ...          // Ignoring remaning parts of the structure
    };

    inline boost::dll::fs::path path_from_handle(const void* handle, boost::dll::fs::error_code &ec) {
        static const std::size_t work_around_b_24465209__offset = 128;
        const struct soinfo* si = reinterpret_cast<const struct soinfo*>(
            static_cast<const char*>(handle) + work_around_b_24465209__offset
        );
        boost::dll::fs::path ret = boost::dll::symbol_location_ptr(si->base, ec);

        if (ec) {
            ec.clear();
            si = static_cast<const struct soinfo*>(handle);
            return boost::dll::symbol_location_ptr(si->base, ec);
        }

        return ret;
    }

}}} // namespace boost::dll::detail

#else // #if BOOST_OS_MACOS || BOOST_OS_IOS || BOOST_OS_ANDROID

// for dlinfo
#include <dlfcn.h>

#if BOOST_OS_QNX
// QNX's copy of <elf.h> and <link.h> reside in sys folder
#   include <sys/link.h>
#else
#   include <link.h>    // struct link_map
#endif

namespace boost { namespace dll { namespace detail {

#if BOOST_OS_QNX
    // Android and QNX miss struct link_map. QNX misses ElfW macro, so avoiding it.
    struct link_map {
        void *l_addr;   // Base address shared object is loaded at
        char *l_name;   // Absolute file name object was found in
        // ...          // Ignoring remaning parts of the structure
    };
#endif // #if BOOST_OS_QNX

    inline boost::dll::fs::path path_from_handle(void* handle, boost::dll::fs::error_code &ec) {
        // RTLD_DI_LINKMAP (RTLD_DI_ORIGIN returns only folder and is not suitable for this case)
        // Obtain the Link_map for the handle  that  is  specified.
        // The  p  argument  points to a Link_map pointer (Link_map
        // **p). The actual storage for the Link_map  structure  is
        // maintained by ld.so.1.
        //
        // Unfortunately we can not use `dlinfo(handle, RTLD_DI_LINKMAP, &link_map) < 0`
        // because it is not supported on MacOS X 10.3, NetBSD 3.0, OpenBSD 3.8, AIX 5.1,
        // HP-UX 11, IRIX 6.5, OSF/1 5.1, Cygwin, mingw, Interix 3.5, BeOS.
        // Fortunately investigating the sources of open source projects brought the understanding, that
        // `handle` is just a `struct link_map*` that contains full library name.

        const struct link_map* link_map = 0;
#if BOOST_OS_BSD_FREE
        // FreeBSD has it's own logic http://code.metager.de/source/xref/freebsd/libexec/rtld-elf/rtld.c
        // Fortunately it has the dlinfo call.
        if (dlinfo(handle, RTLD_DI_LINKMAP, &link_map) < 0) {
            link_map = 0;
        }
#else
        link_map = static_cast<const struct link_map*>(handle);
#endif
        if (!link_map) {
            boost::dll::detail::reset_dlerror();
            ec = boost::dll::fs::make_error_code(
                boost::dll::fs::errc::bad_file_descriptor
            );

            return boost::dll::fs::path();
        }

        if (!link_map->l_name || *link_map->l_name == '\0') {
            return program_location_impl(ec);
        }

        return boost::dll::fs::path(link_map->l_name);
    }

}}} // namespace boost::dll::detail

#endif // #if BOOST_OS_MACOS || BOOST_OS_IOS

#endif // BOOST_DLL_DETAIL_POSIX_PATH_FROM_HANDLE_HPP



/* path_from_handle.hpp
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
*/