
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