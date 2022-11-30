// Boost.Bimap
//
// Copyright (c) 2006-2007 Matias Capeletto
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

/// \file views/list_map_view.hpp
/// \brief View of a side of a bimap.

#ifndef BOOST_BIMAP_VIEWS_LIST_MAP_VIEW_HPP
#define BOOST_BIMAP_VIEWS_LIST_MAP_VIEW_HPP

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/config.hpp>

#include <boost/bimap/container_adaptor/list_map_adaptor.hpp>
#include <boost/bimap/relation/support/pair_by.hpp>
#include <boost/bimap/support/iterator_type_by.hpp>
#include <boost/bimap/detail/map_view_base.hpp>
#include <boost/bimap/relation/support/data_extractor.hpp>
#include <boost/bimap/relation/detail/to_mutable_relation_functor.hpp>

namespace boost {
namespace bimaps {
namespace views {

#ifndef BOOST_BIMAP_DOXYGEN_WILL_NOT_PROCESS_THE_FOLLOWING_LINES

template< class Tag, class BimapType >
struct list_map_view_base
{
    typedef ::boost::bimaps::container_adaptor::list_map_adaptor
    <
        BOOST_DEDUCED_TYPENAME BimapType::core_type::
            BOOST_NESTED_TEMPLATE index<Tag>::type,
        ::boost::bimaps::detail::              map_view_iterator<Tag,BimapType>,
        ::boost::bimaps::detail::        const_map_view_iterator<Tag,BimapType>,
        ::boost::bimaps::detail::      reverse_map_view_iterator<Tag,BimapType>,
        ::boost::bimaps::detail::const_reverse_map_view_iterator<Tag,BimapType>,
        ::boost::bimaps::container_adaptor::support::iterator_facade_to_base
        <
            ::boost::bimaps::detail::      map_view_iterator<Tag,BimapType>,
            ::boost::bimaps::detail::const_map_view_iterator<Tag,BimapType>
            
        >,
        ::boost::mpl::na,
        ::boost::mpl::na,
        ::boost::bimaps::relation::detail::
            pair_to_relation_functor<Tag, BOOST_DEDUCED_TYPENAME BimapType::relation >,
        ::boost::bimaps::relation::support::
            get_pair_functor<Tag, BOOST_DEDUCED_TYPENAME BimapType::relation >,

        BOOST_DEDUCED_TYPENAME ::boost::bimaps::relation::support::data_extractor
        <
            Tag,
            BOOST_DEDUCED_TYPENAME BimapType::relation
            
        >::type

    > type;
};

#endif // BOOST_BIMAP_DOXYGEN_WILL_NOT_PROCESS_THE_FOLLOWING_LINES

/// \brief View of a side of a bimap.
/**

This class uses container_adaptor and iterator_adaptor to wrapped a index of the
multi_index bimap core.

See also const_list_map_view.
                                                                                    **/
template< class Tag, class BimapType >
class list_map_view
:
    public list_map_view_base<Tag,BimapType>::type,
    public ::boost::bimaps::detail::
            map_view_base< list_map_view<Tag,BimapType>,Tag,BimapType >

{
    typedef BOOST_DEDUCED_TYPENAME list_map_view_base<Tag,BimapType>::type base_;

    BOOST_BIMAP_MAP_VIEW_BASE_FRIEND(list_map_view,Tag,BimapType)

    public:

    typedef BOOST_DEDUCED_TYPENAME base_::value_type::info_type info_type;

    list_map_view(BOOST_DEDUCED_TYPENAME base_::base_type & c) :
        base_(c) {}

    list_map_view & operator=(const list_map_view & v)
    {
        this->base() = v.base(); 
        return *this;
    }

    BOOST_BIMAP_VIEW_ASSIGN_IMPLEMENTATION(base_)

    BOOST_BIMAP_VIEW_FRONT_BACK_IMPLEMENTATION(base_)

    // Rearrange Operations

    void relocate(BOOST_DEDUCED_TYPENAME base_::iterator position,
                  BOOST_DEDUCED_TYPENAME base_::iterator i)
    {
        this->base().relocate(
            this->template functor<
                BOOST_DEDUCED_TYPENAME base_::iterator_to_base>()(position),
            this->template functor<
                BOOST_DEDUCED_TYPENAME base_::iterator_to_base>()(i)
        );
    }

    void relocate(BOOST_DEDUCED_TYPENAME base_::iterator position,
                  BOOST_DEDUCED_TYPENAME base_::iterator first,
                  BOOST_DEDUCED_TYPENAME base_::iterator last)
    {
        this->base().relocate(
            this->template functor<
                BOOST_DEDUCED_TYPENAME base_::iterator_to_base>()(position),
            this->template functor<
                BOOST_DEDUCED_TYPENAME base_::iterator_to_base>()(first),
            this->template functor<
                BOOST_DEDUCED_TYPENAME base_::iterator_to_base>()(last)
        );
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
    BOOST_BIMAP_MAP_VIEW_EXTRA_TYPEDEF(MAP_VIEW,SIDE,reverse_iterator)        \
    BOOST_BIMAP_MAP_VIEW_EXTRA_TYPEDEF(MAP_VIEW,SIDE,const_reverse_iterator)  \
/*===========================================================================*/

namespace detail {

template< class Tag, class BimapType >
struct left_map_view_extra_typedefs< ::boost::bimaps::views::list_map_view<Tag,BimapType> >
{
    private: typedef ::boost::bimaps::views::list_map_view<Tag,BimapType> map_view_;
    public : BOOST_BIMAP_MAP_VIEW_EXTRA_TYPEDEFS_BODY(map_view_,left)
};

template< class Tag, class BimapType >
struct right_map_view_extra_typedefs< ::boost::bimaps::views::list_map_view<Tag,BimapType> >
{
    private: typedef ::boost::bimaps::views::list_map_view<Tag,BimapType> map_view_;
    public : BOOST_BIMAP_MAP_VIEW_EXTRA_TYPEDEFS_BODY(map_view_,right)
};

} // namespace detail

/*===========================================================================*/
#undef BOOST_BIMAP_MAP_VIEW_EXTRA_TYPEDEF
#undef BOOST_BIMAP_MAP_VIEW_EXTRA_TYPEDEFS_BODY
/*===========================================================================*/

} // namespace bimaps
} // namespace boost

#endif // BOOST_BIMAP_VIEWS_LIST_MAP_VIEW_HPP


/* list_map_view.hpp
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
*/