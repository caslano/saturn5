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
lSmpdyMVajfcbn+YmGy3kwcSkYkNqMKAUVBpdIAjHchUJGO+U0FosaiCVOrE2ashqjxyVQka05RzEU6irmUjrJryOBwGBSmWhm9a5Zqp1onKDgKpjpwlrsqciKgOFBQpKrMDVR5haYPtzrcUTU1tgX/Ymr3eCFROYqA7WsF01YVAaKkduJ96N4s7D+5Hy+Vo7j3A4gpG8wdO9td0fkmtl0RWAr4UJWoiL0FmRSoxajh/3uV23AGcX05W4wumXzEPwo3n3cL1xKM9U3O1USTD7j9BQXXR7DNBXSDTCFPbjdHn7jaR2/lF5mFaRQjn2kRSDZOLw6VUBodrFfXARLzWWmQ/1abidW2EkSFo+Q/6BtalNOhHwojes5IRDApTOtuPfNu95BlmgQN1FPUGRdbv/NuBdiY6iPA7xDZpb5fJ2WJ7V9PZBAb9Bn1G4BINGWcLPut863RkbsjbMreCaorx3XIGA96Cn5AtU2Ros5GQjGkgTEQJg7qyXMlcZEhSurwyVJXpMqKm3wf9IEugok07B78f5diGnHVoyep6SlUgUl/m0vRYrn89W/w5mvmj2axvo8gi/NE6gBHUea1pNHCfmxz13ojSvqHQmzrfLoGmccaloCP2RI97pI2lrzQPeq1Ujq3c4tbz6eZQNZoJ
*/