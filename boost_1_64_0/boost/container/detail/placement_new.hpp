#ifndef BOOST_CONTAINER_DETAIL_PLACEMENT_NEW_HPP
#define BOOST_CONTAINER_DETAIL_PLACEMENT_NEW_HPP
///////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga 2014-2015. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/container for documentation.
//
///////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_CONFIG_HPP
#  include <boost/config.hpp>
#endif

#if defined(BOOST_HAS_PRAGMA_ONCE)
#  pragma once
#endif

struct boost_container_new_t{};

//avoid including <new>
inline void *operator new(std::size_t, void *p, boost_container_new_t)
{  return p;  }

inline void operator delete(void *, void *, boost_container_new_t)
{}

#endif   //BOOST_CONTAINER_DETAIL_PLACEMENT_NEW_HPP

/* placement_new.hpp
m23cslENaP/pYZ+T4R6goecxFtIN9ZL/16UQu9Kl7YWT5RaqXv9By3cI6z+T2mZfnzUFB5xG1CgBHx3e+TtenLXe2rkxlI7BkvQjl6mfTvvkE7mfBSBvY4vGIRFEyXKqshi9Q/JcbPkCkG9HbmkvpFySzDSpzzmLV+4Hm7sXuCTtNaB4XQPGFqpmKwphMrfprPmoIW65ZTznu43VjCeqJiXpVytLOyNON596VP2fDeXp9NirchOkzdudkuiytC6LXnJxDf4QazuEss7lHsJY4uQYr8OhECD+TyvvoS3Cnw7bu10Mf10BYNWO21rbuMGVGYklrPLm9nHFmPvnGI/+R5g6zaiwM0hTkFe5gHCnG2qPENm/tIszzFCy44PaakduOEZTXe69B31vVMqEFNaqAOeho8KVufQqQlBJTVsbdMoVr1nSfxRJ3293HXv3Cy/iNSRfWo6/lHjsGrDUtKgCkv6+PIzqviPWyJduNDKwmhrBfcNFXSHSvKM+ihZV89SEOmZhU/MOTaPuKupBvsavBMaElKkD5rd08KlCKpFDHkedpJ1GC3Kx+kgYmg==
*/