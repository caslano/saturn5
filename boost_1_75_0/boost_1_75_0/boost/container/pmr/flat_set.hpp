//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga 2015-2015. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/container for documentation.
//
//////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_CONTAINER_PMR_SET_HPP
#define BOOST_CONTAINER_PMR_SET_HPP

#if defined (_MSC_VER)
#  pragma once 
#endif

#include <boost/container/flat_set.hpp>
#include <boost/container/pmr/polymorphic_allocator.hpp>

namespace boost {
namespace container {
namespace pmr {

#if !defined(BOOST_NO_CXX11_TEMPLATE_ALIASES)

template <class Key
         ,class Compare = std::less<Key> >
using flat_set = boost::container::flat_set<Key, Compare, polymorphic_allocator<Key> >;

template <class Key
         ,class Compare = std::less<Key> >
using flat_multiset = boost::container::flat_multiset<Key, Compare, polymorphic_allocator<Key> >;

#endif

//! A portable metafunction to obtain a flat_set
//! that uses a polymorphic allocator
template <class Key
         ,class Compare = std::less<Key> >
struct flat_set_of
{
   typedef boost::container::flat_set<Key, Compare, polymorphic_allocator<Key> > type;
};

//! A portable metafunction to obtain a flat_multiset
//! that uses a polymorphic allocator
template <class Key
         ,class Compare = std::less<Key> >
struct flat_multiset_of
{
   typedef boost::container::flat_multiset<Key, Compare, polymorphic_allocator<Key> > type;
};

}  //namespace pmr {
}  //namespace container {
}  //namespace boost {

#endif   //BOOST_CONTAINER_PMR_SET_HPP

/* flat_set.hpp
poiToJACYmEODs2EoWECpD8nhShzY11zjScFiEoalJc3LIoZyOZfK8dznwj4D71+iZp+zdHKQrDO4//db2pPCZZqzOWLbbu3xKzoS4W5LFgGDHCrLrEKlVDgylt7jS6D8wrSOe2JPue+OlCXb6r6fx1MxmNarVaJX4IhAEdHRgWQNsglCASBFHY7bG1EY6dvIwCZT5p2O2R7q8nhUczRKCFLfbbk6+RV335KgeBuuy57rSRgiYQIQYbMW+wpE4H8viYuICcOnq0g33fQlS0wzwQDCZJEM52aE4MmU0WcSNJUGwIptNlbMR90URbRF4nzLs2jQ3m5Ks1ynLxSfqE+79sIbLGqOqBcWmWezMU12L75EYD5PgAZCD1m0I0AsZApOpxZ4AJcuA+gD/VegPNGqDXqOS87wWnzlfJ75N0VFxaBipi9MsRxTLfbLdUjMPr+6DghiQPChtHbhCy4mVY636zS4FSZjUShpN0K6HVCGo2A2Swxm4bOietQQs5cMa721SF0Qm5P0Mb7kNsVkFZScKoFlFcO5i9Z3GvSdsclAAAgAElEQVRNaSfinGg4g2ARm6CVtnYAGxSUCLsoyGwdFqWQCYGUPrczkklJYPGazsG9vhV+XV7feJerCbp47tfpRPw6iaP0+t5jP3FOPRFecJGXubQPYFYmBAFThFB5jH+d+O8WAS2AlS5AqAQCVdUAkQcCzVOe84R1CcAd
*/