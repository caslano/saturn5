//
// Copyright (c) 2019 Vinnie Falco (vinnie.falco@gmail.com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/boostorg/json
//

#ifndef BOOST_JSON_ERROR_HPP
#define BOOST_JSON_ERROR_HPP

#include <boost/json/detail/config.hpp>
#include <boost/json/system_error.hpp>

BOOST_JSON_NS_BEGIN

/** Error codes returned by JSON operations

*/
enum class error
{
    //
    // parse errors
    //

    /// syntax error
    syntax = 1,

    /// extra data
    extra_data,

    /// incomplete JSON
    incomplete,

    /// exponent too large
    exponent_overflow,

    /// too deep
    too_deep,

    /// illegal leading surrogate
    illegal_leading_surrogate,

    /// illegal trailing surrogate
    illegal_trailing_surrogate,

    /// expected hex digit
    expected_hex_digit,

    /// expected utf16 escape
    expected_utf16_escape,

    /// An object contains too many elements
    object_too_large,

    /// An array contains too many elements
    array_too_large,

    /// A key is too large
    key_too_large,

    /// A string is too large
    string_too_large,

    /// The parser encountered an exception and must be reset
    exception,

    //----------------------------------

    /// not a number
    not_number,

    /// number cast is not exact
    not_exact,

    /// test failure
    test_failure,

    //
    // JSON Pointer errors
    //

    /// missing slash character before token reference
    missing_slash,

    /// invalid escape sequence
    invalid_escape,

    /// token should be a number but cannot be parsed as such
    token_not_number,

    /// current value is neither an object nor an array
    value_is_scalar,

    /// current value does not contain referenced value
    not_found,

    /// token cannot be represented by std::size_t
    token_overflow,

    /// past-the-end index is not supported
    past_the_end,
};

/** Error conditions corresponding to JSON errors
*/
enum class condition
{
    /// A parser-related error
    parse_error = 1,

    /// An error on assignment to or from a JSON value
    assign_error,

    /// An error related to parsing JSON pointer string
    pointer_parse_error,

    /// An error related to applying JSON pointer string to a value
    pointer_use_error,
};

BOOST_JSON_NS_END

#include <boost/json/impl/error.hpp>

#endif

