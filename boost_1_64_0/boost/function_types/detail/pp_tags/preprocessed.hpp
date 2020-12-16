
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
5UFoPetrKbjl5QR1SsdqvS37t2pM1tvR7/re48DjgXNb5WRyFSOuXz2v16zpsxucOrH3jsqTu1qlp8S27tiiaacNZQuDundpEDBhzOhOkTExXu38fdp1bNmsc8qYqBY3qg8P2b/zoG+2NqZboOQTGBsZ6y1JKmnV0kWdqqoqpKpzO7vur9jv07pVo7brVs8OWDhzSXOVl5dXkXXU3Vs3L7jbv5VXq8oTO1teOnc02GyOVC8sWeg3JKz5PevL5gaqQz1Dzxw/0unalb0DbObY8EtVh4NWLJ3dxserSZP0tBFtJ6QkdsxMG9Vh28ZFQ/GRO4/uknf3jv5+Hc3WmLCVpXPb+fur/A9XHParvrIz9PTxA+2DJL+gC+f39TRbokNLZs70Wrl8QYfK4ztazJoxp+H+HQcaZ2dHSikpkf5la2d2u3j+UB8/j6ZNt2yaM2DVssWdE2OSm2/Z/NjAzNSRd+7eubdhkTk+Yt2aOT38W3q23LB2Sb9Tx/e0ydZEdanYtctrS/ms8MioKI+U1OiW0yaPHrpw+qKmPiofn46tmt+1cuk8eVt/uxaN23urvL1T0mJaXbu6b2DV2R1dblw+MtRmGT4gqFvzft27NepZXl6injtzQRM/z2bN1q9d0KdszYyuxpyk4NLlM1slRo1umqdJ6DXNnDjEx6NxYx9PX99tm5fcc+n8sX7VV3eF7d6xp8GsmY81au3v3frGlaPDdNmx3c+cONo5qGuz4PiYUU3atfS909uzYUOpi0eXPO2oPrqc4T1Unp6e1y7v6V+6bEbLuTPm+/qp/PzKN88Mm2ZJGlZZWeFfZBk5ODZmRKMVy+bcceHsnoDuXRv2KCkpUW1YvajvmZPH7ipbPb2LWq1Sh4c1GrhhzWJcQtdwQOsWDdpIXT27Rqh9Iq5V7w5ft/axnrFRcQ0SIxP9SqZP97h49kCvWSWzvFcsf6xteEiD/vt3HWpyeOfRZkPUfkPMk6NC/Ft4tNi9a1+judPnNbZNjut//eqhu0+fOHjn9er9EStKZ7XOHJPQvmTGDM/dFbu9b1w9dk98VELjiJDGg3TaET0rKipUh3cda37q5L62W8vnRvh5NW++cMbiZpHR0Z5SN69upUuntzBmJwadPnmow7qyWd3D1d7h1Zd3hMRHxvtU7NzpadQm9xsS0nRoUJemfSOxfWHbpsXDhoQ2G7atfOGQih07PNavmd9766b5gxOjk5qlj4lrExHW5O4zlYc75mXHB06zJt+zqnRhx9OV+9vFR4/0TU8dfofNOmJgWVmJdOnskb6x0cMbbtk4u39gtyZ9dJq4gOtXDg6uOr+r29aN8waVb5wesmr5krsmpCZ1vn75wKAL5/b2KN80I1Qd4hFy8dzB3kbN6L4T0pLvulC1u3t1dYX68I4jTeeWzPVp3bLhHRGhvoMzU+Lbnarc3To7J7prYJfGvby9GjVSh3mFXazaH9iuVZMO3h4NGhRNThhUWlrin5czsndgV9/eK5fNvxMiikCQi6huEFR7HZruMFTmDFSgHM23FWq+ASaSjaqmQyS7YeqxaCIj1CcPZpgJ1a9AltnISo2qbUHWgahuGSCgCmJfB0ipRJOXQqT+UD1vmGpHNOU2qEk4VDIeqnsJ1ZgLkRhh/usBGa0h1t2oVmuozjWIpAKqEwtTqQJEnQJMMPEMgUgXwtxXAn4CIYpEwMU1iGkI4GYdmu86zNgP6nkGojiN5g6EquugykUwse4wtSCIvBqQYIZaRKLZTsF0I6E6FYARM9RIB/jbADOcCzO9BlXfAJUvgSl3BOztB6QEQQ3WQ3XCAWOVgCYfQNklqPVFwOUEqOgKwGU7qOt1QFY6zGIDoMAH5rk=
*/