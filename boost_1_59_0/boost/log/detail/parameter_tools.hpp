/*
 *          Copyright Andrey Semashev 2007 - 2015.
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 */
/*!
 * \file   parameter_tools.hpp
 * \author Andrey Semashev
 * \date   28.06.2009
 *
 * \brief  This header is the Boost.Log library implementation, see the library documentation
 *         at http://www.boost.org/doc/libs/release/libs/log/doc/html/index.html.
 */

#ifndef BOOST_LOG_DETAIL_PARAMETER_TOOLS_HPP_INCLUDED_
#define BOOST_LOG_DETAIL_PARAMETER_TOOLS_HPP_INCLUDED_

#include <boost/mpl/or.hpp>
#include <boost/core/enable_if.hpp>
#include <boost/parameter/keyword.hpp>
#include <boost/type_traits/is_base_of.hpp>
#include <boost/preprocessor/control/if.hpp>
#include <boost/preprocessor/comparison/equal.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/preprocessor/repetition/enum_binary_params.hpp>
#include <boost/preprocessor/repetition/repeat_from_to.hpp>
#include <boost/preprocessor/facilities/intercept.hpp>
#include <boost/preprocessor/arithmetic/dec.hpp>
#include <boost/preprocessor/tuple/elem.hpp>
#include <boost/log/detail/config.hpp>
#include <boost/log/detail/sfinae_tools.hpp>
#include <boost/log/detail/header.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

#ifndef BOOST_LOG_MAX_PARAMETER_ARGS
//! The maximum number of named arguments that are accepted by constructors and functions
#define BOOST_LOG_MAX_PARAMETER_ARGS 16
#endif

// The macro applies the passed macro with the specified arguments BOOST_LOG_MAX_PARAMETER_ARGS times
#define BOOST_LOG_PARAMETRIZED_CONSTRUCTORS_GEN(macro, args)\
    public:\
        BOOST_PP_REPEAT_FROM_TO(1, BOOST_LOG_MAX_PARAMETER_ARGS, macro, args)

#define BOOST_LOG_CTOR_FORWARD_1(z, n, types)\
    template< typename T0 >\
    explicit BOOST_PP_TUPLE_ELEM(2, 0, types)(T0 const& arg0, typename boost::log::aux::enable_if_named_parameters< T0, boost::log::aux::sfinae_dummy >::type = boost::log::aux::sfinae_dummy()) :\
        BOOST_PP_TUPLE_ELEM(2, 1, types)((BOOST_PP_ENUM_PARAMS_Z(z, n, arg))) {}

#define BOOST_LOG_CTOR_FORWARD_N(z, n, types)\
    template< BOOST_PP_ENUM_PARAMS_Z(z, n, typename T) >\
    explicit BOOST_PP_TUPLE_ELEM(2, 0, types)(BOOST_PP_ENUM_BINARY_PARAMS_Z(z, n, T, const& arg)) :\
        BOOST_PP_TUPLE_ELEM(2, 1, types)((BOOST_PP_ENUM_PARAMS_Z(z, n, arg))) {}

#define BOOST_LOG_CTOR_FORWARD(z, n, types)\
    BOOST_PP_IF(BOOST_PP_EQUAL(n, 1), BOOST_LOG_CTOR_FORWARD_1, BOOST_LOG_CTOR_FORWARD_N)(z, n, types)

// The macro expands to a number of templated constructors that aggregate their named arguments
// into an ArgumentsPack and pass it to the base class constructor.
#define BOOST_LOG_PARAMETRIZED_CONSTRUCTORS_FORWARD(class_type, base_type)\
    BOOST_LOG_PARAMETRIZED_CONSTRUCTORS_GEN(BOOST_LOG_CTOR_FORWARD, (class_type, base_type))

#define BOOST_LOG_CTOR_CALL_1(z, n, types)\
    template< typename T0 >\
    explicit BOOST_PP_TUPLE_ELEM(2, 0, types)(T0 const& arg0, typename boost::log::aux::enable_if_named_parameters< T0, boost::log::aux::sfinae_dummy >::type = boost::log::aux::sfinae_dummy())\
    { BOOST_PP_TUPLE_ELEM(2, 1, types)((BOOST_PP_ENUM_PARAMS_Z(z, n, arg))); }

