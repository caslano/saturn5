//==============================================================================
//         Copyright 2014          LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2014          NumScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_NUMERIC_ODEINT_EXTERNAL_NT2_NT2_NORM_INF_HPP_INCLUDED
#define BOOST_NUMERIC_ODEINT_EXTERNAL_NT2_NT2_NORM_INF_HPP_INCLUDED

#include <nt2/core/container/table/table.hpp>
#include <nt2/include/functions/globalmax.hpp>
#include <nt2/include/functions/abs.hpp>

#include <boost/numeric/odeint/algebra/vector_space_algebra.hpp>

namespace boost { namespace numeric { namespace odeint
{
  template<typename T, typename S>
  struct vector_space_norm_inf<nt2::container::table<T,S> >
  {
    typedef T result_type;
    result_type operator()(const nt2::container::table<T,S> &v1) const
    {
      return nt2::globalmax(nt2::abs(v1));
    }
  };
} } }

#endif

/* nt2_norm_inf.hpp
HwkzFf8L1yWLw5K+dPbIKzzm7GEq3iP3Dsem3GcqPix3JWeZdCip2mWEBK6dhQet0k7Ty2Vo2XEQLTv+Zipu1pYUN5i8N84rIxQdEl734tCwPONIO0dYTrTCvA99Z7Miusp+U3G/DEBa2oOoJ+1jGPdBjJ1hGsb3hzGM9yRVudrm2dIuOo34/ujHhbusUiXivVsp3GUStzd/7LwZnPF02o2Vn6ooN4HvIuunZWiqA9hmUOPewlHd7xyNqI72Dvs0z13beU6rPHdFvP+KPCtMAW0Rf5xIAXnvCC2+ksUrGL9fLqP4WlNxJaSGilFXPFu4S9rRkho1cZ8M7vgQzteYimEYXPS3h7EjXw9ElueJRIIwFUfmwcDyNbPv3bL85ob9z/mlmYrxdL8/yWvV2qY83t++BFs6L61qVpT8GtFoVZ7HJLoroSBTHnxb3WRBLcS7sFVL8QbeZyo+UH4qyn3KYFp+NbQfOdB+jRzHVMcqcnR13ui+EGYqvAkSlvbugXiX5yVtL72Ad5cUbjcVdjfghb89qGqmQlSN+toYMNkB77KC4wpM0pGmFZ0hxLssX/W2IW+26r0IJZV+fLWW93tq3nhAsSQ6XhD8r5YIEayI5fswMEb1fYq+x1Tf++h7XPW9hr5fVR+e2vHPKj0arpVTx8rx/1AaF6YGQo91meMozRqXZTS9tn1Wrt9SgnWCHJzjvZmPaIl6zYkVkcMt
*/