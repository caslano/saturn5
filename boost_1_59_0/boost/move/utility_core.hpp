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
//! This header defines core utilities to ease the development
//! of move-aware functions. This header minimizes dependencies
//! from other libraries.

#ifndef BOOST_MOVE_MOVE_UTILITY_CORE_HPP
#define BOOST_MOVE_MOVE_UTILITY_CORE_HPP

#ifndef BOOST_CONFIG_HPP
#  include <boost/config.hpp>
#endif
#
#if defined(BOOST_HAS_PRAGMA_ONCE)
#  pragma once
#endif

#include <boost/move/detail/config_begin.hpp>
#include <boost/move/detail/workaround.hpp>  //forceinline
#include <boost/move/core.hpp>
#include <boost/move/detail/meta_utils.hpp>
#include <boost/static_assert.hpp>

#if defined(BOOST_NO_CXX11_RVALUE_REFERENCES) && !defined(BOOST_MOVE_DOXYGEN_INVOKED)

   namespace boost {

   template<class T>
   struct enable_move_utility_emulation
   {
      static const bool value = true;
   };
    
   //////////////////////////////////////////////////////////////////////////////
   //
   //                            move()
   //
   //////////////////////////////////////////////////////////////////////////////

   template <class T>
   BOOST_MOVE_FORCEINLINE typename ::boost::move_detail::enable_if_and
      < T &
      , enable_move_utility_emulation<T>
      , has_move_emulation_disabled<T>
      >::type
         move(T& x) BOOST_NOEXCEPT
   {
      return x;
   }

   template <class T>
   BOOST_MOVE_FORCEINLINE typename ::boost::move_detail::enable_if_and
      < rv<T>&
      , enable_move_utility_emulation<T>
      , has_move_emulation_enabled<T>
      >::type
         move(T& x) BOOST_NOEXCEPT
   {
      return *BOOST_MOVE_TO_RV_CAST(::boost::rv<T>*, ::boost::move_detail::addressof(x) );
   }

   template <class T>
   BOOST_MOVE_FORCEINLINE typename ::boost::move_detail::enable_if_and
      < rv<T>&
      , enable_move_utility_emulation<T>
      , has_move_emulation_enabled<T>
      >::type
         move(rv<T>& x) BOOST_NOEXCEPT
   {
      return x;
   }

   //////////////////////////////////////////////////////////////////////////////
   //
   //                            forward()
   //
   //////////////////////////////////////////////////////////////////////////////

   template <class T>
   BOOST_MOVE_FORCEINLINE typename ::boost::move_detail::enable_if_and
      < T &
      , enable_move_utility_emulation<T>
      , ::boost::move_detail::is_rv<T>
      >::type
         forward(const typename ::boost::move_detail::identity<T>::type &x) BOOST_NOEXCEPT
   {
      return const_cast<T&>(x);
   }

   template <class T>
   BOOST_MOVE_FORCEINLINE typename ::boost::move_detail::enable_if_and
      < const T &
      , enable_move_utility_emulation<T>
      , ::boost::move_detail::is_not_rv<T>
      >::type
         forward(const typename ::boost::move_detail::identity<T>::type &x) BOOST_NOEXCEPT
   {
      return x;
   }

   //////////////////////////////////////////////////////////////////////////////
   //
   //                        move_if_not_lvalue_reference()
   //
   //////////////////////////////////////////////////////////////////////////////

   template <class T>
   BOOST_MOVE_FORCEINLINE typename ::boost::move_detail::enable_if_and
      < T &
      , enable_move_utility_emulation<T>
      , ::boost::move_detail::is_rv<T>
      >::type
         move_if_not_lvalue_reference(const typename ::boost::move_detail::identity<T>::type &x) BOOST_NOEXCEPT
   {
      return const_cast<T&>(x);
   }

   template <class T>
   BOOST_MOVE_FORCEINLINE typename ::boost::move_detail::enable_if_and
      < typename ::boost::move_detail::add_lvalue_reference<T>::type
      , enable_move_utility_emulation<T>
      , ::boost::move_detail::is_not_rv<T>
      , ::boost::move_detail::or_
         < ::boost::move_detail::is_lvalue_reference<T>
         , has_move_emulation_disabled<T>
         >
      >::type
         move_if_not_lvalue_reference(typename ::boost::move_detail::remove_reference<T>::type &x) BOOST_NOEXCEPT
   {
      return x;
   }

   template <class T>
   BOOST_MOVE_FORCEINLINE typename ::boost::move_detail::enable_if_and
      < rv<T>&
      , enable_move_utility_emulation<T>
      , ::boost::move_detail::is_not_rv<T>
      , ::boost::move_detail::and_
         < ::boost::move_detail::not_< ::boost::move_detail::is_lvalue_reference<T> >
         , has_move_emulation_enabled<T>
         >
      >::type
         move_if_not_lvalue_reference(typename ::boost::move_detail::remove_reference<T>::type &x) BOOST_NOEXCEPT
   {
      return move(x);
   }

   }  //namespace boost

