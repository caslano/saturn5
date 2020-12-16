/* 
   Copyright (c) Marshall Clow 2008-2012.

   Distributed under the Boost Software License, Version 1.0. (See accompanying
   file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

 Revision history:
   28 Sep 2015 mtc First version
   
*/

/// \file sort_subrange.hpp
/// \brief Sort a subrange
/// \author Marshall Clow
///
/// Suggested by Sean Parent in his CppCon 2015 keynote

#ifndef BOOST_ALGORITHM_SORT_SUBRANGE_HPP
#define BOOST_ALGORITHM_SORT_SUBRANGE_HPP

#include <functional>       // For std::less
#include <iterator>         // For std::iterator_traits
#include <algorithm>        // For nth_element and partial_sort

#include <boost/config.hpp>
#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>

namespace boost { namespace algorithm {

/// \fn sort_subrange ( T const& val, 
///               Iterator first,     Iterator last, 
///               Iterator sub_first, Iterator sub_last, 
///               Pred p )
/// \brief Sort the subrange [sub_first, sub_last) that is inside
///     the range [first, last) as if you had sorted the entire range.
/// 
/// \param first       The start of the larger range
/// \param last        The end of the larger range
/// \param sub_first   The start of the sub range
/// \param sub_last    The end of the sub range
/// \param p           A predicate to use to compare the values.
///                        p ( a, b ) returns a boolean.
///
  template<typename Iterator, typename Pred> 
  void sort_subrange (
  	Iterator first,     Iterator last, 
  	Iterator sub_first, Iterator sub_last,
  	Pred p)
  {
  	if (sub_first == sub_last) return; // the empty sub-range is already sorted.
  	
  	if (sub_first != first) { // sub-range is at the start, don't need to partition
  		(void) std::nth_element(first, sub_first, last, p);
  		++sub_first;
  		}
  	std::partial_sort(sub_first, sub_last, last, p);
  }



  template<typename Iterator> 
  void sort_subrange (Iterator first, Iterator last, Iterator sub_first, Iterator sub_last)
  {
  	typedef typename std::iterator_traits<Iterator>::value_type value_type;
  	return sort_subrange(first, last, sub_first, sub_last, std::less<value_type>());
  }

/// range versions?


/// \fn partition_subrange ( T const& val, 
///               Iterator first,     Iterator last, 
///               Iterator sub_first, Iterator sub_last, 
///               Pred p )
/// \brief Gather the elements of the subrange [sub_first, sub_last) that is 
///     inside the range [first, last) as if you had sorted the entire range.
/// 
/// \param first       The start of the larger range
/// \param last        The end of the larger range
/// \param sub_first   The start of the sub range
/// \param sub_last    The end of the sub range
/// \param p           A predicate to use to compare the values.
///                        p ( a, b ) returns a boolean.
///
  template<typename Iterator, typename Pred> 
  void partition_subrange (
  	Iterator first,     Iterator last, 
  	Iterator sub_first, Iterator sub_last,
  	Pred p)
  {
  	if (sub_first != first) {
  		(void) std::nth_element(first, sub_first, last, p);
  		++sub_first;
  		}
  	
  	if (sub_last != last)
  		(void) std::nth_element(sub_first, sub_last, last, p);
  }

  template<typename Iterator> 
  void partition_subrange (Iterator first, Iterator last, Iterator sub_first, Iterator sub_last)
  {
  	typedef typename std::iterator_traits<Iterator>::value_type value_type;
  	return partition_subrange(first, last, sub_first, sub_last, std::less<value_type>());
  }

}}

#endif // BOOST_ALGORITHM_SORT_SUBRANGE_HPP

