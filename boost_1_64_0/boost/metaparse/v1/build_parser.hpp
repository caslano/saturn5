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
9yFVQ0FEj6o1dS7/lqvMXlGhkd20OIfpLlONF87p5a6o1e0ctZ1pNGdS1U1mj2gf6/fy+poIQqddmGgWV3+Tt7vK72uoclyKidiQOqCfVFKnXBVpg3i7BTJzwiA/wfQ4C3ZYvjIP82yba0Nq5yjgmhGj/vxGHeL/q9W0i6hqpo1svm8r5YhlFUeejewRFjc6y4GqxvjxcwxvgcRTowb0FtzrYh2pzUAdMHOZTLhLDs5sto5ijRb8M1E4UVh3M5jCFyXSXZSfMK7TkBaaEY/rZmn8lWMkaAwz3JS9lTbYzR2XIU0vDydmEpLc217VLS7BHVPf97kU6qJfjGtJUC9H5/5d7yrY9jhOUmTabP9uov+K+3WWjGs2wK82wxtLoTpKd5QZQfa++2r6tln2y03YlO2RB8d3kQ2wigj5io2FRYWhtvAex84O4ZupaVeqbXesCSSCRxLE0dpe5rSvFbXxF6A4IokwbTwHD4Q62tqofqRNT57lmJLhc8jKt/nJXsQbUjTEPUA7+VlTyPMvyftcw5Ml4o6unwsv5RBMtbl4nAXudrFurD2lmnneKg==
*/