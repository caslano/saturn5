// Boost.Bimap
//
// Copyright (c) 2006-2007 Matias Capeletto
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

/// \file views/unordered_map_view.hpp
/// \brief View of a side of a bimap that is signature compatible with tr1::unordered_map.

#ifndef BOOST_BIMAP_VIEWS_UNOREDERED_MAP_VIEW_HPP
#define BOOST_BIMAP_VIEWS_UNOREDERED_MAP_VIEW_HPP

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/config.hpp>

#include <utility>

#include <boost/bimap/container_adaptor/unordered_map_adaptor.hpp>
#include <boost/bimap/detail/map_view_base.hpp>

namespace boost {
namespace bimaps {
namespace views {

/// \brief Map View of a bimap, signature compatible with tr1::unordered_map.
/**

This class uses container_adaptor and iterator_adaptor to wrapped a index of the
multi_index bimap core so it can be used as a tr1::unordered_map.

See also const_unordered_map_view.
                                                                             **/


template< class Tag, class BimapType >
class unordered_map_view
:
    public BOOST_BIMAP_MAP_VIEW_CONTAINER_ADAPTOR(
        unordered_map_adaptor,
        Tag,BimapType,
        local_map_view_iterator,const_local_map_view_iterator
    ),

    public ::boost::bimaps::detail::map_view_base<
                unordered_map_view<Tag,BimapType>,Tag,BimapType >,
    public ::boost::bimaps::detail::
                unique_map_view_access<
                    unordered_map_view<Tag,BimapType>, Tag,  BimapType>::type

{
    typedef BOOST_BIMAP_MAP_VIEW_CONTAINER_ADAPTOR(
        unordered_map_adaptor,
        Tag,BimapType,
        local_map_view_iterator,const_local_map_view_iterator

    ) base_;

    BOOST_BIMAP_MAP_VIEW_BASE_FRIEND(unordered_map_view,Tag,BimapType)

    typedef BOOST_DEDUCED_TYPENAME ::boost::bimaps::detail::
        unique_map_view_access<
            unordered_map_view<Tag,BimapType>, Tag,  BimapType

        >::type unique_map_view_access_;

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

    unordered_map_view(BOOST_DEDUCED_TYPENAME base_::base_type & c)
        : base_(c) {}

    using unique_map_view_access_::at;
    using unique_map_view_access_::operator[];

    unordered_map_view & operator=(const unordered_map_view & v) 
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
    BOOST_BIMAP_MAP_VIEW_EXTRA_TYPEDEF(MAP_VIEW,SIDE,local_iterator)          \
    BOOST_BIMAP_MAP_VIEW_EXTRA_TYPEDEF(MAP_VIEW,SIDE,const_local_iterator)    \
    BOOST_BIMAP_MAP_VIEW_EXTRA_TYPEDEF(MAP_VIEW,SIDE,range_type)              \
    BOOST_BIMAP_MAP_VIEW_EXTRA_TYPEDEF(MAP_VIEW,SIDE,const_range_type)        \
    BOOST_BIMAP_MAP_VIEW_EXTRA_TYPEDEF(MAP_VIEW,SIDE,hasher)                  \
    BOOST_BIMAP_MAP_VIEW_EXTRA_TYPEDEF(MAP_VIEW,SIDE,key_equal)
/*===========================================================================*/

namespace detail {

template< class Tag, class BimapType >
struct left_map_view_extra_typedefs< ::boost::bimaps::views::unordered_map_view<Tag,BimapType> >
{
    private: typedef ::boost::bimaps::views::unordered_map_view<Tag,BimapType> map_view_;
    public : BOOST_BIMAP_MAP_VIEW_EXTRA_TYPEDEFS_BODY(map_view_,left)
};

template< class Tag, class BimapType >
struct right_map_view_extra_typedefs< ::boost::bimaps::views::unordered_map_view<Tag,BimapType> >
{
    private: typedef ::boost::bimaps::views::unordered_map_view<Tag,BimapType> map_view_;
    public : BOOST_BIMAP_MAP_VIEW_EXTRA_TYPEDEFS_BODY(map_view_,right)
};

} // namespace detail

/*===========================================================================*/
#undef BOOST_BIMAP_MAP_VIEW_EXTRA_TYPEDEF
#undef BOOST_BIMAP_MAP_VIEW_EXTRA_TYPEDEFS_BODY
/*===========================================================================*/

} // namespace bimaps
} // namespace boost

#endif // BOOST_BIMAP_VIEWS_UNOREDERED_MAP_VIEW_HPP



/* unordered_map_view.hpp
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
*/