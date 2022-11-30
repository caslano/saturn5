
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

template< typename R , typename T0, typename L>
struct components_impl<BOOST_FT_syntax(BOOST_FT_cc, BOOST_PP_EMPTY) ( BOOST_FT_ell) BOOST_FT_cv, L>
{
typedef encode_bits<BOOST_FT_flags,BOOST_FT_cc_id> bits;
typedef constant<BOOST_FT_full_mask> mask;
typedef function_types::components<BOOST_FT_syntax(BOOST_FT_cc, BOOST_PP_EMPTY) ( BOOST_FT_ell) BOOST_FT_cv, L> type;
typedef components_mpl_sequence_tag tag;
typedef mpl::integral_c<std::size_t,1> function_arity;
typedef mpl::vector2< R, typename class_transform<T0 BOOST_FT_cv, L> ::type > types;
};
template< typename R , typename T0 , typename T1, typename L>
struct components_impl<BOOST_FT_syntax(BOOST_FT_cc, BOOST_PP_EMPTY) (T1 BOOST_FT_ell) BOOST_FT_cv, L>
{
typedef encode_bits<BOOST_FT_flags,BOOST_FT_cc_id> bits;
typedef constant<BOOST_FT_full_mask> mask;
typedef function_types::components<BOOST_FT_syntax(BOOST_FT_cc, BOOST_PP_EMPTY) (T1 BOOST_FT_ell) BOOST_FT_cv, L> type;
typedef components_mpl_sequence_tag tag;
typedef mpl::integral_c<std::size_t,2> function_arity;
typedef mpl::vector3< R, typename class_transform<T0 BOOST_FT_cv, L> ::type , T1 > types;
};
template< typename R , typename T0 , typename T1 , typename T2, typename L>
struct components_impl<BOOST_FT_syntax(BOOST_FT_cc, BOOST_PP_EMPTY) (T1 , T2 BOOST_FT_ell) BOOST_FT_cv, L>
{
typedef encode_bits<BOOST_FT_flags,BOOST_FT_cc_id> bits;
typedef constant<BOOST_FT_full_mask> mask;
typedef function_types::components<BOOST_FT_syntax(BOOST_FT_cc, BOOST_PP_EMPTY) (T1 , T2 BOOST_FT_ell) BOOST_FT_cv, L> type;
typedef components_mpl_sequence_tag tag;
typedef mpl::integral_c<std::size_t,3> function_arity;
typedef mpl::vector4< R, typename class_transform<T0 BOOST_FT_cv, L> ::type , T1 , T2 > types;
};
template< typename R , typename T0 , typename T1 , typename T2 , typename T3, typename L>
struct components_impl<BOOST_FT_syntax(BOOST_FT_cc, BOOST_PP_EMPTY) (T1 , T2 , T3 BOOST_FT_ell) BOOST_FT_cv, L>
{
typedef encode_bits<BOOST_FT_flags,BOOST_FT_cc_id> bits;
typedef constant<BOOST_FT_full_mask> mask;
typedef function_types::components<BOOST_FT_syntax(BOOST_FT_cc, BOOST_PP_EMPTY) (T1 , T2 , T3 BOOST_FT_ell) BOOST_FT_cv, L> type;
typedef components_mpl_sequence_tag tag;
typedef mpl::integral_c<std::size_t,4> function_arity;
typedef mpl::vector5< R, typename class_transform<T0 BOOST_FT_cv, L> ::type , T1 , T2 , T3 > types;
};
template< typename R , typename T0 , typename T1 , typename T2 , typename T3 , typename T4, typename L>
struct components_impl<BOOST_FT_syntax(BOOST_FT_cc, BOOST_PP_EMPTY) (T1 , T2 , T3 , T4 BOOST_FT_ell) BOOST_FT_cv, L>
{
typedef encode_bits<BOOST_FT_flags,BOOST_FT_cc_id> bits;
typedef constant<BOOST_FT_full_mask> mask;
typedef function_types::components<BOOST_FT_syntax(BOOST_FT_cc, BOOST_PP_EMPTY) (T1 , T2 , T3 , T4 BOOST_FT_ell) BOOST_FT_cv, L> type;
typedef components_mpl_sequence_tag tag;
typedef mpl::integral_c<std::size_t,5> function_arity;
typedef mpl::vector6< R, typename class_transform<T0 BOOST_FT_cv, L> ::type , T1 , T2 , T3 , T4 > types;
};
template< typename R , typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5, typename L>
struct components_impl<BOOST_FT_syntax(BOOST_FT_cc, BOOST_PP_EMPTY) (T1 , T2 , T3 , T4 , T5 BOOST_FT_ell) BOOST_FT_cv, L>
{
typedef encode_bits<BOOST_FT_flags,BOOST_FT_cc_id> bits;
typedef constant<BOOST_FT_full_mask> mask;
typedef function_types::components<BOOST_FT_syntax(BOOST_FT_cc, BOOST_PP_EMPTY) (T1 , T2 , T3 , T4 , T5 BOOST_FT_ell) BOOST_FT_cv, L> type;
typedef components_mpl_sequence_tag tag;
typedef mpl::integral_c<std::size_t,6> function_arity;
typedef mpl::vector7< R, typename class_transform<T0 BOOST_FT_cv, L> ::type , T1 , T2 , T3 , T4 , T5 > types;
};
template< typename R , typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6, typename L>
struct components_impl<BOOST_FT_syntax(BOOST_FT_cc, BOOST_PP_EMPTY) (T1 , T2 , T3 , T4 , T5 , T6 BOOST_FT_ell) BOOST_FT_cv, L>
{
typedef encode_bits<BOOST_FT_flags,BOOST_FT_cc_id> bits;
typedef constant<BOOST_FT_full_mask> mask;
typedef function_types::components<BOOST_FT_syntax(BOOST_FT_cc, BOOST_PP_EMPTY) (T1 , T2 , T3 , T4 , T5 , T6 BOOST_FT_ell) BOOST_FT_cv, L> type;
typedef components_mpl_sequence_tag tag;
typedef mpl::integral_c<std::size_t,7> function_arity;
typedef mpl::vector8< R, typename class_transform<T0 BOOST_FT_cv, L> ::type , T1 , T2 , T3 , T4 , T5 , T6 > types;
};
template< typename R , typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7, typename L>
struct components_impl<BOOST_FT_syntax(BOOST_FT_cc, BOOST_PP_EMPTY) (T1 , T2 , T3 , T4 , T5 , T6 , T7 BOOST_FT_ell) BOOST_FT_cv, L>
{
typedef encode_bits<BOOST_FT_flags,BOOST_FT_cc_id> bits;
typedef constant<BOOST_FT_full_mask> mask;
typedef function_types::components<BOOST_FT_syntax(BOOST_FT_cc, BOOST_PP_EMPTY) (T1 , T2 , T3 , T4 , T5 , T6 , T7 BOOST_FT_ell) BOOST_FT_cv, L> type;
typedef components_mpl_sequence_tag tag;
typedef mpl::integral_c<std::size_t,8> function_arity;
typedef mpl::vector9< R, typename class_transform<T0 BOOST_FT_cv, L> ::type , T1 , T2 , T3 , T4 , T5 , T6 , T7 > types;
};
template< typename R , typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8, typename L>
struct components_impl<BOOST_FT_syntax(BOOST_FT_cc, BOOST_PP_EMPTY) (T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 BOOST_FT_ell) BOOST_FT_cv, L>
{
typedef encode_bits<BOOST_FT_flags,BOOST_FT_cc_id> bits;
typedef constant<BOOST_FT_full_mask> mask;
typedef function_types::components<BOOST_FT_syntax(BOOST_FT_cc, BOOST_PP_EMPTY) (T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 BOOST_FT_ell) BOOST_FT_cv, L> type;
typedef components_mpl_sequence_tag tag;
typedef mpl::integral_c<std::size_t,9> function_arity;
typedef mpl::vector10< R, typename class_transform<T0 BOOST_FT_cv, L> ::type , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 > types;
};
template< typename R , typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9, typename L>
struct components_impl<BOOST_FT_syntax(BOOST_FT_cc, BOOST_PP_EMPTY) (T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 BOOST_FT_ell) BOOST_FT_cv, L>
{
typedef encode_bits<BOOST_FT_flags,BOOST_FT_cc_id> bits;
typedef constant<BOOST_FT_full_mask> mask;
typedef function_types::components<BOOST_FT_syntax(BOOST_FT_cc, BOOST_PP_EMPTY) (T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 BOOST_FT_ell) BOOST_FT_cv, L> type;
typedef components_mpl_sequence_tag tag;
typedef mpl::integral_c<std::size_t,10> function_arity;
typedef mpl::vector11< R, typename class_transform<T0 BOOST_FT_cv, L> ::type , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 > types;
};


/* arity10_1.hpp
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
*/