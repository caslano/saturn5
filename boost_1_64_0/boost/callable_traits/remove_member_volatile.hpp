/*

@Copyright Barrett Adair 2015-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

*/

#ifndef BOOST_CLBL_TRTS_REMOVE_MEMBER_VOLATILE_HPP
#define BOOST_CLBL_TRTS_REMOVE_MEMBER_VOLATILE_HPP

#include <boost/callable_traits/detail/core.hpp>

namespace boost { namespace callable_traits {

//[ remove_member_volatile_hpp
/*`
[section:ref_remove_member_volatile remove_member_volatile]
[heading Header]
``#include <boost/callable_traits/remove_member_volatile.hpp>``
[heading Definition]
*/

template<typename T>
using remove_member_volatile_t = //see below
//<-
    detail::try_but_fail_if_invalid<
        typename detail::traits<T>::remove_member_volatile,
        member_qualifiers_are_illegal_for_this_type>;

namespace detail {

    template<typename T, typename = std::false_type>
    struct remove_member_volatile_impl {};

    template<typename T>
    struct remove_member_volatile_impl <T, typename std::is_same<
        remove_member_volatile_t<T>, detail::dummy>::type>
    {
        using type = remove_member_volatile_t<T>;
    };
}

//->

template<typename T>
struct remove_member_volatile : detail::remove_member_volatile_impl<T> {};

//<-
}} // namespace boost::callable_traits
//->

/*`
[heading Constraints]
* `T` must be a function type or a member function pointer type
* If `T` is a pointer, it may not be cv/ref qualified

[heading Behavior]
* A substitution failure occurs if the constraints are violated.
* Removes the member `volatile` qualifier from `T`, if present.

[heading Input/Output Examples]
[table
    [[`T`]                              [`remove_member_volatile_t<T>`]]
    [[`int() volatile`]                 [`int()`]]
    [[`int(foo::*)() volatile`]         [`int(foo::*)()`]]
    [[`int(foo::*)() volatile &`]       [`int(foo::*)() &`]]
    [[`int(foo::*)() volatile &&`]      [`int(foo::*)() &&`]]
    [[`int(foo::*)() volatile`]         [`int(foo::*)()`]]
    [[`int(foo::*)() const volatile`]   [`int(foo::*)() const`]]
    [[`int`]                            [(substitution failure)]]
    [[`int (&)()`]                      [(substitution failure)]]
    [[`int (*)()`]                      [(substitution failure)]]
    [[`int foo::*`]                     [(substitution failure)]]
    [[`int (foo::* const)()`]           [(substitution failure)]]
]

[heading Example Program]
[import ../example/remove_member_volatile.cpp]
[remove_member_volatile]
[endsect]
*/
//]

#endif // #ifndef BOOST_CLBL_TRTS_REMOVE_MEMBER_VOLATILE_HPP

/* remove_member_volatile.hpp
TNpZdEAN538diFTcKkGCKCnX/PTfuTxdvicoaJr7RlDdZMpDbnIO6z23UNSY2nVo6n8vlPWGMzN7d1MwauERVSnrFYHbzJlCi5q4ic7E8t1t9yy1aKuAm+T6TRSOi19AweC7BLS8KbvOK3sC6RSl2J1aogB/bZZucj6nzlaPCnaKjhUSGf0ABOV9LUtZHVS1YFaMk7v5OKBmIWc36GPoP8m7nbVjpDIiv6kf2a+l5HlDUMqjiup/w+9SP+J3KSd007zyJxb39dkljdITex7L1VKWLslDsE9CdUELQQbM5Jxn57fPEePyKqYVmNc2bDxISr6lx0ZFEBI1tyaP6FH4TLFehHC2T7NWZ9qfX64nxTaTNqSu6gRNtxnv+kjPAFcg/6f/DavnxTfo3/YTAHdb5dLcDjMsdWs0+VgBGd5CfeAeb/FExMYoT8vgJeaSsRlohj9FLrphV3k/d8z78tU2tV8IF/MeZhzOWRWwn225CqOrT+MtzDReMXHnUI2ZSvCRRMpIwVo2ZJXXIIqxKShgnHxQFAnnVaK7eLH1F2p4OhsKR3nsxWJUN06ozw==
*/