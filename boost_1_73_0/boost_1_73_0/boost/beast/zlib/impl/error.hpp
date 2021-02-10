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
fI7OE7gIp9NwnFxCdALh+JK4vozGQzpvQUoa8L7WaEhZgyhrKTB3gv9vMJZEk+FoCofg+4HvMyaqTDY5Qqe7XOkFNc9u+TWaYBjFdJZlSa2Q3zA2ODkLT2N4cwj94Ul4Fh8f7pKVTM+PD/cYOxt9iol1QyPFrL1dZ3DSmeMP6Ha65/FxGsdnPW+vxwAc6k0LiybHY/Kn0yhKnsDGEPZfi5l+qC1RY0UN9FxgNByHfyiQRf7fOPKbVM1uWlPkFen06ctS1WJNuEFehEnydv+5+h231uX2jeI2Sz/dXlc1/cpv0XUNORibTKPTafh1WaWaW9PMjIUdb8fHe/Q63azA7DZdR/V6jHEpDyj2ycW2jjArFFygpHPBtnVXFabO4dQwCLVW15qXjDnWA9jxM7bV6Q7oH0RPd4I96CvoHEHn+7IoT7yMZRKpdxfLSSOXzjpgW33QJfTnvydD/56aKuVao7/e8cb3C1BLAwQKAAAACAAtZ0pS/A1DFfMHAABqFAAAJQAJAGN1cmwtbWFzdGVyL2RvY3MvZXhhbXBsZXMvbXVsdGktYXBwLmNVVAUAAbZIJGCtWG1v00oW/p5fcbZXQFLyyn7ZS0q1VUsu1e0mFS2q2AVZU3uczOJ4LI/dJAL++z5nZhzboVwWiSDq
*/