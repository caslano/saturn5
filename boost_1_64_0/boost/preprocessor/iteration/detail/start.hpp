# /* **************************************************************************
#  *                                                                          *
#  *     (C) Copyright Paul Mensonides 2002.
#  *     Distributed under the Boost Software License, Version 1.0. (See
#  *     accompanying file LICENSE_1_0.txt or copy at
#  *     http://www.boost.org/LICENSE_1_0.txt)
#  *                                                                          *
#  ************************************************************************** */
#
# /* See http://www.boost.org for most recent version. */
#
# include <boost/preprocessor/slot/detail/shared.hpp>
#
# undef BOOST_PP_LOCAL_SE
#
# undef BOOST_PP_LOCAL_SE_DIGIT_1
# undef BOOST_PP_LOCAL_SE_DIGIT_2
# undef BOOST_PP_LOCAL_SE_DIGIT_3
# undef BOOST_PP_LOCAL_SE_DIGIT_4
# undef BOOST_PP_LOCAL_SE_DIGIT_5
# undef BOOST_PP_LOCAL_SE_DIGIT_6
# undef BOOST_PP_LOCAL_SE_DIGIT_7
# undef BOOST_PP_LOCAL_SE_DIGIT_8
# undef BOOST_PP_LOCAL_SE_DIGIT_9
# undef BOOST_PP_LOCAL_SE_DIGIT_10
#
# if BOOST_PP_SLOT_TEMP_3 == 0
#    define BOOST_PP_LOCAL_SE_DIGIT_3 0
# elif BOOST_PP_SLOT_TEMP_3 == 1
#    define BOOST_PP_LOCAL_SE_DIGIT_3 1
# elif BOOST_PP_SLOT_TEMP_3 == 2
#    define BOOST_PP_LOCAL_SE_DIGIT_3 2
# elif BOOST_PP_SLOT_TEMP_3 == 3
#    define BOOST_PP_LOCAL_SE_DIGIT_3 3
# elif BOOST_PP_SLOT_TEMP_3 == 4
#    define BOOST_PP_LOCAL_SE_DIGIT_3 4
# elif BOOST_PP_SLOT_TEMP_3 == 5
#    define BOOST_PP_LOCAL_SE_DIGIT_3 5
# elif BOOST_PP_SLOT_TEMP_3 == 6
#    define BOOST_PP_LOCAL_SE_DIGIT_3 6
# elif BOOST_PP_SLOT_TEMP_3 == 7
#    define BOOST_PP_LOCAL_SE_DIGIT_3 7
# elif BOOST_PP_SLOT_TEMP_3 == 8
#    define BOOST_PP_LOCAL_SE_DIGIT_3 8
# elif BOOST_PP_SLOT_TEMP_3 == 9
#    define BOOST_PP_LOCAL_SE_DIGIT_3 9
# endif
#
# if BOOST_PP_SLOT_TEMP_2 == 0
#    define BOOST_PP_LOCAL_SE_DIGIT_2 0
# elif BOOST_PP_SLOT_TEMP_2 == 1
#    define BOOST_PP_LOCAL_SE_DIGIT_2 1
# elif BOOST_PP_SLOT_TEMP_2 == 2
#    define BOOST_PP_LOCAL_SE_DIGIT_2 2
# elif BOOST_PP_SLOT_TEMP_2 == 3
#    define BOOST_PP_LOCAL_SE_DIGIT_2 3
# elif BOOST_PP_SLOT_TEMP_2 == 4
#    define BOOST_PP_LOCAL_SE_DIGIT_2 4
# elif BOOST_PP_SLOT_TEMP_2 == 5
#    define BOOST_PP_LOCAL_SE_DIGIT_2 5
# elif BOOST_PP_SLOT_TEMP_2 == 6
#    define BOOST_PP_LOCAL_SE_DIGIT_2 6
# elif BOOST_PP_SLOT_TEMP_2 == 7
#    define BOOST_PP_LOCAL_SE_DIGIT_2 7
# elif BOOST_PP_SLOT_TEMP_2 == 8
#    define BOOST_PP_LOCAL_SE_DIGIT_2 8
# elif BOOST_PP_SLOT_TEMP_2 == 9
#    define BOOST_PP_LOCAL_SE_DIGIT_2 9
# endif
#
# if BOOST_PP_SLOT_TEMP_1 == 0
#    define BOOST_PP_LOCAL_SE_DIGIT_1 0
# elif BOOST_PP_SLOT_TEMP_1 == 1
#    define BOOST_PP_LOCAL_SE_DIGIT_1 1
# elif BOOST_PP_SLOT_TEMP_1 == 2
#    define BOOST_PP_LOCAL_SE_DIGIT_1 2
# elif BOOST_PP_SLOT_TEMP_1 == 3
#    define BOOST_PP_LOCAL_SE_DIGIT_1 3
# elif BOOST_PP_SLOT_TEMP_1 == 4
#    define BOOST_PP_LOCAL_SE_DIGIT_1 4
# elif BOOST_PP_SLOT_TEMP_1 == 5
#    define BOOST_PP_LOCAL_SE_DIGIT_1 5
# elif BOOST_PP_SLOT_TEMP_1 == 6
#    define BOOST_PP_LOCAL_SE_DIGIT_1 6
# elif BOOST_PP_SLOT_TEMP_1 == 7
#    define BOOST_PP_LOCAL_SE_DIGIT_1 7
# elif BOOST_PP_SLOT_TEMP_1 == 8
#    define BOOST_PP_LOCAL_SE_DIGIT_1 8
# elif BOOST_PP_SLOT_TEMP_1 == 9
#    define BOOST_PP_LOCAL_SE_DIGIT_1 9
# endif
#
# if BOOST_PP_LOCAL_SE_DIGIT_3
#    define BOOST_PP_LOCAL_SE() BOOST_PP_SLOT_CC_3(BOOST_PP_LOCAL_SE_DIGIT_3, BOOST_PP_LOCAL_SE_DIGIT_2, BOOST_PP_LOCAL_SE_DIGIT_1)
# elif BOOST_PP_LOCAL_SE_DIGIT_2
#    define BOOST_PP_LOCAL_SE() BOOST_PP_SLOT_CC_2(BOOST_PP_LOCAL_SE_DIGIT_2, BOOST_PP_LOCAL_SE_DIGIT_1)
# else
#    define BOOST_PP_LOCAL_SE() BOOST_PP_LOCAL_SE_DIGIT_1
# endif

