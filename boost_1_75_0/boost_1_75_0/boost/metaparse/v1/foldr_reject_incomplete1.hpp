#ifndef BOOST_METAPARSE_V1_FOLDR_REJECT_INCOMPLETE1_HPP
#define BOOST_METAPARSE_V1_FOLDR_REJECT_INCOMPLETE1_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2015.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/foldr_reject_incomplete.hpp>

#include <boost/mpl/if.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      template <class P, class State, class BackwardOp>
      struct foldr_reject_incomplete1
      {
        typedef foldr_reject_incomplete1 type;
        
        template <class S, class Pos>
        struct apply :
          boost::mpl::if_<
            is_error<typename P::template apply<S, Pos> >,
            P,
            foldr_reject_incomplete<P, State, BackwardOp>
          >::type::template apply<S, Pos>
        {};
      };
    }
  }
}

#endif


/* foldr_reject_incomplete1.hpp
oHQqcMgUILGreTnr8I38uZfa3ZG0d8+1hcIRmqXycBxHixQxaGuIFNGRgbnXS2Bk1/Mu5VyPpIiGnhYpwhqx32GJuc9eFO5HlAL+aZU3WFtA3vg44b+RN/aO+9/kjeiEMHmj8DMd5Y2E/0beaDqF8sZlF0l544vejHJk7CTUO4K81JriCIVS8oPOG+6KULRuPW3KXEifDBTWQrZldOGrtTy0xFw/JAv8n1ukjW08rx+SgaSUgflufzMH5WdgUH4b2mJneoJLoRyzJ7iYCjEDCUIuBmSSgIHtczomQhKZa32NgnN1Qlv6IUXw4+vn/E0Ek6YaqBzmYFLE26jtQcGkvB4yhYpvPi8EkzDBF3gkEaHZeMLTG5ullDQXpSTINygDyagMvv37MoG71pmC3xF0jXrnKP4bhmgtJg0fe/hRRJyINYe8F0a941+wm+7JIg8Svzb8BUoSTmK7/A0vY069NmSoTaHcBnZuOWbJaonsHBQxBzB4dskLNawSsbdJCALJIQudGyZAxmnsL4VsdpN72ABIPoPNcKKSF8loPoa9ImORIpuM2FfAKO4RK23132AMQbJiy1W+9Tp662J467fdz+it+EohpbAXj8UXi/j/pQYkWY3uvGaZAdW3XXcmwU/A5uPVkM3pARx7bC7fqr6PIxZQKlnArEQfwWK4BAVsOseKJyJ4EUrLtxlewlc2STqoQDpoBFE528JrDem2
*/