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
# ifndef BOOST_PREPROCESSOR_ARRAY_TO_SEQ_HPP
# define BOOST_PREPROCESSOR_ARRAY_TO_SEQ_HPP
#
# include <boost/preprocessor/cat.hpp>
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/array/size.hpp>
# include <boost/preprocessor/control/if.hpp>
# include <boost/preprocessor/tuple/to_seq.hpp>
#
# /* BOOST_PP_ARRAY_TO_SEQ */
#
#    define BOOST_PP_ARRAY_TO_SEQ(array) \
        BOOST_PP_IF \
            ( \
            BOOST_PP_ARRAY_SIZE(array), \
            BOOST_PP_ARRAY_TO_SEQ_DO, \
            BOOST_PP_ARRAY_TO_SEQ_EMPTY \
            ) \
        (array) \
/**/
#    define BOOST_PP_ARRAY_TO_SEQ_EMPTY(array)
#
# if BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_MSVC()
#    define BOOST_PP_ARRAY_TO_SEQ_DO(array) BOOST_PP_ARRAY_TO_SEQ_I(BOOST_PP_TUPLE_TO_SEQ, array)
#    define BOOST_PP_ARRAY_TO_SEQ_I(m, args) BOOST_PP_ARRAY_TO_SEQ_II(m, args)
#    define BOOST_PP_ARRAY_TO_SEQ_II(m, args) BOOST_PP_CAT(m ## args,)
# elif BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_MWCC()
#    define BOOST_PP_ARRAY_TO_SEQ_DO(array) BOOST_PP_ARRAY_TO_SEQ_I(array)
#    define BOOST_PP_ARRAY_TO_SEQ_I(array) BOOST_PP_TUPLE_TO_SEQ ## array
# else
#    define BOOST_PP_ARRAY_TO_SEQ_DO(array) BOOST_PP_TUPLE_TO_SEQ array
# endif
#
# endif

/* to_seq.hpp
AnLM1yH/LXR5sTF4iBgkmnG9FpszEhm9Gr/y8hxjjpr8AzFTJX74Afhy9lLs6yDsQAX5D+zZbY2xO3HkKmfhSyKIw27Af9aQLycfcuU0fAdytqmGcZyDTDuYM3EQc4KRW/enPdiVHBxUyCRsCrkKHZybhfwODSGn+jW2hPFJuIy+LaQO9OF85PWuxcj1r8w7YCMPNAUL4H8ffJ332E4Hb66Edx7K4gPPLGI8jJiFMercCD/RgpxrIn4AWRhIvU3AiRXwd3g/8unMm3U4jO0sYd4DzEJaTfbgO6/CF8cRy1/GvOHMDLDtViERhj9h3E7ZAX6k3tbg/2Lq6/gLeU18//7f0M8YbARydHYr4smNxHTPI9vf8Rvc/PpiYgrw0udgnYHb6Df1rCGmve9bZPdBcmudkHvw9OFpxDanIhu74Rn9/rkdsj4Vu2nDfoCDE9GNI5XkFpZhl+nDjTuxrSncw3xE2iBknr5XLIWXa8iTf4+N/Zp4jTmbKamauZfq6fS/FbFj2mXI+EbmA9uA24ibpiA/scuIRcD9HVfDV+KG9viJGZ/St5+N+SxkD9m/G5nqkoxskTNLmEW9VeRhfgbfo5OfIK+bqTcJH/dFb3zqLOQMHdh3H3p6DrL9FGNBXNAdOWtttJ05mUP486ceh/8fYP+Qm6hTiYufALO/yRzlQWSMOWrXMHIK8K3VTOaQsHF/jfbaomqwlecxfO1s7EIIWPkLZC1fl+YXcj2f2PcU6txDnIENaAM2nJ+HT0Cfvn8SHJ+HXToVuXpPl7z92Ht09q/LyPleT7vszG+vIA+CLITjw0Jp6yR0rT1jdVUpOYjbsZOnifztUuJh4rnnjNz4nWCkNsxfgqni34XG2LceDC48DTuSje3FlzRGFlqA0c+60sj/gfnjwA/EQ9ti8Q/R2AfG+T0wSveN9LET84L4rnewI6XkXVqOAudcy3ztZvZQ1Ii1XgNHLSKeBk/V7OIa94x7DoyZTA6wPzpxJnY/mbmwXsy30a5HXweLx+EPpghl8NHUdYORZz+IvyNn33Qz9YDdFmzg72jmQ7bSDjDzh23J35J3mrQJfVmA/1qKjjDeu8qJnwx+jsJvDwMrlLK+JEmn3dh1eLYSO9uhB/m7l+n7Muq9AoyJj36VGPVy/O/6ztiMdOLDhdhCfP9+fFXYPp5Lvr0R/viLfGzLANpwPzKzGp2cRA6A/sRN1GiLbvrtrLHkB7LJP/Am5k/t8UvTieORi779hbjTmIOAj+jkS/jsQifz9mD53uchqzcYcw2sbxmBv4DfTXlmM+QslbVOmdjoZ85DP06HD5uxIeQoE65GRvBdFzpFliAfD8ODfbOZIzgbeYkkT/mCkScG83wIBoMnEoLOYZM7I/fZ/fC9w8Cv+J5z0hmT4cixEZcvgS/fkB/6EZsKfv8Y7LEDn1B2JrEamPcZ/ECficgzeHA8OCGKco5+5CcTkVXmOmYOwv8h262utsnsrsheMTHzQOJxbHtsc2JB+DKZ9o3Fv5xGn5p1Qm6+RF6vRv7wZ9F9mZNrS3yfQi4XvNqT+Lr6APKNn1zZmLZSd09k6I1B+JQw5ucOImOfgjcjyZ+RV4pBNp69i7ZvAJOh0zfehL/bSw6iPfEQGMJ2EHmZir0oInYnzzZ3BLZgK/fCt+VrsZ/LkD3kNTQV24Lc/bqFOvaSr0P+bHGaiZt7rEA2yuD35WC9iWAe5hS2dGD9FjxPQO7ima9K7YGPX8zcT3ti3w9ZwzQYfb8Tu4vsHUF2NzUiH0bdT90Bzn8Vu1sJn28nxwFOyJ9L/ukH5DkH2zEJv7pSkyboXAfk9Tz4egaYPPFLdB3eP4jfXUk+dEc1uQr6Foqvjys=
*/