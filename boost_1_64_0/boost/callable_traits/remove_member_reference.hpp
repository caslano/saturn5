/*

@Copyright Barrett Adair 2015-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

*/

#ifndef BOOST_CLBL_TRTS_REMOVE_MEMBER_REFERENCE_HPP
#define BOOST_CLBL_TRTS_REMOVE_MEMBER_REFERENCE_HPP

#include <boost/callable_traits/detail/core.hpp>

namespace boost { namespace callable_traits {

//[ remove_member_reference_hpp
/*`
[section:ref_remove_member_reference remove_member_reference]
[heading Header]
``#include <boost/callable_traits/remove_member_reference.hpp>``
[heading Definition]
*/

template<typename T>
using remove_member_reference_t = //see below
//<-
    detail::try_but_fail_if_invalid<
        typename detail::traits<T>::remove_member_reference,
        member_qualifiers_are_illegal_for_this_type>;

namespace detail {

    template<typename T, typename = std::false_type>
    struct remove_member_reference_impl {};

    template<typename T>
    struct remove_member_reference_impl <T, typename std::is_same<
        remove_member_reference_t<T>, detail::dummy>::type>
    {
        using type = remove_member_reference_t<T>;
    };
}

//->

template<typename T>
struct remove_member_reference
  : detail::remove_member_reference_impl<T> {};

//<-
}} // namespace boost::callable_traits
//->

/*`
[heading Constraints]
* `T` must be a function type or a member function pointer type
* If `T` is a pointer, it may not be cv/ref qualified

[heading Behavior]
* A substitution failure occuers if the constraints are violated.
* Removes member `&` or `&&` qualifiers from `T`, if present.

[heading Input/Output Examples]
[table
    [[`T`]                              [`remove_member_const_t<T>`]]
    [[`int() &`]                        [`int()`]]
    [[`int(foo::*)() &`]                [`int(foo::*)()`]]
    [[`int(foo::*)() const &`]          [`int(foo::*)() const`]]
    [[`int(foo::*)() const &&`]         [`int(foo::*)() const`]]
    [[`int(foo::*)()`]                  [`int(foo::*)()`]]
    [[`int`]                            [(substitution failure)]]
    [[`int (&)()`]                      [(substitution failure)]]
    [[`int (*)()`]                      [(substitution failure)]]
    [[`int foo::*`]                     [(substitution failure)]]
    [[`int (foo::* const)()`]           [(substitution failure)]]
]

[heading Example Program]
[import ../example/remove_member_reference.cpp]
[remove_member_reference]
[endsect]
*/
//]

#endif // #ifndef BOOST_CLBL_TRTS_REMOVE_MEMBER_REFERENCE_HPP

/* remove_member_reference.hpp
7jjPGPJvNXlOuHmt0MqlS74Sh3aRcHdPbxNn4jxx4ea7oHtY8tt7ztVaH04Hx/OX3k/1raonTn777by7QtqhnR3jhX/xhf+gYcc8KukDgmw6l8+rskt+jsjXcvzhgHwb0gP3hrMWzDFVtqZvFvkRTm1fun/M2/vPrq/qPiTOPV3i6DOJu41WHGQKOJvTSbvEJMi9+UpjNP1DyhiXtJk5qmkD9PEUVrfO0q88ZnxSB66No5A74LqPLE2Re0nxWwi3TKq6FqYcYd8R52fvE72Ev9ZwRUlJOWbEiwwuLchmb/A4lXu9ML83K8P83qwK83uzuvrvjZ27G0q89Lv9dlMLiZvtv/ak7Y35ayP/tddBr70X9NpLxddT/xdkNvv34VOgf+/9DuLY1zWJsP42qQw5I//etBjj3vNMGdRHy6BOr5Df1snuv/rp+3zC76f6+fZB/dT9V8/LvqkzP+t88Kb+mX3i3pry1sqMfd9E2gcVaT9VpH1Qv/w39yPsy4qwr+mnfxP/p+6/irCvLML+usj76L40xONxMk+shCkcU+zK2LUiXR/Ax+Bbq/w8kuvBItgKzocH4H777C9rMZKvCX6f5ntG7SHvgBPga3AB3AXPgm/A8+Cb8CL4LlwD98L74D74Anwf/h3+HfoO9iFMhR/BDPgx7AM/gRPgpzAHfgYr4OfwfPgFvAgegvfAw3Ar/Brugt9Cj4exClOgbxJoDx3YEXqgthfPXZHba46211xtrwJtr774/ZqvueaLxXfSfA9pvoehFz4C0ySsxw08L8C2YY6bq/lnwQw423XcbM2XHua4GzTf/bAx3AiP1vABuMfeu8r9r+T3pe/U/KervaQy2BcuglPgEjhX7TUXwXPgmfD3cD28AG6HK+Hr8HL4KbwCfgevhMm6fysF3gTbwWthJrwOZsFb4InwdjgFroFz4b3wdHgfXA7vgHfCO+FaWAmfh4v1PJfa+xLux3Q8d8ZXuOx8p8JG2q8psB1MhVkwDY6BTeB4eCo8BTaDC2EL+AfYEt4FM+BG2Bq+DNvAnfAYrU9b+BXsCOMc+gs2gl3gMbCbtkNfbYd+cDIcAAvgQFgGB8GF8Fi4BA6GS2EWPFfzr4DD4OVwOLwCjoDXwFHwJjgaroZj4Dp4PLwXjoMPwmz4CDwB7oQnwo/hZFiL9jwFNoOnwnZwOhwFZ8AxEm/Huf6+0rb4lSHj3Ovxj9dUmART4FuOibSHzbXP7Vfez/Yr72VbujP2N7mfre8S+gO/BH8DfjN+N/4QPvF3tU2730X3tUVd1EVd1EXdr6j/R21U/DPY/082dZPObsQaJTc33Fnkc98pewJmuL4JsMkx4pbpekYl/jXfe82PB9bLc8tnd59VHNBjv0qaYwhbXUNA9mjj1TWnuyVcaDL5O0xtKLdLDP4uwB0iM9d0oUZDAzbgbVle+x5+DnWdmVLzd7xfFd2a1k/XaTh2NRvr7WKNuEUcpAEshbvIm/VE1V6I7nn5s0mqZjOac1a5dna9u0DC7zpbzPe69uaY0U+KfW5dy1M9s65TN4L3S56rnQU86ek6qebxmGRrC5rxkJdbkevS9b4n+dY4Xi3XyuRI+fb952dELiXse4Ez/fX3hL5jLfszJK2Jyx51UdD36zpuJv1Hz7NknnGd52CR/4iVxPfsevDYJ6tsWJfKMUqtDqKdyP9AzeP0nUjbLoSRt+ucVWv+30md/+zcgOxQxk4Dq8vWdUh9L/oZvI+HlavEk47PDdipqME33n1rk5xD0DuRMyPY88cErLiOas88FfrG2synXGOtIL8ywlhTOa+9vhZKuJHTlvZhYSLsdwTrbhEZ+557CwnP5PhDQt+Vl3X8NpI+AXk=
*/