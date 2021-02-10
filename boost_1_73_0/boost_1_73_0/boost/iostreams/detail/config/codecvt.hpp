// (C) Copyright 2008 CodeRage, LLC (turkanis at coderage dot com)
// (C) Copyright 2003-2007 Jonathan Turkanis
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt.)

// See http://www.boost.org/libs/iostreams for documentation.

#ifndef BOOST_IOSTREAMS_DETAIL_CONFIG_CODECVT_HPP_INCLUDED
#define BOOST_IOSTREAMS_DETAIL_CONFIG_CODECVT_HPP_INCLUDED

#include <boost/config.hpp>
#include <boost/detail/workaround.hpp>
#include <boost/iostreams/detail/config/wide_streams.hpp>
#include <cstddef>

#if defined(_MSC_VER)
# pragma once
#endif       

//------------------Support for codecvt with user-defined state types---------//

#if defined(__MSL_CPP__) || defined(__LIBCOMO__) || \
    BOOST_WORKAROUND(_STLPORT_VERSION, <= 0x450) || \
    defined(_LIBCPP_VERSION) \
    /**/
# define BOOST_IOSTREAMS_NO_PRIMARY_CODECVT_DEFINITION
#endif

#if defined(__GLIBCPP__) || defined(__GLIBCXX__) || \
    BOOST_WORKAROUND(_STLPORT_VERSION, > 0x450) \
    /**/
# define BOOST_IOSTREAMS_EMPTY_PRIMARY_CODECVT_DEFINITION
#endif

//------------------Check for codecvt ctor taking a reference count-----------//

#if BOOST_WORKAROUND(__MWERKS__, BOOST_TESTED_AT(0x3205)) || \
    BOOST_WORKAROUND(_STLPORT_VERSION, < 0x461) \
    /**/
# define BOOST_IOSTREAMS_NO_CODECVT_CTOR_FROM_SIZE_T
#endif

//------------------Normalize codecvt::length---------------------------------//

#if !defined(__MSL_CPP__) && !defined(__LIBCOMO__) && !defined(__clang__) && \
    (!defined(BOOST_RWSTD_VER) || BOOST_RWSTD_VER < 0x04010300) && \
    (!defined(__MACH__) || !defined(__INTEL_COMPILER))
    /**/
# define BOOST_IOSTREAMS_CODECVT_CV_QUALIFIER const
#else
# define BOOST_IOSTREAMS_CODECVT_CV_QUALIFIER
#endif

//------------------Check for codecvt::max_length-----------------------------//

#if BOOST_WORKAROUND(_STLPORT_VERSION, < 0x461)
# define BOOST_IOSTREAMS_NO_CODECVT_MAX_LENGTH
#endif
                    
//------------------Put mbstate_t and codecvt in std--------------------------//

#ifndef BOOST_IOSTREAMS_NO_LOCALE
# include <locale>
#endif

// From Robert Ramey's version of utf8_codecvt_facet.
namespace std { 

#if defined(__LIBCOMO__)
    using ::mbstate_t;
#elif defined(BOOST_DINKUMWARE_STDLIB) && !defined(__BORLANDC__)
    using ::mbstate_t;
#elif defined(__SGI_STL_PORT)
#elif defined(BOOST_NO_STDC_NAMESPACE)
    using ::codecvt;
    using ::mbstate_t;
#endif

} // End namespace std.

#endif // #ifndef BOOST_IOSTREAMS_DETAIL_CONFIG_CODECVT_HPP_INCLUDED

/* codecvt.hpp
LuPE63XDPh3QU29cr3T54DoYNe+hxrwCnv1ySacy6b0Y0M7jbriDifdrp55SUzTZnJ6fnLw7oR1YuptbZmiYJjulMOZEWO89fvGkX/nAHx+jUzpev1onYLDrNWtVyBRiYhFNHRIwkstYJuXZZ7ht8WBxJUVm1sIq7LHC/xH6Ju01wni7Nw3KH1e1PVr7Wgv2zqbB+ZcH1313vs1nQy/Mgp6uNQ9uYSHrFB08oe5ocAuV026p/HAbg49tBh0ngFzBrQH09G/nCypFN4jX4xtL5fbu7W1Srjs3n+zUoJe2Ga4vARlGoNH+vvV+I+F7ezYQesLk7ZRFwuTjLRPltx9pI3sv+iU1kznG58rHcee6RLFFwg0Y430byaFNaQ3cZnsOev2b8K5ro1I1LisHkdwpWdoxlEjfsZyPRo8oVoZn0RYuM5HM5Rr2rVjuj6to1w6gJ+IqUYLDXg3CbX/ZO5zM9KXbnX1hxmvy45S6XVG+Xbd4x3WLUGFzT8PNwd5+FB/uwpgCo15ptgSlvZLxUx3zb3zKc20Vhob4NyQb62+2Fj7T2ZvDk6MP5247J5tx9CLtC5xpsezxV79/9s9z2sP1dH9/3NpuGRnZ0oGuikMLF0UUtDkY8TldDga0zDTyqxKMoSKqfWcUZkXi266b
*/