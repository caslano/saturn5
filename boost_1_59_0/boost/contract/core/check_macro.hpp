
#ifndef BOOST_CONTRACT_CHECK_MACRO_HPP_
#define BOOST_CONTRACT_CHECK_MACRO_HPP_

// Copyright (C) 2008-2018 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0 (see accompanying
// file LICENSE_1_0.txt or a copy at http://www.boost.org/LICENSE_1_0.txt).
// See: http://www.boost.org/doc/libs/release/libs/contract/doc/html/index.html

/** @file
Macros for implementation checks.
*/

// IMPORTANT: Included by contract_macro.hpp so must #if-guard all its includes.
#include <boost/contract/core/config.hpp> 
#include <boost/contract/detail/noop.hpp>

#ifdef BOOST_CONTRACT_DETAIL_DOXYGEN
    /**
    Preferred way to assert implementation check conditions.
    
    It is preferred to use this macro instead of programming implementation
    checks in a nullary functor passed to @RefClass{boost::contract::check}
    constructor because this macro will completely remove implementation checks
    from the code when @RefMacro{BOOST_CONTRACT_NO_CHECKS} is defined:

    @code
    void f() {
        ...
        BOOST_CONTRACT_CHECK(cond);
        ...
    }
    @endcode
    
    @RefMacro{BOOST_CONTRACT_CHECK}, @RefMacro{BOOST_CONTRACT_CHECK_AUDIT}, and
    @RefMacro{BOOST_CONTRACT_CHECK_AXIOM} are the three assertion levels
    predefined by this library for implementation checks.

    @see @RefSect{advanced.implementation_checks, Implementation Checks}

    @param cond Boolean condition to check within implementation code (function
                body, etc.).
                (This is not a variadic macro parameter so any comma it might
                contain must be protected by round parenthesis and
                @c BOOST_CONTRACT_CHECK((cond)) will always work.)
    */
    #define BOOST_CONTRACT_CHECK(cond)
#elif !defined(BOOST_CONTRACT_NO_CHECKS)
    #include <boost/contract/detail/check.hpp>
    #include <boost/contract/detail/assert.hpp>

    #define BOOST_CONTRACT_CHECK(cond) \
        BOOST_CONTRACT_DETAIL_CHECK(BOOST_CONTRACT_DETAIL_ASSERT(cond))
#else
    #define BOOST_CONTRACT_CHECK(cond) /* nothing */
#endif

#ifdef BOOST_CONTRACT_DETAIL_DOXYGEN
    /**
    Preferred way to assert implementation check conditions that are
    computationally expensive, at least compared to the computational cost of
    executing the function body.

    The specified condition will always be compiled and validated syntactically,
    but it will not be checked at run-time unless
    @RefMacro{BOOST_CONTRACT_AUDITS} is defined (undefined by default).
    This macro is defined by code equivalent to:

    @code
    #ifdef BOOST_CONTRACT_AUDITS
        #define BOOST_CONTRACT_CHECK_AUDIT(cond) \
            BOOST_CONTRACT_CHECK(cond)
    #else
        #define BOOST_CONTRACT_CHECK_AUDIT(cond) \
            BOOST_CONTRACT_CHECK(true || cond)
    #endif
    @endcode

    @RefMacro{BOOST_CONTRACT_CHECK}, @RefMacro{BOOST_CONTRACT_CHECK_AUDIT}, and
    @RefMacro{BOOST_CONTRACT_CHECK_AXIOM} are the three assertion levels
    predefined by this library for implementation checks.
    If there is a need, programmers are free to implement their own assertion
    levels defining macros similar to the one above.

    @see @RefSect{extras.assertion_levels, Assertion Levels}

    @param cond Boolean condition to check within implementation code (function
                body, etc.).
                (This is not a variadic macro parameter so any comma it might
                contain must be protected by round parenthesis and
                @c BOOST_CONTRACT_CHECK_AUDIT((cond)) will always work.)
    */
    #define BOOST_CONTRACT_CHECK_AUDIT(cond)
