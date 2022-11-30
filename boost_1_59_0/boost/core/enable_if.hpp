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
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
*/