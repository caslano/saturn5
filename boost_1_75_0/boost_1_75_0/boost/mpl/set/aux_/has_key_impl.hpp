
#ifndef BOOST_MPL_SET_AUX_HAS_KEY_IMPL_HPP_INCLUDED
#define BOOST_MPL_SET_AUX_HAS_KEY_IMPL_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2003-2004
// Copyright David Abrahams 2003-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#include <boost/mpl/set/aux_/tag.hpp>
#include <boost/mpl/has_key_fwd.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/mpl/aux_/overload_names.hpp>
#include <boost/mpl/aux_/static_cast.hpp>
#include <boost/mpl/aux_/yes_no.hpp>
#include <boost/mpl/aux_/type_wrapper.hpp>
#include <boost/mpl/aux_/config/workaround.hpp>
#include <boost/mpl/aux_/config/static_constant.hpp>

namespace boost { namespace mpl {

template<>
struct has_key_impl< aux::set_tag >
{
    template< typename Set, typename T > struct apply
#if BOOST_WORKAROUND(BOOST_MSVC, BOOST_TESTED_AT(1400)) \
    || BOOST_WORKAROUND(__EDG_VERSION__, <= 245)
    {
        BOOST_STATIC_CONSTANT(bool, value = 
              ( sizeof( BOOST_MPL_AUX_OVERLOAD_CALL_IS_MASKED(
                    Set
                  , BOOST_MPL_AUX_STATIC_CAST(aux::type_wrapper<T>*, 0)
                  ) ) == sizeof(aux::no_tag) )
            );

        typedef bool_<value> type;

#else // ISO98 C++
        : bool_< 
              ( sizeof( BOOST_MPL_AUX_OVERLOAD_CALL_IS_MASKED(
                    Set
                  , BOOST_MPL_AUX_STATIC_CAST(aux::type_wrapper<T>*, 0)
                  ) ) == sizeof(aux::no_tag) )
            >
    {
#endif
    };
};

}}

#endif // BOOST_MPL_SET_AUX_HAS_KEY_IMPL_HPP_INCLUDED

/* has_key_impl.hpp
uI+bR8eDoTS2a0mX956OXDHNoCF0i9dddyYhGv9beBoNAeR78ZnzA1Ln9hSOyFOadJ4IFGQBFftQEshFpWJTHNtRauhWO8hiHOVVIejY0VqKnwe2rIX1lYWlot5gQJnCUKYLTW+QJZ1MXDxfnOhGu91iTpxpA0E5lJ8j6mGvfHdRA4O+Xv+exe55H9ewbf2T4Lh4BzCo2sR3zO4X52G+ipTcQ7kblKZyZb0xtG4RFOLAEkTq8PC6c/JZ1h3Venl8y3yNoS2jB+r1+G2aV+SFoteFC4J0/EC35wQejAzviwtF3XtLAs+JV871Pp5wBOWOP17BfVhviaNQHoEwtMkT7x9uRYD4GnQG+K+uIOz7K3RXs/sceAfc5+INF5RYvO3xKne1a5AS5ZrVbQ5VaU1AaKs8aXxxPWpbAGiylDmeZ87VhHez05jLyqwup4Y07anaKXLyu/gHA3cBdgVVBVIF3gcpDAer6Lov1sBf1hFIB2EOzhTAL0bOL4DBNDG9pCQR0efozf361avBAln1MDaaPdohqi/X9XhUYUymbMd/fuFP+PAWlasPlyJ09pw3po++OGT3TyH04fAW3E9tqH9iUZ7SsGGyQ5KKKqY6CGV+VjLfmGG6c2fHnrw+CKbcjHBcwsEbMB348KdrNllDESFxC+Y6Y2xm5kXMo01T7z9RRVhtipxLER+HcmP2vVXofS2Mxqrc+4Zfiq35h6U3
*/