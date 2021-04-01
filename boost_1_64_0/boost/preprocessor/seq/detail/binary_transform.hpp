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
kJi0xor5+vsMWQp7pxgOO6Y7EJg8RLHLZ/U/qZpRVzEHB386dJBvtHCGeBA16C6Sp1eGXNLaX03HmDMGxUAiQCA99kzTc1lLQ+GsuCf+yYBwghC3KzXt/s/CrCHLy7Q3OeRpor/KM5lnWxQWixSGILdeF8DqmrCMI80lJXK+6DESkjsn3N15M6qeTvUeEfitFrWpv13bkkrghVOaASOlpdwab9dBNVhnbVbKTY/1El70QeCjhsaSTKFAiYI7AQpdiQgmelDAMtV/GqWjDApYFCu6gYNtVYSz3iC5NF52eyPfNNqwZP7NqYLA/BCotMLL+W3lFPR2s1jDUQMFZrL8a0hs3l20wwdyrxTUQRKACUSdrN2+3ZfHfRhAgN/15FWmxLZX2ptE0dC8RyHUPSuScKw1CrZYHPgQg7WPKkWIogFM4S9ZkuCIqb3uulLhLK6vwuOfSwA1DCx3NNdjZdrnxvkKNNLBGUz08ubUsZoW4Gaq454k0oychiSnJbAfIFYTVcUd/UvCBhw+p/lGGvrMIfxsnl+Uo/kn+iqFQtZuF3c43nCPP0yvNjImxw==
*/