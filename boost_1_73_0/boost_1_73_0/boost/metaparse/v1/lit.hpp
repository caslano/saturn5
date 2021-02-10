#ifndef BOOST_METAPARSE_V1_LIT_HPP
#define BOOST_METAPARSE_V1_LIT_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2009 - 2010.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/lit_c.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      template <class C>
      struct lit : lit_c<C::type::value> {};
    }
  }
}

#endif


/* lit.hpp
2abRJk/E4hOivuK9lMuru/iSzxJCCDH+6KatMWalDCiDNsSK25uIe/9lszsNzg96R1cVHeSaNOiC0AGVCP0eodQePhANRL60xCVOgzbp18ATb45sjrv19vFlv1unsFrBtVDonHWZzXlgRvIfVPKcr+T8T79QSwMECgAAAAgALWdKUjq2UruaAQAApgIAAB8ACQBjdXJsLW1hc3Rlci90ZXN0cy9kYXRhL3Rlc3QxMjY1VVQFAAG2SCRgbVJdb5swFH23xH+46pSXasyhypBquZGqrmqibQEltNqeKg8uBRUwwg4t/34XXJKXvoB9fb58QFo0NlUG10yWTa7p9YrDm+4ys2abJImnB7Sdfh/YLnqO99Gfv6zRbiD5GSy547MvcMCux843ZYZMdthWAx1nyionyYNvAVwtlxD9ZD+URQHJEb/C8hp2uqeDYAnBSqyuBUEefifMyQkYo/pm2vBcvSK7043Fxvq/sHmxhYDVaZIMLY6Ed8sLW1eM5VpTQpdB8o9MFPWuKke8i5pOGwI4kzUrrG39su1D4swz2aia2pq7gLfSFrCN+xCaY41dmaoKVJZ1aAyxHJgEKVbvBJ+n7m7GpeB8sYkOyTYWi7GZONonJ+UbIYLJ11FlqutaNZkTmZnhTA1HLg+uwu/E
*/