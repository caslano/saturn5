#ifndef BOOST_METAPARSE_V1_CPP98_IMPL_SEQUENCE_IMPL_HPP
#define BOOST_METAPARSE_V1_CPP98_IMPL_SEQUENCE_IMPL_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2013.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/impl/apply_parser.hpp>
#include <boost/metaparse/v1/accept.hpp>

#include <boost/mpl/deque.hpp>
#include <boost/mpl/fold.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      namespace impl
      {
        template <class Ps, class S, class Pos>
        struct sequence_impl :
          boost::mpl::fold<
            Ps,
            accept<boost::mpl::deque<>, S, Pos>,
            apply_parser
          >
        {};
      }
    }
  }
}

#endif


/* sequence_impl.hpp
4NhFBgEStkUPhS2PDw8hQp13TL0zIxJWQUI6g3YlnhGTAYSvKkZqI727bT8Bd9W489CL2DdsZ3SBu4UC31QEClMNqBYC4LIaYzweZPqS8Yraxsue8XUQn8Ip3HkwTmUbEUdXO0Xgnfnu9vH+UZP4qjOTXd9hTJVzF9qVsFMAi1/YqjZ7+2Kw143n4JOJ4kHMCXYAgKuyhauYCLU8eL/5LsT/O7Pd44Ozwxy0zSyD2IgH59rZpbS5nA1oRGhdGBM=
*/