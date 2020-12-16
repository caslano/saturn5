/*

@Copyright Barrett Adair 2015-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

*/

#ifndef BOOST_CLBL_TRTS_REMOVE_MEMBER_CONST_HPP
#define BOOST_CLBL_TRTS_REMOVE_MEMBER_CONST_HPP

#include <boost/callable_traits/detail/core.hpp>

namespace boost { namespace callable_traits {

//[ remove_member_const_hpp
/*`
[section:ref_remove_member_const remove_member_const]
[heading Header]
``#include <boost/callable_traits/remove_member_const.hpp>``
[heading Definition]
*/

template<typename T>
using remove_member_const_t = //see below
//<-
    detail::try_but_fail_if_invalid<
        typename detail::traits<T>::remove_member_const,
        member_qualifiers_are_illegal_for_this_type>;

namespace detail {

    template<typename T, typename = std::false_type>
    struct remove_member_const_impl {};

    template<typename T>
    struct remove_member_const_impl <T, typename std::is_same<
        remove_member_const_t<T>, detail::dummy>::type>
    {
        using type = remove_member_const_t<T>;
    };
}

//->

template<typename T>
struct remove_member_const : detail::remove_member_const_impl<T> {};

//<-
}} // namespace boost::callable_traits
//->

/*`
[heading Constraints]
* `T` must be a function type or a member function pointer type
* If `T` is a pointer, it may not be cv/ref qualified

[heading Behavior]
* A substitution failure occurs if the constraints are violated.
* Removes the member `const` qualifier from `T`, if present.

[heading Input/Output Examples]
[table
    [[`T`]                              [`remove_member_const_t<T>`]]
    [[`int() const`]                    [`int()`]]
    [[`int(foo::*)() const`]            [`int(foo::*)()`]]
    [[`int(foo::*)() const &`]          [`int(foo::*)() &`]]
    [[`int(foo::*)() const &&`]         [`int(foo::*)() &&`]]
    [[`int(foo::*)() const`]            [`int(foo::*)()`]]
    [[`int(foo::*)() const volatile`]   [`int(foo::*)() volatile`]]
    [[`int`]                            [(substitution failure)]]
    [[`int (&)()`]                      [(substitution failure)]]
    [[`int (*)()`]                      [(substitution failure)]]
    [[`int foo::*`]                     [(substitution failure)]]
    [[`int (foo::* const)()`]           [(substitution failure)]]
]

[heading Example Program]
[import ../example/remove_member_const.cpp]
[remove_member_const]
[endsect]
*/
//]

#endif // #ifndef BOOST_CLBL_TRTS_REMOVE_MEMBER_CONST_HPP

/* remove_member_const.hpp
s+ASjV8G8+D5cA78AyyEG+E8uA8WwYOwGLbQ77+1g6WwGzwdHgfL4UmwAubABbAILoJLYaU+Nz9s9N4GPqB29RrBdS77gEfDxjAdemFrmAJ7wFTYC3aCYrcYjoBpcBRsAifDdDgVtoDTYUtYCjPgGbAVPA+2hlfDY+D1sC28BbaDt8OOcA3spPXPtL/pzC/aH6185UCfOxO5NLgMNofnwkHwPDgY3gePhxfAU+FFcAG8GF4IL4Nr4Uq4Hl4Od2q+t+AVcC+8UvvnKvgJvBZ+Dq+D38Dr4Q/wBhjjUFeYAG+GiXA1bAX/CNvAW7Rfb4VZ8DY4FN4OR8M7YCG8C5bDu+FCuBYugevgMngvvASugFfCS6B/HOtvC0wKM467ar/3hm1gH9gV9oU94URtv4FwDhwE58FjtT+z4FI4VMf1MPhHOBzeAUdoP46Em+Eo+CwcDf8Cx8AP4fHwYzhO23O81j8bxuteqq3RdZjf5DpMrTN4nxg/ED/pjP+vtZioi7qoi7qoi7qoi7qoi7qoi7qoi7pfyv0q+n+2vpb+TO//l6UYu++2wjHihuMbKsf69mfvDOhVThh+XHbOcZOm5Mwpy88XfcRo0h3jq5Cx3xT7UuS7qD4ikN9r9ROtX/OFHauD4D1a8bk1+AZTsuogRsv+cjlu0N7h1h4jbgS+AX6gnkPWa9XOobC4sCLiOUwS+c5a50D+Rlave4kXXwOdyZHq+7DWd6LWdyz+C2RXV69vcf4iY+trv+2m9X1a5Dua2q52/Tyx5vV01+mTGCNumo6DbPw4jpm4q1qdyqlEaBvaOrUX+YGcl9WzaRlHu/RseZI21qZ5rZ7tGAkPMyn8jfBuiOZJlz3drHfac5+sesjt/+GYCtZt5YlMVvC71kE6ySzVyc+nP9soD1Leyl3u7zpq2VYnmbfQpcdT2R5V6bTnfE0fa9OHudpuvr8dbFo/a8fgWQn39NT3xIbrH2nfZ0Smj6eRx/Hr2205vau1d7LqJh+T9CxPqieeuOFJE4hrZwL5HGvLI/TdnGR9r+Jlkeviqe3xuOwi0L76bsRmSR/kqeVpWJXu0t2+IOndPF85qWG/73nu6770ORp2zP27RX8d9p2b5SLL6NC8WSL7GHqbdvYblneJTEP25u8PV6a16+C3+8A1J/Wr79nn1HKl59r3ov4u6Tdq2JZFeKjou/dJ+tGeOYzjVBPezsIgGdv2HR+8f5wvUDsL9+EDPFblIXYNrG0FyTO9Rnr6uCTqGHgnSK6DmVYHLONX4gpsnI5Z4krt9TNfZCpDrjHZSx/mmjo28G3No4y4bfi2sr8VOfKv/qvLHo18u5HyCkvLSmbnFkXYm6Z5utp3yF6W8DWua6nSf51Z2QFV74JJ+ByX7GL7Ls9uSTtDwtk2b9+wvysTbXov+/7SaxK+JOz8JuNd0s8KutYow15rpdWvNbu34x2RO1/SqTdudi5/7Nhr84YvvXvYcfqZ5O1TTTadcRnvGpf36DirSPGNqZqNp0Fv2PF0hH0glRKeacOLdaxVH0cgdBzZ37Pj6xhxV+Bb4n3ph33j6A0dRzUZPyLb2vbbVgnPqzYXj7WymXY/xw4J57reGyrKL3bt6XtR0idLuMDm7xxxTGyT9JOrxpSE24YdB6nwVUnPCbUtJP38nqSN0Pe/qvr1DfwN3pr3aeKbNe1T5oKgvT3SFtqv7j6M2i4Jt5/kOtlPsuRPh1/P7JuVP3rm3Mo9q99YHt1P8t/sJ5li9BkFDsfXcvDweIPT/RE+toINNeyFx8AmsC1sDdvBDrA9HAw7wANwlNHnBzhCy4+HA137OxpAvOznSIR9YRIcCJPhEJhk9e76fAAnankJcJiW11g=
*/