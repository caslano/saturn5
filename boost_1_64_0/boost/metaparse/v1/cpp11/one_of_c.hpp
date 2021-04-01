#ifndef BOOST_METAPARSE_V1_CPP11_ONE_OF_C_HPP
#define BOOST_METAPARSE_V1_CPP11_ONE_OF_C_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2017.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/one_char.hpp>
#include <boost/metaparse/v1/accept_when.hpp>
#include <boost/metaparse/v1/error/none_of_the_expected_cases_found.hpp>
#include <boost/metaparse/v1/cpp11/impl/any_of_c.hpp>

#include <boost/mpl/eval_if.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      template <char... Cs>
      struct one_of_c :
        accept_when<
          one_char,
          impl::any_of_c<Cs...>,
          error::none_of_the_expected_cases_found
        >
      {};
    }
  }
}

#endif


/* one_of_c.hpp
MTM3m0O8EwgVwm3z+keM1nDXY2EryMGXu97RmqEtW6kqLB7OFeety4QvqHuk7JA6kgKjDtPhpRwWPO7tFghncHlrhX/Uxot/hJc69kGcI8rSEpFta1cdMxGokqgUpvUg2N8Y74JGFjOai70OrfmoHADDcYubmOPewUP2P5aSz51gsVKHfC7g69UFCD7VK//pD7hfvSjb/XW8guV/cf47UXrW/zuLsvbwrW3FDe5PaRja/yAIkLNK7Yu/AxbCg6ll1h4Y+8pJ2OZAIRZmj10vwYCaGdxIugHPbZAn3wAiYx1igLa4zxUsotyP901QE/dD1D9vTeW1/h1F1/jqiuECSRugKV8yYZqDTy2eDnWZZmG4BjvYgA5KrGlVPNbAC/rq0BBQ7l2IXcagRluWGZ26AD9xwDojVSInBqc/eR9/8qPZ44eMFe0adjvi2lea4XBLnKvGnVM7WTuomSQ6dE74KQ3IT8EtD9vFn0fRPAoBS01nZlDJPEePiz1zHRHwQ5HGk/NwaM+jr4lY4xxGO3Do0XUA0pBawalTpVcqyM9JuzXpwgPFahrUsM/wIw==
*/