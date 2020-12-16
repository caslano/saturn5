
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
nvhts+f3b/ly/F0rGzF7c+jyI+X6N7/eV/p1O/qnC3sTK6qqqv6uUoEqf+mYt+KtyIqzg/Z3XTqw92+TPmvT8dyoBfOWRV/Xc/Jdz/S+fc4nE3Yl3/78iVY7olc9/M2v0+6pqqq6jDB4n77+5kVJK2/Uao9I2R8+a27YfzI+9tKRAXPP0vZ8Ed5+yacvbbu8ffxHy7Zf2PTdpN8uPT1rb1T7g73Zcdsc8++4c8oz+yeNjbrnyEX9mj0n3hraY/NDU+aN6P/b1GsuzzK+nZM+BHrim6ir+5pWrzyttoekN8r+qT6JbBBQsNAYDchN6v3DtJUPr9Y9VRqTePaPb0bM2IYeeeBCQuzCg7+W7Lx7jqFt3NsnB+b/pkMy6Lb81ebb5/65u83ml2T/KPZEGvb82Lu1/H6jYcCZ83EZahuhclrIS+iWx9+8VPjGtAXshvPLZ+/bt/Fd9q8MNPyxV4of/EPomWnl5hW/veC1Vh9euht1ebbn6NjixdPHH/zghoguI/tNe/ei3s/Gs7su9Nj02W5v57FIBbS9ry1bWrn0pS6HezRdLRs9UtOnWkgXevm7+M8ujj+x4LmxPbIjbCMm/BE+dysadbAyPqp/yxkd80/dHHOu/ZOx6R870OXnL5/+Ifb0Y4en/nX9hSW9L6/ZN6SPDvkg4dajc9a2O7NyZQkC0H5fR3vd8Fs/FBqEf51/qvmOscc3da+cHjbr1bPxHZ759IWfD9unL+vb1/HEmJ5r7k2x7L3xzTnxQ+9eP/fApL5P+pfX/fSlti24zCmeQ3//Q7avgyoeNY38yYHqCo3Qyozb40acXPptzKWeK7nVRcd/dHnXtZjBNt/86uqJaEaT5b/O3Bqfevfui1+c+6H9uR2Vb4z/fnfO16Mdpmd0yB90B4/96xfTvbtPrptauvyFc9XfJ6l533SpL6ofNK540zbjwsFtG0avMD/68f3XNg5bdunr6I97Hhh/evbtbc63XZLV/6uy7k+/w96x+uKl5i2brP277ctZz95X2P6JYXsXXozct4W2aeumg0eez1oxYPu/Jj2wNzElRa5PC632+PtozUFR49uLYZDX/fLz6Jv29zse3HhUVXVp1kIULIQH8XKqbI1C3/PB/MPfHxo7fHtc9feb/pfOApT3xZX3SyOPdnnON5yOubx94YfZ6+h3TmPmdrvu2aPvX7Y+cWwccw4de/PHz77v3ji93YLDx9/vgp4UTHzC2edaN/4ywfxWC/RMz5geFeN+u/fT2EmftZsje/HAR7/MT/6J1yi/+u8d76DLL17a7utfZky4/otvd6wf/T569Pi6X5ZF3blve+Lh8e3ydc9Mm3Jn992T/ui7Z0ubYY+jlzZ+kPfp5aLca448unVrBzmmmpQv6/rY848o5beE8n3T7ZLbP9u49atOL/d//PsmVHxc33jlzU3XlIzplJ6y8EzVA91cW8La7hgTOTfH8tp770e1Kb/wWQqavfVCx2+XxL3T4ol2rdIs9yxt/IBzxtMPoI7CrlY5N+dd+K4gQq5PbJdH+y+2vjKCZGl7JDP2ya6YINrzQzV7wn9aO6/9l7svbU8xNt7ZlhVejNjSfUrmu2PGbhByf1ioW9jp4fAxB/efvlAQu5GN7vLozS/Z1l6TddIxp2LoM4mOp7rfcfxE1xayPTqucFVcxLJ1CxV7kN/vJZug6vBB0L1IF3a51Q7Dna+33LC+8ZePHMpzTJq4+LdjYfMat6i8I6lqnL5jn1mNEj9P+uirpw9E+LV4k1WHP7p+6flnfg/Snsab5/Ze//va/EcLq+7t+cbc7zP/Vd7r+8atTNF7Dr7c7LnFJV9F7X7oXP8L454/EM49/tjjz6XNK5s=
*/