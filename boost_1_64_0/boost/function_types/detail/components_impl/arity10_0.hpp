
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

template< typename R, typename L>
struct components_impl<BOOST_FT_syntax(BOOST_FT_cc, BOOST_PP_EMPTY) (BOOST_FT_nullary_param BOOST_FT_ell) BOOST_FT_cv, L>
{
typedef encode_bits<BOOST_FT_flags,BOOST_FT_cc_id> bits;
typedef constant<BOOST_FT_full_mask> mask;
typedef function_types::components<BOOST_FT_syntax(BOOST_FT_cc, BOOST_PP_EMPTY) (BOOST_FT_nullary_param BOOST_FT_ell) BOOST_FT_cv, L> type;
typedef components_mpl_sequence_tag tag;
typedef mpl::integral_c<std::size_t,0> function_arity;
typedef mpl::vector1< R BOOST_FT_nullary_param > types;
};
template< typename R , typename T0, typename L>
struct components_impl<BOOST_FT_syntax(BOOST_FT_cc, BOOST_PP_EMPTY) (T0 BOOST_FT_ell) BOOST_FT_cv, L>
{
typedef encode_bits<BOOST_FT_flags,BOOST_FT_cc_id> bits;
typedef constant<BOOST_FT_full_mask> mask;
typedef function_types::components<BOOST_FT_syntax(BOOST_FT_cc, BOOST_PP_EMPTY) (T0 BOOST_FT_ell) BOOST_FT_cv, L> type;
typedef components_mpl_sequence_tag tag;
typedef mpl::integral_c<std::size_t,1> function_arity;
typedef mpl::vector2< R , T0 > types;
};
template< typename R , typename T0 , typename T1, typename L>
struct components_impl<BOOST_FT_syntax(BOOST_FT_cc, BOOST_PP_EMPTY) (T0 , T1 BOOST_FT_ell) BOOST_FT_cv, L>
{
typedef encode_bits<BOOST_FT_flags,BOOST_FT_cc_id> bits;
typedef constant<BOOST_FT_full_mask> mask;
typedef function_types::components<BOOST_FT_syntax(BOOST_FT_cc, BOOST_PP_EMPTY) (T0 , T1 BOOST_FT_ell) BOOST_FT_cv, L> type;
typedef components_mpl_sequence_tag tag;
typedef mpl::integral_c<std::size_t,2> function_arity;
typedef mpl::vector3< R , T0 , T1 > types;
};
template< typename R , typename T0 , typename T1 , typename T2, typename L>
struct components_impl<BOOST_FT_syntax(BOOST_FT_cc, BOOST_PP_EMPTY) (T0 , T1 , T2 BOOST_FT_ell) BOOST_FT_cv, L>
{
typedef encode_bits<BOOST_FT_flags,BOOST_FT_cc_id> bits;
typedef constant<BOOST_FT_full_mask> mask;
typedef function_types::components<BOOST_FT_syntax(BOOST_FT_cc, BOOST_PP_EMPTY) (T0 , T1 , T2 BOOST_FT_ell) BOOST_FT_cv, L> type;
typedef components_mpl_sequence_tag tag;
typedef mpl::integral_c<std::size_t,3> function_arity;
typedef mpl::vector4< R , T0 , T1 , T2 > types;
};
template< typename R , typename T0 , typename T1 , typename T2 , typename T3, typename L>
struct components_impl<BOOST_FT_syntax(BOOST_FT_cc, BOOST_PP_EMPTY) (T0 , T1 , T2 , T3 BOOST_FT_ell) BOOST_FT_cv, L>
{
typedef encode_bits<BOOST_FT_flags,BOOST_FT_cc_id> bits;
typedef constant<BOOST_FT_full_mask> mask;
typedef function_types::components<BOOST_FT_syntax(BOOST_FT_cc, BOOST_PP_EMPTY) (T0 , T1 , T2 , T3 BOOST_FT_ell) BOOST_FT_cv, L> type;
typedef components_mpl_sequence_tag tag;
typedef mpl::integral_c<std::size_t,4> function_arity;
typedef mpl::vector5< R , T0 , T1 , T2 , T3 > types;
};
template< typename R , typename T0 , typename T1 , typename T2 , typename T3 , typename T4, typename L>
struct components_impl<BOOST_FT_syntax(BOOST_FT_cc, BOOST_PP_EMPTY) (T0 , T1 , T2 , T3 , T4 BOOST_FT_ell) BOOST_FT_cv, L>
{
typedef encode_bits<BOOST_FT_flags,BOOST_FT_cc_id> bits;
typedef constant<BOOST_FT_full_mask> mask;
typedef function_types::components<BOOST_FT_syntax(BOOST_FT_cc, BOOST_PP_EMPTY) (T0 , T1 , T2 , T3 , T4 BOOST_FT_ell) BOOST_FT_cv, L> type;
typedef components_mpl_sequence_tag tag;
typedef mpl::integral_c<std::size_t,5> function_arity;
typedef mpl::vector6< R , T0 , T1 , T2 , T3 , T4 > types;
};
template< typename R , typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5, typename L>
struct components_impl<BOOST_FT_syntax(BOOST_FT_cc, BOOST_PP_EMPTY) (T0 , T1 , T2 , T3 , T4 , T5 BOOST_FT_ell) BOOST_FT_cv, L>
{
typedef encode_bits<BOOST_FT_flags,BOOST_FT_cc_id> bits;
typedef constant<BOOST_FT_full_mask> mask;
typedef function_types::components<BOOST_FT_syntax(BOOST_FT_cc, BOOST_PP_EMPTY) (T0 , T1 , T2 , T3 , T4 , T5 BOOST_FT_ell) BOOST_FT_cv, L> type;
typedef components_mpl_sequence_tag tag;
typedef mpl::integral_c<std::size_t,6> function_arity;
typedef mpl::vector7< R , T0 , T1 , T2 , T3 , T4 , T5 > types;
};
template< typename R , typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6, typename L>
struct components_impl<BOOST_FT_syntax(BOOST_FT_cc, BOOST_PP_EMPTY) (T0 , T1 , T2 , T3 , T4 , T5 , T6 BOOST_FT_ell) BOOST_FT_cv, L>
{
typedef encode_bits<BOOST_FT_flags,BOOST_FT_cc_id> bits;
typedef constant<BOOST_FT_full_mask> mask;
typedef function_types::components<BOOST_FT_syntax(BOOST_FT_cc, BOOST_PP_EMPTY) (T0 , T1 , T2 , T3 , T4 , T5 , T6 BOOST_FT_ell) BOOST_FT_cv, L> type;
typedef components_mpl_sequence_tag tag;
typedef mpl::integral_c<std::size_t,7> function_arity;
typedef mpl::vector8< R , T0 , T1 , T2 , T3 , T4 , T5 , T6 > types;
};
template< typename R , typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7, typename L>
struct components_impl<BOOST_FT_syntax(BOOST_FT_cc, BOOST_PP_EMPTY) (T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 BOOST_FT_ell) BOOST_FT_cv, L>
{
typedef encode_bits<BOOST_FT_flags,BOOST_FT_cc_id> bits;
typedef constant<BOOST_FT_full_mask> mask;
typedef function_types::components<BOOST_FT_syntax(BOOST_FT_cc, BOOST_PP_EMPTY) (T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 BOOST_FT_ell) BOOST_FT_cv, L> type;
typedef components_mpl_sequence_tag tag;
typedef mpl::integral_c<std::size_t,8> function_arity;
typedef mpl::vector9< R , T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 > types;
};
template< typename R , typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8, typename L>
struct components_impl<BOOST_FT_syntax(BOOST_FT_cc, BOOST_PP_EMPTY) (T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 BOOST_FT_ell) BOOST_FT_cv, L>
{
typedef encode_bits<BOOST_FT_flags,BOOST_FT_cc_id> bits;
typedef constant<BOOST_FT_full_mask> mask;
typedef function_types::components<BOOST_FT_syntax(BOOST_FT_cc, BOOST_PP_EMPTY) (T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 BOOST_FT_ell) BOOST_FT_cv, L> type;
typedef components_mpl_sequence_tag tag;
typedef mpl::integral_c<std::size_t,9> function_arity;
typedef mpl::vector10< R , T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 > types;
};
template< typename R , typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9, typename L>
struct components_impl<BOOST_FT_syntax(BOOST_FT_cc, BOOST_PP_EMPTY) (T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 BOOST_FT_ell) BOOST_FT_cv, L>
{
typedef encode_bits<BOOST_FT_flags,BOOST_FT_cc_id> bits;
typedef constant<BOOST_FT_full_mask> mask;
typedef function_types::components<BOOST_FT_syntax(BOOST_FT_cc, BOOST_PP_EMPTY) (T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 BOOST_FT_ell) BOOST_FT_cv, L> type;
typedef components_mpl_sequence_tag tag;
typedef mpl::integral_c<std::size_t,10> function_arity;
typedef mpl::vector11< R , T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 > types;
};