/* start.hpp
mYgPxy3keCU6myU/OH4tm3eR+S9TceThKkSeivtO54xAn0dfC2tQzQM+eZw/v+9sxGL/fpb/YBUVf2x14o1XTttAPbaRJuPErhN8Ybz4Aaqqa2cJoVQ6bWKxB4nPYZ8hr1k7mJFUkXPgA+X/3jH2QHlttWYPAj51xQP6Bv4GUo8gOefhFSaMxfDV3TgxwGMLHgo3YaKcEJwmQRYxBxbF8QnGSYkssv18v76eb0a2b2DT3STxEw3FPeKwmBz2kcNWcVhKDu+Sw0o46HFgUZgTq4iki6ETa61yVsuNM/Ww7XSlXIvwcuvclsvpSzwPZ4TuhtDfruLQ3fg1BQp9pQ6dr75cJaGnwHlzOi0NnNQfiBWBR4jYLxb7XMt+vlurxuDyi+cay7ON2OdZdk8qX8NPFltHABYFyytutX0esiOvqZXO5AZOfIettloGd/uaWm2qEa9d8AL66Rb6J1KU2DEnspo0L/XCvlbmEHMyasPw17DcwhUUAr2qzyZrA28kJgne2RqvebkqnKd5AC5hzQ2iPKGzOBaaPVSWGAeZZ4gYQ94T1BM7LbCJ8BfIZW4BAgVVOdypa357FEX740Kx+I9xK2VFT6Wlnwl4vddwtxJOoNw40Tb3xIfDs3Pando1G3ctrax+wersvKTJjsUVZL+0jPqSPSVsG2IxP5WlslkuqZfGX0TXtXnOUJmn3W+DO891qvl8Ed/aI/e4yzA2OOFh0ayw4XLYqa7gmJlhNfEPTDF/gmanvvz6XLR9UFUPZleqmgLgeYx8sUu4xCgAChLcmrCK4/N58yPgMs8wDjDldSIsls4wf1jlYbYIq3GST0aD+v2djfzdn7lWC2KlxvZ9lzQ5A7ZPSWECpdBJS5D/6a92s93+s9NscRziSBrmG5qSu33ZFNkbK/U2tlaH2kS13QVokXpZLN8oQ6WmRpiPCLJI7NBrJzKSrr5bwTHyEWPoSTFusGPskhj5HGMtYhgVe5tmp4+VHcrKPcxjhWDETD/tBF++TH+PSnF4S9NoaSutKpmkrkeExIsIVeWWG0YMPxSdG+cLVLpEgeNhHpNb4YT7PNi9btg1wsU8lxfw7foJ2k0Vod4SBUdgVHk8PXnJ7zreaQ1FIRJZ8FuZBcrC//Je2kouU9n3xICMQg6iUj9Ey/Ook+qwa73dTBJqLEKp25cLhxI64HDh0JNuzao1XNb2TT3K3CTZlmauCYdJWPWkil+/wq54tE2X5VwpqnIAT1h0dXYsTcapv2Y69gO/iD9thd72knQZtr7p6pNXCUdItQaOuKgSkvvUU4LqOOP18oRpLDyprIVoTFpkiZM0SmthXFaRVS4fVRapPCZiwxlhdHtjMP7y6G8oBsCm5i7eRbPE4j2HcENG7KsexKp7SOghFdWHm0G48XDUX0NyWMZSZ8q4ZplwtBoUwdjleFQskwvkEiBM6VM+t/Spu1c5fYqmcDiNg5P0qdyUPjUUrrpPDeQ+FUUaiY/B9YFNP0qDGdx+S3co1MkcPiWlNI0IpvmR+gehiGvnK9Z5qCfxEwiV+XU4gmQIncxjLXphIRWpXD0OH039jaOBUC8V890kK2K4HBLG1RzIZ17chJZ4KVy1MbBM2Kd6ITMkecX3h7kOgk6MIGAsrS/Fhu3EOh0R5l0w8wGkUv2wWt/0T8k2Kpy40yXxxEdQl1mpXkegUM/9qqwMnQeyjtwJY8XGyFub9pXmrzrdbjhCnK5uAB5jjIN31stSqCwUynGNsmum5g4qCann/pDCmR9GHoz6k5J6dJk1x5yv3JTIlpMCTLYDtFKfA398Nnd6s+i/JzhKFKj3rWlAR6ftDaQQFvDi7y/7sOfBcDjMcgARtRJ7V1Fa0B8=
*/