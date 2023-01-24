// Copyright 2005 Daniel Wallin.
// Copyright 2005 Joel de Guzman.
//
// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
// Modeled after range_ex, Copyright 2004 Eric Niebler
///////////////////////////////////////////////////////////////////////////////
//
// has_upper_bound.hpp
//
/////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_PHOENIX_HAS_UPPER_BOUND_EN_14_12_2004
#define BOOST_PHOENIX_HAS_UPPER_BOUND_EN_14_12_2004

#include <boost/mpl/or.hpp>
#include "./is_std_map.hpp"
#include "./is_std_set.hpp"
#include "./is_std_hash_map.hpp"
#include "./is_std_hash_set.hpp"

namespace boost
{
    // Specialize this for user-defined types
    template<typename T>
    struct has_upper_bound
        : boost::mpl::or_<
            boost::mpl::or_<
                is_std_map<T>
              , is_std_multimap<T>
              , is_std_set<T>
              , is_std_multiset<T>
            >
          , boost::mpl::or_<
                is_std_hash_map<T>
              , is_std_hash_multimap<T>
              , is_std_hash_set<T>
              , is_std_hash_multiset<T>
          >
        >
    {
    };
}

#endif

/* has_upper_bound.hpp
ZTq9+is8pgfdN+jCLD56UybK8ylzMD+jiCcYiKKQ4zzQjiJSeG1bqoC7oyoEnzd2oyndbFdPynmTNB0lFBXQg1/UZl6aNKHxtcRkvS06sHui40I9JHgVYxkSPAawsuJ6Nk+0v6QcUPfOstRDyQRl+vVNvLk73yuhDYL0zVcbNO+pGuU8+2q7SZWWCv45tOp404uYMiGPyNqMP+1MNIpa3/mgfNZZVgxaftD9kbxns3o7SAIxBPeVkTYPeeKbPJ/l+0fCmukJNO6uIyxYGzW/2ue3ZTi8Q1dAmSq6LjFpE0Twr6X4r8XQ61fSeaJrUxZuSvYkSqWXSoFykz+RUOiRfWfk66MtlceEQz94xFXKz9IMUqmud2DOWyPrtrKUJnfjO852DoWAW03LRTibAtemk8I8W5LpuBix4idf7TNlQdjYtXok999Q/t+gVQaJD9Zc7AnBPZvpUIP3JbKwl67YP06WrPuNSQ8otABmtS38SUUKlchMajtxezLTGe7/LIPiROCdmvW8Aqm2t4W/Xmz6wBuG3SfELdGCSa3nEyXFJd/Xm7RJ3AZJ5/dexDbD4JYZI2JSbLxG7b62wZpK5pzUMZB+oxTvYE3Li6uYi0c2NkSHhCDQszlK3rDrJ4eEWd23vtK2clfa7eEKB4S4CpVV1Zmt9zmnh6nW3tgnvfCX0uPMEWmny1FQyjviDeBLzsqCkrto0yiEMyE1gUoE
*/