// Copyright 2014-2015 Renato Tegon Forti, Antony Polukhin.
// Copyright 2016-2019 Antony Polukhin.
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