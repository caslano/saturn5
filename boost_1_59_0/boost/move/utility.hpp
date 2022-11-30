//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga 2012-2012.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/move for documentation.
//
//////////////////////////////////////////////////////////////////////////////

//! \file
//! This header includes core utilities from <tt><boost/move/utility_core.hpp></tt> and defines
//! some more advanced utilities such as:

#ifndef BOOST_MOVE_MOVE_UTILITY_HPP
#define BOOST_MOVE_MOVE_UTILITY_HPP

#ifndef BOOST_CONFIG_HPP
#  include <boost/config.hpp>
#endif
#
#if defined(BOOST_HAS_PRAGMA_ONCE)
#  pragma once
#endif

#include <boost/move/detail/config_begin.hpp>
#include <boost/move/detail/workaround.hpp>  //forceinline
#include <boost/move/utility_core.hpp>
#include <boost/move/traits.hpp>

#if defined(BOOST_NO_CXX11_RVALUE_REFERENCES) && !defined(BOOST_MOVE_DOXYGEN_INVOKED)

   namespace boost {

   //////////////////////////////////////////////////////////////////////////////
   //
   //                            move_if_noexcept()
   //
   //////////////////////////////////////////////////////////////////////////////

   template <class T>
   BOOST_MOVE_FORCEINLINE typename ::boost::move_detail::enable_if_c
      < enable_move_utility_emulation<T>::value && !has_move_emulation_enabled<T>::value
      , typename ::boost::move_detail::add_const<T>::type &
      >::type
         move_if_noexcept(T& x) BOOST_NOEXCEPT
   {
      return x;
   }

   template <class T>
   BOOST_MOVE_FORCEINLINE typename ::boost::move_detail::enable_if_c
      < enable_move_utility_emulation<T>::value && has_move_emulation_enabled<T>::value
            && ::boost::move_detail::is_nothrow_move_constructible_or_uncopyable<T>::value, rv<T>&>::type
         move_if_noexcept(T& x) BOOST_NOEXCEPT
   {
      return *static_cast<rv<T>* >(::boost::move_detail::addressof(x));
   }

   template <class T>
   BOOST_MOVE_FORCEINLINE typename ::boost::move_detail::enable_if_c
      < enable_move_utility_emulation<T>::value && has_move_emulation_enabled<T>::value
            && ::boost::move_detail::is_nothrow_move_constructible_or_uncopyable<T>::value
      , rv<T>&
      >::type
         move_if_noexcept(rv<T>& x) BOOST_NOEXCEPT
   {
      return x;
   }

   template <class T>
   BOOST_MOVE_FORCEINLINE typename ::boost::move_detail::enable_if_c
      < enable_move_utility_emulation<T>::value && has_move_emulation_enabled<T>::value
            && !::boost::move_detail::is_nothrow_move_constructible_or_uncopyable<T>::value
      , typename ::boost::move_detail::add_const<T>::type &
      >::type
         move_if_noexcept(T& x) BOOST_NOEXCEPT
   {
      return x;
   }

   template <class T>
   BOOST_MOVE_FORCEINLINE typename ::boost::move_detail::enable_if_c
      < enable_move_utility_emulation<T>::value && has_move_emulation_enabled<T>::value
            && !::boost::move_detail::is_nothrow_move_constructible_or_uncopyable<T>::value
      , typename ::boost::move_detail::add_const<T>::type &
      >::type
         move_if_noexcept(rv<T>& x) BOOST_NOEXCEPT
   {
      return x;
   }

   }  //namespace boost

#else    //#if defined(BOOST_NO_CXX11_RVALUE_REFERENCES) && !defined(BOOST_MOVE_DOXYGEN_INVOKED)

   #if defined(BOOST_MOVE_USE_STANDARD_LIBRARY_MOVE)
      #include <utility>

      namespace boost{

      using ::std::move_if_noexcept;

      }  //namespace boost

   #else //!BOOST_MOVE_USE_STANDARD_LIBRARY_MOVE

      namespace boost {

      //////////////////////////////////////////////////////////////////////////////
      //
      //                            move_if_noexcept()
      //
      //////////////////////////////////////////////////////////////////////////////
      #if defined(BOOST_MOVE_DOXYGEN_INVOKED)
         //! This function provides a way to convert a reference into a rvalue reference
         //! in compilers with rvalue references. For other compilers converts T & into
         //! <i>::boost::rv<T> &</i> so that move emulation is activated. Reference
         //! would be converted to rvalue reference only if input type is nothrow move
         //! constructible or if it has no copy constructor. In all other cases const
         //! reference would be returned
         template <class T>
         rvalue_reference_or_const_lvalue_reference move_if_noexcept(input_reference) noexcept;

      #else //BOOST_MOVE_DOXYGEN_INVOKED

         template <class T>
         BOOST_MOVE_FORCEINLINE typename ::boost::move_detail::enable_if_c
            < ::boost::move_detail::is_nothrow_move_constructible_or_uncopyable<T>::value, T&&>::type
               move_if_noexcept(T& x) BOOST_NOEXCEPT
         {  return ::boost::move(x);   }

         template <class T>
         BOOST_MOVE_FORCEINLINE typename ::boost::move_detail::enable_if_c
            < !::boost::move_detail::is_nothrow_move_constructible_or_uncopyable<T>::value, const T&>::type
               move_if_noexcept(T& x) BOOST_NOEXCEPT
         {  return x;  }

      #endif //BOOST_MOVE_DOXYGEN_INVOKED

      }  //namespace boost {

   #endif   //#if defined(BOOST_MOVE_USE_STANDARD_LIBRARY_MOVE)

#endif   //BOOST_NO_CXX11_RVALUE_REFERENCES

#include <boost/move/detail/config_end.hpp>

#endif //#ifndef BOOST_MOVE_MOVE_UTILITY_HPP

/* utility.hpp
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
*/