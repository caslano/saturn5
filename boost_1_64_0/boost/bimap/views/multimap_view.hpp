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
CAYfY37UOxN7D9wY2KmlvRWHvX0hW3CkeZlXD4Dc/Yd1lSeZdyJIDL1oG7toY8fnaZY4uAJoEpfqOGWB3oj5BBAPh31CTEzT9pK4Wt5BYSnKvet9YvSXZ9KcbGYHA1VvbPZWiGF+HsZa5P99/vxE26ak9KMetk4GTrY99XYkpDNXw2GAXAG5t330eX9bxqL5PTMNVIQ0cwvErZt+WIMnmo3ED4c3agl6xp6S/0zryuAsgZF4kpxhCWeA8Yr+5gyAhLUIndstla7ryatNjdJTY3K6NQNYXxl6LsZ0c5JH4gkzCYz3W1Sbms+mK+XkGkE9mk/CVguqtTsc0BCVF/D5ri8Zyv0R7LIh0mCQ5CY2blYaOMbxc/nXpW3P0+JHJV/Fv1JSmJtC4cpUN4RmDh5SvTlbqun1gdBqLho5DBEuzHVy2R74W8ZTTMGDILR7zQ+xhEKg8eJnWjwf03DMRpl8Epe8GqWFtGDXOxsbjQdLMU1/byJhffrUI6G00bRe7de8DA+FjIOB0/nfLMehZOk2hy6J/cpzbC3oLDEyHNsUEjqgDVjSLZ7Qtth6Fg==
*/