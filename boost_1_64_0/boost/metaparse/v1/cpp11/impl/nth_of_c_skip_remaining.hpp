#ifndef BOOST_METAPARSE_V1_CPP11_IMPL_NTH_OF_C_SKIP_REMANING_HPP
#define BOOST_METAPARSE_V1_CPP11_IMPL_NTH_OF_C_SKIP_REMANING_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2017.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/is_error.hpp>
#include <boost/metaparse/v1/get_remaining.hpp>
#include <boost/metaparse/v1/get_position.hpp>
#include <boost/metaparse/v1/return_.hpp>

#include <type_traits>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      namespace impl
      {
        template <class FinalResult, class S, class Pos, class... Ps>
        struct nth_of_c_skip_remaining;

        template <class FinalResult, class S, class Pos>
        struct nth_of_c_skip_remaining<FinalResult, S, Pos> :
          return_<FinalResult>::template apply<S, Pos>
        {};

        template <class FinalResult, class S, class Pos, class P, class... Ps>
        struct nth_of_c_skip_remaining<FinalResult, S, Pos, P, Ps...>
        {
        private:
          template <class NextResult>
          struct apply_unchecked :
            nth_of_c_skip_remaining<
              FinalResult,
              typename get_remaining<NextResult>::type,
              typename get_position<NextResult>::type,
              Ps...
            >
          {};
        public:
          typedef
            typename std::conditional<
              is_error<typename P::template apply<S, Pos>>::type::value,
              typename P::template apply<S, Pos>,
              apply_unchecked<typename P::template apply<S, Pos>>
            >::type::type
            type;
        };
      }
    }
  }
}

#endif


/* nth_of_c_skip_remaining.hpp
AVvAfxTwosoa2ZIb1oQUZ3o4yuJ7z4HynYJ89/50J47WInI6gegJRkIckKkWAixYwnl4zsums/YpZ+REKVaAYSzC9kIN1V6Hhl1k3CX4+b2DWOSMfzSgKGrQRoXqUzuB5YfRm9dYlu0ZYt5LMbCZuUpATWyncAqqM/C9iJFNVBdahDDtVHKKbUDAU+h36sAet2SQo3TCwZGm7mCcyHV3eRs/EYUoF1dx8KHFEUiNRcvluUKRH76IV8GAIo29WOdLAOqhGUKHmaH8Uke1MofINVpEBR3OEuFqih3bspBueJuy60GwoBKibMxBsTcDJWs8y6cwfWmIY94gFqUpAt42+CAM9BqfveCT8ha/Dm38J3pMP/RToKU+RJfeRb9r5Abza3dUbENHp/ckSaqNFJ8nFH6AppnMpZyBLW/CbM2/ME3pkkhKWFuS4y1CKTYO33FeB14Xv0+/PGQgMwUmpmfeicLTFue9CTwf+mV9IvYLFK+NqTG6QGadPcR4T0QQrYcBahAO792V1It1uX7xz1SE5m/ws0Gj0dwcnIVlUdSYv28AfbSHbT+HEw0Mag==
*/