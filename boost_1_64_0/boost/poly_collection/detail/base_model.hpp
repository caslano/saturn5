/* Copyright 2016-2018 Joaquin M Lopez Munoz.
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * See http://www.boost.org/libs/poly_collection for library home page.
 */

#ifndef BOOST_POLY_COLLECTION_DETAIL_BASE_MODEL_HPP
#define BOOST_POLY_COLLECTION_DETAIL_BASE_MODEL_HPP

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/core/addressof.hpp>
#include <boost/poly_collection/detail/is_final.hpp>
#include <boost/poly_collection/detail/packed_segment.hpp>
#include <boost/poly_collection/detail/stride_iterator.hpp>
#include <memory>
#include <type_traits>
#include <typeinfo>
#include <utility>

namespace boost{

namespace poly_collection{

namespace detail{

/* model for base_collection */

template<typename Base>
struct base_model
{
  using value_type=Base;
  template<typename Derived>
  using is_implementation=std::is_base_of<Base,Derived>;
  template<typename T>
  using is_terminal=is_final<T>; //TODO: should we say !is_polymorhpic||is_final?

private:
  template<typename T>
  using enable_if_not_terminal=
    typename std::enable_if<!is_terminal<T>::value>::type*;
  template<typename T>
  using enable_if_terminal=
    typename std::enable_if<is_terminal<T>::value>::type*;

public:
  template<typename T,enable_if_not_terminal<T> =nullptr>
  static const std::type_info& subtypeid(const T& x){return typeid(x);}

  template<typename T,enable_if_terminal<T> =nullptr>
  static const std::type_info& subtypeid(const T&){return typeid(T);}

  template<typename T,enable_if_not_terminal<T> =nullptr>
  static void* subaddress(T& x)
  {
    return dynamic_cast<void*>(boost::addressof(x));
  }

  template<typename T,enable_if_not_terminal<T> =nullptr>
  static const void* subaddress(const T& x)
  {
    return dynamic_cast<const void*>(boost::addressof(x));
  }

  template<typename T,enable_if_terminal<T> =nullptr>
  static void* subaddress(T& x){return boost::addressof(x);}

  template<typename T,enable_if_terminal<T> =nullptr>
  static const void* subaddress(const T& x){return boost::addressof(x);}

  using base_iterator=stride_iterator<Base>;
  using const_base_iterator=stride_iterator<const Base>;
  using base_sentinel=Base*;
  using const_base_sentinel=const Base*;
  template<typename Derived>
  using iterator=Derived*;
  template<typename Derived>
  using const_iterator=const Derived*;
  template<typename Allocator>
  using segment_backend=detail::segment_backend<base_model,Allocator>;
  template<typename Derived,typename Allocator>
  using segment_backend_implementation=
    packed_segment<base_model,Derived,Allocator>;

  static base_iterator nonconst_iterator(const_base_iterator it)
  {
    return {
      const_cast<value_type*>(static_cast<const value_type*>(it)),
      it.stride()
    };
  }

  template<typename T>
  static iterator<T> nonconst_iterator(const_iterator<T> it)
  {
    return const_cast<iterator<T>>(it);
  }

private:
  template<typename,typename,typename>
  friend class packed_segment;

  template<typename Derived>
  static const Base* value_ptr(const Derived* p)noexcept
  {
    return p;
  }
};

} /* namespace poly_collection::detail */

} /* namespace poly_collection */

} /* namespace boost */

#endif

