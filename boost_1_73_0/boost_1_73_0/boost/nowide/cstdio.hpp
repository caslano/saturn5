//
//  Copyright (c) 2012 Artyom Beilis (Tonkikh)
//  Copyright (c) 2020 Alexander Grund
//
//  Distributed under the Boost Software License, Version 1.0. (See
//  accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//
#ifndef BOOST_NOWIDE_CSTDIO_HPP_INCLUDED
#define BOOST_NOWIDE_CSTDIO_HPP_INCLUDED

#include <boost/nowide/config.hpp>
#include <cstdio>

namespace boost {
namespace nowide {
#if !defined(BOOST_WINDOWS) && !defined(BOOST_NOWIDE_DOXYGEN)
    using std::fopen;
    using std::freopen;
    using std::remove;
    using std::rename;
#else

    ///
    /// \brief Same as freopen but file_name and mode are UTF-8 strings
    ///
    BOOST_NOWIDE_DECL FILE* freopen(const char* file_name, const char* mode, FILE* stream);
    ///
    /// \brief Same as fopen but file_name and mode are UTF-8 strings
    ///
    BOOST_NOWIDE_DECL FILE* fopen(const char* file_name, const char* mode);
    ///
    /// \brief Same as rename but old_name and new_name are UTF-8 strings
    ///
    BOOST_NOWIDE_DECL int rename(const char* old_name, const char* new_name);
    ///
    /// \brief Same as rename but name is UTF-8 string
    ///
    BOOST_NOWIDE_DECL int remove(const char* name);
#endif
    namespace detail {
        BOOST_NOWIDE_DECL FILE* wfopen(const wchar_t* filename, const wchar_t* mode);
    }
} // namespace nowide
} // namespace boost

#endif

/* cstdio.hpp
afbiBO40CN3JJPzd+c2fhFfOTSU4fu10MLkokdtdpkFF9ETbv0/gKOgF/DHDKKWEl7n1ZmaVhgdVQ5LnlMcW2hF7hgfs1MFjpy7gTnfFrNt74uhV814JnG16J9Qc6t1WNeY1BPcxxx/nCzg/OzuNBFeMl/SQH2Mb81cVoKfpu/GQVOHwNxvANh32x0GINxv0/hx812088f+Y27jvFsaHFKt3DRF3QTC+c50bd2JrMk35/Wlgw1kTjdl46Ds4qM+bHD+7kyt/6r7B01QWzMduZTKPhnxTfbvaGgHuJ17g3s5G14Hnj2xYbgqmaEPMBJMfQp4N1jfIXpU0G43c4Rv4eaNbHDVT709UwEoFX3VezLkmFXBVmarHcDbybj33pmP2XjXVDucV/zPAH6nMJNIex7v3oh4LlWt9bmtXOD4wy4LSEEWxqt3VevXIHwa1hTOkg3z0kP4fUEsDBAoAAAAIAC1nSlLn/+YHhgMAANEIAAAjAAkAY3VybC1tYXN0ZXIvdGVzdHMvbGlidGVzdC9saWIxNTI4LmNVVAUAAbZIJGCtVN9v2zYQfvdfcfVeZEOJ2jytcTdMSdTGrWcbsrLOQACClk4WB1kUSCqJsfR/35GSYw9J6zyUQUzy9H133/2QguHPWz0YwtHF3D+j
*/