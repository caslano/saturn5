//  (C) Copyright John Maddock 2001. 
//  (C) Copyright David Abrahams 2002. 
//  (C) Copyright Aleksey Gurtovoy 2002. 
//  Use, modification and distribution are subject to the 
//  Boost Software License, Version 1.0. (See accompanying file 
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org for most recent version.

//  Kai C++ compiler setup:

#include <boost/config/compiler/common_edg.hpp>

#   if (__KCC_VERSION <= 4001) || !defined(BOOST_STRICT_CONFIG)
      // at least on Sun, the contents of <cwchar> is not in namespace std
#     define BOOST_NO_STDC_NAMESPACE
#   endif

// see also common_edg.hpp which needs a special check for __KCC
# if !defined(_EXCEPTIONS) && !defined(BOOST_NO_EXCEPTIONS)
#     define BOOST_NO_EXCEPTIONS
# endif

//
// last known and checked version is 4001:
#if (__KCC_VERSION > 4001)
#  if defined(BOOST_ASSERT_CONFIG)
#     error "boost: Unknown compiler version - please run the configure tests and report the results"
#  endif
#endif




/* kai.hpp
yhf+8VnfJeDH1l00Yk4LRj0mLbmET9o6FNTZXgjM9NHTHLFag9vw5qzwrv1HLdQev4flTxE75akziiI3mY9AzaWEPaqVsMrRPodUHR2u1WtGvVSBemGm5ITvVEATvtBgAC8Ne00FtyCnCvcEaNzH/e/Ly9o0F5cBbcLJYm1pb9dIknhfZON7oPrARQTIroKM4zplYaTfPEXN1Bjf5mnR+p3CFzRNsOleLH1bPQQ6WwtnNNXi2j/vX/XC2vpzKawJXQmljmQvyF+aAuVApa63On8U2xQ2m4D5ykwuXlQRuwJoDJMMAsuHDOf5N41oDLWSI9gT4xeIhhjW00x+0/5vUA1Dwje8NV/1zeulZ63Iosq3+a+0wb3p5dl3ezlONswC7XTcIETnV6sdk67zUsDi25G3atU96nPa8IvpQOO0IQVl//vqZxU3YnbWRPKA+fiPVVSOPZaY6wv+qVQAGawI//hwZc0PglJaPdCuIcaycOniv7IYjl//23L6VY8fGecmJAkcACLehvjL8qyYwKshRYanR/HCux0mo6p/6KBUwYMvYCE6tNWODtEMkg==
*/