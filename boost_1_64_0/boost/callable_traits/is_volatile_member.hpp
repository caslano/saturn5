/*
 *
@Copyright Barrett Adair 2015-2017

Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

*/

#ifndef BOOST_CLBL_TRTS_IS_VOLATILE_MEMBER_HPP
#define BOOST_CLBL_TRTS_IS_VOLATILE_MEMBER_HPP

#include <boost/callable_traits/detail/core.hpp>

namespace boost { namespace callable_traits {

//[ is_volatile_member_hpp
/*`[section:ref_is_volatile_member is_volatile_member]
[heading Header]
``#include <boost/callable_traits/is_volatile_member.hpp>``
[heading Definition]
*/


// inherits from either std::true_type or std::false_type
template<typename T>
struct is_volatile_member;

//<-
template<typename T>
struct is_volatile_member : detail::traits<
    detail::shallow_decay<T>>::is_volatile_member {

    using type = typename detail::traits<
        detail::shallow_decay<T>>::is_volatile_member;
};

#ifdef BOOST_CLBL_TRTS_DISABLE_VARIABLE_TEMPLATES

template<typename T>
struct is_volatile_member_v {
    static_assert(std::is_same<T, detail::dummy>::value,
        "Variable templates not supported on this compiler.");
};

#else
//->
// only available when variable templates are supported
template<typename T>
//<-
BOOST_CLBL_TRAITS_INLINE_VAR
//->
constexpr bool is_volatile_member_v = //see below
//<-
    detail::traits<detail::shallow_decay<T>>::is_volatile_member::value;

#endif

}} // namespace boost::callable_traits
//->


/*`
[heading Constraints]
* none

[heading Behavior]
* `is_volatile_member<T>::value` is `true` when either: 
  * `T` is a function type with a `volatile` member qualifier
  * `T` is a pointer to a member function with a `volatile` member qualifier
  * `T` is a function object with a non-overloaded `operator()`, where the `operator()` has a `volatile` member qualifier
* On compilers that support variable templates, `is_volatile_member_v<T>` is equivalent to `is_volatile_member<T>::value`.

[heading Input/Output Examples]
[table
    [[`T`]                              [`is_volatile_member_v<T>`]]
    [[`int() volatile`]                 [`true`]]
    [[`int() const volatile`]           [`true`]]
    [[`int() volatile &&`]              [`true`]]
    [[`int(foo::*)() volatile`]         [`true`]]
    [[`int(foo::* const)() volatile`]   [`true`]]
    [[`int(foo::*)() const volatile`]   [`true`]]
    [[`int(foo::*)() const volatile &&`][`true`]]
    [[`int()`]                          [`false`]]
    [[`int() const`]                    [`false`]]
    [[`int() &&`]                       [`false`]]
    [[`int(*)()`]                       [`false`]]
    [[`int`]                            [`false`]]
    [[`int foo::*`]                     [`false`]]
    [[`volatile int foo::*`]            [`false`]]
]

[heading Example Program]
[import ../example/is_volatile_member.cpp]
[is_volatile_member]
[endsect]
*/
//]

#endif // #ifndef BOOST_CLBL_TRTS_IS_VOLATILE_MEMBER_HPP

