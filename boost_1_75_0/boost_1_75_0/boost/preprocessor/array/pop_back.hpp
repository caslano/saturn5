# /* **************************************************************************
#  *                                                                          *
#  *     (C) Copyright Paul Mensonides 2002.
#  *     Distributed under the Boost Software License, Version 1.0. (See
#  *     accompanying file LICENSE_1_0.txt or copy at
#  *     http://www.boost.org/LICENSE_1_0.txt)
#  *                                                                          *
#  ************************************************************************** */
#
# /* See http://www.boost.org for most recent version. */
#
# ifndef BOOST_PREPROCESSOR_ARRAY_POP_BACK_HPP
# define BOOST_PREPROCESSOR_ARRAY_POP_BACK_HPP
#
# include <boost/preprocessor/arithmetic/dec.hpp>
# include <boost/preprocessor/array/elem.hpp>
# include <boost/preprocessor/array/size.hpp>
# include <boost/preprocessor/repetition/enum.hpp>
# include <boost/preprocessor/repetition/deduce_z.hpp>
#
# /* BOOST_PP_ARRAY_POP_BACK */
#
# define BOOST_PP_ARRAY_POP_BACK(array) BOOST_PP_ARRAY_POP_BACK_Z(BOOST_PP_DEDUCE_Z(), array)
#
# /* BOOST_PP_ARRAY_POP_BACK_Z */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_ARRAY_POP_BACK_Z(z, array) BOOST_PP_ARRAY_POP_BACK_I(z, BOOST_PP_ARRAY_SIZE(array), array)
# else
#    define BOOST_PP_ARRAY_POP_BACK_Z(z, array) BOOST_PP_ARRAY_POP_BACK_Z_D(z, array)
#    define BOOST_PP_ARRAY_POP_BACK_Z_D(z, array) BOOST_PP_ARRAY_POP_BACK_I(z, BOOST_PP_ARRAY_SIZE(array), array)
# endif
#
# define BOOST_PP_ARRAY_POP_BACK_I(z, size, array) (BOOST_PP_DEC(size), (BOOST_PP_ENUM_ ## z(BOOST_PP_DEC(size), BOOST_PP_ARRAY_POP_BACK_M, array)))
# define BOOST_PP_ARRAY_POP_BACK_M(z, n, data) BOOST_PP_ARRAY_ELEM(n, data)
#
# endif

/* pop_back.hpp
/GuxhqWK+pu0H661Ha7+P4Y+kazSxRFlMQ8WDPud3ZI+hFp11opoxnzQjGS/1oIUVGs4bxVy011eSWkmFqlGGpPJDJMkM/2bp/7GWq8M2nDdYhyhHmbmlSTbC/JF5LoKevdZjENm4wF6rOhQQO+S8Vnum+nkKTC/lTBDQkuQ7pIagUuYR3VAnXEf8V6JXq8JS8sk1MNCAieDvVA0LHmE4Q6ToEq4z6SI/Ks9EkeeSDD0n6Fa5QDQFqC7y0vpZ/4Ba9lNk0iXykGzLENXeomKMBr7zg9yVAual+kIhLJAq5KVYNrNPKPMchSinusv1eOsgnY+WjnDvS78mVlM/BlnEfLQTLWnBLCrlXR0/PzELuKN3K9YRWPNjcwwmsu80mV6F1Hb3nHDrym5cjpFh0yFLF0ZYeiVW87soFW37r+r/H98JcPYpFaG7SP2dDr9jux8Yq3F/eBQnxqGLlOlP4iIj1xDtVMdaGpe/RCE+y6Jsh6qTSK5XB+Ve5eg14KwrvheehvtyL1YNAdkG0fP5pqybZ6PiWhduP32SPbb0277zV4C1Qdq85jfz9YT+0iVlHfcbrCesQbic86OiPISWKFaGt85IQrA36RpvpFViwxVhpm/FqQ2ZT6siB+0C6kecalz7GnSkmQzxbgPUzUMxamWgVn1pShepbmWaisssXHqzqmhO6caJaq7ikQsdbAncN/xqmddR+tqcJt4qOnA
*/