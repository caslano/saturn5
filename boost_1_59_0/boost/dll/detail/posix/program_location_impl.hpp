// Copyright 2014 Renato Tegon Forti, Antony Polukhin.
// Copyright Antony Polukhin, 2015-2022.
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt
// or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_DLL_DETAIL_POSIX_PROGRAM_LOCATION_IMPL_HPP
#define BOOST_DLL_DETAIL_POSIX_PROGRAM_LOCATION_IMPL_HPP

#include <boost/dll/config.hpp>
#include <boost/dll/detail/system_error.hpp>
#include <boost/predef/os.h>

#ifdef BOOST_HAS_PRAGMA_ONCE
# pragma once
#endif

#if BOOST_OS_MACOS || BOOST_OS_IOS

#include <mach-o/dyld.h>

namespace boost { namespace dll { namespace detail {
    inline boost::dll::fs::path program_location_impl(boost::dll::fs::error_code &ec) {
        ec.clear();

        char path[1024];
        uint32_t size = sizeof(path);
        if (_NSGetExecutablePath(path, &size) == 0)
            return boost::dll::fs::path(path);

        char *p = new char[size];
        if (_NSGetExecutablePath(p, &size) != 0) {
            ec = boost::dll::fs::make_error_code(
                boost::dll::fs::errc::bad_file_descriptor
            );
        }

        boost::dll::fs::path ret(p);
        delete[] p;
        return ret;
    }
}}} // namespace boost::dll::detail

#elif BOOST_OS_SOLARIS

#include <stdlib.h>
namespace boost { namespace dll { namespace detail {
    inline boost::dll::fs::path program_location_impl(boost::dll::fs::error_code& ec) {
        ec.clear();

        return boost::dll::fs::path(getexecname());
    }
}}} // namespace boost::dll::detail

#elif BOOST_OS_BSD_FREE

#include <sys/types.h>
#include <sys/sysctl.h>
#include <stdlib.h>

namespace boost { namespace dll { namespace detail {
    inline boost::dll::fs::path program_location_impl(boost::dll::fs::error_code& ec) {
        ec.clear();

        int mib[4];
        mib[0] = CTL_KERN;
        mib[1] = KERN_PROC;
        mib[2] = KERN_PROC_PATHNAME;
        mib[3] = -1;
        char buf[10240];
        size_t cb = sizeof(buf);
        sysctl(mib, 4, buf, &cb, NULL, 0);

        return boost::dll::fs::path(buf);
    }
}}} // namespace boost::dll::detail



#elif BOOST_OS_BSD_NET

namespace boost { namespace dll { namespace detail {
    inline boost::dll::fs::path program_location_impl(boost::dll::fs::error_code &ec) {
        return boost::dll::fs::read_symlink("/proc/curproc/exe", ec);
    }
}}} // namespace boost::dll::detail

#elif BOOST_OS_BSD_DRAGONFLY


namespace boost { namespace dll { namespace detail {
    inline boost::dll::fs::path program_location_impl(boost::dll::fs::error_code &ec) {
        return boost::dll::fs::read_symlink("/proc/curproc/file", ec);
    }
}}} // namespace boost::dll::detail

#elif BOOST_OS_QNX

#include <fstream>
#include <string> // for std::getline
namespace boost { namespace dll { namespace detail {
    inline boost::dll::fs::path program_location_impl(boost::dll::fs::error_code &ec) {
        ec.clear();

        std::string s;
        std::ifstream ifs("/proc/self/exefile");
        std::getline(ifs, s);

        if (ifs.fail() || s.empty()) {
            ec = boost::dll::fs::make_error_code(
                boost::dll::fs::errc::bad_file_descriptor
            );
        }

        return boost::dll::fs::path(s);
    }
}}} // namespace boost::dll::detail

#else  // BOOST_OS_LINUX || BOOST_OS_UNIX || BOOST_OS_HPUX || BOOST_OS_ANDROID

namespace boost { namespace dll { namespace detail {
    inline boost::dll::fs::path program_location_impl(boost::dll::fs::error_code &ec) {
        // We can not use
        // boost::dll::detail::path_from_handle(dlopen(NULL, RTLD_LAZY | RTLD_LOCAL), ignore);
        // because such code returns empty path.

        return boost::dll::fs::read_symlink("/proc/self/exe", ec);   // Linux specific
    }
}}} // namespace boost::dll::detail

#endif

#endif // BOOST_DLL_DETAIL_POSIX_PROGRAM_LOCATION_IMPL_HPP


/* program_location_impl.hpp
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
*/