# /* **************************************************************************
#  *                                                                          *
#  *     (C) Copyright Paul Mensonides 2002.
#  *     Distributed under the Boost Software License, Version 1.0. (See
#  *     accompanying file LICENSE_1_0.txt or copy at
#  *     http://www.boost.org/LICENSE_1_0.txt)
#  *                                                                          *
#  ************************************************************************** */
#
# ifndef BOOST_PREPROCESSOR_DETAIL_SPLIT_HPP
# define BOOST_PREPROCESSOR_DETAIL_SPLIT_HPP
#
# include <boost/preprocessor/config/config.hpp>
#
# /* BOOST_PP_SPLIT */
#
# if BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_MWCC()
#    define BOOST_PP_SPLIT(n, im) BOOST_PP_SPLIT_I((n, im))
#    define BOOST_PP_SPLIT_I(par) BOOST_PP_SPLIT_II ## par
#    define BOOST_PP_SPLIT_II(n, a, b) BOOST_PP_SPLIT_ ## n(a, b)
# elif BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_MSVC()
#    define BOOST_PP_SPLIT(n, im) BOOST_PP_SPLIT_I(n((im)))
#    define BOOST_PP_SPLIT_I(n) BOOST_PP_SPLIT_ID(BOOST_PP_SPLIT_II_ ## n)
#    define BOOST_PP_SPLIT_II_0(s) BOOST_PP_SPLIT_ID(BOOST_PP_SPLIT_0 s)
#    define BOOST_PP_SPLIT_II_1(s) BOOST_PP_SPLIT_ID(BOOST_PP_SPLIT_1 s)
#    define BOOST_PP_SPLIT_ID(id) id
# else
#    define BOOST_PP_SPLIT(n, im) BOOST_PP_SPLIT_I(n)(im)
#    define BOOST_PP_SPLIT_I(n) BOOST_PP_SPLIT_ ## n
# endif
#
# define BOOST_PP_SPLIT_0(a, b) a
# define BOOST_PP_SPLIT_1(a, b) b
#
# endif

/* split.hpp
lLX3Innf1EzQK7Nkpq7kZPLUBwuYyCqlWVkrBY6xTxW2RSf5T4a6TkoS9udBsp5p+DEtOqz4CCqhL+v/s19x9fEbPhQtrHY/KZfFoPN66j+nijMqGbEaCM7+GjM5PVff4+Al4zBkCFClLBuzcZqBo82QaJzQaIZM1AkdGYQsJhdn96XZuhtGcRc6Jw2CIBO4U0v1i9RSbYeeiejOFbqTSuRD3vdTZn6jmmO6mciTaEndL6nKdy0ZQHdWQUXtOi8xoOGoU/wDE33wjV3xD0h0aziajvPQKzrxl2TWzgCwxokGdvOemVr9nL5szSdvJNcO8op1gYm64Em7j9r3k5Tx/d/L9X7jHnOlYsx9nDUHOFxMFw6QD0+YiuC/EG603iHxwVUiUgmlCn9eiuagCE+ClcNVqb82mPsb7kaRALfJVQXZ2dNb5aqCRft93GlJh9BQT/Lvh/WWuE/2ZCep4Jf/TebuCzJ5kstPbFZX1ouYnqhRw8VblLi2BvuHnNjBm82lQGXil+bWTGKoWfrERdalCANJhGDfGVDF4tFrdQY9upubHYmO6p+TZBdFDZomgvgFJMdXgSWrSzBHxwCLDG7G4hz7kJkNlhjfkMGCDpvO3J5BSXNVq9umsBjO649rTZpkpAt9+R08S/YOcgZBERgh2c5rqFOt4fvifBE3z9GiNaQ1Ryucg461tasWS96RjxUNYPX6hxAG1VSgaNtYRYq0CXwMrxQ9jYyrDa/XyuFXkkOiDxmN+VXFBT85PHAu4z1UPBwJoy7VjJSpa8bajXF2OhlMl4UXqAzV2Gr7grC6GfTMmSLnhZWBQDi2W12Jp+waTg6pbbZ806Jf+GKXA+OqAFQhtcRG3yK5xE910dod8DDLGLuNFrskkx5Pg0Ruh/+AMM3geyIPhIg8N6AlFpr67w6pUQignlZyPblpCuPlQqn6YXAyaVntLpQTgCXQtMJg4XZOwC2HSab1R4swhw4oHyO4P8xxiuC7yBk51Sg5zSrPnsdMy1P3ojSgRtuothSUB6h6G7UwBZUH1HwbNTMF5QOqzUbdnIJyAbXPRo1OQbmB8vSyUINsFH/yvsxG9bFRZMuDly90StfMx9OotikPPyotWYvKYaXRrSxXLByUTJpflC2nPlsFfI0D/Ss3MglJ5kHlFjImNg13GDX4UxsgWSQ6iaXiBU/bu1n9jMN2E8941Oohv35Mesh3fP/TUcQOobt9jCd3t+zG3pBtNW0/pnXF3wCtZD0sZPgo61zK+vKnZG/bQ9H2Q7nkx55aSK171Fx7DPCHjCqLvHdKSZtToz6DqEYOaj7+KzlqVCb3mdIOCOgCYJzfL6R1AF1FLDcSV6ErnQacMQ0VGlLjLkYKLfAGQfvIPHR7YzOF1H3wh7Aw6yUCGe4yuYZ6cSVg+wRWHlR3A2Yopr+W4oaNyt4UuEoCUzgwAgGjlb2D59ELlgfUowvNVU+PgGpBwG9MySUKL1N4jDYOdaKopBMydiKMvUXG5uBFfY6owe9TjtcKqJEiSwGR7woEo2eJ5WC2cRWqT8sSWYmzjAoK7tDBnkLUQVUs5HXaIDxsNX4nox1Zxr9DDeulM7+zcqIIQdUX/wH1AFLi/dY7r2U9S6l1D1DZOsgF533kY5f+MWRPPEfC/QpuDNx1cHfANcC9CLccrhluDtzf4BbBWfNtJd8MujRlvi2kadJYNH8EC+DFR2gKYF8SPpl/y+CqUi7/qYQrN3X1ehYeDecnQ/ImiGqkaNT3V1SnUY459ab+frSa8We6KpN0MVm0hB7mbGjvlj39G5mD98Z5Di7UWrfjEZo5Q1GObX7DNr6BkvwkIjNs/FV9B6iO8gZH6WdHeZGi/JWivCA=
*/