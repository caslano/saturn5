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
tA8ghT8VbKiTZuF04sN76k0EKSqPxivHddBnrERK+hpJaYZgmRakABvXRy4P5AJw1L6wMxtoEYgi0OgYa8QxCGICPt6HwtDNTYBPblabwAz8p61f74TJfra2GF7S+48m8THS1BdZS1B42OQk0TO5oIG2Hw8Ewv5fzD5PY1iJRuKxBJ/alfM1qX4xuOCdzRjbfZdsRLNaVcmrEzv6KCkUiIiJrh5DHpVCOEsRQCewAtPMswbGW/Rg6U4czw62XcoZLPQe6C/YafWGASMZqiZxspDlhwJopRWBupTdJLooNdrox3clLqOXC5APM3AvChK091q/M1PT18gPNGWWh6Nuv7Jd7pArinz3OKi4jrOxcNIVlv80GEdkmBicHAyV82ezOFbmRCL/SEpHjNPLYxUAWMYy6vZBllK/zPYFdTPIfdst6bW0VjShS4IapSwAp7dO4MjmrPyVi251pMGPvCMktNQl3KHUaDUh2EFnBFxbavm6Chv26G4pIwXCdpz0TBAqrwFk7kASDrP3mMbL+Bw3iqu7LvBBdtRNk3Fto6gQUaeZ7SJXZTQLyUKn/A==
*/