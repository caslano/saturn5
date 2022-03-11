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
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
*/