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
DSJHBMTPmNKI2WgmuIPhKWgqK9XDmCRIqQSQG8JKssVwREOhda1+G4/TRpZYyTgTqRqnOyqcQlcvqlpjNhW5B1Fr0AIaRW0w9jZUImO5uSJFeFg325Kpwn5MCwPybCwkKFqWPRy6Mqq6EihEPVu2sYQas2faXJTgykS7LUT1zBBp7YHyRnIMh7SgXSaQeBsanlHZ2rdE7KL0LLeUv9Gyx9wzEByzgoEbgRcNYEsUUzZcefFFsIrhyg1D14/XEMzA9dc93qXnn6M2GEaVQO9qSRVmIYFVdclo9iz4T510y4kvYLIK58EyTubBV89P8M4L/AiOYHB4Cn823Ij7eACDkm1N9+HEOTpxDvDAPCWUqPtEUW36jD+UlELU6AJ8dzG1XofejLC1GkpxjaLunVqfaO0Hy8iLrF8YT8smo3BmgnSqKz5bLV4q8Pxl7KF5A/sF6qFEWbwaFwVYEAn7fcS939uY59NoEnqthbUkyDvpzfq5IRVFVfSjthuwLYVaMK4ZvzY6MmrhTVmOjH4YJygDa5N7faBNvgQjj84WJwFy0ctNEq5yKh3LmuFRJYyaOL6tiPEEshWNbi2fcQV1iaVTJJFCOJt8OPp4bJubXw9OP5iJsLxpPINMklx3/yNKJNakR8jaSFW6Hh0cOPpO
*/