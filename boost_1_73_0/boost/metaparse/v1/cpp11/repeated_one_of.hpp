#ifndef BOOST_METAPARSE_V1_CPP11_REPEATED_ONE_OF_HPP
#define BOOST_METAPARSE_V1_CPP11_REPEATED_ONE_OF_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2017.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/one_of.hpp>
#include <boost/metaparse/v1/repeated.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      template <class... Ps>
      using repeated_one_of = repeated<one_of<Ps...>>;
    }
  }
}

#endif


/* repeated_one_of.hpp
fXUL1vW2fi22XcegQkvxSFnbbWWfsk/Z53/j888s/5+Tm/WrlP8veL/5rh9f7iu97ytrw+2/7f7Rbc+v0n7b9rbdVtZva9mn7FP2KfuUfco+ZZ+yT9mn7FP2Kfv8a9r/zzEzZbJzf402AKM27tqF93/XieriMvGN312rG8fr/OWMHJfbVZ2/0tSpSK67vqU+nRPrcY4bXrx+/sKQpv1Zk3XZQeKmNimephML2vE/LlvxpW3X
*/