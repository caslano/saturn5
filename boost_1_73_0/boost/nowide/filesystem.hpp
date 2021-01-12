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
2MvUYk3sQ9AvR6gNNLFICk6z/hwI+nOg+binAcsGMfNAXRYDKwFWOdB8v14NytWCchtAuY0DxTrS8N5a80DzPKB9oHke98ZA8zzgY2DWQebbGzbIvFzqIPNcJnuQ+dp7MTDPIPM84FpQzztBzHZQzxdB+96h5jLrT2B/A9tzxZ48twjhP/l7nFkPK2Y3sVD+M58Z/e95xTwWds6h0Rz01ocaIRZynP5hv+2ib+aHn3jMKh7b
*/