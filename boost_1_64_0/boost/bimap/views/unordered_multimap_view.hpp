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
FcOi41qJbEED4np6SeV8xiJe8dUw0p16gEqD7bgF1POh/nk/06Plod8Acg1N4zBN4+jh0Wn8mL662D2NE+hdTTl82D46XcUHUA6Ep/EO7/uzC6Lj+Amydd5xNPnvFc+6veR/3QHk/4ftG57/613SlpdN3QtL2xTpb0zma7pyXerVigPI/1xTb8Lj+McR0XHshuw6rzhK5nvHcV29ec/5A8j73AbU/eCYeMHI6HTdgP93Tbqm9csfVDTq6ElF1XOrpfPWe3dUmvCj/TDnE+S8LW6rUDB9tZEx63n7kC6uadKVrulKEDdznfB70ajotG3L5q+fM21SmyRNn0aXE7L7X5cIT+MbPk/b6hKvP2TjOyxe4fndMTq/kQ/l95Pu+Y3M/ud3R5f8fjI6v0261o6OTtcX9r0iPF3aMjzzHPl62wbn979tfNqAtrET5vu99qX03qdx4uG2+4TR948pGvDT4pY39jjrw9oh8732S/Ta3/Jfrxvjl9o/c5fsk/nDAy+812HlZwOyr5+2+Mm10zL5PiLOdm+2MWnxzI7vDfv6ob73tqyaUO693+YoSdfQXXldpn678MLV407I2Nbo4l9zX5Bwntw07bM/V7bZ+vPvV4x+s+PdOxh3i/uaD47Puab41ibnJ27wpX+78gHv/S2TRf61wmvHbL21su/SHhtf/OLHS7p47Xu577rY9lXnisd+nh77i3rtI7rv+3/WSv4vWvmHv334TH7+uc9MWVBxyS3bLOvP4l7b+rffnDt5+QnndzvuuuS+jbd47+9a2cx2nzWw1fov236y5ZWBK9scdXKHhcwzyIfVGH7ybU4+7IC51nH8mB5nY9Y5jrfqcQ7mE8dxaibnSH8Jx+l6/D7HJzjcTwwdy9phti/QB52ix4Ucl+rxDI5n6vEe/OzAvsDsPyNlKeeSYKWm5W6GQl3hfXAIvB+eCB+ARfBhWA0fg4vg4/D38Al4FVwP/wyfgvfBp+Fa+AzcARcH9x2Br+j1m8GFev0NyHWDL8JD4EvwCLgRHgs3wZNtv3AG/BuUb4vgefANuAS+rfF4B94J34X3wr/DR+B7Gp+Bwf06YB+Nj+qLk984f0BvznjYHU6APeHhEP98Ead7ToDb1H8iLFX/p6p+u1nwUDgbToGV8BhYC8vgHHgGnAsXwtPgRXAeXAZr4JWwVuNdaPZkQEav2wiO1uueoXp+zoSd4Vmar+fAMbBO8/U8eBT8jYa7wnznL3soSLgpHC/TcP8REwjnPTgUvg+nww/gDPghrIUfw4VwK7wUfgqvhJ/B1XAbvBN+Dp+EX8KX4Xb4KtwBt8Kv4TdwJ9wFv4E74EZpU1puGs9WUv8Cv5uR6w9XwSHwz3CY2keovRjeCmfB22CV2qvVfha8C14G74bXw3vgrfBe+AC8Dz4C18In4MNwg4b/JlwH98DH4U/wSdjGnuvDrvBB2B3er+laZel3wvB9LddU+EdN1zPI5cPnYT+4AQ5U+xC1j4UvwEL4Ipyi9mPVXgw3wjnwZXgm3AQXw1fgEg1nOXwNPghfhw/DN+FbcLPGd5r5jlS/g9VncpOg7HuAXDYs1vIo0XI4BY6CMzRepbAUlsEKOBNeCMvh5XA2vAX+Hq6BlRqvKviI2tep/Tk4F74Eq+FmeBr8EM6Dn8Na+DU8XevX2bAxcV4I0+A5sD38lZbPr2E+tK8/HM6Gk+FVsBReDSvgNXAOXAQXwPPhOfACeB5cDC+AF8Fl8GJ4JfwjXAuvhY/B66H2L/odId9CuvQv12n/sgLmwhtgd3gj7A9v0n78FjgCroQT4Z/hTLgazoG3a79+h/YDdZZ+Iwdf1+s2hbV63Qu1P7kIDoUXw+lwCSyGl8I=
*/