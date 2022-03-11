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