//==============================================================================
//         Copyright 2014          LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2014          LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2014          MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_NUMERIC_ODEINT_EXTERNAL_NT2_NT2_COPY_HPP_INCLUDED
#define BOOST_NUMERIC_ODEINT_EXTERNAL_NT2_NT2_COPY_HPP_INCLUDED

#include <nt2/core/container/table/table.hpp>

#include <boost/numeric/odeint/util/copy.hpp>

namespace boost { namespace numeric { namespace odeint {

template<typename T, typename S>
struct copy_impl< nt2::container::table<T,S>
                , nt2::container::table<T,S>
                >
{
  static void copy ( const nt2::container::table<T,S> &v1
                   , nt2::container::table<T,S> &v2
                   )
  {
    v2 = v1;
  }
};
} } }

#endif

/* nt2_copy.hpp
A8jV509nHNzmiSkAp6n0lw4m92oWkAsBW3Fe8XSfyOK6zp4Lv91mz4bsDdVi+cl4sW01UzDCTBJ/TcWgCtd4ydgPUruroiqN3cGB9O0xdgWX9VxFvDPVXRVfaYwAr5EiwsBVIgjh1baeh21ph11xlFPC8cHHXTHumB8eiBAsnu5HHmDjNREX1U7qoFji7yllA40yRKI+UnTfQ8fbL73AtpnAeeIFtvcklTMeLPI3ARUyYZ49KELg77igRKf0aoP8vNdnT+LvV/S7nn7fpt/l9PsI/ebT7wT6ddDvQyz90/g7gPKJpt9t9LuRfrtQbDf67U0hVfR7kH4d9HsL/SbT7zX024F+b6JfkX7H0O84+n2I5c/weYrL9ony3RbiUxHyLW7Gp/hUpPS6/IRqU8i2+2FVVWfzDk1MD6+Se2LDuO/LxGbMeLtWcd+XDc7Rie77JpIFt2dELN72gcd2jZ88j207Ir4yErflKkfECajGqWTLqpsU82/ehocoC3fNvUoxT/LyVze9MaueR45hg4CdRhcsWAwNj40F7MG6yxMV80AvacHJPqeN/BRJFbmZgjs3G/5P5OuDps+ZnxZzj7JMfn0M5/+0ydmLYwqPFbQGh6u3KC2KxWsJFfPOxwL2NRvofxe2EaXhIKQMPuw/SOeFt0DiMjml4GLQfmPDeRYPlnuHdC+nnStROi+a7GhdAeCCmHbehXepjDQVXyV6
*/