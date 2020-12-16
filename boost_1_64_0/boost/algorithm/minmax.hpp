//  (C) Copyright Herve Bronnimann 2004.
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

/*
 Revision history:
   1 July 2004
      Split the code into two headers to lessen dependence on
      Boost.tuple. (Herve)
   26 June 2004
      Added the code for the boost minmax library. (Herve)
*/

#ifndef BOOST_ALGORITHM_MINMAX_HPP
#define BOOST_ALGORITHM_MINMAX_HPP

/* PROPOSED STANDARD EXTENSIONS:
 *
 * minmax(a, b)
 * Effect: (b<a) ? std::make_pair(b,a) : std::make_pair(a,b);
 *
 * minmax(a, b, comp)
 * Effect: comp(b,a) ? std::make_pair(b,a) : std::make_pair(a,b);
 *
 */

#include <boost/config.hpp>
#include <boost/tuple/tuple.hpp> // for using pairs with boost::cref
#include <boost/ref.hpp>

namespace boost {

  template <typename T>
  tuple< T const&, T const& >
  minmax(T const& a, T const& b) {
    return (b<a) ? make_tuple(cref(b),cref(a)) : make_tuple(cref(a),cref(b));
  }

  template <typename T, class BinaryPredicate>
  tuple< T const&, T const& >
  minmax(T const& a, T const& b, BinaryPredicate comp) {
    return comp(b,a) ? make_tuple(cref(b),cref(a)) : make_tuple(cref(a),cref(b));
  }

} // namespace boost

#endif // BOOST_ALGORITHM_MINMAX_HPP

/* minmax.hpp
3dY/f7QwjGCsemWx0Sg1AouMvgZ7I4GjVxYCLxX6+GJoaLM7iQc55UW0/xXfLCUmPyD0WGTpi5mW5oxiVFa0ThnUOqUY1SpRpzGmwGg0sAK6oZGDdkq4Pw5NuRpJquI2iAvSiiIWsQMEKzum93OfhvYcyYTqnUp0luO4XV560p+47Jp3tMh2IJDBmyBCIsF8AIkkeBltmyUocuxbd36FbbsaksfxPdOkH4v7n9CRHTSkhQSvkJ+gPAf4F9YSHZlJQbVFCW+zzYJ5DFWY5IU2+FSmIK+PcQYzPV71OaILAdxIxnuf/Qy5YHTswjZDPleOjbBF5UJdLsaVxxjcWmH7ygnoVwzSYq7aEKbE+cR/ZRg1EfSqa5dc3ka2/hwOih91q7pNxTmsUNTWgaQvIxyeA8XJWL6Shxi7fMMrC6fdoVehvqwJ25hSpD3yIrK5xey7eQLf0JI4b65we0LBgSAZEAYIomfYa33MoPJVVW4ldmGjvswb1xv9NbuUZ7D0NirLopUItjmoobKQa4yeyGXZWPApRMc+nvVn/A9i9rCxyeRNl3uMUeBNUQncaWZx+eUWd5oJ7oRwSTMFdxrE3Invvp9vjLpx+BRiT6MEe3Im2RNYGc6XEN1sNIllGXMi5kkflx0d6f6Av/9eUP+V0A/uKuBglDuW2ctnw5QPI37ZjDPkhcJ+6CrXvHW4q+XKPrm0E6Gvg9gPxCptiZ8vpdVKWbdM5yETRcPyiO3ayKgyFKCEfigVGTWcHk+IjLqAfk+MjCqn3/zIqAvpt39k1Jfod0Bk1EX0e1Jk1JcTX1pqGjLlhpET8cMKyoE5aBkX+MSTK8CKSF865DnSJo7ojsykuxzH4mzmWBzajYy188csPY5k/p4dGZuDjw766OCPuamPeQL2sU5Zn+DSV0QmuOis79g+dOjMExnbl+JrTXCzcDz+5eZx/yX3P3/HA4bTYrjsm8IzL3fmCpc4uAoWBW+Bk2D0mZXbGyodh/62+LGGSteMS0s9x7ADavq/Psu1o+4NHKKx/q+WmpdaypvTYLHIqup7hZUjRCbyBIkO2TMi5qopb6ySjJH50HiiYz362IlKPHGKDe+0YiZmWkacc4YWgzEibFRUnTw6ZrfRJbtVHlValfggLzfDdu/E9hgqXMIU6N2AdJgAE234JOiKF4qrEoUA0iILqUPxHvDXqNFsNTrSgX8e/CvAv0L8K8E/H/6BGt9U4h3ZNBN5R1RfQ/WsJ7NAfEu2qIQWEScgUn9B9N6JMJEiT2IiWmZaI04utI3kpqXyKTMgRue7OcJrxQHnF3H6O/CMmK+z7NizgsgBH3fpw2hwJmLpDQmFJ0UYuElToVO8QHhxgHaqusWLDGDrUjEa8UMnMZvw+xWHv8naUSpqpp1M2d8kglHiBUdKPeJJwmlx8ZSFr7LUGKAT4XPZ3QCJ2TBeUV5/A9KlVUjJ4QKN8biEl9xAUZwq9dcFxKl8BxLzghISPYjNBTiudOELEp04vksl/cv5iHpNDtL6BIsauXRzwLk+EM0vRlrfoLSCGpSaUNaDdKS5g3oLl23FuxyPO5HWDwVRCJjIx9sJKMJZT0Q+5/roj9muHCxqRVJ/lAMgtxUGpdXUmrTOveCufAT7RHjCeO2JyDEg6N9AABe95twb9FM1JwWkjWgfccHwoQBnWylvHfV4oOxfQYgqakIz9xR7kHSy7F+O4lIz6h3EUHwOeEQ5WOmc6+Nx6uopQX8digFdzr2A2Y6kU4P+Wu5pHVqV4kg5Td9AI1iMiDQoTU3WUFcHy0XrURapCNuINgch7XTpTZSVpdeQFK+jThShCF7wdIaInYCnM3mYiSyuL8HrWThIDRjPRqAf4MM=
*/