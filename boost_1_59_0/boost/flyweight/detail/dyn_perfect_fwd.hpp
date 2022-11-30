/* Copyright 2006-2014 Joaquin M Lopez Munoz.
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * See http://www.boost.org/libs/flyweight for library home page.
 */

#ifndef BOOST_FLYWEIGHT_DETAIL_DYN_PERFECT_FWD_HPP
#define BOOST_FLYWEIGHT_DETAIL_DYN_PERFECT_FWD_HPP

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/config.hpp>

#if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES)

#include <boost/preprocessor/arithmetic/add.hpp>
#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/repetition/enum.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/preprocessor/repetition/repeat_from_to.hpp>
#include <boost/preprocessor/seq/seq.hpp>

#define BOOST_FLYWEIGHT_PERFECT_FWD_ARG(z,n,_)                     \
BOOST_PP_CAT(T,n)&& BOOST_PP_CAT(t,n)

#define BOOST_FLYWEIGHT_PERFECT_FWD_N_AUX(n,name,body)             \
template<BOOST_PP_ENUM_PARAMS(n,typename T)>                       \
name(BOOST_PP_ENUM(n,BOOST_FLYWEIGHT_PERFECT_FWD_ARG,~))           \
body((FORWARD)(n))

#define BOOST_FLYWEIGHT_PERFECT_FWD_N(z,n,data)                    \
BOOST_FLYWEIGHT_PERFECT_FWD_N_AUX(                                 \
  n,BOOST_PP_SEQ_HEAD(data),                                       \
  BOOST_PP_SEQ_HEAD(BOOST_PP_SEQ_TAIL(data)))

#define BOOST_FLYWEIGHT_PERFECT_FWD_WITH_ARGS(name,body)           \
BOOST_PP_REPEAT_FROM_TO(                                           \
  1,BOOST_PP_ADD(BOOST_FLYWEIGHT_LIMIT_PERFECT_FWD_ARGS,1),        \
  BOOST_FLYWEIGHT_PERFECT_FWD_N,(name)(body))

#define BOOST_FLYWEIGHT_PERFECT_FWD(name,body)                     \
name()body((ENUM)(0))                                              \
BOOST_FLYWEIGHT_PERFECT_FWD_WITH_ARGS(name,body)

#else

/* no rvalue refs -> [const] Tn& overloads */

#include <boost/preprocessor/arithmetic/add.hpp>
#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/repetition/enum.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/preprocessor/repetition/repeat.hpp>
#include <boost/preprocessor/repetition/repeat_from_to.hpp>
#include <boost/preprocessor/seq/elem.hpp>
#include <boost/preprocessor/seq/for_each_product.hpp> 
#include <boost/preprocessor/seq/seq.hpp>
#include <boost/preprocessor/seq/size.hpp>

#define BOOST_FLYWEIGHT_CONST(b) BOOST_PP_CAT(BOOST_FLYWEIGHT_CONST,b)
#define BOOST_FLYWEIGHT_CONST0
#define BOOST_FLYWEIGHT_CONST1 const

/* if mask[n]==0 --> Tn& tn
 * if mask[n]==1 --> const Tn& tn
 */

#define BOOST_FLYWEIGHT_PERFECT_FWD_ARG(z,n,mask)                  \
BOOST_FLYWEIGHT_CONST(BOOST_PP_SEQ_ELEM(n,mask))                   \
BOOST_PP_CAT(T,n)& BOOST_PP_CAT(t,n)

/* overload accepting size(mask) args, where the template args are
 * marked const or not according to the given mask (a seq of 0 or 1)
 */

#define BOOST_FLYWEIGHT_PERFECT_FWD_MASK_AUX(r,name,body,mask)     \
template<BOOST_PP_ENUM_PARAMS(BOOST_PP_SEQ_SIZE(mask),typename T)> \
name(                                                              \
  BOOST_PP_ENUM(                                                   \
    BOOST_PP_SEQ_SIZE(mask),BOOST_FLYWEIGHT_PERFECT_FWD_ARG,mask)) \