/* sort_subrange.hpp
UBCYJP0aT6R4Uru3XRiMzVm67uooyBOIOr3f/Cmky5q6KNRzoa8SDvYI7EJXF9psl6nNEsEKFGJ9K3C3T1xiIGbKfoE72D6cnQHWaw9gC+qROx47yGr3Omen0PEPUqEEcEZdPyRwxuYDvjMjkY6xrG9Xzvo1LaZ5usbRbSyRMelA4YMdL6g0hDV6nOAGzMiPUvh0/Rmn7hGqRSMG+5Irrz2TFSnUwlUX0Sg+3bCgnRqo+FMFKQgOc1kPaERT6CgQdo3nnLV4keqSyk5fDBUwAGIAFsfnBzKBY1Ovovrr4vF8jArDDxqcs/XJ9cid1KMEsFkWsESLjQdWv4vsSSWJwaTPDObWlW8NxjM6CvhY9+sLENGmgG9tzvmmDuJKQpifhBDZ8CXfhCvLggsfafxqAEmuHPvhg33W/B0ABWLRrPYtv2VGAsj86N/8vb/Y/qFkL6aaa9B1WVrvr0O1gKdBji35IB+a5t5A7EcbMr9xS7whHyrvAX+Dyc4a0B3Sp+LobDMhvU4HMfsbhEqfjmt9BX1uIJyzUplEMqnUOC0KBRg8AfzgW9rQWJAgR7U16GUdK1vQ50cM329IDzGKhcpmBxKJRubsueNBNFhs6phpDdbQ59Ov+8nXpTrRpEc0qTNtucreOShQpJOqfFJaW4H3lv4SuqG9e0O/bX5jDA3CERqaNGbJHnTuMC1N/etLSzH2h21q2b0/KoENo3tL+8968j2T3o7Q2Dzf9lcxaL0bk+fEh7e8uiEr65SInUi+R6ONKI+egXyXg7TfeXzjVrQKDo6CPN1Bznvv+flpwdhjN0149mWyoAEyQaqB2JzA6UP+7o+n0alH0CmxzOgPjKGVYuCJsXW1ADC0+Rqa+U3R956RnXWpSSRUacpSkw2w0OjwJx75UHYKtlPPtNzVEo/nATKAUnfFVTc5CQQGEWRKJeNuQAaYvvuK62HZCa6dsmOI1mv7E3AxXAyz3ZCxUc5dTAMuG8AJqIDINIjyAJEAhfkxGmIovtV6zdx5sk7AXnzvU9/oagFgm7aefcgZn1N33s4LXhQ2CHsagP0FgPmVtl8IAEGkKeiyBXRP9nOMZeiA1jTg8pLAiUFMQucW0CGAHwHY1YpJmERXfwDKeMq6/97xXYJUk80FpNagcwUM5BSbXCJjGNpYAcBoXbSkbd1QMXbpDcXREBHbd1Y/0CF4DNqwLB5k2rB5Ajj8V6CXoXKYNgbBPskWj3Fk8QiwyWMQmURkICKKjGzyaE0zeRSyyePg7iOZPLCIVPBKd6hO/iw6Zv//7/9/H2mfiT9s2Wee23IY+8yP8nrbZx669fD2mVfuS7PPPP1wN/vMKTf0ss/0+8nHt88Q/OKEsC0Jf+dmhp/PaQng9+T2Br48enjgV/8gDfivzQLwhUngJ13PwPPpJIL8cuiVdJj42MHuFv/o2wyxCDypnwB/EEQEzgnvzawe3pFFPznLAifbZxu18HHHVUTyQvZwA9fy1sJY9NT75EU03kzmY1I2+q10KdEc/OQL8w4OpR7PBePK4q+Yfw1UKqNBHpQKzhO9xKUsPsP8w1t+3VH9S0RPb4oJ/dvGriXvobvkE1iJgzj2pQy9txP9UsrfqMpNrOiACeO0jksxJomleEaEb3tDDsFi9bRZ8b6hSNsS4ozQLiW8de+MvsgOWwM7sSMZOcgKkf8FMlPELrYnpqOm6GlpB3LBq8s+7qXmPe0NO1Dj+IUt1NO7H7Ko8LZNyVn0HCPvWRG6AaMdfYFDLqixyXCA/CsHcdCQ1ki/sTtcSvwDSUN6Ddsb6rXYrPybU+dXK4FEbD+XuxdUISb6VQ5WgJG839RAKw+YGmjlQdaGaK8cL4fwmV9K8GI=
*/