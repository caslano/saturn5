
#ifndef BOOST_MPL_MAP_AUX_EMPTY_IMPL_HPP_INCLUDED
#define BOOST_MPL_MAP_AUX_EMPTY_IMPL_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2003-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#include <boost/mpl/empty_fwd.hpp>
#include <boost/mpl/not.hpp>
#include <boost/mpl/map/aux_/tag.hpp>

namespace boost { namespace mpl {

template<>
struct empty_impl< aux::map_tag >
{
    template< typename Map > struct apply
        : not_< typename Map::size >
    {
    };
};

}}

#endif // BOOST_MPL_MAP_AUX_EMPTY_IMPL_HPP_INCLUDED

/* empty_impl.hpp
4r1IELP6Gl6o8jDl3D7uJkDQqWLKxEvSGpD/3iE770nAp2+597GEzDJKpICaZ9SxvHt/aMy9IB6QbH5zOJy2ZtRA/cBSAHY66MeH2xDDJZXz1oc/qJCbWWSXTXw7sB0CbWkXRWiWlxV17Vcns0J462amOtqjELmVTzR4ezL6rklIDIImIyMEwFHbsNOdm5ZFQmei4ahtOevNixrLpyqKF8T2MenvZTOMTRiQ6rdUwv1jNYzqwHpq8cMWJURFlXr7so3RWaVOb30cJPwdnP/27Bi4QKDF1+Edqgw0Noq78dIipbkldAf59H6qosz4WdpDop93qm/Z6dCmFU5s8Lqulnj6O4VNsVR9IcmsFAtIdjeGOhG87sCqeqlFy6FfohwAqSzkeAlWEldggwBa37YyKVdN2Q46WDQeNPVqrqh+rqgWs6qc0XYABAot6m+PkokavA4sW9zCuBWRrfygevNF/ILFnSjY2WGpvygxFp/zO7a8zKgMu0yZzDMNU35NBJHk1ZY0aXjHy+PvKudsxwHd57zoL1H2X2JwdshOYFBWWePMrQTtZqJwkSo5E1gGWp0/EUEV1iO426x5i6vkitm3wSCCNd6NLteJW/n95Y+eCUjC96N3Pi8DsDWYj/WoX8pE8z75ffb8Q5oUQ6dPqUMlAHf1nKhwgiDoZbhAoIBflrdRcMlGYMGz2ZsSFAziJb0XKzjQbolzARFs0QM/
*/