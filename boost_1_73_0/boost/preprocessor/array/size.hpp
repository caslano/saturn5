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
# ifndef BOOST_PREPROCESSOR_ARRAY_SIZE_HPP
# define BOOST_PREPROCESSOR_ARRAY_SIZE_HPP
#
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/tuple/elem.hpp>
#
# /* BOOST_PP_ARRAY_SIZE */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_ARRAY_SIZE(array) BOOST_PP_TUPLE_ELEM(2, 0, array)
# else
#    define BOOST_PP_ARRAY_SIZE(array) BOOST_PP_ARRAY_SIZE_I(array)
#    define BOOST_PP_ARRAY_SIZE_I(array) BOOST_PP_ARRAY_SIZE_II array
#    define BOOST_PP_ARRAY_SIZE_II(size, data) size
# endif
#
# endif

/* size.hpp
ymEF/pfuufI2eUyEb6DSF7vr57suNnUxY6D2vLT3785nFp6ghB+juO3pVHEj4vf+08zsIP7GazOkbwse/bOkPVgtjgta1PsS1ZGVbr64gD8u/BmPgEvfZq7KtC92c5vp3MTF9be6X9o4rMhNX2TLWOJY5Lbh4rlNXMx9qss8EAfnH2nu+sE/t4mLebdzNw/Ewfmnu0biUrdw4eNx+V/aGOTkpDk/yHHbq6HULVz4/aiunoqB
*/