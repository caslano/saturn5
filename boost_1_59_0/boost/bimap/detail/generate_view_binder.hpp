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
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
*/