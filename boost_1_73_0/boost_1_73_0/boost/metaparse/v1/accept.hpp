#ifndef BOOST_METAPARSE_V1_ACCEPT_HPP
#define BOOST_METAPARSE_V1_ACCEPT_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/fwd/accept.hpp>
#include <boost/metaparse/v1/accept_tag.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      template <class Result, class Remaining, class Pos>
      struct accept
      {
        typedef accept_tag tag;

        typedef
          accept<Result, typename Remaining::type, typename Pos::type>
          type;

        typedef Result result;
        typedef Remaining remaining;
        typedef Pos source_position;
      };
    }
  }
}

#endif


/* accept.hpp
2EUSRqZwv9ObcYbfd9N7M19cUTNz/Aba5/sF1BXm/+N0BXvSqsCxHuwJzGjyu5wfpHGGYYEr1v8h0bNR5vQMS400pBxWlbADGNxR5gzuYqYO7hT8xmoMbt0s1XEA4zurAb5YqAHjNlcDlhppWDnsEgnzqsGZQf//Ta2b+BVkLXfWVfWp/MA5DlzSDDcKWBE3c3g/g0qHwWeKSkfBZyeVTpCwVfDZTaVWCUMr76LSv0gY0oSotEXCkox/W7aebZM=
*/