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
0rnkQLo2GEPKa65a2Lp6k+KK9J3oXdW+P9b0VjdRHk1R1TRBUKabK/OOQZkz+/kTMkmDXQeHykNKtFSK3MfygLnzv1dZnKTONAlqP0X6MN1tQ2PSn1mePYORhPBnlT0XilRKkVTsb6WzdyMQT/xlW2KkDe7yXJ9j2eT3b+C5FQZdL7makVKw7Aw3eWnFRvdmMAxfeIJlBytdH/waQYVP/LcxwP+Dbx42XLu6GxpW67XocmPN1CHUynjW2DQon7NlgK6/D2bXDnhAG9ltyGo6O3unf2TtJeWDcNQ863FdtArXTOCWS5Of0TTbfmFDNUkv1RPjbgQh9jaDGEKUcydXquDGKt2BgtkqSziMfDc3KPv+vdNQdn4coa3/jm+0a6bWtRGNcxBWGPjW8a4Im7soKKnSDtPzhtwErx83z+TrPAXXW0YB2uusn9+/ZgbZNg743DNSDRTb5DY0ufM7EFDtMITGEsos/OJF/ETMqL5LjJgej7EZr2waZ2/9LQ2fPLiZuvX9LNrTSIQJupkN4dg7KGfMQA0ifdW7aEGTsl1cGTHIbH3w4upJ9YVkEA==
*/