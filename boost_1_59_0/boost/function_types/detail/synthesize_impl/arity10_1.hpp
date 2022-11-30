
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
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
*/