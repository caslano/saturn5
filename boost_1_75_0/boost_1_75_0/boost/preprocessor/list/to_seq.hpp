# /* **************************************************************************
#  *                                                                          *
#  *     (C) Copyright Edward Diener 2011.
#  *     Distributed under the Boost Software License, Version 1.0. (See
#  *     accompanying file LICENSE_1_0.txt or copy at
#  *     http://www.boost.org/LICENSE_1_0.txt)
#  *                                                                          *
#  ************************************************************************** */
#
# /* Revised by Paul Mensonides (2011) */
#
# /* See http://www.boost.org for most recent version. */
#
# ifndef BOOST_PREPROCESSOR_LIST_TO_SEQ_HPP
# define BOOST_PREPROCESSOR_LIST_TO_SEQ_HPP
#
# include <boost/preprocessor/list/for_each.hpp>
#
# /* BOOST_PP_LIST_TO_SEQ */
#
# define BOOST_PP_LIST_TO_SEQ(list) \
    BOOST_PP_LIST_FOR_EACH(BOOST_PP_LIST_TO_SEQ_MACRO, ~, list) \
    /**/
# define BOOST_PP_LIST_TO_SEQ_MACRO(r, data, elem) (elem)
#
# /* BOOST_PP_LIST_TO_SEQ_R */
#
# define BOOST_PP_LIST_TO_SEQ_R(r, list) \
    BOOST_PP_LIST_FOR_EACH_R(r, BOOST_PP_LIST_TO_SEQ_MACRO, ~, list) \
    /**/
#
# endif /* BOOST_PREPROCESSOR_LIST_TO_SEQ_HPP */

/* to_seq.hpp
X/P0AS9GYqMJgsth1Xo9vQxC5OJ4R4CjxFKsfblgFPAq8cX+qwzYKwko2RMYoWT87UUFOoSIR+sVEV0W6kllig95WFUSVn3+Q3d02rz0mehLCVRTOkbHnD9wzHW/sHclFotuWsKugUz52awi9Sd94+JTfmEgtoxZvB+d7+VgJSmf9ags1XFlLsPYas7nOG0RS8Awft+jTX5lJrUd1JNqezol2X0KqQ3k4vexoBZdxPFOW9iEPlnfTfbCXHmKiLdM/LOQNZ0ia3FumdQtYlnZc/kl65aeXugWrD//8UrFyE92I70fK8hZb+dxYPmvT0XZzm9sp7sqrGU+Wizr2+9iYeZq98+oXIkXyl82ZH0pVf0jbRq+XrPa6enpdgS/mrhJt1Xe7eVdsWtVKBmICf+8Yt2Y7bPQ8/M7kaC3ubS/vuCgdrGzUnDi9G3AH/58F3B4+dT3oHKd3x/QF9Bnyb29EpMlut1toa5AcZcV4CJE6naxoBJKtGYnW4fUSu5ci+vJQqQlOcUtY/aEzpXdGNCDRTOYLa2VDSLjUJZJI6eXBh2EmLzekvUQE2MpqwaZAzxc15WESIiNCexZihjErPbtIhpcsJd/osR4xP3GLZHtHvo5KC01F1Izhp9Id69dKYaE7KKs6qJruV8hRPxdhuq435CCD2J+0Lr6RN6YayI0M8nYz7ccdO0wehXC9cdI+HchX6tNVyz9x5t+C+Md
*/