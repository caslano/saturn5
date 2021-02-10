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
F16cO70JW3zsgvUCkNeKjOa+NlRBFUDnB5Yu5NS/mN1Wne7QYRQa6oFnvH61biwJuXNcyPWuZRrujb6w+z838AT0g/xTh2mJvGpq/5ed2YowjYa+J5ewwGVksUzY50l8sVhNAjibObbnI6PrFVtNLz//SW632+1gt9sNlFKdE7Cr1SReXo+PoFOAD5NoPIkDeHXKEE0B2AazYW1nHJuF8brGKvPtmsRHsqKz1LxMdjUOgJ7RAcnt+RV+oU//pKckWR58WcKu67598x4rR8dILtXGYW2E42trNTg0SOsuV4iMl6Xf0sETnkN5W55na+99Lz05GXpfvW9QSwMECgAAAAgALWdKUiEs6gtEAwAArQcAACMACQBjdXJsLW1hc3Rlci90ZXN0cy9saWJ0ZXN0L2xpYjE5MzYuY1VUBQABtkgkYK1UX4/aOBB/z6eYci8BpaRb3cMVuqdmgW65UkAh29VKK1kmmWxchTiynV3Qbb97xyaUPfW29KFGxI4zvz+ZmTjs/b7hQQ9ODub+jAbNDrFU8gum5v+jGXuE/Y9QtzSfEgnhCHlkXTgNeQTfQVir8tauGTsldGu92UtokbfMLmmHYBY5kvVOibvCgD/qwtmbN3/BS3j96vVZAGNeCSxhZbBao7oL4G3mdt4V
*/