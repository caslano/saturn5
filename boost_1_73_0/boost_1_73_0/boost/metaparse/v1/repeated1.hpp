#ifndef BOOST_METAPARSE_V1_REPEATED1_HPP
#define BOOST_METAPARSE_V1_REPEATED1_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2009 - 2010.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/foldl1.hpp>
#include <boost/metaparse/v1/impl/back_inserter.hpp>

#include <boost/mpl/vector.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      template <class P>
      struct repeated1 :
        foldl1<P, boost::mpl::vector<>, impl::back_inserter>
      {};
    }
  }
}

#endif


/* repeated1.hpp
oIpTVbxW3f8M3b8ov1Hv+yp1P5n6fVd8uhovzFDHQyquVPEqnb+KN+nyUO/jDnX8gIqP6PtV78dxfVyVX7zq7w/o+qT7d/2+q+utVeUbVP4dur9T5z+urh9U+aWr8U66bg9UPEPFIRWv0vmrOFVfX8WZKp6h4pD2q/x3qPdthjoeUnGlilep+Lhuf3X7pfxGHa9U+a5S8VoVb1Ln26SPq/LcoeIDKj6i66+KjSqvHer6B1R8RJe3ru8qPqLi47o=
*/