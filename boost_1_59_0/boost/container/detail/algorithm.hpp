//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga 2014-2014.
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/container for documentation.
//
//////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_CONTAINER_DETAIL_ALGORITHM_HPP
#define BOOST_CONTAINER_DETAIL_ALGORITHM_HPP

#ifndef BOOST_CONFIG_HPP
#  include <boost/config.hpp>
#endif

#if defined(BOOST_HAS_PRAGMA_ONCE)
#  pragma once
#endif

#include <boost/intrusive/detail/algorithm.hpp>

namespace boost {
namespace container {

using boost::intrusive::algo_equal;
using boost::intrusive::algo_lexicographical_compare;

template<class Func>
class binder1st
{
   public:
	typedef typename Func::second_argument_type  argument_type;
	typedef typename Func::result_type           result_type;

	binder1st(const Func& func, const typename Func::first_argument_type& arg)
   	: op(func), value(arg)
	{}

	result_type operator()(const argument_type& arg) const
   {	return op(value, arg);  }

	result_type operator()(argument_type& arg) const
   {  return op(value, arg);   }

   private:
	Func op;
	typename Func::first_argument_type value;
};

template<class Func, class T> 
inline binder1st<Func> bind1st(const Func& func, const T& arg)
{	return boost::container::binder1st<Func>(func, arg);  }

template<class Func>
class binder2nd
{
   public:
	typedef typename Func::first_argument_type   argument_type;
	typedef typename Func::result_type           result_type;

	binder2nd(const Func& func, const typename Func::second_argument_type& arg)
	   : op(func), value(arg)
   {}

	result_type operator()(const argument_type& arg) const
   {  return op(arg, value);  }

	result_type operator()(argument_type& arg) const
	{  return op(arg, value);  }

   private:
	Func op;
	typename Func::second_argument_type value;
};

template<class Func, class T>
inline binder2nd<Func> bind2nd(const Func& func, const T& arg)
{
   return (boost::container::binder2nd<Func>(func, arg));
}

template<class Func>
class unary_negate
{
   public:
   typedef typename Func::argument_type   argument_type;
   typedef typename Func::result_type     result_type;

	explicit unary_negate(const Func& func)
		: m_func(func)
   {}

	bool operator()(const typename Func::argument_type& arg) const
	{  return !m_func(arg);  }

   private:
	Func m_func;
};

template<class Func> inline
unary_negate<Func> not1(const Func& func)
{
   return boost::container::unary_negate<Func>(func);
}

template<class InputIt, class UnaryPredicate>
InputIt find_if(InputIt first, InputIt last, UnaryPredicate p)
{
   for (; first != last; ++first) {
      if (p(*first)) {
         return first;
      }
   }
   return last;
}

template<class ForwardIt1, class ForwardIt2, class BinaryPredicate>
  ForwardIt1 find_end (ForwardIt1 first1, ForwardIt1 last1
                      ,ForwardIt2 first2, ForwardIt2 last2
                      ,BinaryPredicate p)
{
   if (first2==last2)
      return last1;  // specified in C++11

   ForwardIt1 ret = last1;

   while (first1!=last1)
   {
      ForwardIt1 it1 = first1;
      ForwardIt2 it2 = first2;
      while ( p(*it1, *it2) ) {
         ++it1; ++it2;
         if (it2==last2) {
            ret=first1;
            break;
         }
         if (it1==last1)
         return ret;
      }
      ++first1;
   }
   return ret;
}

template<class InputIt, class ForwardIt, class BinaryPredicate>
InputIt find_first_of(InputIt first1, InputIt last1, ForwardIt first2, ForwardIt last2, BinaryPredicate p)
{
   for (; first1 != last1; ++first1) {
      for (ForwardIt it = first2; it != last2; ++it) {
         if (p(*first1, *it)) {
            return first1;
         }
      }
   }
   return last1;
}

template<class ForwardIt1, class ForwardIt2, class BinaryPredicate>
ForwardIt1 search(ForwardIt1 first1, ForwardIt1 last1,
                        ForwardIt2 first2, ForwardIt2 last2, BinaryPredicate p)
{
   for (; ; ++first1) {
      ForwardIt1 it = first1;
      for (ForwardIt2 it2 = first2; ; ++it, ++it2) {
         if (it2 == last2) {
            return first1;
         }
         if (it == last1) {
            return last1;
         }
         if (!p(*it, *it2)) {
            break;
         }
      }
   }
}

}  //namespace container {
}  //namespace boost {

#endif   //#ifndef BOOST_CONTAINER_DETAIL_ALGORITHM_HPP

/* algorithm.hpp
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
*/