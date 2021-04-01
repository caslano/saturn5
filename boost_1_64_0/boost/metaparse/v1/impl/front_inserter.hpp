#ifndef BOOST_METAPARSE_V1_IMPL_FRONT_INSERTER_HPP
#define BOOST_METAPARSE_V1_IMPL_FRONT_INSERTER_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2015.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/mpl/push_front.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      namespace impl
      {
        struct front_inserter
        {
          typedef front_inserter type;

          template <class T0, class T1>
          struct apply : boost::mpl::push_front<T0, T1> {};
        };
      }
    }
  }
}

#endif


/* front_inserter.hpp
S7LQNM5/a3st4HKm2q0aBQKegcFX8IuWgWTFtrPCEruYcPo+Hy/+siDZtSxvvl0lWL3eaksXdFRAfPINt00ohYyXqOLB+V/wommn0XLTIzhMBEkzzi9evzRXr0RnW1v+ETE/cW8YUaHGGaomEZ5GkpcnEBPyWWGIUoQjqcQXZu8Y0l+38vM6hc/voLKe2YK46VQxR3E5ED+MrhNcuKwi4grhAKWnMrTMScvwi3VoTq71o+pihZZtEJmb/CS9PiqB218oRXJuXkabORFLXWTmfHbmB/Wopns0pLRkUovftwCzOiFrzZHCZuzfJFRmV5yRypTiLEncHkbwL1GamkRrlbacf+t8cPYinRcovG1N/VMGwZHULIBMoPnzW3JI0DqvbnjWYAWsy/dZFGnKQ91akKHJasagVJ4Ynl3nvB257M7A7MAugzux+DVwJD6qG6bggrY5mkbZR/9vHX5vnHaDPw1xGX9/lEoymt4o+Zj11SBthP9cWDnZCzm6v3IKpUEUPHs/a2SvRegbz10rHFPQn7L6LcKVolQp4fXXRg8jx/uqgr5KtsXR+IH0sA==
*/