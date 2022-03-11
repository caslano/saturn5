/*
 *          Copyright Andrey Semashev 2007 - 2015.
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 */
/*!
 * \file   date_time_types.hpp
 * \author Andrey Semashev
 * \date   13.03.2008
 *
 * The header contains definition of date and time-related types supported by the library by default.
 */

#ifndef BOOST_LOG_DATE_TIME_TYPES_HPP_INCLUDED_
#define BOOST_LOG_DATE_TIME_TYPES_HPP_INCLUDED_

#include <ctime>
#include <boost/mpl/vector.hpp>
#include <boost/preprocessor/seq/enum.hpp>
#include <boost/date_time/gregorian/gregorian_types.hpp>
#include <boost/date_time/local_time/local_time_types.hpp>
#include <boost/date_time/posix_time/posix_time_types.hpp>
#include <boost/log/detail/config.hpp>
#include <boost/log/detail/header.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace boost {

BOOST_LOG_OPEN_NAMESPACE

//! Boost.Preprocessor sequence of the standard C date/time types
#define BOOST_LOG_NATIVE_DATE_TIME_TYPES()\
    (std::time_t)(std::tm)

//! Boost.Preprocessor sequence of the standard C date types
#define BOOST_LOG_NATIVE_DATE_TYPES()\
    BOOST_LOG_NATIVE_DATE_TIME_TYPES()

//! Boost.Preprocessor sequence of the Boost date/time types
#define BOOST_LOG_BOOST_DATE_TIME_TYPES()\
    (boost::posix_time::ptime)(boost::local_time::local_date_time)

//! Boost.Preprocessor sequence of date/time types
#define BOOST_LOG_DATE_TIME_TYPES()\
    BOOST_LOG_NATIVE_DATE_TIME_TYPES()BOOST_LOG_BOOST_DATE_TIME_TYPES()\

//! Boost.Preprocessor sequence of the Boost date types
#define BOOST_LOG_BOOST_DATE_TYPES()\
    BOOST_LOG_BOOST_DATE_TIME_TYPES()(boost::gregorian::date)

//! Boost.Preprocessor sequence of date types
#define BOOST_LOG_DATE_TYPES()\
    BOOST_LOG_NATIVE_DATE_TYPES()BOOST_LOG_BOOST_DATE_TYPES()


//! Boost.Preprocessor sequence of the standard time duration types
#define BOOST_LOG_NATIVE_TIME_DURATION_TYPES()\
    (double)  /* result of difftime() */

//! Boost.Preprocessor sequence of the Boost time duration types
#define BOOST_LOG_BOOST_TIME_DURATION_TYPES()\
    (boost::posix_time::time_duration)(boost::gregorian::date_duration)

//! Boost.Preprocessor sequence of time duration types
#define BOOST_LOG_TIME_DURATION_TYPES()\
    BOOST_LOG_NATIVE_TIME_DURATION_TYPES()BOOST_LOG_BOOST_TIME_DURATION_TYPES()


//! Boost.Preprocessor sequence of the Boost time period types
#define BOOST_LOG_BOOST_TIME_PERIOD_TYPES()\
    (boost::posix_time::time_period)(boost::local_time::local_time_period)(boost::gregorian::date_period)

//! Boost.Preprocessor sequence of time period types
#define BOOST_LOG_TIME_PERIOD_TYPES()\
    BOOST_LOG_BOOST_TIME_PERIOD_TYPES()


/*!
 * An MPL-sequence of natively supported date and time types of attributes
 */
typedef mpl::vector<
    BOOST_PP_SEQ_ENUM(BOOST_LOG_NATIVE_DATE_TIME_TYPES())
> native_date_time_types;

/*!
 * An MPL-sequence of Boost date and time types of attributes
 */
typedef mpl::vector<
    BOOST_PP_SEQ_ENUM(BOOST_LOG_BOOST_DATE_TIME_TYPES())
> boost_date_time_types;

/*!
 * An MPL-sequence with the complete list of the supported date and time types
 */
