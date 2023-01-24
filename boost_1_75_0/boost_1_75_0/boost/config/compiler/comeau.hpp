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
5OjDJp6YE0r1GGNFfelwxin2f0FnLVaCB/FZ2DgjUlL+hdKtNimluFNtlr2ENAQ0UyQQZ/5excvH3WGJgeaf4L5lr4dMOaSGCbKHX9YeTjxMEg9J1RPW8GgfZfv2411CnpiQasRiaUiskZtg2XTKfUIeKoGdh5y2Sa/bTBz7sQlz/FMoHJlgY/fkhHXsRsUDaf/S02C8Y4bxCRTEI3z8p8HYIZ5Iw5hhHoWOmOBc9RmsAbghfsr8QxPfqh1s/KrNz9VDoYvXd9cRa30jeC9KywEUi+/6UTOMx5ao6FFS1+JMzK0Z/FefML9zDOjH18g77zDfzjPgz9+Zn89+BvjhZ1g7FzxjbeddWDiB18wII/6MeX5DoYHDuH0ajPNM+DhTu1c9My3204Pk3fNfamO8/xnOy59WVXQMCj9/hsnBXszU2751NbTdLj5uRzX0vBi125yPFgKuXAi4cuEI8xUuHOWwSP0LoPCVo+wbco5aYb2IhVfw2ln5iPKjfJ3cAZlvQuo/ynwwq89M8/XckQFMXTy/yVw8X09dPHOeMxvNr5pL5StjR4nPZLi8CElVvwrQ8v6cXP6aXP4vuXyLXP6BXL4PF/ENpUJdPqOP+fNHTX19+mYVXYIb0imgQBpoIKwZ478dM/El10PhxmOsrx/PgvacwH7hVUDCTThXKLhs7SWPTZsfdx+jcdarUNIU5/3yfWH0GN8XHj02w74w
*/