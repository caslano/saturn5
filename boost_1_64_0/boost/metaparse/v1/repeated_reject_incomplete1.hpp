#ifndef BOOST_METAPARSE_V1_REPEATED_REJECT_INCOMPLETE1_HPP
#define BOOST_METAPARSE_V1_REPEATED_REJECT_INCOMPLETE1_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2015.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/foldl_reject_incomplete1.hpp>
#include <boost/metaparse/v1/impl/back_inserter.hpp>

#include <boost/mpl/vector.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      template <class P>
      struct repeated_reject_incomplete1 :
        foldl_reject_incomplete1<P, boost::mpl::vector<>, impl::back_inserter>
      {};
    }
  }
}

#endif


/* repeated_reject_incomplete1.hpp
wq+ieBq13KHE4JgK6RpJNxPrFnz4lqENQgURj/2nFDshUIXBz0IEe3z1cyf91Xw/OLsR6C4OBxwqEebJtluks0FBytDaRvKpGpA8eWxxXWQonqZPMjMLh+pJjlsisJU+Smz7+buHuyhddCwxpy9CfJKf4agJTm1VDWbEszVIZh/lBgxd0iFfMkzULn1PIsIeO3EmRlYha2ukS3zdsA8d6JI3lInybaOGvY1/d2B0CctjpoAFYuzHnxgX7X8OQYybzShERD3s6Dt6dRKmGX8HnOL5lu3MODaJk2rF+PLG/Fv/dNBjWQO3Z+XDbnAxy/JVvrQvZbAvnwIM0zu3G6871UmYViiMM55kzk9jJntku/YpoH1XFN2h1bSDe/GqtAu06gxmoJa7yGaWLoCpMHaZ97LOHrTsQFNv6B3D4AaS1GIvmil4TtQddCVVw+5RBJOYK59ZbngocKkwV4bn0AfmqwMoX/zsL1sORiszDHn3vGziK70aV+Lh9PQWzqQWpzbY5oI3R30d7Y3wLa8vCnmlokUR4oasVUBBtGWmqn4oN2lvFDXh0VSX3nROaw==
*/