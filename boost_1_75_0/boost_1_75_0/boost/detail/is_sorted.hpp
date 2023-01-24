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
a3yqyzxcTWqGHHIosZF/JFGvnrmTqbuBIcskhGqCgLwnLfrG4PWmn5shYNh+f/YVVMEDNv5Fwq814OeOsWs+GWBdaEKq7U7vdtx41ZBZsd0Oki1+8rW0VITx/XCZG7BANGSZv/1y3YP4+qep7MKbdrWNjuIBXJnnNXKf/hBsk7N9sxRjtAUqicdj/q9HuEjSDsZrCCti+3ll/9YNqczFLuiDl/HkcRpf+QWZi5T6+hD1c3Wq2JTPHDh9dmSrwTnon3eaf9Uo7HzYqLestMSkmWmv1HK16my1XFg9V+ZgZKqkanzhFF/OOnuijf089ECt7oiZJUJrfgAOotLe1n96kPvBB1BO6RJCTrT5PUkukxxH4EstOwT2fl5bVmTKXDZ+OCdrSeP75S1Tak9nfPtLsbBSkLnSqFz+PohFd3bFwcjSHNjajHmZgDarigYIclLi0sdZl+LLGa6xx6SayBcXQ+FtCTaj49LB7/XycSDPp3oGx44KkR1WUaD4QONoCso956goXr0EW7mqP5DznQmVXJkJ+axBOQGazmjOJYRhR8zdxkW5Io5ELyzpPhrbA3uvE4LVD6KbpzCQ4DtN4ueU8pg0tsgOe5KFWGDRrPxFRqG/UPdX8RQCGmAXnkrfif1134h288RJS2TZXv/QlAmaaDTAlDqrbgONVHS8/54cGnTNOCHZ8aKASaPjTWpH2IcdsHncbs/Ty4zcb+nG
*/