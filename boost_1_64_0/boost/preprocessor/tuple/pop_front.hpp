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
# ifndef BOOST_PREPROCESSOR_TUPLE_POP_FRONT_HPP
# define BOOST_PREPROCESSOR_TUPLE_POP_FRONT_HPP
#
# include <boost/preprocessor/config/config.hpp>
#
# if BOOST_PP_VARIADICS
#
# include <boost/preprocessor/array/pop_front.hpp>
# include <boost/preprocessor/array/to_tuple.hpp>
# include <boost/preprocessor/comparison/greater.hpp>
# include <boost/preprocessor/control/iif.hpp>
# include <boost/preprocessor/tuple/size.hpp>
# include <boost/preprocessor/tuple/to_array.hpp>
#
#
# /* BOOST_PP_TUPLE_POP_FRONT */
#
# define BOOST_PP_TUPLE_POP_FRONT(tuple) \
    BOOST_PP_IIF \
        ( \
        BOOST_PP_GREATER(BOOST_PP_TUPLE_SIZE(tuple),1), \
        BOOST_PP_TUPLE_POP_FRONT_EXEC, \
        BOOST_PP_TUPLE_POP_FRONT_RETURN \
        ) \
    (tuple) \
/**/
#
# define BOOST_PP_TUPLE_POP_FRONT_EXEC(tuple) \
    BOOST_PP_ARRAY_TO_TUPLE(BOOST_PP_ARRAY_POP_FRONT(BOOST_PP_TUPLE_TO_ARRAY(tuple))) \
/**/
#
# define BOOST_PP_TUPLE_POP_FRONT_RETURN(tuple) tuple
#
# /* BOOST_PP_TUPLE_POP_FRONT_Z */
#
# define BOOST_PP_TUPLE_POP_FRONT_Z(z, tuple) \
    BOOST_PP_IIF \
        ( \
        BOOST_PP_GREATER(BOOST_PP_TUPLE_SIZE(tuple),1), \
        BOOST_PP_TUPLE_POP_FRONT_Z_EXEC, \
        BOOST_PP_TUPLE_POP_FRONT_Z_RETURN \
        ) \
    (z, tuple) \
/**/
#
# define BOOST_PP_TUPLE_POP_FRONT_Z_EXEC(z, tuple) \
    BOOST_PP_ARRAY_TO_TUPLE(BOOST_PP_ARRAY_POP_FRONT_Z(z, BOOST_PP_TUPLE_TO_ARRAY(tuple))) \
/**/
#
# define BOOST_PP_TUPLE_POP_FRONT_Z_RETURN(z, tuple) tuple
#
# endif // BOOST_PP_VARIADICS
#
# endif // BOOST_PREPROCESSOR_TUPLE_POP_FRONT_HPP

/* pop_front.hpp
vmFXm/cJexzzno10R7z331M977o9Nee91Z7qee+859/H+8E92rwboq2CvyGYEX5GEHlnpQreaZLW5n1KqWPex5U65n0EpT/FRjvg3UIynxHvu6vhPZFkjzrkvTfJlP5beD9WKvOuPMcdiLcK1jVirxfHNiIhz4vyD4/H1JSXKe4bTqeXO+iZ0o/inE17tLPyCnLxwobiW8uhlG+Ccr7mugQxjmxlkuIsRq11ykDgUEovNyw0eNo9N3Z5QZSZLsjnRlrXkPfvUboJx9Zv9/cjnUcNsu+/jPyx6Xye5nk+eVGU+Yg1Z7u5HliI8vmQnlXQ8zQdTzfI14cTJpJpVdeHz1p4Wt5Uij+lXI/GukyBoq5HFXV9RhyTVMbbBoVvxYyscfz5Hc+zh/K0w3gJJ46i6aIbG9cU11xi/hNUx/GZ6bjvyRhvTdsp1kW6J4NexTrgBNL7Ao7lsrMVdTURRzqM3T4+pmgM0Ricx8Q12eLvzBEuOn19F3e9ydwCX5v29PQwBrl46h/ZaG6OQ1df6VmFP793onM4jnnXlGz7c5lYRj36lnIwL+cGygmgckpdXPShUOjuy/WRrkBxrEB2L+SuIwTh2MO9+IqoQwwNuJ6UWGt9Xfz1syNRX29za+jy8LJdJ6FuVK/O8n0u2WUdOOtJbZ9N9ZoK+RD+7UYxBCNfPYQQhPoIDRBCeBjqY8WGvN2hltoF23eTG/FruMl21lwtGt8Ltbyk498GTYhFsjoO9wryt0HFse0vj23p/YnugbC7+P4E+hF/+wF6zPy+QxoBFHeK1sl4zyfuzNQX0T+pd/rjWOx/6JdyryS5RB936nu4Pwu0Hjfnx6n8eOCL1uO+/DidH3/pZz027bUe53pbj1uojnuqjrNVx0+rjl9VHZ9THV9VHXuXqcpXHT+oOl6jOv6eH/fn7fN4yXo8MFD1HKk9338p+iPjOAQyoSRfjJdh0jOxDxEL6oXjyIayn9iiGROy0u+fmFnElHu5KN8AFoVSNfcnUrpAegbRNbd405M+ZsqErMl5E7XWz+U8fO2F56H7CPn6WpaTrr3lfQtYJxJrmj4mu0ixrqteg2rA27CV9LwtoH+xNuwM8xeasy7CLBZM6WCF0t8VTLi6Wo7qbBUaK32qSvOf7mXaWyrY7icmUj433VKWizjI4IiRzEBBZ5OT4kZQXLCkd/LEyRn56eCKvwMlz6ND90nnFVrvSKVyWuks1vtI/Kjt0vPM65DhduRpslZ/rvMg6WgomNlPzFNwo3xXkY/qI3GKcw+86+LOg79fxu8lKW93He67UAt3xfyPuXlioeSftT3Jtde1Qs9oqnNBPF9bs9k3PQ+LbFRnmofkOT5jakZePsXfQHwk5k93xIYp1tEaWygo4zjydaUa+PPMFXnl89wJ1FX9zfT9iFP77nxJjoul+VD5jFAxZpRzJcYB0iqNA+neDnwgTe7vyEN9l57JqPo18pBt6T5bYXPkIdtRHVT2RhpxS+WoeMc9J/EbJubjnNNcSW2ketPx1Jetx6NwrLx/P8DnliZWYGEI76KcYuK1uCg/J6dghnq9Q/t5G88j1Pg5lrTWwM8HS/bJ87/yfiH5ccpL/sxiOP6MlFJeR/Fi1Z6P7O0ocjQG3PlXRNlfBrfHs5TWrl3Zq24vs77ml9kVj1JW5vUFK/EuxTV3KdtUt5TF+JWyY/6l4K6UXQkqZZPrlTJD/VK2vEEpCw8tZXsblbLkxqXsXDj+bvoFW9rcS1gRYRFWtvISlkVahPVRZmFDtEXYEuMlbIizCBEJQcy1XTpLv7c529hhPnup0wLWuMt8Fpe8gH3a/VG2NGUBG9JngbTO8zW1q4w/f+ftRKsbDJN9cvM=
*/