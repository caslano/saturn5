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
ToUlee3tyFOz3oH/wzbKXrFgu1Pgf/VX6IMKkWtKSomSClGI5hdP+Pbncpk0WHN+H2DwxDsL6AadWw8VYA+RUNPbo0FarFdCIdlSubHaz95y5LfxbdqoUWuYoyHa0J93WoJRVdjAqMJlVarGShgrw+obEuY8YgREj5T7RUJD0ZkELiZT2aYA0qnIUgMW4aSam829TxM73F6JVKWbX/j/b6/9Qq7nX1+wvEXnWtaN30xx/CGs4r3MO73Kh2amEW2x1ZtNl0/gQ9npBXHrkTkLS6VzqXROHfQsVSByzcZcPsrFFtJeNBT04ujG00NYRtNb7Sh/rieO9Yxy+Nfkk1pp//W5aHBVBlkUI1vbfGtnoxwuj81CQx4Y8/sDx7sf4gY9a24FJQqEvrxDhNZ/Upu0N4P63rPKQxzI//3Xncn9iZzm0AuOGzIjDN0tyrk/Cbk6hyPe+pnuNKD7nOAlNjF2Iin4F9HOcR38MceDIKGJsf0y7Nz+JCpxApV4AkscSCVC6khgm1hPW6Dhcs3qFECgCDX+yIfk4X9azSyIBgEd530Vmx88/QounZB6Ygqp06BI2JJXyaapL0Rka/di89N5d4YwCv8uYbSRaoHtmiMWrmmYyhXzEMobxYlCd+vBnI2cdz+V92nxHiMPiZA3gj5dAcPtlLHH0zIj6iBJrrR7YAEG9hZdFMqaNadO66t3yOInQbn6Gzn3GZm1XwMoXfWUzJiKK+EF4h4V32sBC4vJ4k9JSuwErBARg+8xSJCdgiC9ybD6ShFElzHiDt5CDNJ1JvrEnhZ6yByrsbE7xdWZ6HQFWVTWz7Uy016Zaa/MtCozqbJ+orJ+emXUkBaqirSaW8BQnmfAKd+LGTCCqJILPcrOayLmjdBv5XJJr5ReWiqgwB/qoa+99NMGU+vCdl0M/1NePNdsBit8i1hzuL07DiI3u/nXc2x/Lq0V7AsFGzZVEPYsdAgcNLvvTmbH42Z/VoospUetYo9tPmP2WJhCs3l5CjKgPnpjrmmrGhP1QzMWQlAIbQhr4sfEnsJkNlkiL7p+AKUXgFIPgcG/iwTjjAu9AYxKjF4CEbhHkD6oFqdYqqv5zOBEHXSL4cnna+ModEEEzD0n7JATdkiIPFhaynAhZ0Uwfgvr1HIzsHv6MnaJYR+h0Mke8NlkYDYsZt7xBAx7un4PhKNhf/23YtiXpuyrYa+NmIhJPUoGFf258+iWjLiHOAsmtrlsIy63aZsyutDT7lu8PiM2Kq/qOKkkDEJvr4LEeIc3L+jK3PE4y7kfgTmGwMyVYHIATBOsLa37IbR33pw4vWwjw3Yv70ZyHvUo1XwHXB0/x85AyUcZTm12hwfb9s314xssrB+fYDGnu7eHxZuE9Ejf3OTy5cGiBvA3mGLu5VnllKj+TLf6ieBcST4Gw0wp59W9FR+yaJyFFAvDTTMKkCuxMBw4QEzCS1r26rA2UAa2svq24fxLwtzORPB6VnMOp5bqn/9m/INkdwkXVw/gICuo4hFkctlCt6hbKxoZQm15AfH0vPvIIuW7+9gihe78NrtgOP5pPvtg9PPqAWVnNAu/UvArHb9SxVesPfBB2i90wy9xe7adpid75R7B0bJjPpWMskTj523D89mazI2bX/aj9rkfCPoqWZ2eK/MvvJufB8t42lKC88MCfMnreGn/+41QrTwNf8yHYrX2S144kENYnG9HHfIZEQkj8dJytAU5BxgeO4xujx/K78MpA5yIMsDJDdnfXfJ08AthdC+d1ur0y22AvukNpPs2N3zf1jneY7uc4z2QYLwHxHh/1HW8+xdex0a5x95DYz71b3XG/Gk05o/lMX+0y5jvHzucAM15pzY+8lsUXNo=
*/