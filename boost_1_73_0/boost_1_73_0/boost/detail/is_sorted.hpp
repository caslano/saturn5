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
VAUAAbZIJGCtVmtvo0YU/c6vuHKlyl4RvI9K2+0+VOKQhoYYC+zdWrKEBhjCdDGDmCGPdvvfe++AE3uT1ebDOkpw7sx9zL3nnMHZjODZD/tYDoWD734S85vgB587p0Ur/+aZftwhSb5A/4OOG3w+IdUU7r2+JBN4ktcXGBuvZMj1jr4nyRPSbahI+jMl501CX9HSew7+M9nctuKy1DCeTeDFmze/whG8fP7yuQ0nrBa8gljzOuXtpQ3vcmP5vWQ3N47iH2zgGljlHARclkKBkoW+Zi0H/F6JjNeK58AU5FxlrUjxH1GDLjkUouIwCxdrf/6HDdelyMohzq3sQJWyq3Io2RWHlmdcXPVhGtZqkAVGwPi5UBpjdlrI2sH0HDRvt2oIQ0WwSklgV0xULMV0TEOpdaN+m06zrq3wJNNcZmqa7VrhlHr71anWWM2W3YJsNGgJneI20H4btjIXBT2xRWhsurQSqrTvy8KEdT6VLSheVUM4dBVc9UfgEA/dsmknNFi90PRQslaU7bqU24ON2NYhUNG1NabDtuC+XGLjbejqnLdmv2nELsvQZdPy74zsvvYcZI1VwciNwY9HkDIllA2f/OVZuFrCJzeK3PlyDeEpuPP1EO/cn58gNgRmbYHfNC1XWEULYttUgucH
*/