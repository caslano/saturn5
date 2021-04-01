#ifndef BOOST_METAPARSE_V1_REJECT_HPP
#define BOOST_METAPARSE_V1_REJECT_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/fwd/reject.hpp>
#include <boost/metaparse/v1/fail_tag.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      template <class Msg, class Pos>
      struct reject
      {
        typedef fail_tag tag;

        typedef reject<Msg, typename Pos::type> type;
        
        typedef Pos source_position;
        typedef Msg message;
      };
    }
  }
}

#endif


/* reject.hpp
jmEIAHQID5grzsU3NPkSilyci4tnAmc9hQsxMDKZAlHUmuL1iICx1uOmDMPO3vwraNccP9XWdvTBrYLXMoFl49L6FqQMymJKHWUSw8u88na3LzZwmyszBQFAdj9KkD7yVEZnPVgg6ZdtYQJ5Gh4657Sn97awwFr6b+N0/6XTIUm5QW3USRYDmhe2fjjRKS/h+S3R8hd5uVIZg6mDCPCmaT9a8O5tx34pEZlmutsYXiWy5/55iOc+3c6R8FWAba2Td7uQVrP9jzoEqki+M5YEmfaKJYO1A9bBBY0Z+VYsYgC9cphLD4YxXTtPN/HWowc2eY3lsyG3bEmcEj1wZzAxYkdu9obQd5Lp1WAqBOLPiqCeNzRskWy7ubEBmYoueb/PgAncrXxi9Fj6RsRrROQPg+FjW6ABflQ8yNpymRQqEc7jRijsd8/xhgBmqi5/B+WgGICvbknUS5rY7YpRpsK1yYMsoZ2lNo1kFY7ovvZA7t+0hwNVIrTy7iEM+Zx1I4rkeAJZHQ4/KgtO8DhlePpUrUfAHuRlU/opetC+PWqmBzplMhaxljUSt0f9yg==
*/