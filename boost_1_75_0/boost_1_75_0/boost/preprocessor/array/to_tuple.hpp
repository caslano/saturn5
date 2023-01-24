# /* **************************************************************************
#  *                                                                          *
#  *     (C) Copyright Edward Diener 2011.                                    *
#  *     (C) Copyright Paul Mensonides 2011.                                  *
#  *     Distributed under the Boost Software License, Version 1.0. (See      *
#  *     accompanying file LICENSE_1_0.txt or copy at                         *
#  *     http://www.boost.org/LICENSE_1_0.txt)                                *
#  *                                                                          *
#  ************************************************************************** */
#
# /* See http://www.boost.org for most recent version. */
#
# ifndef BOOST_PREPROCESSOR_ARRAY_TO_TUPLE_HPP
# define BOOST_PREPROCESSOR_ARRAY_TO_TUPLE_HPP
#
# include <boost/preprocessor/array/data.hpp>
# include <boost/preprocessor/array/size.hpp>
# include <boost/preprocessor/control/if.hpp>
#
# /* BOOST_PP_ARRAY_TO_TUPLE */
#
#    define BOOST_PP_ARRAY_TO_TUPLE(array) \
        BOOST_PP_IF \
            ( \
            BOOST_PP_ARRAY_SIZE(array), \
            BOOST_PP_ARRAY_DATA, \
            BOOST_PP_ARRAY_TO_TUPLE_EMPTY \
            ) \
        (array) \
/**/
#    define BOOST_PP_ARRAY_TO_TUPLE_EMPTY(array)
#
# endif

/* to_tuple.hpp
p8n10ZhLGBPjkffrL9ktUHU6EmCbUiR35xYBoKkfOLBvM5ewrq7uTH7gW2SU9oQ6yuD6gbx+vcul/iN9a0nMOw/2fEG0Q03rhJfTDFDHLgWf9RBnmWWSsymWxuzNd0CQSWGT6y29kH81uwDZ9RNX1yIwGjnR5v5tLOIr1IA3QWW0JHST8pCjLrU4NmelDTontRWTzWV7yBv4V/91jkjd0JUMM8nx8uBESAVdhBWMoZJS9sKd11n4pGJh7B0ssqozqok5rM9iqfHGWlZCfYlDRQshDLTgignfIyal3uHUucmFOltxIaa09KLlqiNvhAUtJ4aKWBhQU+c8AmpUaZIInzAxPYgkhSVPzGkHffIUycvflz/lXzLUQeZr/zF6oL+EI8Ty/OY06yq1IEpwikFAffvcB8+kwb48ELbftw8dmH6qzvM4g+OvADZZchdGUdaDdJ34Zzlytz6HP7t5I5tvI3XijJ3FLvRDjw2uJ0+/+F02+C68X1APF+gUk3sJ5Lvi2smUe/BoK2qbuL/t0zVYdD0bhZpnfFQk7tSOoZ6MvOe65rvpMdWJrMkkVNK5fTGt5LVwp5B+Hk3/VkmXukT7ZjnyHcMxYZxHoOef/YPaUqi+DtOeO75sb4E757XKEAC0LdOuk2BCWKr5fQsvY510s8A7yj+z1e0dFvmMA+sc5Yeo7Xs0geQZXebHwB1iXHf72gK7fVlzN/pu6ney
*/