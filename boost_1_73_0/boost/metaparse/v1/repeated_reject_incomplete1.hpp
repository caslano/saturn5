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
/kvCb88fxd7B02u4P85L+O1vmVF5s5RSlC+vOz6pj7+k4Yrjt93HXX0zH2ex8XJX8f57vk8q45fYL2AuswvSntTH3ThRLbGNf+UME3+7D8hL6gcj5M/a8Gwk2x/3JQvzZ3zx/BmSkT4pyqPZ2/l8ZPqEpDrnScN5E35+fkV5sIuRkhibR47hxZ5JJJb1zjDOPArG2X+23MfRpPHxfEqso7A87Awt5ddvg0ssI1/a5VNBFmXm
*/