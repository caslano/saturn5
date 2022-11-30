
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
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
*/