
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

# include <boost/function_types/detail/synthesize_impl/arity30_0.hpp>
# define BOOST_FT_make_type(flags,cc,arity) BOOST_FT_make_type_impl(flags,cc,arity)
# define BOOST_FT_make_type_impl(flags,cc,arity) make_type_ ## flags ## _ ## cc ## _ ## arity
template< typename R , typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9 , typename T10 , typename T11 , typename T12 , typename T13 , typename T14 , typename T15 , typename T16 , typename T17 , typename T18 , typename T19 , typename T20 , typename T21 , typename T22 , typename T23 , typename T24 , typename T25 , typename T26 , typename T27 , typename T28 , typename T29 , typename T30 >
struct BOOST_FT_make_type(BOOST_FT_flags,BOOST_FT_cc_id,31)
{
typedef BOOST_FT_syntax(BOOST_FT_cc,type BOOST_PP_EMPTY) (T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18 , T19 , T20 , T21 , T22 , T23 , T24 , T25 , T26 , T27 , T28 , T29 , T30 BOOST_FT_ell) BOOST_FT_cv ;
};
template< > 
struct synthesize_impl_o< BOOST_FT_flags, BOOST_FT_cc_id, 32 > 
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
typedef typename mpl::next< iter_20 > ::type iter_21;
typedef typename mpl::next< iter_21 > ::type iter_22;
typedef typename mpl::next< iter_22 > ::type iter_23;
typedef typename mpl::next< iter_23 > ::type iter_24;
typedef typename mpl::next< iter_24 > ::type iter_25;
typedef typename mpl::next< iter_25 > ::type iter_26;
typedef typename mpl::next< iter_26 > ::type iter_27;
typedef typename mpl::next< iter_27 > ::type iter_28;
typedef typename mpl::next< iter_28 > ::type iter_29;
typedef typename mpl::next< iter_29 > ::type iter_30;
typedef typename mpl::next< iter_30 > ::type iter_31;
public:
typedef typename detail::BOOST_FT_make_type(BOOST_FT_flags,BOOST_FT_cc_id,31) 
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
, typename mpl::deref< iter_21 > ::type
, typename mpl::deref< iter_22 > ::type
, typename mpl::deref< iter_23 > ::type
, typename mpl::deref< iter_24 > ::type
, typename mpl::deref< iter_25 > ::type
, typename mpl::deref< iter_26 > ::type
, typename mpl::deref< iter_27 > ::type
, typename mpl::deref< iter_28 > ::type
, typename mpl::deref< iter_29 > ::type
, typename mpl::deref< iter_30 > ::type
, typename mpl::deref< iter_31 > ::type
> ::type type;
};
};
template< typename R , typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9 , typename T10 , typename T11 , typename T12 , typename T13 , typename T14 , typename T15 , typename T16 , typename T17 , typename T18 , typename T19 , typename T20 , typename T21 , typename T22 , typename T23 , typename T24 , typename T25 , typename T26 , typename T27 , typename T28 , typename T29 , typename T30 , typename T31 >
struct BOOST_FT_make_type(BOOST_FT_flags,BOOST_FT_cc_id,32)
{
typedef BOOST_FT_syntax(BOOST_FT_cc,type BOOST_PP_EMPTY) (T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18 , T19 , T20 , T21 , T22 , T23 , T24 , T25 , T26 , T27 , T28 , T29 , T30 , T31 BOOST_FT_ell) BOOST_FT_cv ;
};
template< > 
struct synthesize_impl_o< BOOST_FT_flags, BOOST_FT_cc_id, 33 > 
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
typedef typename mpl::next< iter_20 > ::type iter_21;
typedef typename mpl::next< iter_21 > ::type iter_22;
typedef typename mpl::next< iter_22 > ::type iter_23;
typedef typename mpl::next< iter_23 > ::type iter_24;
typedef typename mpl::next< iter_24 > ::type iter_25;
typedef typename mpl::next< iter_25 > ::type iter_26;
typedef typename mpl::next< iter_26 > ::type iter_27;
typedef typename mpl::next< iter_27 > ::type iter_28;
typedef typename mpl::next< iter_28 > ::type iter_29;
typedef typename mpl::next< iter_29 > ::type iter_30;
typedef typename mpl::next< iter_30 > ::type iter_31;
typedef typename mpl::next< iter_31 > ::type iter_32;
public:
typedef typename detail::BOOST_FT_make_type(BOOST_FT_flags,BOOST_FT_cc_id,32) 
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
, typename mpl::deref< iter_21 > ::type
, typename mpl::deref< iter_22 > ::type
, typename mpl::deref< iter_23 > ::type
, typename mpl::deref< iter_24 > ::type
, typename mpl::deref< iter_25 > ::type
, typename mpl::deref< iter_26 > ::type
, typename mpl::deref< iter_27 > ::type
, typename mpl::deref< iter_28 > ::type
, typename mpl::deref< iter_29 > ::type
, typename mpl::deref< iter_30 > ::type
, typename mpl::deref< iter_31 > ::type
, typename mpl::deref< iter_32 > ::type
> ::type type;
};
};
template< typename R , typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9 , typename T10 , typename T11 , typename T12 , typename T13 , typename T14 , typename T15 , typename T16 , typename T17 , typename T18 , typename T19 , typename T20 , typename T21 , typename T22 , typename T23 , typename T24 , typename T25 , typename T26 , typename T27 , typename T28 , typename T29 , typename T30 , typename T31 , typename T32 >
struct BOOST_FT_make_type(BOOST_FT_flags,BOOST_FT_cc_id,33)
{
typedef BOOST_FT_syntax(BOOST_FT_cc,type BOOST_PP_EMPTY) (T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18 , T19 , T20 , T21 , T22 , T23 , T24 , T25 , T26 , T27 , T28 , T29 , T30 , T31 , T32 BOOST_FT_ell) BOOST_FT_cv ;
};
template< > 
struct synthesize_impl_o< BOOST_FT_flags, BOOST_FT_cc_id, 34 > 
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
typedef typename mpl::next< iter_20 > ::type iter_21;
typedef typename mpl::next< iter_21 > ::type iter_22;
typedef typename mpl::next< iter_22 > ::type iter_23;
typedef typename mpl::next< iter_23 > ::type iter_24;
typedef typename mpl::next< iter_24 > ::type iter_25;
typedef typename mpl::next< iter_25 > ::type iter_26;
typedef typename mpl::next< iter_26 > ::type iter_27;
typedef typename mpl::next< iter_27 > ::type iter_28;
typedef typename mpl::next< iter_28 > ::type iter_29;
typedef typename mpl::next< iter_29 > ::type iter_30;
typedef typename mpl::next< iter_30 > ::type iter_31;
typedef typename mpl::next< iter_31 > ::type iter_32;
typedef typename mpl::next< iter_32 > ::type iter_33;
public:
typedef typename detail::BOOST_FT_make_type(BOOST_FT_flags,BOOST_FT_cc_id,33) 
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
, typename mpl::deref< iter_21 > ::type
, typename mpl::deref< iter_22 > ::type
, typename mpl::deref< iter_23 > ::type
, typename mpl::deref< iter_24 > ::type
, typename mpl::deref< iter_25 > ::type
, typename mpl::deref< iter_26 > ::type
, typename mpl::deref< iter_27 > ::type
, typename mpl::deref< iter_28 > ::type
, typename mpl::deref< iter_29 > ::type
, typename mpl::deref< iter_30 > ::type
, typename mpl::deref< iter_31 > ::type
, typename mpl::deref< iter_32 > ::type
, typename mpl::deref< iter_33 > ::type
> ::type type;
};
};
template< typename R , typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9 , typename T10 , typename T11 , typename T12 , typename T13 , typename T14 , typename T15 , typename T16 , typename T17 , typename T18 , typename T19 , typename T20 , typename T21 , typename T22 , typename T23 , typename T24 , typename T25 , typename T26 , typename T27 , typename T28 , typename T29 , typename T30 , typename T31 , typename T32 , typename T33 >
struct BOOST_FT_make_type(BOOST_FT_flags,BOOST_FT_cc_id,34)
{
typedef BOOST_FT_syntax(BOOST_FT_cc,type BOOST_PP_EMPTY) (T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18 , T19 , T20 , T21 , T22 , T23 , T24 , T25 , T26 , T27 , T28 , T29 , T30 , T31 , T32 , T33 BOOST_FT_ell) BOOST_FT_cv ;
};
template< > 
struct synthesize_impl_o< BOOST_FT_flags, BOOST_FT_cc_id, 35 > 
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
typedef typename mpl::next< iter_20 > ::type iter_21;
typedef typename mpl::next< iter_21 > ::type iter_22;
typedef typename mpl::next< iter_22 > ::type iter_23;
typedef typename mpl::next< iter_23 > ::type iter_24;
typedef typename mpl::next< iter_24 > ::type iter_25;
typedef typename mpl::next< iter_25 > ::type iter_26;
typedef typename mpl::next< iter_26 > ::type iter_27;
typedef typename mpl::next< iter_27 > ::type iter_28;
typedef typename mpl::next< iter_28 > ::type iter_29;
typedef typename mpl::next< iter_29 > ::type iter_30;
typedef typename mpl::next< iter_30 > ::type iter_31;
typedef typename mpl::next< iter_31 > ::type iter_32;
typedef typename mpl::next< iter_32 > ::type iter_33;
typedef typename mpl::next< iter_33 > ::type iter_34;
public:
typedef typename detail::BOOST_FT_make_type(BOOST_FT_flags,BOOST_FT_cc_id,34) 
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
, typename mpl::deref< iter_21 > ::type
, typename mpl::deref< iter_22 > ::type
, typename mpl::deref< iter_23 > ::type
, typename mpl::deref< iter_24 > ::type
, typename mpl::deref< iter_25 > ::type
, typename mpl::deref< iter_26 > ::type
, typename mpl::deref< iter_27 > ::type
, typename mpl::deref< iter_28 > ::type
, typename mpl::deref< iter_29 > ::type
, typename mpl::deref< iter_30 > ::type
, typename mpl::deref< iter_31 > ::type
, typename mpl::deref< iter_32 > ::type
, typename mpl::deref< iter_33 > ::type
, typename mpl::deref< iter_34 > ::type
> ::type type;
};
};
template< typename R , typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9 , typename T10 , typename T11 , typename T12 , typename T13 , typename T14 , typename T15 , typename T16 , typename T17 , typename T18 , typename T19 , typename T20 , typename T21 , typename T22 , typename T23 , typename T24 , typename T25 , typename T26 , typename T27 , typename T28 , typename T29 , typename T30 , typename T31 , typename T32 , typename T33 , typename T34 >
struct BOOST_FT_make_type(BOOST_FT_flags,BOOST_FT_cc_id,35)
{
typedef BOOST_FT_syntax(BOOST_FT_cc,type BOOST_PP_EMPTY) (T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18 , T19 , T20 , T21 , T22 , T23 , T24 , T25 , T26 , T27 , T28 , T29 , T30 , T31 , T32 , T33 , T34 BOOST_FT_ell) BOOST_FT_cv ;
};
template< > 
struct synthesize_impl_o< BOOST_FT_flags, BOOST_FT_cc_id, 36 > 
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
typedef typename mpl::next< iter_20 > ::type iter_21;
typedef typename mpl::next< iter_21 > ::type iter_22;
typedef typename mpl::next< iter_22 > ::type iter_23;
typedef typename mpl::next< iter_23 > ::type iter_24;
typedef typename mpl::next< iter_24 > ::type iter_25;
typedef typename mpl::next< iter_25 > ::type iter_26;
typedef typename mpl::next< iter_26 > ::type iter_27;
typedef typename mpl::next< iter_27 > ::type iter_28;
typedef typename mpl::next< iter_28 > ::type iter_29;
typedef typename mpl::next< iter_29 > ::type iter_30;
typedef typename mpl::next< iter_30 > ::type iter_31;
typedef typename mpl::next< iter_31 > ::type iter_32;
typedef typename mpl::next< iter_32 > ::type iter_33;
typedef typename mpl::next< iter_33 > ::type iter_34;
typedef typename mpl::next< iter_34 > ::type iter_35;
public:
typedef typename detail::BOOST_FT_make_type(BOOST_FT_flags,BOOST_FT_cc_id,35) 
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
, typename mpl::deref< iter_21 > ::type
, typename mpl::deref< iter_22 > ::type
, typename mpl::deref< iter_23 > ::type
, typename mpl::deref< iter_24 > ::type
, typename mpl::deref< iter_25 > ::type
, typename mpl::deref< iter_26 > ::type
, typename mpl::deref< iter_27 > ::type
, typename mpl::deref< iter_28 > ::type
, typename mpl::deref< iter_29 > ::type
, typename mpl::deref< iter_30 > ::type
, typename mpl::deref< iter_31 > ::type
, typename mpl::deref< iter_32 > ::type
, typename mpl::deref< iter_33 > ::type
, typename mpl::deref< iter_34 > ::type
, typename mpl::deref< iter_35 > ::type
> ::type type;
};
};
template< typename R , typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9 , typename T10 , typename T11 , typename T12 , typename T13 , typename T14 , typename T15 , typename T16 , typename T17 , typename T18 , typename T19 , typename T20 , typename T21 , typename T22 , typename T23 , typename T24 , typename T25 , typename T26 , typename T27 , typename T28 , typename T29 , typename T30 , typename T31 , typename T32 , typename T33 , typename T34 , typename T35 >
struct BOOST_FT_make_type(BOOST_FT_flags,BOOST_FT_cc_id,36)
{
typedef BOOST_FT_syntax(BOOST_FT_cc,type BOOST_PP_EMPTY) (T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18 , T19 , T20 , T21 , T22 , T23 , T24 , T25 , T26 , T27 , T28 , T29 , T30 , T31 , T32 , T33 , T34 , T35 BOOST_FT_ell) BOOST_FT_cv ;
};
template< > 
struct synthesize_impl_o< BOOST_FT_flags, BOOST_FT_cc_id, 37 > 
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
typedef typename mpl::next< iter_20 > ::type iter_21;
typedef typename mpl::next< iter_21 > ::type iter_22;
typedef typename mpl::next< iter_22 > ::type iter_23;
typedef typename mpl::next< iter_23 > ::type iter_24;
typedef typename mpl::next< iter_24 > ::type iter_25;
typedef typename mpl::next< iter_25 > ::type iter_26;
typedef typename mpl::next< iter_26 > ::type iter_27;
typedef typename mpl::next< iter_27 > ::type iter_28;
typedef typename mpl::next< iter_28 > ::type iter_29;
typedef typename mpl::next< iter_29 > ::type iter_30;
typedef typename mpl::next< iter_30 > ::type iter_31;
typedef typename mpl::next< iter_31 > ::type iter_32;
typedef typename mpl::next< iter_32 > ::type iter_33;
typedef typename mpl::next< iter_33 > ::type iter_34;
typedef typename mpl::next< iter_34 > ::type iter_35;
typedef typename mpl::next< iter_35 > ::type iter_36;
public:
typedef typename detail::BOOST_FT_make_type(BOOST_FT_flags,BOOST_FT_cc_id,36) 
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
, typename mpl::deref< iter_21 > ::type
, typename mpl::deref< iter_22 > ::type
, typename mpl::deref< iter_23 > ::type
, typename mpl::deref< iter_24 > ::type
, typename mpl::deref< iter_25 > ::type
, typename mpl::deref< iter_26 > ::type
, typename mpl::deref< iter_27 > ::type
, typename mpl::deref< iter_28 > ::type
, typename mpl::deref< iter_29 > ::type
, typename mpl::deref< iter_30 > ::type
, typename mpl::deref< iter_31 > ::type
, typename mpl::deref< iter_32 > ::type
, typename mpl::deref< iter_33 > ::type
, typename mpl::deref< iter_34 > ::type
, typename mpl::deref< iter_35 > ::type
, typename mpl::deref< iter_36 > ::type
> ::type type;
};
};
template< typename R , typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9 , typename T10 , typename T11 , typename T12 , typename T13 , typename T14 , typename T15 , typename T16 , typename T17 , typename T18 , typename T19 , typename T20 , typename T21 , typename T22 , typename T23 , typename T24 , typename T25 , typename T26 , typename T27 , typename T28 , typename T29 , typename T30 , typename T31 , typename T32 , typename T33 , typename T34 , typename T35 , typename T36 >
struct BOOST_FT_make_type(BOOST_FT_flags,BOOST_FT_cc_id,37)
{
typedef BOOST_FT_syntax(BOOST_FT_cc,type BOOST_PP_EMPTY) (T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18 , T19 , T20 , T21 , T22 , T23 , T24 , T25 , T26 , T27 , T28 , T29 , T30 , T31 , T32 , T33 , T34 , T35 , T36 BOOST_FT_ell) BOOST_FT_cv ;
};
template< > 
struct synthesize_impl_o< BOOST_FT_flags, BOOST_FT_cc_id, 38 > 
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
typedef typename mpl::next< iter_20 > ::type iter_21;
typedef typename mpl::next< iter_21 > ::type iter_22;
typedef typename mpl::next< iter_22 > ::type iter_23;
typedef typename mpl::next< iter_23 > ::type iter_24;
typedef typename mpl::next< iter_24 > ::type iter_25;
typedef typename mpl::next< iter_25 > ::type iter_26;
typedef typename mpl::next< iter_26 > ::type iter_27;
typedef typename mpl::next< iter_27 > ::type iter_28;
typedef typename mpl::next< iter_28 > ::type iter_29;
typedef typename mpl::next< iter_29 > ::type iter_30;
typedef typename mpl::next< iter_30 > ::type iter_31;
typedef typename mpl::next< iter_31 > ::type iter_32;
typedef typename mpl::next< iter_32 > ::type iter_33;
typedef typename mpl::next< iter_33 > ::type iter_34;
typedef typename mpl::next< iter_34 > ::type iter_35;
typedef typename mpl::next< iter_35 > ::type iter_36;
typedef typename mpl::next< iter_36 > ::type iter_37;
public:
typedef typename detail::BOOST_FT_make_type(BOOST_FT_flags,BOOST_FT_cc_id,37) 
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
, typename mpl::deref< iter_21 > ::type
, typename mpl::deref< iter_22 > ::type
, typename mpl::deref< iter_23 > ::type
, typename mpl::deref< iter_24 > ::type
, typename mpl::deref< iter_25 > ::type
, typename mpl::deref< iter_26 > ::type
, typename mpl::deref< iter_27 > ::type
, typename mpl::deref< iter_28 > ::type
, typename mpl::deref< iter_29 > ::type
, typename mpl::deref< iter_30 > ::type
, typename mpl::deref< iter_31 > ::type
, typename mpl::deref< iter_32 > ::type
, typename mpl::deref< iter_33 > ::type
, typename mpl::deref< iter_34 > ::type
, typename mpl::deref< iter_35 > ::type
, typename mpl::deref< iter_36 > ::type
, typename mpl::deref< iter_37 > ::type
> ::type type;
};
};
template< typename R , typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9 , typename T10 , typename T11 , typename T12 , typename T13 , typename T14 , typename T15 , typename T16 , typename T17 , typename T18 , typename T19 , typename T20 , typename T21 , typename T22 , typename T23 , typename T24 , typename T25 , typename T26 , typename T27 , typename T28 , typename T29 , typename T30 , typename T31 , typename T32 , typename T33 , typename T34 , typename T35 , typename T36 , typename T37 >
struct BOOST_FT_make_type(BOOST_FT_flags,BOOST_FT_cc_id,38)
{
typedef BOOST_FT_syntax(BOOST_FT_cc,type BOOST_PP_EMPTY) (T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18 , T19 , T20 , T21 , T22 , T23 , T24 , T25 , T26 , T27 , T28 , T29 , T30 , T31 , T32 , T33 , T34 , T35 , T36 , T37 BOOST_FT_ell) BOOST_FT_cv ;
};
template< > 
struct synthesize_impl_o< BOOST_FT_flags, BOOST_FT_cc_id, 39 > 
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
typedef typename mpl::next< iter_20 > ::type iter_21;
typedef typename mpl::next< iter_21 > ::type iter_22;
typedef typename mpl::next< iter_22 > ::type iter_23;
typedef typename mpl::next< iter_23 > ::type iter_24;
typedef typename mpl::next< iter_24 > ::type iter_25;
typedef typename mpl::next< iter_25 > ::type iter_26;
typedef typename mpl::next< iter_26 > ::type iter_27;
typedef typename mpl::next< iter_27 > ::type iter_28;
typedef typename mpl::next< iter_28 > ::type iter_29;
typedef typename mpl::next< iter_29 > ::type iter_30;
typedef typename mpl::next< iter_30 > ::type iter_31;
typedef typename mpl::next< iter_31 > ::type iter_32;
typedef typename mpl::next< iter_32 > ::type iter_33;
typedef typename mpl::next< iter_33 > ::type iter_34;
typedef typename mpl::next< iter_34 > ::type iter_35;
typedef typename mpl::next< iter_35 > ::type iter_36;
typedef typename mpl::next< iter_36 > ::type iter_37;
typedef typename mpl::next< iter_37 > ::type iter_38;
public:
typedef typename detail::BOOST_FT_make_type(BOOST_FT_flags,BOOST_FT_cc_id,38) 
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
, typename mpl::deref< iter_21 > ::type
, typename mpl::deref< iter_22 > ::type
, typename mpl::deref< iter_23 > ::type
, typename mpl::deref< iter_24 > ::type
, typename mpl::deref< iter_25 > ::type
, typename mpl::deref< iter_26 > ::type
, typename mpl::deref< iter_27 > ::type
, typename mpl::deref< iter_28 > ::type
, typename mpl::deref< iter_29 > ::type
, typename mpl::deref< iter_30 > ::type
, typename mpl::deref< iter_31 > ::type
, typename mpl::deref< iter_32 > ::type
, typename mpl::deref< iter_33 > ::type
, typename mpl::deref< iter_34 > ::type
, typename mpl::deref< iter_35 > ::type
, typename mpl::deref< iter_36 > ::type
, typename mpl::deref< iter_37 > ::type
, typename mpl::deref< iter_38 > ::type
> ::type type;
};
};
template< typename R , typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9 , typename T10 , typename T11 , typename T12 , typename T13 , typename T14 , typename T15 , typename T16 , typename T17 , typename T18 , typename T19 , typename T20 , typename T21 , typename T22 , typename T23 , typename T24 , typename T25 , typename T26 , typename T27 , typename T28 , typename T29 , typename T30 , typename T31 , typename T32 , typename T33 , typename T34 , typename T35 , typename T36 , typename T37 , typename T38 >
struct BOOST_FT_make_type(BOOST_FT_flags,BOOST_FT_cc_id,39)
{
typedef BOOST_FT_syntax(BOOST_FT_cc,type BOOST_PP_EMPTY) (T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18 , T19 , T20 , T21 , T22 , T23 , T24 , T25 , T26 , T27 , T28 , T29 , T30 , T31 , T32 , T33 , T34 , T35 , T36 , T37 , T38 BOOST_FT_ell) BOOST_FT_cv ;
};
template< > 
struct synthesize_impl_o< BOOST_FT_flags, BOOST_FT_cc_id, 40 > 
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
typedef typename mpl::next< iter_20 > ::type iter_21;
typedef typename mpl::next< iter_21 > ::type iter_22;
typedef typename mpl::next< iter_22 > ::type iter_23;
typedef typename mpl::next< iter_23 > ::type iter_24;
typedef typename mpl::next< iter_24 > ::type iter_25;
typedef typename mpl::next< iter_25 > ::type iter_26;
typedef typename mpl::next< iter_26 > ::type iter_27;
typedef typename mpl::next< iter_27 > ::type iter_28;
typedef typename mpl::next< iter_28 > ::type iter_29;
typedef typename mpl::next< iter_29 > ::type iter_30;
typedef typename mpl::next< iter_30 > ::type iter_31;
typedef typename mpl::next< iter_31 > ::type iter_32;
typedef typename mpl::next< iter_32 > ::type iter_33;
typedef typename mpl::next< iter_33 > ::type iter_34;
typedef typename mpl::next< iter_34 > ::type iter_35;
typedef typename mpl::next< iter_35 > ::type iter_36;
typedef typename mpl::next< iter_36 > ::type iter_37;
typedef typename mpl::next< iter_37 > ::type iter_38;
typedef typename mpl::next< iter_38 > ::type iter_39;
public:
typedef typename detail::BOOST_FT_make_type(BOOST_FT_flags,BOOST_FT_cc_id,39) 
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
, typename mpl::deref< iter_21 > ::type
, typename mpl::deref< iter_22 > ::type
, typename mpl::deref< iter_23 > ::type
, typename mpl::deref< iter_24 > ::type
, typename mpl::deref< iter_25 > ::type
, typename mpl::deref< iter_26 > ::type
, typename mpl::deref< iter_27 > ::type
, typename mpl::deref< iter_28 > ::type
, typename mpl::deref< iter_29 > ::type
, typename mpl::deref< iter_30 > ::type
, typename mpl::deref< iter_31 > ::type
, typename mpl::deref< iter_32 > ::type
, typename mpl::deref< iter_33 > ::type
, typename mpl::deref< iter_34 > ::type
, typename mpl::deref< iter_35 > ::type
, typename mpl::deref< iter_36 > ::type
, typename mpl::deref< iter_37 > ::type
, typename mpl::deref< iter_38 > ::type
, typename mpl::deref< iter_39 > ::type
> ::type type;
};
};
template< typename R , typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9 , typename T10 , typename T11 , typename T12 , typename T13 , typename T14 , typename T15 , typename T16 , typename T17 , typename T18 , typename T19 , typename T20 , typename T21 , typename T22 , typename T23 , typename T24 , typename T25 , typename T26 , typename T27 , typename T28 , typename T29 , typename T30 , typename T31 , typename T32 , typename T33 , typename T34 , typename T35 , typename T36 , typename T37 , typename T38 , typename T39 >
struct BOOST_FT_make_type(BOOST_FT_flags,BOOST_FT_cc_id,40)
{
typedef BOOST_FT_syntax(BOOST_FT_cc,type BOOST_PP_EMPTY) (T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18 , T19 , T20 , T21 , T22 , T23 , T24 , T25 , T26 , T27 , T28 , T29 , T30 , T31 , T32 , T33 , T34 , T35 , T36 , T37 , T38 , T39 BOOST_FT_ell) BOOST_FT_cv ;
};
template< > 
struct synthesize_impl_o< BOOST_FT_flags, BOOST_FT_cc_id, 41 > 
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
typedef typename mpl::next< iter_20 > ::type iter_21;
typedef typename mpl::next< iter_21 > ::type iter_22;
typedef typename mpl::next< iter_22 > ::type iter_23;
typedef typename mpl::next< iter_23 > ::type iter_24;
typedef typename mpl::next< iter_24 > ::type iter_25;
typedef typename mpl::next< iter_25 > ::type iter_26;
typedef typename mpl::next< iter_26 > ::type iter_27;
typedef typename mpl::next< iter_27 > ::type iter_28;
typedef typename mpl::next< iter_28 > ::type iter_29;
typedef typename mpl::next< iter_29 > ::type iter_30;
typedef typename mpl::next< iter_30 > ::type iter_31;
typedef typename mpl::next< iter_31 > ::type iter_32;
typedef typename mpl::next< iter_32 > ::type iter_33;
typedef typename mpl::next< iter_33 > ::type iter_34;
typedef typename mpl::next< iter_34 > ::type iter_35;
typedef typename mpl::next< iter_35 > ::type iter_36;
typedef typename mpl::next< iter_36 > ::type iter_37;
typedef typename mpl::next< iter_37 > ::type iter_38;
typedef typename mpl::next< iter_38 > ::type iter_39;
typedef typename mpl::next< iter_39 > ::type iter_40;
public:
typedef typename detail::BOOST_FT_make_type(BOOST_FT_flags,BOOST_FT_cc_id,40) 
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
, typename mpl::deref< iter_21 > ::type
, typename mpl::deref< iter_22 > ::type
, typename mpl::deref< iter_23 > ::type
, typename mpl::deref< iter_24 > ::type
, typename mpl::deref< iter_25 > ::type
, typename mpl::deref< iter_26 > ::type
, typename mpl::deref< iter_27 > ::type
, typename mpl::deref< iter_28 > ::type
, typename mpl::deref< iter_29 > ::type
, typename mpl::deref< iter_30 > ::type
, typename mpl::deref< iter_31 > ::type
, typename mpl::deref< iter_32 > ::type
, typename mpl::deref< iter_33 > ::type
, typename mpl::deref< iter_34 > ::type
, typename mpl::deref< iter_35 > ::type
, typename mpl::deref< iter_36 > ::type
, typename mpl::deref< iter_37 > ::type
, typename mpl::deref< iter_38 > ::type
, typename mpl::deref< iter_39 > ::type
, typename mpl::deref< iter_40 > ::type
> ::type type;
};
};
# undef BOOST_FT_make_type
# undef BOOST_FT_make_type_impl


/* arity40_0.hpp
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
*/