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
ksaHeihVdaCIPHovhdMSAyEPqJQrpDkGJ3Omg3K4+TbEhtNA8GdT0+LNQUkEA53BDMazDiyp4SaGj+P5+8liDh8HaTq4md/C5AoGN7fe2S/jm0tMPcdgGthjrZnB4Bp4VQvO8k3ML/ck0bdcZsLlDDqWGUxVJ/qPCKtAeHErxYtKgcAOpRWrcrZ0q+CCS8wuGnezkmroL9LrXvR3BND8xCohtEBmz1E0xMMF9H3pOPgB/Erw7fa2h83Z9ohRsyZcctsqZArjh0O/O9+GYVorTZauKJj+3euRUZpOUjIb/zb6A911OueR190EJIYhXI8ibjBNB+mc4CaG8Akycjm6Giyu52Q2fD/6MAoQWljoAcs6OGn0J9M5CXZx0HIv0Q8g3y2urkZpfHCHlxj/OkrfTWajGF5fB/Wkj82CgwRqhf0tXbUMZY0tW9FP2Dqh3TX7izlMFhTY0oA1cTTMdJLOdzF2zB+kCBuvULoKhkGNF91vdqq9yI/PotZYKEXXWOw2HUPHA3DYRVj5+N+A5SiK9udt55l/BG+xf7HVXon8DC5eGRyd/nsnO/GBbVcoueq1aOP9S1odmO62AJ9x37AZEIdZ4Pz09YXZEubf1Wer6Ltd2cdwGih5dv+mCaR6ONvdAXZWLdmFZqy7L2+w
*/