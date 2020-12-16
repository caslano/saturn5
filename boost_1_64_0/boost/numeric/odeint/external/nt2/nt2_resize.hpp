//==============================================================================
//         Copyright 2014          LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2014          NumScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_NUMERIC_ODEINT_EXTERNAL_NT2_NT2_RESIZE_HPP_INCLUDED
#define BOOST_NUMERIC_ODEINT_EXTERNAL_NT2_NT2_RESIZE_HPP_INCLUDED

#include <nt2/core/container/table/table.hpp>

#include <boost/numeric/odeint/util/same_size.hpp>

namespace boost { namespace numeric { namespace odeint {

template<typename T, typename S>
struct is_resizeable< nt2::container::table<T,S> >
{
  typedef boost::true_type type;
  static const bool value = type::value;
};

template<typename T, typename S>
struct same_size_impl< nt2::container::table<T,S>
                     , nt2::container::table<T,S>
                     >
{
  static bool same_size ( const nt2::container::table<T,S> &v1
                        , const nt2::container::table<T,S> &v2
                        )
  {
    return v1.extent() == v2.extent();
  }
};

template<typename T, typename S>
struct resize_impl< nt2::container::table<T,S>
                  , nt2::container::table<T,S>
                  >
{
  static void resize ( nt2::container::table<T,S> &v1
                     , const nt2::container::table<T,S> &v2
                     )
  {
    v1.resize( v2.extent() );
  }
};
} } }

#endif

/* nt2_resize.hpp
5Gaz5voq+WhbuIU8bk2g7QzMeR5pb0+QryRBvjtJfxfpH9bfl9Q7u9cCXxQ0dmVUzK0bXNu1tLdkg3x6MNZc+ArXcWogNMU5mNqH3wR4WdDa0dCEz8IdHrYdsFT4hkynT9+R8vEUc9Emc7B0kO2oV9+kvwbYeMfLx1v4ABRxt7KhCf3sExw7YZNy/2JzSXTsvFeNsVf3Qnc/6Sy/p0uNz6vm1wvdQwX4rTLlPqz59UL3SAG6z40wPrIFysWP5/b0kU2gywZxusdkDgBezk71N4Dvadl6KfMJTddLmU9G9vKC38rvHE+LTLGyOnmG/UzK3C02PK8w+B+nxO8EeN4rcO0KW7HzHt5oMPyuNvx+btLFJn3pCP0urNWt6OK5lHp7dpN8x9L6i+twQPAC8/1D+Vpv59/q7iF4yBiTpu5eYl7gI2Pr783Y+oeUyKPv12WpEy3PK6DV552t2B/r9Eb5LsHvGPFvJ39m+cDx24fIdp/x0fwbaQHX58RIR8fZnbJ2FHrwfl21L2CxtdubwCt5QROX9y0tA+Wdkrwv6W7FWNuej9KTS/cZz68729GVzyUQmUffTvUZP87l0H5dUajw+reZa9819vAe7eY/Zt7LCq34pI70tLvjX90e55Q5WjP+ITYj6QcYetLG6Pck/SBH7/9GPzZ5kQbe5t2beQePVPUgPXhE6vFB0u6j5RLaGO8S0pfGeMv57h0lPHMk7bAcLXB3GdwI4vo+a9KPLVq4tPFIpa9/sR1/RZ+6d9wcDZNQsZqKnL8P53/nW9PT7iIE8435UN7BYfwm+ggdgnSx9+nKx48u8/GAQ2NzsAAypAK6WeVibwFWQRiOlhzdQMDSwdpMtj4a92wvwMcHCOHXuM5jsM7I8Z1AuEQl9bghwE10vCTWVDFgk0kPqCtzKGBTXZ1DkPCdTjp9xjMc8JlY53Ss6+msD7NQBynAZ+fgTjWv5/nMDxAzuKG9R8f6XezPj4JcemmABVa90jN1vwwy4P6jS48Cr7og6975lvjhGTr9U0xVxvFBpqurowsOcZ3ZZgU/ycODXHs3BXAODA956tnuhDcTbtrC9YFWyQOVCe9ODa/vbsSAE0isR+Ki8c5dP9nIcyYdc/KTJuZkOep/RoAxVNV/U7Aa+eqzDc5VD4rjuV9V+DbuSBWzfBfGxbBPzkrwddhs4rJUjpT5SadBF8v7SfMtZxxpAY/RDhwapd2XtIBH32Yj32yi/1RR8BGOJ5BHxiWVR495E1lGVuTT9PhF6Q8EnuMi7FR46nHxIMVj7TD/i/hNAy9jq/DRPD7GOswy508HA67meOA9/XTFc3+hkXYBzQzyRFkRnjMN/SdJfxjpBxoZDjf0AynDbCUD5JI7FuqMZa7oBjTxtch8hYfcMfxC0z4Wv1jhBybwPwJ49c0JZciaU9vQUtOGWa1v8KkeKXb7C5YBOu936nHFa5Q/XS1ger2x3NhdnSlvlpF7pSpvrelTx0he8I3LehzL6pF4Va5dj9fzNvVhv2WdOFL2EsBhfa/3Ojbm0sDgJLEB0CV/91st8noaU2aT8ECZsrbXPNaARq1ZQRdfszaDRt0XdK55Oj3ArNPPTuDRKuWg7vK9UfuwtFO/Z+fjo8heAjQqn9EXJFgveWP7gKNMO2dJe5TxFznK9OcN0j+FHrw3Kr0DFusbpxmdgiamj0+KDDF5XzDj9+mkfcF8E3gw4Zz/mqH+d9rwaDt/jjy2Recl2LLvW/k71sCfBVpdn7NVnxlkvl+cQ1rAI7oEj6jP5zDP93z8tFwXjJQ21jTpIlMHtPFFhWnxi9JerGQ+zcy7l6h+7N9SFr7bWH/yjMlwmWp78MXP3Ls38xrwsX67VdE=
*/