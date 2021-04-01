/*==============================================================================
    Copyright (c) 2010-2011 Bryce Lelbach

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_DETAIL_SORTED_HPP
#define BOOST_DETAIL_SORTED_HPP

#include <boost/detail/iterator.hpp>

#include <functional>

namespace boost {
namespace detail {

template<class Iterator, class Comp>
inline Iterator is_sorted_until (Iterator first, Iterator last, Comp c) {
  if (first == last)
    return last;

  Iterator it = first; ++it;

  for (; it != last; first = it, ++it)
    if (c(*it, *first))
      return it;

  return it;
}

template<class Iterator>
inline Iterator is_sorted_until (Iterator first, Iterator last) {
  typedef typename boost::detail::iterator_traits<Iterator>::value_type
    value_type;

  typedef std::less<value_type> c; 

  return ::boost::detail::is_sorted_until(first, last, c()); 
}

template<class Iterator, class Comp>
inline bool is_sorted (Iterator first, Iterator last, Comp c) {
  return ::boost::detail::is_sorted_until(first, last, c) == last;
} 

template<class Iterator>
inline bool is_sorted (Iterator first, Iterator last) {
  return ::boost::detail::is_sorted_until(first, last) == last;
} 

} // detail
} // boost

#endif // BOOST_DETAIL_SORTED_HPP


/* is_sorted.hpp
8sqlqYRnpanL2Zzyc/WF+D+p3REKx+ZtBgyF3rriT6E49p5j1O9kXGMRoL9NNGUR9kK6G4HsHqTZqyMNVj3OH+6eS4fknI8qW+db3TebD7KZi/F3NkXOquhCBNq+nSCEeZ6B7qlYe+rN+vKVHBzx/svGwDGTG9B0WVXjtWAiUwO0Wk56g4XeDe5TYtazPxoRRSSH+xPlEXq2TrDxKLzMM1DzpY0MNSIcW2RXyyx8pNQt/HcHFU93D6qezNARRpOQZV3a4NlebaCZH8V/lCPtfswta89BCZccl5jEPGC4Bgxc1xSrQOM1b61z0ELwdCbsBTIO0Cx1sX+kcgjRU8GH2t7E2bIk82GQ4SsxJ89T68lkucwU0tBZKYeBIYn3fj12OP/bHXmvcpjcFDUAZ9Rixhr7Rc92wvNJg+3JG8/j+3Yg2koOa8WIU7pspohxyl6JUgT87FtUWAK9QbCqunwndqwW4vVLLE7N78qRaVSIMS1ExqbASC2FlgMpLAbG9f1+YP0D1A684xSBy7RdPkuzTdDEbgsfNdA6VvuFBBUcTRm7QfDMjfb5/uvMCw==
*/