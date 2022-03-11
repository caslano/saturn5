
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
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
*/