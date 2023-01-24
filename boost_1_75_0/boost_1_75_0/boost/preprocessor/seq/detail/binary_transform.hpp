# /* **************************************************************************
#  *                                                                          *
#  *     (C) Copyright Paul Mensonides 2011.                                  *
#  *     Distributed under the Boost Software License, Version 1.0. (See      *
#  *     accompanying file LICENSE_1_0.txt or copy at                         *
#  *     http://www.boost.org/LICENSE_1_0.txt)                                *
#  *                                                                          *
#  ************************************************************************** */
#
# /* See http://www.boost.org for most recent version. */
#
# ifndef BOOST_PREPROCESSOR_SEQ_DETAIL_BINARY_TRANSFORM_HPP
# define BOOST_PREPROCESSOR_SEQ_DETAIL_BINARY_TRANSFORM_HPP
#
# include <boost/preprocessor/cat.hpp>
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/tuple/eat.hpp>
# include <boost/preprocessor/tuple/rem.hpp>
# include <boost/preprocessor/variadic/detail/is_single_return.hpp>
#
# /* BOOST_PP_SEQ_BINARY_TRANSFORM */
#
# if BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_MSVC()
#    define BOOST_PP_SEQ_BINARY_TRANSFORM(seq) BOOST_PP_SEQ_BINARY_TRANSFORM_I(, seq)
#    define BOOST_PP_SEQ_BINARY_TRANSFORM_I(p, seq) BOOST_PP_SEQ_BINARY_TRANSFORM_II(p ## seq)
#    define BOOST_PP_SEQ_BINARY_TRANSFORM_II(seq) BOOST_PP_SEQ_BINARY_TRANSFORM_III(seq)
#    define BOOST_PP_SEQ_BINARY_TRANSFORM_III(seq) BOOST_PP_CAT(BOOST_PP_SEQ_BINARY_TRANSFORM_A seq, 0)
# else
#    define BOOST_PP_SEQ_BINARY_TRANSFORM(seq) BOOST_PP_CAT(BOOST_PP_SEQ_BINARY_TRANSFORM_A seq, 0)
# endif
# if BOOST_PP_VARIADICS
#    if BOOST_PP_VARIADICS_MSVC
#       define BOOST_PP_SEQ_BINARY_TRANSFORM_REM(data) data
#       define BOOST_PP_SEQ_BINARY_TRANSFORM_A(...) (BOOST_PP_SEQ_BINARY_TRANSFORM_REM, __VA_ARGS__)() BOOST_PP_SEQ_BINARY_TRANSFORM_B
#       define BOOST_PP_SEQ_BINARY_TRANSFORM_B(...) (BOOST_PP_SEQ_BINARY_TRANSFORM_REM, __VA_ARGS__)() BOOST_PP_SEQ_BINARY_TRANSFORM_A
#    else
#       define BOOST_PP_SEQ_BINARY_TRANSFORM_A(...) (BOOST_PP_REM, __VA_ARGS__)() BOOST_PP_SEQ_BINARY_TRANSFORM_B
#       define BOOST_PP_SEQ_BINARY_TRANSFORM_B(...) (BOOST_PP_REM, __VA_ARGS__)() BOOST_PP_SEQ_BINARY_TRANSFORM_A
#    endif
# else
#    define BOOST_PP_SEQ_BINARY_TRANSFORM_A(e) (BOOST_PP_REM, e)() BOOST_PP_SEQ_BINARY_TRANSFORM_B
#    define BOOST_PP_SEQ_BINARY_TRANSFORM_B(e) (BOOST_PP_REM, e)() BOOST_PP_SEQ_BINARY_TRANSFORM_A
# endif
# define BOOST_PP_SEQ_BINARY_TRANSFORM_A0 (BOOST_PP_EAT, ?)
# define BOOST_PP_SEQ_BINARY_TRANSFORM_B0 (BOOST_PP_EAT, ?)
#
# endif

/* binary_transform.hpp
teyxi+7I3fdKVUQTfXnTMVFzW6A85o7adw91Lpv7nSdiF8pxImqb7/eAWaEAE1AH62VL9sQH8COQq/77HiwhHZn2h8CfE384HLAFZQVq9dkkdoKIVYOygvy+UDlh1VMzv+CPN5T9gbeJaffyR9CbLwSqmMl/eORTrrzWfGEQqJCPuYJph9KKstiHkx/2sCmzZBRVj+P0QrkP1YlnL2nJoc9sDhzpxDmDxptpPWkhSIVDi6R1etWOYoWOYzD+gAf406pPLd9Vwh+pUyt/OmvQUiTew3UWh+qu8wkrrEv/ydfdUpD0FKPjRq4M/ygGbaCgUxnhFiaJeBHXTLptDI64o/noRrsV5+F780nHs5mDnO9PWTM10blKmrilU31ei6Nei8E6iiDVNAa8uWgEPzup5Lloz3Y89Q/YSXStLi59MHPGxpaKjNEfktDosJgAiHEPSPovpJ1lTBxAFscPKFC8wOFe3N3t8OLu7lLcXQoUKO4Oxd2dwuLuUhwWWNxlYdHds1zuy0kul7zJfJlJJvMyH36T//u/WO8SFHVq0jTlh2wXAB0H+GTA5F50fVYaQNR9LZu+TzUVkBf9Y6WN1rIuzE5NNa0GizDZbn+kjGLJYuCgRhPN60yiJXcCSW7Dkxp+9rVVTVfpfBGC+Fld7qnzjzeE6YEurtnmugyOenKDJCeoMf7GYV9c1M4JECLF/EveJXpNzpf9vvG7YlFU
*/