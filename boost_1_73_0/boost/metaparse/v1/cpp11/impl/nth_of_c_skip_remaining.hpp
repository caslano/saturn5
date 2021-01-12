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
v1vgGleDc/hWimvMtzvF30lYZkFLxtG7w/1K0a56Sc+Ic0zs2X7x9os1TJwWPceN2tMu4Rlfcl9nmrrOi57vfRaeGZt3Zs4QrZ8ntDv4kXOzW4QS+g2Mv6vIrSVt1nF4uXhfgmvly73iGfmAhPb2CtvOQ/z9TnhWqx64j/G+UDv4oeVV/SGWl7FsHJc+cnxW6riEJ3yFeVp9y8/+4+9YfzSfhOHvfyg+vNHw1t7BVmGLWPvw
*/