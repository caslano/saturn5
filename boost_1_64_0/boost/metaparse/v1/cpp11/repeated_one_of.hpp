#ifndef BOOST_METAPARSE_V1_CPP11_REPEATED_ONE_OF_HPP
#define BOOST_METAPARSE_V1_CPP11_REPEATED_ONE_OF_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2017.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/one_of.hpp>
#include <boost/metaparse/v1/repeated.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      template <class... Ps>
      using repeated_one_of = repeated<one_of<Ps...>>;
    }
  }
}

#endif


/* repeated_one_of.hpp
FNpnQLXYaTXYQkpyRxkUIi4soD/BwwEaZZXP80MD8Qt6FZqy1TOIkEUAzAIwJnzfh9ZJeyoFdiT+WL9dXJ9MYHnIAw5ajMfmQevjXoZ+lDO1vXKDURKpy3ymuwX4ViCh+zofqonrfzg3jKgsCjv49HDYNWqvbYuDW0mzMTX98JxqLbUnZyg64WygPjCT1noVpe5+tN52jbYxXLQNzw0DX2f51/o33G+/TElfasIIMfEFuWnQypzWDGa6SDKMcxjmEh31AVDj5rCj6hDUrgyex5cpPFrUgLR67YxeOircKV8vMdG0n74JYVxMBPtKuTfdKLCID8BcydJLyY0mOo6qL/BE2wBTKKj649jCDOpKyaMNRm1XBiJsN0P5BDlSyAMFt1HhZU/JwoP2+23JYJfodvgRG5/2YnRYHIjVWPiDtEnyc0ofqjzEb9iQzLDL4PWEUjiyUS2OGDHOlBIVjNNaaRuMycR40BfLTHD52f3EFCfUm1ksJJVfzDMlUfQgikeqCD0y1NVJSRaQ52s3dTROl1sYe1J6zqDIbzw3YXLxr1ApfDNf8GMoA204xQ==
*/