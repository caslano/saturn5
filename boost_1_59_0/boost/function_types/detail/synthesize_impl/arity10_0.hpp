
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
template< typename R >
struct BOOST_FT_make_type(BOOST_FT_flags,BOOST_FT_cc_id,0)
{
typedef BOOST_FT_syntax(BOOST_FT_cc,type BOOST_PP_EMPTY) (BOOST_FT_nullary_param BOOST_FT_ell) BOOST_FT_cv ;
};
template< > 
struct synthesize_impl_o< BOOST_FT_flags, BOOST_FT_cc_id, 1 > 
{ 
template<typename S> struct synthesize_impl_i
{
private:
typedef typename mpl::begin<S> ::type iter_0;
public:
typedef typename detail::BOOST_FT_make_type(BOOST_FT_flags,BOOST_FT_cc_id,0) 
< typename mpl::deref< iter_0 > ::type 
> ::type type;
};
};
template< typename R , typename T0 >
struct BOOST_FT_make_type(BOOST_FT_flags,BOOST_FT_cc_id,1)
{
typedef BOOST_FT_syntax(BOOST_FT_cc,type BOOST_PP_EMPTY) (T0 BOOST_FT_ell) BOOST_FT_cv ;
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
, typename mpl::deref< iter_1 > ::type
> ::type type;
};
};
template< typename R , typename T0 , typename T1 >
struct BOOST_FT_make_type(BOOST_FT_flags,BOOST_FT_cc_id,2)
{
typedef BOOST_FT_syntax(BOOST_FT_cc,type BOOST_PP_EMPTY) (T0 , T1 BOOST_FT_ell) BOOST_FT_cv ;
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
, typename mpl::deref< iter_1 > ::type
, typename mpl::deref< iter_2 > ::type
> ::type type;
};
};
template< typename R , typename T0 , typename T1 , typename T2 >
struct BOOST_FT_make_type(BOOST_FT_flags,BOOST_FT_cc_id,3)
{
typedef BOOST_FT_syntax(BOOST_FT_cc,type BOOST_PP_EMPTY) (T0 , T1 , T2 BOOST_FT_ell) BOOST_FT_cv ;
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
, typename mpl::deref< iter_1 > ::type
, typename mpl::deref< iter_2 > ::type
, typename mpl::deref< iter_3 > ::type
> ::type type;
};
};
template< typename R , typename T0 , typename T1 , typename T2 , typename T3 >
struct BOOST_FT_make_type(BOOST_FT_flags,BOOST_FT_cc_id,4)
{
typedef BOOST_FT_syntax(BOOST_FT_cc,type BOOST_PP_EMPTY) (T0 , T1 , T2 , T3 BOOST_FT_ell) BOOST_FT_cv ;
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
, typename mpl::deref< iter_1 > ::type
, typename mpl::deref< iter_2 > ::type
, typename mpl::deref< iter_3 > ::type
, typename mpl::deref< iter_4 > ::type
> ::type type;
};
};
template< typename R , typename T0 , typename T1 , typename T2 , typename T3 , typename T4 >
struct BOOST_FT_make_type(BOOST_FT_flags,BOOST_FT_cc_id,5)
{
typedef BOOST_FT_syntax(BOOST_FT_cc,type BOOST_PP_EMPTY) (T0 , T1 , T2 , T3 , T4 BOOST_FT_ell) BOOST_FT_cv ;
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
, typename mpl::deref< iter_1 > ::type
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
typedef BOOST_FT_syntax(BOOST_FT_cc,type BOOST_PP_EMPTY) (T0 , T1 , T2 , T3 , T4 , T5 BOOST_FT_ell) BOOST_FT_cv ;
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
, typename mpl::deref< iter_1 > ::type
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
typedef BOOST_FT_syntax(BOOST_FT_cc,type BOOST_PP_EMPTY) (T0 , T1 , T2 , T3 , T4 , T5 , T6 BOOST_FT_ell) BOOST_FT_cv ;
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
, typename mpl::deref< iter_1 > ::type
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
typedef BOOST_FT_syntax(BOOST_FT_cc,type BOOST_PP_EMPTY) (T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 BOOST_FT_ell) BOOST_FT_cv ;
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
, typename mpl::deref< iter_1 > ::type
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
typedef BOOST_FT_syntax(BOOST_FT_cc,type BOOST_PP_EMPTY) (T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 BOOST_FT_ell) BOOST_FT_cv ;
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
, typename mpl::deref< iter_1 > ::type
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
typedef BOOST_FT_syntax(BOOST_FT_cc,type BOOST_PP_EMPTY) (T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 BOOST_FT_ell) BOOST_FT_cv ;
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
, typename mpl::deref< iter_1 > ::type
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


/* arity10_0.hpp
TJSXMSuwGzIXn2l8bHigErLXDu4A0qVVFt2+qd1M2PcE2S/18Hm7rno5Epqwgd22jLsF/bVzN6o1OReddu+N0rXzxubfzwckAUMwDq7tKrB+FZwmn7Lgv1lDKTve5IN5+YPUzKrPTJdj2onH1n4VxSm8kXkJWh73TxYZuF483IEjl1/O7N6FODEtAU3UmJTb93REucFeBageZeJVTu+EUzHMnnhvpLdQkTJ7dJh4IE/tSDUS7OqOn2n1yxUjgwQCs803YplsLcF8mKHZajqY86Ja2rkvU7vUno4w45jEyTp1B/JLy4acjHReZgSOqrw2mUjaRLB6rM6vGtHMD11R3o8TcaVf15fkw8wPWyFd5ufdgnE7k+2KfS8MmeFNyRxosd/W9MDB2cF2eV3l4P+A7q78r1dudmsc9GIZeDgj3Pxj3CzrO0XfcDsqVhW+/NfqfhgwahGSwN5ckG8Aj28Fxe6buLjxXvBmd1lscfquK4vbtqdF00iPXs0gvK6aGfMX/NiPMMRe0BmDxOkOPglMHOLIPPUGE6KQxG51zZ8PhF9KXs8ekK537D1tJiNv1Sy0b/cDg9XRvMxDqvByEitcI14NzN/Pvn3ff6yXXS8nNpLnKua3R4973Jtj5WNvv0KfXZFGc0eo/tE1BjxzKGjwKAvV144+LVWiymCMmyCTJe0RnJZRzZQ+yVU+at1qaMeg9uAfNgxq+GIDaCbrmSytvpbfhN0l8v0ALWxARXWNHAR+JcU06A1ItdJqXjKIamLX74waPglpOzIP17OjvK5Q9b7/c4rVU60ddVfQGfm5xOzUdb/SK+fUb1mVtpMmdu0crw09GMgfeZi5mSoMJVHsOx+mnKoeGQ81yg522sNyhH1a1N9c04HFo6dL2nFiT4trfnC7XaHA9esj+VV4unQhuK+OOZs7Ryjx3S3M1yBbQcfiE7NsokeSjzK/Lbyq8ZCG6vnNQF5MosF8TzlxDWvwexzOjJq4snjoeKJXbhWj06kVu+zmEr7jycEpdqCWq/gik3rMVXyXSz7hqz4QyYE9FOEcwsQ871Q/7KJYYvrNRGEcJ/BvR8EOQJV3DS2wtgWxQbUrImBIVKUuaD09tOtwA9AE13W55e/qJ8g8CJPKxGmwqLzTUSmXNQv0X4yErK24Ekny8036HaTP1Ww+zHUifx5E8cUWEn3teMbfayyBQoAcV28rhbh0LmPIw0XBK4HXT3Nf/Nf4ZgtLIS35yKjw0h28gKka1RK5dfZ1I11/53Bc+oXn8AANQ/OwrdJAM4TXnGB3/0WYVLzATjBDGbUVmrLwXYwF7HwqN3DObuxQnSaWOLjwHQjvDu+rawbaDcMq0sp6hLHpW3CojMJkFuFEftpNcB/OyPVa7sjhcsyLcHRIHwL9A2go2Sq9mVlzWMgrFHQL0oZNEZJdZV+OVis/w+cGlFp7i5kqb/XNMkV5xBlaUjBlfh3Uq2rKr6i5QDrjr9NIX67kg52wqqShnSbaHgz4vUeN8Ru1cjPnW8/uE4pNZ0gCO1+oHn4yg3pPKwBtuB3H2ALkWVaH+61vC5p4J/FSF8Qk77OFzERvglxDfMYZTYbH417DU359cVgS8ovMhi5b4YyGlyaaWCF6EJdEL8HhZy9JyMfDeK+SQxuTRWu63opt/BgCTXbcbvgmJ0TnOGfGrkcaISG15H2Oloi35+cpMcVwRMPIMWocx/zC1ZjM+xPmMO8zi9+W8FvN0HqrofBj50QQ2ksS1olbIuu4NveKHWrEW/kS3/9N/8YZMav/TRktlzI/vr0cGGPS1RDFrXqP3dIGUjX3K8Uw2M2PV+/sBg+ksXjZPRuE9g8y0MCWXt5WIwB9GIpdeOCSCiapIoqnxfDVTd9PwhGkNTwu6b5Lo6TNmptcOGHQuzxOw8gdPNNsk0iz97BVLSf58vUR4Zb0vNv9EEC06p/T04GT/i1Ufecw2UW3+3Mu2K1uXm506n2qauhEaI4vhqfk753TXIwPiitXKflr+H4vOFGJ/VfPPAf51mjSMz+47ngNZ5qnKA47QFMVJ8y8ku0sNClqA2lR4OQvyfHgoOMkfSSOcBgEhbBYmzfQVjxb329qOxVcYkXbi9tNt49X9r8c3I50DGBB4FqmgquXOoiwMHLImjHYAkAFOlcm2igmgcMIf0npAlLM4SDuaFJRmSiHWA3pKFPm2aGyMjoFh1XzKIaT/cpdDpXWCralW6jd15PYcy+55epu2WynC2qFaM/jnM4FzB/4TPNMt5g5GeDZZf3VuWdiCzyo9y+ia8gcKEcE89PX6mefFb4R2sX3fswA6uL6FTbeIrwYrKPuiI+kaOV9OvR1D/Wp4BCFAwdeKIKhnp/qgkTfymdHPJU6MZYrN8gXLhgv6X7cxbpRlCsHmM/ugG/dQU+UKrWBvUmMmYgMf60vkZbjdNrE826MybUXtDXk3tia/u/Ry6LcBaarg9v6llx8mCddbl4LaqeO3lziFS3V2k0ky+pNgkJB1+pTDCFpVWClR2B1e36KcbQh2U58D7FlVCXTSLmFe7yvf2F/4TAK9Dd6kVirttnVqJ/c3nINGyd1joApBDqqMV38x5mTeSEeS8shyt2Czr0iZjqerfaCD4Tx25nZ61CGPv27UHzu32JJVFFTVryrSlpIdXxlaye9IYPCSS7/W6JQmLgtrnlnU6fHclmkJ5ma1UHrIKmtroo3ZnX4OOpoY7qw738R4aVIWwfGnOM0ssVKmWrHJfymxV45shg2pwsEepKjkojCCH4jcoJNNP/VahXYrJYY9TPlbZG9Jvt4JHwgQuWgyK/IPRrO9cYjP73VXlWd9MwIlXW4boHylYnUPJ9/VJ3GEq97d+8a1lGuLDFczf739SbiEoeiOdFO3u9AP8hrkV68H7csIOBT1h7by1txYM263La1h1wwMSYTSlMWuIh/NiUlQsvrspSNNvFyXeFpxzLB29x0lae6zrCmqHVdcGXYgpDbtm3n2LbCNiVT+HngQtDdsFCw1qzLeOHaS5xQ6PqqR7FBlaJ3x11iXppqnYQFLYu2CYIP0gcFEIXqn/PLynqoqUVaDZaU4M1Adx32vZoT8X44JOfTBaRjQDC2SwD8DmjgUw+w6ZT4WV40MCu8acS86tyLnErpLnOSXT80vBpWEzWkzszmeLbRyoBq+8rFTWy3X3ppU/jridtV41YRK8UTHbn4DTkyfL3TP/jICAOn6jyrJNrLNX+bOndbqpyQezpv2WfeHTV/oc+PB6BLoIo1+CpWmMYkPwWLDERO8o70VtnzdqHizRL/3zk8PcTw1zj5ifT/n5h9cVG0pDHu3MUYMCnha7zTrmLACxie9DPTy3DpLIInP5WGToTMPbBs+UeS+QQ0ENP+N90JkOH7gMBdyRhfZloeTPTiBJJzPuOO4hljM6EMxD3qGYrVAkn0G4gefzNVaw/qm6LNuS9Zw+DY/Cy9lrB+27zOMCjs/qY32o+4cnqQsP2ObkJSFpM0pjw5GRrAKN82q5NlJjtj6qJ0P4Osh9quuERrshQRDzO0ls+qglcolopLaPAyEMWIUjhHawQ9CVHpHx9WIxSOTCYckMf1wAns7ZKAfKbUidKIFTMbHUUk9o+oMpJABG6uS1SMxH8wJ+drvUDHPz6pr7e7UyNs0cteLzpGs7LQ+8Oi7WZ6xzyfmLxoWiSB1Q+0oJ4VJsJJy68KqeGn6WV+dUPFt+niynTotZc8hQcoHQek4cJ6cPOBSF/R82Z8yj+4lLkhNG9mRlA50TRvvC34eUnAfu/FDHbTXOUKrnV4NiKm41X3rniTvwDSG3zghAt8wjLqRdK9wwhwabN9e7nsE3yEBgkK4Jux58IdYEjDP1K8dolPlrNNnJM0vlEHvZAHKemiflA5+8W92RarZigw71UlVLlKdafM1p0BNqt1pyhXHjBeAv26c3VoKFciMJ94IJ94EFiGp1+14148s229iB6/BQ8/w5A+gXpkDTU8qYPS+9+g9neHWAPudKsF5Fv/NceYB+HkuKzRuu9ZqhV9MDaU1zlY2+CunWv3a7rCd3n0dzpHZ2QviBZ2oxC7DdV3JaF9wdDoQgwT0KHC/aA9vsKCE7LnHm8GrY6mrNU5GWClSmkxhA1APFZNorqtxLsxvkW7cs6qaKKCARy741v88+tuBiH2T8ik1pxjDK6dDtzEuUjrwtNbkC+QX0LfXZdrqmfBYUPxmPR4WEHwikQx1Ri9vmH41szGXZxrgxOn9pNefxvBpnPHstpDGrPpdr/DHXFVTaMyR27/8qPS8UzXeJKMKkyNsXclH0AuiQZ6gAvdqW1cbrMbhYiIp9XmpV0isxOMWJUwohHtAWIFMQTkxD67MZoJ7Bzmaxmi2OKqEYbLziR1+rTjkGdAXlzeJdgDBuALkdVeNzsnv4mwWZDGDwW+12+pudH9apw/O8QSJBIWuDYzaakO+GJriFArpGEkuFQnyRYGbb9I8NAfHEnSJiuHRuo4L0pq/mfYe6VTubtdEHySgWHy+oUC/mjaPrp6ryL6Opli8PGVkNIZ5vOLuAvn1k3tp6fgvocSLeZKvgYL46XSr7tct4p81QwvWsCqYGuPliHsoO24XrAnhHj5O5GOuvkjg44JlPoTcBveoat23F0z+Zkv7SVU3J1/6afUv7P0fts4rtqW28x/8GW/+GWUhSpBkMqeVh/xBfb2bubeE5172/84awGIR3pORooioLxhs+on7KStCPqeYjmqlT+FL9hDJBs01YcwNT7jKxYe/pwRgYBVxerEcHElEw/3k0ys1xZJ+d2cRBxHVP1t0ftNLy3OumIBphkgvnzTKG6y+XLbFy9J27T0bjsi+e/khoKUpmw6M/s2R4hccA9kDxheA3+7r7JVkjtezApS6KV1peihzpJqqmiUwp07GndforLuH66Cz77WE3hs0I+dtFL2gA2hgRX3qXX0o4pFFU2SCA+pY65uYbQQEg59+VMZwlG7H7cHWWnEmw9ltx34Ltn8p8W+F1j3LPTuvLFj5lIDAlDcFNGNl9+7N758h7foaeYxE72pKm/qMy1KYndk+M5wm9u8pZNDgr/LSkYkLgsapJgR7wO+CWTvwuCncfW+T42j++A9T6a9yPT98f2HCjuv8z9BlnuuOBSPjakBlyjsyCzvGkbU2WVMqDtBqsnX8zjJ9UG+V7hWW4UrJLoDu5Aprbs2Z7a5b9j9TjIJZdk82oA41JRf5rjbCvtFSU04UnOr4Z7GZJ5LFxeC7EeW40kQqMrSD/Z12KdrbkvZgiJNsVXzxI8Ug0I5l08Sl8AXMJR63Gd4ZgMv3lbRc7W+2VOPvOlQVkfgSrg0tjcwhmc89Kc3eKG1ezignQS48ycC4dLN7VumwDu3L+d9kjtr8PDCg19vRBhIQH74Wz3ge9zG8LhdpFmHrECmvjPSYaWpJIXOuOPXLijJHztmZLm1KjBsMq6zSHC8D3pAZ88dpjZ/s38NiuwkAMXEQ/V2tx67Y0/YjMtESH9tMBfvGgIO4WZzHMKKMVaHkJ7Yu64kS31Of/DdEodLbxuBc2tuRq1ZZhnxMvK0vjbaQZJixgTjGr6cavSRxN+QmA7FByMJOnDSlao8H5JWixrk6faaGoT5NUcB0vycpxV5bqOzB5k+77VrIazZ68k1+QR9zcuVQl++y00Hg3j+81hxzDOjlkz7/vZ2xJ4vdv8mcB/0b85pwMeAd+324C5SPZ8GrOsjjKxX3V38rqew1jo0tK8Z3/JykZscjuVoF4PybFdTCokkP1hJErzOFi2Ynq2orbEbj5EdHJ/0rK5qxOyrjf17b0F7QjFSZueurTOCUqlVWilDto0MnVRR+JYwWc/D0uj2nxwEpGfKyR35CYSwY4RTUDbQ2rn7MvEu42En71StN6miqpw05NsGXa/DPmkSzYQeO2MF1syYxxaxXbyGYmStKRHoY93AvwBBmj+742kdfN1iq98J1wdBHMyFkUm8mS+RMC7KcmgNBBgXVl96qTmr06cbk+U4RAAzEJIQ1qIU4zgJNhMO3/tsVKr+7inWxtu1Xt41aW7YbhBCnmlePtVO31TJ2q1r/nSNdnK+9kV+aTwFMpK6riuGN+XJSzrCIyX5kpJKF40tDPownG2igrLg/PyG7Zd8DzUiMpUxVDyvN5Cwrp4n/XUpPaC1TZIRAeXQGldKqh39aXl4ZtfKnl8iPy/2SIXFez2vq+Dytm6Z/MIQ4gXS+roNYx3cve0+ykUYe0WsH/PUtCe1IcZXrgyUuePZizeRUtQktiUgrp6RnLPaRTJRKJBKiQifcEw8BiktGBmJAMkkuvjSsX79gkp8ZrA9xhiczwfVmsSL6OjR8+Grfy449DM/NG0NNNxF/iEWLb5DFe1UUT5G4b3xv6bnSdz3dWUUzVj1tuSyVbv8Hl2KiE1chz0QJXbPBvbLh9mzxZPGwjet8nsIlpYuXsPvQtMeNPhvUg6uVfGxunv62W/UTP23msjxjsfmu010Bw8x5GwIA+kD+5pN92KZK/uQIOfFsMkWVE+BzEh7KCDVv3lMmdO9nVYZJVDRtLwCXaOsVGemGHnwpW6QXkfuShKuaoh+5LAB9FpBnSQj9eUr9d/SHuaYMFZKg8NFW8azFiPRh9ZBX9NNq1D200B6AYDRzXWeFDJLmR/9XMhQj328uO0xf7OGJhhAHCsmwZQxboPVu0IE74J4M7B0x2N5Gi99ERMiox4BG3ywXd4ZxkVNA/YYdZRMm7ZQe4t1clLFqy3tcDnqlQMnWgKf1YR4hF8w8XAvzNergrgigKQEqMR9ffHTD4pM/vs7aQMQ+T7SD9FXVzkXdmNJeKreWkh1f+xIJadjuPYCbRf+Tre5apbC0NwoJo5vGBsKmMCViutq4WwE+EG7Zm/1v1SMfjJx63NvNtlXLh4uBs5Ah4AIIMU7mXCV54Ml6GQoyedUnYXT9+/SJL6oOigUBmAzsGWCiNgcQKRKYI5W1slsvjfXexPa1GlTp2EeBjsumpj4ihOS8mNqzUq7K2Ch4BCWHNo0eV4NbrkavGDhGZelLWH1qYW9Be/kCQ3g9WlHVM86ddeAzyu+NKeXboiTLBMlX0FkXWzIi0FYRtj2Lvxxk/1giLRpdaMgMgac8NLtA/rNKMOhxzaBqUIgDD421SQddn3DcHw4btkoYpLZADkhZrby83GD2LM4xi61VC+6FsHfYaAQehzLiU2tr26eGqJodeGVx04Z0a1hxgMK1PYo03i2tJgkNbxYkMVxpEnoD77K/xKmTdC1Nv8956OadVDPRIk7mBYxkxoHb3GZ+uh89XRtfigf8V5TfCLvYLj3UzNvOSkPKl1Vze+7jj6TaHhkSt0KEiIv/jxvL/mCw81nIfaaoRiltVgr3Gh12kDXgw6hHyTIQzTXo4v35DyZS9jzSwo+K4QA0xCq7IRT0xM1ODU8WZT24OL64jBzkfjaOP4cKB6klVbmePio0TK1KsutY+dmxygefy4I00gQKnjo6JBTzrp2ujt04HyF8ZySAwNzu2m/vxtlvaKIcGyzoojkQJjUF/mMmnT+8PK7m6Ik+EZrjoY+KzNzFNSV52PJF1vWBFhF28sATWUMNFrQhZpcvnVUD+NFqPWFMmy9Htt1ftk4HWWg7eY5e1+O7YYACiz10w1Mx3fI89pN
*/