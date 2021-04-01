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
ecuSpUVof+KbJzMxCXErlHcCj+m8RWCX6IfsuZS91C1+3LBDyWde+nDBFDQH3kumRI+3HMLkYLa8m65EH1nT5kTkeQQXSUqoHYdkV1ti0GUv5NTFNmVErJaFgRHPB/WQKwn0/OBJdoFU8DVLMbKLrsC/hDG8mOnj4J59KD2ecwZ3r4W84W/UbKuUe5xPNpbpYuP34qv98LdkX6PF6+LE4j1naTTM8QWYhTzFtzr3GBmA8RPG7I7OGhK9mnLwLXveMBez0ieHLa8PQ6qzEwx8HLxX89suySuMhI2kwqwPESNojS6ddoWZBNHEVTFKoPNy0+E/5lr0qitxlPvsfrgAfw/hrO64rSI9IZwMJQyK48RWUHuhPhyxm4riPIiEdBfBvaTSEciXyQ9abqEefWleOysUBoRUu5RmKIfF4LCe9U+t0kfLdhpLaODVcNIbp+dOhLAYe6ici+n5lxVbjT1ocIEZqWJeDSprn3zONL5CkKa/wUHWGa3kJQNZazxBAGh2laDpgwqoZ6I1JZlMO2jYlikdQhXJIlC4JirqbWZJJsa7XvUBYq3kbkc43Q==
*/