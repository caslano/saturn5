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