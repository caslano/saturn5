//
// Copyright (c) 2016-2019 Vinnie Falco (vinnie dot falco at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/boostorg/beast
//

// This is a derivative work based on Zlib, copyright below:
/*
    Copyright (C) 1995-2013 Jean-loup Gailly and Mark Adler

    This software is provided 'as-is', without any express or implied
    warranty.  In no event will the authors be held liable for any damages
    arising from the use of this software.

    Permission is granted to anyone to use this software for any purpose,
    including commercial applications, and to alter it and redistribute it
    freely, subject to the following restrictions:

    1. The origin of this software must not be misrepresented; you must not
       claim that you wrote the original software. If you use this software
       in a product, an acknowledgment in the product documentation would be
       appreciated but is not required.
    2. Altered source versions must be plainly marked as such, and must not be
       misrepresented as being the original software.
    3. This notice may not be removed or altered from any source distribution.

    Jean-loup Gailly        Mark Adler
    jloup@gzip.org          madler@alumni.caltech.edu

    The data format used by the zlib library is described by RFCs (Request for
    Comments) 1950 to 1952 in the files http://tools.ietf.org/html/rfc1950
    (zlib format), rfc1951 (deflate format) and rfc1952 (gzip format).
*/

#ifndef BOOST_BEAST_ZLIB_IMPL_ERROR_HPP
#define BOOST_BEAST_ZLIB_IMPL_ERROR_HPP

namespace boost {
namespace system {
template<>
struct is_error_code_enum<::boost::beast::zlib::error>
{
    static bool const value = true;
};
} // system
} // boost

namespace boost {
namespace beast {
namespace zlib {

BOOST_BEAST_DECL
error_code
make_error_code(error ev);

} // zlib
} // beast
} // boost

#endif

/* error.hpp
iuVkNQC6yXkZJkvO1LOMgUq9oeVpR0Dek4THCjh71ZB8I+pP86loJA+l2muTKMR7GenCiZKBS9LMz2GeYJPeb3Lq8qrLawxyWqJdBlTCp/b0hqTCBN7miLxPwfHETZGXS3hRDq9CH1557mFKmL2CojBgNoYqlC4asUahbXTVQY9aOEWRIcyc3mjTMwPRReKSJ2VQUVkBO3jOiiQKRIEnst3L7XiqhzvI3AQ1Vq1MQhe2BHV9hMx/PoBa6kZZ4XmoEOryyGOCtDufwxYS7xM38vljK/kTaEJSJj8RZ3yiCGqoa5sYrPlL4uByLX6pXtbLwnojSaFcqH09LUnaKJDbamG0Bs67aGTLiLGUvRdr4KhDisMv8BED0JMrGb4LGXeWrbSzHRt+0vlBktWdyiGXOtYjK9XkkWVxNR+tu5pHktXVvDiGENlwv8Kw0GLfXJyF6h/YClbsWTiRfavKWA29uYwK1pfhyWl1mRk3Wvx+Vrhj/X6s/MiTK9rgR3gjPWHFOsm4lyK36NjmuqmIbZIloqkpx7k245qzVyCu8el4pc+Kjjg39fuf9lyG8gNixNu0Tx+JtYMi/PHp1YYdFOEP9jhB7rkMNn0ZdOP5WsIfZQb3XJaXvYbGPQtsY3LWmBHILagd30mK35uBPhXIWNXXTkHOmRc4tADwC0s1ZrJUg1AMsJ16meZ+BDwBZtewZBDgkiYQQNUZr7PZJSZz
*/