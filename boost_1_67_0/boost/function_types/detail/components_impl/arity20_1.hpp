
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

# include <boost/function_types/detail/components_impl/arity10_1.hpp>
template< typename R , typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9 , typename T10, typename L>
struct components_impl<BOOST_FT_syntax(BOOST_FT_cc, BOOST_PP_EMPTY) (T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 BOOST_FT_ell) BOOST_FT_cv, L>
{
typedef encode_bits<BOOST_FT_flags,BOOST_FT_cc_id> bits;
typedef constant<BOOST_FT_full_mask> mask;
typedef function_types::components<BOOST_FT_syntax(BOOST_FT_cc, BOOST_PP_EMPTY) (T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 BOOST_FT_ell) BOOST_FT_cv, L> type;
typedef components_mpl_sequence_tag tag;
typedef mpl::integral_c<std::size_t,11> function_arity;
typedef mpl::vector12< R, typename class_transform<T0 BOOST_FT_cv, L> ::type , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 > types;
};
template< typename R , typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9 , typename T10 , typename T11, typename L>
struct components_impl<BOOST_FT_syntax(BOOST_FT_cc, BOOST_PP_EMPTY) (T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 BOOST_FT_ell) BOOST_FT_cv, L>
{
typedef encode_bits<BOOST_FT_flags,BOOST_FT_cc_id> bits;
typedef constant<BOOST_FT_full_mask> mask;
typedef function_types::components<BOOST_FT_syntax(BOOST_FT_cc, BOOST_PP_EMPTY) (T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 BOOST_FT_ell) BOOST_FT_cv, L> type;
typedef components_mpl_sequence_tag tag;
typedef mpl::integral_c<std::size_t,12> function_arity;
typedef mpl::vector13< R, typename class_transform<T0 BOOST_FT_cv, L> ::type , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 > types;
};
template< typename R , typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9 , typename T10 , typename T11 , typename T12, typename L>
struct components_impl<BOOST_FT_syntax(BOOST_FT_cc, BOOST_PP_EMPTY) (T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 BOOST_FT_ell) BOOST_FT_cv, L>
{
typedef encode_bits<BOOST_FT_flags,BOOST_FT_cc_id> bits;
typedef constant<BOOST_FT_full_mask> mask;
typedef function_types::components<BOOST_FT_syntax(BOOST_FT_cc, BOOST_PP_EMPTY) (T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 BOOST_FT_ell) BOOST_FT_cv, L> type;
typedef components_mpl_sequence_tag tag;
typedef mpl::integral_c<std::size_t,13> function_arity;
typedef mpl::vector14< R, typename class_transform<T0 BOOST_FT_cv, L> ::type , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 > types;
};
template< typename R , typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9 , typename T10 , typename T11 , typename T12 , typename T13, typename L>
struct components_impl<BOOST_FT_syntax(BOOST_FT_cc, BOOST_PP_EMPTY) (T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 BOOST_FT_ell) BOOST_FT_cv, L>
{
typedef encode_bits<BOOST_FT_flags,BOOST_FT_cc_id> bits;
typedef constant<BOOST_FT_full_mask> mask;
typedef function_types::components<BOOST_FT_syntax(BOOST_FT_cc, BOOST_PP_EMPTY) (T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 BOOST_FT_ell) BOOST_FT_cv, L> type;
typedef components_mpl_sequence_tag tag;
typedef mpl::integral_c<std::size_t,14> function_arity;
typedef mpl::vector15< R, typename class_transform<T0 BOOST_FT_cv, L> ::type , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 > types;
};
template< typename R , typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9 , typename T10 , typename T11 , typename T12 , typename T13 , typename T14, typename L>
struct components_impl<BOOST_FT_syntax(BOOST_FT_cc, BOOST_PP_EMPTY) (T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 BOOST_FT_ell) BOOST_FT_cv, L>
{
typedef encode_bits<BOOST_FT_flags,BOOST_FT_cc_id> bits;
typedef constant<BOOST_FT_full_mask> mask;
typedef function_types::components<BOOST_FT_syntax(BOOST_FT_cc, BOOST_PP_EMPTY) (T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 BOOST_FT_ell) BOOST_FT_cv, L> type;
typedef components_mpl_sequence_tag tag;
typedef mpl::integral_c<std::size_t,15> function_arity;
typedef mpl::vector16< R, typename class_transform<T0 BOOST_FT_cv, L> ::type , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 > types;
};
template< typename R , typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9 , typename T10 , typename T11 , typename T12 , typename T13 , typename T14 , typename T15, typename L>
struct components_impl<BOOST_FT_syntax(BOOST_FT_cc, BOOST_PP_EMPTY) (T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 BOOST_FT_ell) BOOST_FT_cv, L>
{
typedef encode_bits<BOOST_FT_flags,BOOST_FT_cc_id> bits;
typedef constant<BOOST_FT_full_mask> mask;
typedef function_types::components<BOOST_FT_syntax(BOOST_FT_cc, BOOST_PP_EMPTY) (T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 BOOST_FT_ell) BOOST_FT_cv, L> type;
typedef components_mpl_sequence_tag tag;
typedef mpl::integral_c<std::size_t,16> function_arity;
typedef mpl::vector17< R, typename class_transform<T0 BOOST_FT_cv, L> ::type , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 > types;
};
template< typename R , typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9 , typename T10 , typename T11 , typename T12 , typename T13 , typename T14 , typename T15 , typename T16, typename L>
struct components_impl<BOOST_FT_syntax(BOOST_FT_cc, BOOST_PP_EMPTY) (T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 BOOST_FT_ell) BOOST_FT_cv, L>
{
typedef encode_bits<BOOST_FT_flags,BOOST_FT_cc_id> bits;
typedef constant<BOOST_FT_full_mask> mask;
typedef function_types::components<BOOST_FT_syntax(BOOST_FT_cc, BOOST_PP_EMPTY) (T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 BOOST_FT_ell) BOOST_FT_cv, L> type;
typedef components_mpl_sequence_tag tag;
typedef mpl::integral_c<std::size_t,17> function_arity;
typedef mpl::vector18< R, typename class_transform<T0 BOOST_FT_cv, L> ::type , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 > types;
};
template< typename R , typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9 , typename T10 , typename T11 , typename T12 , typename T13 , typename T14 , typename T15 , typename T16 , typename T17, typename L>
struct components_impl<BOOST_FT_syntax(BOOST_FT_cc, BOOST_PP_EMPTY) (T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 BOOST_FT_ell) BOOST_FT_cv, L>
{
typedef encode_bits<BOOST_FT_flags,BOOST_FT_cc_id> bits;
typedef constant<BOOST_FT_full_mask> mask;
typedef function_types::components<BOOST_FT_syntax(BOOST_FT_cc, BOOST_PP_EMPTY) (T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 BOOST_FT_ell) BOOST_FT_cv, L> type;
typedef components_mpl_sequence_tag tag;
typedef mpl::integral_c<std::size_t,18> function_arity;
typedef mpl::vector19< R, typename class_transform<T0 BOOST_FT_cv, L> ::type , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 > types;
};
template< typename R , typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9 , typename T10 , typename T11 , typename T12 , typename T13 , typename T14 , typename T15 , typename T16 , typename T17 , typename T18, typename L>
struct components_impl<BOOST_FT_syntax(BOOST_FT_cc, BOOST_PP_EMPTY) (T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18 BOOST_FT_ell) BOOST_FT_cv, L>
{
typedef encode_bits<BOOST_FT_flags,BOOST_FT_cc_id> bits;
typedef constant<BOOST_FT_full_mask> mask;
typedef function_types::components<BOOST_FT_syntax(BOOST_FT_cc, BOOST_PP_EMPTY) (T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18 BOOST_FT_ell) BOOST_FT_cv, L> type;
typedef components_mpl_sequence_tag tag;
typedef mpl::integral_c<std::size_t,19> function_arity;
typedef mpl::vector20< R, typename class_transform<T0 BOOST_FT_cv, L> ::type , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18 > types;
};
template< typename R , typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9 , typename T10 , typename T11 , typename T12 , typename T13 , typename T14 , typename T15 , typename T16 , typename T17 , typename T18 , typename T19, typename L>
struct components_impl<BOOST_FT_syntax(BOOST_FT_cc, BOOST_PP_EMPTY) (T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18 , T19 BOOST_FT_ell) BOOST_FT_cv, L>
{
typedef encode_bits<BOOST_FT_flags,BOOST_FT_cc_id> bits;
typedef constant<BOOST_FT_full_mask> mask;
typedef function_types::components<BOOST_FT_syntax(BOOST_FT_cc, BOOST_PP_EMPTY) (T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18 , T19 BOOST_FT_ell) BOOST_FT_cv, L> type;
typedef components_mpl_sequence_tag tag;
typedef mpl::integral_c<std::size_t,20> function_arity;
typedef mpl::vector21< R, typename class_transform<T0 BOOST_FT_cv, L> ::type , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18 , T19 > types;
};


/* arity20_1.hpp
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
*/