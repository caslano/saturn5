/* Copyright 2003-2015 Joaquin M Lopez Munoz.
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * See http://www.boost.org/libs/multi_index for library home page.
 */

#ifndef BOOST_MULTI_INDEX_DETAIL_ORD_INDEX_IMPL_FWD_HPP
#define BOOST_MULTI_INDEX_DETAIL_ORD_INDEX_IMPL_FWD_HPP

#if defined(_MSC_VER)
#pragma once
#endif

namespace boost{

namespace multi_index{

namespace detail{

template<
  typename KeyFromValue,typename Compare,
  typename SuperMeta,typename TagList,typename Category,typename AugmentPolicy
>
class ordered_index;

template<
  typename KeyFromValue1,typename Compare1,
  typename SuperMeta1,typename TagList1,typename Category1,
  typename AugmentPolicy1,
  typename KeyFromValue2,typename Compare2,
  typename SuperMeta2,typename TagList2,typename Category2,
  typename AugmentPolicy2
>
bool operator==(
  const ordered_index<
    KeyFromValue1,Compare1,SuperMeta1,TagList1,Category1,AugmentPolicy1>& x,
  const ordered_index<
    KeyFromValue2,Compare2,SuperMeta2,TagList2,Category2,AugmentPolicy2>& y);

template<
  typename KeyFromValue1,typename Compare1,
  typename SuperMeta1,typename TagList1,typename Category1,
  typename AugmentPolicy1,
  typename KeyFromValue2,typename Compare2,
  typename SuperMeta2,typename TagList2,typename Category2,
  typename AugmentPolicy2
>
bool operator<(
  const ordered_index<
    KeyFromValue1,Compare1,SuperMeta1,TagList1,Category1,AugmentPolicy1>& x,
  const ordered_index<
    KeyFromValue2,Compare2,SuperMeta2,TagList2,Category2,AugmentPolicy2>& y);

template<
  typename KeyFromValue1,typename Compare1,
  typename SuperMeta1,typename TagList1,typename Category1,
  typename AugmentPolicy1,
  typename KeyFromValue2,typename Compare2,
  typename SuperMeta2,typename TagList2,typename Category2,
  typename AugmentPolicy2
>
bool operator!=(
  const ordered_index<
    KeyFromValue1,Compare1,SuperMeta1,TagList1,Category1,AugmentPolicy1>& x,
  const ordered_index<
    KeyFromValue2,Compare2,SuperMeta2,TagList2,Category2,AugmentPolicy2>& y);

template<
  typename KeyFromValue1,typename Compare1,
  typename SuperMeta1,typename TagList1,typename Category1,
  typename AugmentPolicy1,
  typename KeyFromValue2,typename Compare2,
  typename SuperMeta2,typename TagList2,typename Category2,
  typename AugmentPolicy2
>
bool operator>(
  const ordered_index<
    KeyFromValue1,Compare1,SuperMeta1,TagList1,Category1,AugmentPolicy1>& x,
  const ordered_index<
    KeyFromValue2,Compare2,SuperMeta2,TagList2,Category2,AugmentPolicy2>& y);

template<
  typename KeyFromValue1,typename Compare1,
  typename SuperMeta1,typename TagList1,typename Category1,
  typename AugmentPolicy1,
  typename KeyFromValue2,typename Compare2,
  typename SuperMeta2,typename TagList2,typename Category2,
  typename AugmentPolicy2
>
bool operator>=(
  const ordered_index<
    KeyFromValue1,Compare1,SuperMeta1,TagList1,Category1,AugmentPolicy1>& x,
  const ordered_index<
    KeyFromValue2,Compare2,SuperMeta2,TagList2,Category2,AugmentPolicy2>& y);

template<
  typename KeyFromValue1,typename Compare1,
  typename SuperMeta1,typename TagList1,typename Category1,
  typename AugmentPolicy1,
  typename KeyFromValue2,typename Compare2,
  typename SuperMeta2,typename TagList2,typename Category2,
  typename AugmentPolicy2
>
bool operator<=(
  const ordered_index<
    KeyFromValue1,Compare1,SuperMeta1,TagList1,Category1,AugmentPolicy1>& x,
  const ordered_index<
    KeyFromValue2,Compare2,SuperMeta2,TagList2,Category2,AugmentPolicy2>& y);

template<
  typename KeyFromValue,typename Compare,
  typename SuperMeta,typename TagList,typename Category,typename AugmentPolicy
>
void swap(
  ordered_index<
    KeyFromValue,Compare,SuperMeta,TagList,Category,AugmentPolicy>& x,
  ordered_index<
    KeyFromValue,Compare,SuperMeta,TagList,Category,AugmentPolicy>& y);

} /* namespace multi_index::detail */

} /* namespace multi_index */

} /* namespace boost */

