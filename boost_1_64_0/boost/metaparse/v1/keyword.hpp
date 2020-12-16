#ifndef BOOST_METAPARSE_V1_KEYWORD_HPP
#define BOOST_METAPARSE_V1_KEYWORD_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2009 - 2010.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/impl/void_.hpp>
#include <boost/metaparse/v1/lit.hpp>
#include <boost/metaparse/v1/return_.hpp>
#include <boost/metaparse/v1/is_error.hpp>
#include <boost/metaparse/v1/get_remaining.hpp>
#include <boost/metaparse/v1/get_position.hpp>

#include <boost/mpl/if.hpp>
#include <boost/mpl/eval_if.hpp>
#include <boost/mpl/empty.hpp>
#include <boost/mpl/pop_front.hpp>
#include <boost/mpl/front.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      // Does not consume/check anything after the keyword
      template <class Kw, class ResultType = impl::void_>
      struct keyword
      {
      private:
        struct nonempty
        {
        private:
          typedef lit<typename boost::mpl::front<Kw>::type> next_char_parser;

          typedef
            keyword<typename boost::mpl::pop_front<Kw>::type, ResultType>
            rest_parser;
          
          template <class S, class Pos>
          struct apply_unchecked :
            rest_parser::template apply<
              typename get_remaining<
                typename next_char_parser::template apply<S, Pos>
              >::type,
              typename get_position<
                typename next_char_parser::template apply<S, Pos>
              >::type
            >
          {};
        public:
          template <class S, class Pos>
          struct apply :
            boost::mpl::eval_if<
              typename is_error<
                typename next_char_parser::template apply<S, Pos>
              >::type,
              typename next_char_parser::template apply<S, Pos>,
              apply_unchecked<S, Pos>
            >
          {};
        };
      public:
        typedef keyword type;
        
        template <class S, class Pos>
        struct apply :
          boost::mpl::if_<
            boost::mpl::empty<Kw>,
            return_<ResultType>,
            nonempty
          >::type::template apply<S, Pos>
        {};
      };
    }
  }
}

#endif


/* keyword.hpp
Piz/Dvisd8Oe5cLuQg5OAM2XgE6rxwq8h8zk87Bu5FQwL1H9T/hDG0C7n5EXLEbcCNvwzePQOWci1oVfvPlP+MAY8/UoPwt4+jSRr/o6F3Eh7OOd14KmsG+fQ0b/BN95ToRvAD78GXZukhPtuwt+huZbUv9Fl/PtEY9zM7WpuyEfE3T1OKAr4Xv5NyOPh/mm+neAuxw5yK/N6Vktnt1hLHt6YWLYnRnN47wVemCMrt3dcuHXwL8qGwBfCzhbIAfQ7RXMg8IXfhhdXnkscku7eJ48F/5kLeKZ7Ziz0a1lzDs7vs6TYubrN/F5xKPeMN/n5o4j66Er/+LrC0ugg5bwMTmc237E2vNhe++9luc9kYN4fj3mIkZDdrHOSV6B2KAl5vAfRO4ca10mRXAO2/H4MuRFMNeUPQJzylcb23oi8mURxCnqeeyaTh0dH+Mjb0cOP86XrUUev7+5ud89b4jzUu77J8ybh2P8ut8lcvZtsOeYYw0EianjdT+3+YCt4L7tZ68jJwk8y8AHrlMRc/TGH3y0rq+g3ED4jgt5TAt/tmIyctX3wSa2hc6GjT8DsdEq+D81eZiLAHHmY22QLwtr58BPN2Auq+oK+ETA8WgfxJnnwv85BrHwYOh82MKpNZhf+hdrw+hnEEfOE+2sn91Ejmdx/P2NPD/Qlc2xiThwJfT/28Z7D/H83VNnJci10nVcv4nrbVcYYdvChrfyJeflsiHJy7TKarrM5OKm4V7ivmSv03Tr3J5JXHZ2bfJ20OPkMxBn3Qq9uD4mnykJ/m0YBZ0I/fDCVoaz/Ub2e8xnovwl98TXN/EB5N46QL9D9xlygEl01rbWie9/dzvGAT7yC1Mgv5fB170UMprDcG2Hf7FvLOz3VPhWyINcw+dZ1yK+yS7FHNFwrH+aolvvc74R92Xw1518/mVSLeSykKDdyLu1gk1DjH/RB8hFXA092AG8jfx+PXIv4T6Y04bfVIx4af0KPud8Auz2eeDHCvgIpzJ8l28Cf6HNz8HWPXiUuXG5pxp44KcNgq/llaDDFiAv0YD4hM/ZjgpiXvtLxKlPkKTHmciZH9cBMuE03m/Th+fE+LrWzs6mcSxsD12Adb4110FPLcW8xDvwF0H/a5Gj+XYvfGHY1bexnuxva0G/zvC71iH+gx0Ow96fD7v3Gnzjv4FWM1Dnznvh02FO6lSsTTlkNcZoEuj8KWLzrzA3tBVlEct8Cvu0mrenagZsdhv4jh9gznoq/FvQcJwjMR2XLxf3P06w7vPNM3n+e7i5cWjuWBVjk/cgH77jaeS35oFGOxAv3JO4Dt8GjIUC/fgFz1+sYr8r+BqXmbr47PHrYtbSz8Z4nQYfeibkKAK7iDF5shmdUZANn3kk4tIE6zL2of0PhqHDz4btvwu5D6yFChQZy2Wfw+34BzpeOB15V8Qifvhbob7wEeGH/7ENMuAWsIuHoe3gg7q2JOkxMgtzBQ6dT7qer0HaaWzL05DHyhjfbsu/jGV+HQNZoeu9F4KnoAdc7/F3MU5HrLcHegpx1q7+ovzxD/E1VDP4XOcX0BVo846TY+bKxJparDVlz3zPwb+aYSw37iAeV8A/3XAJ4izEgM5exjbnfwr7iXF94EroNJGjjp/jGwrawq9sGMf1H+R09MuwwTcidlgEe3AY9M985LFApxaYR5uMptzwMfihH+Krb+gaAOjDGzDG0yEX4JehOh1/PcZZxtxUYBmPCb8V/Yi05HwIeXtGN0dYN4XzfSd27/U7oRORJ6texq7PzsLanIXQw4gN5/E1GTmY/81aIeptH4IPX2qk2TrktTomkNWGGN9x8SfQH5CRsXwd3FLQrzd8krwvua+7DeP2T2I=
*/