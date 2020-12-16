// (C) Copyright 2008 CodeRage, LLC (turkanis at coderage dot com)
// (C) Copyright 2005-2007 Jonathan Turkanis
// (C) Copyright Jonathan Graehl 2004.
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt.)

// See http://www.boost.org/libs/iostreams for documentation.

// Used by mapped_file.cpp.

#ifndef BOOST_IOSTREAMS_DETAIL_SYSTEM_FAILURE_HPP_INCLUDED
#define BOOST_IOSTREAMS_DETAIL_SYSTEM_FAILURE_HPP_INCLUDED

#if defined(_MSC_VER)
# pragma once
#endif

#include <cstring>
#include <string>
#include <boost/config.hpp>
#include <boost/throw_exception.hpp>
#include <boost/iostreams/detail/config/windows_posix.hpp>
#include <boost/iostreams/detail/ios.hpp>  // failure.

#if defined(BOOST_NO_STDC_NAMESPACE) && !defined(__LIBCOMO__)
namespace std { using ::strlen; }
#endif

#ifdef BOOST_IOSTREAMS_WINDOWS
# define WIN32_LEAN_AND_MEAN  // Exclude rarely-used stuff from Windows headers
# include <windows.h>
#else
# include <errno.h>
# include <string.h>
#endif

namespace boost { namespace iostreams { namespace detail {

inline BOOST_IOSTREAMS_FAILURE system_failure(const char* msg)
{
    std::string result;
#ifdef BOOST_IOSTREAMS_WINDOWS
    DWORD err;
    LPVOID lpMsgBuf;
    if ( (err = ::GetLastError()) != NO_ERROR &&
         ::FormatMessageA( FORMAT_MESSAGE_ALLOCATE_BUFFER |
                           FORMAT_MESSAGE_FROM_SYSTEM,
                           NULL,
                           err,
                           MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
                           (LPSTR) &lpMsgBuf,
                           0,
                           NULL ) != 0 )
    {
        result.reserve(std::strlen(msg) + 2 + std::strlen((LPSTR)lpMsgBuf));
        result.append(msg);
        result.append(": ");
        result.append((LPSTR) lpMsgBuf);
        ::LocalFree(lpMsgBuf);
    } else {
        result += msg;
    }
#else
    const char* system_msg = errno ? strerror(errno) : "";
    result.reserve(std::strlen(msg) + 2 + std::strlen(system_msg));
    result.append(msg);
    result.append(": ");
    result.append(system_msg);
#endif
    return BOOST_IOSTREAMS_FAILURE(result);
}

inline BOOST_IOSTREAMS_FAILURE system_failure(const std::string& msg)
{ return system_failure(msg.c_str()); }

inline void throw_system_failure(const char* msg)
{ boost::throw_exception(system_failure(msg)); }

inline void throw_system_failure(const std::string& msg)
{ boost::throw_exception(system_failure(msg)); }

} } } // End namespaces detail, iostreams, boost.

#endif // #ifndef BOOST_IOSTREAMS_DETAIL_SYSTEM_FAILURE_HPP_INCLUDED

/* system_failure.hpp
VvgSfAe+DN+Hr8J94n+/qv/yDiTvk3WwHZIga35GoZcCR8PeMB8OhT+AF8Ii+EM4Gc6EJXApvAzeAWfD++EcuAXOhW/CBXAnvBx+ABfCL+AiGM+1fwzTYRX/WsLFMBtOgcfBlbAdnAT7y+/B8Ap4GlwCz4Cz4Ti4HE6B18ASuAJeBq+Fc+B1kPdobTtrtX5+xI+UdxqCvjpukPawSsr7V5JPP4Ut5XcWvBl2gT+Xcv8FHARvk/p3OzwProdF8A5pJxvgEgnnStFb7rJRlhd4DpN6WOfZx7NL4veuxOM9l7+qBvx9IP72ir99Ln/rGvC3Tfz9Tfy94fK3uQF/b4u/HeKvFo6J99vQGoqEs5GFfayo1hB9E+xfmWxfsebomNi/Yk3SYW1gGexfmdYqRWT3qrE2ryK1d/UFkjDs22vj6ljbtzplCfafkIXIWuQRZBtyCMlcypq7pbF1VbEjdsSO2BHN8fXN/1dMLJziLAA48vn/x7It/f2rVfIcfxpiI0OQLF6Ihv5Tfw+da58/bOQZw4edOaGIXQCVxXkTygaVzJysxlFGZKtxlEHhxlwIR4+5fNTV0SIZrrnYUer8ACvX9X2Ux7P9L5HlGaHjLQlhxluceLSSeLi/71UZJ8qSvmFIG9JX3XD6yHb/HGqTtg2nr/ow6Vutzg+22kWfvrPd6SMexvT1jNe2ttWRi+SQvroG0jehqLi8UsbMivzfd++fN9iYPsIJHgd7m5eXzVHYZ3DCbyXhu+O9yxDv44l3+0/CxxuUWhLvNSreOJjLhXCC4/3XKONN+MSb8CW/z5Z4+5r4lR+XfQ6PIe2Id35D8VbVaULxTNWo3d9oKZtYPGFmySRXfblAhTOJ+TPblC65ju2asy0rrKgwjmFqXbme6Ib53qcn7Pb+uZvC0krj9/m9YYtufdiZLv1Md9hav6SS7kjpZrt0s4N1df9Cf6N0c126uZ54fNcpIZWnRSVlU+vndycqna66PVuE556vX6HOX2F1pqSnIx2tc9P3UD/zKOA/ohA/MWVKUpyvVUJSUvzJ/JGYapnactg+4CEV/gX0rTahj05vi1+Ctqrxcz7+n5AwHPlTBPNEwd/AkTqkx5llblDqRVbQXJEuf/0dHMoZd1XOSjdT60p5im62dlflptxyXf0u5RP0fbMEiXSmRLwl0sm5rxwwtZMpxZV5EworK8tVHtaRh7bkofGecsBb9xyvKhOM7UD09Vzck1H0A8SF9BEX7zyrvqanX5N0t0MCdsK7kO6C8OlWmYeaN+26/hQrv23IS3OfUBDID+ptMtffiDxFGn3N69PME4Oqe5HeT93pdqdvY9PQ9PVw7qfh0ic304bS95OG0ydhu9MS+XNBuHRUNgtNx3dIx+bw6agonFxc0VA6njpMOjYfxXQE2ll2il+5iXhKQnp1Qz98OirnlxVH1M78YdiNaivuOCb75DsfktcjkJOIo/VpmDj2Vk8oYfM5UfkbEjafCVe3h1zy5xEkXHuQfpzf/mebp7OPvEwOGdLbx+kDwqeXB40G2v9h0lvgSq+Pa2/0RZbevx5heocHylfm4AdJegciXZ22FC69EwhD7llh25Ly28c6wZxmwg5+nuCe69RrvcboeXW+PfNMcSpfviBPnkwNny9Hs03WSH60EE/NJT/SDobLD5UXEbXJtIOH70Ncx9nG+Hrm2je0CL1X9yW+eUHxJZ7qFh1ZPPMORnePzjt47O/RgfSuTQv9Dn9/5xm+Pr2DXMmN6D03P8r0ir5+P/lzdnRp1u+7YdP8/73G4Ga1xqBwY+fj3ur65TW588vzi25dvz+2xuCbusbgU3mf41B9dJ2MRf1R/l6E+L8dJGNKMmZV5/k=
*/