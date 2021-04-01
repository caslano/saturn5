#ifndef BOOST_METAPARSE_V1_FAIL_TAG_HPP
#define BOOST_METAPARSE_V1_FAIL_TAG_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2009 - 2012.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <boost/metaparse/v1/fwd/get_message.hpp>
#include <boost/metaparse/v1/fwd/get_position.hpp>

#include <iostream>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      struct fail_tag { typedef fail_tag type; };

      template <>
      struct get_message_impl<fail_tag>
      {
        template <class A>
        struct apply { typedef typename A::message type; };
      };

      template <>
      struct get_position_impl<fail_tag>
      {
        template <class A>
        struct apply : A::source_position {};
      };
    }
  }
}

#endif



/* fail_tag.hpp
PL5XflcBYxkWP0T1eN2F5JX+johN9ksfomLjgMgPuAxpeQizMqt0e2A24uvaKvLQ4OeL171NNxaC2vPoxYtb8vHBstFZZ/bAFSUUyE1pbGWEC+Ib8nHbdWdS2lzx2HUsY3WXKBelQj2LOIboBmpjF6EUHW53ZTJ7QmbXGae+xHYyhztAOYtsKpDMpIz+3VKd7LuHfq4nv6TPu6368KnFU2cTQvlffeXr8sUMuK8Nq+YFpp5FhZznwb4ochkpAnHGuEjwJZGYcmaNX2BRAZp/KNxe7/5ty4kwHK58kMNaxTDdmd0FCpUDSnMc4yyq90UqwACW/OqIgLOSE6kuUhXRX0W6TKvKYN5KPL1oUsyi090joZqcPJpYnge7Bnobx90rYU1mldztVw8R7GRzC7PQe/K4gQiGxIg1sIqHqFhPRokGT2oVE6H4vuoiw3z3dmcVlwBWKnn3DBI9/fGhHIMcKchIbPRcw1D4cmDUlfrs3KSRHbM3DtFHYnrB3nT5xovcRCgvkkpMzfXhkdMpNBvac8ejKOy2CRlwnQX0YOzz44SVE8eIZafT1/kF0Q==
*/