#define BOOST_LOG_CTOR_CALL_N(z, n, types)\
    template< BOOST_PP_ENUM_PARAMS_Z(z, n, typename T) >\
    explicit BOOST_PP_TUPLE_ELEM(2, 0, types)(BOOST_PP_ENUM_BINARY_PARAMS_Z(z, n, T, const& arg))\
    { BOOST_PP_TUPLE_ELEM(2, 1, types)((BOOST_PP_ENUM_PARAMS_Z(z, n, arg))); }

#define BOOST_LOG_CTOR_CALL(z, n, types)\
    BOOST_PP_IF(BOOST_PP_EQUAL(n, 1), BOOST_LOG_CTOR_CALL_1, BOOST_LOG_CTOR_CALL_N)(z, n, types)

// The macro expands to a number of templated constructors that aggregate their named arguments
// into an ArgumentsPack and pass it to a function call.
#define BOOST_LOG_PARAMETRIZED_CONSTRUCTORS_CALL(class_type, fun)\
    BOOST_LOG_PARAMETRIZED_CONSTRUCTORS_GEN(BOOST_LOG_CTOR_CALL, (class_type, fun))

namespace boost {

BOOST_LOG_OPEN_NAMESPACE

namespace aux {

// Yeah, not too cute. The empty_arg_list class should really be public.
// https://svn.boost.org/trac/boost/ticket/7247
typedef boost::parameter::aux::empty_arg_list empty_arg_list;

#if !(defined(BOOST_NO_CXX11_VARIADIC_TEMPLATES) || defined(BOOST_LOG_NO_CXX11_ARG_PACKS_TO_NON_VARIADIC_ARGS_EXPANSION))

//! The metafunction generates argument pack
template< typename ArgT0, typename... ArgsT >
struct make_arg_list
{
    typedef boost::parameter::aux::arg_list< ArgT0, typename make_arg_list< ArgsT... >::type > type;
};

template< typename ArgT0 >
struct make_arg_list< ArgT0 >
{
    typedef boost::parameter::aux::arg_list< ArgT0 > type;
};

#else

//! The metafunction generates argument pack
template< typename ArgT0, BOOST_PP_ENUM_BINARY_PARAMS(BOOST_PP_DEC(BOOST_LOG_MAX_PARAMETER_ARGS), typename T, = void BOOST_PP_INTERCEPT) >
struct make_arg_list
{
    typedef boost::parameter::aux::arg_list< ArgT0, typename make_arg_list< BOOST_PP_ENUM_PARAMS(BOOST_PP_DEC(BOOST_LOG_MAX_PARAMETER_ARGS), T) >::type > type;
};

template< typename ArgT0 >
struct make_arg_list< ArgT0, BOOST_PP_ENUM_PARAMS(BOOST_PP_DEC(BOOST_LOG_MAX_PARAMETER_ARGS), void BOOST_PP_INTERCEPT) >
{
    typedef boost::parameter::aux::arg_list< ArgT0 > type;
};

#endif

#if !defined(BOOST_NO_CXX11_TEMPLATE_ALIASES)

template< typename T, typename R >
using enable_if_named_parameters = boost::enable_if_c< boost::mpl::or_< boost::is_base_of< boost::parameter::aux::tagged_argument_base, T >, boost::is_base_of< empty_arg_list, T > >::value, R >;

#else // !defined(BOOST_NO_CXX11_TEMPLATE_ALIASES)

template< typename T, typename R >
struct enable_if_named_parameters :
    public boost::enable_if_c< boost::mpl::or_< boost::is_base_of< boost::parameter::aux::tagged_argument_base, T >, boost::is_base_of< empty_arg_list, T > >::value, R >
{
};

#endif // !defined(BOOST_NO_CXX11_TEMPLATE_ALIASES)

} // namespace aux

BOOST_LOG_CLOSE_NAMESPACE // namespace log

} // namespace boost

#include <boost/log/detail/footer.hpp>

#endif // BOOST_LOG_DETAIL_PARAMETER_TOOLS_HPP_INCLUDED_

