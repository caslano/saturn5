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
yDDRLtWUaOaMpHW+qyY6eqIDI+vwLwgMLKhrV5MLn+eFSgtvFqqA3rbffG7H58pSolqPWlCJqDAgNT4C2AuIBW3RUpjt6Juxvw30WlKWxDSSNdhrOqQxj3upR/thXw5v42bGbA7tyTPpQ1cBF25teunWTVULjh+JO5NY+7fmGyZBSYLZD4migC2Fug9PfUACNKw3Ow0hlfl/Ljlnz67tiaJIZmRZ8ka0h3tGNudYuNnEVdkGH6kEEgXJLb4nxeN+fXi/RNd1vSvp4wrCp608F3dZbWgA6nQzaTo3Cq2Bxfd5bQV3QD4qHOmeC+MNFFXJGkgBNZLLkgbVFs9DVS6Kmu6AHgqixhYDVdGQeCidOBniTds8vdj18T0ApFOvP75t9F/Lvu1bNS3Viov86sb/K/TPMMIrIfS9SzgRiv4NSrxcRf7Z63Btu+eL/fNMzMXQypFFuStLeW29ayjIEZl9n36nHa84OSIUwcoEI5C9a7TAGFuXAfy04b7I5ldyWdK5UAS7N3Fwl84Kki2Qxas+7iQlYNxB/0GadYpR2bzlFHCU1jSyFqGa88nMSQ==
*/