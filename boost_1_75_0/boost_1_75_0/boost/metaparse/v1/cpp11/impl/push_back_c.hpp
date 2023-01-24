#ifndef BOOST_METAPARSE_V1_CPP11_IMPL_PUSH_BACK_C_HPP
#define BOOST_METAPARSE_V1_CPP11_IMPL_PUSH_BACK_C_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2013.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/cpp11/fwd/string.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      namespace impl
      {
        template <class S, char C>
        struct push_back_c;

        template <char... Cs, char C>
        struct push_back_c<string<Cs...>, C> : string<Cs..., C> {};
      }
    }
  }
}

#endif


/* push_back_c.hpp
Jq9DLrSG7NpXJK5jcE/CHtmsuz7K47n2NuNH1uDAtBdEewEHNHjKeahnSdw/Ji8I/8Iy7B9M/LfrCpMXJEbwS944YQy7ctLRhhsFMGkbloxAdPAVnjkp3A748GhQncA7JGBrju8QrFEaKNO9i/X4Flnu/O0tMuebhC2SxCy8ajG2yN5zeNZ+sUUS+M7zkraJj2zPuE98yrYipUlsk8wzcJtQfeuPY1TfGKZp98L6D5b1Jl/BmeeFjwTRoXCrFrAk85ozz+nBay79O60vsNMASgVAKXjNxPU9qT+vxwlyG2As9o+BMg0zQKtFVp+txeduke7FypE+93vSvUhqlECqz71pwVmLO1HNKd2HZe5tm6LT8Wr1PqxmNh02hyoQYqEcnexQbAqGF891T06tvlWZnprb4p6euqgsqEx2AAsHuzhga4ENeTaq3/uBnA3UsNkyGHWlt6KXxumy+9e52UHcrR9puV/DEAbiq2rqGYBsj05qgjUl5+kYXG7O36Vds5K8O8IjY6/9dgYq96/zBsD5RN2xKHHd2UYK9YNSV1xHctyc+WdcZmY4xoCcqL+F9X2o4AMyP84m6M3ZWAYlCqdmiw7I6imYkBI+YmtYo8HlSMeNUnB9tHp11L8WTc6zcFWj/gaEnM1TX4B8tiCTn5A9ccRS+4LnbJZ6/6s+5YBv6Xee+upXfEt1+FjpKXBLtc/AUxNEYhZ/3f7wzUAM
*/