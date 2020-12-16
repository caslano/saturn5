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
# ifndef BOOST_PREPROCESSOR_CONTROL_IIF_HPP
# define BOOST_PREPROCESSOR_CONTROL_IIF_HPP
#
# include <boost/preprocessor/config/config.hpp>
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_MWCC()
#    define BOOST_PP_IIF(bit, t, f) BOOST_PP_IIF_I(bit, t, f)
# else
#    define BOOST_PP_IIF(bit, t, f) BOOST_PP_IIF_OO((bit, t, f))
#    define BOOST_PP_IIF_OO(par) BOOST_PP_IIF_I ## par
# endif
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_MSVC()
#    define BOOST_PP_IIF_I(bit, t, f) BOOST_PP_IIF_ ## bit(t, f)
# else
#    define BOOST_PP_IIF_I(bit, t, f) BOOST_PP_IIF_II(BOOST_PP_IIF_ ## bit(t, f))
#    define BOOST_PP_IIF_II(id) id
# endif
#
# define BOOST_PP_IIF_0(t, f) f
# define BOOST_PP_IIF_1(t, f) t
#
# endif

/* iif.hpp
6dDOpnX9/Uh6EOERBMUWd4E/pdvTxj+fl3/ueW4xbHOYuXKJzdbEE0V2y6v3G/pSnb2TrEIYHGekkOwEUzpK1cXMSD8vMnTAdIix9FhZWT+JHJ2WFZkerfCWZT9fWPBsAXFHEVUsFuMBTSOnaYrmrSLHsryqOPxCkckpkofnMLmsnDuhBvbCUWotU/eNVzU+Z2yaQcpJWmmVw8uFCgKiJ1fnoUVupScgLioyD+BvT+G6Md8CwlZk2P6PqJfZjFEjJUpkTGIuQXE3zeWmWba1PaayHDtdd0YLj1TXWz38RYEpg25CMT8b/j4sYNydw+vOnA0PUx+2wG8rkDAesZdh3GQVKinEjPmK3gY26Iqfy9z5kXammSlvVE8PCyxZ3FpgOgSE43GMX9laNTEY6/LpaMPFioA3yNATJ6Ge0ToCdgnM4WpSyebSasozMRNweEnEie90vDa0PHUEDL714Isk558vVY9ZE+qBa2jNuxxQXtVBq8vb/4AHnRjKCW5K+PM/SBnMlPj5ZECaAny0M1e37aGt4/xrJC1ONhxeFWBDs+6f3/wCCp16K9K2/W17U+L37DtHbQ8nqYe4UAYXcjYVarknXE84xnjv6KFuQE5nvPowA/QAQDH5RXxY8+R89SinfXg1FzJEeSBIraDmcGtUhtl7NRu80gNi4zWGc/UwdT3n/UGWVzdx7JcGNj7ySPeDl2uu0bUNsq2tmn7hDtzLpZfK0k1TZAeGnteB4qv1DnyMDszT67zSrFM/H0ukWfpTEMvcvruDf5rNBuTQSMnv1C4a6S5bZG+zB6NCs9enZvKyejSfpwt1ACUu0+FnF9DAG+BFBF7G4JsZPB3gdPY9goFHMbAO2hX0qSsZ9C4GTaucP6+i1TovM3zUWkK94OvjkN1BP3BHINL2NAmkS+CsoOTjYhLa+WeoPONLS2mqY8T5HB4jlK+fJgfFDnq9zWGuaku4zgwaYMYQTtIBf5ovN6Q+QhUUyjUmitWck0pF9LZlH8bi7Yic6uwhHsqXGmFYV12YoBAya/KNw4fBtHrgmQR5tUVWglj80yTGc0+FesLKhlS+LoDbAq0X8Kdp89nlVtzBp2kUjDNXL7YBpjPjlERPZPvc1vPK33WB8h+b5TM/u7yxHvXkE8Sl19jP8/dxxtP5j6+b/h0vFe9kPNnfKV7eB0jFM7InSHdDoN0t4fXc9PSOvNT0DVpv4yZz/JWmvF6RPQCzAA40XW8z8w80OXrldrlmdtW1J6zWyIRWM0hVrFPZzFymc3ZLdDB5l7OlramelG7D4PY8IPy4VyEzsuxmxuZc1tDGIjUHZYMMY2TeI0sly1JzbGapb3KFJWT6CHK+kbEIGQDNoEhAPLYb5rx8bOCkynB7Hm4Z5MSFxtEjOTQGgMkMqJZYfVkwEZyoIm7sRpLRrSKAUWUBr5gDnMxTt08I8K4htvCIboWNlqDUcC6VBlSnwSJUsR0V45nKp2R2E2m5bKJfNnHmOZDdKntiQrfKyMyBPjfv0jQisaz3EcQgTVDvar1eh44tjuqN7DLqXdAt75yaSiac1y0dNNNOaIqABtVnofoJsvocWf0oxp9JG3njklRyvOnXNtXLmzAktBr8HUf6j7cbf8fp/B2n83eczt9x/wX+nnoh7p6ZY3D3AXTBMCd3Y7vOnFhGHWsx6v4c5sc8yY9pzxM5skDuayRbysG+Sg72qAvy476vnM+PnTN0Zty10xi/8ecz4w+/8hnM+AMuldZtVOLMUdk8k0cFCa3NDjv5v83sdt/Iro+HXY6D207jQMa9VLx1o/Er/qYqm0Hjl5omJdifnZ/P9B0dS993xzN9WaBH1nEFaMZIbgY1oNUQKGilSdg=
*/