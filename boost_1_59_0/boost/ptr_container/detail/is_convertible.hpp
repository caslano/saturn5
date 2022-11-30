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
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
*/