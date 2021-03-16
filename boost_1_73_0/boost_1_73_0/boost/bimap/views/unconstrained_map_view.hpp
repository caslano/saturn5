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
tEp8FFcLyuIfyarC28VGvq+/ukUFXE3O0dGtNhV0h0kYFXO0c4NscidvxBI7Ckf0LuuO/NPN5o3RRI3cRC19talti9zSVbSyjq5U+QDJW8gjeeP2ALn7IC13aylbb8n3MTK8Juv4yIjXywLNGyIj3pv7fVMAEF5CLbBE2olaEPpQnJgR6ba0L4MWKp0qWT49pam6wHlc52FRKcqK+V7+7sLEpyiPYc4jU3kkHxnlkf9WYYKW2Th/hSPWlx3p5K8=
*/