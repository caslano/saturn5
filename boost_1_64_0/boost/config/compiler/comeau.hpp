//  (C) Copyright John Maddock 2001. 
//  (C) Copyright Douglas Gregor 2001. 
//  (C) Copyright Peter Dimov 2001. 
//  (C) Copyright Aleksey Gurtovoy 2003. 
//  (C) Copyright Beman Dawes 2003. 
//  (C) Copyright Jens Maurer 2003. 
//  Use, modification and distribution are subject to the 
//  Boost Software License, Version 1.0. (See accompanying file 
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org for most recent version.

//  Comeau C++ compiler setup:

#include <boost/config/compiler/common_edg.hpp>

#if (__COMO_VERSION__ <= 4245)

#  if defined(_MSC_VER) && _MSC_VER <= 1300
#     if _MSC_VER > 100
         // only set this in non-strict mode:
#        define BOOST_NO_ARGUMENT_DEPENDENT_LOOKUP
#     endif
#  endif

// Void returns don't work when emulating VC 6 (Peter Dimov)
// TODO: look up if this doesn't apply to the whole 12xx range
#  if defined(_MSC_VER) && (_MSC_VER < 1300)
#     define BOOST_NO_VOID_RETURNS
#  endif

#endif  // version 4245

//
// enable __int64 support in VC emulation mode
//
#  if defined(_MSC_VER) && (_MSC_VER >= 1200)
#     define BOOST_HAS_MS_INT64
#  endif

#define BOOST_COMPILER "Comeau compiler version " BOOST_STRINGIZE(__COMO_VERSION__)

//
// versions check:
// we don't know Comeau prior to version 4245:
#if __COMO_VERSION__ < 4245
#  error "Compiler not configured - please reconfigure"
#endif
//
// last known and checked version is 4245:
#if (__COMO_VERSION__ > 4245)
#  if defined(BOOST_ASSERT_CONFIG)
#     error "boost: Unknown compiler version - please run the configure tests and report the results"
#  endif
#endif





/* comeau.hpp
tisysp+69xjAcekVaEFp2bir1xhHsEGH2cWcwvRHYYoB+0sawljRe9SB43xRc6y/rP6Vpx1whNiGRvY/ad7gvptA36V9i0BaeBJXAvjTNr0ZTCrJMnl/5emVlW/TtC2n5RePWgbmqJt561AmWxPXcXZFKizaDCiH20+f2JkFDW2w55kL9ZeMFqDXMcgV2VjRVSPi4o0XgzksqSTFgBCq4gvPLgne0sQ0A7gHsjk8xNSPLhD6VknF6BAHUnEXJZbrDv+kvceLRcdeqjY5qVmRTa55tHcd6kAJbXXmbrwD3GzgewpuyHkksoa2q4200mvnlO/R37NmfpQmkEUYc3O6EkYrU7C1xjlA6Wmq8N7oNgtkHvrDVYIqSSo/Ab3LFH3m2ZXAzhAernx5N33H5DY7gUza4eTJj9/Pst/QTdM3WPMTOWvBIYvOtXhq43r+05pOaZvx94BNbHRUEh3TjND+weRDj3Ol7l+WaFpwJw7dQh2QZDFojYuM6U1xP3oQOgcFe1IEVb8RS3cxwh+l6ZUMe3IIkYXvATIDAjibJc43a9aUJ5ZJiiDRiFSoaA==
*/