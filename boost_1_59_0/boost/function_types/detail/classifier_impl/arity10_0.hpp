
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

template< typename R >
typename encode_charr<BOOST_FT_flags,BOOST_FT_cc_id,0> ::type
classifier_impl(BOOST_FT_syntax(BOOST_FT_cc, BOOST_PP_EMPTY) (BOOST_FT_nullary_param BOOST_FT_ell) BOOST_FT_cv);
template< typename R , typename T0 >
typename encode_charr<BOOST_FT_flags,BOOST_FT_cc_id,1> ::type
classifier_impl(BOOST_FT_syntax(BOOST_FT_cc, BOOST_PP_EMPTY) (T0 BOOST_FT_ell) BOOST_FT_cv);
template< typename R , typename T0 , typename T1 >
typename encode_charr<BOOST_FT_flags,BOOST_FT_cc_id,2> ::type
classifier_impl(BOOST_FT_syntax(BOOST_FT_cc, BOOST_PP_EMPTY) (T0 , T1 BOOST_FT_ell) BOOST_FT_cv);
template< typename R , typename T0 , typename T1 , typename T2 >
typename encode_charr<BOOST_FT_flags,BOOST_FT_cc_id,3> ::type
classifier_impl(BOOST_FT_syntax(BOOST_FT_cc, BOOST_PP_EMPTY) (T0 , T1 , T2 BOOST_FT_ell) BOOST_FT_cv);
template< typename R , typename T0 , typename T1 , typename T2 , typename T3 >
typename encode_charr<BOOST_FT_flags,BOOST_FT_cc_id,4> ::type
classifier_impl(BOOST_FT_syntax(BOOST_FT_cc, BOOST_PP_EMPTY) (T0 , T1 , T2 , T3 BOOST_FT_ell) BOOST_FT_cv);
template< typename R , typename T0 , typename T1 , typename T2 , typename T3 , typename T4 >
typename encode_charr<BOOST_FT_flags,BOOST_FT_cc_id,5> ::type
classifier_impl(BOOST_FT_syntax(BOOST_FT_cc, BOOST_PP_EMPTY) (T0 , T1 , T2 , T3 , T4 BOOST_FT_ell) BOOST_FT_cv);
template< typename R , typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 >
typename encode_charr<BOOST_FT_flags,BOOST_FT_cc_id,6> ::type
classifier_impl(BOOST_FT_syntax(BOOST_FT_cc, BOOST_PP_EMPTY) (T0 , T1 , T2 , T3 , T4 , T5 BOOST_FT_ell) BOOST_FT_cv);
template< typename R , typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 >
typename encode_charr<BOOST_FT_flags,BOOST_FT_cc_id,7> ::type
classifier_impl(BOOST_FT_syntax(BOOST_FT_cc, BOOST_PP_EMPTY) (T0 , T1 , T2 , T3 , T4 , T5 , T6 BOOST_FT_ell) BOOST_FT_cv);
template< typename R , typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 >
typename encode_charr<BOOST_FT_flags,BOOST_FT_cc_id,8> ::type
classifier_impl(BOOST_FT_syntax(BOOST_FT_cc, BOOST_PP_EMPTY) (T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 BOOST_FT_ell) BOOST_FT_cv);
template< typename R , typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 >
typename encode_charr<BOOST_FT_flags,BOOST_FT_cc_id,9> ::type
classifier_impl(BOOST_FT_syntax(BOOST_FT_cc, BOOST_PP_EMPTY) (T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 BOOST_FT_ell) BOOST_FT_cv);
template< typename R , typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9 >
typename encode_charr<BOOST_FT_flags,BOOST_FT_cc_id,10> ::type
classifier_impl(BOOST_FT_syntax(BOOST_FT_cc, BOOST_PP_EMPTY) (T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 BOOST_FT_ell) BOOST_FT_cv);


/* arity10_0.hpp
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
*/