// Boost.Bimap
//
// Copyright (c) 2006-2007 Matias Capeletto
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

/// \file views/unconstrained_set_view.hpp
/// \brief Unconstrained view of a bimap.

#ifndef BOOST_BIMAP_VIEWS_UNCONSTRAINED_SET_VIEW_HPP
#define BOOST_BIMAP_VIEWS_UNCONSTRAINED_SET_VIEW_HPP

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/config.hpp>

namespace boost {
namespace bimaps {
namespace views {

/// \brief Unconstrained view of a bimap.

template< class CoreIndex >
class unconstrained_set_view
{
    public:
    template< class T >
    unconstrained_set_view(const T &) {}

    typedef void iterator;
    typedef void const_iterator;
};

} // namespace views
} // namespace bimaps
} // namespace boost

#endif // BOOST_BIMAP_VIEWS_UNCONSTRAINED_SET_VIEW_HPP

/* unconstrained_set_view.hpp
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
*/