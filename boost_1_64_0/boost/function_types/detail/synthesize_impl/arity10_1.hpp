
// (C) Copyright Tobias Schwinger
//
// Use modification and distribution are subject to the boost Software License,
// Version 1.0. (See http://www.boost.org/LICENSE_1_0.txt).

//------------------------------------------------------------------------------

// no include guards, this file is intended for multiple inclusion

// input:  BOOST_FT_syntax     type macro to use
// input:  BOOST_FT_cc         empty or cc specifier 
// input:  BOOST_FT_ell        empty or "..."
// input:  BOOST_FT_cv         empty or cv qualifiers
// input:  BOOST_FT_flags      single decimal integer encoding the flags
// output: BOOST_FT_n          number of component types (arity+1)
// output: BOOST_FT_arity      current arity
// output: BOOST_FT_type       macro that expands to the type
// output: BOOST_FT_tplargs(p) template arguments with given prefix
// output: BOOST_FT_params(p)  parameters with given prefix

# define BOOST_FT_make_type(flags,cc,arity) BOOST_FT_make_type_impl(flags,cc,arity)
# define BOOST_FT_make_type_impl(flags,cc,arity) make_type_ ## flags ## _ ## cc ## _ ## arity
template< typename R , typename T0 >
struct BOOST_FT_make_type(BOOST_FT_flags,BOOST_FT_cc_id,1)
{
typedef BOOST_FT_syntax(BOOST_FT_cc,type BOOST_PP_EMPTY) ( BOOST_FT_ell) BOOST_FT_cv ;
};
template< > 
struct synthesize_impl_o< BOOST_FT_flags, BOOST_FT_cc_id, 2 > 
{ 
template<typename S> struct synthesize_impl_i
{
private:
typedef typename mpl::begin<S> ::type iter_0;
typedef typename mpl::next< iter_0 > ::type iter_1;
public:
typedef typename detail::BOOST_FT_make_type(BOOST_FT_flags,BOOST_FT_cc_id,1) 
< typename mpl::deref< iter_0 > ::type 
, typename detail::cv_traits< 
typename mpl::deref< iter_1 > ::type > ::type
> ::type type;
};
};
template< typename R , typename T0 , typename T1 >
struct BOOST_FT_make_type(BOOST_FT_flags,BOOST_FT_cc_id,2)
{
typedef BOOST_FT_syntax(BOOST_FT_cc,type BOOST_PP_EMPTY) (T1 BOOST_FT_ell) BOOST_FT_cv ;
};
template< > 
struct synthesize_impl_o< BOOST_FT_flags, BOOST_FT_cc_id, 3 > 
{ 
template<typename S> struct synthesize_impl_i
{
private:
typedef typename mpl::begin<S> ::type iter_0;
typedef typename mpl::next< iter_0 > ::type iter_1;
typedef typename mpl::next< iter_1 > ::type iter_2;
public:
typedef typename detail::BOOST_FT_make_type(BOOST_FT_flags,BOOST_FT_cc_id,2) 
< typename mpl::deref< iter_0 > ::type 
, typename detail::cv_traits< 
typename mpl::deref< iter_1 > ::type > ::type
, typename mpl::deref< iter_2 > ::type
> ::type type;
};
};
template< typename R , typename T0 , typename T1 , typename T2 >
struct BOOST_FT_make_type(BOOST_FT_flags,BOOST_FT_cc_id,3)
{
typedef BOOST_FT_syntax(BOOST_FT_cc,type BOOST_PP_EMPTY) (T1 , T2 BOOST_FT_ell) BOOST_FT_cv ;
};
template< > 
struct synthesize_impl_o< BOOST_FT_flags, BOOST_FT_cc_id, 4 > 
{ 
template<typename S> struct synthesize_impl_i
{
private:
typedef typename mpl::begin<S> ::type iter_0;
typedef typename mpl::next< iter_0 > ::type iter_1;
typedef typename mpl::next< iter_1 > ::type iter_2;
typedef typename mpl::next< iter_2 > ::type iter_3;
public:
typedef typename detail::BOOST_FT_make_type(BOOST_FT_flags,BOOST_FT_cc_id,3) 
< typename mpl::deref< iter_0 > ::type 
, typename detail::cv_traits< 
typename mpl::deref< iter_1 > ::type > ::type
, typename mpl::deref< iter_2 > ::type
, typename mpl::deref< iter_3 > ::type
> ::type type;
};
};
template< typename R , typename T0 , typename T1 , typename T2 , typename T3 >
struct BOOST_FT_make_type(BOOST_FT_flags,BOOST_FT_cc_id,4)
{
typedef BOOST_FT_syntax(BOOST_FT_cc,type BOOST_PP_EMPTY) (T1 , T2 , T3 BOOST_FT_ell) BOOST_FT_cv ;
};
template< > 
struct synthesize_impl_o< BOOST_FT_flags, BOOST_FT_cc_id, 5 > 
{ 
template<typename S> struct synthesize_impl_i
{
private:
typedef typename mpl::begin<S> ::type iter_0;
typedef typename mpl::next< iter_0 > ::type iter_1;
typedef typename mpl::next< iter_1 > ::type iter_2;
typedef typename mpl::next< iter_2 > ::type iter_3;
typedef typename mpl::next< iter_3 > ::type iter_4;
public:
typedef typename detail::BOOST_FT_make_type(BOOST_FT_flags,BOOST_FT_cc_id,4) 
< typename mpl::deref< iter_0 > ::type 
, typename detail::cv_traits< 
typename mpl::deref< iter_1 > ::type > ::type
, typename mpl::deref< iter_2 > ::type
, typename mpl::deref< iter_3 > ::type
, typename mpl::deref< iter_4 > ::type
> ::type type;
};
};
template< typename R , typename T0 , typename T1 , typename T2 , typename T3 , typename T4 >
struct BOOST_FT_make_type(BOOST_FT_flags,BOOST_FT_cc_id,5)
{
typedef BOOST_FT_syntax(BOOST_FT_cc,type BOOST_PP_EMPTY) (T1 , T2 , T3 , T4 BOOST_FT_ell) BOOST_FT_cv ;
};
template< > 
struct synthesize_impl_o< BOOST_FT_flags, BOOST_FT_cc_id, 6 > 
{ 
template<typename S> struct synthesize_impl_i
{
private:
typedef typename mpl::begin<S> ::type iter_0;
typedef typename mpl::next< iter_0 > ::type iter_1;
typedef typename mpl::next< iter_1 > ::type iter_2;
typedef typename mpl::next< iter_2 > ::type iter_3;
typedef typename mpl::next< iter_3 > ::type iter_4;
typedef typename mpl::next< iter_4 > ::type iter_5;
public:
typedef typename detail::BOOST_FT_make_type(BOOST_FT_flags,BOOST_FT_cc_id,5) 
< typename mpl::deref< iter_0 > ::type 
, typename detail::cv_traits< 
typename mpl::deref< iter_1 > ::type > ::type
, typename mpl::deref< iter_2 > ::type
, typename mpl::deref< iter_3 > ::type
, typename mpl::deref< iter_4 > ::type
, typename mpl::deref< iter_5 > ::type
> ::type type;
};
};
template< typename R , typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 >
struct BOOST_FT_make_type(BOOST_FT_flags,BOOST_FT_cc_id,6)
{
typedef BOOST_FT_syntax(BOOST_FT_cc,type BOOST_PP_EMPTY) (T1 , T2 , T3 , T4 , T5 BOOST_FT_ell) BOOST_FT_cv ;
};
template< > 
struct synthesize_impl_o< BOOST_FT_flags, BOOST_FT_cc_id, 7 > 
{ 
template<typename S> struct synthesize_impl_i
{
private:
typedef typename mpl::begin<S> ::type iter_0;
typedef typename mpl::next< iter_0 > ::type iter_1;
typedef typename mpl::next< iter_1 > ::type iter_2;
typedef typename mpl::next< iter_2 > ::type iter_3;
typedef typename mpl::next< iter_3 > ::type iter_4;
typedef typename mpl::next< iter_4 > ::type iter_5;
typedef typename mpl::next< iter_5 > ::type iter_6;
public:
typedef typename detail::BOOST_FT_make_type(BOOST_FT_flags,BOOST_FT_cc_id,6) 
< typename mpl::deref< iter_0 > ::type 
, typename detail::cv_traits< 
typename mpl::deref< iter_1 > ::type > ::type
, typename mpl::deref< iter_2 > ::type
, typename mpl::deref< iter_3 > ::type
, typename mpl::deref< iter_4 > ::type
, typename mpl::deref< iter_5 > ::type
, typename mpl::deref< iter_6 > ::type
> ::type type;
};
};
template< typename R , typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 >
struct BOOST_FT_make_type(BOOST_FT_flags,BOOST_FT_cc_id,7)
{
typedef BOOST_FT_syntax(BOOST_FT_cc,type BOOST_PP_EMPTY) (T1 , T2 , T3 , T4 , T5 , T6 BOOST_FT_ell) BOOST_FT_cv ;
};
template< > 
struct synthesize_impl_o< BOOST_FT_flags, BOOST_FT_cc_id, 8 > 
{ 
template<typename S> struct synthesize_impl_i
{
private:
typedef typename mpl::begin<S> ::type iter_0;
typedef typename mpl::next< iter_0 > ::type iter_1;
typedef typename mpl::next< iter_1 > ::type iter_2;
typedef typename mpl::next< iter_2 > ::type iter_3;
typedef typename mpl::next< iter_3 > ::type iter_4;
typedef typename mpl::next< iter_4 > ::type iter_5;
typedef typename mpl::next< iter_5 > ::type iter_6;
typedef typename mpl::next< iter_6 > ::type iter_7;
public:
typedef typename detail::BOOST_FT_make_type(BOOST_FT_flags,BOOST_FT_cc_id,7) 
< typename mpl::deref< iter_0 > ::type 
, typename detail::cv_traits< 
typename mpl::deref< iter_1 > ::type > ::type
, typename mpl::deref< iter_2 > ::type
, typename mpl::deref< iter_3 > ::type
, typename mpl::deref< iter_4 > ::type
, typename mpl::deref< iter_5 > ::type
, typename mpl::deref< iter_6 > ::type
, typename mpl::deref< iter_7 > ::type
> ::type type;
};
};
template< typename R , typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 >
struct BOOST_FT_make_type(BOOST_FT_flags,BOOST_FT_cc_id,8)
{
typedef BOOST_FT_syntax(BOOST_FT_cc,type BOOST_PP_EMPTY) (T1 , T2 , T3 , T4 , T5 , T6 , T7 BOOST_FT_ell) BOOST_FT_cv ;
};
template< > 
struct synthesize_impl_o< BOOST_FT_flags, BOOST_FT_cc_id, 9 > 
{ 
template<typename S> struct synthesize_impl_i
{
private:
typedef typename mpl::begin<S> ::type iter_0;
typedef typename mpl::next< iter_0 > ::type iter_1;
typedef typename mpl::next< iter_1 > ::type iter_2;
typedef typename mpl::next< iter_2 > ::type iter_3;
typedef typename mpl::next< iter_3 > ::type iter_4;
typedef typename mpl::next< iter_4 > ::type iter_5;
typedef typename mpl::next< iter_5 > ::type iter_6;
typedef typename mpl::next< iter_6 > ::type iter_7;
typedef typename mpl::next< iter_7 > ::type iter_8;
public:
typedef typename detail::BOOST_FT_make_type(BOOST_FT_flags,BOOST_FT_cc_id,8) 
< typename mpl::deref< iter_0 > ::type 
, typename detail::cv_traits< 
typename mpl::deref< iter_1 > ::type > ::type
, typename mpl::deref< iter_2 > ::type
, typename mpl::deref< iter_3 > ::type
, typename mpl::deref< iter_4 > ::type
, typename mpl::deref< iter_5 > ::type
, typename mpl::deref< iter_6 > ::type
, typename mpl::deref< iter_7 > ::type
, typename mpl::deref< iter_8 > ::type
> ::type type;
};
};
template< typename R , typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 >
struct BOOST_FT_make_type(BOOST_FT_flags,BOOST_FT_cc_id,9)
{
typedef BOOST_FT_syntax(BOOST_FT_cc,type BOOST_PP_EMPTY) (T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 BOOST_FT_ell) BOOST_FT_cv ;
};
template< > 
struct synthesize_impl_o< BOOST_FT_flags, BOOST_FT_cc_id, 10 > 
{ 
template<typename S> struct synthesize_impl_i
{
private:
typedef typename mpl::begin<S> ::type iter_0;
typedef typename mpl::next< iter_0 > ::type iter_1;
typedef typename mpl::next< iter_1 > ::type iter_2;
typedef typename mpl::next< iter_2 > ::type iter_3;
typedef typename mpl::next< iter_3 > ::type iter_4;
typedef typename mpl::next< iter_4 > ::type iter_5;
typedef typename mpl::next< iter_5 > ::type iter_6;
typedef typename mpl::next< iter_6 > ::type iter_7;
typedef typename mpl::next< iter_7 > ::type iter_8;
typedef typename mpl::next< iter_8 > ::type iter_9;
public:
typedef typename detail::BOOST_FT_make_type(BOOST_FT_flags,BOOST_FT_cc_id,9) 
< typename mpl::deref< iter_0 > ::type 
, typename detail::cv_traits< 
typename mpl::deref< iter_1 > ::type > ::type
, typename mpl::deref< iter_2 > ::type
, typename mpl::deref< iter_3 > ::type
, typename mpl::deref< iter_4 > ::type
, typename mpl::deref< iter_5 > ::type
, typename mpl::deref< iter_6 > ::type
, typename mpl::deref< iter_7 > ::type
, typename mpl::deref< iter_8 > ::type
, typename mpl::deref< iter_9 > ::type
> ::type type;
};
};
template< typename R , typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9 >
struct BOOST_FT_make_type(BOOST_FT_flags,BOOST_FT_cc_id,10)
{
typedef BOOST_FT_syntax(BOOST_FT_cc,type BOOST_PP_EMPTY) (T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 BOOST_FT_ell) BOOST_FT_cv ;
};
template< > 
struct synthesize_impl_o< BOOST_FT_flags, BOOST_FT_cc_id, 11 > 
{ 
template<typename S> struct synthesize_impl_i
{
private:
typedef typename mpl::begin<S> ::type iter_0;
typedef typename mpl::next< iter_0 > ::type iter_1;
typedef typename mpl::next< iter_1 > ::type iter_2;
typedef typename mpl::next< iter_2 > ::type iter_3;
typedef typename mpl::next< iter_3 > ::type iter_4;
typedef typename mpl::next< iter_4 > ::type iter_5;
typedef typename mpl::next< iter_5 > ::type iter_6;
typedef typename mpl::next< iter_6 > ::type iter_7;
typedef typename mpl::next< iter_7 > ::type iter_8;
typedef typename mpl::next< iter_8 > ::type iter_9;
typedef typename mpl::next< iter_9 > ::type iter_10;
public:
typedef typename detail::BOOST_FT_make_type(BOOST_FT_flags,BOOST_FT_cc_id,10) 
< typename mpl::deref< iter_0 > ::type 
, typename detail::cv_traits< 
typename mpl::deref< iter_1 > ::type > ::type
, typename mpl::deref< iter_2 > ::type
, typename mpl::deref< iter_3 > ::type
, typename mpl::deref< iter_4 > ::type
, typename mpl::deref< iter_5 > ::type
, typename mpl::deref< iter_6 > ::type
, typename mpl::deref< iter_7 > ::type
, typename mpl::deref< iter_8 > ::type
, typename mpl::deref< iter_9 > ::type
, typename mpl::deref< iter_10 > ::type
> ::type type;
};
};
# undef BOOST_FT_make_type
# undef BOOST_FT_make_type_impl


