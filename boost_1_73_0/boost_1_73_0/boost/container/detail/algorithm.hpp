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
zifhFy8AvUyq626FHaMTX4h1zQUpMJHLjaLS4CTzKJ4kYeJ8y+qcdwWFU81s1Vi9cwxHLnD/SUA9fQSHFQqFo14+FYxnPUVZZgoOC94cvDXMw1EymIaTNIwjZ0KwKgQawWql9YItAosy3Dsuyone3TaeFZRQhANZia42DWjuhCdEOWuK2tlf1wfTiltT1JSo+QZKYYXJCfphrlpSyxLJte7XjHNY6kaXVDnkmuCI0PaU5BXUdP2ftW8Fm2tkvEGuOoypIRtNDAVRRA8Son6QpvGdXKxWhjwnnOs6iGLjQ4BkK6qIoa4o0S2jfc3AoLemLMU+rloojM0xnLvphTHYQvsmt5NpnMaDeJw4ge5z3Bn9FlxOxiPHr0vH1s3I7ed7ZWU1Uz0sDit7evMA/nHg3jFmAhVojmyx40ma4eKBuxth9JZgW1Efr+kiELr3D2FCW0ydHRot/avTyT7s4xkm9wF/Yw0tufHGSL5BKxuJAcsrmv9poCT7m1ocuC+wgr81W4/Bd5rdh/+8Vr8vNLdGeEQO0LSozrLnDvd99J1roLKzeHoZpJl5j8/OsANdq8fFonZx/u4wPzr6+9HxS2aqEnwIwnHwPhyH6dwJisKW084AYzAdpbNpBB+C8WzkTKnCESsN5SiLLzBEkwo7
*/