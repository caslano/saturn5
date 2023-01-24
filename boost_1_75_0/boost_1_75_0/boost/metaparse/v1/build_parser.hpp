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
pfDLbrwyCXo4/Zv9Kz+7yWyKdJff/w1v6aLechneshdueXCTWVe4NnJLzA+/PAlIVS0wkuGCZfDe3/puUe2TED7Q/IDfs3WjBe+xqvf8yBbhIzP//iy2HEQ5stxU/xaWEOvfziNjH/Yd4PVvoecRQ4bvn1Sjo0pKm+AFiZ3+TE3sRIxowOghwoOqRKtp7uykO2GbuxtHJGfZiyEiinCFbbvxfNtlQN9vEji1SC6SOgsYLZwlhM7Q7OzIMBjH72oyxsG2px0jSzeGugjOilZI3TXpdckjGinNEXD49xLaHF8s0de0UHuDARju7K+11XLznpPsnmpPeGw19rtrRw190rCp1i7UbjOfgygpe8lJXLIaqnCe9B7omRACwJYWY3+CmxM4dmdi4zPoO4QF1KHXQ+A6Um5Jv0hnYhtdw0IiAjeYWryxLWJHaxU7tiVaDTcA9z5Lq/+dyKcLc2/djneQ5GZJmpxqX8Zq6fGK48F2FJaGS8DpmaGlIvbX6ldCAC6ACgyF+qCs7gsIylctxNrKty421MAhUffN1BSogz33pzpy6TVezsFeUo2OOBR1gxvgq0z2YvDxKo5h7dQvdQ9yJjC1F2Je2xnP2ktGYTreh7V8w+RENdCgLmmMHiv24gbycazgOvYKJtme3NlEx14BADiX34fuLCb5T1pBw8BZUUIZSbb0JKoT2EJ67U1/KKXomfs3Ml3favm6iWjI
*/