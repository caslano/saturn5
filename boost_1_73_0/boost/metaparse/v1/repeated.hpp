#ifndef BOOST_METAPARSE_V1_REPEATED_HPP
#define BOOST_METAPARSE_V1_REPEATED_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2009 - 2010.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/foldl.hpp>
#include <boost/metaparse/v1/impl/back_inserter.hpp>

#include <boost/mpl/vector.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      template <class P>
      struct repeated : foldl<P, boost::mpl::vector<>, impl::back_inserter> {};
    }
  }
}

#endif


/* repeated.hpp
RUhvSklUpKKQVEpNzdRMpmZqphchz0IyViiyYkMIeb8V8lzZrOyGlhCyQhLy3u/c+Z+5d25TTdj33I+fb+fMuef8z/887zn/B+/lCC7lSL7EDL7GTP6VWVzN0VzLHP5GIsexOieyKU/ncZzCATyLQ3g203gep/IC3sgLuYDT+DCnczEv4hpezE94Cb/mDP7EfO4qTy5nbV7BJryaHTiHh3Euu/A6duP17MEbmMUbeT1v5kO8
*/