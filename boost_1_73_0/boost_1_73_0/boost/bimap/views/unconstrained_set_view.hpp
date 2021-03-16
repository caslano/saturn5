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
eWNkxM/XbCrK/7byGUoP30C1ohb52/IO+a80dUgvqKYPI4kS83JruO02yhkpx4jRM0g15npdUv1leZgefSwevai2MK+w6XI8F6q7qQ6d6W6phyrr52Aar/+FPt6ppWbZg74s1TQHxd5UTF4HScfWdAhdt0tes9LHMyyKrVSOINC6DFuYaGj1AGiTqLaBsYnuVLwUB6QuttCqt15sGQUXbU7W9s8zzTzQkFJz1IZo7gr83cUuOn5U353lMndpUD4=
*/