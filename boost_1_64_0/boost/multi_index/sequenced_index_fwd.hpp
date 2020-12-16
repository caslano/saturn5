/* Copyright 2003-2013 Joaquin M Lopez Munoz.
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * See http://www.boost.org/libs/multi_index for library home page.
 */

#ifndef BOOST_MULTI_INDEX_SEQUENCED_INDEX_FWD_HPP
#define BOOST_MULTI_INDEX_SEQUENCED_INDEX_FWD_HPP

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/multi_index/tag.hpp>

namespace boost{

namespace multi_index{

namespace detail{

template<typename SuperMeta,typename TagList>
class sequenced_index;

template<
  typename SuperMeta1,typename TagList1,
  typename SuperMeta2,typename TagList2
>
bool operator==(
  const sequenced_index<SuperMeta1,TagList1>& x,
  const sequenced_index<SuperMeta2,TagList2>& y);

template<
  typename SuperMeta1,typename TagList1,
  typename SuperMeta2,typename TagList2
>
bool operator<(
  const sequenced_index<SuperMeta1,TagList1>& x,
  const sequenced_index<SuperMeta2,TagList2>& y);

template<
  typename SuperMeta1,typename TagList1,
  typename SuperMeta2,typename TagList2
>
bool operator!=(
  const sequenced_index<SuperMeta1,TagList1>& x,
  const sequenced_index<SuperMeta2,TagList2>& y);

template<
  typename SuperMeta1,typename TagList1,
  typename SuperMeta2,typename TagList2
>
bool operator>(
  const sequenced_index<SuperMeta1,TagList1>& x,
  const sequenced_index<SuperMeta2,TagList2>& y);

template<
  typename SuperMeta1,typename TagList1,
  typename SuperMeta2,typename TagList2
>
bool operator>=(
  const sequenced_index<SuperMeta1,TagList1>& x,
  const sequenced_index<SuperMeta2,TagList2>& y);

template<
  typename SuperMeta1,typename TagList1,
  typename SuperMeta2,typename TagList2
>
bool operator<=(
  const sequenced_index<SuperMeta1,TagList1>& x,
  const sequenced_index<SuperMeta2,TagList2>& y);

template<typename SuperMeta,typename TagList>
void swap(
  sequenced_index<SuperMeta,TagList>& x,
  sequenced_index<SuperMeta,TagList>& y);

} /* namespace multi_index::detail */

/* index specifiers */

template <typename TagList=tag<> >
struct sequenced;

} /* namespace multi_index */

} /* namespace boost */

#endif

/* sequenced_index_fwd.hpp
5JgiGWB7m+91NAVNSEjf10E6zTrSz5h0Qx/6p0mHrQHpL8/dJul6/QK3MGNkzzAuaXo8wrBTD0H6awskbu/ZiQpDaNhfXmbUX5R5Xu6WV/0eWdcfravvQ1onVjfAfCyt+YvsLKZT01FFWBzMy0GwutBFGZPjNWZ90N1cXGvIeFMLHX5OdYd9cGqixgCR1OUX8DsyoV0l3Q60E6uUhraaHRVN5+X62r6zE75v9FaqMYpvxifG5uZ6K+vyZ3BaXjGD7jCcz26g+3L39LqUJxfGnm6PkrVHIoIs9fMgu2q/LHV74HtA95FE3v7ADixwNyem9H2+O+v7lzTd6SALLaf05c7ido6/aWKfTbEzaez4lhunCjt1qEajbY1iDxV2aflJGIkTqxIdAcfi/abUX/InrlhnYA93XNqaDyvesHuazC2fgTM/pecNFmRh8XvZge+q303LjTl+X9w2/L4kJe3FPUb9XYKpnJmJ+rsEw3eML729/r6mLnUN6Hz3W02DsODEXnJuB/0+d3Kd2HGP7QQadoGhD4EX674hB+oJafvROvTi0jCu+stGYuQQ3+g/nsZgf8lo7MKa+ucYzqW/4H0vc1Mrzor/WleI9VrE+nIpfFv2Kz/Jxbw87e0PHUZJb1f3AEemG9I34/1u5xb3O1BlcUWMTe+VfeHX95R97vMgS30faBvAb+D79/G7NBidlBPnQOlHT9gr55GfmTT9/BrGaoXZRTBy+tzorS/L85cxlLG7lT4HmUUZexTmJDxUqSu3J++rn1Z7sVuPjdXcG2qN+V21xmRFflStMRj7UfbfH3b0Lm1OTtHLON/dfFtFa26ryBozXmN6A6TSvd7shEk/OT/YgCma7/XObwdca/dDm8XunYgZ1aUQW04idlRXHcZUvQZgOVCVoab/85pIZ4IG8ycBh2NrfRfgHtfbWJXXCuq+8m9Z7xc/Ce00t9qDdpqD3Q6kXdmLZj9l0EABq3k7UmNcYvTp6Zmad5ukvcKkEd4JSf8Opx84WPOu3FnuTT5t0Ajvdsn7Xka/x6xOd4ekve4zBo3w7pT0yc9S+oHp/TXvpKQdN2k1L/R72L+lii77+SnpM4ZXGWIucAwWn2IucwwWk2J2fY5hsDgUs49ieJHUuLqWLFO1eYA9wkns92fk2PlRNXY2piQfDtGqLIi7NAIH5aG4Y+PtOCgTxX1wBA7KRXH7JtpxddlwfD9d4wACyh4UgNAP7zDokHFC3zNp0HU/1GvYNQw6ZJTQP3Etgw4ZJPS7Xtukg12LxENWdEVcWJfLET3PmroOp81NDXWpGapLzT0OVg6253yFv5PsOZv7v7N/JntS3P8R/t806FW/0/TddP8n3XNvVJtAKuNiSfJANm1oz44oXclAEE3rvE1xy9LmiOXpasxx18SgKNQv1w9RzFLv1NKQf2r/TrLP5uVBHeTYTrLf5pgv6Xfonxyu7ft9S6ROkgdZ4QvQ4e43Q36n27+swc86/HThR1lWB/izrICH4Hc/ctJ/KgX25FDcAvz04efxKHijSgcxJ1RC5P/FWOdB+r0GLY96h5zYnh27ohKOWToAv6Ck1H/n1VfMkn7T8XJtj6ZynUC4iZ04flgouY9iIrOmyPlGwmHG/j5wVWJOoBh8Z05tFD+ubZx0vpnYBt+b3QTt++NAJ12M+o/bjjTajVHHGNvB6XQ0oO5MMMivaTsJzRhOOF9eg2CQTPSlaym62cVRF74xtBu50+LFsjNkTvjf6sK0ns/X+5CV9R5+X+7U3+VHyYRzyr5bqTGoVUU0KuT63OETfN8ehpltxe5Vx/Ju27f/pKOTwys0SJ/qcLppA3mFQTdtILu2cbppAznN6GgDwXXy2eM=
*/