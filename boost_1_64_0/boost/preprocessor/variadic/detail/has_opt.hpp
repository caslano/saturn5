# /* **************************************************************************
#  *                                                                          *
#  *     (C) Copyright Edward Diener 2019.                                    *
#  *     Distributed under the Boost Software License, Version 1.0. (See      *
#  *     accompanying file LICENSE_1_0.txt or copy at                         *
#  *     http://www.boost.org/LICENSE_1_0.txt)                                *
#  *                                                                          *
#  ************************************************************************** */
#
# /* See http://www.boost.org for most recent version. */
#
# ifndef BOOST_PREPROCESSOR_VARIADIC_DETAIL_HAS_OPT_HPP
# define BOOST_PREPROCESSOR_VARIADIC_DETAIL_HAS_OPT_HPP
#
# include <boost/preprocessor/config/config.hpp>
#
# if BOOST_PP_VARIADICS && defined(__cplusplus) && __cplusplus > 201703L
#
# if BOOST_PP_VARIADICS_MSVC
# include <boost/preprocessor/cat.hpp>
# endif
#
# define BOOST_PP_VARIADIC_HAS_OPT_FUNCTION(...) \
    __VA_OPT__(,) , 1, 0 \
/**/
#
# if BOOST_PP_VARIADICS_MSVC
# define BOOST_PP_VARIADIC_HAS_OPT_ELEM0(e0, ...) BOOST_PP_CAT(BOOST_PP_VARIADIC_HAS_OPT_ELEM_0(e0,__VA_ARGS__),)
# define BOOST_PP_VARIADIC_HAS_OPT_ELEM2(e0, ...) BOOST_PP_CAT(BOOST_PP_VARIADIC_HAS_OPT_ELEM_2(e0,__VA_ARGS__),)
# else
# define BOOST_PP_VARIADIC_HAS_OPT_ELEM0(e0, ...) BOOST_PP_VARIADIC_HAS_OPT_ELEM_0(e0,__VA_ARGS__)
# define BOOST_PP_VARIADIC_HAS_OPT_ELEM2(e0, ...) BOOST_PP_VARIADIC_HAS_OPT_ELEM_2(e0,__VA_ARGS__)
# endif
# define BOOST_PP_VARIADIC_HAS_OPT_ELEM_0(e0, ...) e0
# define BOOST_PP_VARIADIC_HAS_OPT_ELEM_2(e0, e1, e2, ...) e2
#
# endif
#
# endif

/* has_opt.hpp
nVC+aygyyGMOrHuNH8GEBsGgHmwpr89zHWkXcbz0fS4Bs3lGHkJ5aQf6LnMRKkogLt7ptxO+LFzxHGx/OqcNhuDvszO67vdBJ4j6J77ewVzF0HtKJd1ODI8NtFxjaamjBviZf6UTvxuRYh8wmOp64kEWnJ1uL0/4U8+rw0Zvagrg9N50xIn3aice+stca7lU/pbLSRZYAcmD0tWrFLuc0RM+blJBe7lqqVLNI/sy+oEwTvJuP5VAcqwbDFZYJ8jPr2HuXiS3cnBj9ml+3UVERtwPe9xcenOM03PxyTsbCSKJXo756iUqCYgdV/eIS78Och8dinKmb+7n7gmXK8zG4Np8vn08XvkErvxqlFMP+Z/2GeD7DLL7MrETNXme5nEw+QgdVIwzhhjtXj6zIcdwNSPagJ9GcIaraGs4SWH/Yo9N7RbtF+oiub0d+5Seq+yO85KLr6Ay1IVE8XnVncpzVuf72SIoYdGR0yX8QjaOUpS5JyAFSlryrxtrIERsOuZBeJMF1IO/LZ4eqeK/Mjg6JJv1glhSYfsgtslX/myB0wyWR2W2da2j4Rkp+Q==
*/