/* base_model.hpp
ZOdP4yEsPZCcNdWlmADvst99Nq7C9Cd8QXpXPaIHplXGOESbvh7iNjb7ydgT8OS8MIdOmEskh/b3dyZ2dg1BHfTjRy7OzvuH/LwvhKF37IIpuz5ihviysaH1Uz+2tkZghoJcYOTaIpseXlsd8v2QevJxqs7ClbVF4Qbp4wN9joVL5+Iw+GBQoRPoYyIKpzxYJk35/bs9EktfT/Z7YTrAdtjY6LXNlBnDRyKx0euafk4eXcbkRTv8WGjj4HVwcADxg3lPeksuXT0iI954MFIUQU9sXVl+SaKtvaW1zkuTuvYBNePQWG6dO+0+PxGikWANdRMVjFyxrRY9f02y1e9/uTiNpkFcG8mlExa8ZEr9uNX3u2icOo41B9iWjzPM23neZC5OmUI2UegShrNobUzOXJf4IT1EY+z5cLsvq4WNWCfMGLuM5uIGd/QMwLdsZtO0Np7s5r+Os9eUnwhhMCxzbY3dL7JoEeuPNr9xCzvT2mOM9Ssbp9Etu3LljivZGTx69ft8br1af1VssMaViQicBo0+fw6zvQAmm4wGc4rJ+3JxihnUo7ZC9XQnB+0xgHxAuOuLI3BDPbuSveQ/QXvxK0L1ycqGPvau3HpUQZCD8Z6ZTWdNstnOncby6bts/57KoxOdtPJiMGUbIjDSsJ//hGxrmXRIthLOltebq6TITrqI4eKZM5k0XxAm43ZcS7dpu478R4a0pf4RhdNapMGMR2KYPtGiaW8yEsNwQoR2LFtOh3BK9k0+z1nMOfS9bn81tFiIttN6tjMe0Fh/cLPPzm7SUDvnJ/eQ33XYWOJafxdQJ2HopYFuWeTbkdrJY1luJwwfHTbdmy6Lf+/9cNGYTHSRLQa5RdorJxrlrLHA93W7vLqgPcZ3+GMTs8KkNanW+uxigwvqYZ0luJ/u8e8Tz3ejW91/cXBf+kiZMqMBjRgZ8Dq627qvbBcvrDE2mYqik2nv2DGYutL9E5v4sac3EitegnWijvc6Ps51emsu3eP7YgGM5tEZv4/4bSrOWtk7ZL/NsT4fJ3eCR3p3l+XX4zaGHNodaOzcaCpEj8rHVRdZfA7W6wTMRw19JIeudReLPhaia44BXf5v04Pcmzmx9Je26Vr3UYgRhrM7LEzuvolg7SgXgxRBH5sYzKFpM0Gg8+kQ3crDg3WydxRZmFCebT1zGRvKqUvrBBLIeqY4beMK7xfo8vWcsfEEzR3Duxxr3Xfcpkfnw52VRueR2Oh82M8V3ueEykQ/4/djb24bxvMGjb3Khm06Oawly6RNi37O3uv7xpU2NuueWtII4ljMxkQ8h/f7u40LPYNfJcyIjzml5+LM42Q/u5z1TNzvsza9wPNwYckYbWz0s3DTbpmNtZ6D+7qx6eHc1n7eaOEK5a8jFiacv47ss2nRz8/9PmRho/JX38fuy8FJ+0GbE6F6op6rG+zY7yKxtD3IV/qPhZ2Kxuo5iFev6Tdlf5gZq7p7jUzl+3PxskSQ1wW5n555y/aKvH48aJwRxw4AZ4e/rmG3aeeAVlyb9PPJ6Ofc/tj6ElNX9DNuP/ewcPbzbUNP59L1bNtaL4uiK5f0c/4ojPJEO8easnDK9Xb6tKsMLbCFH0ebjI7z9bu3J9PtZ+VWHHDm+HmZnS7As/rJGZF0pRNOt+Fr+oDhS89hrHWqqa8ZWt6z+l3+HPH2aIwekHcb3HQ0Tg/GA9zY1w0u8vl8t9/PvlEIp6atPKb8aCGsmrfX0u60sKFn8v4Y/s1CGK9lv89+y8ZFP4u357KxgngPaeQZvdrGRT+DN/YdvcbHat4S5JxjAW1vsifjugfTBm+NEXLGX4e3cVRv6p607hNYEcXZ6Y+nL8728/bGNo0/JhQ=
*/