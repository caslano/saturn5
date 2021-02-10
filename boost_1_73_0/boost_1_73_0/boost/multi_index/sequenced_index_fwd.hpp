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
dZr6SiqXbgaTi9H1hG5Or65Oh5NbGp3T6fCWwX4fDM8QegllOYn7LBcKynOSiyyWIix1/nWvTu0nmQRxEQqqa6EQqnoNpCgUEV2c/tH3Lke908u+d1H7iajiPIrTwIcD5ifUgftMQLSlOQ1iTJEglNtAg9EOiEy3ARD+/yF+3htOLncQoiDR8f8Jcj3ue8Px+Om6R4nKcgjvMvaury7P+h+vP7EqEGQi6HP/syF5w9FZ/3ww7I837agvxCIU02LGzqvQZKI5TdHTvFXuZ0hDh0lJFCIBotCDrdTMw6fPq/zps7gP3NoL7QZ5VaBJarkQSz+mpl42an+CUUYOA9MRdRv0p5Ec9yfeeNT7vX91NRw5/cHwj9PLxqE5yoVGxlNrj78+bjroZjBkGZA7TWZt0o1MVBp8L68Cz+bi34VEVqIcUPf4jYWv0DngpbJG9DwXoryKBclSXB11yMWRpJqG15eXtkb5wNSmj4OkJRaZfoAoJNs0GN1U6i3M2oYAJcU4U8Htw5StioXIaIW6SQuYRUoms7iyom3kO9ZR79hTay+xmOPsdbtdOLN1opfgDxr0gZyzm9HVWcNxnDBFIxKN8rjg8w4LtLuNbYd2S3/aDFiTS7Nt5DniHGmOMCF8h7XHWm2ZypBWvtTeQpks
*/