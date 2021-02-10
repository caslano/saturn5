// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2014, Oracle and/or its affiliates.

// Contributed and/or modified by Menelaos Karavelas, on behalf of Oracle

// Licensed under the Boost Software License version 1.0.
// http://www.boost.org/users/license.html

#ifndef BOOST_GEOMETRY_ITERATORS_DISPATCH_POINT_ITERATOR_HPP
#define BOOST_GEOMETRY_ITERATORS_DISPATCH_POINT_ITERATOR_HPP

#include <boost/geometry/core/tag.hpp>
#include <boost/geometry/algorithms/not_implemented.hpp>

namespace boost { namespace geometry
{


#ifndef DOXYGEN_NO_DISPATCH
namespace dispatch
{


// dispatch for points_begin
template <typename Geometry, typename Tag = typename tag<Geometry>::type>
struct points_begin
    : not_implemented<Geometry>
{};



// dispatch for points_end
template <typename Geometry, typename Tag = typename tag<Geometry>::type>
struct points_end
    : not_implemented<Geometry>
{};



} // namespace dispatch
#endif // DOXYGEN_NO_DISPATCH


}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_ITERATORS_DISPATCH_POINT_ITERATOR_HPP

/* point_iterator.hpp
KiwRQWNXA+0BKj7c9opiJIDhalucZHviMiu54EBKSERP1XUuAn0KAFgMnI4u3oswR4UhJg0VRwHTrhCbmHs9PISoATqAOh5jLwxNFwqSA7jX3DRHVuGMYktK3QuKSs2ITW/5qXCtCavtHAxOCCksWoZgGvNVuXvgbRhAgQk1S7FQGr8p8E3AT9O7UqoA43IpU+MP+h0+lUEiGcfRKqoBNPUfDwdNo+CHwU/D4MN4PLg+xwgEMBuiA+iVtAIr3sqE5oGFAxT8E/rbfK/m015ePkFo1t8xArdz/wiyChhx+eniwqacZxTjTMKJQkwtOBisxlSABk1m6TObql2wNx5engXD0ehqREStQ4LgpO+RxJqfP3DgbTgDI/JdFzXNmuzvbaWQWjTmklWbN3kDsbm9EKyT1tbZ/1p8Tfc74tXj1rHW4pKFr9vbVO6IvCy2R3iR3+B3k25c1kEB4IdQWWRBKstNVphcC9WYZYhIHh3smgGqTQAYU0ZFXLFO1TrCIAClOYvrgb03GjWXOIwRwbSB4evR1QQjrTXo+maIYc3/jgrJ39guh3/uefUj1Ne4A+OAtl6zm6m7kR35ljd5eXU5RKhsn7/h5xeD8YS42RZOk7ezjWCT0QAocKrzy/dXwQ/DwdlwhHiGBNLigNWu
*/