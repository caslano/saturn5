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
6gSoIKqYmsa0Q5UMqjOqDqB6oEoDlYYqA9RgVFNAnYtqDqjzUVWAykS1HNQkVGtAXYxqPaiZLj9Qc1x+oApdfqBKXX6gFrn8QFW6/GLcL86E/EDd6PIDdavLD9Qalx+o+11+oB5y+YF61OUHapPLD9SzLj9QL7r8QO10+YHa6/ID9YbLD9Q7Lj9QH7r8QB1x+cUa86XLD9R3Lj9QP7v8QJ1w+YE67fIDFRWJ+YGqhaoCVDyq5aAaoloDqhmq9aA=
*/