/* Copyright 2006-2015 Joaquin M Lopez Munoz.
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * See http://www.boost.org/libs/flyweight for library home page.
 */

#ifndef BOOST_FLYWEIGHT_SERIALIZE_HPP
#define BOOST_FLYWEIGHT_SERIALIZE_HPP

#if defined(_MSC_VER)&&(_MSC_VER>=1200)
#pragma once
#endif

#include <boost/config.hpp> /* keep it first to prevent nasty warns in MSVC */
#include <boost/flyweight/flyweight_fwd.hpp>
#include <boost/flyweight/detail/archive_constructed.hpp>
#include <boost/flyweight/detail/serialization_helper.hpp>
#include <boost/serialization/nvp.hpp>
#include <boost/serialization/split_free.hpp>
#include <boost/throw_exception.hpp> 
#include <memory>

/* Serialization routines for flyweight<T>. 
 */

namespace boost{
  
namespace serialization{

template<
  class Archive,
  typename T,typename Arg1,typename Arg2,typename Arg3
>
inline void serialize(
  Archive& ar,::boost::flyweights::flyweight<T,Arg1,Arg2,Arg3>& f,
  const unsigned int version)
{
  split_free(ar,f,version);              
}                                               

template<
  class Archive,
  typename T,typename Arg1,typename Arg2,typename Arg3
>
void save(
  Archive& ar,const ::boost::flyweights::flyweight<T,Arg1,Arg2,Arg3>& f,
  const unsigned int /*version*/)
{
  typedef ::boost::flyweights::flyweight<T,Arg1,Arg2,Arg3>    flyweight;
  typedef ::boost::flyweights::detail::save_helper<flyweight> helper;
  typedef typename helper::size_type                          size_type;

  helper& hlp=ar.template get_helper<helper>();

  size_type n=hlp.find(f);
  ar<<make_nvp("item",n);
  if(n==hlp.size()){
    ar<<make_nvp("key",f.get_key());
    hlp.push_back(f);
  }
}

template<
  class Archive,
  typename T,typename Arg1,typename Arg2,typename Arg3
>
void load(
  Archive& ar,::boost::flyweights::flyweight<T,Arg1,Arg2,Arg3>& f,
  const unsigned int version)
{
  typedef ::boost::flyweights::flyweight<T,Arg1,Arg2,Arg3>    flyweight;
  typedef typename flyweight::key_type                        key_type;
  typedef ::boost::flyweights::detail::load_helper<flyweight> helper;
  typedef typename helper::size_type                          size_type;

  helper& hlp=ar.template get_helper<helper>();

  size_type n=0;
  ar>>make_nvp("item",n);
  if(n>hlp.size()){
    throw_exception(
      archive::archive_exception(archive::archive_exception::other_exception));
  }
  else if(n==hlp.size()){
    ::boost::flyweights::detail::archive_constructed<key_type> k(
      "key",ar,version);
    hlp.push_back(flyweight(k.get()));
  }
  f=hlp[n];
}

} /* namespace serialization */

} /* namespace boost */

#endif

/* serialize.hpp
mL0eyrv9aH4wly6vRiGuZ0P4jESjUbwB+C5S4Z7NxM8nQzii87ntRV1xPbRiK6slRxAnTt0+uuxchA8848ey6S7OYU1nebFbsuaeEO4h/gojyz4IUcMPcP8/Xjc0Ez0zFmcxUP8AMr1jbyAKwaLqV7iS/9uhpv2k3FKqu8q8AbJPW/t/4Fjm1noE7+feLISpqs8/hvIOP5Y6fL/zxH7iM3HEfmb+0/2fGyrdH0ni3SU20UFdsraYtY+EwFM8BRKUet37+6vxHW6Ehf56y9aU87vPwVuzAyBS0udInTYWQNW5yIA8NLD2V58OG/Uf1yvzZXIbW/LGnOtN893osXbsCQdRNq1BpzPtB9pcX2n+v6w6+4HAEHP+j9vbXD/WUVbKdUOrM/qbnqzCH21lb73pU4m+K7pWY72JGmLWf4yxvd7kMv3HYNnVC0jPOBcnEuzx0igqT1sOUoZRC14buym9HFWdu+a0XlkNuvTBppswqi1RlqJYzsafpFTNY6OCrsgchKsnZqVqay7jkFLifPxJcnt9ksBuixcu+xyoQ47j6DFFh40sOY0S52F5FpIN18qladGkMD9aVONvV34rAogFtKJYmf8xqRJewH0MpxD04nAFnS82U5hn5dLreyP4yjWQyoikhg6Bachw1UwvMIEybuCq41SSj+PZvDUpnFETqMdNTAj05vPPwsTkrD7q/vdadf8b5n9PShI4EdYLYZN6lFNPjNMmQqJhNyxm60CsOsmSbjtOzuNptHGMK7pIWt78MoodwfhxQpKzeHNArzsjeB3eBVYA0MpkAkpjyROYDmusi85p6kcQIYjzVpgL4WYPvfmpnnA0ePXYc3T2b17/sol/8hyRTgH5LscNHQNi2l1L1NyK1JAzz1ttnCeR/u8a1f9Toq31YQzlUWa33MN29Y0panmPJNibT3+6upL+p2815tPNlF3x7iTMuO3Zgxea83fqc9jufEzyfyX627exuV45KCvlcljmkvZ/g2j9fbAth7Jc/wYp+Jq0sMf/uweZ6Z/fpzrr9aWV8nfpVI32+3mgWf8x4rDd/rZ1oCr/xNvq33PM5Y0+Y3km+2dCoPtZbqKtTZIbJKdIJ2XRFbSpEfPLVvB+hMf/XBBMNr5dynxJna3vzuD7y/kD1JuidYSwLBzgZFGComLBbQfoVy5rXtmm8hq+ryTFuKpeiZPalLjZzkw8eMwkvCh+kGs+7MMokNO+rdYFhyuqf83Pzv4mm9m/9Ff8CQ5PcwuFYw5ub+ZmOI/oWy/aEbcnUDpZxjf9PHi8euKXCnHrCX2E6fYHgdoyA3umJ76soYrNaVaxIQAwnRRsfPtNOir1tDfMv4xeKWthVVsSt/YtuWqKK8olZov02dxPU5rc5qeyDWZXecKdosVQ9VpRvQBLSn4j+g090wuI6UHcfAh08E9AGakl/KdnEbG+G1AScbk3sMX9xx0xZ1r5k56RJWeOXG1POVZ9EjeiWAX/ixYCb62L1P4C6U4Pa2SrhiBshYBNBBkUaYsgjbUfCW9xvYQmpikvKYlrJHPg+iuRgb0msCx4MTHlwk3c9/BeL6qtXpTcDIxpaDR6uEueCD5DAodxzCfBmO/d2Gh6gN1+PhQk4KkTKcM+dacjCt6zAc+AMoF/bFEAbB1aCQJopBTEocV1PLrPQnjAESffyDP0RMxNOZjoOBXA+Y36SP9Xpyv+S8wWlA1RypWqKt5hGLVIa9UybpaQce+WMu4Gsm1GjsvNx4du3BXok3ASU3GQmrpJJuJRgCfVkMCtZYfI0rRIfQPj9NXAqQl4OhTG8tl71zWf7y5i9n995VYxF/sz3RuhkC8rmMFwORS+C2kqnsYivCTino6vhgM=
*/