// Boost enable_if library

// Copyright 2003 (c) The Trustees of Indiana University.

// Use, modification, and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

//    Authors: Jaakko Jarvi (jajarvi at osl.iu.edu)
//             Jeremiah Willcock (jewillco at osl.iu.edu)
//             Andrew Lumsdaine (lums at osl.iu.edu)


#ifndef BOOST_CORE_ENABLE_IF_HPP
#define BOOST_CORE_ENABLE_IF_HPP

#include "boost/config.hpp"

// Even the definition of enable_if causes problems on some compilers,
// so it's macroed out for all compilers that do not support SFINAE

#ifndef BOOST_NO_SFINAE

namespace boost
{
  template<typename T, typename R=void>
  struct enable_if_has_type
  {
    typedef R type;
  };
 
  template <bool B, class T = void>
  struct enable_if_c {
    typedef T type;
  };

  template <class T>
  struct enable_if_c<false, T> {};

  template <class Cond, class T = void> 
  struct enable_if : public enable_if_c<Cond::value, T> {};

  template <bool B, class T>
  struct lazy_enable_if_c {
    typedef typename T::type type;
  };

  template <class T>
  struct lazy_enable_if_c<false, T> {};

  template <class Cond, class T> 
  struct lazy_enable_if : public lazy_enable_if_c<Cond::value, T> {};


  template <bool B, class T = void>
  struct disable_if_c {
    typedef T type;
  };

  template <class T>
  struct disable_if_c<true, T> {};

  template <class Cond, class T = void> 
  struct disable_if : public disable_if_c<Cond::value, T> {};

  template <bool B, class T>
  struct lazy_disable_if_c {
    typedef typename T::type type;
  };

  template <class T>
  struct lazy_disable_if_c<true, T> {};

  template <class Cond, class T> 
  struct lazy_disable_if : public lazy_disable_if_c<Cond::value, T> {};

} // namespace boost

#else

namespace boost {

  namespace detail { typedef void enable_if_default_T; }

  template <typename T>
  struct enable_if_does_not_work_on_this_compiler;

  template<typename T, typename R=void>
  struct enable_if_has_type : enable_if_does_not_work_on_this_compiler<T>
  { };

  template <bool B, class T = detail::enable_if_default_T>
  struct enable_if_c : enable_if_does_not_work_on_this_compiler<T>
  { };

  template <bool B, class T = detail::enable_if_default_T> 
  struct disable_if_c : enable_if_does_not_work_on_this_compiler<T>
  { };

  template <bool B, class T = detail::enable_if_default_T> 
  struct lazy_enable_if_c : enable_if_does_not_work_on_this_compiler<T>
  { };

  template <bool B, class T = detail::enable_if_default_T> 
  struct lazy_disable_if_c : enable_if_does_not_work_on_this_compiler<T>
  { };

  template <class Cond, class T = detail::enable_if_default_T> 
  struct enable_if : enable_if_does_not_work_on_this_compiler<T>
  { };

  template <class Cond, class T = detail::enable_if_default_T> 
  struct disable_if : enable_if_does_not_work_on_this_compiler<T>
  { };

  template <class Cond, class T = detail::enable_if_default_T> 
  struct lazy_enable_if : enable_if_does_not_work_on_this_compiler<T>
  { };

  template <class Cond, class T = detail::enable_if_default_T> 
  struct lazy_disable_if : enable_if_does_not_work_on_this_compiler<T>
  { };

} // namespace boost

#endif // BOOST_NO_SFINAE

#endif