/* parameter_tools.hpp
f9VrJ2XcBEsoRloIltGDuMEfCXcpBudZBvDCZslxx2O31W/fqMvqE/XB9pmzqUSetDgM7z8lIk00zgySTdeWskoNSSVMZO7WAnx6A0Fw+4Z8hxLvXjgPxL8d1Ooxpos43Me6lDWWTdH2e0RORU91Ig+zJvoXvq9FN5SfNadx8FXUKyfsrfH+5nQZk74p1bZTv2dh4Mo45SkiuXvFYw2hfxWSFE57kH2C/qpukcSlv5gv7HqM6Y/XN6VoALet4PJRHyMutWaUdE33YyEY8VHogn5jyus2XvnySV1J9tYliKXxBQTzRuPZVFs4oxtYxNVI/1Qlq89ODkwqorHZzegc3DoqsjeJ3KolLGY4Sok9kf23GXdC6x0j14T250B5f8pMNOV2rrnlVshQ7sptMpVbvpFjSsX94utsqqW/h5C33HwytYLqG4HjOx/OkFlA9LcwvqmfVvaIejGpST3GdOUeChMdMQg+KDiIhViCctGPWN24QnOtOnE4dCd/im24YvoKOx2GqhOEpAp2h34XY/7GqlexqHjDYFRbDJd3vpDbnzJFT2g8IGRUW/Gk969WnldQactvPNhML7YtlPP+gGEHtKFcBcrYIbkz4jFvoGP1mIu5Ips5/9ey7DmlgYurWGS5C2qELR+NeesnTpXBcaHzqcapRXJH+5uL7d9wLM10Wv7on1Mp/8O/V40t4hTC2uvm9BY7l4fhJ1buTwa8JbWNGx5DghepK3ZLkb2ZcVzeyuo+rChDH+ta13yU+egcjcreUdkmJYXWyQaUKc4cSQhMacxLxx8E38b2f04Wc8uHRU2quDNW+pj7XxkpmN6Hq0vQ2EXLTVarvM8JfRvHQEac6+EdksOL88wIa8DnY7UtxKdm1WycZDZixUdgncYwS/UvaZx8ZSV39mnl2Dp23+BY7sIZrpR3+ftKJ+/1V5sA55sG1xqOqQYi8xxWYXpYpTeclDuD8Rua+v31q3HmqUyxOv5ZzKt5pqEcN9NVdMnKvA/+XVSxYvsxc6X8ir81knuI/+JXssZ+f4/guOUYHs6YGWSW5V4ndp+eTjROWSfgPnXGf+tg6jcreSI+lWqv0FjP72PxUtq/fibnumV8XPfFv3vgx5v3emhu9r3NM36Je6JPL/iaxrkpUFU2/O7xiUEwiJaGK2VXS1LGE79JoDh+HmT5cXC+EYG/S+wWk1fkhlMZlcoqXGUE81HqoIAX5u2PmDLVseZL/XfVBkfsOK3ycobQ/51jeRIHhmPr2v2ZY7kCp55jK4MwNEPs6p6e9Ur1zM/aUIJA9AZ7ev2DUoEpCjo0wzQK+iPju67lRcZ3fMt/eIRR0BcZnmxm0P5UGojjrAHHyArugUWqCwxSrBHjn9rE2l5Q+P0GVapWcIuEkzMs+4WdocuorkQYTI5GJwn0katcayrO/s3n6ZsKc9lh/fI7M0n5JY8PIF3ks4HmZ1WOk9u3GaUlwHBbsHeo5ir1ZwWdXvM/vH5MWIyyxeMQd+vWOlWIdNyJmN9n4ZPWQIV8qnytDvK7GdJwGmirdg+5SGNvyZCAf91Ei0vmq8PCB3hubNPRq4OnDxdiuOLNGjgop+z59A2Sl3EbXeEmGY4RaIupCTc7lWo51R/qs1mPgMgWYFOj+p+FtdmQMGWmbLsRzWmKkauI7+NYCL7ox0RktOTQunUaOHEfuelyHpm4lv/4OlW9Owc9At9qDkeGGsvek3Zf9L6XWz6OE40zNSv+XpfjihyL/8G+vk+SxJOU1iyrqmj/19NB/7J1pMwNim7JZadaLNYkauKBar2deiwaR9trgY296rtx9I6wX8SwVvlhxLeT1fy2Dn7J3AWh1yTnajXr+cFg2AmTJ3cyKSOXbXCHLNXzbS3h5rYeXLfla0OAdO3YuSfrqai1Ss7ecjw6P35bizfjbEBuqZxVzq30vqp5HBJvNjFCQILTmFCdPxF9qwMR2hZiW8lhWOHoC8gZMaAtA+fUTTAFvq3M7CDOrGT2H2y8Sxaaw1InxiJqpj2QXclF1pvvFbjejDfvcoeA/MF1L16NM5aqlXcNE4i1RaLOpeP+BMaQkPsWwGaMIGdmf5Xv0wqXK2ycapfc964RGh53HzfHvCUVv4RoJKyY+0s2SHEyFWkgd1J1L8lNbTqs4HdgRVrc0tgFGmxxkM1I4jMilgtfT8DJwuMZeImmJ4T3F4uBaqybfuYORLIjSuf6oKX1OUILnFkMucY36DvJOiVL4WnpOElFORPeb5RfKbi1qkxHjOqX9WrvFNcFLxN3HqfzuRD76/CjdS77CHo+SeTOBrR0On3PgwFN3mX+ojQBq7EAECzv023pLs6/yb6gw2UoCWE8Ye+9zHnitDrPfndk5MneX1Yfo2T28KqMZan7u7H22f8L15URzPyBaKS3aAi7QGlEcIli64klz8g2xTN5RdAJa2NBZQoeZ9LYZUwMPLFfEXKU/kqlCjhRGJXhl5OSm7+Z0i8h1mJN3YyqD0jLq9zICVGRTkJzZKMvzRZZ3kOD10bjJoN5zVVyim1+9/0ykQ0cPLqdwGgn5NQ3vVowWhmjLhm4ao0KyFtn1v9X69XrOkZ+bq7G0OskvtlMJxeARvT5YUJoypmf65ATplQU6yFsG/mqkkUai/yjtR5JaIavgySBIIz5/l2kPVeGuq5fVTBfMG9npsHUYuRSrIwXTlmhnEqsK0K1CW16qC7zRPyHlGStlNcdGoNrOl4ExuC9ZRL3bweGhICCok/6rzDL6brhvrtUiGqoJYWcnN/VYpbtjpjVwkTkJhxVli4NG6imFiskd81rBB34/s8YfVAcYehWCv7XbbLQrJ0bd0dt9d7Ps3Nj+Mlaj65qLmqSETRyv2gkZVZbZQw3pYzEWRLZnd8Fp1yFIrH8AyiDK/I8WNcJsCj/6Prth8k2YGpkSpXJcijPwsW227+8xvNzN6kP2ZodxzekI8YwZIt5OIgLr/nKP3dteD1cIwzp3J3AcB7SlpnL7zbUa2/ACutNohM7kxeHag7qq5HXhJZL0GSRiDSVBOK1NKxUYdamnPPMaI+V0a8PZbtMMD2eKBD0twnC7Smvv4y79q8e4oSph/mtxuoxqr4wwbQhmWhEtl6aqYX/4NS/9aX8p6APJgYmJbKXiAnLeSJwqHdG4vlv+3UbDdFM1z/AIPVIOw6tPI1EnTjFGps9nDzpVlkY/05jIGLmvJxo1LaNNa7p003I+y1TR6hjG/QgOi5X2KEW7+pmJPTzScISdMdfcv2mKtk7M8F4mXvfUMu3KgeRumUDpbzhniDOORqXjcgc6Wv7Nxmmn+bKVW0W9SUELL6/mG0a+qpsqCLV7ubdPsLyUu92XTI5SQ8tnkJ0O54x34Usj93yT5t+BLiGY3Gf26HiF9lGXTNA1k7EU+Z8TCz7w+SVvf1tzbEiHjvRZIqpJs0R308ZRncb/DSHn0nV0Cit3u8vY6+Tbs0WVTeHeujElXVvXOJicNdCEi5N3NG5aO22I2MxAoq2k4qkrvdgb+KPxSTAzjElV3k6C09HdqARovp2ijb9Q09HH1d8wEdTxYmLGULcF8KkcZKqMIKkAPpNxoYeGol5YF27vnAyCT+c2yjrXuKHTDZ9g8Sf9bt1E/XpJ9PKwXucR4Gh97LBT/Jjj+CzZck98L2qM2ktlXcGmgDl3zcSiT8KbfXxdyotAqLwpvRB32Gtojz4FabWEWCHA1Z/8dyGjPlfS3oNVXgH5aAj7fZGnESGwdvzlIX0o0WH0NsZB/Rt7GupWCCynP3e7ntL+Ev1AwqyVUL8lXNoQGyXJLgt1wbTq2UoS/AUMcv+ytKm392kH8XrQG/hsiBaVrm+arB3vm6MxKXUTZYIg5YLHieSJQHrPsv4r/Y/VFH6PMba1GYaRNzHACQmLHofPU86EieNtolaHXZNmfUUCF/dx/DyBgq2KezpXziXNrdOfrC9K1znWQIYwpIgnKX6KRc5mmlTufCTfw+qiG4Sn97Thn4kabw5YFGSsPxndqyGn1I5Uhd/DsiU5dI7rgjbp5cbU6f93GnbL1Rpe6YtEodSbyntrwYF2A2WX4fntuKb2/tdXnHRB5LhXVuSS9DLqOx7//T4Xnzz5E9BTYlDeoCoeHuyGVy1YzOAVxNDRbhURFLArFtjm/VnW8i7x7pptBmpW5Apxemn/11TeRV68aGer7HnmaM3/+2v/7pQxBLMznYiWHG5WLFXVkRhTOwTiqya8UFw+4e557Q2ypA8r8Uj7NU6wUbigOJSRn1zcgoPQZBThfoal3y0yaujj3DYkkAMvMxkokcg0s0MmC8HCx8+MGSJR1m7F/NoCps5Uym6kT3snXb/gWbDzEv6Lxi2TbPUynBfY9H4Zh/v3JqleqZII2qv9ntwi6FquVCSr2lKz2yK/gpnqg5RSrsDCvqBPirK4HOt6fHDo4wOQckD2vjRe5e73nCKa9leJ3cFiqoMT+HMfaxKPKXF3oawp9FqjRgPlurUWESytSfqCCoEPBG/mt6BSs1fzRkvqM851iSVPg6jKvXnjk4hLk+YRtz9UrYfKhpcbi1UEf88mr/DHeH5tIyfWxtEzmbF0j1VYkgfYVyapc3hVrdISHeq+nSZaT0VU+0pon7JrOa11mCJdxCyl6xtNGDiYdPpf7/F6TOAxNXfNqELQu2DIeaELkdibXIlXsfdh63Ds6gQ4BjgkNamk4ZrR7hSDdufv8fu5dDdPSbH55ykgkd99R+qUvqcm0Pw3mLtSNYiwJGGnpf1lxtBuFr53XG0Dg2Ru6lvtmesI3yvS4dXaE+NbI1gvOaw372JWvSwIEgiGPgVu+T/uUuvarNJrsvl6XeL3Dgg7nYf5J8Y2K4ZvIV5cvjtzoblprD/VMMiedUG19AkhCPj2Es3c56GDsro31pzOhXurWegjddZgMIp1R1s8I4qm8sH+UP3DkmZxoRWFr5YRAwZVDk32ohqAwmL444YG7O1G0Vve1a5q7QfmTrcjcq4iFwQLZv8yRmzOCHbPHhjojCFoJNV+GE3pjwg/pRYqQCCv/l355paCnr8KV1aiK6ycJqiPKeC6TTCjMmmkNTdojY3+sxvvo9yMitK998Qzi15YLLdLbrQfyzvI1sLNi6b18xA8R7hJGgmTLNql2EVjgt2LMEU9naeFs8YIa7pexu6GF1vkc45VFjXLJ1kW5R0Zz+ZKVXzEq3dOaVcL8lia01GE2TX33jiQ7e6K2HX8dOGa1aD8eFaDgFzFKMEKZeZLpa7UJJSvrw/SMSbKgRpqJYMnW0uM0Na/BnYVvUC58u2pY9kqXuGJ+kO0ZR0tmn1hY9ZsJr59zkiCjJFjwtvM8fZc4wZNOPXVn+P8QXO9xd6YrN+iXuTNeRwModPjKSOycWMk0c1YOqPau8CMXz8e8Rv3LGG+XKQB2BYNQZQFPYVHXYNrReFm4QQdC7O6DhYjPrS/JAoHbOil0mTlJHM7xeUOtI32V9lu/Bz3oeuaCaqJB7tx+wJ4M2GYlIjWemF79RdvyHAaChrPvJA1yEVElvSp6T4FnvsS/e3mZ8R8gcY7pZnpXVBIakedSKRR4W7xe4LobQr4UrY8Ep6HCcjHvDKFW+NS9aaNvxE9KZp6GaojJ2su+elyBZmFCVFOjKdjB9fEX+I5kCQLh1jCRjK0jbtijQ7aMJ87wjn+i0p69JipIN1szaVoX7DNqsj2KT6eNogGFvy/Nd1QSnyZjC5MO8rtSdcG4tmc5xEmJnClC69aNP7gcLPYrlfzwwBPa2DMcKiNFrSB11XuqFoc3UY/Nzc5+RGWQlvLHieLm23tfCEHC2HfHTtKlxXYzDlyCikP48aDCP4W49zJFLalSLHhfhRN2na5ZcZx63kUNQiJaeA0URdRy/KR1FOP8GA153FioGq5gdK+Ura7k2uVMng0R7vsXwpBgNOfr9UDy5kUx8ZhdCYSaxAEiLTCwya2iDFNgr+6gI0xXRc9WEuMsfMJ1tjJdqUS5k8z2s3h7AmM1epD12LgJDUYXzLb4O59DkQabcZZKKEsWzmQwNkvjVs0Hi/WcQiDGtofLS0wHIZKsn4VbDQ39bQf78MH2dFpIYwFvFwR47VFGGwYY0+dkZ0UUaoUuUPfyLoIeKuy8beoE1QHoS8OsTFdFIroZtrRqr+HY0SEBh3QKEz14lXNurJxdTWScdIrf/Ggbq8FztINvBvfzXDsyoZTulPtu9AwNpjYPTpXzzQ+ciWEsZJZ3OAAu7qzuCBQPZD+2Ga+BzmxsAnndwVkZ37qZrfZHkz5nq43R+L2Is0uuxXxN0JeqFg5hx2pdjLpRFbyF/e3GjTS1vPLg709kH0vT82G8ZobmDJlvWF+4yWliwsHybxaDt7jzWnfMzJkjc/fhiUDWvD51JS5OIkm2AGuAtd/tNyGKnw7j2aFRB8+NaSGULbxVsGd6rxCyaHM3eQZI7kSuI1i0CKUVNQgjKAMUr5UTBGM1VFUeLZvqVVz/TfVZZjNgG8Lh05DYOCAcs/3BGFw+2L+2qXl+nUgE7ZjTbjcRKr3+wvl31Zxioti0zOygb5FGLmPJeS2HNtcVyUfg//GdODMCFJ/36YJzTNv9KbwhtCu5/+cMMyT7yEsW7wekaz9cmxtCPiwronCfyXDk8qrvhPVoo1Vl3/9mbO8r8R1L1gJaIcJ76EMaljSbdBSW1YGilmnYF3frQizIo5t8f3/NBT03XPmPKR1CayUOLSLojhGeTPfng5OzR36DBVdoBTqK5IbH8aGe+p0/t7IR7cfGWzD7E98O0M16Dr5TjbBP/LQVMfOjKd/Qdi/ex0WCZtFQgTnuYGJsyZD+/mcRD+RpTze5+pFmoXXX3MI8HAzOxFsIrCoYDVF2RHaxVyozVdcexx2djWT0PjU7iF0ieBgbzDSrW4F9ir/uGfsTwb4tyS813y8kMZT4gEQfmWGXhLBxJT24EZkytCX8g315F86dHnVfTZ3I5v4QXnyayEqEwBAj0MA4kthck1D7kPmyV65cakONOtmjcjpHjFb+qeSp4enhvsJLqK/tA2L8kwQKRLVIh25F0wQpRjeHaJy0+hkMuWi/H0LN6striLcwKUml9uznWSmJ3s6TD6v4Rlb6JwsEOjkbvyzG5yzgthZibRu50lWU6eFqOMgyCn8hmhHn9dMz0z6jlZTQR4T1bt/zNB2fOqCVWtbU+xLvFIIVT/fZmGtunIxc8I39MaT976uGbXTcN333KmLIG2TOKTm+MYkoBB5lbhogv5QNAPiNvHjJX/nsoLPZdYDY8Kr51AVcxpMBArXTuyC3km0C+wdlTDuuTDye4dsv38ipVd2monu4jS0hkWvAk3r3o/Y8miNhprkiFnPzrVliOf90mEMrRJwuv3/QEn0Kvw773eT2oScxOj12FRseefWi2TZ+dGVHSv9dLJfb29dhf3cm3pnzmLu4maxlzuWpcxs1xIjuvit9i/f1rv87M+1hvIT9zC/9i712afuZXNCmWOj73pDek9xTuoOGF/8+w8VlLdRD5pWZCgXDxqGRn07Y96N1Q8bZzEaQn1UWw1dfI7ucowYFQpeSZ4RI6VV3zTDlo+qVHB2JSPYLgfWf6NK6arS1K7tuyURTAJtPp6PKZMlOll2rKSHtQ6uZRUpJISp/1UrJpLC9h/uRppJhkP
*/