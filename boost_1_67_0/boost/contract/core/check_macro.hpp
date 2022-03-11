
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
DSPyY9ErPUTr1pabi+9iGvbndUmmi617GOAzSIHH+KWr4NvRfjUoTvju3nXpeblt4BCVmLtMIQc/PP1wndpEduKIH1QUNpajCZ/BJ/XIMkFTUgxPm/1ONNXyLD2A8WNfZRPevJNJbH7VTt77Ns0vsZJfW1x3ytMw20a1kDcJA+b46Q9bj0n3zTBIU+Iz3lpNOYotEb7Uk0Ccm/sr+PMY30un6xC0XWJkh4FfTxUt/pjVSgyjmFyBLgs5CbibgzWafHx2OJ6nxw3Uh/Szrt3J/WzG3K4kWrRusEPbnaDY0jbkMVyEB8GL3H+Mw/d38Hp8Bk3QV1PBeUj7CtWIOqqR2BRnG0aILj/UES4ieiZwth6D1LwjMW4Jq+dFbQnqBX7MZ7ZwV42SLGkRFPte9tnw1AKXQegXFbIai8+XpvW1n7OxEcu3cYg4XT7pT+m1Lb3ENDcG4JLPIxmUc8cFAgtSU5eZFjcgzpEi/tIY8LA+aFxNrVDgykS6iuG6ek2mDx4QEiahcGYJZyvEFQ/8e4unypKznVTObu/lLc4GpF1xeRATDAfZpSCOuxF8VYQeA5NanX75SZSTTB0Z5BvWUCgxV1iHp8/BgsstJnM6+k28wWVyrtdEO2rHpq23jKUqmIgvIJw3nNiKl9uZCcaVvFMbl4srPb23gRd84lHoLqK+gJ3I+62fFoLeEFJjZpA0SbJdkBlUCCJytJ7O2mwRmmbby5hae1hR5qdeEpZIGasejzM23f1VFnAyet3PTeSs0Ms4opQMLvl6to7t+a5czZIcDpLvXUF7Ps2TkdeKkPAdUokhSEtUnfY5J8Yx7440WH7lXpSdZ95bIfotpwREY3cCwWIM0Ep3+VKjg8rRdPIW03Gil6Y0oKSm28j/skmCoh/7DhYW0XES+TeMz0h5UhD1sysqsOT/sQmQXwhT4stigVULrvO5vnDAA+fshlnd9PpcWVQEJ0CbnLEu+Lhr35Cg0s9yzDuxZo9qHVR6TuysrUgeUaHlMOi36Y7W4ipb440EwRfGn8HgOKNveauh5q3E+v7XVbzvLut1dD26s5+xl4LyNEcgaSfmx2cK3TQpsTjCGZve2che7ZqtSBH/ouAoDVJRggy9XFZwk4Nh8/ctvZMwYizzLd+gli+jDajzaA1oIEbb5ts3vWvHR+be3FSF4czGMwG4o+pqPLkPsZFV6tXwxEgA4dXhSts220ZncFkulLy8WrYPmfA+ySsEUK3WXtuf7H5MkW7oHCDnelT8eFUQcPP/HXTh5cmIkk1sK879+cb6ea/97ev9LeBLC11s9Z3z/X2+fXv1/RHxzZOX21Xw2vpB+uH9Bv79YvvOj/x9hfsQeuDBjuHcplvh5Z8RQgjtTqEOxJUY1UsQbsFohZo5MI4u463/pBm2GnnIvneG7g07GX0jSfins4qMwqKQERmenZtz4yB6G2Q61PtNsUASizouVOaTs4aYKIZWVBRLWL8BZioKG8l1z1h5aJFvsQ2fNqNjJgReSnxXAlODejdfUNMs7R3fNDGJbG1FfWrqrStceUPCNCTRY+rNtykcAYgxNClHSLrKc+idUUWfLZPoBmTqAGnPaTkS5v0gXze1NRehy7BST1mVZgf6jejkseyWc1rdD8DXAhZShW38zCVmTUfuOaUgBpSHfbvsvcwKgMgQRWuwa8dTzBS6Y6SPTFD1BsgrtaKQ4XWZUl+tkuUEIAB48spLR0wIl9l2QPL2UBNBPNie/Ozpd8SVtLyslCDDg6hYuwIIlousnI+eNS9ja7DHZnUdGf4qA6cKj9tGzi8INYvmC2jbTayzWyvkBp2N8W+10tjp3251KOmAWjZIyfjj8c0cKErytNN3UL0u63Q/v744hhbulZD2wsfeQw3anQU0pOnGVqoX/M4yBp8elGF1gzNm0Gv/AncGwIDOu8oLt/xKnTqlWC3pmD4EF483pv2bDC+No8JaeTH5JAwHfrxkdBQ0K7HnrIi483diNgXBuCixQJUDg9mrQia1vmP6ODxL+dulfGtiFiWBumC0ALhp4MtCl64nfvOlCeoq3Hxm7MvOlCrS7Ji+Zc2qMI0KaiVMZEyxekkFEE9bNWLDC2JeIWNjZN+dYONqDyxpC9XS7tIH0mBGsSBXe15QtQbifOkzt5wZIK/uFy9cYj49Mp4Q00+Taex6yy+knCff0c0BjVbbjaDCW4WllG1+NfalNqjMHFn5cNs9v2UXseb67fECSz/bVrzhBVnUUTT32CoAoB0E2ZOaM8jjXF6ucruEvJlAo4oAc8Ya1qUDnfGnuu1LTNvOtx2BmERpkU+E+kPpcQDPhVAcD8w2l70kkoglkEwhmb78iMLgf+r7DKSdRWXW+PxZjQee0tncuV3Riv8sT53lziegAPHNRGsKSaNRSzAFYvtZmUFJBWYb0MXtfqr5rpSykUIUD8VkT3hxAM66I8NIMulMRQOdqd66OwuCKyGYUec7oy6UKDZk8hVk3dPaOpwPecfR6C15kNevScQP/FCOc8vlq4B6RF3/kzAodVa8BxztqSETcYLAhUpPNEuFprJf0Gm/ZZ9cgIJV5LSngJvHsvwhtrgvFH95Lpku1o+vNwqKt1C0R0+Yb8W6kCfONSWYZXIfMQlV+AHL0042fadJ8kwefewc8SVg9uyPIupqgQs/PNN1wK4sRBJP+vE2X4sGFnqK5uRRjMQ8pRgXQu00LGdVTys72ZSGyS4HUBc5Zhj2Nsf36LlAcavC+T3d+qIAeCTU2Ef5FEv95kjkBQs8S1Nl0E4456TOHDMsqfAdaMPY8UcU3S7hgxyRwUp4w477KsP6zV7LjW4qg/yMr9gK60cPRQa9GpuGuRAbYRnUhhmJWy8mli+oBj/pPNXpQOfeWb3qXS/TBVcjhvsgUOj0VDIJKfFzCaYNyE0AezCg8PLLfPaGMjVu/2fb4YSGhGm5ClCBzlvapI5SGAazm6UzaVkKpxkgAd/3kAf0eg+Y1tOW9Eqw80B7vQUnk6UowZmFcos2F3qwvUzAuo/FsKglAMzQ7bLO+YXYoGul/ZsUgaMG4l7PMC32X9zG86ABMBJCzUNUch4hAb1xiRVnjNCz1R4KHrJWoDsuQuZUrjoyKg4KzATSXa0Wa6s4kJEkqrQJrvGRoFxAZ44TVzxwpDRW8n5mvJKuE16D8hzSvJCiNw8sDW8SqKC9U3e4cHNw0BDV0zyyi2sFWbq5obE2H5oQn8EQMZfXP+yi5lUm/4EsgdmswSmFse/8gdtq2Nio0xULNASzZkc3O66pnXkkJVtCKAxsUYjDe9rkNO/8UAzXTT8QzohjudiHL0qH7mNkyDKg7usb+4HqhefWut4S/QI+EuxSAAYZH/7JKU9C5Pkpq8d/ZgRRIi0emsffiwh3EVFQ0JrelFuQllbOSdVh+Vzmc64UvHOOtuXfG/WZpb1S+pbEsu9JauNkdJEDWvjKXlFrWxXO5Hq+6QaXCJpZB9bz1NdJXoTNoN8Qx8GitDIDFC/esVCiZ+EyrejQQbZ2h3KCemSPSj4vPiGQH6ghgFriSUC7szjBuI9467N5iOL+EP6nd4JFrfwsr5cWt4ZWGlUTee9RFlCe5EnZ1hz8uZY8CDKkTgJw4azjaG7DoFi/YJ8iLIpJ6mZ26GsLBx+nO1mnBFMHLlc5dBLQh0EPOhZwJ5VkOs+/Qiox2yPT2dakhYFIJObLarZiwTAfQpjHVCGpkblZgTf7/fpZZkS8P4gjqku0YZSjicJORmmzr86J+YkMFqtVO9f1ioTqDXRV8+kVDK69jx+OvL4yYDWNiV99X4osIMCPpEhRUBENhLXNQ1V4s99CMHBqes180ShViJeT2rHekMCzUmxwito7ZidDw28mTPub1VJwlBI8U2906dfoE7bIjTLyVI+xUdrH1Tg3F+Nz6N/52Fm3VHMzgXtSVyFBBM8S+LXK48+B2+cEebTYUDI+3vidYoiCyDthMGCpsLtEGA6H2a4QwNr3YkSOsks12oDuwksKzKM9vOCfcKA6vAC7Eyhi0hI5MgXvPOMdE1FYQ7NagALYYN+gCdpNN6lxqXPpQmc6XZMCFyGkYf7hj6DCnx7Q6SBPz4cWm1B+L5U114zsp6mv+a9gObMEPRh5BFbP+BuR33t6nU8gTWkSVQbeUK0ngilxbN4v3JMFDJHU+/YAndVWvICiR0h7UVKijGhjC9V2EoTwsVOoHBq1CUIWHvtHy5fvnO2QnxKwm+ujo9njDc4HkSNSbGlBiGM+g6S4WiMAuVfnmsCGIquS2bVtaWT59FSnXu/qWGN9g7G9vKUTUQeztYouv9Iq/3nlt/FqkO3oTHdfliI7dslQzB32od/8B+mwivxkTeQUkzTOlZxrp1+wYBGHcdt7GKauoI59tSOaONB68JwMhiMXMroPa3Iz82x8hP28ASPDq6PmDXZc4SqoC/issj6zzNAzMhIIYvF8lPVD4sSc5oewmekeRqKTgl44vs7SCQiklNBJuih8I1goL93HrR21CK41l6t4VFElRUfxwanQBDaxYlB2KO37IzMxYXmUFuAitax2/fzLvf5fMQGWoL9AI/D9hKbjWrs0XC6Gz02cqATwuRecNZD9WV3O6XktjnXykajiEQk7In+LI8D+tfseJOQqZtQPlVi0ubZEuGBo3WfblYGEvaRo0etjQISmN8gMNF+WkEjOTDad9KIs+ukTYY2egsVYd/NvBIIudDzaLGbOhFZ26H/8QLIOR2wdrGfHQNUbeZ+pKBZYmdms87bvkNPxBoG9UUw+kUiB42qqkNT7Z9BMb3twGiWTqe6rOCNeFO5hLNQd0kzEYpCWX4y1Rw9ykd9xTbXRyT1tGoVCfBUdWFja0YRc2gkw9qnfJxnRSDtejSry4UTf037PKdAevBSm//LrDdhLodv9Iy9N+w5Vyn8jJjwqc/GMikrBYeq5m89AvJo5PGagao0lPfZ7dyycddGD9Hjl5qhPUUDptkTL0W6UbMaoFZUlARsU08enE6Nbop5qUKKfKIIOWyMQEkNGPzgdOIu7cxLO4OQmeRwMbIqMvMcJ7PEm7YWSlZw2leRztuyV9kpoVFfEQyMqnrpabijFzJ7d8u+mwCGFUC8zILVFP7giniIOM3Szt2ZZ42dgXqJagGfqiDJFrZulp4ta643RsTSCsE6aRZMfNB3jC+ynWj6SRMRQhLRU+oP+ByeA2H9f5ueAoXcjgkzFIGy+chW/oB/5YQsqWjOPYfSW43nyiOrQYcQ19N8kxhwwMRG6DIT110LCZz8M+Qg1o32or19x2+5R5V7Njr8rw2E2RfQW3nyUB26TGGLTJGuaLPNDPGp9PblruHtuzbSZ5POaN2ugiq2DaBO58jZRSg6dKacgYgXwOUTLa14sQ7/9T50MtOwygKNSyDsjt5cquBORcWYg6roB9Tc31rgEj6GfeesqQgI6TXm3lWNOqcoMmKXJXdP4ykBbLVQ4rFODFtuaP4GTOwdmccU9uon1RsLz0sTcxEg4FXHAuNppc8ZAS5iYigv1rUXfuoOpawTRqKXgudK68bdtkjbftt1M/3dKdDlNrxTyQBs6Uu6ujHHhiakXhXO3cBn0mMGLGXGot7/uZDXoh4MoJbqoPFWedE9q4eiVSIOckBmaRJOqrsSzuGvat7/lV/2dMVttMKsDEuH1TlqaBHE2MqJForkFtRSf74RnQaOfzTICD0jK+gaqBCrNmg3r2NrgRU/RofW3h0V4Jax/ZQx6HhkJGfXp8ArSUEmifi4E+0hSu1RktzjdR+zHuQT7Rp7hkOeBveBawQl+iuh4h/fWLR2Xa3WlwjqGAZcmSQ8KhPp1dqrH4x0O0SWXgdtunoCRqKfVEoFAhMCNH2y5ygw7SnXZvHE/Ohc+sXpKPQaBlqSlYTuBQL3g2QjktEaWNIZc7oPWLYpLn1y0ktKA9fpUwjroEOrTBPp8Hypx9ENNsP5Ae20zIETVUKH77NzvmxIWPe2Ur1YjruyRl/xhR+zDQ2TsJ4SscnYNdiAKRA4rYqAst7IQnq89fl5ZIMd1AbT5vtv+UL6GrWwFKnuv252Djt6dz3m42woFwdR6qlgPKYKhM+iGcT2li0tB3Xl1i3ZDClLICoa+hY7Wfx8InMXwwQDl7JSAIwG0j3b2xPhdySWXFFYXl1cIqLWqojCAEsOlVOPjNVd1fhBwfQ06AYtNtcOgkJ6/orHbGF3yskvN4QCwujJgV6BBI5069kUPpJe5Xedxqp+2paosEO8+OyAGm38JW7jEvpLhFdn7Id4+Rv+UuFY9+hMQ2I2vbrBlcDrneAJIElZfn+iahz9Uyhj6O1SvJqphgBb23KVPwlO+Qf9S7PlrMupb2Q99V5zioJ90zRraJKDQELtGFmy7qY2Z+GIjPHeu4nWt5c90m+7qWwTd1buy7hoeTD7/YcSRs/MVo7pwZ69qn2E8d2e1PAG0fDFmdWOYysOALxaWIJ7FsBrEz70+KATP0P7NxAWJPuv12YfOJ03FY29eJrTgE3RuCnAo5msAOGicJhHSG80FCgI+Y2cdshF6McWK93cFvF5c0uyivBnw5kkyTIPP8xZ+4jp7GXX1MiduzMSf69qgEMiujbfCCcb4KQ5XwMSdmWDkcsDhGUa94hKNvrd4ybUHuemsgvjR0T6urhQwT2rjNKebXjCAVMyrKHLdb9sW6n5X0zmFEXjfwRgPIoRK9TsW1++GYlaFhczu95DN5hHQdG+9dgtSkGzfGRA7vonrqpE7nCyCtNd5aB5qJC8dQhkgRA9DjnzjCWSoeffVd8OR4g0eisOlVEilleyTIlnzRWnyjlS+41NAXqRQU2UzzN4ENEP7gbpuKRSELkXithc6qLlaARLo9+pt8NTrdPOc1dMj1Mm3m50sVC7s/HXo5cvnjaSur25Eh19dK7mvrXdUg749ikUHYVc0AHDEsSfD0EX6lIqIeBhLGD+IlSm82pVMmgneHv74py0ZdbdqxtejwweLW4F4AVUvHIrwQzdfpNkJHEjboE857Dv2qm72wQY+1y78GXut6+eWNwEqUJrVrFUDa8GemMQz2vFdjLIpA8wl6fyVaca41dUNf0PILZO7l/7u1LrL6mlgeg1DEJhPt/ESYkdyPcJUF1ThSg9pB4c7x1Q6rh+U4K9SXSeuUquQHpSGUVqxc71p+QRGrllZxznZJ1wvcRaJeOwm7WL7dbfFZJTzhF792rCRG9iwictsiF6mFMZdC5UOuGogECIOW31lH8jMTOd/T7KGq1mvXHgbfgwANKjojt3oOqOb1RTosg4WLP2+Fo6wzXKoMYjiJuyQNIooyqFuDdEC8LszbO7iRxWUNmcWzLxoyRA4Lgsp6VlmxpdChsNmsWHozy8WPzXyukzzmbbec8hJz5aw/EzhMyPDPoelpTpjGvOAS6nWlBXVbl2Qf1Gba5HbXDraxmZfbX+GpFhynUe4OWBJFx9XLDYYatFGF2T8QBzBEcqqGwa1syIOTWc9B0CgWVn8nkBtyU4l4TZjqBUErNoTLDF/cbcNEXQOuNyWPQfY/v747kCkv/bgv1cIzyUCNJ7eb+F1mcQ90+qmiVfxwkbQmNR6lkUfOsbUa4UYzxS4Vy7LA63Mj/CCe5DE3/MoDDlW4p0FirrqvVqAcjFGKlOlWbI1b/kZRofdTygAtw9mJK1o8nNPeWS7WMkmg/A+xRzOnazMJ2jjJZiOGYaZZwrTF+NxQjF8uNZRJ/h023i42g9YBdpnJc6ts623G3ndx+DGLyQE/9qR/ZhKMKsNCV79jVvuix0vDmxafBPU2W5I4byIJ2xzqJvGvuBR86ifWMrNujrQDWQGOOFCa9XpTYkqL4nPuKQjkddOqPbeXmYrjosvG5BcWQISU3XJxEDmyAzHVBVi61376eIWnQZiitesCbs6qeswqx1mq6Q8SaU56tRtNopPPb+RvJBN5y3OMYle1BNvok+4u7Ne7ApysTWtrhQIj0dAvJMiPAy63K0kOfu5qAal+FGGxgk7JssgA5FfuFuPzR3I+uMR9hjtOmhMW91nOy6VM/tT9imMO8I68VJEeFP2UVQsbq6zlQtI4dD5aXc93M4hC+Kt8LbeyxAjPQmo59vt6wQ7cWH80G0+CyHytvuCN0Yk7arWtEWDF0Jh5/C7s2j9QLEB/DV2eDxfN30X4tYFLXv6P67EZAJQm91GivZ+uriIX6UeV6ks0Xbh2YzN7lZY7ETEMUHMBL0ULOVTViwFO6FPnHqnO/KHOaol4LY8DGjDF0nViSKmaQ7MFXBBr+tRlV3yus2dNWWFGgBV3ytr/buG6otsLC/zZ0JiVZRivOPgyUSfqglq5o1OruvOJdLSPOQlgJDK5d8OnRNMHuEmMjC/jVY4kvD/+xUdufslAIBDS3V9yWIkuZHlHzW/oVqqklrTVcrOYGvOCPpaviDk7iAr40Pnmpe46Ad44mFsN4MzdSDD3oNvgMOxGAxmnOC2OJGe3A9bSLif73W/fmxqMa1kzHWgbFjl5Gs64SuaIQTtakiq96nGFG+MAnkylgkp0JRCU//l+fIp4aQTCknilTk+GK6fzTaGu9VrZwr3dKP692SXVJ4Xq2uy2fJwusUPZrbG49K9109lQxSawH7OmyS8tb60wuTrD66gXGij0e3WYW/elTqneOKR2LvHENdCQkqPo4V/k4YDgtWfJ1fmd8aKp4ffAmbPDsIc6jOHRD+SwKqTxOiTSECKzTpTMEq0hRZm+rZfY+EwSebb/oqIxHnugROm1jocXfN5qtAnY0tLcA34KQGqKcbl8BScMOjcDuR6fCYE23WRzUD2Q3fTwDLQ8trR1ZhbEAu8BOBv3vBJUcg8Gl7K2MILDpNcuYWoemQhyGCdAmDN8bncjkAQDgorD0eUAK07zNEibM9FLXy17cY423izt55zGLCPoQNDgia+Bm8e2vhM2dXQbGCur7KP/Rrsp9C831phBroOH6kwmmEGhzPve8iMsdnmO8Idj8bftlDi45iIokNBlE1zQM/plXinr0pmi7XNjaIIUpCvuASwLKEUmK+9ahqN7VMu24s/MtGnXTV75VoM4JqC7eSet5sPttTNTF3zKOCfVg8CLn4+0g005Ia3kUcnFUDzFKl2ctiOPmxaNIvJ1fABt5AfbO4j5U0BNoKcrudiQxZ9UnGA0EgEPJ++P+Tco6JRR+yViXlFnwgUegGrn5U=
*/