/* error.hpp
JMax9aEpuvUeb+/BWK5G1nr1nMjAvS9txK2/TDv7Bkfn1JdcFMUxLBgAPizB02fvtukEcsFI6AchGlTdwYqFZREELZTVs1sPY2mrF1WNMmQBxd4bToQ2mrPVKqJJIsiwE5HjbPTA4R1Q1DDDYCwCuUxm5VZR3hy/ory6hAvmux+xo6cNHZURopzmcMbbaBsnXmh87Mf/S1akHpBlrg3spNccAs22FYQALphgT2/NO7nhA7LUosE6L7erV5R5HTK1dvMEYOv693g1bxfPqgDmVOZbatNO7Wv85bqW04+P0jPKVCEhUnaAB3KsCnpKvYzXsZJNTPs65SvjSV8ttYutj1k4EJ5P4EdOab1m3FfVHlvlaxBnCdxleWvc8Xs1usbUZBudaacQs8z3WYH1R+oEsBWMBiEBFOKwDpi6oBoDBq8R/UENjVgtTDWEMzWTmznYKWJAheoXJraoa1j5XzZmO++NKvu8e/OcYitchmlN4LkAXni0Qaa4aR4R58v+5luF5U72lKPIgctEz0TKk55snTvPIvHDdBCxjkpEAckAAAjTQZoKUGAiLf/RCN/SVyJGcaShgzw4bXNEQP1Q96ej7C7x+Ss2Q+ZiVBSFgCo48xghgwW02CdSPHkJnloxOiyKfDOWmXox4h6bRy+/oDNLRegsuGUiVG+//DLtDpa9Mia85lAOZWdYwYMkUjVedz/T1xbcLYtDQyApG49IBkcCZn/18KhPfkA/FPlqXLg3HEgErT+T8HYD7AA8/Nu9N00sQtt7tqeIpyVxWQV5zuNAuK+rpMNyIfFUZA/YLId/psJBxUlIK5n936iGY1a8AtR3T1D3PxnW7PViKnbeqd8/B2Db9xfCiIdqu2fe2p8qzLes8pPBhmUkGU8SMQVVmWAvGrgR3OM015jmLOq7qsT05CiB7Iq4d/TYwDYKBN+I3wQup66WhXptda0eBph/leP6F2Qega+1NM14dnQeE/X+7GKwzMdaLAeB9jX36fyNkUgS0iKnQxe6DkOHOU0XhLbmIViP0KnhMqq4UsXpW9xM7S0vUlZXH6htZS9PGp5u69gLi8zRc8Ah9lojcdUF9yTJEwkuG7Ir4jB413/9DRcKDHpmzKKyugSp4O8rBdDBdNpbF38HyvkhHVlKVvNqpVpeB1QEltwdVTbtWIbj4SUpYc7ZPngqsc2JHJn7RUuxMsXSNyE8I1w1Di+MHGn79R6M1xXgf3uoFXNwOBW0hGwBUZb0NBkTBAm8bESlhatJR7CRQy6w/eZIIbn5YeBDAdER8YuHwOXwKYhwZlkdse2g4DME1H3F/zd2tATz/WzbMaUMJIOneeQbcc42uOoHU2cNnI5xScj2sH/cBdffb33COKcbF/O8O0VnpTZQtgRB7iy7NI7zooUqna1ODZooRJZTYfLngtT+D+0ps643nXvx0W8khHuGMqkAisrD2icaLP/OpmW4W3qp9RaRm9XsEsBB5RD7PgCtwxztg7RlAENVyosVRwwdXuVgw3K4vCH59jkwDjAK7ko7GDYj0LAhwFWvndsj2K5eBh0xoSqZlV5J2YnlmKywJwEbUeJbjz6BAZqRoKN27QQ5uHR2oaDb/QclPTfKO/avKqudaTmKEifM6zY5//6vSfqmt54+ocHS22+0MkgL6OG95Sjisi6KFxoDcHtHRN5Vn+KwTod0GArjkWohZ7ZPUUSRr3jUt8PKEHayYjKbgERtg5GcFfVA3bQeeVWd8vfSQL+KBrx6kV+4q3Y3sVGhO/f/ZLy6dMLZffhrH6OIAaX2+mafRQ8uR/+DdKd7Xydq3DmSA9E3poBMTSE+cUtuzTw1MO7ZqvMQmNETeK4P1Wv2jf+FifOCK3OzHex9z59rUcFxqaTevSHZy3YGdMffrvVZum5Chid/qjzwhdJmGP8fmyiNfWrTKENMStdFS1kQfDl/7RcrzbmIy/QwOevPAeKEuH7dYTOvbIDYgcseq1YTn4jZDRg4b1vClT8VlGpmBXXXhML1DMq73WBvIC5WgM7tsI5JyRmv9dpeKfDheY1Tm0oMUrh5BgDe1S+8Kv4H7bU6rFKf2HsbEajZnCZzI0JNnk3McUDCH7ty+hCLnK3lEkOWl4WRUllQErE/s8LkSIysH7ec3Xb5cJ2BcovvjuTEG19hDlI7Q979DkHh+KajG6xpwH8mhZDikBvnRr9rI549nbSDTIdLutoMgcRueGbq+PZNpcpikERt1nfosRBN/xkC4C1s6t4VEvaJr2AqTiOfIyNPTKXGRVpYcTdeZa52uFD3W5Ysnn1PitKtIK5vraywQEEVAj2KOylfgTucQWZO74quCm/FJv4SbKNAeEfAOiZJVKTRbT/vuib9ogfX120p8MttjUFS1TSvHu046Tm1OKNQJRRE597fn35khem0/Df9o+GLD96qB5GebRClv5v06h5qhX60hXCcakMIGq3vkYYLkZJ0X5fEfEt/IqhVPvcFc9r23hntpeM61VID5er9BZqSat/ZrxBMULmsEiBUxrr87/n4OgJhA8zLC+AJS4Q+0x3u31ghcK6OuRMlBAM+sNDCce4IeEPsOXOaZ2kzY7LV1OIcygY4wFsymNg3rE1JpmKp06bZzJUCnU2UF6NOcRIZRsKNGAx0ghSJ4pW2YGk8KxBCpXtP0DMgqW6Gn5OeWXcssXc6npPwetfviXpSmq+/WfqtFp5NeSgbuEUGA9i99+uFPCFxE4g8TnnjMJV9XNAUKCFef9Jvip6FzoHvJVgYHjU70RaoVFPxT6Zpzv7s/Y71YPe2HKgjxMu9cwR82VcpZENg2KXeVO+tm6h7ck/28HE7PaAyrVL9S6dAgCE/AL+JJNO7QQq76xtrJPuch9YoDttALiTiDleRm+9EBFGahEL2k4RVyw4u9UahAA90Wjgf8DqG7TfsfpJtnhv92bdn+laZXG8C8ugh59GP6ASbYi+9oZyBPYb/z2eZ7vLrMCNPidaWf3MbHhoxgOer4O3bk00qs2w3HwBjrMBzJImpPkIHcTP91AgQfDXT35uR17oiK+tGcotFEvnNRM1dp82uMlqDFDTqEy+BPHPBOwEG7a9e1tnHEVqR6YPvgnjplhzu/j2J1MbAAATKWCvF/+HqID87SjU73WQG7yobeLdlNakegRlIAzNw8mxxGwSiR2RDoON+muCG0CafT59F9CKnXyiE0puzY497aizS+mNKJLVQvU8IT/8gOopPMdYlQU3hOnW9GmBxeiFQCk039X7TtZNJcCefIARKExso0L1mrFVFNfFjHk0fA8U6Ojt1Rz4ChXaa7hF8U8GQMYN8dLX0qWwXkdgwRMOVrAl2uEfs4aQ5ICme4zir4x4Khh7L+PdoI4NAi1jnjrOJWc9rdDrA0EWcp91KxSS60qvYdxim+LZ7X0rCIv4SZbNMf/7Hef483dYW/WYmZ6Dli+xsrCH9Q7198LG1tYyA29/oQw7EqMbYphfferDOIPG84T93RdIbtdbfRC+L7TK/ewIlxOAoqj+vsDMiiRM2tBi1CP+gacJfxlECxvehQ/flAJf0dgS6lexQnV/G6TlHY5qRg/9E7/wXgTeAIRoUzcIOgmJAmEhCGAGacqnmUWGqqmsAGqP1tRwZYh2aKUdJ7vlq0J9FBi3czChvOlGhKfXrJhV+OzktmopljXSYa4ZdGjvT/Gmr/mg43SwPBbYQDgIInt2SkJRAJYIexrytlMVTO540KbbamEGy1EKAB6RDq+xjBxCgI0jymFRRqrCONRCYDRhXZ4Ul3lniJCWV1LjNLZ20bHWmoh6+RQHX3ewoTCyqT9Msh7JJvvIT4xDj3CMHKzkaIFohfYNYW2XrNcIS8vP9L6Q2e6ddvcm/C1nxz6H/XvqZnYOjAhX+VpWqzzhYrPy1wG8ZvtUSDBslrbe8tM4SY00rAKJwERjEAhIAFw0AFkWA7/1/sgu32b8OnalziE78ig+XsiACSUfMDradKL3/3PHlSEoBTeQCPVQvOwIIYwIB10ENPN0ibsHP2Pf4DaiaJJdKFk+vPhGFV44DHKsLzHQhGlTVxYVDQrDgLCQRGAArc4FlaEZIoAP+3yNvyKABJ4SMZl3W5bBU4eArOrXvTD5VXgcpG+gPowNhBw01c3F5iKNRDnKTuicqgdNg5KYL4cBdQhg49gxxhIxRFvA63Q5JHWAWMsMQI8Mnb7ORj8zNUeUyiddfGBbjP0zrwJcdhQGA5GIJOtjyltqQ9axvYdJzzCc4jwrLwm90mzcrOCOhstBT3NvR+JkvLSh/u66kr+9vRp0Mx0FQdUlsVXhMpd8QgQHgNRJJapOOA/c9LmfiaIyunnHYevalvq5TLi5mS3jwA1E+PDKYBFlE/ZdGvkYAATbsAqBApmAQqERYLJQA0Ae828LYZ6njdnyeWGd7ddXhQuHwDTJpIhKWu4IX8GMeg6tpdIQle+BnO+zin10XlFTMU00pgKzQwZ/jel863Tw6lc4kqlbTn2SiVG2j8pzT/GIHAAAA6QGeDEWmQhb/+s7ueKTQ5+NrmuBpY2Y5CEy2oEtOmVKt4dVz85M+NtiIQ2m0/zC21YHMyU53d7h7lwy56o9nNV6OgV7hljHDgFqfuA1G20pG4OnB0151Ao0R3wE4C+IOPg3JrYLohdTZoJxEpwWYbC52hOcfULAYMUzSdHKiE+Xwf9b+sQbODix1HMCALjWFBHazswKWDKvOUQqO5TZ1SO4vQVi7G87/CdVkWhGFu+QIiggiy3NDQyqbKAZPJIG+SzjBqM7mWGqovDQRCOnGezGJVpdif2wUKZjMPOz480xIbHNYyPny8l9AIRpU5cIKoUMwoCgWGQzGAlmQEqRwKVTRQsINn+u4th+2ED05ehzBUIZDC+G5AVZVVHaWopB2JbLCcis2ERyTU8ebL1nzNyt33GpVgPz/vxQxBl2y4GV74nSL6yyXPccnh1pH204Kl2S2hjUeZEC9yvgqvN3X2eC1sEbirJrLR6mbSoCNDBKMW3nSQ1oZtFD06W6v8CX02LxixAgDwr7ShEznxWdbz4pmJdcr23UIrkRTZhdNLsU4TAUIMUUoipRO2JWAAQzEJYlFXMvvwGcrXeeMM/uZCrMOlx+7pTXdN06lKamqBNOszgcYALqrAdYAAAPzuRn4xllffbvRKkjgaO15Lo+mAVedhm2OWLpipa8Lu89V4Uw/AAAHhxiastSiVI+WbGLykZTNfxVWWm260qIr95QWqze7w46RMQIgHyEaFM2eD2GjIeBoFgoISgGS1Y3etULhKwtKK6Gyc1kQSJmb7OSdlZciP8gd1tMvd0e9qOKgd8IQbUT8GKUiFvnGoaFBybud9pgbOV76Y4Rce9khtAin88dYEYVFM1JFcfmWarU97BepMxqM/pwXxSN+wxnNlbXu/OTbVZBPBZjZYkPWxB59CcbQ1mUgsmikMTnLcNI5mUl6KxeYnfpLmyWJ1szFqapLDCmx2SX8pOu/YcqKGuu4XxPdILWOCsUvJyOvUT/g+rDBkB78VeWC+uD5yF07o7t3ykhdMFt0ashNK4FmQCCcFjdnSwFgH9usPhr3fb+n7nFSu/iatK+/2xgKyvoOe66OOebbrvd/2mXW9Qu8VI+KbujVSvOOa9ORanELpxRIpVyPMlvRt1EK26kAAADlAZ4MSaZCFv/cKhU6RgX9tlFvy6lJ1uBG7TkOs4XFyIxHxpRV33wifykDdHAlCrpkn7XBLRzynrsfeDUbFXtyG1J0BvYuNdkSLcZFr1raSKZpmK33KerHilzRULF6GEUgbraOyxH8tvtd+d8whkCNZo2ZQZFMDgfnqlWeMXpaLCyytEhRlms6pMXMJY+/+eh1HtddOStgXvMSB5BNXyvxq3J9P7Rbq2iCVZKUfbPn7t4A5Zf9HKzl6Me7I/FURGLgulOvagJepL+Gvpq6fNfJM2PdyEkP5lvPPK9wPTXCA6MZqJQkgCEaVOW+jMJCwNhoETOW5fS0yypELaKqklFlhDrY7w7acRMbc2sdjiYYG6nfciystxaHiY7N1KSBVcxw+57jW8/+R5ZyuSph6PyGju7a/g+6M7lSmIxUg7Up0zk9aAwXCMXLuHYydFr/Q6BXs1CtIuETXRJlPq/CdMZZtRJZIrBVwg7Ld/zQz4t9g5gwssV1cRowCWym4sIYFHvLgTGy+Jtb2NKT0NQ1oL2o43Mx413khrzzQQFLJYzO69RjOxA6zNIApLyeyeSMaD1HEgvAMKoakjAF3vld9ybhttSvd86CwcjKx0vusLznxb6K9QEs7gWIwORQCAA0OoAH6nGDl58n6HcdfoZxSeFpxHNtCetnWLF0s9tlXY3yk2KQ4PdTLRcyVB4IQSJmJJWh0LDAwJhfYn0hGk/kfgAAAnLhBUEY2CgoEhBMQ3olcKCUsiUmSFLWGZJAqKbojKoSFaFyXb8YhNdsL63H8dcapWw+0SymemlI0Nl2WxEMoc63eCiySqH5C04dYDkwE+j3DV9Shm1PTNyAmW0IZhmZRSWikkmhIbibDrxZzKITuScC2Q30HZvo+8oVCUNrM0KzLdRf5EbDG3pV2DZ83BL2QIOwdahQkuHegfrZjaMwttiNPQ1E92CGFgK1LGNsBqPQk33H6Z0fNLzinRDT6rQqtXwOM3IJ2LXS1vGifeE6iyLw1s9/XagJwZ9dD+3szgEyBqMBoGrBQJAHWy+TSLLxb6kEEYAEy+NrtciijVVQxJjCXVc9IkGURCRUk+hILicDUzbeIHvnWIgywnt0attAsSKWlBkMHfefnet1i5ZF2sSUWmBEF4RO9dvK7lquz0V/eNd23KasBFzcyTfVmc6vZS5XhuqiLfVz3L5F40cbteekGVWfLESqmiTgtwpSv5d88LAfAAABDwGeDE2mQhb/8BrRFL4DM/sNNrlfE029dslA8+y6gI3vNR0Rr/K1SVy/PSUm8PVIZeIp+Z2h3+GLCj0NlN3SKfMUoemOvyzuAsaFRN7u0SuTFL/FlOz0FjDD4t5gclOAI00Y8v4bTzLrcMO1oEJmD2J5tQDZLpNjKTECvjAX5siAsx6jfvsly1HH/kt4d33uVb+AfFF6XKTUjZKF1KLfGJBQxgZHvTxPgVH6KtYUDhv5KalCILLQIrGkd6oCYwtspjNJ4n1vXLALYnJ1vzbpRvZzOyAB3Q62q0Rq3QjSZje8qJgFcjfxxXMo+F8TNfv6nGseuvAd+kArMWdT/2BaLe+Ig9ouZvaqZWeySMfuQaYhGhT1mq7DQZFANJVVI4Yjiw2QoWDlxW+jvH/V+JrAREZfaebfZpi1aHGbIwSoLgn2zVGSFs0fadhxtxW8qnrk8ZW1tL3OXUetZy4wV6wtNITpqtrVRS3TOzmxMZUzD2MgPMGJNrpVBU4ANK2WsAQ1kOYILyfPRtexudc+zjszsGX2gee8aZV+StzyS2PxPisjGRz3SXLEWig2+8YKfpX6x12xQKdktfx6DF0la5INWYkzCB0qZNUXfRZ1nuyouZKlPtaOFNFnhS9nIHInmfXJZcE7Zym7FY/Yh39MH3q4WB7SIsgGLruVOmc0MMJL5npQh7qmszaupL3YJl3omo50c2ISyICo4WsJEs7AMQQIQgeAAAH3mt8T2w+1xePzAC+a9nGISfv9
*/