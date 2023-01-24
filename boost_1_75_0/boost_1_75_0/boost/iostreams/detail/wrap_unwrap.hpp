// (C) Copyright 2008 CodeRage, LLC (turkanis at coderage dot com)
// (C) Copyright 2003-2007 Jonathan Turkanis
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt.)

// See http://www.boost.org/libs/iostreams for documentation.

#ifndef BOOST_IOSTREAMS_DETAIL_WRAP_UNWRAP_HPP_INCLUDED
#define BOOST_IOSTREAMS_DETAIL_WRAP_UNWRAP_HPP_INCLUDED

#if defined(_MSC_VER)
# pragma once
#endif              

#include <boost/config.hpp>                             // SFINAE, MSVC.
#include <boost/detail/workaround.hpp>
#include <boost/iostreams/detail/enable_if_stream.hpp>
#include <boost/iostreams/traits_fwd.hpp>               // is_std_io.
#include <boost/mpl/bool.hpp>
#include <boost/mpl/identity.hpp>
#include <boost/mpl/eval_if.hpp>
#include <boost/mpl/if.hpp>
#include <boost/ref.hpp>

namespace boost { namespace iostreams { namespace detail {
                    
//------------------Definition of wrap/unwrap traits--------------------------//

template<typename T>
struct wrapped_type 
    : mpl::if_<is_std_io<T>, reference_wrapper<T>, T>
    { };

template<typename T>
struct unwrapped_type 
    : unwrap_reference<T>
    { };

template<typename T>
struct unwrap_ios 
    : mpl::eval_if<
          is_std_io<T>, 
          unwrap_reference<T>, 
          mpl::identity<T>
      >
    { };

//------------------Definition of wrap----------------------------------------//

#ifndef BOOST_NO_SFINAE //----------------------------------------------------//
    template<typename T>
    inline T wrap(const T& t BOOST_IOSTREAMS_DISABLE_IF_STREAM(T)) 
    { return t; }

    template<typename T>
    inline typename wrapped_type<T>::type
    wrap(T& t BOOST_IOSTREAMS_ENABLE_IF_STREAM(T)) { return boost::ref(t); }
#else // #ifndef BOOST_NO_SFINAE //-------------------------------------------//
    template<typename T>
    inline typename wrapped_type<T>::type // BCC 5.x needs namespace qualification.
    wrap_impl(const T& t, mpl::true_) { return boost::ref(const_cast<T&>(t)); }

    template<typename T>
    inline typename wrapped_type<T>::type // BCC 5.x needs namespace qualification.
    wrap_impl(T& t, mpl::true_) { return boost::ref(t); }

    template<typename T>
    inline typename wrapped_type<T>::type 
    wrap_impl(const T& t, mpl::false_) { return t; }

    template<typename T>
    inline typename wrapped_type<T>::type 
    wrap_impl(T& t, mpl::false_) { return t; }

    template<typename T>
    inline typename wrapped_type<T>::type 
    wrap(const T& t) { return wrap_impl(t, is_std_io<T>()); }

    template<typename T>
    inline typename wrapped_type<T>::type 
    wrap(T& t) { return wrap_impl(t, is_std_io<T>()); }
#endif // #ifndef BOOST_NO_SFINAE //------------------------------------------//

//------------------Definition of unwrap--------------------------------------//

template<typename T>
typename unwrapped_type<T>::type& 
unwrap(const reference_wrapper<T>& ref) { return ref.get(); }

template<typename T>
typename unwrapped_type<T>::type& unwrap(T& t) { return t; }

template<typename T>
const typename unwrapped_type<T>::type& unwrap(const T& t) { return t; }

} } } // End namespaces detail, iostreams, boost.

#endif // #ifndef BOOST_IOSTREAMS_DETAIL_WRAP_UNWRAP_HPP_INCLUDED

/* wrap_unwrap.hpp
1Kpp34GLL6aNkeaYSCNAwfNiKUU2qDgv2du3vb1zbBqO9MpcnM24rho67lHPOmwWkey0OZfZV2nNAdv35S+o03JGZneQixzqFkWdiGsheqUT4Il8xMBrTfavPbclX5pSc0Zemny9RjpBORoKbfHIVm8HvHhU3ZSKW+Wkprtj28IaOKVdBdyp5ivFr0qT890dd+UNnNKk8d2tbOqpBgEWSgZO6W8cJkHhfHdi28UM0BLRwoFTZpI/J+Zc5EQO8qwGKQ2Vj2lWL2/gen+9/oBFFJz6KW5V9balnx/0bgeT1GniY7iEVeNwpmRxkradjFyTnFFA0sJx/NUjRJbPo7B+iIQL+6e1Tck7KlD80p4LbjhdzopmF9nrm69WaMX3BlDXbhJO+rZXTA+exQE7D3jb/Y0c8Y8zbhf6fQNmVACQV9PAapB9eHi9p94c0E1y00+QOlMmFMrjlgF9wALOCJ7vXDJtXsWgmQbc96ck5GgRjxr9nE336yP1lX3Pa4G1FKAqE5iXcfPjYpN1O6ZuMOuor7OtUzyIhtfw1DAs8JANvR3WIP+la3FGYCHVUTev4RXngvAnKdEwwZeuY9mOU+WPgY84qlPPaUq1il8iFoePluxpZ8uifXRkqY2dRWNC6lBN3s91ty2/G52sFOSKiYyP84G7Bg3XsTzUajwwUZ493yfsz71o8L6jlws3Brb1y9PL1Q7xLlr+tCtewqKY
*/