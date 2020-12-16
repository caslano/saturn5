
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
5jFsG/BVF00cpmmysqfkuytAn9KkIVm6aJqjmmY25QyMrn8C/jrVkqX5UaVmV4dKJe7kw8ptuB4VO+0bsUe3tLbSgEw3xmqu4LGUtWioozTNGsiBbUSNAOHg0K5IqTIZ6RnsiWRL2UhfbCDmtJ90Me2zA32Px12YLNTHon7STzrTTs4/9XFLudN5J9/CXa5Y09TX3feXuG6UO819PB0nBbfDFQvl6XbyG+hPElLcVp51FIFZIePcEhLCnc2Uxh9MOaCPcA/W3T3xSISGvbRVjJcK1JqQGfgRrxHpy1Mok3pvlWbh4zTfjVa9U8AUeCPGvOGbImbyJk2e3HFnKBWL9vd0Mh0pZDtpkM2Rd0LfctzbJ/qFmh/MzHJXtWtONtRIFXPGJk6H9jcUUSk4o5kBgXc8ohGQEopBhQcjp55KNOGZjVPXoluupRcVaHfbpzuMpEMbS3m9uPDE6g8XixvDvPxAfx0yp2PTqEnWqR5L/qUMEq541ec95UC36ujo9ujWdoxXA6k+Y3T7ZnaXVaOL0iIkr6cJamBOU8VQi6DRPVo9UHJJlIeZ0dM8nnO5dtq2t2Msdt3twt3hcbd3bIfedUPPbr9+y1bWm5msnY4eoCYQTfXG3BsAjRoDac/MuN/KVEp2aaJqEGO4VCyRira1d0UT8W5dTqat3JS5cZ87M57x6Qd3+vWlCa1nPi74jIen7PvjIzfiYzfic/WIj3nE5/JxwXvjo+LyxafciI/diM/VIz7mEZ/LxwXP8eVott6nGnlNTTppgMjqgu4lf8NDGGBwyXB0xwsJB4YvGV86n++z7RqWsUHxksKAJNzOkMmDXZgdjyKLGUWZBotaJh8pW3m+DenP9bFNDW1B/noCgyAur4fceJ6WiD7/XWpWhH2Q2JYUGSlOChOZNE1mJ4ulitknFdK+6046002Mm2rq53AY2zM1vmvRGqQg/VM0UrijNml2xrva2/M0IuVp9euxM5Di24N7z6DizqfVGt1NzwSZK2bzs3E9AXXvd2ppbPJdjgPIcqtMpovWQzCeuv49qRjr9tfSeTKwJz1u5vNmtj4pHKH5VM1WmzLuPgzdWUpZSt2Q2uXxTOcLnvtpZSJD+VV32PHSjEp/erqkkmj2UNFPQYSyo52gcW595RwtXglVnKhoaovu2qWg5gskluUtN43gT9sBVRr2XfdeqlKUgk8Xo4m7molJ/z24h7j9omAO0z2a0lk0kXDMOyom3by4Zkq0Dqi42Y9QVqr9paxKYZa3KKR/t3efbcjMlCoo9MB+075NMyiXUX+AYsrvtgdj8EB/GIj1Jzw+VNKljKUaXb05Cn++R7jlkKR6Sef9jYBXaFzuhdK4lQ8sMehVbYbTst3XE1FymzTFtnQ+/OB00ayi/LltJp1dNZqyYIPFqx+vWXm1qOUIsqnYdbpLoPyIy5t7zGkzz/48f6pWTLPfKlqFWsFL+fn0jOBFeYntlEi2b3jI1JNox602Y0uedulMNWxqY9DP0Hx+pGjR+lz2BLQPNZ0p5Opl1N/XnzD6e1OSj+bMtCoHW/qPl7IY0DDfIeVMtExjmZXORwvYWZN8oZavWkokFbQANytO7akycZNL27C1bKk4W9A2bLPqmcebRoJmx7TbXLRo71Zv5YidMgoQzagZNbdz2p2m8jCcSTb4gj2ZmIFdJMswxe6N0qkputeuntO6brVRxoboM/arpC1XP04pzrputcyODWCkrbt5i1HqBot5ihruQV61M98n9JoX7pGi2pc2kQSvvnewp69YrlWlvxoVaYXcnZ6cRN0F8dO0vyQkkreD+Xi67OQ3Ze4X6S9aVQrFuXD9o8PdKY8bmuB07SdtYH6W8R9d4u8=
*/