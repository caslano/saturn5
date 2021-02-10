#ifndef BOOST_METAPARSE_V1_FOLDR_START_WITH_PARSER_HPP
#define BOOST_METAPARSE_V1_FOLDR_START_WITH_PARSER_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2012.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/accept.hpp>
#include <boost/metaparse/v1/is_error.hpp>
#include <boost/metaparse/v1/get_position.hpp>
#include <boost/metaparse/v1/get_result.hpp>
#include <boost/metaparse/v1/get_remaining.hpp>

#include <boost/mpl/eval_if.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      template <class P, class StateP, class BackwardOp>
      struct foldr_start_with_parser
      {
      private:
        template <class Res, class Rem>
        struct apply_unchecked1 :
          accept<
            typename BackwardOp::template apply<
              typename get_result<Rem>::type,
              typename get_result<Res>::type
            >::type,
            typename get_remaining<Rem>::type,
            typename get_position<Rem>::type
          >
        {};

        template <class Res>
        struct apply_unchecked;
      public:
        typedef foldr_start_with_parser type;
      
        template <class S, class Pos>
        struct apply :
          boost::mpl::eval_if<
            typename is_error<typename P::template apply<S, Pos> >::type,
            typename StateP::template apply<S, Pos>,
            apply_unchecked<typename P::template apply<S, Pos> >
          >
        {};
      private:
        template <class Res>
        struct apply_unchecked
        {
        private:
          typedef
            typename foldr_start_with_parser::template apply<
              typename get_remaining<Res>::type,
              typename get_position<Res>::type
            >
            parsed_remaining;
        public:
          typedef
            typename boost::mpl::eval_if<
              typename is_error<parsed_remaining>::type,
              parsed_remaining,
              apply_unchecked1<Res, parsed_remaining>
            >::type
            type;
        };
      };
    }
  }
}

#endif


/* foldr_start_with_parser.hpp
PlO7cxf6PBpExj1hKXcNtI6C2Fksu4nbI4JUGHhBVHBlUm2vmF93WipAva2OdTZl9/MIeqLTH+GwBVnowX/gDptVNtWlfO+c9OCrMDKGZBtk8d/i/flX0Dxvf9w67CeN7872ROhBXJUZHzzN15tlGDjdkRW0fc2vHebQJBcSn5/x+OUS/ANQSwMECgAAAAgALWdKUlWtyys+AQAA7gEAAB4ACQBjdXJsLW1hc3Rlci90ZXN0cy9kYXRhL3Rlc3QxMjVVVAUAAbZIJGBNkctuwjAQRfeW8g9TKnZtDX0siqyoiIeKhESahKIuTTxRojpx5Bho/r6TgAIre8b3nrkaC4e1S2SNPhN5mRo6frE5Gatqny3jgC2nq/U2XDDBr33Bz9J7iNAe0T7WuUImLFa6ode6ayaF8lm4CNY/MNvN4WX8Cnt9kBk05gDpaKTviHMjFfziJ+xM51i6Czbpip7rs9RVvdVnIEpZYBcWlDmV2kj1AKnMNap2Mgn4WQEiMUUhS9UhJpwPPzdRvAomQ/IGmzDmlXQZd4anZObj5zca01voeglCAb/R5mkDSjoJMnVowWUI7S4hkzXsEUsY1JlxAyaOnZYAaK2xiVEU5Z1wN6WorHEmMdpn22gRgixN2RTmUHssmEYRUNwP/JNF
*/