typedef mpl::vector<
    BOOST_PP_SEQ_ENUM(BOOST_LOG_DATE_TIME_TYPES())
> date_time_types;

/*!
 * An MPL-sequence of natively supported date types of attributes
 */
typedef native_date_time_types native_date_types;

/*!
 * An MPL-sequence of Boost date types of attributes
 */
typedef mpl::vector<
    BOOST_PP_SEQ_ENUM(BOOST_LOG_BOOST_DATE_TYPES())
> boost_date_types;

/*!
 * An MPL-sequence with the complete list of the supported date types
 */
typedef mpl::vector<
    BOOST_PP_SEQ_ENUM(BOOST_LOG_DATE_TYPES())
> date_types;

/*!
 * An MPL-sequence of natively supported time types
 */
typedef native_date_time_types native_time_types;

//! An MPL-sequence of Boost time types
typedef boost_date_time_types boost_time_types;

/*!
 * An MPL-sequence with the complete list of the supported time types
 */
typedef date_time_types time_types;

/*!
 * An MPL-sequence of natively supported time duration types of attributes
 */
typedef mpl::vector<
    BOOST_PP_SEQ_ENUM(BOOST_LOG_NATIVE_TIME_DURATION_TYPES())
> native_time_duration_types;

/*!
 * An MPL-sequence of Boost time duration types of attributes
 */
typedef mpl::vector<
    BOOST_PP_SEQ_ENUM(BOOST_LOG_BOOST_TIME_DURATION_TYPES())
> boost_time_duration_types;

/*!
 * An MPL-sequence with the complete list of the supported time duration types
 */
typedef mpl::vector<
    BOOST_PP_SEQ_ENUM(BOOST_LOG_TIME_DURATION_TYPES())
> time_duration_types;

/*!
 * An MPL-sequence of Boost time duration types of attributes
 */
typedef mpl::vector<
    BOOST_PP_SEQ_ENUM(BOOST_LOG_BOOST_TIME_PERIOD_TYPES())
> boost_time_period_types;

/*!
 * An MPL-sequence with the complete list of the supported time period types
 */
typedef boost_time_period_types time_period_types;

BOOST_LOG_CLOSE_NAMESPACE // namespace log

} // namespace boost

#include <boost/log/detail/footer.hpp>

#endif // BOOST_LOG_DATE_TIME_TYPES_HPP_INCLUDED_

