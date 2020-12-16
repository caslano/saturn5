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
1bBPOGCXCFjKFzmOwvwSO0qWGMdjDVJsXRoQPUQ5PMA77WEI77sa78sOvBMk3i48aELiju0A1NhYLBb5e6u4xrz+fPoeh+DrjIdo7UTfvEfcoe7096QV7lD1w+7QCvp7K3E5l9vj8fqysrLcWRlZ+GRkZGRlZGaKv1v///k3fezzD6yAK/y2VY1ojvI0p+2+KJHCYTWsYU6HmUGxZxtLd60hVLoUq72KgcbfdXfCNgCsHN3pr3cquxDjom5lnNZcqnldf+NTe3SrRGtFooM8JjtgfU037v//LN2e5QjSC+RpccEY/TZav43Sb1PpDZ/NC6bptxn05rj8lWQgsv3+MznisQ78yQI54mPwaLDZg90zUXovJrN1FxJ8KJYtXrrFz2XBEaTTm10bBNybPOmFjptNK6HwZvezInQthaZZyKiduZ+N+gFPxDy7UVi/X1BMP61BNUkEE9AMAUSwBJTzKYACAqhqHZ6iE1zMReP6xrvxMj63hoFSRRSTTI4QyBBSZr5yk+C0C8bTT4AB9XLmH77N/JMXG5wokRxMT4k6OP9xRNQiXVlyQV8kTCbzgDtZO1oEApxMKmHBjdoMRxZJPKVbs4zULR7gAFxBLbKo4XIUvETl0cBs0UY0pSetea1gTS0D7M5P1CK6RjRgTRIQpbReOQOiAdBoCggZEKVN1NIvav3JEs1VRU3h5KKMqVzDCADJGCcisXGhF+BFcJVJdYhwsRBYWNJUcVpNLQcwfu8kZMTxHMjZJEpDIjXpUYiQMirXU8ud5bqDHEvJ8QNMoFn/ZRJgDFMcT2x/prjRFmO4pBPSKpGsNbhqsvwcDkkSvagCVW0MJ2TJuPzlTRUXi7JhnpM18UQEME7VVKSfWhS5kbj9+9yUkh6z6JQqr4YLsslNzThB0QwvqVnNuq/EIlXrpnEV+iKExwxeMGZyRMvmozNhaKL5EEMF4l5Ug2h0LSAl2XWlKAFaEpGDOYWMzD0OmxVqZqZQbb5qGiTPl11i6CX77WFjpDThqfuhhj+az9HGhzqCmgAtcrOIEENE3G2N//TQ7rb+/+M4H//oJ0peqmex21xyQXgMSY+WsmTInyYZ6sVnIF0yj2RpX8It7hGeo4WfI//a3KzPW3AsCm8OkGHyZFfAwoPRtzjdF8cR0R3LLX8u39xK5Hy5WQv1C/P5508c8zMU+jA/N7WcnxtQUL5lKObn7mp+broB6Qa7hRJjxRDDcKdN0avFbHtWUu9ghcIvJKseRgppAwmIiTgFbyTKA9AYIsIrqc5agONKMwTREEN/OFHcUw7fOIHkFsHV1atWY4ubXEp/eAJE2lQVPXiamwDKz+K5bQNev8Mw8/B6qbzEgK3yQk/15C775F1r2ll5rqezV/MxGsy02dpEUS7jNl2xFxwViy/iiiVJAmpUi7XrKTcpg2AhK5sLgew4M3E3zUtFPYy+Xen7ybPu0GD66/K5fY6PBw/v1n/fB/ZY/kZcn7pTq/OuX/7swPbgmue3f55W9dOOz9N63ttmeu6VsMYC6yAku8gnYN52hOI9+exU2FqhTMaKXTgjW3uFyLBj/QZ5/k9HTco4TAE8qsbHK+QBQq6dPF4ygnm3No8i00zwFUz0WQFxUJ9heTsrHuP6BcS4Pl/gUnbiAo7MUaOc7zqvPx4tdE2GSGV71hYIIGAuTWQUkIsA0k8IdOZUsfV5Nloh3f77nZI/IPOxZlcqjFMZbRhambdpqy9X4p2QsI7EvwmmU0Sx2/sw1rAJiCWY2G6/tlR2kAOWF7+pwi3P7wHBv6M+c+7VqnO0f/75I/QH0c4hMhbHNc0mxrVGrOhQ1buOUkpS0sd4aE42m76iCkzn9gFvFydNy3g=
*/