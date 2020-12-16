# /* **************************************************************************
#  *                                                                          *
#  *     (C) Copyright Edward Diener 2013.
#  *     Distributed under the Boost Software License, Version 1.0. (See
#  *     accompanying file LICENSE_1_0.txt or copy at
#  *     http://www.boost.org/LICENSE_1_0.txt)
#  *                                                                          *
#  ************************************************************************** */
#
# /* See http://www.boost.org for most recent version. */
#
# ifndef BOOST_PREPROCESSOR_TUPLE_REMOVE_HPP
# define BOOST_PREPROCESSOR_TUPLE_REMOVE_HPP
#
# include <boost/preprocessor/config/config.hpp>
#
# if BOOST_PP_VARIADICS
#
# include <boost/preprocessor/array/remove.hpp>
# include <boost/preprocessor/array/to_tuple.hpp>
# include <boost/preprocessor/comparison/greater.hpp>
# include <boost/preprocessor/control/iif.hpp>
# include <boost/preprocessor/tuple/size.hpp>
# include <boost/preprocessor/tuple/to_array.hpp>
#
# /* BOOST_PP_TUPLE_REMOVE */
#
# define BOOST_PP_TUPLE_REMOVE(tuple, i) \
    BOOST_PP_IIF \
        ( \
        BOOST_PP_GREATER(BOOST_PP_TUPLE_SIZE(tuple),1), \
        BOOST_PP_TUPLE_REMOVE_EXEC, \
        BOOST_PP_TUPLE_REMOVE_RETURN \
        ) \
    (tuple, i) \
/**/
#
# define BOOST_PP_TUPLE_REMOVE_EXEC(tuple, i) \
    BOOST_PP_ARRAY_TO_TUPLE(BOOST_PP_ARRAY_REMOVE(BOOST_PP_TUPLE_TO_ARRAY(tuple), i)) \
/**/
#
# define BOOST_PP_TUPLE_REMOVE_RETURN(tuple, i) tuple
#
# /* BOOST_PP_TUPLE_REMOVE_D */
#
# define BOOST_PP_TUPLE_REMOVE_D(d, tuple, i) \
    BOOST_PP_IIF \
        ( \
        BOOST_PP_GREATER_D(d, BOOST_PP_TUPLE_SIZE(tuple), 1), \
        BOOST_PP_TUPLE_REMOVE_D_EXEC, \
        BOOST_PP_TUPLE_REMOVE_D_RETURN \
        ) \
    (d, tuple, i) \
/**/
#
# define BOOST_PP_TUPLE_REMOVE_D_EXEC(d, tuple, i) \
    BOOST_PP_ARRAY_TO_TUPLE(BOOST_PP_ARRAY_REMOVE_D(d, BOOST_PP_TUPLE_TO_ARRAY(tuple), i)) \
/**/
#
# define BOOST_PP_TUPLE_REMOVE_D_RETURN(d, tuple, i) tuple
#
# endif // BOOST_PP_VARIADICS
#
# endif // BOOST_PREPROCESSOR_TUPLE_REMOVE_HPP

/* remove.hpp
x3zggvnAtTKnobkyp9ucnQ8+rsrpMK5Xv61288E65AugfI7ng5GQewbByuk2Ph8oro9s5W8fpvVekd3yQ/NQPuUzOyz/En2n1lb+9jS1TVflcZvu6O60Ta9+SuNF2h9Q+gmtlXknCVjzkvZ1KO2JPHnS+0nbb9H7SUpz1syeJ6jcyEq8JNzPednp2C7XUX7M/TZedlaxSwHSxPqhajtz8F9DsktzTbso+bxwP+dzVy+n+bz+mdiuWQ6fA0aNk/jbJTjJ36nPqo6HXK5Xv3uMuSn0BlnbXW1/LEW+AMoXAt4jRd4tWrznQ24ngpX33SPV/TE0n/O3p7fT/P30hbU/+tvmGNqLVORhYJhXhMr9cHq+xOMenZM8nv6iKo+lXK++NLNWPN5AvgDKF+iQx730vWcbj6XD1DyOHs95fL6H0zz+8FX1/XDfeIm/0t+d5O/kV1X5u8r16l/IrdW8mDAB/FG+eo7HP/THTLDx90KV5/mlEzh/Lw50mr9bX8vzorzfbaWp8n63hTplu00TJT5fdHeSz/NfV50X+03kvOyt75AXD8ilIlh52TtaPS/OmyjNi3sLazEvXp3I+Swb6jSfwnfV98eUAom/Mi8n+bv4bdX+WMz16l+aWqvxfAL5AihfK4fjuQRyxxCsvL+Ur+6PCZM4fy/fxvrO1crz4hniM8tgnRcr98MlkyQeX7Y4yeMH31fl8QTXq99XWCsevQs5j/uaO+TxFPR7FNp43Jer5nF6Iedx/230wx+r74dnCiX+9jvdD3/g/CnPj0VWHjw8X/lNb4FCn8Z6P5ENPWNafJxDPUKKbHyUp9j4sO0Zm1kkX1cfqKu8rvbycHF3cfUwudeorpeva6z/F0lzRXkp/mumcW2tNVfETOY2OviC0zbKpHemHmJNK9movakje1x/QV+ftcKe9hDsac/EnnZ/7CFUlj9vsszJwXEKTjxMNeIigcoOr8TFYVEntUlvO595uJmglZOh5qIBz+cxxWbvA6WivfWNaerWtPUxlGGaYrP1gV/UfX/mFLldr+7w0JnMLubmNfALEMHbpXyfYqTrXHbSbQ52eM9l870eYfHec/Gth7mV7c/L07/aXdnmloo2az//Qb4mYr5D4rphgv3nP5C7IbX31fZV9pRNldt7mHU+KlqSN5fVtr09jXM026scS9t4eXoUlq55N8mYPTvfQN4mPK+b1OqqY9of8jshex3B2m5kwF4I9Xk6e5qy7cktK1vb8fwTpm4/9gk7ave6aVK7u/5N09L2230VeZvwvAXVtHsTZL9BsLW76wHG1DYfNl3Z7u5dampzrTbD3nbbvHy61OZuH9XS1leQtwnPO7+aNq+C7GUEW5u7na9q65QZyjanfF0bWwer24193FrtLZkhtTdlbi1tfA55m/C8sWhvWwftnQfZMwi29qbMrGrjmAeU7e21pqY21mor7FulrQVcvx7K29XStocfkNra80o1tp0M2QMItrb2iqpq29C/Ktvad1RtbOuvbi/2m3e2rKYy4mz3+zb9Bg/D/KUehsOsy0oXo372uVq2e99fpXanba/GxvmQ3Ytga3faD3K71+qH+3wO+Re9IYNQhtDUYsVhPoQUmtFebwR+3Fw85nkOIxxBaCHm4zKvIkTguCVCC1VopdC1CqG1hbBSKOfpkUi7ByEKoQ1CtCK0VYQYRYhFiEOIR0hASERoh3CvIrRHeA/tM/LjDiI6GToidOJ/J/G2dbaDXTh25ZjMsRvH7sAeCOTrh8cpQ4oiLRihJ0I9hF68/EYIt7yRLh5zH0Fm+lvWsQBB9jMrpZFsb/ydivCzT9U8N3zUeWT5PghpCH0RflPkvemjKYsAWR76IfRX1Ec=
*/