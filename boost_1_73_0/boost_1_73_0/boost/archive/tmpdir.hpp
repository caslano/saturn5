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
J3L0DvIUFSag8WN8ENFstJOwWdG2jdHcTtxiUZMGeXApwSY91n7P47x8vazBRINun3TBIZUwnU8a0eDkQBNkdOl7O5x8hhDNFo1PmoNPOtGcIdJHPXr9FCefg4jmO1Eqz2Xnk0E0qMSxp3ZO+UPcyWco0YzT6pPh4DOMaCYKPr/48YlbnHwOJppcjc8wB5/hRn1mbnrtVCefEQ4+wx18Mg0+D057fL2TT5aDT6aDT7bB5/qqSUEnn5FEM1Hjk+0=
*/