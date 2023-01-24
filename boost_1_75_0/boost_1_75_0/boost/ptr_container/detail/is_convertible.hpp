// (C) Copyright Thorsten Ottosen 2005
// (C) Copyright Howard Hinnant 2004
// (C) Copyright Jonathan Turkanis 2004
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt.)

//
// Contains type traits machinery for incomplete arrays. MPL compatibility
// is included for completeness, but is not necessary for the current 
// application.
// 

#ifndef BOOST_MOVE_PTR_ARRAYS_HPP_INCLUDED
#define BOOST_MOVE_PTR_ARRAYS_HPP_INCLUDED

#include <boost/config.hpp> // BOOST_STATIC_CONSTANT.
#include <boost/mpl/aux_/lambda_support.hpp>
#include <boost/mpl/and.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/mpl/identity.hpp>
#include <boost/mpl/if.hpp>
#include <boost/type_traits/is_array.hpp>
#include <boost/type_traits/is_convertible.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/type_traits/remove_bounds.hpp>
#include <boost/type_traits/remove_cv.hpp>
#include <boost/utility/enable_if.hpp>

namespace boost { namespace ptr_container_detail { namespace move_ptrs {

// From Howard Hinnant.
template<typename T, typename U>
struct is_array_convertible {
    typedef typename remove_bounds<T>::type      t_element; 
    typedef typename remove_bounds<U>::type      u_element; 
    typedef typename remove_cv<t_element>::type  t_base; 
    typedef typename remove_cv<u_element>::type  u_base; 
    typedef typename 
            mpl::and_<
                is_array<T>,
                is_array<U>,
                is_same<t_base, u_base>,
                is_convertible<t_element*, u_element*>
            >::type                                     type;
    BOOST_STATIC_CONSTANT(bool, value = type::value);
    BOOST_MPL_AUX_LAMBDA_SUPPORT(2, is_array_convertible, (T, U))
};

template<typename T, typename U>
struct is_smart_ptr_convertible 
    : mpl::if_<
          is_array<T>,
          is_array_convertible<T, U>,
          is_convertible<T*, U*> 
      >::type
    { };

#ifndef BOOST_NO_SFINAE
    template<typename Src, typename Tgt, typename T = void>
    struct enable_if_convertible 
        : enable_if< 
              is_smart_ptr_convertible<Src, Tgt>,
              T
          >
        { };
#else
    template<typename Src, typename Tgt, class T >
    struct enable_if_convertible : mpl::identity<T> { };
#endif

} } }         // End namespaces ptr_container_detail, move_ptrs, boost.

#endif      // #ifndef BOOST_MOVE_PTR_ARRAYS_HPP_INCLUDED

/* is_convertible.hpp
3+/BZbm+eZGx+v0Lgk6BIf/UA/9B8U8c9UkGJv3WbtRH4kNISU+LOw6XoZbv2gVwjfqVcPpDvu8++Jc+dOqFj8KjUkOmVmi+YsCn33ge3QtJMzEbd8s96/DREkjNud6CuJRq7l2tt91+qDiv1eqjaJgS0cfgxVFBmMG58A7yOknqgg3skj9M8TpMpit1I2CSAQk2rk47n/NcGCmOFzZAuCRKzuHFrZVfoD3+KG+A+JTSsTsbO//UIhgim2gaIGeE0sK/f13YOQSq0TZzhGhBUkVgA9endO1Pg63DsyYDYEPK1mE26LbdRlby8LTWsxBFiX0H/vgCOSdI2BPBEJiSsM+W0k3koPhPiUWENSEU//EvCkRwbvnCGoRrSp0rYMOuEf1eaQ0p65+BYIm9koZ7PoJq0H/uPtAPWJ8oz8aGnftlcI8Crn6dRhdmRKphPk8rkn8FgZvLECH0SSpKbGDFxI8X7kD3TPU+vDiy3MI1P59ZdyGs4ysDlAQgg9036Lx8Gby2sM8GyCCSpSzWXvkhVgWpm8JjiK6NlLrXCyKLcLNjgYQhdUKIm1jIlD6+uBnGqJYjICx1jCq5csT2UnnURK+iDyEp293ZqCXzbF5LQcNo5myILANBprw3qEh6nrqaTVBvzk6BvbN/48aZGvffSvCPFxQkYOcCp8qDVvY7lz5B+Pig6XL9POju8m5F5CMJnOviasMmQ119eh8i
*/