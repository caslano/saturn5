
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
N6Zo3piZ5dPKS58tRGmTvk79/fkXlzw58vKlH3Y1nXu24/l7wqt8kLV+87ydT6yJ7LEsSHu0XdFscvvGWz4w7G49+0TkyL7lnuH6Rn+Hnzyx0jxn1eczVixtWbxvaWa/Y/GDE9HnHV+3T13RNH/Vns8zXrhl4nUVQtdTfv55+HLZ0etuWN0lN06Jn/Zyfxqy6X1fTJfNfPeFh36PCUOaMEuH2t638MS0JY+P5L6beu7Oofcfajp/17qW396pQ39fzN5+5O21yzdsXD/t1ttfv+utnT/tjx02t7Xu7OzXjS3OD/dstH/LHzq73VRhNrj373j3O9Tth6WnF/W74aMzPz/V/6ZPZ1a+xNw85dzHNzdSxcX7Z4aXLUzv/9HDzbdmIwwa9r/6sm+d1G/XSn7vV51bBrRfZzkzYWS/nR8PfvbXOUXtr732ncF7uMfLwlzL0AfbnprXY98Xuf1m9Hrxvim3t/nh91f/7JDWZhM6sHl6+z7hRbvCzzx104y7d7d+dmRCs02mGQt1Hy+OG9P47YgNUUcPXTywW/fHYxd6dM499Ind337dhOfG3IwKW32077eln6v7i/x7QC1bI1Dd3lpXgU7n1m+9r/8M4aZTUaf7nm39qGV1+50lfzTLfdL5+0ZTd93Xhum/HGv/6rkWoycUvdNj7Z5lp+afWDbm8FuRY/468jT1M41rnrz9tRtf3+e8eNPnp4TnvtX8fSPUxfP58pMzS1IGNV+ZE5/DrPo6YlnB2/Woow7ZrDMO2eN6z3ygaZdt4zoNiBvAHP84dfbllsbpCxdtRH998O2HG+5pta1T8qltXuPv7OvJHRcknj9/Qpj69+gFOjSlyer24QnXlP90X883t8+/9vfzRWt2J07lZ+jOR46iCm513HO073yuc3iH7uGfHP4SIe32UhwzNMgxLUjQRa3YvPb+dfccF5rOffb+Hmtf/LT7O7k7P7qzFzu6fUzCwdLYJhGn+hQu+1p3S2TMvKMJkRte9F6K7XXHe6+yhpO7GaSCCRWX37tr8/GOt3RYi34sf0br9yJdoT61fwsiciW6MqBrFN5pSPnu9LlDbhow23xq7k+GPd2NXd4aM63N/Vyryp0buo7L7pmo++irpBa3PBX7j0UX7mj8Uyp/bEbGjmPtMpf8ON6cmBff0lT2Tefxuioajm/qs9db1v2OqpmLM2695tY2A010fHaF+Cz7vlJwnWhxTy/H55ujL83dc822e9+8Qj7Qhd1Z3GzXlvGOZ1Y/P7/9ipghux//uzQjZvmqZ2ZnTfiz++DYARWr/mh0IbnbP179ZtF3j+Q/4Kr89pc+v3bbMnrGhidmff/dkvN73twz5wXGEF5UXHi5a+tbXlt4ZN+L14e9PJI/F5bQ/JvKu4sqdrU6+W3Gm7NvOBteRcPvi5Ifm3zpkfmL2twe0euu3ze+1Ni/veN9402QMOuKRHUooEOTTxrZhdlvbez/wrwWU+/t1Pzvpvf/0HhXbo8Nn2y58OddO9+Z3O6pV9avN//Wuc8LL40e+snxsH6Zuh+4RtfelZe6YWuHDdsjop6In1ze96EHV/c4oh/JHv858oevjPbU4++OunH9E6umjbP8krX/cM8SNLMqAFw23vPivp+Zoc3fGT190mc/HN19e87Ee7YcvtX4CR1P8eDLoUtfWT32whfLKzoNapqbs2dEqrnTtf8hH+tQp2d27vpt+YmJOf/0DrhzWMnML1L7nDrzTdEw019Lv9jQY9e6lY+/6L67r/3zaaPX5xdsir2zVaFRd0fW5L1zv3kpu+S6yVaveXL6LYeGnyrrMKKy4+Xb4396PPxgtwlz5recNXJM+KbnJlfkFW6reGwNMr3wyXM=
*/