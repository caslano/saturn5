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