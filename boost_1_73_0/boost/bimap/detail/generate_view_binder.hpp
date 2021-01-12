// Boost.Bimap
//
// Copyright (c) 2006-2007 Matias Capeletto
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

/// \file detail/generate_view_binder.hpp
/// \brief Define macros to help building the set type of definitions

#ifndef BOOST_BIMAP_DETAIL_GENERATE_VIEW_BINDER_HPP
#define BOOST_BIMAP_DETAIL_GENERATE_VIEW_BINDER_HPP

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/config.hpp>

#include <boost/multi_index/tag.hpp>

/*===========================================================================*/
#define BOOST_BIMAP_GENERATE_MAP_VIEW_BINDER(                                 \
                                                                              \
    MAP_VIEW_TYPE                                                             \
                                                                              \
)                                                                             \
                                                                              \
template< class Tag, class BimapType >                                        \
struct map_view_bind                                                          \
{                                                                             \
    typedef MAP_VIEW_TYPE                                                     \
    <                                                                         \
        Tag,                                                                  \
        BimapType                                                             \
                                                                              \
    > type;                                                                   \
};
/*===========================================================================*/


/*===========================================================================*/
#define BOOST_BIMAP_GENERATE_SET_VIEW_BINDER(                                 \
                                                                              \
    SET_VIEW_TYPE                                                             \
                                                                              \
)                                                                             \
                                                                              \
template< class IndexType >                                                   \
struct set_view_bind                                                          \
{                                                                             \
    typedef SET_VIEW_TYPE<IndexType> type;                                    \
};
/*===========================================================================*/


#endif // BOOST_BIMAP_DETAIL_GENERATE_VIEW_BINDER_HPP

/* generate_view_binder.hpp
wVfSjabQVGhD5/UXBtBpK4QRINwM8K2I5D4kNZFeYvbEkSjcD79+nhx3N156S/y/I1o7/S6U2lYQvLMxLPDiPjMiyI9Gkha/YG4gw9wLR4yy6sEJm+BNZ1ljrQ3WPusj6xhvH2JjpBb8QGBTpxnIPQm1kGMvJM151l5rf/gzZmr4eCNha7OcVbhSPzhh5nWOcSW7o9xxMIDP3Rc9w1/n7wkYQGQoN8ghBKGz8KOQKo5jG2AP
*/