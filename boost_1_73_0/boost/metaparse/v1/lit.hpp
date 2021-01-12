#ifndef BOOST_METAPARSE_V1_LIT_HPP
#define BOOST_METAPARSE_V1_LIT_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2009 - 2010.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/lit_c.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      template <class C>
      struct lit : lit_c<C::type::value> {};
    }
  }
}

#endif


/* lit.hpp
ybs+kHw191rvKfFrNc03eP58vb24PrDRHUnXZiYNVw2G49cceyaQS2Ki66G/TNGOaVn51yYG+bJRPrj+ILhGIJbPu4ZSLuwrRc3TBw/LTh2YFV078Lr6Zbr+VIOkZg+PrpVZkZsP3hD+rj+LpfdVPha9veDv+nnTH655+uTn1kS5YZKJ3+23Bu/T13SB6+xbBdfZlzX9qoGrjNPqjqjt8y9FTA2eC5S/DGoV+X33HXS8s2D7
*/