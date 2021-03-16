#ifndef BOOST_METAPARSE_V1_ITERATE_C_HPP
#define BOOST_METAPARSE_V1_ITERATE_C_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2011.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/impl/iterate_impl.hpp>

#include <boost/mpl/deque.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      template <class P, int N>
      struct iterate_c : impl::iterate_impl<N, P, boost::mpl::deque<> > {};
    }
  }
}

#endif


/* iterate_c.hpp
YLnOKajDev4go1NMJJzAIKTP6XRM5lLd1luyYkEKl3kKq2MhFQ3UkZYMReXuxJCyZOs+aF2FlbxtARQ/OLMYp2czYZklS6ZsMyT44WFPMh0tqKNCkm1tFm3NE5bwZNYMidcX1vDEIatOmziB2WyEzQJWTQL+iEP5rMWK2YhrR8R2ZJsQbu0QKy6olco2x2MRuKBTxeKtgci+2RpKpqBexoiL4YkJemt1G3dCJsQKyhaIiQ01d5kGBIo6mg1ziQE=
*/