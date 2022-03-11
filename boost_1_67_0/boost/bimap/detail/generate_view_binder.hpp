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