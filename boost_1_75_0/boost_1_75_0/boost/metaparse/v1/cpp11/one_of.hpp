#ifndef BOOST_METAPARSE_V1_CPP11_ONE_OF_HPP
#define BOOST_METAPARSE_V1_CPP11_ONE_OF_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2017.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/is_error.hpp>
#include <boost/metaparse/v1/fail.hpp>
#include <boost/metaparse/v1/cpp11/impl/eval_later_result.hpp>
#include <boost/metaparse/v1/error/none_of_the_expected_cases_found.hpp>

#include <boost/mpl/eval_if.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      template <class... Ps>
      struct one_of;

      template <class P, class... Ps>
      struct one_of<P, Ps...>
      {
        typedef one_of type;

        template <class S, class Pos>
        struct apply :
          boost::mpl::eval_if<
            typename is_error<typename P::template apply<S, Pos>>::type,
            boost::mpl::eval_if<
              typename is_error<
                typename one_of<Ps...>::template apply<S, Pos>
              >::type,
              impl::eval_later_result<
                typename P::template apply<S, Pos>,
                typename one_of<Ps...>::template apply<S, Pos>
              >,
              typename one_of<Ps...>::template apply<S, Pos>
            >,
            typename P::template apply<S, Pos>
          >
        {};
      };

      template <>
      struct one_of<> : fail<error::none_of_the_expected_cases_found> {};
    }
  }
}

#endif


/* one_of.hpp
HK7b5nAvGK+lepBSDMJ5A67bIJ1Geir6r2zRHic5Afay7aDu+SmZO8HaLkd47yT0+Ylwio1rNx64zdBuAPT/zdDvl+wzDk0Fj+hmfkAHFhQXTv/CsoobsUg5GChrAxirE3LdR6Vlr5NFQl+DQAw0Yx7iGsCGEThKgO+uhX1l93ppCXpPx3oH3A3Ssgh8VQcNc3dJMz6GlbgOONXB4ulPF6bB03fcGLPDk3Nn4pr9eJSGei1aJGyfymXb2f0YVmSCbKxPP+1rDKRX+gWVd/EsKUV8sm3R3stlfPLgmskyVaTH5SIvNtYtXtMOE8Z6ce00cZTqHxKmp8T5k6dbWVf+fuCdi9DB6VCw7HcdXjV1vLtZWkbHj3o1bthFV7sn/bLo8qDSXETY1TewuIPQ6w6Y/eIOIkFzpqnpv4Nln1sWgF2SQ4PsZaWJyGXejvLomd6eo86b1RhEWg7MmE/Z7lV2aSUo9ar2m5/hvb81Ye8TDj0aA5C/wdMM/fxf9g+n2UOUSVuNonpsISo2vIs7oJOL7piDRIkp0qJePveUXxYWK3/o8Lnf9UnBd73KDi3YRasUgO2s+q1AnIBOIX2afgZOLi1a0QEjfefvJ6BSP+xDwpgWiPYCdLUnEtnjbrUEPN+trYOesR5G1TBZgZP/xT9gh32j3g65DEuLlgOaGBs3If4iC5lqJx6OSVmg4cSWVqVgiQnhVsO+80GlDSgL
*/