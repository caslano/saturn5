#ifndef BOOST_METAPARSE_V1_REPEATED_HPP
#define BOOST_METAPARSE_V1_REPEATED_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2009 - 2010.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/foldl.hpp>
#include <boost/metaparse/v1/impl/back_inserter.hpp>

#include <boost/mpl/vector.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      template <class P>
      struct repeated : foldl<P, boost::mpl::vector<>, impl::back_inserter> {};
    }
  }
}

#endif


/* repeated.hpp
29LtnOHoXxrHnKWRRoWwYZtLKn6/LKuquzYgYRSNO/Z8wDgwLOZZkVIFSAfG47MRRPVBszReoWZ0gcG0ZO6qyGoMPpQ/jnDYLfOEI9ucIiy2SyIzOWOC36OhRHtqYCoR1MJMK10s6sBRqmUf/T0UksklciH4bcHgjqZ4jZXMICzTCDy24s5fH9v2zKj5c0csrFwK/bzrbSGRT+VQTxbAREcwXZSBKYusRNEG51WGWbO1JgWDlONlykJbGKCwzlCaBmZJUAv7aIMhoGB4xjrYIEbxPKcKc8/jliYfW09mDNqtDx+v1JW43mq3rtTLK9FuEtKGT9D8BQbQ9KEDv0ouWhvbgO+M5rhl0aqADdruB+rdH3k/d70XW1dkcL3lNknTPz95d3px8ooclrarGFXWMZpef9rdefjSso5Nk9i1XeIOUnnAJCsDOk+5aZFt2MRPc6fdRnrN3UN4sDOgVhzkShoZynTo2D4v+wJWkw1nnNSmD1+0T8P5CTvPO8Kqwu2yRdcvTs7Ho9P3DecoDFmOjzfJpp1Y3wT7dOSXEVwGAI+hcNCtXv7XzyQbke2nDrHHGD/iFYoP3JIjbtuZYoeZDS8u3b+k1VL7J/TufGe9luff1ByQuoQCshqHAan/Vv8OUEsDBAoAAAAIAC1n
*/