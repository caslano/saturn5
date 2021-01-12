#ifndef BOOST_METAPARSE_V1_IMPL_BACK_INSERTER_HPP
#define BOOST_METAPARSE_V1_IMPL_BACK_INSERTER_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2015.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/mpl/push_back.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      namespace impl
      {
        struct back_inserter
        {
          typedef back_inserter type;

          template <class T0, class T1>
          struct apply : boost::mpl::push_back<T0, T1> {};
        };
      }
    }
  }
}

#endif


/* back_inserter.hpp
jDtteA67BOMOGNrew2m0jYkKilCf2w/j75VZt9SBaSgHH+4v065pK3Oq8Tlwyacf40cXZFnIWz33CpT7hIzjeXPlBXIl7S4H749XIeH2mpTTOn6ydh4QQFr9+b+a9ipp1zPui0QtbddnpJ1Vi3EkOj5VW//+UgbrE9HqPfvvmKc/aRMZX26aNt82Mt8YmdaPeCn+X3kCT/JSp09i+m6MuzdN1ybyxFbfUdYnMmWersyjKu2F
*/