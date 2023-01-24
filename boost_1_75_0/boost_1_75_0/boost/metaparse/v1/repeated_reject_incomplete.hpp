#ifndef BOOST_METAPARSE_V1_REPEATED_REJECT_INCOMPLETE_HPP
#define BOOST_METAPARSE_V1_REPEATED_REJECT_INCOMPLETE_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2015.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/foldl_reject_incomplete.hpp>
#include <boost/metaparse/v1/impl/back_inserter.hpp>

#include <boost/mpl/vector.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      template <class P>
      struct repeated_reject_incomplete :
        foldl_reject_incomplete<P, boost::mpl::vector<>, impl::back_inserter>
      {};
    }
  }
}

#endif


/* repeated_reject_incomplete.hpp
6eKr050u/rH2QnLjxLk4+SDbGAhmyKM7O/2IclYC7EDf3kFyVqKN5CyfOinZp95vkbM+mcTjH6fT0c6PuyeTXr6DH3+dRud/5Mdv+fGdyTKq7JFJdOvf+SPl0+i4ht86ln9qOf/9iPFoCn80iz86mz+aN43jsxL2jAhIqyR9ostZMiAtXaBnMhE0mnU2Rsal5cKUP4fyzRRdweoacEXnsViFdGWjxBZKgQpEsEZA5ONHXCZs2Ud7Vbeeju4X7Ydz8MFW45Wt3JeWgmtmhCfAlAqzdRPgLSZuRFLZY7HNOOQia7UguelC/Sj39J3Y3E7U2Rv1NlPU2Qe0xppNa6zZFHW23sYvG1FnhtXcnwZ03I1QeWQkYjAT/Knl2ituLLQCn7yuHtdYOflQd2gP0BIrb5xoXmLnyyXGxmY774NYYc1CV2hWjCXGXv3TPqL6ZhEbKq6nq91ohAWEIPUUUIPAgRr15U4AVXbXs0f2K8IUEvTtAbbqlGz1QH07mktYVHKraFyrociQ584wuvMoMt35t302QVYURdZJdxbvwwWI4WO332YTIBAGkM+KqUT+y/ixlB9L+HEuP+ZPpTWQy3/3zGp3LfBAqlPRYi0MwOSs3724FvoYa6GPXrqME9alFO4eb9BuPCeSBLqyH5bDflwOaEoCrQcM3bAWImgt9GFrId6j9gK4ua97CYpvDqf4/e1Q/HpsdDe5bnBWF9Gs
*/