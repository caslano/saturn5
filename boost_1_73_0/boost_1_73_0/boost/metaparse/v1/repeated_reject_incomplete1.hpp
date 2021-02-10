#ifndef BOOST_METAPARSE_V1_REPEATED_REJECT_INCOMPLETE1_HPP
#define BOOST_METAPARSE_V1_REPEATED_REJECT_INCOMPLETE1_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2015.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/foldl_reject_incomplete1.hpp>
#include <boost/metaparse/v1/impl/back_inserter.hpp>

#include <boost/mpl/vector.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      template <class P>
      struct repeated_reject_incomplete1 :
        foldl_reject_incomplete1<P, boost::mpl::vector<>, impl::back_inserter>
      {};
    }
  }
}

#endif


/* repeated_reject_incomplete1.hpp
fPWfVsl1oJK3r/kBUEsDBAoAAAAIAC1nSlL+qXSSZgEAAEQCAAAfAAkAY3VybC1tYXN0ZXIvdGVzdHMvZGF0YS90ZXN0MTI5MFVUBQABtkgkYG2ST0vDQBDF7wP5DkOlFyFu60EwLIEiYkWxpU29SA/bdJoE092wO1r77Z00/XPQy2Z3efPeb2ajmQLnJlAKurIbJ59P2u+cX4cUxlk2PSz49JhBUbvVqrIFaHWRaNVVwRVc4Zz8N/k4VGsC7amp9yJYGzadlRreDPF2MMDJCzw4y2Q5fiVbcJngXXtjKefK2QTz2gU6a7J9Qwky/bAqeVsDxBvnYonurLU6RgnBQ121FR1BfjiIIBy4UiiZG5GfjtqarfT9Tr7a7HExe8VTi1gV1nkK+LEUfSfTudtujV2n0Gt9EqX648k8e54m/ba56WSWqR2pnbGsPpaqMQWp4e39oCcO51LZHqEE9hjcdoFmw+SRS8L2QbA0AVdEFnuhdCwW3wetGDTesctdnYK8Cf6biKdhRzB2gRP8AxrBQoYQjwpBkWl/+Vr13x9n8+fJWwSjPKdGrq/VdQSRIF8itTpzqMuP8wtQSwMECgAAAAgALWdKUsVz3xKyAQAA3wIAAB8ACQBjdXJsLW1hc3Rlci90ZXN0cy9kYXRh
*/