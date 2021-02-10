#ifndef BOOST_METAPARSE_V1_CPP11_SEQUENCE_HPP
#define BOOST_METAPARSE_V1_CPP11_SEQUENCE_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2018.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/cpp11/impl/push_front_result.hpp>

#include <boost/metaparse/v1/get_remaining.hpp>
#include <boost/metaparse/v1/get_position.hpp>
#include <boost/metaparse/v1/is_error.hpp>
#include <boost/metaparse/v1/return_.hpp>
#include <boost/metaparse/v1/transform.hpp>

#include <boost/mpl/eval_if.hpp>
#include <boost/mpl/vector.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      template <class... Ps>
      struct sequence;

      template <>
      struct sequence<> : return_<boost::mpl::vector<>> {};

      template <class P, class... Ps>
      struct sequence<P, Ps...>
      {
      private:
        template <class Res>
        struct apply_unchecked :
          transform<
            sequence<Ps...>,
            impl::push_front_result<Res>
          >::template apply<
            typename get_remaining<Res>::type,
            typename get_position<Res>::type
          >
        {};
      public:
        typedef sequence type;

        template <class S, class Pos>
        struct apply :
          boost::mpl::eval_if<
            typename is_error<typename P::template apply<S, Pos>>::type,
            typename P::template apply<S, Pos>,
            apply_unchecked<typename P::template apply<S, Pos>>
          >
        {};
      };
    }
  }
}

#endif

/* sequence.hpp
jKFZURs77917tu8u0FjqOCoxZEGWJ5L+HnBdS8XLkH1ZzNhkNr9h36fzBctRq5gF7tP3wG0oe2wP5qhWqJwy48gChYVYN+u3KebAZZbfg4nyAWqEe9SgUwSOSVQJDSIrNchKF5WGNFLciSVHDlluUcYhBSIzUFoRFvBIR3GK8QMsCXnS1fiouyHTUkcC/D7jqn5UjnkA4BhGx9CM7YsZQ8+Hy1iD74M3GPcPofe/vGdE/xXiebQ2APBGIyJe4M8Fc5SzeQjjQb+Fe7A7BkP4VgnwDjfcq8np2fmECSNsn9fIcARnGJMdSx7BHR2tE0JVKpdeyb2z6/7lIO22zSoFOaLbWzX7buX/tW9/RPbH/QNKhzoXMuK9VC/F29Uv5AoGfas+BNTxX9Vf9E1M72A8GEBR3f2pOXzrjum8KOe3yWcKYJPpNtU/iwxzvSmB2E4I0uRsyBJdEL6dQZBHS7QlBu9koTOZU+r2bI19JCFUbi6hiMryPfBMNSUyO6VahMBtqBDEcrmMch4yx7FEZxuoXUgygSDkvWun3sADsjF2XSPgf9r/ejlfTGfjfXIxu7xauGRwGzOwXCN10t2N0AUqbFuYiRRC1qaydS3JYY4lVbdCiBVGmgq4Tk0IU78GFFdKsCUdHQFhI228US4a
*/