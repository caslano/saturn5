
// (C) Copyright Tobias Schwinger
//
// Use modification and distribution are subject to the boost Software License,
// Version 1.0. (See http://www.boost.org/LICENSE_1_0.txt).

//------------------------------------------------------------------------------

// no include guards, this file is guarded externally

// this file has been generated from the master.hpp file in the same directory
namespace boost { namespace function_types {
typedef detail::property_tag<0x00000200,0x00000300> non_variadic;
typedef detail::property_tag<0x00000100,0x00000300> variadic;
typedef detail::property_tag<0,0x00000400> non_const;
typedef detail::property_tag<0x00000400,0x00000400> const_qualified;
typedef detail::property_tag<0,0x00000800> non_volatile;
typedef detail::property_tag<0x00000800,0x00000800> volatile_qualified; 
typedef detail::property_tag<0x00008000,0x00ff8000> default_cc;
typedef detail::property_tag<0 , 3072> non_cv;
typedef detail::property_tag<0x00000400 , 3072> const_non_volatile;
typedef detail::property_tag<0x00000800, 3072> volatile_non_const;
typedef detail::property_tag<3072 , 3072> cv_qualified;
namespace detail {
typedef constant<0x00ff0fff> full_mask;
template <bits_t Flags, bits_t CCID> struct encode_bits_impl
{
BOOST_STATIC_CONSTANT( bits_t, value = 
Flags | (0x00008000 * CCID) << 1 );
};
template <bits_t Flags, bits_t CCID, std::size_t Arity> 
struct encode_charr_impl
{
BOOST_STATIC_CONSTANT(std::size_t, value = (std::size_t)(1+
Flags | (0x00008000 * CCID) << 1 | Arity << 24
));
};
template <bits_t Bits> struct decode_bits
{
BOOST_STATIC_CONSTANT(bits_t, flags = Bits & 0x00000fff);
BOOST_STATIC_CONSTANT(bits_t, cc_id = 
( (Bits & 0x00ff0fff) / 0x00008000) >> 1 
);
BOOST_STATIC_CONSTANT(bits_t, tag_bits = (Bits & 0x00ff0fff));
BOOST_STATIC_CONSTANT(std::size_t, arity = (std::size_t)
(Bits >> 24) 
);
};
template <bits_t LHS_bits, bits_t LHS_mask, bits_t RHS_bits, bits_t RHS_mask>
struct tag_ice
{
BOOST_STATIC_CONSTANT(bool, match =
RHS_bits == (LHS_bits & RHS_mask & (RHS_bits | ~0x000000ff))
);
BOOST_STATIC_CONSTANT(bits_t, combined_bits = 
(LHS_bits & ~RHS_mask) | RHS_bits
);
BOOST_STATIC_CONSTANT(bits_t, combined_mask =
LHS_mask | RHS_mask
);
BOOST_STATIC_CONSTANT(bits_t, extracted_bits =
LHS_bits & RHS_mask
);
};
typedef property_tag<0x00000001,0x000000ff> callable_builtin_tag;
typedef property_tag<0x00000003,0x000000ff> nonmember_callable_builtin_tag;
typedef property_tag<0x00000007,0x000000ff> function_tag;
typedef property_tag<0x00000013,0x000000ff> reference_tag;
typedef property_tag<0x0000000b,0x000000ff> pointer_tag;
typedef property_tag<0x00000061,0x000000ff> member_function_pointer_tag;
typedef property_tag<0x000000a3,0x000000ff> member_object_pointer_tag;
typedef property_tag<0x000002a3,0x00ff0fff> member_object_pointer_base;
typedef property_tag<0x00000020,0x000000ff> member_pointer_tag;
typedef property_tag< 33287 , 16745471 > nv_dcc_func;
typedef property_tag< 33377 , 16745471 > nv_dcc_mfp;
} 
} } 

/* preprocessed.hpp
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
*/