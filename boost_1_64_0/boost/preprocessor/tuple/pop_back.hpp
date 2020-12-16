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
# ifndef BOOST_PREPROCESSOR_TUPLE_POP_BACK_HPP
# define BOOST_PREPROCESSOR_TUPLE_POP_BACK_HPP
#
# include <boost/preprocessor/config/config.hpp>
#
# if BOOST_PP_VARIADICS
#
# include <boost/preprocessor/array/pop_back.hpp>
# include <boost/preprocessor/array/to_tuple.hpp>
# include <boost/preprocessor/comparison/greater.hpp>
# include <boost/preprocessor/control/iif.hpp>
# include <boost/preprocessor/tuple/size.hpp>
# include <boost/preprocessor/tuple/to_array.hpp>
#
# /* BOOST_PP_TUPLE_POP_BACK */
#
# define BOOST_PP_TUPLE_POP_BACK(tuple) \
    BOOST_PP_IIF \
        ( \
        BOOST_PP_GREATER(BOOST_PP_TUPLE_SIZE(tuple),1), \
        BOOST_PP_TUPLE_POP_BACK_EXEC, \
        BOOST_PP_TUPLE_POP_BACK_RETURN \
        ) \
    (tuple) \
/**/
#
# define BOOST_PP_TUPLE_POP_BACK_EXEC(tuple) \
    BOOST_PP_ARRAY_TO_TUPLE(BOOST_PP_ARRAY_POP_BACK(BOOST_PP_TUPLE_TO_ARRAY(tuple))) \
/**/
#
# define BOOST_PP_TUPLE_POP_BACK_RETURN(tuple) tuple
#
# /* BOOST_PP_TUPLE_POP_BACK_Z */
#
# define BOOST_PP_TUPLE_POP_BACK_Z(z, tuple) \
    BOOST_PP_IIF \
        ( \
        BOOST_PP_GREATER(BOOST_PP_TUPLE_SIZE(tuple),1), \
        BOOST_PP_TUPLE_POP_BACK_Z_EXEC, \
        BOOST_PP_TUPLE_POP_BACK_Z_RETURN \
        ) \
    (z, tuple) \
/**/
#
# define BOOST_PP_TUPLE_POP_BACK_Z_EXEC(z, tuple) \
    BOOST_PP_ARRAY_TO_TUPLE(BOOST_PP_ARRAY_POP_BACK_Z(z, BOOST_PP_TUPLE_TO_ARRAY(tuple))) \
/**/
#
# define BOOST_PP_TUPLE_POP_BACK_Z_RETURN(z, tuple) tuple
#
# endif // BOOST_PP_VARIADICS
#
# endif // BOOST_PREPROCESSOR_TUPLE_POP_BACK_HPP

/* pop_back.hpp
m0WyqZiDPSR+5lNcrmTHm3fQjqVBVuGlCPUVY45tsdpxSL/0ZNzIFE1O75McY+98xW0SRHlctMYh1yfY5TuE0u/HzFOHZJ61iDLjs2MYjWt6F0aL30BgGOXNQm+3SHPSLVTodz4n+aqvt7T9+GpyhTgqG/VBHNVHyR983Gvzt06Dv67RRKBd/vY74G9dNfwdUPGnxdNRBU9KjrOiFRxz/v74k/hDWZXv/0K0+UvaquZvQJ/kNnFRvAva5fC+rXY5hE75vDvOn+aU8dnQyd9/o/cM7fE7cmv1/GZCRtUPkSjzGHgbPOK9Hqof6o04ud7K8+fk+tpcXlZzWc04/sU+h9DluB/eVPGE51DUx2wcH3AwjnXbJP74PZPMXfJtcIc4Khd1oT6o5i2wIaPfKwhmhP2ct+JtEm+DyVe1Nm/8XV6b/HBc7UUrOUO8zNlhOo9gLUBxflhO6ZvZkw54nUcypWyDfM7i12Zy+RtIZhVKd9E+Z3H7LiC5IXimESV9C2gTxU3BufMe8N/Ibh9/jOSew/sTeuQdTuUKFvCJoEcwWJxbx6j0fhtvl9KX+KZQRr95CKEkx+eJ58hGKX06d+XWcTA3QNbu3PCc43v9v1B6usO1onSSsUjXI5PouCd4ak16j1K+XBhfvkbPI5kBmmsIvsAsSh+umK9zx2dkyfO17ZrAaEEcgiuCdc6u6bdJq5mzeXlKW4SHMfo140qbIhwUn11bbSE9ELTZooLeX6f3EDW5P6PgfgqzyuKqSNOPO5dV2Bh9RfP73LIs3cvYZKFY+Y7uOZJpiKtIQfPb3VyHNB+ZNPo3s9O/0W76frbSBzzaR3GoBsV5SNzL31/1FuUoTq4vfTuV85/K/eoX8Hn+L7Zrtu3Ef5/kWMfXGUHb7Y4D6HA8DkIovafdNa8wSu9S6foiVnENZ+PRzXLnry1iVTy1Cmf0S+G6e9juUaw8DegaU/M1+YJqeJlG6Ul2eXmQ0uOlfuRuuf21wDNNtO+XD/P2ObMWiLwO77tuIV19v3x5u8ZaID13xx4Sxb3N37dXvxZ4fnv199SnttfsnvqN7dXfU/8DMuq1QLPl9u+vbDZa1Ex7LTBph9VGNV0LhLz6Hhlxjm31ENLVa4EZO9Rrgdq26gs59VrgfTscrwUO3lH9WmDqjpqtBfbaUf1a4ADIqNcCPe6A7WznuX3NtefZw1bbiae4aq85Lu6wO9dCj+M55dIOx3PtJ0inuVa6n8E+QMW9jHzOuv37D4vy/oOXo+TqmxbaXEXttHGFR6HV3Hf03GmXK+iRzuXYI8XbCpX8moJ8utjjMXWnYx4HUHoXaW725HyF3wZfOI9TnVBXxPG6qjgLbanN2TqJM2zcq4az/Q44Wydzxu/DUA+olO/F7HN2oBrOjqo487Lc/n2av/I+TVFX5Xw6rJU2Z967iLOhKT0HpPbr2ze1unWCFrvs8gZdjsdlq12OuYmm9C4K3qfl5hXmF0ycmM95l8dmnTvOm1yW8lromdaMfiMQXBCGI4SjssVW3saggdmIkr/vRnvv5Pl4CW9TLDNqclas4Cws0PqNsrzCImnen0PpaVhzFTSv65Ff9lsl2ovv82Na1/ayfI2voeg7WNQm+Voc9UQc1ZM4FPWibMTJZYNDyQeY7z18vzYMZwYyYFPouGzlcCye4PCNq4z8D93wpWf/0vlx1G6Sw/nKpEifJJ3PBlH6QtwNuirSCyQbdKb0Z1gWcyOen6C+hSKZ/B3rH6ku3zEjrPIygkXWgz2z4iMr2Jj7+AohfSeUMlMySYRkqM+1IZkXWUf0Vy9xbKC/+mgEC0JdBF+EZ72rBLKTyaHfH6PPLrEs+iB4Zd4XRWnzfhXynHc=
*/