#ifndef BOOST_METAPARSE_V1_IMPL_FWD_ITERATE_IMPL_HPP
#define BOOST_METAPARSE_V1_IMPL_FWD_ITERATE_IMPL_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2013.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/is_error.hpp>
#include <boost/metaparse/v1/get_result.hpp>
#include <boost/metaparse/v1/get_remaining.hpp>
#include <boost/metaparse/v1/get_position.hpp>

#include <boost/mpl/deque.hpp>
#include <boost/mpl/eval_if.hpp>
#include <boost/mpl/push_back.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      namespace impl
      {
        template <int N, class P, class Accum>
        struct iterate_impl;
      }
    }
  }
}

#endif


/* iterate_impl.hpp
oVFo7xuKjS4C+GxDAlNdShFAWkl1hYrbGg3LL80LvasuB9NS1VKV3aW8rFAkOxybxb//4j9CWiSNQj3O90K0jyBrgxwr3SRiQ/wO84f3o0/kgqnZuHH0gOy4gUlVGg1VZsjC1G4I0pURsULrmi6ctqERjc4+gychNyHwXiERGfwj4z54U1A6k3tNRN39MJW7ncEfU3WF9Oi83us+vZUirfYZup16wHlvtljH82XQM7rLxSrmpm6jSfqV3HC6a2zpolPwSOioQFqUiLZdjliNTQW99Woyna94VX6YjnEhyfJSaXVXV5bN0piXk8NEd0VC3EeXrH/v2JR5C3acklxjA7pAOwtQJAo+EAW4qpDaZeHBYk1OjdQylVXEjIud4mn4HDYjsQD+qtphP6gP3tOGxGl49k3Fe+/Pq/V88eawpzTFmsK3/NZ0nDI+S7DQmgN2atw//CKXT9NhQyf48Arede+I/l+/ka7+oamfn/vEL7+c31BLAwQKAAAACAAtZ0pSMeF7hAgCAACmBAAAHwAJAGN1cmwtbWFzdGVyL3Rlc3RzL2RhdGEvdGVzdDEzNzJVVAUAAbZIJGDNlMFu4jAQhu+W8g6jVFwqUhNgd9UoRKqgKtXuFgTZ3tNkQiyCHcWGlrffsQMU7b5AL0k8
*/