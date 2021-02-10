#ifndef BOOST_METAPARSE_V1_BUILD_PARSER_HPP
#define BOOST_METAPARSE_V1_BUILD_PARSER_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2009 - 2010.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/fwd/build_parser.hpp>
#include <boost/metaparse/v1/start.hpp>
#include <boost/metaparse/v1/get_result.hpp>
#include <boost/metaparse/v1/get_position.hpp>
#include <boost/metaparse/v1/get_message.hpp>
#include <boost/metaparse/v1/get_line.hpp>
#include <boost/metaparse/v1/get_col.hpp>
#include <boost/metaparse/v1/is_error.hpp>

#include <boost/mpl/eval_if.hpp>

#include <boost/static_assert.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      template <int Line, int Col, class Msg>
      struct x__________________PARSING_FAILED__________________x
      {
        BOOST_STATIC_ASSERT(Line == Line + 1);
      };

      template <class P, class S>
      struct parsing_failed :
        x__________________PARSING_FAILED__________________x<
          get_line<
            get_position<typename P::template apply<S, start> >
          >::type::value,
          get_col<
            get_position<typename P::template apply<S, start> >
          >::type::value,
          typename get_message<typename P::template apply<S, start> >::type
        >
      {};

      template <class P>
      struct build_parser
      {
        typedef build_parser type;
        
        template <class S>
        struct apply :
          boost::mpl::eval_if<
            typename is_error<typename P::template apply<S, start> >::type,
            parsing_failed<P, S>,
            get_result<typename P::template apply<S, start> >
          >
        {};
      };
    }
  }
}

#endif


/* build_parser.hpp
Uq8LO6SnAgAAyAYAAB8ACQBjdXJsLW1hc3Rlci90ZXN0cy9kYXRhL3Rlc3QxMjI5VVQFAAG2SCRg3VXbbtswDH0XkH9gPQTYijq+5NLUc4IVbbEGG5agydqXvqiyEgtzJE9SmmVfP8rOpcX2sG5PGxA4kkUeHh6Scmq5sYwaPiSpkHOFf1/4Zq10ZobkejabVA94fzWrF5digQ5AVzYnaXAwTYPa+xVMuX7k2jci4yTVvCw2eJpRS2u8IGpF0AkjOEcIpcV3aoWScMO/roTmGZi1YYUyvEFqoATOS8pyjn7tVnwKry+pXgv5BibXk6DTilpxg9zd3fkOjksrGLU82dHUnBbLgedyrJbeCUglGR94Udht98JO1Ol6DXKhpEVff7Yp0dfybzbI7bJ4Cyyn2nA7EEb5/X73zI8Oxh+5XNg8gbjXIA0yy4UB/EllAYlUkaGkC9QgqJNHaXZGZlWWmGIGVsGDs7UrLXG7xgwqb1OlDgtuDVB0fKbVPrtCSI4xDCL5QsJcq2XlzQqBBGvRozAMnwgfhyGMP/yRyH8nUnsv0mj6XKCjrUI105o1UmFf/ut++Rcqsq0C7rZjjJ14UfXWdrrrRsPxrvt1SHJrSzTfbdM5p9jaHO+Ho+l0MiJMb0qr0OJwAKmkS17X
*/