// Boost.Bimap
//
// Copyright (c) 2006-2007 Matias Capeletto
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

/// \file views/unordered_multimap_view.hpp
/// \brief View of a side of a bimap that is signature compatible with tr1::unordered_multimap.

#ifndef BOOST_BIMAP_VIEWS_UNOREDERED_MULTIMAP_VIEW_HPP
#define BOOST_BIMAP_VIEWS_UNOREDERED_MULTIMAP_VIEW_HPP

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/config.hpp>

#include <utility>

#include <boost/bimap/container_adaptor/unordered_multimap_adaptor.hpp>
#include <boost/bimap/detail/non_unique_views_helper.hpp>
#include <boost/bimap/support/iterator_type_by.hpp>
#include <boost/bimap/detail/map_view_base.hpp>

namespace boost {
namespace bimaps {
namespace views {

/// \brief View of a side of a bimap that is signature compatible with tr1::unordered_multimap.
/**

This class uses container_adaptor and iterator_adaptor to wrapped a index of the
multi_index bimap core so it can be used as a tr1::unordered_multimap.

See also const_unordered_multimap_view.
                                                                             **/

template< class Tag, class BimapType >
class unordered_multimap_view
:
    public BOOST_BIMAP_MAP_VIEW_CONTAINER_ADAPTOR(
        unordered_multimap_adaptor,
        Tag,BimapType,
        local_map_view_iterator,const_local_map_view_iterator
    ),

    public ::boost::bimaps::detail::map_view_base<
                unordered_multimap_view<Tag,BimapType>,Tag,BimapType >

{
    typedef BOOST_BIMAP_MAP_VIEW_CONTAINER_ADAPTOR(
        unordered_multimap_adaptor,
        Tag,BimapType,
        local_map_view_iterator,const_local_map_view_iterator

    ) base_;

    BOOST_BIMAP_MAP_VIEW_BASE_FRIEND(unordered_multimap_view,Tag,BimapType)

    public:

    typedef std::pair<
        BOOST_DEDUCED_TYPENAME base_::iterator,
        BOOST_DEDUCED_TYPENAME base_::iterator
    > range_type;

    typedef std::pair<
        BOOST_DEDUCED_TYPENAME base_::const_iterator,
        BOOST_DEDUCED_TYPENAME base_::const_iterator
    > const_range_type;

    typedef BOOST_DEDUCED_TYPENAME base_::value_type::info_type info_type;

    unordered_multimap_view(BOOST_DEDUCED_TYPENAME base_::base_type & c)
        : base_(c) {}

    BOOST_BIMAP_NON_UNIQUE_VIEW_INSERT_FUNCTIONS

    unordered_multimap_view & operator=(const unordered_multimap_view & v) 
    {
        this->base() = v.base();
        return *this;
    }
};


} // namespace views

/*===========================================================================*/
#define BOOST_BIMAP_MAP_VIEW_EXTRA_TYPEDEF(MAP_VIEW,SIDE,TYPENAME)            \
typedef BOOST_DEDUCED_TYPENAME MAP_VIEW::TYPENAME                             \
    BOOST_PP_CAT(SIDE,BOOST_PP_CAT(_,TYPENAME));
/*===========================================================================*/

/*===========================================================================*/
#define BOOST_BIMAP_MAP_VIEW_EXTRA_TYPEDEFS_BODY(MAP_VIEW,SIDE)               \
    BOOST_BIMAP_MAP_VIEW_EXTRA_TYPEDEF(MAP_VIEW,SIDE,local_iterator)          \
    BOOST_BIMAP_MAP_VIEW_EXTRA_TYPEDEF(MAP_VIEW,SIDE,const_local_iterator)    \
    BOOST_BIMAP_MAP_VIEW_EXTRA_TYPEDEF(MAP_VIEW,SIDE,range_type)              \
    BOOST_BIMAP_MAP_VIEW_EXTRA_TYPEDEF(MAP_VIEW,SIDE,const_range_type)        \
    BOOST_BIMAP_MAP_VIEW_EXTRA_TYPEDEF(MAP_VIEW,SIDE,hasher)                  \
    BOOST_BIMAP_MAP_VIEW_EXTRA_TYPEDEF(MAP_VIEW,SIDE,key_equal)
/*===========================================================================*/

namespace detail {

template< class Tag, class BimapType >
struct left_map_view_extra_typedefs< ::boost::bimaps::views::unordered_multimap_view<Tag,BimapType> >
{
    private: typedef ::boost::bimaps::views::unordered_multimap_view<Tag,BimapType> map_view_;
    public : BOOST_BIMAP_MAP_VIEW_EXTRA_TYPEDEFS_BODY(map_view_,left)
};

template< class Tag, class BimapType >
struct right_map_view_extra_typedefs< ::boost::bimaps::views::unordered_multimap_view<Tag,BimapType> >
{
    private: typedef ::boost::bimaps::views::unordered_multimap_view<Tag,BimapType> map_view_;
    public : BOOST_BIMAP_MAP_VIEW_EXTRA_TYPEDEFS_BODY(map_view_,right)
};

} // namespace detail

/*===========================================================================*/
#undef BOOST_BIMAP_MAP_VIEW_EXTRA_TYPEDEF
#undef BOOST_BIMAP_MAP_VIEW_EXTRA_TYPEDEFS_BODY
/*===========================================================================*/

} // namespace bimaps
} // namespace boost

#endif // BOOST_BIMAP_VIEWS_UNOREDERED_MULTIMAP_VIEW_HPP



/* unordered_multimap_view.hpp
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
*/