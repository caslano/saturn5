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
J8/hInbw59lcJTOzUWn1e8YnT+nhPtY4pDDJ74jwaR5D54mke1hJe9Vq+d7YL5K/21Up1f2IMwwjDXyFqtXwOegk/GerK+WE9CuWWkehSlnutuoGTNa/3T1CfTabk9iYp3WAhoSqoU7f7l4cSn9JYA7tEeQsLr4b71SBOj05lt7ZQUdYGLX8HA1Z/DX/eZ5iH4E97FqKrup7WJTdr8nkCzLD0O7OCC5WzpcBKrwV8uN/ie8b+oGFuB+DA0idjXahSjvHqxe+jmAYQSIuFLvzesz+jv6bzeDsHSaC35iIa5CSNltg8NwxpH0pmnhnIt9RoDSiQ+FAzm0nUOiRLPiSNgGlWPRvAGYsmdPp5X6xeP62Ryx5WDwSOu3Of9LTVYAlz1bBTr/VYH5nH5TfPwFlZiqQYnAVHhkcAHOdrWBgtA2OPpJrDAox6mWDKmzOhak83Akr3yiCbPwJuGB9Gss4DmmWKlB+8zA43JMGOfvpsMJ6Iix+MD6g73yxvLvzys5AVVDINgDz0idAf28DNqn3wNVBFT5bHoHiG3tgi+NMWGc/FVbbTFLvW94/3GTsssQTIRrFDyD6UwBkNCVADTsLvMudgX7/MGTdXwmeFpKw3mGat/ydKaP6m7PWbzSX6uSZhoR/8ociVhJou+HnhNwbsMZTCYwMFkG+0Q4fL5OVUl+7Z0hIjX34k2fRI+3AKs8Iq9Inn7flXfs0L2xf
*/