#elif defined(BOOST_CONTRACT_AUDITS)
    #define BOOST_CONTRACT_CHECK_AUDIT(cond) \
        BOOST_CONTRACT_CHECK(cond)
#else
    #define BOOST_CONTRACT_CHECK_AUDIT(cond) \
        BOOST_CONTRACT_DETAIL_NOEVAL(cond)
#endif
    
/**
Preferred way to document in the code implementation check conditions that are
computationally prohibitive, at least compared to the computational cost of
executing the function body.

The specified condition will always be compiled and validated syntactically, but
it will never be checked at run-time.
This macro is defined by code equivalent to:

@code
#define BOOST_CONTRACT_CHECK_AXIOM(cond) \
    BOOST_CONTRACT_CHECK(true || cond)
@endcode

@RefMacro{BOOST_CONTRACT_CHECK}, @RefMacro{BOOST_CONTRACT_CHECK_AUDIT}, and
@RefMacro{BOOST_CONTRACT_CHECK_AXIOM} are the three assertion levels predefined
by this library for implementation checks.
If there is a need, programmers are free to implement their own assertion levels
defining macros similar to the one above.

@see @RefSect{extras.assertion_levels, Assertion Levels}

@param cond Boolean condition to check within implementation code (function
            body, etc.).
            (This is not a variadic macro parameter so any comma it might
            contain must be protected by round parenthesis and
            @c BOOST_CONTRACT_CHECK_AXIOM((cond)) will always work.)
*/
#define BOOST_CONTRACT_CHECK_AXIOM(cond) \
    BOOST_CONTRACT_DETAIL_NOEVAL(cond)

#endif // #include guard


