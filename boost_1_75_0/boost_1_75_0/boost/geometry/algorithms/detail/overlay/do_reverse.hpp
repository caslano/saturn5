// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2012 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2013 Adam Wulkiewicz, Lodz, Poland

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_ALGORITHMS_DETAIL_OVERLAY_DO_REVERSE_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DETAIL_OVERLAY_DO_REVERSE_HPP

#include <boost/geometry/core/point_order.hpp>

namespace boost { namespace geometry
{


#ifndef DOXYGEN_NO_DETAIL
namespace detail { namespace overlay
{

// Metafunction helper for intersection and union
template <order_selector Selector, bool Reverse = false>
struct do_reverse {};

template <>
struct do_reverse<clockwise, false> : boost::false_type {};

template <>
struct do_reverse<clockwise, true> : boost::true_type {};

template <>
struct do_reverse<counterclockwise, false> : boost::true_type {};

template <>
struct do_reverse<counterclockwise, true> : boost::false_type {};


}} // namespace detail::overlay
#endif // DOXYGEN_NO_DETAIL


}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_ALGORITHMS_DETAIL_OVERLAY_DO_REVERSE_HPP

/* do_reverse.hpp
QvXhJkKjV7cuakKnzTMXt3W1lizraqru+HFrY9PUlvowaiElmNnRuLiNxpxVv4hQ7O2m6a3tjbQ5USG0zOJFWsokQifE2GWaHm5qqmhtCNeHl6FbzDM6gdpvbYRi1bc1oV0k1cpwx4LixsZwU2cnQm8kaFlWd0TKgRbCd6VNDYtvuqkpXAkRoRnQN+ZrF3eFFnfR59d3hVvbb/oxQm+RFK9fBpTtIlKb4s5IvRaYNG91hx4BVirMORSkadB/IVqbsvr2RijfOlo/rU7F6Ak0FRq/izZBMbpeqIKeIH7AoxOuZ6lUdrSSAYLQXtoXvOZkIKFxYltnV7itqR3KOZKPC/LJj9FfEn4MfU4DqFQrDy3eG9H1QWNMpa2d9Q3wlg4DnvzU+ra2TvR3VNq0oKMxUoQJ0CPG8CK9D1n9oBwLY59BOVPN17R1NNS3Fbe1dSxA3+chMpJg3vMQ4U2Q8Pd4mPQyQq2kn0qmXg9zoZF0HAxddNTQZj9GvzWEZtaHQtBrkOPTZvDXtDbdcm0zbYOfJcxuXxT1ZBntiemt4c4ulhD6XFZ5PNP/H0+XSpEOcn/xlS4R5WYhUa7okLuiOUeO3LZC6ZAJOXLMlamwYm6zREmOYaLNMblmmMUwM9t+n+H3++P3z/r0eb1ez+v1/rwfetAf7PCn0GF2l2esh9Hol4uVdR5vUB1KlwdSLhedfQuCzfS+wzerqNrdbOaL
*/