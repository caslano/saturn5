
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
EsvNbttEFWdu2ORC9wKpWBQWxAgWu44dAleRtao7NfEzh39AU5pc8A658LHE1jN8pnOaYsOSxX1r7PqwRGr6mGi5IZWkUoZcZfBhPCLgsVJ59EGneCLCq/wfzKLIavjlu36i+2PnN31ouVYwvN98scDgSEp63NB6MgN4czxSUh34Kp9iPbnuAy5rik5ya14xzSgvUOgLikgD+w+W6w78EQ8MP10UyhSypGDTFfXLG94On0i3s1twlEsracTo0AC3saGaQouAbNJy475t47glIE+aR8H3uZLNmDpp8+swLjvlf0ySsOHXFh5uTPtZe63DFLx7tqZ1QeScuActhlrlV5dfPLA70fyKBuFjuUizGMzt7ErFYiUDqZuUoUHdZrBW82sVaUYFqNfmDdjwYEVVQnH3BuMkYUe5CEvRVa22nrlBn3/j1WoRdmbpczk9pEgNUvNHCyYm1in0je14DAQdMJwi+hN7e7S2dwjsf2PoRG/S8QhEfiC6WTrqmLZFIUk7q1QyQToAZS4Q95/y3ZY3oygXL6zqe2Nx/+I0FY/Fy5onCNwvWZLwi7XhtA==
*/