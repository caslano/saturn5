#ifndef BOOST_METAPARSE_V1_ACCEPT_TAG_HPP
#define BOOST_METAPARSE_V1_ACCEPT_TAG_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2013.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/fwd/get_remaining.hpp>
#include <boost/metaparse/v1/fwd/get_position.hpp>
#include <boost/metaparse/v1/fwd/get_result.hpp>


namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      struct accept_tag { typedef accept_tag type; };

      template <>
      struct get_position_impl<accept_tag>
      {
        template <class A>
        struct apply : A::source_position {};
      };

      template <>
      struct get_remaining_impl<accept_tag>
      {
        template <class A>
        struct apply : A::remaining {};
      };

      template <>
      struct get_result_impl<accept_tag>
      {
        template <class A>
        struct apply { typedef typename A::result type; };
      };
    }
  }
}

#endif


/* accept_tag.hpp
sVcEhs/liHyI+EG5+I0xlKHAZT1FgHYORGNkljIetz5rarWTe2XmzPgMVt/bzgkIBvajbM7xHE96rGQ2t5BEbGmhx8cGGssvQNkLH4TPasmdHpWVBJCS6hxzstuVg21XgRQxL/HTBtxEQlT+09YcigdFY0OKFZUAXAaczKy30KFiOa5Mms8QpmPd9AcE8OGOHHblgEMRuLly47wtRL9yL+OTMdcaNJn1zC77ITBNOEiSKzHmL5ZgWR+vI4KQG6YBUfXqzAM1W+5wgxJFEAUt5sudJQxLas06Kl7G2Yc/FuQG/pL9VrX9CWQB7pTABytOG3wcp9bFOHBniIeCCjMp96zC+ZIBdc9bgLnGAgeeVlr9cl2R5Uskx4GpAFlW9ebu8hfKH3cUxhcWFkNmba6/6NJa12p8S62DJqO6yANoB1OKIr5XfIJg7bVuhm9roqjt6rBsqJDToQk2ioTyAh8p7wmISZCK56T5q3A6CzSysSrOkEbpuB5v32Y/aW1RUmxFrKnpfUzOdOYk2YV/PCwmLjPV5UxX65MALyVnKU5t+SgVsvrnRjXDJBiuyw==
*/