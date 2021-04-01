/*
 * Distributed under the Boost Software License, Version 1.0.(See accompanying
 * file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt.)
 *
 * See http://www.boost.org/libs/iostreams for documentation.

 * File:        boost/iostreams/detail/execute.hpp
 * Date:        Thu Dec 06 13:21:54 MST 2007
 * Copyright:   2007-2008 CodeRage, LLC
 * Author:      Jonathan Turkanis
 * Contact:     turkanis at coderage dot com
 *
 * Defines the preprocessor symbol BOOST_IOSTREAMS_HAS_DINKUMWARE_FPOS for
 * platforms that use the implementation of std::fpos from the Dinkumware
 * Standard Library.
 */

#ifndef BOOST_IOSTREAMS_DETAIL_CONFIG_FPOS_HPP_INCLUDED
#define BOOST_IOSTREAMS_DETAIL_CONFIG_FPOS_HPP_INCLUDED

#if defined(_MSC_VER)
# pragma once
#endif

#include <boost/config.hpp>

# if (defined(_YVALS) || defined(_CPPLIB_VER)) && !defined(__SGI_STL_PORT) && \
     !defined(_STLPORT_VERSION) && !defined(__QNX__) && !defined(_VX_CPU) && !defined(__VXWORKS__) \
     && !((defined(BOOST_MSVC) || defined(BOOST_CLANG)) && _MSVC_STL_VERSION >= 141)
     /**/

#include <boost/iostreams/detail/ios.hpp>

#  define BOOST_IOSTREAMS_HAS_DINKUMWARE_FPOS

#if !defined(_FPOSOFF)
#define BOOST_IOSTREAMS_FPOSOFF(fp) ((long long)(fp))
#else
#define BOOST_IOSTREAMS_FPOSOFF(fp) _FPOSOFF(fp)
#endif

# endif

#endif // #ifndef BOOST_IOSTREAMS_DETAIL_CONFIG_FPOS_HPP_INCLUDED

/* fpos.hpp
kss3ZdiV321Ux2YUx655p8K39ca7XA0Lc5LmkyGxmuuREd0HXe50Jyzq1gy2G/eT2HucUKk1EMYRol2mcya55SIgiM5eP+jTeYecSCASxksy5z6leFo9TL5UF4fykL5kTq4C0snrhcWZy3M3tYLSHsy5Ct1HjD+QhpLctxJyAkm5xG/TRKszG3h+zizQMmz6vhDDFQ8AZZc2OMbLOvOTRlvD85omYeG58qL0aaHR/PuRIrXKmdkGQ+Plg6F7NpPlJWMFaJRChnLTu+1AvHKI9zVFXOc14hpRZMNelA8wgEuuTcAWFTMOj+Y733RSXonGcUJi2FUtIWQgltOD2yP1oqj/XbqqUTAMIHCFOjbqtgjxO0TfWmZkhuVQCHpPPQn5S8NmruHv6lZ6piyhtiQAG1ie4dxT+QIZySZjNTCDFWhycRHkY6uQSUlMwxTYYv4gLlyew0AdyNaoGpnAM/G9GqrdgOo/OQWgAPDFuDQiFXnjwea/rrKCFrZsBUfGvNca5s75fYXKNofQ7EF92dsGaoQ030XSc4iWSD4qvoF04fceNkNazBOBPAgYGg==
*/