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
Q0b1tBR4U5V/daPCIsGsGgojKzO0d3JUemiLAFi0HG5ha9quglu/+f3Dt/CGOxauc9CvKuUxomK1VWabwTvDXD3lzUWew5HtpvazcYlK30AzHD5tsnJ+nAxvAX41ecOb7+UzXb3eEHBakiwEdpq4SH1E+b1DDsJ445xSzujUrj1k2IeVHx7ZxTBQ8Ysu771fCuPmS/8KqdRxMhqcnw9mg6o0a8CpRAu6uLwaYUbDxM0wzNGHFrwaPhUyWMjF3c1wdjm+CT5br57mykrNgP5ZD9xPI727vRoPMN0eNpv7VKWhrAaVGNjl4QYJhp1Tb3LLaKRcE0IFuwkUw5HLYV5BXJtZFMsamLYw6rCnAVTu5ZGfPJnbyuUTRzwqdAVg1bD0TVWK3vrDeDr63DB+UdXcxrclYXb2kFxqVtmvIDW536oZRKTWGfKrJMeywhz+Vu9RHa8rxTnMsDFWWeQjSrb1pYyOGwxldEL/MOWa3vw07LTaiWVZnYZWF7ocE92uhhRvFGvTWb5iY5yeo5jajxbdIMHkid0ikSIt8i99XT6oHLO7erZhagfK8Qb6f1BLAwQKAAAACAAtZ0pSOtHBV7EEAAB5CgAAJQAJAGN1cmwtbWFzdGVyL2RvY3MvZXhhbXBsZXMvc210cC12cmZ5
*/