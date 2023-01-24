# /* **************************************************************************
#  *                                                                          *
#  *     (C) Copyright Paul Mensonides 2003.
#  *     (C) Copyright Edward Diener 2014.
#  *     Distributed under the Boost Software License, Version 1.0. (See
#  *     accompanying file LICENSE_1_0.txt or copy at
#  *     http://www.boost.org/LICENSE_1_0.txt)
#  *                                                                          *
#  ************************************************************************** */
#
# /* See http://www.boost.org for most recent version. */
#
# ifndef BOOST_PREPROCESSOR_FACILITIES_IS_EMPTY_HPP
# define BOOST_PREPROCESSOR_FACILITIES_IS_EMPTY_HPP
#
# include <boost/preprocessor/config/config.hpp>
#
# if BOOST_PP_VARIADICS
#
# include <boost/preprocessor/facilities/is_empty_variadic.hpp>
#
# else
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_MSVC() && ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_MWCC()
# include <boost/preprocessor/tuple/elem.hpp>
# include <boost/preprocessor/facilities/identity.hpp>
# else
# include <boost/preprocessor/cat.hpp>
# include <boost/preprocessor/detail/split.hpp>
# endif
#
# /* BOOST_PP_IS_EMPTY */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_MSVC() && ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_MWCC()
#    define BOOST_PP_IS_EMPTY(x) BOOST_PP_IS_EMPTY_I(x BOOST_PP_IS_EMPTY_HELPER)
#    define BOOST_PP_IS_EMPTY_I(contents) BOOST_PP_TUPLE_ELEM(2, 1, (BOOST_PP_IS_EMPTY_DEF_ ## contents()))
#    define BOOST_PP_IS_EMPTY_DEF_BOOST_PP_IS_EMPTY_HELPER 1, BOOST_PP_IDENTITY(1)
#    define BOOST_PP_IS_EMPTY_HELPER() , 0
# else
#    if BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_MSVC()
#        define BOOST_PP_IS_EMPTY(x) BOOST_PP_IS_EMPTY_I(BOOST_PP_IS_EMPTY_HELPER x ())
#        define BOOST_PP_IS_EMPTY_I(test) BOOST_PP_IS_EMPTY_II(BOOST_PP_SPLIT(0, BOOST_PP_CAT(BOOST_PP_IS_EMPTY_DEF_, test)))
#        define BOOST_PP_IS_EMPTY_II(id) id
#    else
#        define BOOST_PP_IS_EMPTY(x) BOOST_PP_IS_EMPTY_I((BOOST_PP_IS_EMPTY_HELPER x ()))
#        define BOOST_PP_IS_EMPTY_I(par) BOOST_PP_IS_EMPTY_II ## par
#        define BOOST_PP_IS_EMPTY_II(test) BOOST_PP_SPLIT(0, BOOST_PP_CAT(BOOST_PP_IS_EMPTY_DEF_, test))
#    endif
#    define BOOST_PP_IS_EMPTY_HELPER() 1
#    define BOOST_PP_IS_EMPTY_DEF_1 1, BOOST_PP_NIL
#    define BOOST_PP_IS_EMPTY_DEF_BOOST_PP_IS_EMPTY_HELPER 0, BOOST_PP_NIL
# endif
#
# endif /* BOOST_PP_VARIADICS */
#
# endif /* BOOST_PREPROCESSOR_FACILITIES_IS_EMPTY_HPP */

/* is_empty.hpp
wH0+3uveVe9mRgvL3q3XaRvu9T3Hjkqc+5VovZAfrZxSYXHUEBnGM9e2vmpQYi4pA2yoNPD7cXFEEmuKIVngvsU+XYOz6W4GY4QdvDDfgOErWJPRhiRDWamoeGSDYzaw/Od5VT89j4D/hFSiBZnvlaPF75ZZjRu0TBUi4bPF6axEIvK8RNY/uBMwSjxJvPEGauU+mgdTjPNQGoQ+zbvDLaSoNrzf/HQ08n4+bzew4nt3XTK4r1s+S+v5ZsKu3/v8FdCTG6bSW7I1ezl5iRwQ53GL+oAfkEE7s7hl+aAdxV/Te3JpXPibb5v8heMFPwjV+XfNzRNtNGQAtX+ToyACwrTLEd1HYknZTWs+KVuk0k33eo2woDRi2V12Iptc48y9HX0I0Bv8nR4TqjLi8+pKViMauwM8i2Z6MGbr9nS9jCcaqn/lA07C5tTBogtF5npdip6+7DJJX5SEr/K1iREw1E61bG4Wlp88o4KWP+vFy9QWdlGXIqJt0G97vT/hisg9n/r50ZZqePXhWmKz+lDM2yik7agCtPWIuE7/ejOqu88+vKfjr26rXb3nOJ7W8QZUVrrnOkBwswnSWz85de4wcu/S2ALhyehxxiPwcEMeFiaTrhB9ZkPfhhhPw8bAkwhGyYRDRPRdiaFSXPEdg2y/bsQL0U3CJGHgF1l4wcTzGXUD2N3QM/CP7ScTeq3v308R2AdY7j9BfNvxM9fx
*/