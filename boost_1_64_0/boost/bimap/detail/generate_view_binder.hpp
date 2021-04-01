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
yKBMaEYuOSCeFQ4L44JRSCS+lui3GnH8ZCqJNkqAj4n9CEcs2X8tOHh42K+wRqFSjjuDEJv/A1OkZCR6ELyHrFOlVPG+5XszOeQKxtpAyYNnV0/+elUxWc3bj58fCVJbcVVyDmJG9noydPyYNMBgSwOodnmChvFoGMbdwqIGSGM29tT8eLoP93lHk/u2FJXkYCnggKALLgYjgwJDTvr9qGwG1+5baANEhj65Y1FgGOomnShdEHMEbNks2PtQ26ozX/X1wBuGdSxHmbPntvV9sL1pej+S93fZB4sJxCFas9GtbYcuV/ft97rZ7xYts4zuLLALxtRs3cJpvPibvmSHh7nbru1I1TFG9S76R5y6W2psam9n9bHSJpX9Dm2HVMHry9fS5BJuRcIBALxJJvpKequSYZ5nS96rn2YmEYES6PHISiHo+dn8zTa3zND2esaneolUbip/89b6aYPl2vQLHCyjlJw4hsq4JHU9lzeUYj7y13s7HfV8thpodVEf+swOM6sfEdDV9ts3MfagE4CjPfxBdo6U8yo+HH9z5z1E1uxSm0S6SfR99FVM6g==
*/