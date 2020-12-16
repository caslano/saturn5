
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
6Niqf5PJHWY97N3th6mfBC7vvi/yoZcPhm7bfqCN7/ZnhiQ29V+1e2KnmDeihx3afmpPYu9H9DdW9Xp0/KVfPhj8sulQVtvMESMXto81qv7NT0TIoFBGB4SEhzMarh40gNEw9UDZP1QdHsFoSP+wATJVh4bfar3fajGzv3q/z6R47KtM9YvH9jTJ/6/fflJbHjtxZs2aaiioFS/fOjHLkG9/4202GQ3a4ix5+5n9U6rK2X72vVAeTy9816rm+/Frbn4/y4R1Ct9D4OeRf/ko5/u3fIjaRD7Pk/jTBD7nlTx98/MEc9fV7f4RlVCedpSueJ+YPw9H/JSyzqBivsJ9KS72ia9cJ3yPnfwDiZYR3/xsZ4UvtHM58adMdI4fQbT70+L+dnpfS3Qbxc/wp/trKI14Ho7ii9/b939G8fd18/36CjftXSnIT/xe/Gni/xTn+v7wKuIv9Rfk/+zN5V9N8dw9pc92rtP7Y5/n6LwEl4eoL8RfIAn3m5c5n2/wJzcvn0TxvGvfx0Pyqd99POVCfqLeqik/8Yknf/H+dp5fCvHVpO88P2n1zfPLdlM/M/lHUnqiPpQQ/6NOzvUrvUV+pW7qt578A4Ndt+dWsf48zTU3z2//c7eHLyJ+iPou4g/nt3Nj35wvEVUTn+PDIju+CPb933me5N/5pKexL+wrv6167OTXWekbPEajwcqo1mICpbBRMTEZqbhcWXbzW1E0Wm2hRaMt5mmaLDq9hXaJ2awaFi89Ld1+kw3/rrkNHTNz09F/fucJC698yd4exSEeBWNpmybpC5TwTt+jj0tLo9tx6GYch/My9vt86C4fCh8Tl4oSxtrHDwZqiJpxBuVL4dltGtimJsdTOaQvb+h1cOt1WRi21LTf6LQRWQmjU7DDLb2O4yEr/mVprAUh9ftOhxIP8sx1jjcYJzfpTGMWkw17lCjY9jfFII+haO+xwsszGO37qycaCuwf0uH3JrHmcnDT5mS7m3ao2/NV2tNeJvmmeMXXoLeK51esXDeJw3WTe5COOri1RhPbH87uymCjPlYAg42YxciggASE+tNuZqqf1VrzuXzHD6mj3KQsWdoccjPdZy6uD/ziFKi9vUHs6XL9kvdFGwoMIt9Jn8RAhgImK1nH+T5IUn328PtXIEHB0PCIdqtckk027Y5Ptu+Wb8cJ3o60PZUG51bRXx6cuwhPiiD6OzYkJSbwBSBw4JvyzYU2PS8J92cXng3PosMqDvVS/Nn3/Uhorv2tLvxJyyl98jdNwiZZBmdO4Vmbcd1XbKgm3kSwqDYcDUWcYNEJVZwwW/YXp0Qin0+LRH/HqRN/OI7yi9j5R5Md2teJb7PSNVVi/Jj0TNkeBFx3Gy5f59KfCuk6HkzEpT+rnNgfiXwuUld8khXl7Zov4J7bdEQ1FdsRwneZD+KCV5DOIIYdb7dDmT0NMbyYl8jnwnJVDlYfCu+AMc6XjRGfw4vYziLfvXKK4biSuueLyiryCZvdx6dxinu+VUP+/F5C3j7UFIKoa8IJmpij0Ym39XB/Jx+tpoCdMWMwIl5SJPKFTzYS31Ro1NFFOTbJjiiu+fba6/RYjsGIhF815ND/0O1NdB+T3sLvvud8Jx6Vl4K4uefK4hTUXGgxmziU8IefwyQdEU4J05qO6Mv95fpZ9NDPAr2O+8uVlWAL+WaJd5Hi/VSoP7u2Tyi9PZwNqVjxzyYxexHP79nHg7ULxgFT/NgBf9gwB/UpRNI5eslUoKeW4nyl8MVW9v1Xim0f57L6Ol+URv7kp4xnJIxnnJuM/AsLbBZkLNeE181tOa3Ol3UVFsDS9WabfDsWByzxnJ+u9vcQpmgsEnSfTnpzvabLuTAyNUw=
*/