body((ENUM)(BOOST_PP_SEQ_SIZE(mask)))

#define BOOST_FLYWEIGHT_PERFECT_FWD_MASK(r,data)                   \
BOOST_FLYWEIGHT_PERFECT_FWD_MASK_AUX(                              \
  r,                                                               \
  BOOST_PP_SEQ_ELEM(0,BOOST_PP_SEQ_HEAD(data)),                    \
  BOOST_PP_SEQ_ELEM(1,BOOST_PP_SEQ_HEAD(data)),                    \
  BOOST_PP_SEQ_TAIL(data))

#define BOOST_FLYWEIGHT_01(z,n,_) ((0)(1))

/* Perfect forwarding overloads accepting 1 to n args */
 
#define BOOST_FLYWEIGHT_PERFECT_FWD_N(z,n,data)                    \
BOOST_PP_SEQ_FOR_EACH_PRODUCT(                                     \
  BOOST_FLYWEIGHT_PERFECT_FWD_MASK,                                \
  ((data))                                                         \
  BOOST_PP_REPEAT(n,BOOST_FLYWEIGHT_01,~))

#define BOOST_FLYWEIGHT_PERFECT_FWD_WITH_ARGS(name,body)           \
BOOST_PP_REPEAT_FROM_TO(                                           \
  1,BOOST_PP_ADD(BOOST_FLYWEIGHT_LIMIT_PERFECT_FWD_ARGS,1),        \
  BOOST_FLYWEIGHT_PERFECT_FWD_N,(name)(body))

#define BOOST_FLYWEIGHT_PERFECT_FWD(name,body)                     \
name()body((ENUM)(0))                                              \
BOOST_FLYWEIGHT_PERFECT_FWD_WITH_ARGS(name,body)

#endif
#endif