/* check_macro.hpp
TpzGiP1lP0mgByfA5flDiJhyspgEGuKTeL/oOyEzuSED0HU8tZ4NHipAGRSS4ukutZX95fpT5V+WB5K0y6lQTwt3FdksEtLm9XCrJYdfdLHcswpCRgWRYjwOU85KGi+NM3KoTw5zeeFY5XoF7/3d52vnjr/9qYCf3qwQuzjw2Yg0MagiY40hYNGjCL+ELlTExUXQJpzytRuVtohKDAWQvHHlvqM14aSKcj9rjkEsfEzpMEASMsFy5e6MnAClggFQfsM6EpbQ3E5PnW3S/GtWNOwFvc4aztnb5r3/87t/8fOJ3e/0F3E8z3nXH3/hs9845+1XfcedfjdDQn+fbifJVF5uFnR+d9yPM1CK3G8XmnT+O/7A0fEA6u6JFaO11D8QvSHqVYoywb4pEEM8yXUEzIg+zjsFIBviRJq6dOE3yQRdCplC8WygKOWQIJydASBZuhiW9EUwvp8pWCC9e9QvMpRZHZed/d3vx3n7QHFGqhfhJd6X4jJWzuckMGNXL8XjRYQYZgEUEbEkCfT7QdJSNvuGNa/AlHYj0ge6uoXH1w96LgQ5wZABe9Aw8nt7wh5IT5dYUHTQ5pbUGN4QduTQAG8rrrb4xYY4sCWBaPpY4aH3r5i6hQzHZnwwcLMw+gIi+/FfYgIN5o4o9sPgJ1LXhNi5Qpo3GYNkIldxiY1FVO/1hj+y4yXlZNMyYvySEw2/Siqh3WUQ+CEv3+yaHMdKR0MXOaJn55ryI4aO3eFQTudoJq0x2ZL+K9qo6dlVvPfNjvrePtSKty8DM2hPougH1I6+L5Pwhwk6YYHS0zinVOqNleKrVMQoGiZRDwxMQRGE6lE/m3OqyIAkLI4EbMTHeUZf2iWPRCR8WEmgQiOnktRvGYfvOAVCxs3VQCPQcPa+fPQgGwnaKGjUhJoTVv+BJA+pWpzyXCEh+FDq7We1kORGKgZwmaxSq3pys2Yxrf8PhAW6WCYeG4+wbXzHiRQFsFKMtl83TJlDR7k+9KhEVqlcHZ/rjaFNKAHR/aGsetl4dUs09bhuufbPcs24oXiA0BeYrCKBchXmBqV1P7M++AoZkxxe4Rxr33RQxOgo4MG3lTyktjuy2PnIQ+Pegf+T3XU+vKiJWs+/YuF1ZGnAmLX2z1HqBYWrbiitJ5WERJo53+hydabCO1C6eOmEakKlcXNDmVKVXcbjMpUNC0bRxyoxi7aVFcRKc11Bnc4qf3FY9/q/n11SVdL6B2Mv1GLh3UrVrtt2RD/f4orYl1kbpymsHY2wQDBDN8Vi/uQe6t+1bexquZ3eGgIJYgDrWDW+iwaNJwMObRWmauLLCn8fse3a3xvSdhfZ/3195FNeSvn7Fdyz9vB61wWRxgkY/bp+Q3/fDf2nCGtS2Lj35Oshmai1Jao0ub7S6aXCfm9FL2war7vURaNcF/XUs/nPm6SDJa4u5lZiq5dgqfvDRF0cmRbJvmdLtxB2fUKbuvn9CPGgpHJ9ku3M1kuP97BqXL1ylOHmO4WHEd04uW8mMTusXx9G+11rYlVWLTmzHsa0r+uig2L2eNt8EJyfea/C/iruCzpljHtMuGX9+PKZ5fhh0rTzOgJJyYb1+mEgTNk9GfxiISXkOxRBf13I0GEunZYxk/7qVPSSfagcsTSTi80D5/torZYl2J0n0lSOo2hHUPM4vxmWI925Y0bQ/bhwXBxnI0aTpLD9uJjVb7AQinLyOZCYrz23vC6tytAZN2t5SrmqGufbFxOZpxVZwmab3NhTxyePFeQfzT8HX07bHISYNmh+to4jOwbBs+jDct6qPhfS+5S2Nc3V3XUsjp9PDkX94XRJ/lUUAuCdHgCTq6m6OcJIAjB3CK8T0EHsnAn+N6hG5Hrp+6+z53FCu+E272TrdSRokZdQCMgQLdjJqtVXyCkjYKxJHODjLPkBpAj8GqQubSVJ5rLTvgXmgmFcuTGvcJLv1xwkDKYFEFTafGVmqW/WL7rCPrCxpsprQQpKnripfkdXqz/0bc7atTqlvRf8nBcrOoXnVNPWQR86TeVpJMQ6LN2vy3+B078+4VUPx6/3WWFRow9pROJB3fBXadd+Za/U+RiqyEItPJMwn23XqHyZHoixcRoHNXfY0HN80SRFdY2R3Y2gdBxpP+L5ey9FiCEAFF8IEOTwWRXrunnIkPmlPfnUku0QbF0EwxsQTL+DbaHaMkCBtCYF5o3b1vNT/uel31MPMC1iP9znp4faINWqb+ALNwIQTKx8OcMtppLPSx8Z48wunru2r+biAw1gHAmKslsYTIpi2HgJEYE3gc7aIJj6J3BuAhrt/+S2vopRHFowJu9T4veS8mtQXkXQ6X3gIyhjCr0TauwJelPm5LEZRMbI88+F8UY8eIwmuPAn90h+8JiM0D/cEC7+EDIkSXJcaSIAAKyK9MEUSTkZGY2RnzMBIKkbipaA/skGLe7DB7oE5HgAuirJW/EujfeMXmx9YtPTVG5pEIjpW/ZanJ/qzIliIZT8IST89u8JhPa2NL1SPpJ1h9sN4TpDCGo/RDjCwx3KeJ3Sw90hIbbpEdb3ES4tETA4Tyg/3BsOD16KsB+K8EK0wONtInzT4TGMEXH8kQnwyCQSeJYNPJkkMm0oMv8gMu0eLpL4CSSGbpoShdpNAaqNWtunc2+kYANG/4CryfRRlJdF1cmKhhVE/2iJQvRKdA1FV+qqXmlED/DH/C6L6TmI/rAT0wGP6b+PGWKM7uaP9fmE138RNQDHeJpRit6JrYDEaaZIsNVL2tPifWyMO1uKuyAJuByKuyqLO7FBWkuLJ+IEGXMivfIjYTmDmT8ASfNAALQEhTxAqhgQ3TQBrIqSy4lKV4tUY4NUlxDfDE8kRYv+pxt/c594zhhPg5Z0YRMvZBEbHhxFMhyDWpS0MKRW1hITZfF5NS9q2TuGDxGqysv0Lano205ZLKH2N9HIb+K/vi2kfzs2SxaT+yYvl6wokIwISZbw+aaml6wq8E1ELkU3I1ln+ZvhjxRjgRRhphQlvRQVtFSL5RTbyFTt4VRrgVQHtDQnn2QXuTR6Xtudn7ILixRmyeTIkoBiTu2WC7qUd5po1JIc6rLYBHLc4qqgfn1CkgzGTXw/AtDDtj61GVJegmoUGpGDNTSFLqPgFz65GocqnZZLiKESbiYJbqZjkl7hmyzsaeaVJAaXEJ0PlxkkibrNuL6q77K6BIirrHUe6D1aI6GVPtCSefyLnyzdD9lcSHqd8z7RUno4iVp7VGxfwjymlnNCFn1txfTbEA84jTwkads5B78IAiD6BWEMW3LQ3Yzcq1/E9dJeOXjA64zviwW4TEmYLaZIGT++A0lJrKi9GkpoIKqayK15ft34VMQSF7h5HN1TjDA8swDgtW3b3n2/tW3btm3btm3btm3btv495+JJmqZNmjYzmblqWsB7NgdJzWcGKyHAxpdUQLLX43TX16vBoIoDygdo7vKDBfLAbtPJYi1KGiGqmgK60Rhq3SX6BSgqg+hx/QYqVCGyA49FwyOaDwqNAhQVCSW9kNOxrwXtQtxMHhltASK9EgrNCSs11OBzXCL9yiupKhmtUrOggi3tz1dY6bZGHrmageCFVZBOkKSG1afaQIkKkabOUZXuxiDJq3BdX2Nzk9hM0nirmGrPkmyd1X9tKBo6WBnqKnW6VH4EtJEeNJX1dIccVOJzv/NsamDUs60tn/HdREHEb4NOx6L87Kz1tvZkjur7YuVltulCJu5UjuZb8u4Slu545uLe7uzzhubilvuzDw0jowcnyVDwTxEKJxMzKwkS7/jAAcbexKiF1cW9qhIP+NSaBT5NzT9pkzSSPU5aIvTWRf4taUS+Jw9ai/Ry7+82rkUKh4OpgrsTFTcVi4UV7FsX1gtYs4X0vyJUskyWGiCQ9CIWKPiVR2mVlfIWpN6Vw9MW1lc4xAFd88ERv0YmV1wreEzLO2erSDjofEFi0nLeOzideiKqvd9YQu5X/p+jOhtRykqDlAWiiQN5PBMVcCRKpmvIXtFxZJlKnztViD67V0PvRuptupcNC3WeonQ8Z6q+5zADhQSiAkjhZnxSgKkX9s0+B2FTAOuPW0LX1ha7y6pSov+Ze4n2DJp09pUzWvtc25BsFzU9W4jwaY8FaJEbjx0FqMfH7yS4JGrGHpS9tDG7rGLXqeWpPzApeTE6Hdd0/kjYhEx7h/qAFMd1Id/5DGB2IZStz+msueLKDtkrEyjW6uWS2Xj0gQ5TxHFHtmMitQpJJj7OKacKHbybtBM/ZGHbz2PlzmXCpmludoXcztn7nY2bsz30J9GqnmV9btWrs3n5lWBhMOXCrAvrVH7lcJJFlgtlU2SmA0RIsmj4pIj5jFIRJSyqJOiolbqLjBFV07FOTVmZJzGkwaueOz5e846AF6V800C7ktACUVkD1YNxvnuAkTz1sKQy1e5eLAwJsE7Vjrr5gF7JauNSDLSo82KC3e1sHjinPrpAF3oJW+2FiTiNwrrRV3rGVx+geZf0ADgp6G/MNR2ywP7L8R3G3zT1tjM3LW9Svx107r70J3DujHrLn5TbBmh4a7BeY3g2z/VmR2F6vdzED+DjdfqAkugQraUga9v51GCZ4+m3YLF7Sf+QLPqkplX3xTO9/oYCOyho3sq/VWDO4Nncgnu10EeyM3R4Ff2PZ5V4mVKOGwAom+G6Vx5+RWyBHEsPEcVFQ4vwloCuXvbVVzvpBeRj/ZvuG9c1tdj2Dc6wxF8m++iU5/hJ2fcglV7+Zajgm0fp9e1TZ1q0WcYTe7ugUUzliBh0f+FS/D/O8P/GGlE4CWBcF6NAMf2AUHMC4Uj9nRvtOTFBsGYcE7R/reDb+uZl+TwS/QLE+ADJ9Qh7RTNmRYDICfYVCSFJDbvzgfwAy9JbJi6Mj4affQqy6Ao2abc0uw/JW8bGCQW+xgb95Io8ca57xks7ZYGUvgZKzHbzy9SUxDKU9La9eJ69nLYQzsyr8dF/i0SG5pqum3ze/otkm05s/54dAqL6baP9wcT6bbMkmVhEg5s7Jke9mTPdl3vGhpkEQVESmlGiJbi6auR7PNU9rTwamhmjAOh4PX82TejazXArMjgtmT6dERU+8Zke/5wtJ5q1rJvuFc9a1MhcfM5dxcld1TlkPMdgGURiRteRw8utNE9jrc5gvVCrG87Y5b+ZuMxplUMH88K8eevrvHe/J/SqOe3eqdeJqXS30VsuCAWOhfpReG41dxwfeKtkjBhIR1ehOAVViPh1qBh0uGL2PXChuOt+MmkKTfc/w4MhqA9zKt746QjP1vDf/uKZxMK7+iJqIHk3nfua1b7DdwXXJz6KtT7E5xz5Ncr+Oh/RuDbW5I7RsKbRsmbWuN7RUb5Rwx1TzzbWzHzSzdbV1H7QzcTW1eTr0tZU1yz8eQwdD8kk6BZ+ufzY0YgzX/kQVwZ+Xvjw6f8QHu0YWX2OhdqPhUtifUahV0u44PNTpL3r4bYLlLAgBsxmsgVuTNQVQYdIAbUg63vjmONU2+2xsTdzN22/doSRtaZTD8lPeu1xskLjN8a4iG7zDStXzEQKWfRahs3/ofi5wC/vDppNI6Gk6KKNy6REMR2y7bo+7J7W7p4O7iZ2bqEtjCI/baOd6iHmqH+8txJVMVJ9cBbliJFv9RDddVNtdhTlcl0ttldN9F418l6N8L5NPKzBGs7JH8uxf84R7quZvMzx7stxvMFrtz/CtjSq1UCgfMpbQ3FHAIOAZvMjkIq/BgTvjxk7XgW/XwaHau6zJQJn9BMMoyI5dM5NQg4WRtWmk52bfyIofERwcUkb9VFS8sZYcVYTsQfZ54LKZKvw4a4y5qXT4aVy5qJDZ6dT57UqZatx465R5/157vjtxjoXxSGo/mBg2Ncbw/AmQU/CdI1zb8klcuCgd0hogqvb5gMVmPUzMNOcMNUENAVvNxXNNtVsp3jICoWqOLOb+fUio/CYOd2DbtqC/Y98+deLh2/IMkBxtR2ZPAHvaQo07o0EaOYYBN1WS6sLjyxS62CFoH4JqF4J8EPbdHPZ1BM5Vcnf1NQ09AQb/Hw5QDy7j2m08r8rQbKYxTgLfpahI3Gj036GYWbWUebZVwACLP3TRZ/5y6bVyvjwyrdVS50sy/AMy/re1YTe2ncg27beXYrKLQjFHSqObYiRXTH5nTMCmycLGydhW1g2m2SKX/PlLSipnQywn88rJ0vTh1m2n9z3Xd8Kqt8ttpsoJRvumVrcw9suit/940hBLpInr+Jq/gNqVic75H91b1Gr2PIdzZ+drvaQp/PivpzI2SYKyngLylCGWXh93qga0rxjuzw+qv4O5LxJcioL1jKi38d1AObUW3oUunpe/gYWOnpz8tzz2nqL4f7ngjkK+ZnbcnUZj6EvyHBk07e2nC/fugXyrlTEPTbvO0XANDfttCYRQ3Oqw3KpCNEiQ0KxedO9kTIFmjjwes2qHr+qYceXJ7erg721+6cu4Gy1uq46thTGv/YEeEo6uXZ5EAgvj7NlNPbaIHjctIcoyUIYdJjxd3GCPrpscJlNwh7bKr44YeRsmmiulbwP2XwVJkdTLVow0WbNBX1VxVu/2fFDJYu5nGkzs57GTBbLRlSLQIGBgYMYewZ9WiLbTyoBTRt9P3gR7OxOB/iIeeYRsvMg4AsdM/5dNmCRpiLXv55X979r+5qWVVQxolGE+tNK5ojCobWasmytZcUv3rW3LScevav3DFk7ZscjLje+GOPJmp8s96SIUhlVdEJKqOebOi67Sd6ZzzcMOCG/+iShyjkVuBnrcXUwKAk8Kru3wC6/s7g9Py+RtRxGkRoXQjNgAL+WeNG3kv6IxWS+ut+5+DaF7FI9P8jdxlb5xjp0afI3UzNKnW9wYNASp/I/nyc0/jMLboT1zCIvufkhPwe4aBxFY/V1pocY1Z8/y6UsvQL1twIRQ1+9UUeqCuTiT4gUe4px+Dxfi1lUELiYD8nNIhkvmSWVON/umrj0LIMKBndBu/8qrOTP1JA4xUJdynJ7Uvuk4y2V7p3SInzhWmMxq01D/BctS3JaUF+afl8Gn7MyI8aQ+98ZDCnPIh3u5v9VxKV4ohioCGdMHYpcH/5n0iA1E353LBXH8uoDEvTxIiKonCBnCIa9xViQA93+nZ9vsmdfWTwpUsk8wD2/LFYZ/JEuuvl2eV09Y+6cwBnRA/yWWzPMSmst/4+EQxbzsQlF1rszgoGG9OGMTBZ4tGXTl1lFJi0awD4pfvP35o6URYOMaJhwRE8JFqyA/r9tzM9pzjM5To5VUMClWohu6UBgTrrHMjESFhGkOe7b6T1bDjrRprysqFxDHho3eNW0C/0ilaavCGaRk0PvOjETjW7s9ywQM3MxFtnn9X/VlHJMkq3ft3C6ueuRExTZr6groPNdH832BWs8nHNus6KbTI+u4erlZPZhop0TIf5jLzR1IMnOyvTzi/Ov5x63gR3q11XdRFreC7mkkeW6uInOEio02PDoPTng3wlk9TdCZGg/mvhM98vt8LtF64Qe2TqzxmfZEwPq7DIbjZdpZ9erSXNwKIStlOK1I5Fg8gfor+0w0A+4KTAugLGkjskkqy7FTeizyh3LL5d9M+HotbC0V7T7XKBZqrfZLIHNkym2OrU8nCy84t6xVF04XR0VaMA9M5NItW45z0iZ
*/