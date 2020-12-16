// Boost.Bimap
//
// Copyright (c) 2006-2007 Matias Capeletto
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

/// \file relation/detail/mutant.hpp
/// \brief Mutate functions to extract views of mutant classes.

#ifndef BOOST_BIMAP_RELATION_DETAIL_MUTANT_HPP
#define BOOST_BIMAP_RELATION_DETAIL_MUTANT_HPP

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/config.hpp>

#include <boost/bimap/detail/debug/static_error.hpp>
#include <boost/mpl/contains.hpp>
#include <boost/mpl/assert.hpp>
#include <boost/static_assert.hpp>
#include <boost/type_traits/is_const.hpp>
#include <boost/utility/addressof.hpp>
#include <boost/mpl/not.hpp>
#include <boost/utility/enable_if.hpp>

namespace boost {
namespace bimaps {
namespace relation {

/// \brief Relation details, mutant idiom and symmetrical metafunctions builders.

namespace detail {

//@{
/// \brief Converts a mutant class to a view with zero overhead.
/**

This function is a safe wrapper around reinterpret_cast. It checks at
compile time that the desired view is supported by the mutant class.
See also mutant, can_mutate_in.
\ingroup mutant_group
                                                                            **/


template< class View, class Type >
BOOST_DEDUCED_TYPENAME enable_if< mpl::not_< is_const< Type > >,

View&

>::type mutate( Type & m )
{
    BOOST_MPL_ASSERT((
        ::boost::mpl::contains<BOOST_DEDUCED_TYPENAME Type::mutant_views,View>
    ));
    return *reinterpret_cast< View* >(boost::addressof(m));
}

template< class View, class Type >
BOOST_DEDUCED_TYPENAME enable_if< is_const< Type >,

const View&

>::type mutate( Type & m )
{
    BOOST_MPL_ASSERT((
        ::boost::mpl::contains<BOOST_DEDUCED_TYPENAME Type::mutant_views,View> 
    ));
    return *reinterpret_cast< const View* >(boost::addressof(m));
}

//@}

} // namespace detail
} // namespace relation
} // namespace bimaps
} // namespace boost

#endif // BOOST_BIMAP_RELATION_DETAIL_MUTANT_HPP


/* mutant.hpp
PH/EKfPlLDo5/3Qg5SVUVOhXyjn2JyiOU+iZvyfL5wzJruC7ZqfQ+5vXfoZDTx/f6Hk+vtGHmnyLF5p8ixd7f4tTvSm18Xe+XBfq/X1ebPgW/0/ZW/ED+hbe/ergV6skPZnSWjldpp1dXl753opH3e8Ct2lTwGhYBCNTjefR1QQ7gbXA4WBt8A4wDhwPJoA7wHrgR2AD0KogTjAMbAxGgU3BJDAVbASmgW3BdLALmAH2ALPAlWBL8FX+dv0czAVPgzeD58G24EWwHXgFbA8G8Tcr0r7mM8TX+L9d/MZv/MZv/MZv/MZvfjHzq/X/R4y8If3/v8ZgfQD3/xfweffTVczdBu8AO9RF//cvdmHYb81TCWCuA+Bw7aQO4DNyh2Ot53l9z6RDTlkdMx0Ax5ErdQDHyN1cNdUByDDFSrE4LnUAYe84ZSFIewWkNbBWZIXXWQM8t4DDT1DGoK8XwX3yIAr/jXJKxLKeACPIrrxTP7vQe881oy4Acep98mK4vfZVY12DjdK5qHwtooxj/gjv2f8300VcIX9XlIsi3KgTkOGjaA0ju/GkN0DjvEGZ4aWLiOL7/oj8tVaboCzSlK8Me6l55mleJTqJThX8LjbRSXxBfuqrP8CXqprrJEZSGVVVqorTUifRgGQ5So7Y5VMn8S7Fnar60kkcQlijTuLDQ546iTByh0D/s0GUX0UnMZfiSsKONR946CReInmkEilQhvwM3HUS9dFUJ/HOocp1EokURxXk7Zwsn3SS1cGOZp8YznWA/RV0Erym0WvtfbGPtfdTvPafMlvL6K23WOxDbzHLW2+h6zbxL7VxDtQVZmekU3bYq2276np+V5jusk0Kedfp3mY3acPYf0e5J4WN/O+0+5jfRPNossCbyM+Ldvdz/vgI1XktXvyZ5zu5420j55P8TO66Fuy/qNWicNB9UjwLbTWw0j8M+z1N0uarobbBgueR8PXLNgt2hOqvZWjmc6Rkel7tpnu+S02K6wW7e+/KC+T/Pft34lO1u8WuGdpDjovnI0l3sMOzDdXnSdWhuNdR3H0Qx2Xyf9B+VpxQO1qCZNwpFeK+ZBJ3OsfdCQzk5+Geg/UV+U8wtJ+ecQIyTh/zuqiuV6M4t9ojOM5wcg+ytxVBdmMbaozXYYjXvC31DBNWIczaMGe7NAF5cbVLXO3F1KPUTmjVxHHVKc/jcdmX36OwWqQ4QfJClm8h+WW0whdJrlFesM6c5DW0uuKIWgvySJY/RPKLWrrYiPWdl5VkbaNwp6Pi+jG6HqXVFB9SuEKWv0vyF7Ug6JJfEW1Ui/Y8hRuI6840z9P1aK22+IDCFbH8dyT/RhuCVXqXhKL20+6jcIMUV3vroPsdphWKJRTuDpY/SeFOa2Pxu4M9FbGn6ngKNxjXrbheh8J10/qIZyncGJavp3AfaCViFNbPRqtjtVEUzsJnqmYd9cxnBMsHkDxVs4lE1KMd6s9qIoWrytej6Hos3uv3EM4lt8OOIHmCZoHvRnjnf1KjKFw0X0+n61W1WLzXTnkHxSXvQfJQLUp85no+cOGSfM/DxXq0A2vUI9YNAtfp20iV1x+0BYnNdH2PtYyuF+E6ytvQTvyJ2pH+2nBKF3POqFwXUbqvaG3EKyQfA7lVyl/T2oktajyVC35pZXyf2hxiK8U3SLtdrW7rw2WDWV4cVtZB1P9md2K3GENenOFc8mGijod8shZB8okkj3/fKX8OMpffeIMsiv3FVwjP31mGOYXj5dw0jfztsnezXKT5dO1xNZFkq+2+vlnCwd10LxYsC76iur8zFlEYVcTz9097biO6QtZY7aFM1+zYX/B2ZYbNbpzbKOfiXaL3fr+9l+UC5SPXcF8=
*/