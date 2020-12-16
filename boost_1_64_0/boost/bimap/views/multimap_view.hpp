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
yzrK0hStLNwPBfvcBdKnqmlQl64pV59qEPcK4z7TcXfu5VpRHtIj76Tn6lMNck7SCJGTresUfd7bE61Ma6pY7FSta6YPEc577lM35z6+FWU63tw3yehJiizPcnvdFq089VUNzBUX1ojqJO8yHXS1VW9LyrQq6N4Rqruzt3KC5Qq2FWlwjjTC2uqUzMiynWFfowJlq18ZeY0qq2tYY+6T4/Q+2VynnHLpeMK36YPG3dmza0W5sqVcpKfnnDElaYTKy0cp16X29WqClityDvMqE2FC81yUcWJ5dtf7sC6R+fusfe2Jlj/GPXL99iXVdV99/Dy46+NQlPQGca4kanrovNL6KOgSWR8lYfVxTwvyEqwP4tP6CM3frq6R+Zttz+nR8le3tr7au70I03wfVHdn/7kV+W9NH7w0Ul+AtHtTtDLJDat3nRPGmdtlvlhRud41XzSFlWl2K8pk2sQ9t8t8QRpha5NqlfsfqOXpiymz5/ZAmaQUMp703jtS14b6JYYeVhudH82a3qyLf2zKS5uZMJ1lz6cxixKQj73yLIG9vJSW6aUMvVcvN2Xtb9aSoWPUr4vFF3Sv5ZBN/B6NKGt9Q3nFSr3t1T3L0PWYhuli9hOSimz7I1H3G+bgninu90Sst+xhkidu2yP3FHRtM0Pcx6sdqXqxZ0vdrcqmDbvxDiwlTPP1TUtKtlzjWPf41d/mbmbvYVvE3oP62YufD+y4UorSfPQjp//p3gP2BPMspnXPZLS9dHyVG3nU/HgvOVIvucSTJ7fpIUfqIbfpLffYf6N9vsvHW+9t+NPFfyltSH3n3o/6Puklz+klh9l6OU8POVIPuVkvuV8veVEveeDWy/F6yOV6yBV7y+t+KHJQjnxp14DcJf1f5Gx4kkr/dX6zf+X8vtf1+ybX722u37v1t92Pb3b9/orr917X77tdv+9w/d7p/JZnIftgNuY2/b0ZozJv+lxWniXjFirzxniRb+UPgz3hcNgbjoD5ah+kdow1GZ4Ox8BFcKzKVI6Dy+F4eCmcAL8Ei+DdEs6RsZDnkrBU8+OWsbhOZQObYEe1Z6q9J9wC+6pM3ii4A05X2br58GZNp9rSZ3RwgqaTgjlX0+mispfZsAvMgd1gD5ir9jzYHQ5S+1CYC0fCbnC02o2sp6ZXrOm5ZXzyNL18jae/xjMAjoWnwomwAE5W+/vwMOagxvuGxpuFOeTonGnsBWdqvczSdqvQ+GdrvHPgNDgPzoVz4QJYAs/S80vgfFgBF8ArVMZ2M1wEr4fnwq0qY7tD7beq/S6Vuf2Gnt8DF8Pvqsztw5qvn8Fl8Fdq136hzxPIc5R+cRn+MuDl2l6NKiO7SfvFBi3/FXAc3Agnwc/D012yszst3cvXZwn7YAfpVxwqK9kf7oMD4SPaPo/BxfBx7d8/UdnOJ1S280m4F/4cPgAPwO+r/TH4FHwNHoRvwl/Cd6UdAzLSz8BE+CsjE677x7C7PP/712TCt2GOanxXaf2mYzYHZdA0vhrYCdbCwbAOngYbtB7XwjK4Di6Dl8AKPX++nl+t52tUJrgBrofr9PyFKlN9pdgd2TrZU4WjNH9u2brlOg+cp+1TreFyMUc1XCZmZKhMmRmfkH3ClvkrdPyRj1B/m13+SloYX10L/TW10N+eFvo72EJ/R5vx19NdfxNa5q+whf5KWuivroX+mlrgrxizR/0NxOwLG1e36ji6TcfR7bAHvAP2Untftev1Ve/VGYNRrq93qyz7bo3nXg2/BxbBb8EZKtt9ptrPVnsF/LbKlu+F2+D9cKfKfH8HPggPqcw3cp3/MzJaLZXPiiabVYlZEJTN+oTlso4nk7XrN21aLZcVLpO1jzgOY6w=
*/