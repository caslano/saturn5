
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

template< typename R , typename T0 >
typename encode_charr<BOOST_FT_flags,BOOST_FT_cc_id,1> ::type
classifier_impl(BOOST_FT_syntax(BOOST_FT_cc, BOOST_PP_EMPTY) ( BOOST_FT_ell) BOOST_FT_cv);
template< typename R , typename T0 , typename T1 >
typename encode_charr<BOOST_FT_flags,BOOST_FT_cc_id,2> ::type
classifier_impl(BOOST_FT_syntax(BOOST_FT_cc, BOOST_PP_EMPTY) (T1 BOOST_FT_ell) BOOST_FT_cv);
template< typename R , typename T0 , typename T1 , typename T2 >
typename encode_charr<BOOST_FT_flags,BOOST_FT_cc_id,3> ::type
classifier_impl(BOOST_FT_syntax(BOOST_FT_cc, BOOST_PP_EMPTY) (T1 , T2 BOOST_FT_ell) BOOST_FT_cv);
template< typename R , typename T0 , typename T1 , typename T2 , typename T3 >
typename encode_charr<BOOST_FT_flags,BOOST_FT_cc_id,4> ::type
classifier_impl(BOOST_FT_syntax(BOOST_FT_cc, BOOST_PP_EMPTY) (T1 , T2 , T3 BOOST_FT_ell) BOOST_FT_cv);
template< typename R , typename T0 , typename T1 , typename T2 , typename T3 , typename T4 >
typename encode_charr<BOOST_FT_flags,BOOST_FT_cc_id,5> ::type
classifier_impl(BOOST_FT_syntax(BOOST_FT_cc, BOOST_PP_EMPTY) (T1 , T2 , T3 , T4 BOOST_FT_ell) BOOST_FT_cv);
template< typename R , typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 >
typename encode_charr<BOOST_FT_flags,BOOST_FT_cc_id,6> ::type
classifier_impl(BOOST_FT_syntax(BOOST_FT_cc, BOOST_PP_EMPTY) (T1 , T2 , T3 , T4 , T5 BOOST_FT_ell) BOOST_FT_cv);
template< typename R , typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 >
typename encode_charr<BOOST_FT_flags,BOOST_FT_cc_id,7> ::type
classifier_impl(BOOST_FT_syntax(BOOST_FT_cc, BOOST_PP_EMPTY) (T1 , T2 , T3 , T4 , T5 , T6 BOOST_FT_ell) BOOST_FT_cv);
template< typename R , typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 >
typename encode_charr<BOOST_FT_flags,BOOST_FT_cc_id,8> ::type
classifier_impl(BOOST_FT_syntax(BOOST_FT_cc, BOOST_PP_EMPTY) (T1 , T2 , T3 , T4 , T5 , T6 , T7 BOOST_FT_ell) BOOST_FT_cv);
template< typename R , typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 >
typename encode_charr<BOOST_FT_flags,BOOST_FT_cc_id,9> ::type
classifier_impl(BOOST_FT_syntax(BOOST_FT_cc, BOOST_PP_EMPTY) (T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 BOOST_FT_ell) BOOST_FT_cv);
template< typename R , typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9 >
typename encode_charr<BOOST_FT_flags,BOOST_FT_cc_id,10> ::type
classifier_impl(BOOST_FT_syntax(BOOST_FT_cc, BOOST_PP_EMPTY) (T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 BOOST_FT_ell) BOOST_FT_cv);


/* arity10_1.hpp
+jMMfXt4QURbntRBn79pYznDZJg+G/jgX98ibJA+IVo5ooNsvNgdPi81gFbXlCUD3+82824wOIkSwImU7sloa3dlhYBleFRjInm8C6yLKczHLrlPw7HrV93w/Gk4o+fL4AJ7hHfGL0IPQnsCgJ/TozttFsi+96ABZJhn/65QMHKXeEHdv/Rk7Nq3JzFRq3nntW7DgZer7OViB3uCXdwBNVrmErya5x/+KFWGfvQaEdw2z0ixPUewjExtO13y3Im1R4h/P3YN+vhQxmERa8Kx4V4TxdVw8ifPdP3iTiLhVFjIHyP16C2uagSiMq6GLfvf2svUSdB7IdAaWsZRK1+kCdOMgS9uNmPtTqI8uVBh1xGGJipF3Z5seU+RbZylQ1DXB/f3g837Oa9/yFZPI0VCVocKtiPKBRoOrc4WzYixI99P6kU3if0qdsSasqZlZVz6dmWSV30Ko2v4wc0IOyG6VMC8975KdyiDH+c3jgGoHMqyV+NsqK2j7yZ89gsqL/8gyK/BEtboZkEhaIRclBHHIzrxA0rA27H9hl4WZmwFOwWZPGgB8wQDudCtcA==
*/