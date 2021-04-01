#ifndef BOOST_ARCHIVE_BINARY_WIARCHIVE_HPP
#define BOOST_ARCHIVE_BINARY_WIARCHIVE_HPP

// MS compatible compilers support #pragma once
#if defined(_MSC_VER)
# pragma once
#endif

/////////1/////////2/////////3/////////4/////////5/////////6/////////7/////////8
// binary_wiarchive.hpp

// (C) Copyright 2002 Robert Ramey - http://www.rrsd.com .
// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org for updates, documentation, and revision history.

#include <boost/config.hpp>
#ifdef BOOST_NO_STD_WSTREAMBUF
#error "wide char i/o not supported on this platform"
#else

#include <istream> // wistream
#include <boost/archive/binary_iarchive_impl.hpp>
#include <boost/archive/detail/register_archive.hpp>

namespace boost {
namespace archive {

class binary_wiarchive :
    public binary_iarchive_impl<
        binary_wiarchive, std::wistream::char_type, std::wistream::traits_type
    >
{
public:
    binary_wiarchive(std::wistream & is, unsigned int flags = 0) :
        binary_iarchive_impl<
            binary_wiarchive, std::wistream::char_type, std::wistream::traits_type
        >(is, flags)
    {}
    binary_wiarchive(std::wstreambuf & bsb, unsigned int flags = 0) :
        binary_iarchive_impl<
            binary_wiarchive, std::wistream::char_type, std::wistream::traits_type
        >(bsb, flags)
    {}
};

} // namespace archive
} // namespace boost

// required by export
BOOST_SERIALIZATION_REGISTER_ARCHIVE(boost::archive::binary_wiarchive)

#endif // BOOST_NO_STD_WSTREAMBUF
#endif // BOOST_ARCHIVE_BINARY_WIARCHIVE_HPP

/* binary_wiarchive.hpp
vbs+csX3pEY+8Z2i570lDNu1IsqHUlj41t41LsBQ4Uya1dHEMTLKq1lT6dHNVqqMdb7G6rLr31Sqigfalk/53yRelDN4l8mjbUUY/vm3DkxDMlmRz6Y5+Gxlaa2v2UFT7OQ5XEWQWsBbhWpZcxkifpiPZBgSSx0tA8KiQZuPI5vDCA/oCIHZu2lGmMTUVwGPURnVh+KMZJQnqxw/4SzOihuvAjrbnX3LAMBkmNgcGRo/LEAgH6Tnn6tqhaodiBI2kl8o6ptru6A9ySVTlrqRhaPMAbZOJEBtnntQ3Mzf4xn1L2qb3L01vvBRDZ8flMWkcwvNCu+p52dNsZzdDyxMtRFaQzU0y0+iqPZAb0GCEGoTRtyQyO5CZeeviYZCBaf/xVEaB45YngYqAmsoV+qYXO9+gmCGkV8EKCJ4ck5rlViaLx5mEo3b3hwM1sL3Kw7ml2knKIH80G4nDPu48+7mvgE5KBj3E8KQ/8t0vYBxTHfm0sIuci6oevJqlQ/DwgqTVBRxc3aOKFqOlKwZfWsGZ6+RhkeSlCcKp7f1CJH6HyMdgMcepbt8QM7kqg==
*/