
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
unY+d5BeUNo7U+7gbr8oCjNPPMmyL97P+kHBvFYswE5vhH63l/1+5l60dwEyM/0X8I1DYtTm7gSyCqb4ZBgJ6Glp6J5mfLSBzX7SxCSKGh/G/edwTVaHKldZbZJrWtXZqB6TSWMgJK7Yz1yBgbj1vEEGlhRF2l6eoSVvcyCKrkCjbLhSRPaYg+UJKpy5C0zk52h9iZZ9+VLMV3qN3X8I5wuLiJV2CVcFAa3WU7y5aMYC+A01xMgafKIG95Ead4eN7m6PYK4Kyn26nrArgmp8wkY1EvKLV3gA5Gx8REOjcdE+zXj/zyjG+48jFfWgFZMQyEkCWwiyWCG8NC59zM4BFCmPudF+zrGAJWxb64Cz4C7S52PA7LV1dacCgQZjrY4UZSuXxCWRJKBE1dtzgcNmHnkH5Ejzn8y01USl39aJ4al8SQyPRdhU29wdiv7tfKUjWgIpWigBPtssbhqJUxQM0Z586dsCZPA5GHaHgBMY8RyM5Qd9QWY8j+ljDhLuFCbcEJOvbr4O60AF660Nwjr8YLv/GdaTtibCSnYx220aLfeAmxQouS4t4NOwmKo37yS3Z89DJsYDcJjGp2G3Z3UubOHFHELIHvWqqm8HeQVtdEb0eURbGwUqwGp+BAkE5r88jw1EoxQpk2QMZcKvzgIChQRofylQrqdmEGF6GF4Ys/hu8izT7pB4IE284vshSLxyzCOYH6JIrqUAokeQ
*/