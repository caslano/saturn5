# /* Copyright (C) 2001
#  * Housemarque Oy
#  * http://www.housemarque.com
#  *
#  * Distributed under the Boost Software License, Version 1.0. (See
#  * accompanying file LICENSE_1_0.txt or copy at
#  * http://www.boost.org/LICENSE_1_0.txt)
#  */
#
# /* Revised by Paul Mensonides (2002) */
#
# /* See http://www.boost.org for most recent version. */
#
# ifndef BOOST_PREPROCESSOR_PUNCTUATION_COMMA_IF_HPP
# define BOOST_PREPROCESSOR_PUNCTUATION_COMMA_IF_HPP
#
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/control/if.hpp>
# include <boost/preprocessor/facilities/empty.hpp>
# include <boost/preprocessor/punctuation/comma.hpp>
#
# /* BOOST_PP_COMMA_IF */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_COMMA_IF(cond) BOOST_PP_IF(cond, BOOST_PP_COMMA, BOOST_PP_EMPTY)()
# else
#    define BOOST_PP_COMMA_IF(cond) BOOST_PP_COMMA_IF_I(cond)
#    define BOOST_PP_COMMA_IF_I(cond) BOOST_PP_IF(cond, BOOST_PP_COMMA, BOOST_PP_EMPTY)()
# endif
#
# endif

/* comma_if.hpp
I/OgbXiZS3BrKW0kUieELmjHOi4nKajzRtod0Wzk/dgbVypaoP2M2pDWch6fpXjQ+H3VAGN3eTfam3V0qehqfMrpFy+YmZvqXJENRe45DnyqkFbHxF5nDiaTzUucdmhZ6jY+piot6e8yUTHv1oVediRSoaDUjAWhV27zGEL9WGAk5/LCM09ZgEWh0YTMnJL3vfF52nU8x7+L0O2lpEmmefZ0hml/P79pG8yDYCx1TSSpjSDlqjNzqEaDQEA/35GG5HtN6Z12r4ahMtloRldCqXGu6biQaWXHewxmsrEeRlcm4yZxr1aygSt7dYdqb7bYPE3GA5Ula7csdWhpyjW4NBVpLH2atThIBnG6LgWztNneLvRXtfWxqdnp6Dta2pfxTrK7Ws2d3URdZh6HDsCH2eM9fnsl8phK/V5H2Km1m8hn6xnzogmQ5PaIDLtrhGHpBz1sBM5HyPqisMZVVpoadYEyHG2XRwuIt4o32k0XXoSnvhi/K722UcbZfWEnKvOdCI8az2WRraSOwWEKEJxvRxGDyKVNU12XMseT9aPFfWHbu4IimRMvHNX5n6Y0XHejAV0YrtwWee3hPgg60oz0phF0QRvtFnEfoNMxOD3LpMTVCszjLSxBFRMxiUcIJj3zrJ3tK7GOKRXtgBrZTn1YuM7mr8KmoKQCJPj6UUDVJwlgzcK270Nd5xTgQrFTd9SqHOCtPD4/FvN27tEYVVmjIivC8kLGgD7i4VhUi3HNPCYCTc4uSWpV6tuIuybEtmpKu0MXmDur+SZdzGV2Wsp/jd/KQIP1nFdUWj1ZXjSc/ZKnYf0PSSxsBqa8ggV0+86Ga91xMGPQlbXGXAmZ+N/gAJXmNd/j/IcEVLH16RouHzqcx7fowVwyHFLZQweFnl2B84lhn9j4hWOsIuMfm3pgvffYbe7jPfNT9XU9l58s+6ysB2Qc9VtVrjOtkt1OmV21MWbiTFzfZBvj7bLaEPsuuRo5C1uS2LXzxeT8a9auYel81KXgdEHr7rAmWpsm/F667vdEs1FX9grhLIuH5dHPxGKpGx3fvs45iPBiWAPp4wBCo1vUpYaOXb3XGZU+8OYB6XIGha0QKICece7LqyiLUA4azCXDYXyCdt/QfHymTm1szr8ZzzMaH79Xk70fAv7OClQBOsiq9StJOhIWG5VhDsiEpjYfbe3sVnenme0eEw5D779wzuIaTtMxYYldtVkmx5NA23t7+rbpN2reUdrT2ZkiEwcoZufvV+753laObZ/s9iTNQxcPF91Om1g6cracdW6t+kPieAj/0AmXp9LXk7ritigCpPIFqYbFu6/ndlpBp326pPJlP+TqXxb3ao2TGlhobeohgKnDNvlO3oLNw/PltEn2dgeDX8ZSPUsw/v223BMLpwt+z0tTO42znl9r92TsT+av6f/jMs3WX5rVy70zs3ekTe/NyLwxlxiHsPu+aLljNbok9zKbmomuabdl0mhvkvDDzGfi09fo1QUN4oshJAsN4tlsnXe9+gslHzZ+ij5HXyx+/I0TxZV4fo7nlXl+hedVeH6b51V5fp/n1Xn+hOc1eP6O59V4/pnntYr4+9c/Bot//Q346+CV/vU7ymwr6N5rtY/Kk0rU7zXQ8EnkXZ+BXcId8k3U90HXWQnnG7H50xe8/FdEebIYka12B2XaM8p1mqdWN+PyLoUm/R7j/ciS7ksez8rNpudq5awufkyW6n72u/4aGIOXC4qHhS20kubwxXBTMfEr2ektEHp+7Ves+NhcPdCOkbPMBlfStJICTSG+azLJ6mAeqtijruddW3kuin3yuFdrWF9P7aPb2dz0yaJxrfMni9S9nNa2Swl3mlom2pvNrcstyxY=
*/