#else    //#if defined(BOOST_NO_CXX11_RVALUE_REFERENCES) && !defined(BOOST_MOVE_DOXYGEN_INVOKED)

   #if defined(BOOST_MOVE_USE_STANDARD_LIBRARY_MOVE)
      #include <utility>

      namespace boost{

      using ::std::move;
      using ::std::forward;

      }  //namespace boost

   #else //!BOOST_MOVE_USE_STANDARD_LIBRARY_MOVE

      namespace boost {

      //! This trait's internal boolean `value` is false in compilers with rvalue references
      //! and true in compilers without rvalue references.
      //!
      //! A user can specialize this trait for a type T to false to SFINAE out `move` and `forward`
      //! so that the user can define a different move emulation for that type in namespace boost
      //! (e.g. another Boost library for its types) and avoid any overload ambiguity.
      template<class T>
      struct enable_move_utility_emulation
      {
         static const bool value = false;
      };

      //////////////////////////////////////////////////////////////////////////////
      //
      //                                  move
      //
      //////////////////////////////////////////////////////////////////////////////

      #if defined(BOOST_MOVE_DOXYGEN_INVOKED)
         //! This function provides a way to convert a reference into a rvalue reference
         //! in compilers with rvalue references. For other compilers if `T` is Boost.Move
         //! enabled type then it converts `T&` into <tt>::boost::rv<T> &</tt> so that
         //! move emulation is activated, else it returns `T &`.
         template <class T>
         rvalue_reference move(input_reference) noexcept;

      #elif defined(BOOST_MOVE_OLD_RVALUE_REF_BINDING_RULES)

         //Old move approach, lvalues could bind to rvalue references
         template <class T>
         BOOST_MOVE_FORCEINLINE typename ::boost::move_detail::remove_reference<T>::type && move(T&& t) BOOST_NOEXCEPT
         {  return t;   }

      #else //BOOST_MOVE_OLD_RVALUE_REF_BINDING_RULES

         template <class T>
         BOOST_MOVE_FORCEINLINE typename ::boost::move_detail::remove_reference<T>::type && move(T&& t) BOOST_NOEXCEPT
         { return static_cast<typename ::boost::move_detail::remove_reference<T>::type &&>(t); }

      #endif   //BOOST_MOVE_OLD_RVALUE_REF_BINDING_RULES

      //////////////////////////////////////////////////////////////////////////////
      //
      //                                  forward
      //
      //////////////////////////////////////////////////////////////////////////////


      #if defined(BOOST_MOVE_DOXYGEN_INVOKED)
         //! This function provides limited form of forwarding that is usually enough for
         //! in-place construction and avoids the exponential overloading for
         //! achieve the limited forwarding in C++03.
         //!
         //! For compilers with rvalue references this function provides perfect forwarding.
         //!
         //! Otherwise:
         //! * If input_reference binds to const ::boost::rv<T> & then it output_reference is
         //!   ::boost::rv<T> &
         //!
         //! * Else, output_reference is equal to input_reference.
         template <class T> output_reference forward(input_reference) noexcept;
      #elif defined(BOOST_MOVE_OLD_RVALUE_REF_BINDING_RULES)

         //Old move approach, lvalues could bind to rvalue references

         template <class T>
         BOOST_MOVE_FORCEINLINE T&& forward(typename ::boost::move_detail::identity<T>::type&& t) BOOST_NOEXCEPT
         {  return t;   }

      #else //Old move

         template <class T>
         BOOST_MOVE_FORCEINLINE T&& forward(typename ::boost::move_detail::remove_reference<T>::type& t) BOOST_NOEXCEPT
         {  return static_cast<T&&>(t);   }

         template <class T>
         BOOST_MOVE_FORCEINLINE T&& forward(typename ::boost::move_detail::remove_reference<T>::type&& t) BOOST_NOEXCEPT
         {
            //"boost::forward<T> error: 'T' is a lvalue reference, can't forward as rvalue.";
            BOOST_STATIC_ASSERT(!boost::move_detail::is_lvalue_reference<T>::value);
            return static_cast<T&&>(t);
         }

      #endif   //BOOST_MOVE_DOXYGEN_INVOKED

      }  //namespace boost {

   #endif   //BOOST_MOVE_USE_STANDARD_LIBRARY_MOVE

   //////////////////////////////////////////////////////////////////////////////
   //
   //                         move_if_not_lvalue_reference
   //
   //////////////////////////////////////////////////////////////////////////////

   namespace boost {

   #if defined(BOOST_MOVE_DOXYGEN_INVOKED)
      //! <b>Effects</b>: Calls `boost::move` if `input_reference` is not a lvalue reference.
      //!   Otherwise returns the reference
      template <class T> output_reference move_if_not_lvalue_reference(input_reference) noexcept;
   #elif defined(BOOST_MOVE_OLD_RVALUE_REF_BINDING_RULES)

      //Old move approach, lvalues could bind to rvalue references

      template <class T>
      BOOST_MOVE_FORCEINLINE T&& move_if_not_lvalue_reference(typename ::boost::move_detail::identity<T>::type&& t) BOOST_NOEXCEPT
      {  return t;   }

   #else //Old move

      template <class T>
      BOOST_MOVE_FORCEINLINE T&& move_if_not_lvalue_reference(typename ::boost::move_detail::remove_reference<T>::type& t) BOOST_NOEXCEPT
      {  return static_cast<T&&>(t);   }

      template <class T>
      BOOST_MOVE_FORCEINLINE T&& move_if_not_lvalue_reference(typename ::boost::move_detail::remove_reference<T>::type&& t) BOOST_NOEXCEPT
      {
         //"boost::forward<T> error: 'T' is a lvalue reference, can't forward as rvalue.";
         BOOST_STATIC_ASSERT(!boost::move_detail::is_lvalue_reference<T>::value);
         return static_cast<T&&>(t);
      }

   #endif   //BOOST_MOVE_DOXYGEN_INVOKED

   }  //namespace boost {

#endif   //BOOST_NO_CXX11_RVALUE_REFERENCES

#if !defined(BOOST_MOVE_DOXYGEN_INVOKED)

namespace boost{
namespace move_detail{

template <typename T>
typename boost::move_detail::add_rvalue_reference<T>::type declval();

}  //namespace move_detail{
}  //namespace boost{

#endif   //#if !defined(BOOST_MOVE_DOXYGEN_INVOKED)


#include <boost/move/detail/config_end.hpp>

#endif //#ifndef BOOST_MOVE_MOVE_UTILITY_CORE_HPP

/* utility_core.hpp
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
*/