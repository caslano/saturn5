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
0rYjkYz1WJQnr6f6FqjvXOe9RPI7US6REoyUfBeammNDSVjRB1sFnp4kQ4q5yxnVIA8IWMvPWSiVXsD6DF2Ru8qdfImx/1P5MgEu952lS3jRTwFSRHacxYSlhUBLXqA9UR0fTcUvv7WAn8vzQ0/m8ZP54kmZobUyQ2uBwYVK5gw8AganGt1UkryhzAKocYwif6FK+QkUjvotFM/G/xze0GVYHddjXCHsvVmh98LqFoi6odwFwhz3qmENXWFI88l+S7c3zP8xpXFQz2dw7MrQR01hAYgmT2mNA8yLu9jWIN8Y17NhXLK5uWGBhvQ4GSEbzfNeY2SrVLT3PqENYYQ78AytpNwewbevbuzT/WaK2pmgvDDNZDIaVS7DNQm2XUYRIzr/jUnxjp1mU3iIMeO8+y4S65ZTWq6VuaqQaBTl6BCm1854AqOz2F8sD60VcSioopaH6pNQIEJd5Zt0X5BzRcZ1ycd18T2ebyqaAdxiIWsiHp1Cbt9D88n1bTYH8MmC03Q2+sNT+L7Zc/kKZnm27gsnzy7h0mR59iy+SsyShz6WJQ8qJoWGS701nQJnDQtFzlcd04vYkJu6N6FIA4Zco516KJBWAU5l2XcsOBbkXyGFhD8yVs9bpsdle3xIS7kvj01uCKPyyzivsPgDlLPrhO4Ea26d3BoYPfYtr3BYOLbkMY3t2w3x2PblhHroko9l41EAZx9nG3D7xtWa
*/