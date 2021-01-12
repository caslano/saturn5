// Boost.Bimap
//
// Copyright (c) 2006-2007 Matias Capeletto
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

/// \file views/unconstrained_map_view.hpp
/// \brief Unconstrained view of a side of a bimap.

#ifndef BOOST_BIMAP_VIEWS_UNCONSTRAINED_MAP_VIEW_HPP
#define BOOST_BIMAP_VIEWS_UNCONSTRAINED_MAP_VIEW_HPP

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/config.hpp>

namespace boost {
namespace bimaps {
namespace views {

/// \brief Unconstrained view of a side of a bimap.

template< class Tag, class BimapType>
class unconstrained_map_view
{
    public:
    template< class T >
    unconstrained_map_view(const T &) {}

    typedef void iterator;
    typedef void const_iterator;
    typedef void reference;
    typedef void const_reference;
    typedef void info_type;
};

} // namespace views
} // namespace bimaps
} // namespace boost

#endif // BOOST_BIMAP_VIEWS_UNCONSTRAINED_MAP_VIEW_HPP


/* unconstrained_map_view.hpp
kayHMvzX1IIeKiP1kXl1JH5BqjppaqVOmJ9k9/fSWIpBXckO2HgDkvcb1h94KU+UA+FUDtLpOtbp56zTkazTrRAiXQehnAwciTKtd9PpgnC8sjYSD8cioboGNT8NL7Z0CQbhrs/1Nv10KJL8tZH59cJVl+u/hH6sMVSWpdAqi20MRZ4Il3kqXTzEuniv2DnWDGzjtK8yUGf53NVNF3LpIESryinzPp/zPpzQx5/OVowLEDkA
*/