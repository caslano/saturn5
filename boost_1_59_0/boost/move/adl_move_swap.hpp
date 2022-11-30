//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright 2007, 2008 Steven Watanabe, Joseph Gauterin, Niels Dekker
// (C) Copyright Ion Gaztanaga 2005-2013. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/container for documentation.
//
//////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_MOVE_ADL_MOVE_SWAP_HPP
#define BOOST_MOVE_ADL_MOVE_SWAP_HPP

#ifndef BOOST_CONFIG_HPP
#  include <boost/config.hpp>
#endif
#
#if defined(BOOST_HAS_PRAGMA_ONCE)
#  pragma once
#endif

//Based on Boost.Core's swap.
//Many thanks to Steven Watanabe, Joseph Gauterin and Niels Dekker.
#include <cstddef> //for std::size_t
#include <boost/move/detail/workaround.hpp>  //forceinline

//Try to avoid including <algorithm>, as it's quite big
#if defined(_MSC_VER) && defined(BOOST_DINKUMWARE_STDLIB)
   #include <utility>   //Dinkum libraries define std::swap in utility which is lighter than algorithm
#elif defined(BOOST_GNU_STDLIB)
   //For non-GCC compilers, where GNUC version is not very reliable, or old GCC versions
   //use the good old stl_algobase header, which is quite lightweight
   #if !defined(BOOST_GCC) || ((__GNUC__ < 4) || ((__GNUC__ == 4) && (__GNUC_MINOR__ < 3)))
      #include <bits/stl_algobase.h>
   #elif (__GNUC__ == 4) && (__GNUC_MINOR__ == 3)
      //In GCC 4.3 a tiny stl_move.h was created with swap and move utilities
      #include <bits/stl_move.h>
   #else
      //In GCC 4.4 stl_move.h was renamed to move.h
      #include <bits/move.h>
   #endif
#elif defined(_LIBCPP_VERSION)
   #include <type_traits>  //The initial import of libc++ defines std::swap and still there
#elif __cplusplus >= 201103L
   #include <utility>    //Fallback for C++ >= 2011
#else
   #include <algorithm>  //Fallback for C++98/03
#endif

#include <boost/move/utility_core.hpp> //for boost::move

#if !defined(BOOST_MOVE_DOXYGEN_INVOKED)

#if defined(BOOST_NO_CXX11_RVALUE_REFERENCES)
namespace boost_move_member_swap {

struct dont_care
{
   dont_care(...);
};

struct private_type
{
   static private_type p;
   private_type const &operator,(int) const;
};

typedef char yes_type;            
struct no_type{ char dummy[2]; }; 

template<typename T>
no_type is_private_type(T const &);

yes_type is_private_type(private_type const &);

template <typename Type>
class has_member_function_named_swap
{
   struct BaseMixin
   {
      void swap();
   };

   struct Base : public Type, public BaseMixin { Base(); };
   template <typename T, T t> class Helper{};

   template <typename U>
   static no_type deduce(U*, Helper<void (BaseMixin::*)(), &U::swap>* = 0);
   static yes_type deduce(...);

   public:
   static const bool value = sizeof(yes_type) == sizeof(deduce((Base*)(0)));
};

template<typename Fun, bool HasFunc>
struct has_member_swap_impl
{
   static const bool value = false;
};

template<typename Fun>
struct has_member_swap_impl<Fun, true>
{
   struct FunWrap : Fun
   {
      FunWrap();

      using Fun::swap;
      private_type swap(dont_care) const;
   };

   static Fun &declval_fun();
   static FunWrap declval_wrap();

   static bool const value =
      sizeof(no_type) == sizeof(is_private_type( (declval_wrap().swap(declval_fun()), 0)) );
};

template<typename Fun>
struct has_member_swap : public has_member_swap_impl
      <Fun, has_member_function_named_swap<Fun>::value>
{};

}  //namespace boost_move_member_swap