/* dyn_perfect_fwd.hpp
oK22ac8iMSEjBKx0jH9MlpQr70hfSNFw3+kg+7lNaG5zysxoS5ZU0e0ux5VihyKWt5pRxmK0tifMji5F7NXVjF4vplP/SAh4C7QQTTPgFaBmZlah24b8v2Sru86E5odjSNov6v0BuVEEKDumgydj7k2gwtiN7ZycUNV8VxAii1OShijh7hci9WdngFh5rtL/FMY0AzbHI2u/qMfGvGNzMYn56G3LaKQCfNvYWcOWD7g5qtNWJuyeRMTR26DJcIZSvQL2ngskl+8xwPWtQ2R+10z/enYs2CVMy1ARDOy/InBlKdME/huiFcHeh1ID6WZGyhwbJFiMw3y3DEJhgM7f8IzkcS3gemXPVTvQ/SgdCyf66s5RNEv79BTDK1EBwNrjwWIPQhR9DWEeckXGO3R+cstv5NMbu4lsk5xSMgom2k9zJ99EBdlQHmoyYYi8fLN8l1mZs5UR7CJrEPLfkwGXFbfDawWm1W6MVSIKlXM96H1MUTf7smGhBs7Kav54oDaera/klFeS23c+7L/UQXZweBlrInNg+E/3zCndWCV2Pbq7TNotyXpkMdo3xuhc1W1jNK52paEfaEuQI5yArHMlhMsbPE7WI0QGCmE7TRf44LoyjG2D2rTI2CnjE00Qo+QYsrD96OJH06yTzpBByVQ7QCDW8UR5EGn+le0ryvPk0pDSNO0c3X8JabYPzwcaip8paT5Eqtmd+dzhy/2GoS9GBH5joYjWZ0JY0B479ijsMQH2y4xncoA2KA4EQTT1QBRimQMvrkhAkViX/iz14xhosXrZ5F3dcoWLD/wF6rokjycuH+AU/w0QQ1m+3jO0Hvrgw3Qdm/2UYR+6cLXDsklK1+S/jfoLEhnxM2P7T8nFwojvRYQ+H2h1qZ8Iw058NSqYelCTKXthpHBuXBQodeHNA3jvQJaAeoOQ15K3mH6XKX51gco2/7eLYqnCXu8Wi2jOBAls43Nb/GOS2IopBjwofi7jrJJZAoDtja37jd2RTqF/IFJFd3CU+wOqToj18WORFtRJb24YQW4Xts+KhREJB5GtDBeWwqFF/Kqo1YJpsw4RdLcBdViIxIcoI9Ab8rMffbpyWbjvN7KWZiRJGNMoncnr9Oa/WbbQ7y/vKwE8rRcMBLL2j/kOWJQebWEpGf1QSoBulT8h79yUkeK/UWiVYp3Pu6uzTlEo0m3grlPlyMe4i2oVHtgbnWPT5jIBsiWdlwh8YtSnNACRGsE5Q/j8kgOfUV1EZswiMu0Lm7ZS7GqIilKt5ywAA8GsI6F9hFhpA9i5doorMnM8myQ7CN4sMop2FBwH0HdKH1h1R74M9xT19Nbx62sNDwX19Vr8uL488Bw49bBNonOvqdxZ8/YdPHHge2QrICv6werS/XWlXdDb8zh1VIuQtZoxnIiKLSthlR5MLxDKVxB8/wk7KD5jZZwKUNL8snGdpcY1mOb6AlY1hdEFKhQupZe25O/IWiMRsa1dagopc7QR05rYKGgqnStm0u+lCjigY83nB3GwoyUl8PK4m/1+x5p+qZc5tabGvOnj67pQtDzZ1DveoyuSxlQ3uRo3X9v5HHOBG7cUa6jTzDuhizSGh1xD9+UCuCxqZ7999s152uJzI5tad3C7CCxDoStaS03upH+Z27c07ZpRVsRNFY9SVQuLiNUw0fxK1Bco2NxRW8YkjTrtOSVbbnWPN5xjPUMpYpg2FyhSRwFnXPFPgkT6zOygt/vuvEocrXw1hu577S3HBrzogEb/ygj44mAm8ryClp8jp+VrKrtUexLSA5vNtHNqSE23Bk958ge8IziHL2q0HHGjHOpuPDGSK/Mgk6qxG12Y7GIjIONmwd7ByviaDXpyNQOU8VXP9m0rlDCFL8VWz7sJjtsRJMrx18z1dNbLMj7n6s6+Qump8dxaLvrLNTyEZTXTS0yiwTjW/3G8EzRf8CdAXGAESP5oCq+9yFfcyY30XQLedyQYePHcTPmhlDfi8hCjtp1jy6Fty9VvyGBYofFoKCtlyM9csx1lhVECdahRpWIiduZlOl628oMQlYMnyKP8PGKLSwq5HvASxMqPLi7z/oPwDGgIrwvH/AIwJp4XRPoRUpPI/HbYqiQjGpb/5QCiTD2FEG2fG+2FYJ8FrugQV9qIwmgA7lJMKvRe44g7QI+do8ASr96VckYKLdlCoQ6Fax9zhARJQIgIBBGknAfkdSeFE+d6BOqtB7VKDHQZt8/3wLULD+zlj2gF5e2MB1K4R2iljQltyy8/Uak//DVMWpnRjHuSW00A7DkmjWJhH3j4j9CTlgl0wc5f9HekwOQdwYhQnF3Q1qT+0qsBY/xLJNXASRXvvypu5rYxcErqrizUX8d04cynl/15YomuGZMrYasQ1werfNIuGGUWYnFs9VaZ3xdUIGQfG8AjdFHsswJtlC0K4QUbD/lzVJKeGn2MKaTXdxd5RnnIPtiROb6or096xiTfTyJcgxFFkb4mOvycfqB6zHtmwbQoafnIwT7I2MZs8eYZ1dw0+Dw7RZPkz3XjIoHsB1/ULQknmt1i8OJphpm+b4QluqIFuBbX9JpJwuoONypkaIaAS4SZUHvVfRBtOGtSt4ls3h42GpkM3CsJjYz86NO8bAuNzOHxynjFuWWFLYDRU+cQl8wycYA1e9SM8cNml557JG49GEZXQMKhgPb8a+cdPxVsXyDKMG746X/mllsGneehT8G5eo/MtF/YMfsD4CkrIBeLiFv0FqqTm09pWzfHufH2328FiTMbFnX6gBYzlJNHF0zOEJs+UfLCQcExHbtq4Y915P9NLKrertshCZADz6M82heWiAAQx4GirC6SqxsIV6z+IMKXEzpA/25InA0gOJ+f+GwP3Z5D7CzCkDQKEbSCPxEjXPCw2lA4vkufTKvyZKrYwQIYSZXd7+PEK0A8gjkQHxyyKj2pyXgJTGCYny7XyAzV0JlY43IkGVxFss7ehUa+TNEHzNW8aNYzNywcSPpqwEcQE7rgYrkAuGmo2AFbCprjweycAqQXq+solzQQtKEEPXVjxIFaLim5gBrcngCl8Ud5IufbikwrK5zFIeHPvuR0jnUcWTaahW4aUfUmDTzQGYo0E3wxOWj7mZnnlHxonSGgYZAg14jKi2P5MaUaVk5sBhx/nmO8EA+8sFB2AAf9y3h4uxQzGDeVNDGyciVUuAIIFsGxpQupkgIQxZH2XesEJ0D0PXcgqFDO2wh8q2cmSuUjrh6zMJjFa3rkVsVHH2kL5WtFGsTYZIiq34Ywcq4pVLrfA5U53whHhqRD65S0fkHIQVUpS1l7k+beAXYLN8RTV8azEmA4GnBq0jGLk2ttzzThGxgnBa1znWojLfvUGMvsjGQxUorY5dKBmK4XMG0tlZEIecarF8R1xEKBt2vjbhn2JNaYd60L5NW3z2o9ACtU5q6qSC84mfsWUgJWETVFf7x+6rqrGqWNdRmHNZBjiunPfVU8nPY76iyjWUvYFYW+CevWADE+fNFAu41uGVSDkfunQJcyF0PM3jmh3+z5Rlwld6jXvGGYm7EUK0a1S+f6sVaZEw+DysPKQWB3DEiNrW5s62oMkGnSX6mRIshr6qcvHXlrCC5YLRUSWmrF+7PWmSF6Erf5vP2NMYnd/gbH5yvvSxQrhEmIHfoQb4uhsjtTrIT4k4vcisnTbylhMI4RfDb6vVHEjTusC/O86PvGwkk0+qJOem9Q0qCzlV+y+g4yHJ6Hu6uLWECeELm/fnuv74YPBci9cPiK0XgPHEo512+4k6Nt94rTWiok4erZzg30ocmK8v4LuPc7R1mNFcsFwNpJQgw6B6VRzEBrosyQG7tb6DxVMoe7EPmReSV+Frn4hX4Vu2EC9TRtccUCc4hMjcEzXcqr2t2Nnv3U6F3KCxaNQqjO9OIYITNjL1M/Nm4NJZoq13/miLLpirIJDZvORwruj/RxWuje5w4W6RihgnmVkUCjtbU94cdopX9Hg6Gibjo8oASc7p6Kg2HYFXQaCIY/nXJkDUWJKdfWJ0y3/whPREEEi1haLj/UNvjFfvjY9xzXdil92OETkbxFJIqYo9sSJbgML8Iofj5BIALgp4NVJtAsScIY4nu/hQnLbtrhr1IGKyS3A4Ry4TdjPNyqZV1hGQW6jaklREVFvuTUmgBFNISzVZr8/9sGD3O76NCSE24kS4gjqX5C5r0DQdWOEvwGZzPOEoGo7r7sXjUNbH45Ln74sRN3BPgYg6N3HovY13ADe2L9d8IFD/C+7DF7XdgemLZKTpcIkSq1pffQe/+S/uDID8/cl5SHiof2bT4gdPNE4/OqsRjBqKTscWxOXqDLAzkAgrPNFhxN/nCwtADH1OIj0X8itAw7SUJnUfQFGsfK3byHDHssTcoSx63hJfWUOATNlIChfG8cd9TA0rsL4vqOFPWRgJxyYUUiuacCpgqSZQ7z1goVnQI9wCd+UJP9p8ws7h0APCcts6APaGTw0TALl1hNXwFnAGcpeMNn/F8tKBuue6NxVPpp42JDmOChJLjnfBZTZtW29WQikjS33cAnIzo7VHIbMY8YC3gtdQ85XHOarK2Apq0IsemaCriwOs9Z9F1JFG59VhOAX4SFd8D0q06XzDK5cO5yp7lF7Ap6+a9s+rc0yoy9NRtv/CD6Eh9wYLKyrJVeWTMI5NiYferTZw4K8q1pK2RDeCHbZm5c33VnL55mLp/VPts5NW6bMtuuqa/UsgWN9u55O2fPiVSzy5fna/uBkN1wSz9a3bKlCe2ex7+BupG1MdqO4l5AZD2VHxa1Z+SBxTz8pQVjsB8zaULxzoZsgf6r3NbJuG24J1Q8R9eIfb01Kmn4JrswhejqO/Nn7Zo+L7jndD7cLaJV35+VBTwdiNEnT/cqT8xR32wfoeCvOtXh4pzccg3MN4uUB43/Dbt/jNi4401rcRjr/ZAqO+NXo3znxeeiotmJXZoT/rJTn0inp+ibXmeshQrpWXHjglqDKbBze8Djg6548a71r2LHgtPHZWXqAsbLvMhFopiPZCuSIQi3BJYg9uWH3OcOyxvkRUs6E/ENN7HetbuRHLKeflo3tY+vcwbHaBJVzLWKoI7aRT48zrdTfKSQLwUqtWbcbd35AwxCTIj+d24tguL/n7kBS9g+aELfzMrAQBqMLE0R+3LW2g9lz9kDSngvxPWuzVBF+FoiOoMwRkh9HQvmK1LY9rtNNI07ueA1F2s5y3qGvfxAZZIpE5xkXtPy/89k4V7n4WfKQ1LEU60ohU8/PXhU3kOJDMuLQkVQGBOP7USGUufp+GJzWK3Zdu0EYG16UXVC4DLXnqmueXHaK62KBNXY1BJk9rJD9en64ydbVA8Rw0fdDGWzIFiAZK0As0Mt76ZXO2MBPR8gcNvPxwNMGDsoA5LalRpzI/C3K2YpzGmP6pUIcyPxYzqisC2H+FRYZNxMcW1QS6q4/YfDfYfQRTxx7XbXZ+3BX4pPgscdBw5P5GalVV9nj4pWYjOse4+9mwdvpF1g4x2MZ1Mips7c+wXbD8pQFz2PEfYIn2aOtDz1pGpdYqXgIAMkIzL6rCiTKqU0Tt1oy02L8RXFmvvLVa9/hWpWkBl7vzxTeyc8srWLzavV46at54VIqiz8kyo/lLYr8o05n3E6Ai7W4KCwGMEIpQHXTi1b8WHlLv9xMjntPpClC+TDH/WWvrbq/YZppOd2yDQCd9N6BwW89JZiFtW95es9slbR/YNpVPnCNIuh1TzozgKHS2/1a5hCTpn7e9OBUu7UF3DkrnLMlfNCGAVy/aDFYMOP61YXSFWi0X4JvDUJ4aUko1C6vmQRs9D1NrjIiMx74rwlh9+uuBpDEpuL0Vg5ut+D82rxPgrWFBvrSGAuZ4aKe9SIfw38PGQchEfNzB5gQPXetILG5UUtfsov6c64Jsz5GbmrVhn+PRdjv4xH4AfEWV4XUoXXgMl+6OyrYedA8A+zBRYeS+oN7HwNBNzegbD32IRb2q7lwmJAPlnqvpPu0ekKdZ1EXTtTtxjAi+1mazMUv9srRBkTxuYVR4DuiKlsqitYsqnyC8KW1lxVklybES3cMkq+olFuEAIBicZY10AOtuA1KV/wUuDxFPBfUKftPWjFqziJUlZLlUfG/R6UOMsh+sqcaDBqk4gQ4/BZwrLo0tPXs3jvU3wlOH4hsurrBPIA9irpeY2N6QgymMIg0D+2Jr9/ckeCnfQnJVFb1WWaHHKuPoIpXjmXFqt/ufrkhXlSKC/WsaPucArZNctqbkFU6+0KFWVQBQ6d7mDTof0qn4y8GOO5zbTJGI+ClhYtWQSPU24cXUwqJdLBDxopR7b/rAUZlJ7JMK8SX5wosW7S0zAc0wP0EPz4ICXBlBXk4hmVP/qM879tB/ze4SyiYeyiJ7tv+QmieMV7LBEtqGhVYV3bokuz5yxIJhlYo6gmhQft+0jbUMoIjzHfuazNI59YVNx48PbPI2Un3DklksiM9eTNPR+xnoXtUm3TnWAM2JIuOQnDTozBjElp3uiKY0uTiCK5EbpohSO8q5AylCXe3bIwOfbsYTYkz7wG/GHE0Yb6p+iIfcHoDfEPhhtEqpiaobGwvjJlRWNGwaKxIgY7ZNw7YTOwlAHJ4uALDybaMkLChoKhkyqal9zjkU+XpRpz2Nlcii2hfpE89iiIlMFb+hffs4+XPvKKxttt40RqYwdgEgRCc2oFhYUIsDkXkcA2hMpIbGBscjW7LodKVBOwMiQC2wBp+MguFC2bebUKcs2LYkphBWmYBGHEO1WjfL36PJ5zUVhUoSWSR57e06krW/nfMVPTmal0ptOHrNMPzwBcUdYphtU2kXPBlhbjPntjpZAUNSVy4E8i2A6/Rgym7+X/wgVEqMI0ePOS39yd5kaJWN+jJuq+znSesD/LYNn+2++lQW6XoEx8Vrb2HEcWI3P7opZYIiswGgIxXf5BS0ik69vYuKOtru5vRovHD6gpbGikA0Apw3HwzOXwFVBcVZyTWxVUtrR1NskXgt4MKcxTr1XOzbpzBN68eoMKxMLxuf/M0WrRSis+Pr8dAI1NfHd8rBnaW9OssIPnJ0s3Mk7ucnMsx27Jw6lfErmmQDn0RcenLfH40oAAdAs9Hk7u6usyLO+skfpVFsmeA7+OdlvX/SaFJchLDkcU5Z7mEYF67ipabjPlro6meB9JAjKS3Fc1miB9uKzQZXKNlvKZ+d1+UPq5jf/d++V4EPqQc7Llyz2Z6H7io5AH0Nn9doTg2uomzqK0pySt5YSyE9qnUd0fb/nBU1i6DX2C+cfgMNSEdsSa2J4YZR6JqTcQz1BSfrycPgmuKXp5k6yNtuJ0pYBFtpZ6y4m9fXqJFeO1HjOG3oPwPSEhLGKRL+zkZRzswgO9mow+hqHimR78UpAR2v+ubuue3sriq05NKxj4Rdacm2Otypjt6IPMkbx2TlASxfvPka6zhPG/3c2HmVhpbIH/GCt7znpJwJuun+1npmIRE9Js2+dA4Oz6t+jOgeTbRMRmUGlGyCe93Crmb5wrVh0BcOW2U1DUv4bDVeJ0EtVBJQ05GtPUBGyLZp/OQyubzwAX10DNuC6DD2nYpg2PU42vDM0WgCeozsd7iz1Iy/dA0FTSyVvJowvF0jWScEdZI/tnXN4mYcQ8yYF9uELL
*/