/* is_volatile_member.hpp
p5lr4t1lVpp0fQfgaSnzrNhx5h4nyRNn1nqSnd0xCzXdMas/9qWviEkzD3KEp5y9nmlmXAzHUNt8F8ox1sd/EzfN5HEM955er76b8Zq0x2ue5ynhHk8TxiDxtp2+ib3FPG9WOCnmLucqM97T3rko5nwzIXaa+XOsu7zTrL20Tz7x7633SjjsGNHzPN3aejxd6nlL3NUxtzpeiXNMQ8mX4ZSQ742gfIut/bDLJd8XcckSDvTRpJA+mmVtIM0R+Xvicpxx5kXOpL4eP0HqzLFFLlDnl22dI9WJdpZ3FmZLubvim9OXFwW1c75J03bZJTLpcUPMP02j2PPN07EebaPqY6S7MzVprNpG3If37ZneGNlOovgvkHkI3qs+g869CebgW/H/KbCD0O8nq99OvmLiB+lxDuC/99q8ctxXNe0hl8zZXiEyEmePgSePhKENc6xgGRuvx2IvuK3rS3A64YaNOI6e20Y93pf4fRLnT7tXZGtmp8zff6b1wrI5i6vbINM5lbgLQt5xWGnDpZJnVbBdKWT6JZ0v1wv7G5uZ6J70MOumCRf74tfctunOa0sfePzW7UX/eH/m5sPRPem3/Rd70jfH6O+l3j/UcmS/uNkYY8Q1VBtKjWAmTIOnws7wLDgAng8HwkvhIHg9PBauhYPhgzALPgmHwFfgUPgGHA7fhyPgp3Ak/BKOhUkO1wf0wmyYCSfCLDgJyjfi4QnwPDgfXgjPhyvgOrgSPg2vhO/Bq+HX8DrYhPa9AfaDN8Nx8BZ4ArwbzoFrYTFcB8vhBlgJH4Sr4MPwTvgI3AEfg2/Bx+Hn8Cn4L7gFxtOmT8P68HmYDl+FHeBO2BW+CHtq/FCNHwl3wxnwb/BM+C5cDvfCq+B78Dr4LbwHfg8fgD/AndBx2MsPY+BHcDY8APPhtzAeNoql/6EXHgV7wzpwKGwEZ0IvXArT4GrYDq6H3eBLsAfcA3vCvbAX/Aj2g7Xi/OmN4LGwHcyCmXAIHK3hCXAYnA9HwEvgKLgWjoFPwfbwbdgbvg/7wI/gNl//wu3wX3AG9Mazfg+7wlnwRDgJ+QI4GZ4Jp8AbYQ68E86E98HZ8M8wHz4Fu5B/G+wKX4aZcCfsDj+GPeB+2BN+DXvBb2ETWIfrqylMhM1gKkyHzWAu5beAs2E7mA87wxak94GtYD/YHp4CO8BpcA5yD0f3mP8m95i3rozuKf9fcb/W8//Pof/3Pf8vTmEu0uf/RP2t3qQ2mW+EvZlg1r8beP7nwMb9/meZPvcHZHpb+8cfSPhcx/1ML8/uVraHfa5+T8LLnHDP4dlWPtM+Z++R8AVOJJvCb0v6pY7rOd1XbfttgtS9pPOL4jF1TFUZuUXGZY/5TS2jKn1+bqBO80mfKGXsDX2/2T4PZkp6Qzn/L5tJuqxzMA9Xe1b1Nf51Ih+n76tyHyHhHvRmM/p4alK9ENvIQ/Dj8RPwozR8RoqfZ8LJLpvf/BaGc8clSV36J7VwKMdxxP53j/dCbM07gWcSf7jSsc8j/mcWJ/T5I0nOkXMmrkKeP3rr+OobZ3DIkKcD/BT/NXJ75JhL/QM7p7ikbD59oe3UKj5onKnsKNvO7fb5wn8W2TVNg8aZyvY1gWfrVJF9CVlr713SCqxsNwkXEU4S2dcJax1c/TvRyp9CGxCm7U4W+bG0dwfp5wKRlTrhcn1Z7TpUR5FdZ8tmfJa6x14bSd8a9r3naZKWYO0a3yThpNAxJespzSXtMRMyhqXOxQ7Hk/RdJofzVvsX8m75aPxQfLaPNXzPPBtyLnacTCHMudvn1plV9uFl3BRYeWnXoHESW4s/ulcmDX4MfeMk6333OCnLn72grBzr1+5xYq/x8z5Alrs=
*/