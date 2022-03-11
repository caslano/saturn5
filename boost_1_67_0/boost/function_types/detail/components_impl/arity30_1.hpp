
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

# include <boost/function_types/detail/components_impl/arity20_1.hpp>
template< typename R , typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9 , typename T10 , typename T11 , typename T12 , typename T13 , typename T14 , typename T15 , typename T16 , typename T17 , typename T18 , typename T19 , typename T20, typename L>
struct components_impl<BOOST_FT_syntax(BOOST_FT_cc, BOOST_PP_EMPTY) (T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18 , T19 , T20 BOOST_FT_ell) BOOST_FT_cv, L>
{
typedef encode_bits<BOOST_FT_flags,BOOST_FT_cc_id> bits;
typedef constant<BOOST_FT_full_mask> mask;
typedef function_types::components<BOOST_FT_syntax(BOOST_FT_cc, BOOST_PP_EMPTY) (T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18 , T19 , T20 BOOST_FT_ell) BOOST_FT_cv, L> type;
typedef components_mpl_sequence_tag tag;
typedef mpl::integral_c<std::size_t,21> function_arity;
typedef mpl::vector22< R, typename class_transform<T0 BOOST_FT_cv, L> ::type , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18 , T19 , T20 > types;
};
template< typename R , typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9 , typename T10 , typename T11 , typename T12 , typename T13 , typename T14 , typename T15 , typename T16 , typename T17 , typename T18 , typename T19 , typename T20 , typename T21, typename L>
struct components_impl<BOOST_FT_syntax(BOOST_FT_cc, BOOST_PP_EMPTY) (T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18 , T19 , T20 , T21 BOOST_FT_ell) BOOST_FT_cv, L>
{
typedef encode_bits<BOOST_FT_flags,BOOST_FT_cc_id> bits;
typedef constant<BOOST_FT_full_mask> mask;
typedef function_types::components<BOOST_FT_syntax(BOOST_FT_cc, BOOST_PP_EMPTY) (T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18 , T19 , T20 , T21 BOOST_FT_ell) BOOST_FT_cv, L> type;
typedef components_mpl_sequence_tag tag;
typedef mpl::integral_c<std::size_t,22> function_arity;
typedef mpl::vector23< R, typename class_transform<T0 BOOST_FT_cv, L> ::type , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18 , T19 , T20 , T21 > types;
};
template< typename R , typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9 , typename T10 , typename T11 , typename T12 , typename T13 , typename T14 , typename T15 , typename T16 , typename T17 , typename T18 , typename T19 , typename T20 , typename T21 , typename T22, typename L>
struct components_impl<BOOST_FT_syntax(BOOST_FT_cc, BOOST_PP_EMPTY) (T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18 , T19 , T20 , T21 , T22 BOOST_FT_ell) BOOST_FT_cv, L>
{
typedef encode_bits<BOOST_FT_flags,BOOST_FT_cc_id> bits;
typedef constant<BOOST_FT_full_mask> mask;
typedef function_types::components<BOOST_FT_syntax(BOOST_FT_cc, BOOST_PP_EMPTY) (T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18 , T19 , T20 , T21 , T22 BOOST_FT_ell) BOOST_FT_cv, L> type;
typedef components_mpl_sequence_tag tag;
typedef mpl::integral_c<std::size_t,23> function_arity;
typedef mpl::vector24< R, typename class_transform<T0 BOOST_FT_cv, L> ::type , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18 , T19 , T20 , T21 , T22 > types;
};
template< typename R , typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9 , typename T10 , typename T11 , typename T12 , typename T13 , typename T14 , typename T15 , typename T16 , typename T17 , typename T18 , typename T19 , typename T20 , typename T21 , typename T22 , typename T23, typename L>
struct components_impl<BOOST_FT_syntax(BOOST_FT_cc, BOOST_PP_EMPTY) (T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18 , T19 , T20 , T21 , T22 , T23 BOOST_FT_ell) BOOST_FT_cv, L>
{
typedef encode_bits<BOOST_FT_flags,BOOST_FT_cc_id> bits;
typedef constant<BOOST_FT_full_mask> mask;
typedef function_types::components<BOOST_FT_syntax(BOOST_FT_cc, BOOST_PP_EMPTY) (T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18 , T19 , T20 , T21 , T22 , T23 BOOST_FT_ell) BOOST_FT_cv, L> type;
typedef components_mpl_sequence_tag tag;
typedef mpl::integral_c<std::size_t,24> function_arity;
typedef mpl::vector25< R, typename class_transform<T0 BOOST_FT_cv, L> ::type , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18 , T19 , T20 , T21 , T22 , T23 > types;
};
template< typename R , typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9 , typename T10 , typename T11 , typename T12 , typename T13 , typename T14 , typename T15 , typename T16 , typename T17 , typename T18 , typename T19 , typename T20 , typename T21 , typename T22 , typename T23 , typename T24, typename L>
struct components_impl<BOOST_FT_syntax(BOOST_FT_cc, BOOST_PP_EMPTY) (T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18 , T19 , T20 , T21 , T22 , T23 , T24 BOOST_FT_ell) BOOST_FT_cv, L>
{
typedef encode_bits<BOOST_FT_flags,BOOST_FT_cc_id> bits;
typedef constant<BOOST_FT_full_mask> mask;
typedef function_types::components<BOOST_FT_syntax(BOOST_FT_cc, BOOST_PP_EMPTY) (T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18 , T19 , T20 , T21 , T22 , T23 , T24 BOOST_FT_ell) BOOST_FT_cv, L> type;
typedef components_mpl_sequence_tag tag;
typedef mpl::integral_c<std::size_t,25> function_arity;
typedef mpl::vector26< R, typename class_transform<T0 BOOST_FT_cv, L> ::type , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18 , T19 , T20 , T21 , T22 , T23 , T24 > types;
};
template< typename R , typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9 , typename T10 , typename T11 , typename T12 , typename T13 , typename T14 , typename T15 , typename T16 , typename T17 , typename T18 , typename T19 , typename T20 , typename T21 , typename T22 , typename T23 , typename T24 , typename T25, typename L>
struct components_impl<BOOST_FT_syntax(BOOST_FT_cc, BOOST_PP_EMPTY) (T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18 , T19 , T20 , T21 , T22 , T23 , T24 , T25 BOOST_FT_ell) BOOST_FT_cv, L>
{
typedef encode_bits<BOOST_FT_flags,BOOST_FT_cc_id> bits;
typedef constant<BOOST_FT_full_mask> mask;
typedef function_types::components<BOOST_FT_syntax(BOOST_FT_cc, BOOST_PP_EMPTY) (T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18 , T19 , T20 , T21 , T22 , T23 , T24 , T25 BOOST_FT_ell) BOOST_FT_cv, L> type;
typedef components_mpl_sequence_tag tag;
typedef mpl::integral_c<std::size_t,26> function_arity;
typedef mpl::vector27< R, typename class_transform<T0 BOOST_FT_cv, L> ::type , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18 , T19 , T20 , T21 , T22 , T23 , T24 , T25 > types;
};
template< typename R , typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9 , typename T10 , typename T11 , typename T12 , typename T13 , typename T14 , typename T15 , typename T16 , typename T17 , typename T18 , typename T19 , typename T20 , typename T21 , typename T22 , typename T23 , typename T24 , typename T25 , typename T26, typename L>
struct components_impl<BOOST_FT_syntax(BOOST_FT_cc, BOOST_PP_EMPTY) (T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18 , T19 , T20 , T21 , T22 , T23 , T24 , T25 , T26 BOOST_FT_ell) BOOST_FT_cv, L>
{
typedef encode_bits<BOOST_FT_flags,BOOST_FT_cc_id> bits;
typedef constant<BOOST_FT_full_mask> mask;
typedef function_types::components<BOOST_FT_syntax(BOOST_FT_cc, BOOST_PP_EMPTY) (T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18 , T19 , T20 , T21 , T22 , T23 , T24 , T25 , T26 BOOST_FT_ell) BOOST_FT_cv, L> type;
typedef components_mpl_sequence_tag tag;
typedef mpl::integral_c<std::size_t,27> function_arity;
typedef mpl::vector28< R, typename class_transform<T0 BOOST_FT_cv, L> ::type , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18 , T19 , T20 , T21 , T22 , T23 , T24 , T25 , T26 > types;
};
template< typename R , typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9 , typename T10 , typename T11 , typename T12 , typename T13 , typename T14 , typename T15 , typename T16 , typename T17 , typename T18 , typename T19 , typename T20 , typename T21 , typename T22 , typename T23 , typename T24 , typename T25 , typename T26 , typename T27, typename L>
struct components_impl<BOOST_FT_syntax(BOOST_FT_cc, BOOST_PP_EMPTY) (T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18 , T19 , T20 , T21 , T22 , T23 , T24 , T25 , T26 , T27 BOOST_FT_ell) BOOST_FT_cv, L>
{
typedef encode_bits<BOOST_FT_flags,BOOST_FT_cc_id> bits;
typedef constant<BOOST_FT_full_mask> mask;
typedef function_types::components<BOOST_FT_syntax(BOOST_FT_cc, BOOST_PP_EMPTY) (T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18 , T19 , T20 , T21 , T22 , T23 , T24 , T25 , T26 , T27 BOOST_FT_ell) BOOST_FT_cv, L> type;
typedef components_mpl_sequence_tag tag;
typedef mpl::integral_c<std::size_t,28> function_arity;
typedef mpl::vector29< R, typename class_transform<T0 BOOST_FT_cv, L> ::type , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18 , T19 , T20 , T21 , T22 , T23 , T24 , T25 , T26 , T27 > types;
};
template< typename R , typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9 , typename T10 , typename T11 , typename T12 , typename T13 , typename T14 , typename T15 , typename T16 , typename T17 , typename T18 , typename T19 , typename T20 , typename T21 , typename T22 , typename T23 , typename T24 , typename T25 , typename T26 , typename T27 , typename T28, typename L>
struct components_impl<BOOST_FT_syntax(BOOST_FT_cc, BOOST_PP_EMPTY) (T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18 , T19 , T20 , T21 , T22 , T23 , T24 , T25 , T26 , T27 , T28 BOOST_FT_ell) BOOST_FT_cv, L>
{
typedef encode_bits<BOOST_FT_flags,BOOST_FT_cc_id> bits;
typedef constant<BOOST_FT_full_mask> mask;
typedef function_types::components<BOOST_FT_syntax(BOOST_FT_cc, BOOST_PP_EMPTY) (T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18 , T19 , T20 , T21 , T22 , T23 , T24 , T25 , T26 , T27 , T28 BOOST_FT_ell) BOOST_FT_cv, L> type;
typedef components_mpl_sequence_tag tag;
typedef mpl::integral_c<std::size_t,29> function_arity;
typedef mpl::vector30< R, typename class_transform<T0 BOOST_FT_cv, L> ::type , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18 , T19 , T20 , T21 , T22 , T23 , T24 , T25 , T26 , T27 , T28 > types;
};
template< typename R , typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9 , typename T10 , typename T11 , typename T12 , typename T13 , typename T14 , typename T15 , typename T16 , typename T17 , typename T18 , typename T19 , typename T20 , typename T21 , typename T22 , typename T23 , typename T24 , typename T25 , typename T26 , typename T27 , typename T28 , typename T29, typename L>
struct components_impl<BOOST_FT_syntax(BOOST_FT_cc, BOOST_PP_EMPTY) (T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18 , T19 , T20 , T21 , T22 , T23 , T24 , T25 , T26 , T27 , T28 , T29 BOOST_FT_ell) BOOST_FT_cv, L>
{
typedef encode_bits<BOOST_FT_flags,BOOST_FT_cc_id> bits;
typedef constant<BOOST_FT_full_mask> mask;
typedef function_types::components<BOOST_FT_syntax(BOOST_FT_cc, BOOST_PP_EMPTY) (T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18 , T19 , T20 , T21 , T22 , T23 , T24 , T25 , T26 , T27 , T28 , T29 BOOST_FT_ell) BOOST_FT_cv, L> type;
typedef components_mpl_sequence_tag tag;
typedef mpl::integral_c<std::size_t,30> function_arity;
typedef mpl::vector31< R, typename class_transform<T0 BOOST_FT_cv, L> ::type , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18 , T19 , T20 , T21 , T22 , T23 , T24 , T25 , T26 , T27 , T28 , T29 > types;
};


/* arity30_1.hpp
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
*/