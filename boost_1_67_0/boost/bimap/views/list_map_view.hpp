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