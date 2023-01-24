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
# ifndef BOOST_PREPROCESSOR_SEQ_TO_TUPLE_HPP
# define BOOST_PREPROCESSOR_SEQ_TO_TUPLE_HPP
#
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/seq/enum.hpp>
#
# /* BOOST_PP_SEQ_TO_TUPLE */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_SEQ_TO_TUPLE(seq) (BOOST_PP_SEQ_ENUM(seq))
# else
#    define BOOST_PP_SEQ_TO_TUPLE(seq) BOOST_PP_SEQ_TO_TUPLE_I(seq)
#    define BOOST_PP_SEQ_TO_TUPLE_I(seq) (BOOST_PP_SEQ_ENUM(seq))
# endif
#
# endif

/* to_tuple.hpp
a00eduHwCzMEwCMlIs0cdSIOfh9l1DwwwugNww63hR7eqFNd0Mdcj44cSk/OrX1R0VD8Dd+0s41dQmnNqwoe/olCZHWNt/bE3HarJ4h+uH19yZwYh0HP+R6ENBU1BTQ+Rs0aokKMuAQocianWXRzQel5g4vAt5zL7cJZh/7nk6xNCso/76b2Dz+mWWv5cDB3sKry2LwTdT1Vwo5te+NrFOSfVtRDOpnbmd6RPuqPun/4u6nMgqdp5a6xnk70HPFk8ZLoie0CTcdJJ2PCkqjYOHk20x2K4+CrlR+TGzo9AKH9+AHLJHB0Bm26b/6S7IvfYr0StS/NfpcBb9tbpjMgDgsKz6Xg768AtcrEotkiaY4f3YcK+68vYlTadhy++xq18imqj2GRaoqhOtEACMyeh0Q4VTocLwliqg1sEGLjPAiRQsEZt17frxc9AEpSR58rdfYu22tPRNTFRADWzmbs5liu6Y4yVFFpY/uv0u7qW85ox30mIvAMnqS9+BNOe4EopL1Aon3aeKJCdVbxwhyCbzXR3gCJhvx3lsU3WHpf7hhfkUd0tZXW1dj4wIEIso1jg28msaSRs3uaCgkkOMJgZzUqMBYOeUUzsY6pts9C/X0aOJHakucM406oeQf1jtE3THSUo0gUSY374us88BvnDr57Ss9A76ixeV1D8Zs5pt2f1p0u6kOAPxXsvhnmzXwX66xLHnb7ylVd4hZq
*/