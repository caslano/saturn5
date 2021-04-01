# /* **************************************************************************
#  *                                                                          *
#  *     (C) Copyright Edward Diener 2014.
#  *     Distributed under the Boost Software License, Version 1.0. (See
#  *     accompanying file LICENSE_1_0.txt or copy at
#  *     http://www.boost.org/LICENSE_1_0.txt)
#  *                                                                          *
#  ************************************************************************** */
#
# /* See http://www.boost.org for most recent version. */
#
# ifndef BOOST_PREPROCESSOR_IS_BEGIN_PARENS_HPP
# define BOOST_PREPROCESSOR_IS_BEGIN_PARENS_HPP

# include <boost/preprocessor/config/config.hpp>

#if BOOST_PP_VARIADICS

#include <boost/preprocessor/punctuation/detail/is_begin_parens.hpp>

#if BOOST_PP_VARIADICS_MSVC && _MSC_VER <= 1400

#define BOOST_PP_IS_BEGIN_PARENS(param) \
    BOOST_PP_DETAIL_IBP_SPLIT \
      ( \
      0, \
      BOOST_PP_DETAIL_IBP_CAT \
        ( \
        BOOST_PP_DETAIL_IBP_IS_VARIADIC_R_, \
        BOOST_PP_DETAIL_IBP_IS_VARIADIC_C param \
        ) \
      ) \
/**/

#else

#define BOOST_PP_IS_BEGIN_PARENS(...) \
    BOOST_PP_DETAIL_IBP_SPLIT \
      ( \
      0, \
      BOOST_PP_DETAIL_IBP_CAT \
        ( \
        BOOST_PP_DETAIL_IBP_IS_VARIADIC_R_, \
        BOOST_PP_DETAIL_IBP_IS_VARIADIC_C __VA_ARGS__ \
        ) \
      ) \
/**/

#endif /* BOOST_PP_VARIADICS_MSVC && _MSC_VER <= 1400 */
#endif /* BOOST_PP_VARIADICS */
#endif /* BOOST_PREPROCESSOR_IS_BEGIN_PARENS_HPP */

/* is_begin_parens.hpp
ZqkBXlG+9+Ms9Ow3KqY7ZXaAYei1LxqUmh+1UQ/mq2FjwdTBJzL5KQhzMMoqayVtWbUwREcX1kloyALoBLqKQuZUgGh7Da3QCZ4o+yxQdIakF311andK0l0f51r8bXSB60vJCpk2hrnjHN47UTe0CyqmhOdS09AljKYotuukVlY/fKR4Gglr31aRKm1oLbuHP0aYgiWP/HLk9EfmG0tGNMe6r9kH0fjP6S4nTGQJLAxxLA7u+UEuN6Gtjl3oSPsEKaawXjXQakNYAkGDE+K55/TGS1UnBNgc/WjvHyRas3k9DrCjKMWKhBoMBj/KUALPs6a8jCnnOCCmgWbtjnJ2nxtvCG4A1zbR5A6WFHBDixWnu+/51zOXViwkufdCsMhhoKQBZ/RBOaXrlg4yLL3oXt/PujAZAtHukj7ZnQP0+WkL/1EN2O2zAdbiXZpUdpJVKLh6q19rtoe/yEEx9j/mMOqRhkxXZ+098Km3eNcQwU0t4vJEvKSKNsbA3o/uVDaVSkxWIH2rmSKtahpWBRlk1EnRlDkR8DmckfH3XIfdProqKoKLZJe9Pt45Sg==
*/