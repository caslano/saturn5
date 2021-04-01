
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
n0Je0BijFV5mTnM/rOZWfgl+0FDVYQ/LyNjYH70D9t0gINCMaYd3s08QIEmfzSzgUR9w1oet9MVfh/Fs0nexRLQ3kR5tb8T/Hi9cvSC4U1g5O1obW/y0Ers/Th+NeUaGd0VXbqawO0tsoW2DjQ8oazy77QrkD4KoEDOFFzM6bOqzypOdWw4h+CcuRFUqa7iNDkx9pGqrzNJ1lGJTG0i1nVLf/myJtbqwRkpNQAaZNx/o92qAH+v7eNknhKq6hFT5q8nhtlpQcEENZO7Kd+7MLVnoeEpEi+ptLcWkV296G/oCPnPYVP3pcnlCBlxiNbb0iSyjd+FYvpeyZyqozXOTuFsfOdxDQqHdvNebO6uWI0SqZ+bKt196wnYpaYbEG5F9XpOwcrNCQ/ilXMjTsnSl14qrMDa15U257rk7HejRSqKHHFOdgN0xT8dW3XxIVTAI+mm86hppC/jN2fov+8JJ1vedpZ4i85ZcrDFDWiVpKIN+64X9XaePDmcg9emd0f0evJlMz7bXPVXQtnt+vImkfrt1Ioro2w2nBTi96Ng1hWSJz0CZG+vQaiDu9A==
*/