/* date_time_types.hpp
9TAjOr54ZKC8sLI7kqCUsBUo8nVdF0ayC7HqYPYg2XYfC8Q7D5ioz4AC0NMxOT9V9d1Y7idEWLcUUWHohRqgYZp1JcmKNgZkOE/i5P/64bs1KLq2Ld95wC/dbAK9nDofevXzjugoArXGqBAjIXKNEwcQDDnF0g+uvWO9F7S5mLnfnzP70xJTsvIkPYH433sztgjvViE6Hhk3g/XxH2P5fFa7Awgg93wPO41kT/Q4kJKS/BnsTOgZk5Wcntdsf8AI4A2BZbd5TI0HTkcldJ5m9VojaLqjbkgw+h7Kh0wdTh9SrE8z7w/4mXfYtIhOaLvT/C7pt8QNGUoi+9t8sBVMaj44co8aPdsqhN0ry5zXkmiN+o33/H0ehdXaHCEYWrCf7SPc0gQF5Hxg2ciqwis1ftU7zbrVXaHNpuKAIAYewk/qFpatludR2uYDFLTtvE+U0FxLsAzqmduSlYgWs/+NTcsjNAlVh7EJPCIMNykALt3/YGUqo5jXH5QQeQiBG3rRqI/f4qJ9lSis3VwteSz9/uypihGgB4a81zPHGy+jB9s34c9hla7DMRZDVqCb8C7AKxMa2Lx724wdMh/cTVfA3jtYhLpT+wctyr+bEI8Fj8+/HsbKUQwNomjnYVnsV6AcbttCAyCxsqvz8gWYhm0LnxNhGMW+6jT7hMLt2gLKsn6RkFQlUSoqLi4I3fV2V3VnwwxZfZ6M9sDQals0Fe4fyRo3DCiTG39Gf7Otn0pc7VkxGgJ+H6PfG8W021DxgZ4Qm2p/Je3D98xsjmzrC75kou8n0Lb+GXKTJ40Hh6lQCL+YUgNsLl5a9a8PA4yQw9WHLDL1VWUF/hKP0oYi3f0yzFvO5NMQLJbe9f92aQ08Hk6qx8i0DsEHF6GaeGkEkvef6n9mGBwSdMUe0GdKqHr7Yb00bi4tQDk3x4q3j/v223hJZOPv5dmP+llfCJA01B1SbenjbWma71plSeff2VsK/9OITpjwL4AE5ehDWeBaHwSwKFWJId8xsPzlLGYNlmPLr7+8D81yAEhry9bNEYT5Kl7PG6jK/PNEc+61Z9ESrcQLa65Kjtoyuo6BmTg/AnRb3UvjRZa/ykM0RWCV2AQXXxEml6LtvoisNQOSXV97JMtm8OTF9KBg5RMLUIjOaIE9ui/sU8N9GNZQeG9pOCZelTP7L2p/j21jHUpEhS3SXXuLTLU08eUdPhumJaOM+zmB/Y/9KBmM/v/r86uRFGtIUMKsJXgonotQadbRMA4QqpYYE6elJRsDQg6owNIjYYI1N9COuSdKDV4EObS+urEmvCjINPYdQwdlKGYdYh8/FaMPJ4/AT+Z5clptVBpdsbb8l27//iVoap5ZRExU90H+uq0BCf8+vw81zKMtWlXDHyM6cGV8f5WPg4JsH5VEEczObF1To6u07FoyCPsIeSLfsM9fYcIJzmobo2G6t1pspVHYZRNIhDEvq4t4J/D3qk37et+movo9lIXvH/L55ev6C1h5SD/wx45sUOZVFSPhCQzHGF4bDO0fFKGPd5vP2JpuQ6Yd8nz0FFjSKsVqzV1RBM9N/kR/2A4vCv0XrvCC5zVCKytUlMP81GkCb3X+szjOgcuT7/3FGrbyjRGzNN1gXCyCzYzLjHddOtyNBSM7v9ZAAs3qGhwvp9Fs5wH0fVOY/XalHaT1WpMNLHcUZ5Pe1KYpmpFW++swWvTe7ak4LxuQge4aurcMKG9ymv8E5KX1AcDd8IVqYIq7uir27rg2+aH8IIMXDFqAR3fHjv29hivoJzO2s+tE2eiIXGpn31bVLyA5+e2esCtq0X3ZERGWiVJcytuEkbuuQNl2FqxC/bUCBZAXvJ8pOnjIyjg2YUeErse1r7ipPBi/5pJ6CCLfvfjudqYpVhMkiuYheDZsBKBe6kS4XjEo+c/GPL1Fzt60hBjp5S4yvqMHRdNG66h6HwFPFTvhDLNYbNw9ooze73JqdzsH8Q5++uMaHOC8/2QPtk8qEhUCfZTRtWytwiC4hLfIgBrw1+fRa/vGnyyKNOaZKx5omk1BVtg5IFOxgBhI72VVB6YERn7pSh6yp1wkl0odPnfkdhahVAcz3Hty7uZtyPJe5+jAhGPG40JRKPSqCIdm1N+3wVWCvh9gUvuoxqUSnh80Z7b/ub4kBC6yOSIil12F3vY1qW5gebNjqXhzOfCN/hthElaMMhxb1DJQLGEAigadE/m9Lh6NrF0fyJvd3IodIrS8WNzv5R62T7WuEALA/9Q3kKe4/qWOLTsjp26aWdz7Fga8UAkbxs6P8In+4mPNAw3tTyM3TF4RZYTfp1IEw5gh7hgV+ZDHqWFfMgn26NDgULZat3lv1IgY4NEYS3rHv82hKtGAOBlF1pnSDE5I6AabXm3+YtqhquqpJCIPYFCHNX6QaxHszhkAfgkyIlczYsiPJI22uC4fJ6bzEhl7LcJQkmLDEykgHUXvpRh+1iaDKGEEgczi1ZAOuoSCbYvwz12FQqPPwxTL0Bh99Yu4L0A3+zrxt1Zd1HZQsfiTNyZ4tkslNH01IsCGj/J//yS936zvJznRMwDY9j2p9mFJAeNZVCwnirq7MNzwYyKd1+pCSeOE+z/K6TnCchJgEW3tv48UxMulK/ifk25cLHKHunSWFDxVbV3VjfGP/aMgwiTXFqO4Tao3xV3sr0N0v2834K/AHpXt/vgahXbSFsSmGe3pNu6ZP8D4SewPE/fv8at7GEsn8n92Ypjk5tGX4UMBK4HLhHalosZGgFnEQY0AjNdPyuDqODhlJSlBjHsKa8jb54i8euO0Aj05hCZT1Ud5a6BXf2uIhAB1/u3rw+nYA3wngAQ3vJy9Np1UqFghQh/JhcKVGSBocxB7NiyhIPZtPdSheBNMOcfJOyLK1mxAmLayv0fvCGAe0S6HptIA9QhZqe6PypNl0axC3j3o/ETJGBiDR9heDMAwj7iR/1YC7OmTsRQ6B3hmdErd7N7HZT2/cypMIhVRy9n/76efvJj4sq8RvF+sxCiqaFq62v2a5P4+3migv6DEdpwWSjbuxj2Tp/L2U5D+SbRNvK7elr431WDyeEcGWK32mIfobka/afQkYQ2DvMa1g0jPihnrqvRRboZ3hCciApoP9AmIYVki+kXuhE9WdYN9W/o8fbDfdSiuAEKXWU4mIg8xwF6BqpYT7CgnZQk4MSg6NQ93IhIc4ibm0yjt8k3QUZzjsaEZTPFN/N4ooxDcE7UQBX0urlb46HzmutE71M6n1IdkLQXScUl2uFrklO7Q1B/43IA5v/0bsoCZipoIP2TEiO+uafp1WLsBOLX5Pp/LWSCS7a5V5Zdbd9t4KoGwyOMhN6bMosT5DzkyoxM1+6O4Rggt0btx+xY1PPhpGT2phjVjsEE79mx4AjkaUYnYc8GICiOD5vPEbDJfFMfGVH0Na6tuPXFvkCsy2A7OsA0iivz9qkneRf+rhhRW13dkBAp3/X9pulrA796/RsgcgJsNoBiX+oJgGcauBUCPAVvEWNuj6w/j9y6U96LhsUpphSPQ6CVhgmzHF2hHm42bAhUlCXY75e/EMuMCVjVoBZPFzT5A1KY8dewHZLA4bANHjQcCOa9fbablO8y8USUyLPrLC9xY52T7yRy3pfCkYh11zxsfgmfR7GkH03BZaKee+w5yt4wmKf6wu7tm2T5c4TS6kl5a5q1JQDFkno78Du2TkcejPWb/SpYMd42H9sSByGDEXRR2s0T/rUJBLX6xVWwYV4X0J+3Gk0Nj4AMDjbaoKsg6sB3DldgPnZI2qcpJZoUBWmooEq6/5FEuYWhfd2iZtl9i79N8jOlkH6G1guwFTVNnwe38i+1YPS6UD2sX1Jr9TUz5TYgN9LBfLdRk/pPImygn/WGPscINvcfgor+L0UntBBXaMeRR2KZzeqKivRRX7BzYRhW7d3P1hlY0hKHl8BKv3/CAWSPPbNLiu6/Tgx6bjkbDogAx9AEPsLdgc/n5UbZlkkttUk8OSFDRu9XJ4xCXplk2ADRa/9VCIRZdrpAko3/0nseZ/eIEWtwr0UByPAEi8Bk/vL1p+LpYu1Tb20IK4SOwa/6088VspFyCe8F1WswwXtz+xvN2gs+7CUZ0jzMtwWPMMIkGj6mkXrj9iTGaXjC950O7tlAZ/xcJB8hk6QYe8rX9bUUMY24Dx+waoviNz+3axpR3jYfywvED5LZRG2t2zB7O1dBA1oHq/CUyNOHdAt4Fah90jIIaCSCVHRhwsffokYULwpTyN5Xs4ixLUOCsnSYcuTur1O1StgdoCq9vZcdbjaBFbB/hz9olPqoKLLJOe0iP+UUy5zgXwBQciE2rNj8t8qN1lzDnNl1LBFfWIzR9f0izk5VWuwfJHhbmg+ksln0naM2CS6+gNBhMmoKaatM0Bj+LltwVvbHPd7srOcP9/c5+/cCn+p9CjaNRV5HCOiNuCH5FykUToDn+LvHofx8ah+MxxVJGh1qCXaF9PinGfhx/1y0OBLh/i6XXTDko6TXKpSKoHdkfJVnH2HdZC1VnGbtTl6WsioQInjXQuUKD+/63m7kAFBAQAAAAAAMAABMAACoAqqqPo6hBTG3f8KqGhqpmow3VMVSD3k0NUE2q2qqpZphqNmOqjBgN0ZhRAAAMAL0DN+lxe5qhDNBABZFuUKmiG0Q3jVRFpIlEO1ADFYixtQ8+UADUmL8/gIiUApUnKiCxlAmUSYJJ9gA90QMVEZUjSiPp7YKiB+72imZrawAIAAAMAA3QzABOPtroBg4PNnQ0mMXBLBZXt7AS6cBS7RgcNUbWiV+JpkcUSOHIxWOgTgo+arkJAj61rzmXB3rFxLhA5nFxL6QxQV2FdF9S05wIQ1Q87yKsAE3T/kRsnm5Yq2smgXF9b2IAz0f5BZq+G9pKkc0UN9mGwgsIPD0ykRWsLrV+hZ2kOTqnzMIOpOnwPvlZzJX/kv0lmk7gnLDDl1Hd4BDog1ZAZRfnBZckNzjiqr+2szqe+bQnuBba0Ju+xlhFn4acWqwnFsudRy4S2lYdBjPkkj9YRs/VCLkOO2CpUTC7R7fT6WDIy/+fsyw8hCDmz7XTqw3rFF+AVtw1gZHNB0wFijZQuTmd/DAaryriALPgTBkTS+mVmI4H33uPGVA+t7Q1Q2tmc6llgC8DM6E/GAfkFrwT4i8EklEUbUIMbff7/vj06LEJXIujAt05Yvi48fgVVE2cjdBifZyLxZ7ZIAAav3CfaATp0hdoLCCsYoc6ceGaH1Qi368XnPTowBGOscGN+eO9wJVvieXm24qfM7fdNiGJ9VLAIsjB+KiS8q/240unMVpaVeQC3DHWMBcWlXmskc8PAcM0x3fGocmXyM7lg7zGskceU58+IJOmkn6lnhFVKv0Qau+gP1q7odasVg+/HNmzhmc5ASqgONUj54m9sgJDaH3c426fi9UDZZ5bnOlMfyThy1oC4z2cXZjb8OBdT8V7OuPAeaseDKmqbviLE8kPjd/ygrkNdthdRncIQ9xdAfRtHWGpHkOmCiriMRPiUKTfz+70UZbcodZu/QoSReGWaSAIYqQ68Rf9vW+Es24wva1HRfRXmjKM8F2NzW+i7zDCfGpXHSIQ/qmr0DmmSKxvS7vJ/wr4+DwXxtjS1b1xQvkwdWWjZsp4JYnWHp3y/U9sLWnCGhuyNuoGdf6aXUpDVvoHC6/WtjeorETkqVcAUBdCYMrKLqzZInbgwUOIpAMWUA4CmIh+X0mB2ezH43OgVBY9ot49+C2YD4HFbkymjUDtUq140x3CzgQV9Hc5fJwIRFXfm9+T8+h7Y6untw+KA+lOwyN7+tfk7T31a9/zOUmzz+MbybhyNX1V5TWatERS/2x1FPsSiMzbZLcxmUWYFKL/feHJVycT29jvTPTW9bxzMdLKFijG3x7XwpweTqGBWUw0/LpoeorvJpZ3eJPrsX1MeDf3dhROLco4m1DJmCDUzhsQ3AV5RefKn3XZJPJYCVg8xo7kFydNCWlEAsKriUdSkrDyX3sMPrw4j3NJEtOJhoXX9amTClYHDy2yUjDQoKHyvKfxT50S8WeN8rcwVoVW1YTjGvv/ltU7ubUlLojuUr00+zPps5sV9SHMFH+JPSLmM91mzmAvLV5V6OpnX0a1khYKonJigdc2trSWdEA9cLmAldc4vSdfv8PhdUaGf7mbtd9ItzlXgYznlYAUWvAZmydbrKmLWNSLQWnPlEUniJdArQv1nkgV86MxVW1BY079v3IuyceE9zeL/SD6SZZ/iVsWIv0ULHiDNrCnPjD0GkKGNSBL4hL0TiitEV4NHs9TIP0/FkuYG8HbdkvMhPzSJZLi08gJ24c3Qrb23/Yr01Uk5sGYrkhJDfcgYa1rIte9PEEjlvg2MeRePCGgqRXFd9wNvmknVmsB4Iw9LzHeH67KXYn0YlBwyf0KHe6Cde0CI/sJfqB+NIebu0AB9t4lMX4K5q+TV1l85/aHtN/oJ9dJBVuaOY6J2cUy5zTIRbgaB8iRes8rzwsoZ3mym6PIBtZHg6nCSvoNB9IPgoqwN2W/FV2FoSD9WvaO2HcDgXYlZ4ImYMUSZX/5+/NN3OGVPhOTiN1LyrhHetxWJHhcx87j4xPHiIpVVX5/Kv4GVbbXAycJePlWMFkXnYDWvGwU2cTI2e2t2uY/e/dOLJlPO1wUWyV1fpe+60/8bCT/VjDFsIC7vfDjXww0YB5q47zmYhjQzy+I4tqE9pGo9tVg0xbUUkA3qf9g21Yyvy3ec7ZOOSHDvnQzVmWWbDdr7w9v4q7J/screH1j+zUGmp0uGPkU2q9xsR36h96CgSxNVFg/WvYy1fpz3I8op+ZWGmXzED97pM/+JX6e8CNjoPcOlEN6mBSDnnNs2B200RRC2DKRLBcaLO+kD7Mr7gfoFxIJdzUvzT0oGVCaJST2/Kz6D3Qs74EB+r9d9eGXBVOR3opYWwFfbk+Q+gNxagx4Iednj7KSDrtljZ8CyyL10OWdj/A+H6tscTnhyeu8k7VcKI9zJw8botLQgimCQp62AMjksMWCl2xFBDoiNXHTvNTeHhIMmrVGMsfR6lXNiLAxTC+ctbhs8AMbxS996PAsJXspadE6DHKYA2+0QXKoDxMlMJRzBF64OxaRP83/BftG21osj6WZK9PWTAr+W1GKFyz4g57geKrypN4djz045/BpZv5EwHcZQKkrUCQRsQgrHMuyL9r+aQlfo1XmLgKAGFPbN+et7y34cMBANgY+8nZJoSGE4CmZs1FRC3hGacfAJ03QdcVkd+HImo8YAwXxhCmelnCSdUIp3Uuc6ShptPqw6jtEeuQr0CJOBWcKr477i92ToGnkIPMzFKp+/q+L2lVUjvOtM3R3Iq6I5J7NR7yjE3Z9yaARCkgJEFhNQdCw6aaYrA1/fcUqA48YJE2E+C89exg+lEtwjdO2KANLRJ9MbwaZIyQAL7LkovoRMWcqhamUPZTegoSHOscaAmtE/1z82JoSsBn/Y/rXGa5hpAVtx0OCNG0JMy3r1+g4hpApnO1ScPRxwwykEs5Z+B+L42QCoXw2ShOTTN8Y3wn82CJwCVRF0RfpBIIDwObneDrifLCz9ospHCLknFHfl+XoPSHigIY2ayaP0VAu6YwvvcZOLgI73io42EP1cyqFrmuNERUvkiBAR25YJkfcQUDI1eAtw7BV77GH+aa1dVP9xY0r+j2P0yl39xr1BvtwQ0ms77NAicQDGZwIqNnypaH4ksH8e+EQQ6DE+BSC2MD2E3ccH3i4QOGOLNuq3/rSD4F7VpY6BV9FMDr8YlcnbUerkz56HNjDcuqqX9mO/xUP6AxhxlRuQ0dVB+5GT88Xu2tKcvPFurmaFi9AlDK7kOzfoNP29RP1pBGPGqdmNxyy1+bE2UjOcFDA2G5LHDQpFrg7BMjXlqBQDJCY9mBBxA6p6G9lJprxVkSLtTnbU6pVizg5ucsQ+UkyaLEnSB6vVHWWTc0BQCioga92T7iYHcHwGzwa8fiL7nKE+iaTZxCMOuycTTJyMkHy1vsWjrzpQtb9Qk9wVr0QcbenoqemKWvDlMg7jV1UQ8IRZvpWAujPJUcfhBcnXQHnRhWBXim+HdkSAJSm2loBhQLGzPMdm9+U21HeesdtP8WBf9KBNPqNBCXKe3eCXGs0EsXeDTKdN0GhIUskxDzSPW34C2lOGZeuHGszorb6YKEd/HcjhJijwIq0dkq0KM6Dd81w4CJbDhXDUnlYFhkQ/La677XyY+7OQAzP8bfQAu3fzi7seAdDA0isf5VX0d80eRPFP3sV2v+d4GElQWXpQvw7KHUTRLHDYbeFwc8nP0V4FEqqi93HF16eRL0Zf/PtXGadG9cvJlM0UTxOJaI5xrzfSTczv9cGhqqRrBq2U2nLj1U4putDlIjRemYKGnVOSKe7k+yvJ6ptN+AO7RSljgLUtt3xCGjKQ/C6qeopQcfLTum8MLyMSeDRqdDnhRiuh1TVCyzSuuxrMCHB0oRAsTaueM0AACz/04IeZk5lnxQtx9aMllMTEr1mAir/Lmq9iI0yfW0gniPugpmiOluEGdzpmFzNiOUVvsl2CKw7ftoljAp7UXvoxLPfg30muGlklMs9jw72C+/I3TEZASd0+W+1ddJ9IcAmiahgyEjvTRdlLhDflSaIyNcRNCNpQzhgqsjzE9GnR6AF7L07sqCX+MfqOx0zFpdaFhoMUaaAP1FISqfNVlkt9+JkoAQEyEgcVWo/b+09iq+oLLAAZPiWnu+RT1UNOBWInbT9F1xqtWpj2PZd4LpLzvOlGid/5g+o6IZ0frwr18BNwDxaaGScijfujoAgttMnJpfQog8WBxCZVkna9HOXQr9YSNxyzT4p7mDAfeOEyItAuM0OE18xkVTbj9WxeZdWHCarLADU/Dee5IfFFsecEbyUSqLE9TTnTvWlEmhKoN2F6l99QkED/ZcsI0LgI0vppOUPGN6aDKML+uYUVAUICQnIlqsrtl3JlfEtdnn3MdUnthNdzLg4zzwfenl0I8bMLyZWgn2D0IqQPiCStnMaY95gGKqVSu19SOp19Nh+ItQDaHLIpC7vM7YLv3t7uf1LeHBmIIiA1ZbMQpe3608qBZQa3it98q8mSPpC/5mGYRU3sC9KxWu6Vh4icgHfTDSE7pbhw1V72/q75ckYgFIzVH4opgEN7PQCm24gkIzgPCY=
*/