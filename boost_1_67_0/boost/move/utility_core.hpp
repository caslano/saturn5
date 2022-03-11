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

      //////////////////////////////////////////////////////////////////////////////
      //
      //                         move_if_not_lvalue_reference
      //
      //////////////////////////////////////////////////////////////////////////////


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

   #endif   //#if defined(BOOST_MOVE_USE_STANDARD_LIBRARY_MOVE)

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