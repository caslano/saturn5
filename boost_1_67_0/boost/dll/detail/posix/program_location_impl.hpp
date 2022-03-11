// Copyright 2014 Renato Tegon Forti, Antony Polukhin.
// Copyright 2015-2019 Antony Polukhin.
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