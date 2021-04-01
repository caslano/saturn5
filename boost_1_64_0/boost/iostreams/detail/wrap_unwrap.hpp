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
ululAw40hvMHm0TKZlQAch1G9k4owN2v+3iyPOkeG+WfcejLdIDUnqxA0yIogZFwQp2G794NkWakS62+iGSpZAZXDv2BNiYoiIfREsAz4e8kZRW0VY0fg17lqD0lfeMGoQgU2FeWm2wUd4U94D8s/MpstNxKcDdlTl0zca3kkZJbS6XEZpFggDmlBOumqqjrfrFS8aYisZ98Xyfw1EpB6I206qsyYsBHp8GBC+NqAjAcx/UWYyhqf0nmjY8kRv+IdrwUtgspwgh6dRMfBv2NPTg2yz9FH6HBZBems8V+sXjLG6RmPiTIT8sQafX+mHS2Rs6o9KAOKGR2sKEl1Enkt21lqt/LoFasRty6650WrMD0pbBslMnLmAXMtGiyf9dcvwgaRVzUbIB9QQU4DNXhxevX5bdmzQoQKU2OfUUakSKY811NwOCBWJaCA2XwMPygaV450N713IU9sGKFl+U+fpzRsUd4x19d5fFWKsNKhtCpA6L0nv9dThyROV/LqoxuMccShEEKJ/pBUKvvXgwdvv51ieEwzYp7LIHpaYcrLCG0LWUyDO1Y4brEJw==
*/