# /* **************************************************************************
#  *                                                                          *
#  *     (C) Copyright Edward Diener 2014.                                    *
#  *     Distributed under the Boost Software License, Version 1.0. (See      *
#  *     accompanying file LICENSE_1_0.txt or copy at                         *
#  *     http://www.boost.org/LICENSE_1_0.txt)                                *
#  *                                                                          *
#  ************************************************************************** */
#
# /* See http://www.boost.org for most recent version. */
#
# ifndef BOOST_PREPROCESSOR_TUPLE_DETAIL_IS_SINGLE_RETURN_HPP
# define BOOST_PREPROCESSOR_TUPLE_DETAIL_IS_SINGLE_RETURN_HPP
#
# include <boost/preprocessor/config/config.hpp>
#
# /* BOOST_PP_TUPLE_IS_SINGLE_RETURN */
#
# if BOOST_PP_VARIADICS && BOOST_PP_VARIADICS_MSVC
# include <boost/preprocessor/control/iif.hpp>
# include <boost/preprocessor/facilities/is_1.hpp>
# include <boost/preprocessor/tuple/size.hpp>
# define BOOST_PP_TUPLE_IS_SINGLE_RETURN(sr,nsr,tuple)  \
    BOOST_PP_IIF(BOOST_PP_IS_1(BOOST_PP_TUPLE_SIZE(tuple)),sr,nsr) \
    /**/
# endif /* BOOST_PP_VARIADICS && BOOST_PP_VARIADICS_MSVC */
#
# endif /* BOOST_PREPROCESSOR_TUPLE_DETAIL_IS_SINGLE_RETURN_HPP */

/* is_single_return.hpp
Zi4L0mWR0Z3De9vaV9FllHSIieti6reaLm8f2iEyymH5ctz1evfv3yEyrlu8vfyolMfGREW2720vP1ZQ3j0uNqZbuKog5cet5TKC/aNDu4SryjLthMM0Bj82PsK8DCdlemh8fCTNbO1OObaLiOkW79Dvacfp4V1CI6Po1rZMZxynR8Yqe99nZRoDHRMX3r99XGR8ZPvQKNv0cwXTu3XrHh7Xv31EePvO3Ux9n7dOp2GUdaKp79zC0/qHRkWZpn/jMLbS3DT9W5ke3iuWCpHxUtE27wsFyxYdEdmOyaHR9ml5haZ1CY21Tbso03o1DW7Zv1t8XCR7XsE8v7PNMz48Oiw8jIV3GMtLMr17t3A2YFR8aDf78l52XJ/YuMjoePP6XLFOl7Ho1s3Yvc3Tv5fp8XHdu8Uza70rmqZftU7n1RIZH96uf8NGLfrHREfZ1/na30y3L/f1QtNaNrL3++eC5Q6Ni48MNbZVKC9S+/QfZHp0DBsw3jq5m2n6Ddt0WTXr7quqyvS/OO5/od3jI/pHhfcIjzLV+VHqsIfE9GToYnqxQ4THxXczvT5uFrxGo0IZF3v5LXfrazo21PH1dNsoZ6nk1W4rvyPl0sJ2HPlJlzsen/KlTA4jtrp3dXlMd/Ny3Csosx1zPHQ5pZEx0YxNTGR7Y1zcVFSp3v5KNVIleZ/Rv4nSj5FW1AjiFO1yNipl4Z+RE8ck9x+YnJ4xSvfZplSai1E+imtgJqcP4h1BL5dcW/WE0YZansrCfMJKuehp4aXK6Pc26ZP//OlngL+9H/q23f/iN10nRLf3MLX3MLX3kvtnKDVUtyvLs4d6Wlt9LfGX9cVcM0akybIF4A09vSv9WKz383LTv7tWjVlwH/cQ2/XBV/vJPR2kzhbqNDTquNTy8XTzsVTx8XAquDb4Sj9C6vtT5kzZcOr6Eof8lL7GrDI9fOxP2xnjVUGuj2qMaZlCYxoo10llnJhmHycnRuYpve30v2Prx9OEhXiKWMfK+r3rpLcd7/hsvAF6TDJ0ndThYBuzyrpeUFHbSvqw6LZrAoy2AzPGKlXUdrHXtW0Xrv+amq7no9dTT68sOdf51bmTKhjHMYxScKm/HS8Xh/EqdD1ZvS7268myjJSxjDJGjZSfHqN5QdYOgkryehd/ZkqIeYxGJA5l/7ePk1yrNlDGKXiOUfdXFa2aqhXqGeWvy7mq8VyjPIS8TpFjGGIal1/9pN8xbCfZ15/R/Ua7tKffw7xq0i3VOCfanfPY3fjuzZPrfgziXEJX2/16PtLzq1DkNpB5mfZ/vUqqplyHufZCJ2OJnauqDyy5FleuHVFSzeWHMX9y8lFTnX1UM1nXj/Uy5Xu4qt5qIFdTqGppaUlwGuvk6Vra0pQr+bu4l1AV3CuoEPc9/M7T3zYWt3X/91i2G/p+Mv24Juqa+Xo7u/nK612p1Iwhyel6+dOY7i/HE6UGpo7M0Hu+bd9suEDf98bW/1Sdd3AJUE+5GP2foP0Jvc7TfWW76XVOSh6k57+I6fVnGtOb6On6os7Wa/7q6ROZnqLb5/say5EXYEwfNbzglRYo+27YLKNOGbbGcvW56u7kL+N5V6/vaT7rTZK6FtVb1/V3dlcr1Weqm1PB9asvLTLKPfR8k5jvBD3fb/RyHdPbKj154NA0PT2L6cv19G16udrr6e1D0xL15Yh1ncvU+VLXWUwfBXXS0lMHKxkvpf6gt2N7S3kVaPGVMdyr9x835U8fvejjbT0+x0pscJ3tFliwLYo4tgfgq+8bdZ9VDZS78pUxCNTr9YSqIPvzSL1Md3zzVQl1mL26javy9NXtWRvd3q3wvqzXZwjL8hfddpQvx3bet/S+oirINng=
*/