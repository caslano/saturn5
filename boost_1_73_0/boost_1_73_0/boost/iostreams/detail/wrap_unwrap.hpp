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
ALeoqOKS2XO77vmyeSxvISLUedd4B8F4czBfbG6Cqw2vqC0jGU62MtSALGoS3h2Q6YAw6zyyXYLP9c12fRXMrueLs/b/5vrjBZdmu14uvmyXi9UquLpcns3+PH+6eNR7Ad2q+RKBejr8R+Mx/oKaSq7D46F59X3+T5IHSI39Z0a+6ZVVgg9+eLkO5lUnN4Xz7sQ3G7NzeDp8fzocDIbuu8Vi5L49mZ27o8Vo5J7Mf+0vRu/PB8PT3215lz91QKiwMULB/hayU7aDl8q/EOJQG8hCk0BvdfHp2Dop/XAFRqt9ASFjC60GsXJ6pixIKdQF5fbbACXfrfLhR8R59mvnt33KcJHU4Y7nBXQpEghbNvUWxmDDz0EbySaxw/a8CDjw1RLYE8+EjTBcZC9b93FlqpWuMLOETGXX3Te9xscvSxkddyeT7vd/I+LfXeexI0Mz6xPH3k+o+8JstBIbHmb+ecIB/3Upg/62oPT+ZNh/96rs/5Rk4uxhf92NTQ/aj0Ul0LTzD1BLAwQKAAAAAAAtZ0pSAAAAAAAAAAAAAAAAFAAJAGN1cmwtbWFzdGVyL3NjcmlwdHMvVVQFAAG2SCRgUEsDBAoAAAAIAC1nSlIGsoohSQMAAPYJAAAfAAkAY3VybC1tYXN0ZXIvc2Ny
*/