#endif

/* ord_index_impl_fwd.hpp
JrPqg9Ji1iNmi4DtP5EY7AoMalSuw4ySat07RaQlIEYRGEz1AgO+I+Z4CvY5+zs+E6salQ3Zv337vubyEpGfiJibRI3BWi8wYAu2sAjYe4ZlPpoMDC6SDed//NanuvdS0Z7qxJsgXvd6LzDg8yBYJNyxBjL58a3I3VQrG9776Zq+uvcyUe7k/kzTslB4sQc48J2xd6Fg7KRFProOslAnG+5aUXkrtKEo8Md8CAFlJ3Heb8ATMgZvuykYDPIf9FF3YFAvG1p+m4g86dNEVSbqivn0uUp0dj8+XxKekNNWNATcZ+zzfeZsaYKaC0274e1fLgYl2HpxsRdzge10ySJg54Se4aMFwKBBxeEdOOUn3XuFmJmGiF2/xqD/FA8wGMdVdN8iYNsIM2J7honWnmF6l5palMC6Z+h8RM49gyHgXh+vlesCMFC8itXDj9S9V4oO5z4k7KQmL+QgHIkyg2AoGN/ylT46AxhMkg0ZPw25UXN5lWjMtGuHFNzngU7kO2WJp2DHn9X66AH41ibL7y2bX0Iut6vF7dmIOfHLfmUrbmI8Y8ATcp60WCTc585RH10LWbhYNhz38NIBiDYQW8H1EsyHDazzoVz+lNSODeUOHcoUsW+RcMdg1fjMmdMU2bD1wlzE6F4jCoHDQuCw5BJ2HPh2DmZ4l14s9dFM2MuXyIbrTpl9su69VkTTYS87cXis+wb1gKy7hngC9n2F82P28qWyITLtrom6d4bI9MXy3QbU38zhtJfVI3Jay/b4xqd4ZsxWvsyylWeKNvDflKFt5bWstrJ8Psac32Z497nzKT46G3NgqsoRcH3iWN07S1Aq/Gi4qzHmMvY5wGclm+FdfvUTfJQC/qfJBv9b80bq3uvER04cKmqxj2lmf/9sEdlmePf7P85HJ0D+L1cN569t0b2zRRP2SQWIy2+Zyv7++XYIZnjXGnhsbH9whbU/aO4Sg5fHuj9QD8i4OzDDu+KvJP/3gv/psqH44tsP0L3Xm/irtbAB2qexv3/GnYE9vrEBDvfRYYg5uVI29M5JQLWPG8TARHiOUjT/eZez888Yf2YRsM/VDontja6y9kY3iikp8Bcl671R4wPsOpBxZ2TGt2WgT8wGuFo2rD4jgnrLc0RrT5wj9ND7oujvnPsi9Xysu6J4ArafJN1Hy7I0Bk2yYe2sQ+7QvXNFZlKstmKqmg89Ge8mhSN1xaoWMF/i/y4UzFqQ4KMDoAuuUf6y3S/cqLm8SdwXd2/Tp/BiXQvkE9bV1w7js4biCdj7gT8zTI3Ba2XDUwe886buvVksSkb8TZLGoJUdg0g9o0UYT8DGYFuGicueIRse/2P0Q9CC5mw1KPRc2NCLeS7URpmngiFg+0gkBocDg5myIaf8uWd07y2iv2MXOb72NGY5UHlCeQXBULDOVrdm0Br4y2bJ76J1M3/QXN5q/ESLHTnozRljIJ/wognhklBlXTUfBhYFc0fn5wzqnqYxuE42PPfCJMRm3ybmwT7KS9AY5PRhxiDKvi4YCpZ9sCaDOnCHe7ZsuHbGFkSl3y5eAAblwCCfG4OasWW8EBgCto34dQZdmaQxUPuCt4Y7u6M7xAjnPA1zodwDDA4cwQ2CoRCzkT7LoEpgcL1sOPH5lkrN5Z3mvlIbMGj2BoMw04WdeAq2TpTBhq/10BjcIBs++mfzQM3lXWJOEs4QgMFibgzGdv5ewuUyc1Mw+uC5DOqDtfFG2fBq+3cn4fa+2AA5WAI7sYPbRup8QqYw/bjx7RpxGbQLfGZzZEPzgOKlmsO7RYFzb09+Z3buGZj5j4SY9aEhYNuIizJoV2AwVzb8edb5z+ree0QbNGMB5kEH9zyQjzicHQRDIeY=
*/