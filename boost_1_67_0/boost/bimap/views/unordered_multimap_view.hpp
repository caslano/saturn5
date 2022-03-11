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
+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
*/