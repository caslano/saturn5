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