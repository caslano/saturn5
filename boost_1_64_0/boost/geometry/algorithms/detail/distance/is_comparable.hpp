// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2014, Oracle and/or its affiliates.

// Contributed and/or modified by Menelaos Karavelas, on behalf of Oracle

// Licensed under the Boost Software License version 1.0.
// http://www.boost.org/users/license.html

#ifndef BOOST_GEOMETRY_ALGORITHS_DETAIL_DISTANCE_IS_COMPARABLE_HPP
#define BOOST_GEOMETRY_ALGORITHS_DETAIL_DISTANCE_IS_COMPARABLE_HPP

#include <boost/type_traits/is_same.hpp>

#include <boost/geometry/strategies/distance.hpp>


namespace boost { namespace geometry
{

#ifndef DOXYGEN_NO_DETAIL
namespace detail { namespace distance
{


// metafunction to determine is a strategy is comparable or not
template <typename Strategy>
struct is_comparable
    : boost::is_same
        <
            Strategy,
            typename strategy::distance::services::comparable_type
              <
                  Strategy
              >::type
        >
{};


}} // namespace detail::distance
#endif // DOXYGEN_NO_DETAIL

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_ALGORITHS_DETAIL_DISTANCE_IS_COMPARABLE_HPP

/* is_comparable.hpp
mL0/T6UEJ8rHzb3kKhCs9jI/0bG9xMLdo7lZh2NMnSdzvANL2KKLvGU8yLlqKXEuQSWLru8gfWskLZR79nRitSKZJSnj2ZBfc6Js2tIrZdbDzzxYabvRzWyN5YXSJervvTNIi1dUGf6adlVnm9gOjxzGz5vmBJmgMhTXhGWf/+2Gmh8NBctrWe/Olw7JZIXecqA8L2PTFBlAqlOz+EWIe3Igc/KyiyRmMNNLdUvV94/n26gTsGk5PoA9CiwjLGm5XIqAJwWcbq8jvdSNpN+znWJA8lh1c2TpQFV4D+ZJQaxvvUTesoXtreAZSErTddmV4q/Kfq+KEHLj3j+mQKz08BiFEdFBlHPQUqafRQizZ+VorQYJjvK9eWKNbtZGTnmJ1Vayi7k9PUH+Ue29+EUoUVg79pGEUS/wvX9JkukKIm3uNthjMiBQw1XSyo0LIsi6dyzg1G/JZfE/BmtZYMgooiaTIEbJ72WOp+iosf2JMp4EyzmUSqZY7sUPFM3Jcv/v8d0OoKH+Dja5iKZboMWjMR/ioCRRJk2mdtcM9J6gB43GPJAVIj1QQROUNA==
*/