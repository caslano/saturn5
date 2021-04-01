
#ifndef BOOST_MPL_MAP_AUX_EMPTY_IMPL_HPP_INCLUDED
#define BOOST_MPL_MAP_AUX_EMPTY_IMPL_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2003-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#include <boost/mpl/empty_fwd.hpp>
#include <boost/mpl/not.hpp>
#include <boost/mpl/map/aux_/tag.hpp>

namespace boost { namespace mpl {

template<>
struct empty_impl< aux::map_tag >
{
    template< typename Map > struct apply
        : not_< typename Map::size >
    {
    };
};

}}

#endif // BOOST_MPL_MAP_AUX_EMPTY_IMPL_HPP_INCLUDED

/* empty_impl.hpp
fQhzmPnC33JKgsye4PEfj/fqcwUKTH9vKe6AdRvP0dVGst4mmZAQnrrkivR2tzpWlUIqDRjHMvtVxNXp3ufV7azcO2+8V3SjiSm87pf7m2qOQMU1mUxk7qQ2K6THZsUA4zkCTInoGWvgrMUJCxoXmYg6kVCd5n5yn0QYYKcksMg37fNWBXdBOqUCxeXi5OCw0Z79ry8V8bB7qUTS2DgwWYyRz25vA83dDvR68B7IbjGq7YiTWnBw/u1vFNE1wpFCVnt8a/c9GSfmel/5aJkiKvXIHYa9O7IU+srAMvaiqN2vygjeXnMc+Te2NGstzJjhD6xAnLsQH7eOzVFgNlBdc099SCUl3sFAD7GmP1cuRI/8ElMdWCXMXluzEyqgo1uit/PKoqVe80YkLZVfsgnqNseE2DfDwRhOYksie/tXCa7KaSppO9mir7NL9nkctgVqwPmsw73ent3kGciutPR4FnrhL11o6Lz1ZOxCfbz+wcG7UjdhOIFKrwxiOwa2fK5hMlzzLtfs5jkNunh4+Bp/1xTdiCuPQmq4o7KI5T07Op+UZsCx3UsrY+Bb3w==
*/