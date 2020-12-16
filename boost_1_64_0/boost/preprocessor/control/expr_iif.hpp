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
# ifndef BOOST_PREPROCESSOR_CONTROL_EXPR_IIF_HPP
# define BOOST_PREPROCESSOR_CONTROL_EXPR_IIF_HPP
#
# include <boost/preprocessor/config/config.hpp>
#
# /* BOOST_PP_EXPR_IIF */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_MWCC()
#    define BOOST_PP_EXPR_IIF(bit, expr) BOOST_PP_EXPR_IIF_I(bit, expr)
# else
#    define BOOST_PP_EXPR_IIF(bit, expr) BOOST_PP_EXPR_IIF_OO((bit, expr))
#    define BOOST_PP_EXPR_IIF_OO(par) BOOST_PP_EXPR_IIF_I ## par
# endif
#
# define BOOST_PP_EXPR_IIF_I(bit, expr) BOOST_PP_EXPR_IIF_ ## bit(expr)
#
# define BOOST_PP_EXPR_IIF_0(expr)
# define BOOST_PP_EXPR_IIF_1(expr) expr
#
# endif

/* expr_iif.hpp
0OaqDsK6UPUSkvX0cx9hiic8j34Gnh0WnmfnmHisvVm3+R2ZlsxiqSB5yXpWfQbGqD59YlWfVtZ8Ws/hR9Qphs+VooERObNbaicEXPe0tO6OjkKVMfCyosTanKxwL5LnBXgL/aMRqdG/oqGfkc9SZnpi7YSscMIk/Ib+8UXbKdf7S2+R673bWI/qtD7hQVWKaSEQB228OLnJkjS3ldYudwD6zvjIOBp+n/ayDyzQTKPcDhBrBiKHJ9+rQV1/j75u6pGtWD+/qCpZeqqdFUkPKZInntc1Y3FHUC5QTtqvRD7DGuOLVScPBKQ6OSPS/hly5QoLZzj38+wy9YFYVXJaUK4zJyExltdpjnDfKogJxxzuOwYxsXPOai0e/QinYu1xX12gUP5Rzndzfk6dlhBOY8q70Sxd9mYFxIFeCk2bzgGIpqmOF8wWxHELEiEuEpXwUDXDyhF+U+n6nQQKiAq8yHEkTWpua3Myj//NdlJtl2Fj2hIIoiFp2RpakE4LOPKleopImhFJtyIEfBKq6+K5vKoU8HRz1f8JmROgJoRS1S2WYfqUX9pD70cub3DPcoKjUdd7GmU6tMOqxV6x12+obiFSjHjvD9vpHNNuFion5lR3owKs0HMMdaSYUKv7OLXdTM3CSt4PK/lNAX18SRF6r3Mgup0FlWBOt2QkZqhFcZZtJlUcL4P0nxKTlCFepaTimKQc0V5GBCYyeFBnT69wyx4GxZVzpBw/awtdsfUYGtdw2N98aLdkZVVYRMoCCoNeZcxetNGdPw8vrcwOicQDRuC2xbOdIBX7l0Q+//sq1HusH2A11rhobifLuS23Lo3gltBQUuNiWelJn3Ewgd/WAOh765fc8UkraVD8zRczL+suNC/P3ebl+i5sJb3fwhTO/7zZeHJ27Gx8ymdofdwfn5/tOea0u8FPfBQAKfLEVB8zbxEKY+THglOSsXSHXWIPMDbaiTX3ohd0xFV3B6avWzxOGVMUynmc1newQ7YWEN+bbazui13DirDbC4iG2XoPIgmg0EDgTvFq2eKu2cbRX6idz8mxQCEyGHUM8GphnB2YAL72YoeiVzIVWqqsI7er5v4/2aQJbgAQDkBy9kmu3DXrVCOmAFnygC6ZsJ0upUJWXqQGDH6M9fKTyKK9lyRyBdD1VQ8hBzgPl0rRlU2tUv+CRML1nExtl0azrel7iJeb3Xt0Vv7E4qgbS01WzuRWu6E/t8nxiNlvPqReaP3BcJFo5vWn7IymWesPaQ1uyNhVX9JoPPNCq0hAfKXUMEf4P9ea/30v82mUtmWfuYS84zU2ZvVrCe4ErQV9yHR8VlbVOUBfB64lCU8Zr882FgE2Y1AxtdoiZJrXJOSbXl2Wfw8vtLcgWQ6iqEUW+PFZXE1ALO8O83kT6PFZsRPodq++nAXEpd3xnGMveAtmaGmYzD6Jfd4sYw6MWA8jcgOikNofaZq0EiTjGPOrswxd9S+VfCrQBA2Gjido8EuJHjecZnjSvypjTg3IIl6lnC//wB5S/jltJP+WdLPf2KT9Bg8flHAWUV7Se7NPZmvZh0XOLLthXQv307u+SjYwejcdKCb4RWC2teh8nZYXWhHV6n0gn2KjVSkXBZDm8Yof/03T1JXIqXJiFzlYaGR7yQMQCYG0xlWObK1hZygh0rMxqTOhPUGfwRertVQE26fveI0Vq0+VzSse6a3wFEzwiRu8tDt/DSzkF1tn2slBIB3F+RxDN+wU38iGHZtu2JHrAafSCkp6WzKt85k44wAF3I1YTBqRFoQulzMB4iWUgVH01GnO0LCAZOiAVOxQcfUHRGQ3dLj5dERbD3aLvoc3vUR4GV6ysFHvpW6gLKiMKKShzbo=
*/