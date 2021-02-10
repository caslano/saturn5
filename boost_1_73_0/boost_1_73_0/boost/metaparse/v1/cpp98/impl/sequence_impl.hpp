#ifndef BOOST_METAPARSE_V1_CPP98_IMPL_SEQUENCE_IMPL_HPP
#define BOOST_METAPARSE_V1_CPP98_IMPL_SEQUENCE_IMPL_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2013.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/impl/apply_parser.hpp>
#include <boost/metaparse/v1/accept.hpp>

#include <boost/mpl/deque.hpp>
#include <boost/mpl/fold.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      namespace impl
      {
        template <class Ps, class S, class Pos>
        struct sequence_impl :
          boost::mpl::fold<
            Ps,
            accept<boost::mpl::deque<>, S, Pos>,
            apply_parser
          >
        {};
      }
    }
  }
}

#endif


/* sequence_impl.hpp
2so2aS0rVGKLY/8Yfr76cgN5KYxFN143Su1vQNc+cmydEWpD+B02HFEcTcH37KdxmAGN4wImlfQ1rCyQJXkwUnK7UlowSLYFrchEKHDVbGCNwjUGwWkQVaXfobH+TPWhkIZa02YfHHRAn0dg0Qx04+rGgVR9SpBqExAnL4unn9ndMps+LmAnjBSrilgcStDiQkkifPIk7YBTVjpX083RTPw40o/1w7t0pa8bSRCqgL+Msg/RlFgWxIxw2nRCp7Bdys6ZjXvzH1Ne6U0o194nud5uPfBh2F2lo7bFPp2kyqumwG7LMua89zBbZo/zuOf5zWeLjPvNeXKe4hQigj4gEjYxdEGXKavRVNBbLibEg1dy5TXGlSaRSOvsZV0B8eJHKRDKWS5BHtYZFv2KRq73EHQv1g5NWIEHhFJYWCEq6NpSuy5LdiHWUzHa6VxXKfNDbVkfv5IOe6BiMfzRXIe90Fqi2w0VJ5U3puK917vF8nH23GG3eY41uT/xT16axPijBG2exD2EIO+ub8zX+w++y9D2sf/RWf+tPP/xKbT9j3z//EN4/PSn/w1QSwMECgAAAAgALWdKUv10r9IwAgAARwQAAB8ACQBjdXJsLW1hc3Rlci90ZXN0cy9kYXRhL3Rlc3QxMzQ2VVQFAAG2
*/