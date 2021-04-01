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
// has_equal_range.hpp
//
/////////////////////////////////////////////////////////////////////////////

#if defined(_MSC_VER)
#pragma once
#endif

#ifndef BOOST_PHOENIX_HAS_EQUAL_RANGE_EN_14_12_2004
#define BOOST_PHOENIX_HAS_EQUAL_RANGE_EN_14_12_2004

#include <boost/mpl/or.hpp>
#include "./is_std_map.hpp"
#include "./is_std_set.hpp"
#include "./is_std_hash_map.hpp"
#include "./is_std_hash_set.hpp"

namespace boost
{
    // Specialize this for user-defined types
    template<typename T>
    struct has_equal_range
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

/* has_equal_range.hpp
jTPy6xZXWi+PAIRu/TI0kHju5FRHwaiTF+PEUwVxS1/z1k1lPQS2l60jLURCzXQ5pbY6EAtHS1ei+C6VegB1EJZt1D7hjv/CLbLS5GvYvF2pIQ7TUJJN36M8YnvV/ILTsa+9LUAsAtYqB2c0hcnbYtkDuQ7cCGBLYmX0S3Tyz8V5xNvGGPcXIV/3HbQxiyONFCJ9aAf9qP1lTVFl/Jdg0+26+bChyRtv0skd2i8kgFYaztqCrAo5geFfI3ouro8NLbRfFQAFmQDjx9r2eZpviyfUu/xtZjR8PhkObpdV28un+CDlPoS8825P4qwqqlN3Sfua8M2sEAIBxWQ1gtNmAJBRa5Mz3NrpXPnkdgh+XZ6NtKtltMKlZC9Ys9XWwFvUxASAKT7ulVrmjDjPJadP+e2qFUfZWF4grgsxmpqYR5jTRuWhxU9xss/wD6qIH8V8iEiYBTFtVB02PM4FWqAbhlUFVnIsyA6MVeFI68PsJ9bW3zu22CjWXmynbTcm9Lqv29RsJ5831L1QxBxnQ/Nrb4YcBtKGPRjp9cvKFbQ7WZdUHCMna+Gsnf6IUQ==
*/