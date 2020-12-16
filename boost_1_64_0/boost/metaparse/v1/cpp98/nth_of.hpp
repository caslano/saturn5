#ifndef BOOST_METAPARSE_V1_CPP98_NTH_OF_HPP
#define BOOST_METAPARSE_V1_CPP98_NTH_OF_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2010.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/nth_of_c.hpp>
#include <boost/metaparse/limit_sequence_size.hpp>

#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/preprocessor/repetition/enum_params_with_a_default.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      template <
        class K,
        BOOST_PP_ENUM_PARAMS_WITH_A_DEFAULT(
          BOOST_METAPARSE_LIMIT_SEQUENCE_SIZE,
          class P,
          boost::mpl::na
        )
      >
      struct nth_of :
        nth_of_c<
          K::type::value,
          BOOST_PP_ENUM_PARAMS(BOOST_METAPARSE_LIMIT_SEQUENCE_SIZE, P)
        >
      {};
    }
  }
}

#endif


/* nth_of.hpp
p1vCySGwkd/8cqf7zLa/H9SX5127dVN7r/G618Q7YY7mfDoL7bBW/aeOTUOVk0Nz5gdy3RJ/zcsmz3v1kXt02UKLydviPc4B7uAtM4JbeqPAHfrQbD/H2/+fGb4drS/o8a/eiq+ZYCJfP47TrotreWc9K2vS3EVo+79geVq1p75u/EnHm9fe4T0+yRvmnrTXcvgRcH+Yz3YFvpfTGe77Cs6SgoE+reRoBA+PK3PYZyozgtzmHY+q03d/mJGqhVLw9JugJsINa/R7bL0Zi497+YhXCvDj9+lKr/3c9xqrw4QbeTZY2Lez/x9J68VSN/BkCe2x7CNv3RKeFODtcsEaHDzc6+N/9OwJbJsQaUb8t36KoV/wUgXrbdxQv+OOi/Pco738iUtsz0qXiQf3u8Mcs40e1hMThn5a0lz0HO0i/0/0ber4cP9LvCcfnRabqe2ExXIRbwctntTr5S/5Un42nz69ZzY+UT6q2sNHnsEcOac51RFr3/sGD+f0fnOytGquU7gaV2eROGXtMJqAhhkHx7bIVZss9GcN/Exb/XTNuT+cj0FrR3GGcZMPb9eMBxbr1Dh7dXW9MxY2RQv4uRRY2Q1W0+IFT/Itt/BZLb3fAUfcgX14tix9XkaPV7eWrHCxShdnC3Lb/Bd1CcP7w9AXzgqWZoHzo3DdKX7iGD4bTAe10+MX4IpebJkNTrXFE/XtRa+fENekt/DheLmhV5/d1FO4vvhsmNALt2+kK5239dLjozrbo7j6myB+hpdnKQcnOtBx3c1Q6+OESzRaebobzp6rZo6hdj771JzAjDDqRJgVV79ZW+uatP9xPXrB553MJWiM5Ufh+HDaEgbC9sDgKHJA17Xhg0vnpUU348DBcC0VzYKrRzenEyLs6SLvfoge1KNf4Z2i8jelK1zjIbb7/1Rf01le92VX5858dkBfdXC+mWcDr6e3Q+mZFWYAk8o5X3SWcLGP2RJeaKz/ezwTo5Tiqke3V6L33fNedvGq6nznqPg85XPumB2nsJbp+Ak2znFuns79F9tPmwTing9mnxOvZ87wH3rWWs1lKkmz8fa98H4W+RtpzpWKVsn4Ox1cRE1Hhc3pXS94tgND5+Oub9fCbxxVwj5SrKRJact3OdUM7MtVh95OT7tdlbfS+ryCWqZbK/bTh+aRIY1hIX07YgeseCEej/lbevT3PvprPcyd6xzlhnPHoHfGvSGtYB6NFMEPN+BdOjzkOWHbv7RW4iMBZwK8c2o8uxxHf68P55sRB/+uDx256BfxiCFG6nGar7XuZV84+TC/mjaXGNOWKa19aSK9XsQ8U50F+sLiB7AgDm3ex9yXzqlhjXFjmuv+gg9o2zy9aODOZiiz8ADurj+dJxOfaPIXSvPOmQHjvlYfbeiexnAIBnR5TzMl1seu8fyZ1+tdv6NHj5llB/j7Gmp1KcycBe/6iPHZUJjkmR+90C8hzwBPPpqzVKJnj9j/WF6hIM06IzHPCvtPDYLb1lbloOvnUQupYdRPzh+r8JNy1Iu2TbcIZtEUhYfq9YJ8dKT3vxVX9+zinO5NQzFYyifKeYHccJWm3JUFLjeEj/3ojm70hvyXU5ezHpkF4LHKC9UJ/hpAEzTDs4fl6Da9lqIGX7iZxqvuvUXVdRe+7oz8pbSG17CiMuxXP8lqq+/ivAjMaqcvb6Wisb6BZfNwvF5qi0eO4c2uecVdPX3bTx173YRB+kpv/zQU9170bFlBGIa7fzls3kCPhMTSl2fVRDPc3h8O2XehXp431y+Hb9v7Df4S9tfoCB+dfaT39R+uBJ+HsoetfGOk8yscWOClfvtUX6ufG+vlFEd13SSuX+mj5uI0D2ZEmg/TIB/FsmM=
*/