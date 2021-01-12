/*
  [auto_generated]
  boost/numeric/odeint/external/blaze/blaze_algebra_dispatcher.hpp

  [begin_description]
  tba.
  [end_description]

  Copyright 2009-2012 Karsten Ahnert
  Copyright 2009-2012 Mario Mulansky

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE_1_0.txt or
  copy at http://www.boost.org/LICENSE_1_0.txt)
*/


#ifndef BOOST_NUMERIC_ODEINT_EXTERNAL_BLAZE_BLAZE_ALGEBRA_DISPATCHER_HPP_INCLUDED
#define BOOST_NUMERIC_ODEINT_EXTERNAL_BLAZE_BLAZE_ALGEBRA_DISPATCHER_HPP_INCLUDED

#include <boost/numeric/odeint/algebra/algebra_dispatcher.hpp>
#include <blaze/math/dense/StaticVector.h>
#include <blaze/math/dense/DynamicVector.h>






namespace boost {
namespace numeric {
namespace odeint {

template< typename T , size_t N , bool TF >
struct algebra_dispatcher< blaze::StaticVector< T , N , TF >  >
{
    typedef vector_space_algebra algebra_type;
};

template< typename T , bool TF >
struct algebra_dispatcher< blaze::DynamicVector< T , TF > >
{
    typedef vector_space_algebra algebra_type;
};





}
}
}


#endif // BOOST_NUMERIC_ODEINT_EXTERNAL_BLAZE_BLAZE_ALGEBRA_DISPATCHER_HPP_INCLUDED

/* blaze_algebra_dispatcher.hpp
FK55T8TiOEOUvCRYWE4ivB+3Yxk2TA/JaJsM3dZuJ9ZtlOtWsXVbrdZXpWYUoHrdMOr29bPLi/OLyL3NjhT7ErfnCyz7hWn79s7M50k0QyGUeVmsNz2uMjPZZNbmMRamY1csLx2imZabP4QrJbCsE47HohcuKlnsTxxh/L1z0FNmZHWozkmlZ1YOpZL5JHC8AeXPGOkDKyB1zAa8N0RGcnsK4d5hAI1lWI3jKGR8jHAUQhfS
*/