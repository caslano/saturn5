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
CtKPD76t/nT+oQnYsDHTtVWRBLEvZAjRj0kOzL/HTz9ATHLFY+yWYPKHMHygbRmoM0emdipRKdmTbIzj9MmIi08V3/Y75/9NVWdPpJCgCgx4+/C3k4ArrCTdrLepHnPfPiq/+Izj3LAxheHzaOEXMYjrxmabCm0nXfCTu4x1/ERaL6bOcHjNLwuwx4fAPy7ZXjVtHpkOvkDEBkm5kEOL+lZLHP1XI5QuZ1BmaF1nYOsALEBLwRM8jyBuwailn3emTRBUIOOhuWoHnYKLHAFiIGVi5S9NjkMoXQeEGEd1euA7Clx+Rag7I6XT/mH2W4/1LOfGM42jG2AQIyqHxgCQyI9U4X8wccWjhWAVjo7wb4twn1pi3IaZT37fsVYTj/TVAUjmb4TV+rVpt43jjf7+HfRXyfCOXjetfiTc2WyRH0t6Kk6xqr4BNTM2Czu487ve8OSAFCNu9X65zC93nQ9KtYjwwS/W3lu959INAEAvlXEfj1XyqndCD1N1C5NktbJtmUC8RjCVKnZ8HAhX8ieT5ZN2qq5QFOKbhBwfY//R3WXUhAuRTIBuJ0i2kg==
*/