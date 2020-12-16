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
# ifndef BOOST_PREPROCESSOR_LOGICAL_BITNOR_HPP
# define BOOST_PREPROCESSOR_LOGICAL_BITNOR_HPP
#
# include <boost/preprocessor/config/config.hpp>
#
# /* BOOST_PP_BITNOR */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_MWCC()
#    define BOOST_PP_BITNOR(x, y) BOOST_PP_BITNOR_I(x, y)
# else
#    define BOOST_PP_BITNOR(x, y) BOOST_PP_BITNOR_OO((x, y))
#    define BOOST_PP_BITNOR_OO(par) BOOST_PP_BITNOR_I ## par
# endif
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_MSVC()
#    define BOOST_PP_BITNOR_I(x, y) BOOST_PP_BITNOR_ ## x ## y
# else
#    define BOOST_PP_BITNOR_I(x, y) BOOST_PP_BITNOR_ID(BOOST_PP_BITNOR_ ## x ## y)
#    define BOOST_PP_BITNOR_ID(id) id
# endif
#
# define BOOST_PP_BITNOR_00 1
# define BOOST_PP_BITNOR_01 0
# define BOOST_PP_BITNOR_10 0
# define BOOST_PP_BITNOR_11 0
#
# endif

/* bitnor.hpp
eKr7b2bgZNYXuOvKgZT9cKpWu802OWxH1S2J7f/Ve+ceaJ2xey0e2tEug3E1M/7keQ7kvRQxy6CeXqvfLwVyXl3Xum31NF1pljboDtq5ORls8dqFFtQjtCYtuu8TmdOZtCU6lV7esUJRPnajHwn3a5FxJ9KRYSdjZnVWGsx/R9YECOHz+q9itkUtb/+bTfbWR/uFlJc+wQjF6yORozpRGXWFWtviaFJ5YxjdPw7GKC3utYva22XP121scT398iHNvyOPUI+sddFzM5DXMarXYKqePRSnfapZB1eh8Ayke1l3b3Oj8dPWMWLk93HR81GaadqPa2mbpus+zJHZuTNZH+qLuzpe3tB07lmKJYmC2aRX88he0fkMtSmNeBDp69XGxXr8aL+tlkK9t45ZRu6/vWRENYKlBlPQWqTl0BFmZKBtjmmQ0rZ9C/KtV7LDPmcLOa/sSvIGvYhGx1j0zBu8JlBXEVh7jXqIaFTWti4jy2pbpokSKvyYad3TMZgkfTDv9pd9sa1hN46+0LZPEzXkNnzYZYHRO6cxX5tL6k4/XZE8m2bU11E9bfoiel1FlrxoLsN2rzFFXnXUfV1/M+MP58qX+m5pj+oJ60hVF+K0MPlrKXagkWJXXau6SZzAXN02ezuSNBRmwjLC3LEaOhgUdTc0trfUT3K6Z88wgyTUOmDy1NcsWdTT0tnV0G51sGeGQRPr4jxNZO51g3cwa8XLHGcFGrJnOXiBuZbXBUWXSDQmgZnGXbZ0VN8byJyz/qpnrC6SNtZusARq0ilsN2pmy9xasPuuaTMi9bbuXQ5YTutu73L7U9mk7mq3yGI20aZeqg2d68PSIfoD/5hiIF9I53UPGEdm6KETx+j1zjB6tZ6u6tV5enVGL5tfQ9j700XSx3OwyEySDloP+ujGeNfL8T+XvZhcV2dHUH88IY2rJEC9lmv6Ef/PO5Fnbhwb8c/o+beo+TWyyqLLaa/0lv+WaxdUy/EBO9dwwzoEjmCkyEbV1fMu3jaizXNTQY1zuuFMr7gofJ6la/GixS3+BvSUatdsdMrZFKzLnp8Iylnkf9tSsCfqqD374IXMaTF311tXYk5r9JvNPdgItRK4WbbvGWirfi/JkEjpWmpov87uLnmG/uQksEyDpq526j2wYSXMCjNpqPeoqeOZ43tBqp99DkLTP5gn+fw0aFrcFfSDWNc17V6V8NRmL98x62y91nv7bEx51jpIKMy5nOCpxaZbszhmUzWq76WuriX0FVeF5HRHVvNP6wEZykg5nSAxxcTVPDcvQeQ5l9GfSrEIMaBjCD2Ervlj9lbzDEbLT6npgNFLOs0KTc0cdk00A7vmWc3xKOyGGa9oSfdkvRo7kjDrKrQy3sBX7OlRyog9luhstgZvViArEwSdMlInZS0+xlgk7FZ+kKaP4Q15y/qWFiutEk2xbKyP/ZkCa1G+ixpujpLqqTLjf4GDGvk0ofSSRAdVmvyMQlJx9TeYq6EXaqzFf4KSj6SX51AwRtL3RWTajkVblvx3SKwGa6yUqkH/bIiWUdXSmNLue3OaLp0vcojDmOKOmsjZuREtStFIZNIaD/roVrHbsrTdpZwgoZ1Z6LwMIozH0oRHz2J6NbXGVCDS39vIsss3aNojCnoaKX5u3fIqYa83jOzVAwbSl8tdxTuNBHeVGMEOnfI5enK0TWX7TbvouRI+K6LrjHbfa6lstpRXBDVqapCbnj8lEeLnSujeH6/MJKmXI8gEGy2SpzXWOXueQgfoeG0X9kd0X+2pF/oXthuRp8c/v2tBSPjzCpzTJasxG6QJ8beWPSOt/aaCEadQcXU0jy6Y/yqhq8DkjVlAsScEI0WAuSntsm7vWbU=
*/