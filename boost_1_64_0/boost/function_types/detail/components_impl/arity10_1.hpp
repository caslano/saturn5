
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
tj6Q8sUTy2efcOdGeB/hT7u+SHCuu84E7jYwKZBjc7Eu12YFTeIdKdgjlv2MpcxYyo5lv921Lds+IvhdKPslWOv6LNdORFvm8nDHGYsW++92vFv4nliOT7AxluNx/Z7rE13/JrjT9W+x7K/gLMnrFOEz3DaBHKOsPyV4QrBV8EfBtwU/FzwZ+t/gfNRdt+IfLhjkzoOs7yI8WDDE7YOgRFDJb3KvkfQF4mkJpVxZn+z6JHfMsr5ItB8Jf0L4O8KvhnKeXdsT3ls+axeMEdQIfhbLfgkqBG8K9hL82PWRrj8VjBXMcf2jYKfrd13dCd5xfaug1LWTwH/H7q6x/+7c3VwdhXLsodSXa4eClwVPC34qONWdD+HewpMF+wn2FxwgmCA4SHCg4GOCiYJ9BR8XVAlmCg4XHCGYJThacJhgnGCKYKrgEME0wXTBDMGhgoMFRwpmC44SVAvGu7YkmCTYU5AWlAvmxv47fXu5a9zVp2ChYLHgCkGtYEnov/+xRTxnC/oLzhGcJzhXMMD1jYK17jwJBgouFOTLdme6/RM+NJT9C2U/XVuWzy4VXOb6clmvF5woqAvl2F1/GUm/Fcr+C44NpQ4E1YKjBDWCOYIqwUznF8xz519wTCjHHcqxhVJXgrmCWaHUmeAIQT8pb0RK2q2k33X3sdD/BuFeodRBKHXv2oxgrGAfwUTBBMFkQYVgUihtSTBOMF5Q7Nqoa5eBtFfX74dSF6G0X3dfCKUtuzJDqa9Q2nYo9SIY5Nq664/dscn2xwl3E8wXLHB9juAEwSdde3L9t+xvnqQjQU/XjgS9XNluDBLJsQhuFFwv6C6fLRXEgttcXxJIewulfQkOFnxMcJBgiuAAwf6CQwRTQ/+9y4Hro4SeEvxC8EvBjkDasuufBc8Ktgt+4/p5d48L5HoLpD8TvOLuvYG0fcFrgucD6ZsD6aMFzwRy7fN7p08E0he4sY3gV4JtfKHM5kCuQ37T+k+BXHuBXKOBXJeBXIOB9CGBXJOB9LGBXFeBXMuBXNuBXL+B7LsbA7j7uBzD7sI/kfUfCR4PpN8T/C3wX0b9V6G/BHLuBe8F0ifzPcPfETwm+IFgi+D7gu8Jvit4WPBnwTsuz1j2OZZ9jmWfYylH8JzgN7EcbyzHJdju7k+C12I5dsHLgldiqQvBs7H/PuxnYjkGdx8QbBU8HUt9u/tPJMcSSj0K1wZyDTmWzy9393z5/D137QqXu/btzo2sR7H4Zf0bwg8Jvi64TrQad/7k82cFn3H1LPx4KOcslLpzfbH4nnL3dHcPcGNZ8UxwYw7RdoZyzKEccyjH4/psty+BXN+CiwPp/wUXBfJ5JBxJXYjnblm/wd3fJH21uz5lfVbgfwN0f8FR7rmkYHYgbc/NrQP/+6aXuPm1GxvJtq+FUjeC5a5OhU92YwDXLoRfEbS7a8ON74QfDGWfQzkfgi2Cr4Zy7IJNoZw7Vx+h/z3LbqlMsw6+Fsj1GEgdBf77kAcEch0Gcl0Gck0G/jcNB7p7rWBvNxYLZX9kw09JeZ8UXBvJcQvqJF3vrntXz258EcpxC2509x1X14LPCj4nOMf1QYEcRyz5yrbvufu+YFgobUzwsOtb3VhLeIXwZuEfC/LdfU/8p4aZZhs87/J3bdzdNwUjXP6yfpzbxs0D3DxB8IibH7jxvpsPRFIPbh7gxvVu3C/4gRvvR7K/7vp213wkbTqSMgXtgp9E0i4FPxM8Ifi54EnBU4Ktgqcj2U7wjOBZwS8FzwlCV8eCcyXPlbJPFwvnyXq+ICWIBfWB1IegUbSTIvksEl1wluBMwRmCsyPxRJKPoMWN213ekeQdST6CEwQNguWCUwSrBE2CkwU=
*/