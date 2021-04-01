// Copyright David Abrahams 2005. Distributed under the Boost
// Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
#ifndef BOOST_DETAIL_IS_XXX_DWA20051011_HPP
# define BOOST_DETAIL_IS_XXX_DWA20051011_HPP

# include <boost/config.hpp>
# include <boost/type_traits/integral_constant.hpp>
# include <boost/preprocessor/enum_params.hpp>


#  define BOOST_DETAIL_IS_XXX_DEF(name, qualified_name, nargs)  \
template <class T>                                              \
struct is_##name : boost::false_type                            \
{                                                               \
};                                                              \
                                                                \
template < BOOST_PP_ENUM_PARAMS_Z(1, nargs, class T) >          \
struct is_##name<                                               \
   qualified_name< BOOST_PP_ENUM_PARAMS_Z(1, nargs, T) >        \
>                                                               \
   : boost::true_type                                           \
{                                                               \
};


#endif // BOOST_DETAIL_IS_XXX_DWA20051011_HPP

/* is_xxx.hpp
oXlq7tR3ZxhYiw7mjnQ3nvm65NRgAzZU/OI/tHQY9yNvYDus6M/RVmYefdVQi6FXHyXfUKYLN9W0Rr+Tv4gmmmET5V35LjoVNEvm0HPr9N+DIjrEX6n311ZhdUjHjIeaJx39MT0K7E4pIafWH2O51QGTyzcC/CeY1FTlnFKjSJaFAi1Jmlq8tmdSSiw33trtbQWHwfqxqmAkUurliEVPHF2ppfdOwEC+FfUiB4hocuJD0TPsuveUzWbOM3+3jgd8fBGq/I4nb2x6pWlkMghxSi6fRPvupAZIBcihJJ80vNzQrv2zOueVPQI942R1K6qrGqeT+CROFbG+57dScW/2h4RLx2Kn+6ziGkqkENTgDXXABej6/QDsnP6Tlvwo49N8aBToQeC2o7xok96C6ja1chdX7x8dP6TwUl3ja4XRHg54HmuSAUCf+vLKx5EmaU6ckpE/i27q+nxgS62VrhTpCJr+ABBTE5dKJa3dHmKxwlAl/tm/iZjTT1EuY6iPpwuAOzV2fJInsEmrq4EoQxiNgenBgi6+qdBW+zuVxrKKb+9GfM6t4IL2gCMGbQ==
*/