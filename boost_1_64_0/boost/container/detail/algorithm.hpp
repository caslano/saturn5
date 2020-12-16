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
8zwPHN4FS5Ksa+jqJbAUMjtmCze1fwHLQA0ws9lnYQZpzbojuwbBcqX61gyolwArJLNl1qvNtRyY6oyxNawUdwXmTcbzvDuyIAmmI7Nkpv3NywLmT8Znu3hgQAtYEBmvwcraag1ML60ZftVM6We8ZCbPLefCEslUzOp3en5H6TWZA7P42JvDYRlSns8SonbDsqX9lrjWyYblSHHquDEHYPlkTryf15qEwVRnjftpe3z7S5g3GZ9DlaxHqTAdGd9vzC9jp8P8ycoz+22efjBMT8ZrnzzyWT1YAhnPc3u3ll2UnpGZMTvaJ6QfLF2qYan1pdOwbLIKzK785ZcEKyRzZiaWrJ4HU58zEZWYPchIy1NqJ1Mzmz/eVA8LIrPiPTvwtY1SO1lVZi0/NZ4ASyZzZNakbk9vpT4yXkPZgrQIWA6ZDzPT5XueKzWcNxGVmSW3iz8H8yNzZxYX1DRTyZMM1+t3dDz6xqvZRTa3VAoZaiig41CTzz4wA5kPs/LvGi6CWWUp960/LW9N2zYwFZkFi3Ou1b0FTENmzuxJzn93YD5k5dias+eX6g7zJXNlcROOVQuGBZK5MNt1asRUWCyZDbNeFaaUgiWQWTO7aPY4EJZMposter39SMeRZn5DYfkDTJV+fqLjVy3+twLmPdBUeb/5mY57+k1aDgsiiy9+v/mFjnU7A2Jg2iBlTTLKu3+OYkPI8LnwVzp+2aNMKiyMDM+xH2Y/5Ph0WCIZ/vbUD9ty8aUJLCmY9mNxqXVuv4Zlk9kxe9/ApxEsl8yC2Ry/xS1hhWTmzL5tjCsDU4WYKn/39ZugODGxPyx+uLLmTzOf+rwdbC4Zav9hMV73pir1SZamf/M37A/J/mv1LE2pncye7bfspEHZL43MjNnUxxtGwjKkPEePH7ITli3Z8l0B62E5kgUd8tTAXpCZsjyfO/XIhuWTubC4C12vNICpRhjnWc2+/QaYhsySmdnz9K4wLRnPJbRg9ReYjsyG2Zq5Bw0wfzIrZvufOC2GBUm57C7s2AMWTlaW1df/v0WNYKPJyjBL/tqzNixOijsXd38VLIHMnO03vNxGL1gSmTWzzU//UWaUQsbnHtkjxgqWQWbH7Ha1d81gBjIHZmF7KlSC5ZPZMmu1uMFNmNlI4zl07tTwd5hasnr2vz+EeZPxOdzIN7jBfMmqM4uYN9UcpifDc/o7HVs+3NUSlkYW61f0/BMmc0t5jQyNVvpyzFR53yHICmpHr4DlkFVltrlJQR5MddzY5o6v3Bemkyzklsd6JU8yvl/LC0lXlVykuDrVej2AGSTr1Hn0M5jZCeM1F2imZCu5kPG46amrNyq5SHGHxNtMJRfJPj9teQ2WQ1aX2cJ9T5QaNCdNRTVmHWuMngTzl2yFbYVusHgyH2a9rr75AkuX4v7+9DAJlivFzapUv76SyynjuKuzl1VVciHjNVg6XBKwRCmuSf9N42EZZHy/AU3eToQVSnFuPr5lYN6njfcraPWrPyyMjMftdKoaAEsi4/vdfOvkAsuWrekTW5hZprF1K3UzFqYj82Y29vYjpWd6yWaPMg+DJUu2MfViUyUXycIH1R4KE2eM7duiUE+YVrI5DyZ/ggVJ9uf55krtiZLtnruyDCxDsmqtbvwGy5fs0OyP92Gas9J5VslcD/Mnq8rspfnnfbB4yao8s/sAS5PMclLsAVgOWdRP8/9pa8cE1IbpzxmbRekmKlghWQ22ZvSNoIow7Xlja1mj5jBYmGT9debhsGTJ/kh+6AUzSOa+9ZRpyf2usUUETRwN85Ps4Z1hGlgcGV7jBFlpr9tPYdMlM+my4S1srmQ5a/O/w/6QzKbdMKWfKyV7crBzP9h6yc4=
*/