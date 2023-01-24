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
i0VIxCMoz4l1rPRLsnaQz9SDyJgz5eszBh1yjDg1z15MX0/E1YYTFxIDVf5VOhbniwC2WCkWNbVqZ7Pt15xbKeyBAEKl6Adhs2jPsHHjEhPaHeVCl5yJO9Kgrlws0vmn9k6NjljE4unC16vCRAs/8RhWXCUaZKO4vnjjP/7BgGrpCt+b0uxwQu7yNwGqiAJr89eBUifGjMnnnq8/1DBFROLNqhKkvy8FOtnR45FxYIgnFvH6DxArEslGxarG5x+YFiWMeD65C+FG0Z3hLOLJZWxb3Saw2hqoOdNz4CbNwBL2rLiEWIuJ8VF+7SrncwoZOX2jv8ZV8hT6IteBxfnkKdLy3NsEcBM47VhtatVTGK8zez/xGTF9ZTno655qAliNcgxxqlYVJsNpUtS8J+1Xzpn9+aPcrGiniF1oQ00B+S3th5SOpDYBIQV0VsewqqrSQlOlnMHT5dXF6R2bE9sr3pfXSgslKdPiyYayQJnlxUyOca/oQ/3C2F6aD6qItJjnBRn6ZLWLqWeohEX7zcB3IM244h/muxqaYqquf/nvJYyQbfImAYbvE9Bixk7u3Iqf8xPeDRu55z1VlOsXa2gHA4R8p8Msq8Y2mub3F4YRt/2pnm8jcDrAlZ3B4M4ffKk/fSKGGDR3K0MBU5ytrsN8ZZbalG0OO5WZepUL2eIjS4c252hSSQOdyNzh0hwIdLWhBS50EApXJYJPZbjq
*/