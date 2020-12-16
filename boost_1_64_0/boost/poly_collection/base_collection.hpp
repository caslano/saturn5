/* Copyright 2016-2017 Joaquin M Lopez Munoz.
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * See http://www.boost.org/libs/poly_collection for library home page.
 */

#ifndef BOOST_POLY_COLLECTION_BASE_COLLECTION_HPP
#define BOOST_POLY_COLLECTION_BASE_COLLECTION_HPP

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/poly_collection/base_collection_fwd.hpp>
#include <boost/poly_collection/detail/base_model.hpp>
#include <boost/poly_collection/detail/poly_collection.hpp>
#include <utility>

namespace boost{

namespace poly_collection{

template<typename Base,typename Allocator>
class base_collection:
 public common_impl::poly_collection<detail::base_model<Base>,Allocator>
{
  using base_type=common_impl::poly_collection<
    detail::base_model<Base>,Allocator>;

  base_type&       base()noexcept{return *this;}
  const base_type& base()const noexcept{return *this;}

public:
  using base_type::base_type;

  base_collection()=default;
  base_collection(const base_collection& x)=default;
  base_collection(base_collection&& x)=default;
  base_collection& operator=(const base_collection& x)=default;
  base_collection& operator=(base_collection&& x)=default;
   
  template<typename B,typename A>
  friend bool operator==(
    const base_collection<B,A>&,const base_collection<B,A>&);
};

template<typename Base,typename Allocator>
bool operator==(
  const base_collection<Base,Allocator>& x,
  const base_collection<Base,Allocator>& y)
{
  return x.base()==y.base();
}

template<typename Base,typename Allocator>
bool operator!=(
  const base_collection<Base,Allocator>& x,
  const base_collection<Base,Allocator>& y)
{
 return !(x==y);
}

template<typename Base,typename Allocator>
void swap(
  base_collection<Base,Allocator>& x,base_collection<Base,Allocator>& y)
{
  x.swap(y);
}

} /* namespace  */

using poly_collection::base_collection;

} /* namespace boost */

#endif

/* base_collection.hpp
Td6C9inWJffAj8hbrkk+9Xrkw3DChxiSU65F/q/rkHdPsRa5F4FJa5CXtQZ546R1yAcwNGkt8gjiU6xDXocGdKIH/ZPWIA8iNsUa5GatQd40aR3yQTjghhcBRJHGGAooo+bLhBnt6MIAhuBCBHGkkEf1VwgnGtCMTvTDCR+CyCCHIgx9hA8WNKEVHehGHwZhgwNueBFAGAmkMYYCyjAtp3ygBe3owgCGYIcLfoQQQRwplGA8n/CjAc1ogxXDcGIEPgSRRAY5GL5KHNCEbtjghhcBRJHAGAooo6afcKIRXejFEOzwwI8QIogjjxKMKwgj6tCAZrShEz3ohxXDcGIEo4ghgxyKMFxAmFELC5rQig70YRA2uOFFGFGkMQbThcQB9WhEC3oxgCG44EEIEcSRQhZ5lGAcIB5oQBs60YN+WDGMEQQRQxI5FGFYSdjRhA70YRAOuOFFAFGkMYYCTBcRbjSiHV0YwBDscMEDP0KII4U8SjBeTPqjAc1oQyf6MQwfgkgigxyKMAyS3qiFBR3oRh8GYYMDbngRQBQJjMG0inCjES1oRxd6MQQ7XPAjhDhSyKOE6ktIazSjDf0YhhM+BDGKGJLIoIjaSwkvmtCKDvRhEDY44EUAUaQxhjJqrJQPNKIdXejFEOxwwQM/QkghizxKMK4m3KhDA5rRhk5Y4cQIghhFDElkkEMRhstId9TCglZ0oA+DcMANLwIII4oE0iigDNMa4oN6NKIFXeiFC36EEEEKeZRgHCL8aEAzOtEDK5wYgQ9BjCKGJDIownw5YYcFTWhFB7rRh0HY4IAbXgQQRgJpFFCG6WvEAY1oQTt6MQAXPAghjhSyyKOE6iuIBxrQjE70wIphODECH4JIIoMcijDYiAtqYUETWtGNQdjggBthRJFGAaa1pDva0YsBDMEOF/wIIYI8SjB+nfCiAc3oRA/6YcUwnBhBEKOIIYkMcijC/A3CjFZ0oBt9sMEBNwJIYAwFlGEaJsxoRDu60IsBDMEOD0KIII4s8jBeSdjRgGa0oQdWjGAUSeRQRO03SVM0oRUd6EYfBmGDA254EUAYUaQxhgLKMH2LMoJGtKAdQ7DDjxAiiCOLEox2ygea0YZO9KAfw3DChyBGkUEOhqsIOyxoRQe6MQgH3IgijTEUYPo24UM9GtGOLvTCDg/8CCGFLPIwXk0YUYdmdKIH/bBiBD4EMYoYksggB4ODsoBaWNCEVnSjD4OwwY0AwhhDAfXXkJZoRxd6MYAh2OFHCBHEkUIWJRi/Q7hRh2a0oRM96IcVw3BiBD7EkEEOhmsJNyxoQiu6YYMDXgQQRgJpjKEAk5OwowXt6MIAhmCHCx74EUEcKWSRh3EdYUcDxv/VoQP9cCKEeBVlmN9ktvM7oKaHOT5AevJ6jN9rj/Cb3wZeW9n2PEY84YeZz/Lj79nW7yNs8PJ6lHNyxxGf9xO3RsLyYcJ+BfswgASSBu6Hau7bjF4Mw48cTNMOPW/Looz6MwgzBuDWs7Q0DHp+1obgQ7yP8hG/zU7z2ok6Xvezzf+SvCBsMbatvC/zuoatj/dRXg+ztcUJB/KIOIg3W9MOjnEQf7Zh3ieR5n2S32H50c/v2lL83ypBlGFkfyP77ehezT5+bFFEH++jfsLKZy0ck+V3ae1R7sN2hM+7+bvyBhjR6qUcI8Pf4radRhofQ/58iHAhdTL7+MzIfesxyrVtXNPKtdp4X/sN7oVWpFBG8qXxNpIwosyx9ZeRzxhYwxbGMzmG90W4EESY/9drkG3dGt5r3Oq7iPsgPr5tYX8H6Uk482j4PPfcRnp9heP5zXniDsrHJ6Yx1uWz8TErn7ffSTlYTR5/hbCdSXpi7Cvcg88=
*/