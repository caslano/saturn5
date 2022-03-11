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