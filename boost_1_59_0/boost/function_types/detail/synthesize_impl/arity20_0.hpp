
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

# include <boost/function_types/detail/synthesize_impl/arity10_0.hpp>
# define BOOST_FT_make_type(flags,cc,arity) BOOST_FT_make_type_impl(flags,cc,arity)
# define BOOST_FT_make_type_impl(flags,cc,arity) make_type_ ## flags ## _ ## cc ## _ ## arity
template< typename R , typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9 , typename T10 >
struct BOOST_FT_make_type(BOOST_FT_flags,BOOST_FT_cc_id,11)
{
typedef BOOST_FT_syntax(BOOST_FT_cc,type BOOST_PP_EMPTY) (T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 BOOST_FT_ell) BOOST_FT_cv ;
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
, typename mpl::deref< iter_11 > ::type
> ::type type;
};
};
template< typename R , typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9 , typename T10 , typename T11 >
struct BOOST_FT_make_type(BOOST_FT_flags,BOOST_FT_cc_id,12)
{
typedef BOOST_FT_syntax(BOOST_FT_cc,type BOOST_PP_EMPTY) (T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 BOOST_FT_ell) BOOST_FT_cv ;
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
, typename mpl::deref< iter_11 > ::type
, typename mpl::deref< iter_12 > ::type
> ::type type;
};
};
template< typename R , typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9 , typename T10 , typename T11 , typename T12 >
struct BOOST_FT_make_type(BOOST_FT_flags,BOOST_FT_cc_id,13)
{
typedef BOOST_FT_syntax(BOOST_FT_cc,type BOOST_PP_EMPTY) (T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 BOOST_FT_ell) BOOST_FT_cv ;
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
, typename mpl::deref< iter_11 > ::type
, typename mpl::deref< iter_12 > ::type
, typename mpl::deref< iter_13 > ::type
> ::type type;
};
};
template< typename R , typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9 , typename T10 , typename T11 , typename T12 , typename T13 >
struct BOOST_FT_make_type(BOOST_FT_flags,BOOST_FT_cc_id,14)
{
typedef BOOST_FT_syntax(BOOST_FT_cc,type BOOST_PP_EMPTY) (T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 BOOST_FT_ell) BOOST_FT_cv ;
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
typedef BOOST_FT_syntax(BOOST_FT_cc,type BOOST_PP_EMPTY) (T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 BOOST_FT_ell) BOOST_FT_cv ;
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
typedef BOOST_FT_syntax(BOOST_FT_cc,type BOOST_PP_EMPTY) (T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 BOOST_FT_ell) BOOST_FT_cv ;
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
typedef BOOST_FT_syntax(BOOST_FT_cc,type BOOST_PP_EMPTY) (T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 BOOST_FT_ell) BOOST_FT_cv ;
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
typedef BOOST_FT_syntax(BOOST_FT_cc,type BOOST_PP_EMPTY) (T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 BOOST_FT_ell) BOOST_FT_cv ;
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
typedef BOOST_FT_syntax(BOOST_FT_cc,type BOOST_PP_EMPTY) (T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18 BOOST_FT_ell) BOOST_FT_cv ;
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
typedef BOOST_FT_syntax(BOOST_FT_cc,type BOOST_PP_EMPTY) (T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18 , T19 BOOST_FT_ell) BOOST_FT_cv ;
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


/* arity20_0.hpp
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
*/