/* arity10_0.hpp
ivLk9DTX1ybF5treB+Vn8XqXKZcMKP8Dtp/a1LQ6KfeoU1Z2Wd6qprrMbdV3pqY8Nsx5nFw28lGjq9ocx8nWubfv0Aik/TXmOs4PLD95BS7ZHF/DMr6UMud+S7mZi65Rx30zxTwtearZxXars+WxdfJsePbMuR0fY+bevrZx0VxthgF/SflHTJ/2AfsrDxuSejbjG9myTO8FSDnzcW9X1p9ca/bBXp+MPDo03XkTJ062vsUnL2p0i4C/qiOm57gfyNuEM2qmV7lpNrF49+f+/2+XvjnJe25HNMtLGtbn8uFNLPe3rLmC7+EzPslHbUl+M6ZNr5oRdLmfSZ61ixbX1fpt2ML6px1ZQxG6DVt0Gi9XLF+MISlfXsQ6IgjM+NlfuC78uLo+MPtR0dC4rEs/4crOx0kpOcbfme3k3rRqyVFLjlpdv7Se/oXyKO2Dt5vDGK/TeTrhw8vT18SDTufuw8tz/UHt6o7H58vqyj+1QRJyk0zK8WV05Z+2upaeVvOvmVOdeX9qotu2cXWDi8lNlM/dDEv7l2Y3XCb/zBQtiSGTz9Q1nd7JrG/qEEdKWq3mRzNhO2kptH1mY2znWkSH9r5oxSLv79CmOBD8SdtpWLwgyX96TY36Fyxa0MG/uLFRj2NRY+J3R145Lil3URN+d+QI1Mu4itpm955+fVMy++iUD1GYxF+/Ipc/yV82yJ3/fhNs/v7M5cofv81fzm7i9zPO1SuWZPObnZ41y+orFnXYnq9O7aAvq13gWtaS+uW1nQ/okFlTj5gxfiFRqFz+zju4cPmCZbX4O5Xf0DE/9+JuJ/0kgq/irF1NnSb5faifXcg9r5m2avnyzm+vJPksaPKvtNZm8gmCLud7M1aeXLt8VUPtYiYuJp8mvc9V6Iv9iS45NK8w9b1qUSMVwt/yMAhuFVwTB8H9gs9L+uIoCC4TtMr6LbL+TeHbhK8Uvl34WuEHBF+U9CXiu1xwkax/Qda/JdwmfKfgOkl/RXC3+44+8VwRSd6yfoesbxa+S/gq4V1SQTBIMFgwRFAqKBEMFAwVHCf7+UnB8YJPCcrks90EvST9O8nzYcnjbeGdkf/9/kdj/zv7b0n628LvRf538b8b+99/fyfyv6O+Rda/F/vftP+O8N8i//vkj8X+d7j/HPnfs35c1n8Q+98W/75wIFge+N/+XRH43+g9Sz7rGUi9CW4O/e/U/jkWTdIXhv57K8+T7YfxG6RXRv63Tsv4js0DA/9bjLvxXZwH8dubV0f+NwIrAv/bMmdIXk2uPQtcIMkNJNxYaJR8vojvUzkmFnb7Izgz9L9JN5zvGNxL8Lo7f8IPCi6Q/NcK8uSz3rJtH1evgmLBAEG/lOQj6CvonxKPG+OIN+a7F1N8f+EJgZxf+fB8+ewi154E+7k6Eu4jfF8g7UvwW/GcHkp+Li3lviHoxneBFvHdn1e7Y+f7Pq/he0Wnu3rjO0xv5rsxbxGcHUiblDwX8p2hewT+N85G8v2FeXzn6dWx/z680wSnBrIPfLdgP0FB4L9DspDvSqzjOwdH892Armv/HN/D9xm+7+7TsexP7H+/qXss28b+t5BG8V1wt0b+u/tujvx35H3d7SffCfkGv2l0Bd+X8lgYZP6KUpKXg9vP0P/W8ybBVwM5j4Ln5LPdXFsKpZ0JygQN7voULBM0u2tTcLnk+aqUuVrSLwpeErwtuFfyODaQz0U/xrVd+axUcL2s3yC4MZZjjOUYYzlGwecEGwQ3u34glmNy/YDrI9y1HstxyLbHC385knMbyX4Kvia4S3C34B7BlwQPCB5ydRDJvgo2RrIvgvsEXxE8KNgk+IbgW4KTJM8XQsk3kLbjrkvX2FKSh3w=
*/