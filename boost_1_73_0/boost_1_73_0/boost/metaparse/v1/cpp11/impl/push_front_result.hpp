#ifndef BOOST_METAPARSE_V1_CPP11_IMPL_PUSH_FRONT_RESULT_HPP
#define BOOST_METAPARSE_V1_CPP11_IMPL_PUSH_FRONT_RESULT_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2018.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/get_result.hpp>

#include <boost/mpl/push_front.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      namespace impl
      {
        template <class Value>
        struct push_front_result
        {
          typedef push_front_result type;

          template <class Seq>
          struct apply :
            boost::mpl::push_front<Seq, typename get_result<Value>::type>
          {};
        };
      }
    }
  }
}

#endif

/* push_front_result.hpp
YXRhL3Rlc3QxMzIwVVQFAAG2SCRgjVNNj5swFLxb4j887SpHQrK9IQs1SrNK1E2ghF21Ry88glWwke2k4d/X5mPTqjn0gjFvPDNv/KAGtcmZxohQLkppl5/Y/ZKq0BE57rOEbLPxAev4cNiss2HTKnntCA1uaBoMBOSRPMIR1QWVr3mBhCps684CcikE5ibqGYLlfAlPiwXs+akyHZRcIHBRIBYe0Y1pQ9BnhVBxAw16xLMCHwQ0GDl7sXXNUZhRLO83FqJ7C1HPRSpjWn/yPFVoicxYDWve1clUv30GKliDQxKgURRgztZCjfalUvJ8quCPNIAGA5xqU3ARkWclmxAKXpaorCmPZDIEJqSpULmO3mXRub5GONiEmoaJYjAdBoFb5stPT4tw5iwkcZoFbgu+3zBe+ypvDSjMeeua/oxX1rQ1zi3NhCithd45qr/LGfjgt+BfYbaNj9kuCWdJGn//4TT6qEcn9nVMtM/6DRUvOyiYYcBKg8oGgeCmCCqm4R1RwIOupHkg9NJjLYWNx8hc1hHZbF9icB14ZL/avcBzGu9D+q+/yCPpOskgi0N6tz8L+LLKVh759rrLXIY3DXpua8mK/41/7k5PR2h/kxEZZx3uXABM0+uRrdQmvIfxyKsdMn91srIh5GdV
*/