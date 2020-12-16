//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga 2005-2013. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/container for documentation.
//
//////////////////////////////////////////////////////////////////////////////
//
//       This code comes from N1953 document by Howard E. Hinnant
//
//////////////////////////////////////////////////////////////////////////////


#ifndef BOOST_CONTAINER_DETAIL_VERSION_TYPE_HPP
#define BOOST_CONTAINER_DETAIL_VERSION_TYPE_HPP

#ifndef BOOST_CONFIG_HPP
#  include <boost/config.hpp>
#endif

#if defined(BOOST_HAS_PRAGMA_ONCE)
#  pragma once
#endif

#include <boost/container/detail/config_begin.hpp>
#include <boost/container/detail/workaround.hpp>

#include <boost/container/detail/mpl.hpp>
#include <boost/container/detail/type_traits.hpp>

namespace boost{
namespace container {
namespace dtl {

template <class T, unsigned V>
struct version_type
    : public dtl::integral_constant<unsigned, V>
{
    typedef T type;
};

namespace impl{

template <class T>
struct extract_version
{
   typedef typename T::version type;
};

template <class T>
struct has_version
{
   private:
   struct two {char _[2];};
   template <class U> static two test(...);
   template <class U> static char test(const typename U::version*);
   public:
   static const bool value = sizeof(test<T>(0)) == 1;
   void dummy(){}
};

template <class T, bool = has_version<T>::value>
struct version
{
   static const unsigned value = 1;
};

template <class T>
struct version<T, true>
{
   static const unsigned value = extract_version<T>::type::value;
};

}  //namespace impl

template <class T>
struct version
   : public dtl::integral_constant<unsigned, impl::version<T>::value>
{};

template<class T, unsigned N>
struct is_version
{
   static const bool value =
      is_same< typename version<T>::type, integral_constant<unsigned, N> >::value;
};

}  //namespace dtl {

typedef dtl::integral_constant<unsigned, 0> version_0;
typedef dtl::integral_constant<unsigned, 1> version_1;
typedef dtl::integral_constant<unsigned, 2> version_2;

}  //namespace container {
}  //namespace boost{

#include <boost/container/detail/config_end.hpp>

#endif   //#define BOOST_CONTAINER_DETAIL_VERSION_TYPE_HPP

/* version_type.hpp
o6OWu9jVuoZhMtdulrtuq0bjzrWr0TC1Mhl3NEymlkbD0mJp6tD9fJ+e993nfJ7n99HT83h6PZ/P9/P9/b6/f9/fn6NYkZKzRLEyZR1VKFal5KxRrE7pQ4NiTUrOFsXaFOtQrEuxHsX6lD4MKObaoGx/innJLGbvbOzNhQXIbGbDt9z6IyxJ2JrHXn0JlqHkzFZyFig5y5ScVUrOBsec9Nw2Wy4rxfOYHcxWiedtuhTrUaxPsQHFXBvp3JTZ/m//fSIsQGYz81wcboQlkfmYLR4/sBOWSeZl9sLiqS2wXGF7lz55MqxQ1PLta/8cD6skCzAb1z3xMFiTqHPlT7eOg3WI9k4Nj9wL6xV9MO+BwTzvDY6JGjNnteVgBOYjs5ktWTF7GCxB2IS9b/0JlkbmY7Yg79HvYTnC/hx38FFYkZKzgszLbL572zBYrcj5r/i6l2AtZH5mN51uzYT1iPa2Ths1BeZqiW5v+pjbfoDZwkYPu7cXFkfGa/l59V/qYalkAWaFoZe2w3JFzuw5R6yBFYq4zPLRP8KqRHt78/9TBmsUceb9OFiXsEm/FI+Fud+PzsnHS0CxZMWyhBWNvGAOLExm8+V55+okWKmwyZMufQ5WTeZlZt4hhjWQWTAxH9nCc4p50y6lDxGR039LcR7M2hSd84GFed/AgsI+2/zOMliyYplkvJZ32hcsOGT0+/ZkqOVFeg7wmcoZr7kwn0WG/eBLMffNN8c4WIliZcLMMQ5WoViVkrNGsTolZ4NiTYq1KNamWIdiXWQ+Zkffc+L/LaLEuT9wNksxm8xmZq7RYfFKXCJZkNl7s797AxYSOQfvEc0IhVnO1TETQw+8UfgbrJDMx8xsD7AKYbfmT/saVm/aY5a8NG8zrJXMy8z8RjisS2kvIuo07ybB3K3R7Znf6ID5yfzM2kp/exaWTMZrmb1xyOOwDDJey7wZ+745ZPfNzCNDLbUxOeeYcw1YWLFCk5PZdVe2rjlkBw9WsLiXaXs32wqsSrEaYWZMwOocLRxqYPYK/T66yQlrUqxFGM/Z5mj0XBezf8nnuhTrUaxPsQHFXB86m4fMx+zm5j3fwoLCtsXsKYSlkPmZjZnwcDUsm8zL7P3dj5wOCwu7MTttCKyELMis79WjdsPqyCxmy7J6qmFNIqeZc4S1iz60LxnfB+sTZm/c+RDM+ih6mZl5U5gtbHn/sf+G+clsZhNOOKISlkjG29vgnncrLEPE7bt2XhCWS+ZltmrCjtmwQmH8N/7KyALMVthPnQSrJ7OYmXMGWLOoc9cltyTBukR702q/egHWL/pw3J+/2gSz/hsdd+aUFbNgATLe3hvLqq6BJZNZfCz1frIUlk7mYWa2W1imyGmeGYLlkwWYPX3Ug2WwcjI/b++uK9tg9WQ2s9v+snwerFXYeQesYbBu0fdTz8wfDhsQtrK95UyY1Rbdh48O++ebsLg2p7jpM5JZXF3M7DnmuALLIvMwM/sCWDaZxcy8Vw7LJ7OZvX14+jRYibCh1/9jBKxKtGe2I1iNUmezyPnCX/qOgHWKOs3YhfU6tndbTj+zV8U75xHF3B87m6WYrZhfsaBi8YolKpasWKpi6YplKhZSLEexPEejd5aZ/ZvmX8z2DitUrFixUsXKFatUrJqbeIe4lpuYQ6onw77nNZq7+MfYy2bC2oUdsD4+GtZP5mXGr6c9nwy2Vy9+49armE+xgGJxiiUolqRYimJpimUolkUWYDarMRyBFZJ5YeIZrDIyHzPzrDSsVrEWMgsmrtE7hJm5SlgPmc3s9n2v/Rfm2hxtm1ZlPw7zbXZq755b48hQ53/IzHk5LNXEMZtbftsJsEweFzWvMXtOPot7nX4=
*/