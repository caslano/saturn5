// Boost.Bimap
//
// Copyright (c) 2006-2007 Matias Capeletto
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

/// \file views/map_view.hpp
/// \brief View of a side of a bimap that is signature compatible with std::map.

#ifndef BOOST_BIMAP_VIEWS_MAP_VIEW_HPP
#define BOOST_BIMAP_VIEWS_MAP_VIEW_HPP

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/config.hpp>

#include <boost/bimap/container_adaptor/map_adaptor.hpp>
#include <boost/bimap/detail/map_view_base.hpp>

namespace boost {
namespace bimaps {
namespace views {

/// \brief View of a side of a bimap that is signature compatible with std::map.
/**

This class uses container_adaptor and iterator_adaptor to wrapped a index of the
multi_index bimap core so it can be used as a std::map.

See also const_map_view.
                                                                            **/

template< class Tag, class BimapType >
class map_view
:
    public BOOST_BIMAP_MAP_VIEW_CONTAINER_ADAPTOR(
        map_adaptor,
        Tag,BimapType,
        reverse_map_view_iterator,const_reverse_map_view_iterator
    ),
    public ::boost::bimaps::detail::
        map_view_base< map_view<Tag,BimapType>,Tag,BimapType >,
    public ::boost::bimaps::detail::
        unique_map_view_access< map_view<Tag,BimapType>, Tag,  BimapType>::type
{
    typedef BOOST_BIMAP_MAP_VIEW_CONTAINER_ADAPTOR(
        map_adaptor,
        Tag,BimapType,
        reverse_map_view_iterator,const_reverse_map_view_iterator

    ) base_;

    BOOST_BIMAP_MAP_VIEW_BASE_FRIEND(map_view,Tag,BimapType)

    typedef BOOST_DEDUCED_TYPENAME ::boost::bimaps::detail::
        unique_map_view_access<
            map_view<Tag,BimapType>, Tag,  BimapType

        >::type unique_map_view_access_;

    public:

    typedef BOOST_DEDUCED_TYPENAME base_::value_type::info_type info_type;

    map_view(BOOST_DEDUCED_TYPENAME base_::base_type & c) : base_(c) {}

    using unique_map_view_access_::at;
    using unique_map_view_access_::operator[];

    BOOST_BIMAP_MAP_VIEW_RANGE_IMPLEMENTATION(base_)

    map_view & operator=(const map_view & v) 
    {
        this->base() = v.base();
        return *this;
    }

    // It can be used enable_if here but the error message when there 
    // is no info is very clear like this

    template< class CompatibleKey >
    const info_type & info_at(const CompatibleKey& k) const
    {
        BOOST_DEDUCED_TYPENAME base_::const_iterator iter = this->find(k);
        if( iter == this->end() )
        {
            ::boost::throw_exception(
                std::out_of_range("bimap<>: invalid key")
            );
        }
        return iter->info;
    }

    template< class CompatibleKey >
    info_type & info_at(const CompatibleKey& k)
    {
        BOOST_DEDUCED_TYPENAME base_::iterator iter = this->find(k);
        if( iter == this->end() )
        {
            ::boost::throw_exception(
                std::out_of_range("bimap<>: invalid key")
            );
        }
        return iter->info;
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
    BOOST_BIMAP_MAP_VIEW_EXTRA_TYPEDEF(MAP_VIEW,SIDE,range_type)              \
    BOOST_BIMAP_MAP_VIEW_EXTRA_TYPEDEF(MAP_VIEW,SIDE,const_range_type)        \
    BOOST_BIMAP_MAP_VIEW_EXTRA_TYPEDEF(MAP_VIEW,SIDE,key_compare)
/*===========================================================================*/

namespace detail {

template< class Tag, class BimapType >
struct left_map_view_extra_typedefs< ::boost::bimaps::views::map_view<Tag,BimapType> >
{
    private: typedef ::boost::bimaps::views::map_view<Tag,BimapType> map_view_;
    public : BOOST_BIMAP_MAP_VIEW_EXTRA_TYPEDEFS_BODY(map_view_,left)
};

template< class Tag, class BimapType >
struct right_map_view_extra_typedefs< ::boost::bimaps::views::map_view<Tag,BimapType> >
{
    private: typedef ::boost::bimaps::views::map_view<Tag,BimapType> map_view_;
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


/* map_view.hpp
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
*/