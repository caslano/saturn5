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
zS8Kd+JtfqD6oFoDaiCq9aCGodoShTtKNr8o3Cu0+UXhLpjND9Q0VCeicKfc5heNezg2v2hcPbb5ReO6h80vGncsbH6grnD5Rbtf9Qj5ReP+pc0vGnd6bX7RuAdg8wN1r8sP1L9cfqDWu/xAPe7yA/W0yy/a/bJIyA/UDpdfDWP2uPxAvebyA/W2yw/UIZcfqMMuP1Cfu/xAfePyA3Xc5Qfqd5cfqFMuvxrul1FCfqBiUO0FVRfVIVBJqI6BaoI=
*/