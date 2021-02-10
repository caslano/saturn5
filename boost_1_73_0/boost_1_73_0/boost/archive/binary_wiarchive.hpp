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
0OWc8xcwRs/kGYXPxrrwkVmhZLoRK2kxDVf8u8fqMB7uWsyveNw4BC4uTFolLSMgoqeVzlKyRsTxUOU0+5vOcWPL08Ymk4W22K8Ot6Fb9VKEExzFA2cNMhaYpm2q1kGP4hM/rO0Fdt/oaTxxYDv3YPuspgUj6vgymA7b9Ft/uGj/YRBFD7JIgJDO+KHf0MEDzAI+LHXC3Ib9Ji1/2cysYfB5AUhN9XyuihiGANL8fRK5klMQSwmctLxOljfASSTniCBEuoUXUkfYcLywKjEEVBrr+ZWmLGWqYgBMuFMP+xyp5y6zHHcQEot9OmegprwiJ9AGs8IsPeTUizaV5V0cKTwj6uKDKNr/NQ8JAt5mAgsXlsRgK5lviPAzDLimva9NAdewgXCCObgO4KOL/DqOygKnXsriOTA432rvGmG9Rx89ICcMzvkihGOQWthhIVOXizyKo9bStBBdO8ZgkRoiIzGVyTNFRo25Orj8TTdKFiHdIPU6e70ombmLYsSygl3p5gXZYTy+fyt4V2bNZ5hueHmMUrhDpsEuxQYAcXF06dkYCRZ0AnIFiOhE7CwimULZxVLJMqa8i9yUlAaHvmwyrnNrfFETOoGDU7GPSrY3LWnMs1bhqIcRT6QD50ZkBugpmjgHs+FXWuXL6B6H
*/