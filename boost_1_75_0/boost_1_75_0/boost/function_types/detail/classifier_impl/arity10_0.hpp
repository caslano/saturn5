
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
cUy//2lGlkZHo+n+j2boyrfV+J0f7G5G1x5cQTdxFa87wi1ZWceLn6E8VnvaAzYMU3tAHFKDv0jD7/X9CDtBHnJWEGOnEEf+0VqNw3p+dyd1zAQsHU+0/Ml7kZZfNgppeaA/0XIoZJzxnekSGHD2qWVaju/afUYc1jym5fN4KvN/Ilo+z8JhzUMO6/lkIub3ReFB0l5+fxQvwNFRTN4Lo5i8j4kiXos8EJuZ3tlbeGneygWqzAJVsgDSzKujaHNbELo0ZypGYyckTu7vNxmNNvhVzOhvWSXv5dNKNjgZOw2lh/9zt0PxgnZHTMDohMuKuDRHK7jHVUXkaRCZd+UYP7RAk7x2XuZUYW2R1z/F8HysgNZWJiUZyOGFZfuRFtYU5kAXMZ6z07cpkEiT/bhVZ0WJOjGd8dPaCTi3wYSKyjZwZZqgYQODBgVV4nSEquxohH16kk68qrlyota09gLO8bXI50Yny0doGZXt24oZenaCw28lpqdgeD9k+oSSke7EmiB9qrUxfSIplDPrB6JPOcbjZ8ggqJKToTGU9CloDFf8QGOYE6HDueoHxmoak/d+0KUudEJ93nqcNblJu3kYMCPeGf9UCbDqUZ61T7yrfwWtfzKkYAYWSe8fgs7B4lje6YcEDZ9NP1xB3yJ/sLCs80ziZlq9xTFxmzEfiVv7iFCWdfFxSb7eUb9eVb+eUb/mHCfaNJOvD4qruJQc
*/