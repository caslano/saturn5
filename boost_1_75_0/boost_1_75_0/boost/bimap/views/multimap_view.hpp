// Boost.Bimap
//
// Copyright (c) 2006-2007 Matias Capeletto
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

/// \file views/multimap_view.hpp
/// \brief View of a side of a bimap that is signature compatible with std::multimap.

#ifndef BOOST_BIMAP_VIEWS_MULTIMAP_VIEW_HPP
#define BOOST_BIMAP_VIEWS_MULTIMAP_VIEW_HPP

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/config.hpp>

#include <boost/bimap/container_adaptor/multimap_adaptor.hpp>
#include <boost/bimap/detail/non_unique_views_helper.hpp>
#include <boost/bimap/support/iterator_type_by.hpp>
#include <boost/bimap/detail/map_view_base.hpp>

namespace boost {
namespace bimaps {
namespace views {

/// \brief View of a side of a bimap that is signature compatible with std::multimap.
/**

This class uses container_adaptor and iterator_adaptor to wrapped a index of the
multi_index bimap core so it can be used as a std::multimap.

See also const_multimap_view.
                                                                                    **/

template< class Tag, class BimapType >
class multimap_view
:
    public BOOST_BIMAP_MAP_VIEW_CONTAINER_ADAPTOR(
        multimap_adaptor,
        Tag,BimapType,
        reverse_map_view_iterator,const_reverse_map_view_iterator
    ),
    public ::boost::bimaps::detail::
                map_view_base< multimap_view<Tag,BimapType>,Tag,BimapType >

{
    typedef BOOST_BIMAP_MAP_VIEW_CONTAINER_ADAPTOR(
        multimap_adaptor,
        Tag,BimapType,
        reverse_map_view_iterator,const_reverse_map_view_iterator

    ) base_;

    BOOST_BIMAP_MAP_VIEW_BASE_FRIEND(multimap_view,Tag,BimapType)

    public:

    typedef BOOST_DEDUCED_TYPENAME base_::value_type::info_type info_type;

    multimap_view(BOOST_DEDUCED_TYPENAME base_::base_type & c)
        : base_(c) {}

    BOOST_BIMAP_MAP_VIEW_RANGE_IMPLEMENTATION(base_)

    multimap_view & operator=(const multimap_view & v) 
    {
        this->base() = v.base();
        return *this;
    }

    BOOST_BIMAP_NON_UNIQUE_VIEW_INSERT_FUNCTIONS
};


} // namespace views

/*===========================================================================*/
#define BOOST_BIMAP_MAP_VIEW_EXTRA_TYPEDEF(MAP_VIEW,SIDE,TYPENAME)            \
typedef BOOST_DEDUCED_TYPENAME MAP_VIEW::TYPENAME                             \
    BOOST_PP_CAT(SIDE,BOOST_PP_CAT(_,TYPENAME));
/*===========================================================================*/

/*===========================================================================*/
#define BOOST_BIMAP_MAP_VIEW_EXTRA_TYPEDEFS_BODY(MAP_VIEW,SIDE)               \
    BOOST_BIMAP_MAP_VIEW_EXTRA_TYPEDEF(MAP_VIEW,SIDE,reverse_iterator)        \
    BOOST_BIMAP_MAP_VIEW_EXTRA_TYPEDEF(MAP_VIEW,SIDE,const_reverse_iterator)  \
    BOOST_BIMAP_MAP_VIEW_EXTRA_TYPEDEF(MAP_VIEW,SIDE,range_type)              \
    BOOST_BIMAP_MAP_VIEW_EXTRA_TYPEDEF(MAP_VIEW,SIDE,const_range_type)        \
    BOOST_BIMAP_MAP_VIEW_EXTRA_TYPEDEF(MAP_VIEW,SIDE,key_compare)
/*===========================================================================*/

namespace detail {

template< class Tag, class BimapType >
struct left_map_view_extra_typedefs< ::boost::bimaps::views::multimap_view<Tag,BimapType> >
{
    private: typedef ::boost::bimaps::views::multimap_view<Tag,BimapType> map_view_;
    public : BOOST_BIMAP_MAP_VIEW_EXTRA_TYPEDEFS_BODY(map_view_,left)
};

template< class Tag, class BimapType >
struct right_map_view_extra_typedefs< ::boost::bimaps::views::multimap_view<Tag,BimapType> >
{
    private: typedef ::boost::bimaps::views::multimap_view<Tag,BimapType> map_view_;
    public : BOOST_BIMAP_MAP_VIEW_EXTRA_TYPEDEFS_BODY(map_view_,right)
};

} // namespace detail

/*===========================================================================*/
#undef BOOST_BIMAP_MAP_VIEW_EXTRA_TYPEDEF
#undef BOOST_BIMAP_MAP_VIEW_EXTRA_TYPEDEFS_BODY
/*===========================================================================*/

} // namespace bimaps
} // namespace boost

#endif // BOOST_BIMAP_VIEWS_MAP_VIEW_HPP


/* multimap_view.hpp
qv1YDsYqyXH5XoF3xOCjILfPU4znP8PAvAcQ/DUd+Ow/nRyAL1ZGPUBn/4vPcfa/8g6ElsXKXw/g2f9igPeel1sF4G7jo3+zyyyaw84FWQDAgoEFAELwMobgfzbqIbjgFqw/Wqm43wiNvZcSNEYzNL6wEk/zo+E8mspEKfODyvz1ApWJ4jL3UZkoHMBnD0kLgCKyAMAi5S8YLAAGrmwaZk9eHmQBQOF6+NR5r8loATCrHY5t4hi0ANiLENr+NWkB0F+zAJCebGwB+4cvswUApakWAAL723uMISD+2c4WAEJoFH8GCwCXrwrB7RulMKqxBcBdvZuxAEgINBNAFqMIWVehAcANd+oO9IevVg0AhunTL1+tGgBcq0/vspoMAK4lAwD0n+RdBnQkbcZpgwGAwFcLIV1ZswbpA/yuXUubHWZFNQCYtwLhdS9RsXi9AUC8HoOeiJIGAMV8QA2zuKwDoVD11twANAAYvEI9Jq7tHsJhlApflMeI/RHPY/cufYH4kNVRmgHAV9xfMAD4tRcoFKQFABZpu4IsAJ7vzxYAmHpiBVX0QpTeAoB4rYx0JdVNFgCYd9hSPPmiWDt3gWmPd+xqnet3snyTx8J8PiTNnUHLr3qrQ6RjR18d/jjVAiBaswA4apNlYgwWAF/YVK4B5vGZUGkBQANnyyU8YlJcBTS0hbYgC4BM1QKASqkWAHjyAF4qNAuAVSVW1fha
*/