/* enable_if.hpp
8zo58SZVQG4QT58WjMwc4jnh0wUdR7/jdHtRilenM4pQxMdtugN5hareuqzjNgJNqVxrjOqnMrX87jgNzyUfl2zCxYXYXDI6mAnQerza8RdDAzauG4b2dU2mww7Pzf0naLqx9NONVCg2U9ViyYk5Pk08JqlAyjFrRQxfdzWO8jC+avOTJrI5xHpsjW1+/SzRvQiJertB+xDBIYUt8Xsqz6U2w3S/hWXsydfLEGTyueedwHlUuD+hfQTnxrw/Y/5Ip/Yo9iFcSY3QJ4C3ew/erImN2PnTUHRNPDezlbJ9eq+qT7Wvc9/OO0H/NjgmnMHzfH5hCx65iQO5keGNxpYvnoNu+4YnGb98iZXn0xheL5uDV2O/9fELHV5xmotcXkV8roaYlfbS3h+zfBhvbPBql4fK6FM/8/v2WsvHpzHz4fUBLy0s8+M3Gh4WZ94CDtvyUJhxf4vh4dPYPl3amhfUtbzeHucFGsvrsha8CjgV4HhxOfHyaXyfbVb80bfr1gujNNxNG1tfPCctukG0L5uLFl7FcfgiovU9i2P7u3w63zOo769nWrYk6XiJR+OPMMu+dC5aiAatP4agjY1ie2+HZjGqED1bLR7X6dlqxq8Yv1cRjXlXoB9o4+TB/lv2V0pfOa1FGcfM43eH+DTks73eG5NTBJ1ar2i83ufQDcxMVXGFeHpW0RVVPYBj8Qf0eiS06cqHfb+dZ9fEZKrSlHpzm2R+MC7TkLZdexb7I3GIrDk1sr+1y4dS2/l7Aiyrfao+QXsM0dHfY6RKUl8+Ohed6kzs96Ck3qL6OUftprxXyiVMd6xbJ1JbUHzQoO91c1738TB3UHdh0k7a8WLd/QFrsx5vxmBvZAzOjo7BJ9IxsHsungTch0+KfiWhQxDLFLTfkp4QyV/l0ITH6TOal0dX24fcJyXluHR9jBaW2wPijPM8tA0ivXNOXc3xR3vyS5W25OeJ9M42dA1oPxvTVS8OusSK0JDRft7S+vrqFuWiof1ia1qQqW8ErA5ftrS+vgXsBhWx4ftV6Zuf6xtK2tt9vRVfUTc/I/dAhP7GeeiTVCbUJxnfbqGP18L48U1RGQmI3bh0c5wuGxezRtwSpVM/G2Jzp+8LDdKI3lw9I9TylnlzUKltJyL9pgfw+VKS/lyvaomIZfr0I+DwuUqghrxXY98Cs3r0kR4YObtPu1VyM3HB5gRkcawYWZjqqZ0TNNjU6N7yu18t54rElLnpGkJnbPwz0Vup5BInfozlWMcx1r731MpWeDmQ+/DrFnT6y3M7br+1sTPdNKpbQ9iMG3v+7gR3z+j/VvaveE8pkSxVm89brAy9EHnnMXd6Mnz8nyIyWukAIVEd/hShYXsdFB3VCh9MRtrz/ln8K/shq27jV8RfcCe2sHFV1bMwFsbYtKb83YxbrByLQab4/8+5aGWgM9r/Gtp4yQWcTU1xQc/ctIpz++e3et2P/z7ge4+b984dtOA7d6oWf88eXYvftAB7ManP31dgWwl2f4HtVLBO9U2SiL4fjOYpR0IO1PTqdJKo9No4elScDjPKzu+F2va4zz80OrA1h5d3hsbU+2Zp4k42WhTnBSo75ovjNCoM6TFMrG5LemxsdRvYOLYUNOV+DEnA0/Lp6TGxzuNjY/SKHhM3gUbMSQ8vLI+HaRt45TZ4KPX/RJ/GBjcj55EiZzaZAo3eRXDcOMnq2ktcEqZZxTQlSdrH3d9ifBTTFDQJ74d6tR5SuJRuk836I3qmA0H9XQOaYn85tH2792HEr8vV6PsTx8XuR6+HzOx3AiDXvp0C+I6hbYhxen7y2fnjBDcwNtLn/67ZE7gdVjXd1uI3+G29fdEmjZfXM9GYcE+ktv4=
*/