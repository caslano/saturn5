// (C) Copyright David Abrahams 2001.
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org for most recent version including documentation.

// Revision History
// 09 Feb 01  Applied John Maddock's Borland patch Moving <true>
//            specialization to unspecialized template (David Abrahams)
// 06 Feb 01  Created (David Abrahams)

#ifndef SELECT_TYPE_DWA20010206_HPP
# define SELECT_TYPE_DWA20010206_HPP

namespace boost { namespace detail {

  // Template class if_true -- select among 2 types based on a bool constant expression
  // Usage:
  //   typename if_true<(bool_const_expression)>::template then<true_type, false_type>::type

  // HP aCC cannot deal with missing names for template value parameters
  template <bool b> struct if_true
  {
      template <class T, class F>
      struct then { typedef T type; };
  };

  template <>
  struct if_true<false>
  {
      template <class T, class F>
      struct then { typedef F type; };
  };
}}
#endif // SELECT_TYPE_DWA20010206_HPP

/* select_type.hpp
SDyiJi4XiaaaOBcSuR1+SNI0Elc55NP2NrAW+zDn9faQg84057SlnLqI66678G0EPykNj6b+1ZWpxDApwnlKtrP6iaxkkZXosITJ8/xD+GIrRI+LLC0qq1FTsho1NUtaUK3MwKQUS8xBA7+0XMzrraARh8JoeC4LI6/DEkbeKGEUcT2MKNTkYBD0rp/5O/pkyyHNbxxBw6HiUUgx77xYI0lyHAWXGbhYs+VJs/G/Tox/hzX+V9P4r7fG/1F7/C+X4x98BgpJbEYuzgFDZUs76byNRMZBl17QQIkYFwYFkAW9g4cO1rKMiRPmQ7qD3b94WYITS0AraCDaqsDy+dTyx53lF8Tj8ABT3B9eAg7XXnPjyxzmQcOJzHLdmOhGnk5ShiWk8JBE2z08HTy03eaCly3jRodOCEmvWFjDIbav4cLCI2kcbhYJCUsFkv930goRRzWuezpWJo3CSeCb5Brv5hj3RUmo0U7lx4vdhYRaHIMSqmK7xmLHidNIeZZJkox85SS+uqECQ3JTPV4tSog5AY+BNxSXfy6+UHs7SXu3EcXpWpQ0O8hdSm0aXNLfEWgFf+OKu4JBlWM4zW8mpuBikra1V/fHbt5xdbqDlAT22a+g3xRIB33gRLdCeYlDxOWseg13K1JND010K+huYK3lGO085nuTmjzxUnqijp19JzwxO+MblLYFmFhAgcRHlrmAj+9jrybpppCY/G+I
*/