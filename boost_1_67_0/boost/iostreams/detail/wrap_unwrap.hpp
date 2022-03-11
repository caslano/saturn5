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
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
*/