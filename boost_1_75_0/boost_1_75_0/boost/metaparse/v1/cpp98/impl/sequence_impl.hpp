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
W/kiLq44MfLTnzwtivfgKJDvq3lnKuZRzzMbjTIKekrkZPwequf+Fq5s/DOZb4DRd5Pqo6t+/ALTj2cxib94o0oZTMgslbXQaIAp7+0mNuPZpA+ayeW9KltPitRdMBNIZTJzg+OmG7hWxNlTKmsj9boTk7XDWQc3mxbAMU0xPkwBIpWZ+PEseUcNadpLJlLMTDMo2qzAu2ul/EWNqmdPW3nulb42rmTnrw/6y28FXmtlVn+3i32ulThjXERveChd0ixm+X6Es4G0KomL1UKR0pbQlmNM9khLE2DnlJApRTu2ML4c6IJmOwaTpNuQtRXzzr9xbh+9egJLeCn6Fq+UJ9cQy7cx1Rt/ZEuNyvL5XDjt6k0sP+ts9k5B96r3h7WhqrdL6qDU2101lmPyX6tRUabl7mvA6j7jQBUcc6zl7sD1ML5Sfe1G/lTI9ld3omJWnsOJphVDWTFOLR+Ll4Oqnf8iD+EprYA7XkVhmWEw1eC8wgxu8WXC5P3DBlqHEKUa8WRz/52Dd7ijpU2Bd+hT0m5qkhpUXqC8Mum0SZWlncCtd1gnolEx94ChEbhcu8+u7+SPwf3W59i2jBuBRrl186JhYr+EHsKn0d+BPg5ayVXM655Dn0//xsF7+JQPtJDf/SpCr6dSJCEq1bTQWLqbgjrxZevDdGIr29nVZZrEZdqmL5kVNHKhqNc5z1MxnvlVUIjMXQVUMNM06SRN
*/