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
NvawnuAN0n8vN8O/c7oF/KlX1R0+8tuk5Qq/TVgQ7Ac0TZwhYf4klLwmBlRcSbpYKN2SbcAhdoeIQnP5zUYvPjwBT+fxiQ8CS02ECjfo+r/5eK6IQa5j/QGzeDim8K30UTLQrLBFiKTFKzHqEJSbL8utYeWEd7i0K3NqsYyv8YfhFjVTv0XNg1I3l+mRb9LmtMA//gvgT7K/DfxpQn9S/MmB/vClqT92HvsDcZr9EYFOtHkPVm55XmeGKRgVU0kbc5MIHbmYyNH8r0COVUZyfDHv3xawxswfg+9F/jCoGXFoAwnUo/ZzLcbaQ53r/4Y0PbxRds6Jnav6O/suif97KSc+krsFkbsVkftiGoq2RPPOgSEUQ+Y+GS4pc76QfK6ghMnLRcIgSugzWiT05EhPEAm42l1J6N79Oo6FEd2Rc3G1O5eLcQ0Vd9J8JoUFkrihIHdlefmhP3bolKPi00tUqx2nVn67ysGtiGx+Imk3ImkvIunAKjCaJIJOACaGAFD+GyU7F+G5XD4OXLXDFOIzEVMfMaWmstTEqrusygZmqklOKBiYqCa5sdTlBnCYNEAm6a5wHISTJlI5Dd5bB2DwVsDgzZODt2r2GTN0qF0+cS1Wtp63nQb5xB/D9xrltZ1Tej9eHf97TKoCVG/cz3RtZhuUx0O4y0kfjkfjuLfcrNLhSnJNnFlmyOWSUhNtCcgmJtkp22Dm6Qb5BYSnZHZQ7AtCNibezBJZ2VRd8LiYyTxVE3iUB/fpjZZCn7vvtqLPFc5ToM/l1vTZdBL6vBVXO30S4iV9BvkFfSrizPRZNuJM0wf5teAuhV8nzbK06E+SorM/PI9ns/zSQG3kxahgoX2gUaPfi+SZ3OJgybylFMq/u0aq8FAlFZ7ohh+Tum3ynRI9n3btzGDzLVBM0JWVPuwfM+FDvY7n53bVyuvZG62svFwGKy+XYsylGG6lkugduU8abi2R69lrM053PaNRKSyjs2cPv/HapAX5dF4A1OdnJ9ISurRbprC02kVMS9ObetRcDlwqoqKMbsavBR0BMsbvxbR1VTgjhAzZqMBoiI8bdTaPs/Ey0KYYaDNV0ubpItyoJ8sHSIpsAtYCOK7jlv0xP7D3v+VoTW/WoD+V0vfx9LQ5lF6I+3wmSQv35eI+j6Bc6zhaVb6amjOgQVGodLjUaO+MLvQKuTInCnK9MR9tc0evIKQbTbYwVz6bSPX8HiDVvUAqv27/N511aKz23niq32Ouge/9zaBlICGKQaQXuQC1mQS6E4G+GkFPN4I+B0DzOPaxVHXLyjMoEilLy9O3K0vLhqLgo94Y/dyfoL1/A3V2IBthkCrEshYvNmbmseti5X4dQ+VaQblmIlPcYpQmwp22Vjq6dku2WvenI4uM8tuxuTQJSFSrT6Jaw0BXVeZJZeul/Cmf8O6uyk1cLBrLx/8lKRbN1ce/8JSXEQX/dBP+mQr+TekE1dQ/inrTnnrTmYTSHoECKXV6pdR5cWCUQXAM3GQQBwNjjbmXGjudbRAnjSRJJZK8T5Li47skSeZLkkzxnzJJQtEncaGRPqlzLMe3hzq+rsDFFuPbU6apoq8MEf+3StmhEj3+1dRT6pB5/x58m5xkXm3EMtSBSZ1S2VpFFeGvB3MFpgwUXTxZKQpCzKW3hjVlgvQftyrtb5xkKaQk4N0lrQOz8sO2L6T3Lwi+tmAWTfvUVebHPK6l+7YrhN0265X2ubhHGUSZD0+SvU2nK+YxvEAHreMszJNscPZAHksIoQnhJZCpRcxS9NB2VgqGuEcE2Q3slNLA03KId950SkN8UnpcscC4CVH/ul2n7jB8M/YQaqMQtbWA2maJWhtELXAl7a6HJ6o=
*/