namespace boost_move_adl_swap{

template<class P1, class P2, bool = P1::value>
struct and_op_impl
{  static const bool value = false; };

template<class P1, class P2>
struct and_op_impl<P1, P2, true>
{  static const bool value = P2::value;   };

template<class P1, class P2>
struct and_op
   : and_op_impl<P1, P2>
{};

//////

template<class P1, class P2, bool = P1::value>
struct and_op_not_impl
{  static const bool value = false; };

template<class P1, class P2>
struct and_op_not_impl<P1, P2, true>
{  static const bool value = !P2::value;   };

template<class P1, class P2>
struct and_op_not
   : and_op_not_impl<P1, P2>
{};

template<class T>
BOOST_MOVE_FORCEINLINE void swap_proxy(T& x, T& y, typename boost::move_detail::enable_if_c<!boost::move_detail::has_move_emulation_enabled_impl<T>::value>::type* = 0)
{
   //use std::swap if argument dependent lookup fails
   //Use using directive ("using namespace xxx;") instead as some older compilers
   //don't do ADL with using declarations ("using ns::func;").
   using namespace std;
   swap(x, y);
}

template<class T>
BOOST_MOVE_FORCEINLINE void swap_proxy(T& x, T& y
               , typename boost::move_detail::enable_if< and_op_not_impl<boost::move_detail::has_move_emulation_enabled_impl<T>
                                                                        , boost_move_member_swap::has_member_swap<T> >
                                                       >::type* = 0)
{  T t(::boost::move(x)); x = ::boost::move(y); y = ::boost::move(t);  }

template<class T>
BOOST_MOVE_FORCEINLINE void swap_proxy(T& x, T& y
               , typename boost::move_detail::enable_if< and_op_impl< boost::move_detail::has_move_emulation_enabled_impl<T>
                                                                    , boost_move_member_swap::has_member_swap<T> >
                                                       >::type* = 0)
{  x.swap(y);  }

}  //namespace boost_move_adl_swap{

#else

namespace boost_move_adl_swap{

template<class T>
BOOST_MOVE_FORCEINLINE void swap_proxy(T& x, T& y)
{
   using std::swap;
   swap(x, y);
}

}  //namespace boost_move_adl_swap{

#endif   //#if defined(BOOST_NO_CXX11_RVALUE_REFERENCES)

namespace boost_move_adl_swap{

template<class T, std::size_t N>
void swap_proxy(T (& x)[N], T (& y)[N])
{
   for (std::size_t i = 0; i < N; ++i){
      ::boost_move_adl_swap::swap_proxy(x[i], y[i]);
   }
}

}  //namespace boost_move_adl_swap {

#endif   //!defined(BOOST_MOVE_DOXYGEN_INVOKED)

namespace boost{

//! Exchanges the values of a and b, using Argument Dependent Lookup (ADL) to select a
//! specialized swap function if available. If no specialized swap function is available,
//! std::swap is used.
//!
//! <b>Exception</b>: If T uses Boost.Move's move emulation and the compiler has
//! no rvalue references then:
//!
//!   -  If T has a <code>T::swap(T&)</code> member, that member is called.
//!   -  Otherwise a move-based swap is called, equivalent to: 
//!      <code>T t(::boost::move(x)); x = ::boost::move(y); y = ::boost::move(t);</code>.
template<class T>
BOOST_MOVE_FORCEINLINE void adl_move_swap(T& x, T& y)
{
   ::boost_move_adl_swap::swap_proxy(x, y);
}

//! Exchanges elements between range [first1, last1) and another range starting at first2
//! using boost::adl_move_swap.
//! 
//! Parameters:
//!   first1, last1   -   the first range of elements to swap
//!   first2   -   beginning of the second range of elements to swap
//!
//! Type requirements:
//!   - ForwardIt1, ForwardIt2 must meet the requirements of ForwardIterator.
//!   - The types of dereferenced ForwardIt1 and ForwardIt2 must meet the
//!     requirements of Swappable
//!
//! Return value: Iterator to the element past the last element exchanged in the range
//! beginning with first2.
template<class ForwardIt1, class ForwardIt2>
ForwardIt2 adl_move_swap_ranges(ForwardIt1 first1, ForwardIt1 last1, ForwardIt2 first2)
{
    while (first1 != last1) {
      ::boost::adl_move_swap(*first1, *first2);
      ++first1;
      ++first2;
    }
   return first2;
}

template<class BidirIt1, class BidirIt2>
BidirIt2 adl_move_swap_ranges_backward(BidirIt1 first1, BidirIt1 last1, BidirIt2 last2)
{
   while (first1 != last1) {
      ::boost::adl_move_swap(*(--last1), *(--last2));
   }
   return last2;
}

template<class ForwardIt1, class ForwardIt2>
void adl_move_iter_swap(ForwardIt1 a, ForwardIt2 b)
{
   boost::adl_move_swap(*a, *b); 
}

}  //namespace boost{

#endif   //#ifndef BOOST_MOVE_ADL_MOVE_SWAP_HPP

/* adl_move_swap.hpp
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
*/