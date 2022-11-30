
// (C) Copyright Tobias Schwinger
//
// Use modification and distribution are subject to the boost Software License,
// Version 1.0. (See http://www.boost.org/LICENSE_1_0.txt).

//------------------------------------------------------------------------------

// no include guards, this file is intended for multiple inclusions

// Type encoding:
//
// bit 0: callable builtin
// bit 1: non member
// bit 2: naked function
// bit 3: pointer
// bit 4: reference
// bit 5: member pointer
// bit 6: member function pointer
// bit 7: member object pointer

#define BOOST_FT_type_mask                            0x000000ff // 1111 1111 
#define BOOST_FT_callable_builtin                     0x00000001 // 0000 0001
#define BOOST_FT_non_member                           0x00000002 // 0000 0010
#define BOOST_FT_function                             0x00000007 // 0000 0111
#define BOOST_FT_pointer                              0x0000000b // 0000 1011
#define BOOST_FT_reference                            0x00000013 // 0001 0011
#define BOOST_FT_non_member_callable_builtin          0x00000003 // 0000 0011
#define BOOST_FT_member_pointer                       0x00000020 // 0010 0000
#define BOOST_FT_member_function_pointer              0x00000061 // 0110 0001
#define BOOST_FT_member_object_pointer                0x000000a3 // 1010 0001
#define BOOST_FT_member_object_pointer_flags          0x000002a3

#define BOOST_FT_variadic                             0x00000100
#define BOOST_FT_non_variadic                         0x00000200
#define BOOST_FT_variadic_mask                        0x00000300

#define BOOST_FT_const                                0x00000400
#define BOOST_FT_volatile                             0x00000800

#define BOOST_FT_default_cc                           0x00008000
#define BOOST_FT_cc_mask                              0x00ff8000

#define BOOST_FT_kind_mask                            0x000000fc 

#define BOOST_FT_flags_mask                           0x00000fff
#define BOOST_FT_full_mask                            0x00ff0fff

#define BOOST_FT_arity_shift                          24
#define BOOST_FT_arity_mask                           0x7f000000


/* def.hpp
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
*/