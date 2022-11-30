#ifndef BOOST_QVM_ENABLE_IF_HPP_INCLUDED
#define BOOST_QVM_ENABLE_IF_HPP_INCLUDED

// Copyright 2008-2022 Emil Dotchevski and Reverge Studios, Inc.

// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

// Boost enable_if library

// Copyright 2003 (c) The Trustees of Indiana University.

//    Authors: Jaakko Jarvi (jajarvi at osl.iu.edu)
//             Jeremiah Willcock (jewillco at osl.iu.edu)
//             Andrew Lumsdaine (lums at osl.iu.edu)

namespace boost { namespace qvm {

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

////////////////////////////////////////////////

  // The types below are a copy of the original types above, to workaround MSVC-12 bugs.

  template<typename T, typename R=void>
  struct enable_if_has_type2
  {
    typedef R type;
  };

  template <bool B, class T = void>
  struct enable_if_c2 {
    typedef T type;
  };

  template <class T>
  struct enable_if_c2<false, T> {};

  template <class Cond, class T = void>
  struct enable_if2 : public enable_if_c2<Cond::value, T> {};

  template <bool B, class T>
  struct lazy_enable_if_c2 {
    typedef typename T::type type;
  };

  template <class T>
  struct lazy_enable_if_c2<false, T> {};

  template <class Cond, class T>
  struct lazy_enable_if2 : public lazy_enable_if_c2<Cond::value, T> {};


  template <bool B, class T = void>
  struct disable_if_c2 {
    typedef T type;
  };

  template <class T>
  struct disable_if_c2<true, T> {};

  template <class Cond, class T = void>
  struct disable_if2 : public disable_if_c2<Cond::value, T> {};

  template <bool B, class T>
  struct lazy_disable_if_c2 {
    typedef typename T::type type;
  };

  template <class T>
  struct lazy_disable_if_c2<true, T> {};

  template <class Cond, class T>
  struct lazy_disable_if2 : public lazy_disable_if_c2<Cond::value, T> {};

} }

#endif

/* enable_if.hpp
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
*/