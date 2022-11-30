
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

# include <boost/function_types/detail/synthesize_impl/arity10_1.hpp>
# define BOOST_FT_make_type(flags,cc,arity) BOOST_FT_make_type_impl(flags,cc,arity)
# define BOOST_FT_make_type_impl(flags,cc,arity) make_type_ ## flags ## _ ## cc ## _ ## arity
template< typename R , typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9 , typename T10 >
struct BOOST_FT_make_type(BOOST_FT_flags,BOOST_FT_cc_id,11)
{
typedef BOOST_FT_syntax(BOOST_FT_cc,type BOOST_PP_EMPTY) (T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 BOOST_FT_ell) BOOST_FT_cv ;
};
template< > 
struct synthesize_impl_o< BOOST_FT_flags, BOOST_FT_cc_id, 12 > 
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
typedef typename mpl::next< iter_10 > ::type iter_11;
public:
typedef typename detail::BOOST_FT_make_type(BOOST_FT_flags,BOOST_FT_cc_id,11) 
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
, typename mpl::deref< iter_11 > ::type
> ::type type;
};
};
template< typename R , typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9 , typename T10 , typename T11 >
struct BOOST_FT_make_type(BOOST_FT_flags,BOOST_FT_cc_id,12)
{
typedef BOOST_FT_syntax(BOOST_FT_cc,type BOOST_PP_EMPTY) (T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 BOOST_FT_ell) BOOST_FT_cv ;
};
template< > 
struct synthesize_impl_o< BOOST_FT_flags, BOOST_FT_cc_id, 13 > 
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
typedef typename mpl::next< iter_10 > ::type iter_11;
typedef typename mpl::next< iter_11 > ::type iter_12;
public:
typedef typename detail::BOOST_FT_make_type(BOOST_FT_flags,BOOST_FT_cc_id,12) 
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
, typename mpl::deref< iter_11 > ::type
, typename mpl::deref< iter_12 > ::type
> ::type type;
};
};
template< typename R , typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9 , typename T10 , typename T11 , typename T12 >
struct BOOST_FT_make_type(BOOST_FT_flags,BOOST_FT_cc_id,13)
{
typedef BOOST_FT_syntax(BOOST_FT_cc,type BOOST_PP_EMPTY) (T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 BOOST_FT_ell) BOOST_FT_cv ;
};
template< > 
struct synthesize_impl_o< BOOST_FT_flags, BOOST_FT_cc_id, 14 > 
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
typedef typename mpl::next< iter_10 > ::type iter_11;
typedef typename mpl::next< iter_11 > ::type iter_12;
typedef typename mpl::next< iter_12 > ::type iter_13;
public:
typedef typename detail::BOOST_FT_make_type(BOOST_FT_flags,BOOST_FT_cc_id,13) 
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
, typename mpl::deref< iter_11 > ::type
, typename mpl::deref< iter_12 > ::type
, typename mpl::deref< iter_13 > ::type
> ::type type;
};
};
template< typename R , typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9 , typename T10 , typename T11 , typename T12 , typename T13 >
struct BOOST_FT_make_type(BOOST_FT_flags,BOOST_FT_cc_id,14)
{
typedef BOOST_FT_syntax(BOOST_FT_cc,type BOOST_PP_EMPTY) (T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 BOOST_FT_ell) BOOST_FT_cv ;
};
template< > 
struct synthesize_impl_o< BOOST_FT_flags, BOOST_FT_cc_id, 15 > 
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
typedef typename mpl::next< iter_10 > ::type iter_11;
typedef typename mpl::next< iter_11 > ::type iter_12;
typedef typename mpl::next< iter_12 > ::type iter_13;
typedef typename mpl::next< iter_13 > ::type iter_14;
public:
typedef typename detail::BOOST_FT_make_type(BOOST_FT_flags,BOOST_FT_cc_id,14) 
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
, typename mpl::deref< iter_11 > ::type
, typename mpl::deref< iter_12 > ::type
, typename mpl::deref< iter_13 > ::type
, typename mpl::deref< iter_14 > ::type
> ::type type;
};
};
template< typename R , typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9 , typename T10 , typename T11 , typename T12 , typename T13 , typename T14 >
struct BOOST_FT_make_type(BOOST_FT_flags,BOOST_FT_cc_id,15)
{
typedef BOOST_FT_syntax(BOOST_FT_cc,type BOOST_PP_EMPTY) (T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 BOOST_FT_ell) BOOST_FT_cv ;
};
template< > 
struct synthesize_impl_o< BOOST_FT_flags, BOOST_FT_cc_id, 16 > 
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
typedef typename mpl::next< iter_10 > ::type iter_11;
typedef typename mpl::next< iter_11 > ::type iter_12;
typedef typename mpl::next< iter_12 > ::type iter_13;
typedef typename mpl::next< iter_13 > ::type iter_14;
typedef typename mpl::next< iter_14 > ::type iter_15;
public:
typedef typename detail::BOOST_FT_make_type(BOOST_FT_flags,BOOST_FT_cc_id,15) 
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
, typename mpl::deref< iter_11 > ::type
, typename mpl::deref< iter_12 > ::type
, typename mpl::deref< iter_13 > ::type
, typename mpl::deref< iter_14 > ::type
, typename mpl::deref< iter_15 > ::type
> ::type type;
};
};
template< typename R , typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9 , typename T10 , typename T11 , typename T12 , typename T13 , typename T14 , typename T15 >
struct BOOST_FT_make_type(BOOST_FT_flags,BOOST_FT_cc_id,16)
{
typedef BOOST_FT_syntax(BOOST_FT_cc,type BOOST_PP_EMPTY) (T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 BOOST_FT_ell) BOOST_FT_cv ;
};
template< > 
struct synthesize_impl_o< BOOST_FT_flags, BOOST_FT_cc_id, 17 > 
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
typedef typename mpl::next< iter_10 > ::type iter_11;
typedef typename mpl::next< iter_11 > ::type iter_12;
typedef typename mpl::next< iter_12 > ::type iter_13;
typedef typename mpl::next< iter_13 > ::type iter_14;
typedef typename mpl::next< iter_14 > ::type iter_15;
typedef typename mpl::next< iter_15 > ::type iter_16;
public:
typedef typename detail::BOOST_FT_make_type(BOOST_FT_flags,BOOST_FT_cc_id,16) 
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
, typename mpl::deref< iter_11 > ::type
, typename mpl::deref< iter_12 > ::type
, typename mpl::deref< iter_13 > ::type
, typename mpl::deref< iter_14 > ::type
, typename mpl::deref< iter_15 > ::type
, typename mpl::deref< iter_16 > ::type
> ::type type;
};
};
template< typename R , typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9 , typename T10 , typename T11 , typename T12 , typename T13 , typename T14 , typename T15 , typename T16 >
struct BOOST_FT_make_type(BOOST_FT_flags,BOOST_FT_cc_id,17)
{
typedef BOOST_FT_syntax(BOOST_FT_cc,type BOOST_PP_EMPTY) (T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 BOOST_FT_ell) BOOST_FT_cv ;
};
template< > 
struct synthesize_impl_o< BOOST_FT_flags, BOOST_FT_cc_id, 18 > 
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
typedef typename mpl::next< iter_10 > ::type iter_11;
typedef typename mpl::next< iter_11 > ::type iter_12;
typedef typename mpl::next< iter_12 > ::type iter_13;
typedef typename mpl::next< iter_13 > ::type iter_14;
typedef typename mpl::next< iter_14 > ::type iter_15;
typedef typename mpl::next< iter_15 > ::type iter_16;
typedef typename mpl::next< iter_16 > ::type iter_17;
public:
typedef typename detail::BOOST_FT_make_type(BOOST_FT_flags,BOOST_FT_cc_id,17) 
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
, typename mpl::deref< iter_11 > ::type
, typename mpl::deref< iter_12 > ::type
, typename mpl::deref< iter_13 > ::type
, typename mpl::deref< iter_14 > ::type
, typename mpl::deref< iter_15 > ::type
, typename mpl::deref< iter_16 > ::type
, typename mpl::deref< iter_17 > ::type
> ::type type;
};
};
template< typename R , typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9 , typename T10 , typename T11 , typename T12 , typename T13 , typename T14 , typename T15 , typename T16 , typename T17 >
struct BOOST_FT_make_type(BOOST_FT_flags,BOOST_FT_cc_id,18)
{
typedef BOOST_FT_syntax(BOOST_FT_cc,type BOOST_PP_EMPTY) (T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 BOOST_FT_ell) BOOST_FT_cv ;
};
template< > 
struct synthesize_impl_o< BOOST_FT_flags, BOOST_FT_cc_id, 19 > 
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
typedef typename mpl::next< iter_10 > ::type iter_11;
typedef typename mpl::next< iter_11 > ::type iter_12;
typedef typename mpl::next< iter_12 > ::type iter_13;
typedef typename mpl::next< iter_13 > ::type iter_14;
typedef typename mpl::next< iter_14 > ::type iter_15;
typedef typename mpl::next< iter_15 > ::type iter_16;
typedef typename mpl::next< iter_16 > ::type iter_17;
typedef typename mpl::next< iter_17 > ::type iter_18;
public:
typedef typename detail::BOOST_FT_make_type(BOOST_FT_flags,BOOST_FT_cc_id,18) 
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
, typename mpl::deref< iter_11 > ::type
, typename mpl::deref< iter_12 > ::type
, typename mpl::deref< iter_13 > ::type
, typename mpl::deref< iter_14 > ::type
, typename mpl::deref< iter_15 > ::type
, typename mpl::deref< iter_16 > ::type
, typename mpl::deref< iter_17 > ::type
, typename mpl::deref< iter_18 > ::type
> ::type type;
};
};
template< typename R , typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9 , typename T10 , typename T11 , typename T12 , typename T13 , typename T14 , typename T15 , typename T16 , typename T17 , typename T18 >
struct BOOST_FT_make_type(BOOST_FT_flags,BOOST_FT_cc_id,19)
{
typedef BOOST_FT_syntax(BOOST_FT_cc,type BOOST_PP_EMPTY) (T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18 BOOST_FT_ell) BOOST_FT_cv ;
};
template< > 
struct synthesize_impl_o< BOOST_FT_flags, BOOST_FT_cc_id, 20 > 
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
typedef typename mpl::next< iter_10 > ::type iter_11;
typedef typename mpl::next< iter_11 > ::type iter_12;
typedef typename mpl::next< iter_12 > ::type iter_13;
typedef typename mpl::next< iter_13 > ::type iter_14;
typedef typename mpl::next< iter_14 > ::type iter_15;
typedef typename mpl::next< iter_15 > ::type iter_16;
typedef typename mpl::next< iter_16 > ::type iter_17;
typedef typename mpl::next< iter_17 > ::type iter_18;
typedef typename mpl::next< iter_18 > ::type iter_19;
public:
typedef typename detail::BOOST_FT_make_type(BOOST_FT_flags,BOOST_FT_cc_id,19) 
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
, typename mpl::deref< iter_11 > ::type
, typename mpl::deref< iter_12 > ::type
, typename mpl::deref< iter_13 > ::type
, typename mpl::deref< iter_14 > ::type
, typename mpl::deref< iter_15 > ::type
, typename mpl::deref< iter_16 > ::type
, typename mpl::deref< iter_17 > ::type
, typename mpl::deref< iter_18 > ::type
, typename mpl::deref< iter_19 > ::type
> ::type type;
};
};
template< typename R , typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9 , typename T10 , typename T11 , typename T12 , typename T13 , typename T14 , typename T15 , typename T16 , typename T17 , typename T18 , typename T19 >
struct BOOST_FT_make_type(BOOST_FT_flags,BOOST_FT_cc_id,20)
{
typedef BOOST_FT_syntax(BOOST_FT_cc,type BOOST_PP_EMPTY) (T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18 , T19 BOOST_FT_ell) BOOST_FT_cv ;
};
template< > 
struct synthesize_impl_o< BOOST_FT_flags, BOOST_FT_cc_id, 21 > 
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
typedef typename mpl::next< iter_10 > ::type iter_11;
typedef typename mpl::next< iter_11 > ::type iter_12;
typedef typename mpl::next< iter_12 > ::type iter_13;
typedef typename mpl::next< iter_13 > ::type iter_14;
typedef typename mpl::next< iter_14 > ::type iter_15;
typedef typename mpl::next< iter_15 > ::type iter_16;
typedef typename mpl::next< iter_16 > ::type iter_17;
typedef typename mpl::next< iter_17 > ::type iter_18;
typedef typename mpl::next< iter_18 > ::type iter_19;
typedef typename mpl::next< iter_19 > ::type iter_20;
public:
typedef typename detail::BOOST_FT_make_type(BOOST_FT_flags,BOOST_FT_cc_id,20) 
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
, typename mpl::deref< iter_11 > ::type
, typename mpl::deref< iter_12 > ::type
, typename mpl::deref< iter_13 > ::type
, typename mpl::deref< iter_14 > ::type
, typename mpl::deref< iter_15 > ::type
, typename mpl::deref< iter_16 > ::type
, typename mpl::deref< iter_17 > ::type
, typename mpl::deref< iter_18 > ::type
, typename mpl::deref< iter_19 > ::type
, typename mpl::deref< iter_20 > ::type
> ::type type;
};
};
# undef BOOST_FT_make_type
# undef BOOST_FT_make_type_impl


/* arity20_1.hpp
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
*/