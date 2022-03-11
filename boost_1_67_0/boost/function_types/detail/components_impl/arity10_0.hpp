
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