/* arity10_1.hpp
lBDEwJKt57jWeRUzgL6zWPOZevr2vqRFcQxaGRoGU6CAcGute0l4/NGkj6zyLAX+jFW+xYqAOtk3RZF/ckLsYInawazXQtX1Cj+J6SdY/IlxMAQsSxYaLHqdnGud64tYWYU2g9F60z3tKZud5/el5ObrERXkbkbuanI3J7e0hbkd1jvI3YLcZeRuT26f15mb7v6uxzPCoimAzgQLbuUql3yTTmkrJkcKQk+q/kG91iHiOI2B3cgXbOdPMSkRpakaS4HCIv9JFE2RFzuKObGA3UooHkK3n7k16GBVTKgWsfw2lNeq0SIjskq9Jd9gsymJ1STlaPeKToGXQwExNZSYt3LUNddkgb06hU9Pi+ppleGMDt/yKww0UwBI3GR4eEWv9My+WUwyUh7FXrucYokSp6gu4tesltc1Oosv357IGkRjBLQo9YHLIVl7p5SjR4vrYFM2k4k1mauaiY9YTglYQmnlaQp0RmSgK5Sv7rMWI7t8V9cJqtLkMZJcPtm8fTEK4C7Fbm1wao2FOiiLrxjPbtCmQpvEvmhrQjWstcJJOr0VwGNm9edxlDtohitlUrKUHOLJ4xf61LMDI72mM1M8o2i8xYMk0zoLxxLIRWZJNEELonCSMqGDk9zKBLAeeGuxml2cTIljHQfanb7g41AJh88Bcavj9RGF7cDPIDt00kIHfrRGx+VPJgPtIYErvRgFdlU+3jkLRRPTpe9uc5ZTvyB+96eWgfBYXK6FQIZcY6Gp0CpcJmk/EU9ReDmEcIRf3Ijc2TWCua03dJx9I1isthjOftzeVUjqZ9XhugB1aK0/zg8OUA8w6uqqT7X7s4lKPyC6x6GtR5sc1hsscj9gnw5NVfoBBz7vB8Yp3UAtf1h6TSdTM0bHiKDmNzV5jTuWXXIsqxyN05BClIhXfJyk1ykjhNr+NEKhTIGZTDS1klI0mtCizvapTFUcG5TfB8FP8wZxVJR9CNBkf6uCXGwJwgF/yJcFHizVqRx8umQrspfD1XehEUDqMlSiywDch4NV8nB1HR8WYf6eQ4QXwr4uaNWzNVGrSW5pvTbP5OBUKYpvzMLwm+mJPivHBI6GNMQF32zBcpPNYV4ipEgPK6mjb0YCLaEINyTAn1+6zd06rCfJyJalfCjN0Z91I9zb2R9LYGLZRb6L9Eh4xHCKp1ySDQjFEpaTv/2aB8WNFtECwTifTa/t0bA4lw/hmiaxm59ZD67VG+XvpGu0wn06On2RePES9xcuo6F5n5IH+8h8rn28RoWxX/5CDwUWMyB/5wzIHrtrrAwgKR0Hfx0YrvwnG0xTydeFPWIyZjKC5uejJWrxbbZitDeLXWBSJk+31vtCA/45z4voO/gqlXzzk1N72PVS6bqtTotLUy0yntK3+exyQVdmzXPQDbZTQwzH7UxMd2oeLJqgRZQ5Whwc5d5hNjumK7sKKHjN+XNaQ5UKARNgI36uxnHhSLkYneXcFyMi0Z+Dn33Alow3/XGqJFUa/ktUZanGqRLgClOF4neGKl01nHYg8Adyw9CvO/9tKFB+qtq1y25XUaQ+zWm3bgu7NXhteA9O9+69Z+8jPy/dyunFi49dbGU68iunjz3W47HE1a0Ocbp168dbX8zJb8Gph4e3h08Dz8acJid3SY4ueKYppwMGnB7wynfGpzh9/vk1z4/3HvMHpydOmE589u5bfpz+8MPVH35t+FMzTouLfy7+vuTKnzk1mVabso5+puZ06dJHlt74/p58TlNTM1JfarTuOqfZ2U9n9/ytYgSn27Yd3DZvir4/p089NfapDUf6DOR08WLPxd4LPeZzunbtG2snt7nvBKd+fmq/7CHtjJw+9NDlh/6Y/+MsTvv3P9U=
*/