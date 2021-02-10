#ifndef BOOST_ARCHIVE_TMPDIR_HPP
#define BOOST_ARCHIVE_TMPDIR_HPP

// MS compatible compilers support #pragma once
#if defined(_MSC_VER)
# pragma once
#endif

/////////1/////////2/////////3/////////4/////////5/////////6/////////7/////////8
// tmpdir.hpp:

// (C) Copyright 2002 Robert Ramey - http://www.rrsd.com .
// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org for updates, documentation, and revision history.

#include <cstdlib> // getenv
#include <cstddef> // NULL
//#include <boost/assert.hpp>

#include <boost/config.hpp>
#ifdef BOOST_NO_STDC_NAMESPACE
namespace std {
    using ::getenv;
}
#endif

namespace boost {
namespace archive {

inline const char * tmpdir(){
    const char *dirname;
    dirname = std::getenv("TMP");
    if(NULL == dirname)
        dirname = std::getenv("TMPDIR");
    if(NULL == dirname)
        dirname = std::getenv("TEMP");
    if(NULL == dirname){
        //BOOST_ASSERT(false); // no temp directory found
        dirname = ".";
    }
    return dirname;
}

} // archive
} // boost

#endif // BOOST_ARCHIVE_TMPDIR_HPP

/* tmpdir.hpp
SroK2itvdhUgeE/qZrNpENSyg4I7YpuMtgPgf74FCgVQDKhgGEuwoKXHwObttLtj/5sxHxpW5Q07+QF2hJFS35a5MJq5SNNaa2WrIU5gIAkjClYqsgY5c9Ie343JgMJgKh5e/Ggpf9fEHI9ftmuWfIHd/4mlpdyQd3bdOqmy6kgIOorD8Kmfn0rYeoPt+oGEl04b9MYDE0NvSoO7XDh5SdLGUaosRsfT4+ec2nrk7foSh6r1XX+6gs+6c/XTxd3r9+/OLy/urk5v3vYCE5EzUbHI6tmTrsP9IZi+OZ+eXsxe7LEP8ogZSsX8aLjT3i504y9AV52cfx/c5njvLO2+hlF1NnjPWtFfc6+fJb5GGVVEj2grb5JumEPNmA9gj1GPyOAYuFDlzXTWMmnfPlH6HSSS10gyVVKBNo+QBjpoamEHjtbOOsOL3cWRCFsFM9HxP6v2r6X+tdT/x1J/WsS6dL6O2/Ks6+FfqGqom6Pe574yr4XQjPvG5JU21E7Q13uys9QpDUraZLUbyrAd68AZCLjJdG1DtalEbv32KXJHfCxQ33lEmcFqZGyJjh/dS51tPFskwndVhaVjw1tMHCNrYp8j7RypgK0oZ58dpMK3XKQTXbRRpjj1ub41No+F0yEHprdC2i7koz9REHWT
*/