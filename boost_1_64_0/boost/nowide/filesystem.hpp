//
//  Copyright (c) 2012 Artyom Beilis (Tonkikh)
//
//  Distributed under the Boost Software License, Version 1.0. (See
//  accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//
#ifndef BOOST_NOWIDE_INTEGRATION_FILESYSTEM_HPP_INCLUDED
#define BOOST_NOWIDE_INTEGRATION_FILESYSTEM_HPP_INCLUDED

#if(defined(__GNUC__) && __GNUC__ < 5)
#pragma GCC diagnostic ignored "-Wunused-parameter"
#endif
#include <boost/nowide/utf8_codecvt.hpp>
#include <boost/filesystem/path.hpp>
namespace boost {
namespace nowide {
    ///
    /// Install utf8_codecvt facet into  boost::filesystem::path such all char strings are interpreted as utf-8 strings
    ///
    inline std::locale nowide_filesystem()
    {
        std::locale tmp = std::locale(std::locale(), new boost::nowide::utf8_codecvt<wchar_t>());
        return boost::filesystem::path::imbue(tmp);
    }
} // namespace nowide
} // namespace boost

#endif

/* filesystem.hpp
tJhZefTrPfD0DAhI7iAXC71ufoxIxWnR72/jZvKP3RufkUPFBn5mC5IdEzBEvQjinW5zc+GAFinFOv3EysN8ZBd7c2zR1TmCWvZ7ktS2K4pgyvktNrRrCCGLRBj6HMtlmIuDIm1j9dJNkGjOC1fhaMOATXFXskLfWgB9P98YOqba6wgfAY+rp4jQ5WuKD8ZpWBo0nMCoftMbabhptquoj77BZY1yt4hAST2IuA7C0eVjeOD6g0UldJykDi9/M8TCUNb91jSWIDCMO+W17bHPQoHBbtVSp8b42+0YhrvqLm/0VUEPNvuDgGWNSWLOpHCvcwMOme8bxIXBiZkoRSJ1bu3FQ5oi13bwvZ5HLlooeNBBcynGDbtkVIJ5IuBsFHn1CjeFiF2Dhcy/Agmqz8agDxKIChw8lfz36oMuSrSCB54S3qOtl4y5vXyy8ERfKgksnO3TjvpDmDGSynDNemAeYyU/YuzWt2GfDVXu56dK3IXrg543EmxFJ7r2Lvl03vjimoWLBaAzAA5ZJykTlu4+nDotYbhtvHktzmQyyC/a1Ck5a0JxBeFTVyZziA==
*/