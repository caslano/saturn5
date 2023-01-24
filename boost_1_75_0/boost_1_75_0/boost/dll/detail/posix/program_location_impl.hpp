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
RcvdQoexGYU+czayWzRL9oregOzv7TnLbnmqt7Zb7hbKKuyWFdt5t0zFD7y+Xd8tW3dZluxrnaG7BSzZn71i7RaUP6rcyeJD5vJX9N3SYZfHcpHAbjnuo5B8NVW5W36LDtkt9+Nu+UJs4sCk02AvIqsyek8+dxCLd1qrRafQ3W/MCPG8vMDfdUpR8GHHOU9wzNrJiKLxK3xCWYPAWJ1fRnGGTldFS2zExzthdCDP5Kclu8r/1CWRKncJLwNM2Xz9dBvoY446FYp3pwtNnQWroyxvVhuGPQ7qYBQ9oAaQFqRiR9FIsfkFJiY3Skkoo7WdkPwnigmJMgUSNbG+bgXdxwXdOTs8KsWSaiL6jre2EZtvoHLzWOu8f9B9yQ6PWgX5UHzULReRNqB8wvZyzR9H+3DwFZY2IWSq464Z37FBWjmHDjK5CsEMEPir3LMetWkK9InFkSEIUkoI0ngUTuFn9dGDIosLxEc3AmTHRBKK7CUUcTOKHJQogsH7aU5XOSZxqXxcosioywlFYIDmjFOMIge5e7x709/1UGSGjiJyXgcj7KuUCxiS+T/AEFKlFkacHUdITpXHgeOD7ou2S3/EjBA8aWUJsYwnWrxQzHYLQ8gBE2sXUKgj6VTBh+khD3Mt0ahc98YAoW6qaDQuHfCtLMrx4AJ2nqMJUpiyiYpVsQhsNyVDe92U7KfwOQ5Qv6iWBIQC1qQKrUcufiSV
*/