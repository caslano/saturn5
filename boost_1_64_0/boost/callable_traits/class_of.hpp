/*

@Copyright Barrett Adair 2015-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

*/

#ifndef BOOST_CLBL_TRTS_class_of_HPP
#define BOOST_CLBL_TRTS_class_of_HPP

#include <boost/callable_traits/detail/core.hpp>

namespace boost { namespace callable_traits {

//[ class_of_hpp
/*`
[section:ref_class_of class_of]
[heading Header]
``#include <boost/callable_traits/class_of.hpp>``
[heading Definition]
*/

template<typename T>
using class_of_t = //see below
//<-
    detail::try_but_fail_if_invalid<
        typename detail::traits<detail::shallow_decay<T>>::class_type,
        type_is_not_a_member_pointer>;

namespace detail {

    template<typename T, typename = std::false_type>
    struct class_of_impl {};

    template<typename T>
    struct class_of_impl <T, typename std::is_same<
        class_of_t<T>, detail::dummy>::type>
    {
        using type = class_of_t<T>;
    };
}

//->

template<typename T>
struct class_of : detail::class_of_impl<T> {};

//<-
}} // namespace boost::callable_traits
//->

/*`
[heading Constraints]
* `T` must be a member pointer

[heading Behavior]
* A substitution failure occurs if the constraints are violated.
* The aliased type is the parent class of the member. In other words, if `T` is expanded to `U C::*`, the aliased type is `C`.

[heading Input/Output Examples]
[table
    [[`T`]                              [`class_of_t<T>`]]
    [[`int foo::*`]                     [`foo`]]
    [[`void(foo::* const &)() const`]           [`foo`]]
]

[heading Example Program]
[import ../example/class_of.cpp]
[class_of]
[endsect]
*/
//]

#endif // #ifndef BOOST_CLBL_TRTS_class_of_HPP

/* class_of.hpp
PkjWBJ2AgTVBh5GEofgJ0+AoxLf2ZyYsQeqQm5AGXQe0F2nk7yPIickI9K3lGYgsRmp1Dc8OuA85gBxCmpD3kc7DY2xrdXAD98ECWI00IIeQF5GTPuFe93TWeiC+tTcT4QqkBKlD9iKBs1SOwgx4DBbAvchJ/o4fQXjIYqQA2YTs1DNTGopYxwWPIq8jJxD3SOKJ9EMmIsuQaoS1L7LmZdvI5mtd9mDXgBxEXtE1L0f5OwtaF+Af0g8JrHPJgZuQnbLOJbjGZQgyEzmCuQk5gbQbFVzHMhHORUqQeqS7rk+xr0l5H0kYTXki6UgGkoNUICtmog/rkYOk/XXEKmZNCZKJ5CCbkJuQBuRwcXQdR/SKXtErekWv6BW9otfHdbmRso99/j+7orSwuuhsrQF4Ptky32a/72p+RvSHvNhklfm/zSb8bN8R0YG51d92ajZ+rLodbWO5uND7c8z9VJ0X1Pu2PYaygjrix80SRqkEonNE5n743gdHk0/9rXRg7o64O8zdEZ9mc3cmjmZc/mZxL/EK2fvnLV2LMF7Hui9A3kfXap6H2cU6r+eUl5YtncQ5Qn7oHh2i11/zOOAu0awveIF8+flpzkM45E14ek2didc58Cm6vmAo8jP+qKuQ9LKRcHaNThtp/JulU3V7BueGdP5G06P3u5rx/9vEPMA2VyQHlZv8uEXudxdzlnGfZPKjKzF/qRX5cXPz/NB5GYmnzn8E5mUkLiF14n5383Z1DD8zSiWPKpjVy5aKoYtrnOuEurGduf7cGdZ5WSOi8Tvi8StnaxkuRt7mj8aS8PixgCYkbgVVtvUzqt/VzKW9JObp5IPL5qaqMj/YH6ibJLN24AUxT+P7sDbk18UdG8i7WuL3CumM7domJt7Tvo073nNOIP2vJvvSMq9jwPzLVpSrPz9IQ7Bc1Y44huVRfVu/B3dqu96FuH37KJaF51F1ZUnz8tO1CkafvO4YXL8gdoMZC+9qm6eq3lBR6M8nvFF39vsVIwLz6UXG389YY5mDvFjXVBQZvwcYv2PbiNuRODX9KW5NGSzEvF3M5YxPx6td8zjqWhZfh2D2CtoqOp+zuvPvCiTQ3pqSKZeW58Rnm3nEsHqq/a3OV0meiF2WsSMfVG+Z2cNC0hfSBjvrfvEfaPmdQNpSfhnlEcovu6q60rENqhtC7KP1fKGY37Ti+XcWUoPs5evQnyI+PwYmBMszVeq9+kFs5jKa+FX8ehEJ6rJVR02h7lETquvVNRXkvcRnJvd3yv1B6F/c8Sbq6Z52jGWS3/G9Vph+oknbSWB++teYf4O83oq1CpHKhfiGl4vaSRpC2tBBLYNxWgYjkTfxsyKsn9EfxuZtSOvZp0X/PPoql5aJ+oGG6Rda7gdmn06/eEyHzjYiKUgh8g66OeH9Nn+sLixzjO8W0Z/LCps4E1/8ML95L/r3q8EX7RfN/W6mX7xSzJcyJ9MmpP3hyPS320VnkTXMtk/Xq9r2nkPeaHXfGPqbRzyxk3iaOeO3/o1zxg5zww5zyWdvzjjyXOnZm0vOkn1jXtlacN29yX/+9ltd8n51aNsTg5znmLOu8dm/9beVHm/p9NpfVKyYNPTg9f2d9odx2p/HaR8ep/1z/vPmsCPvq3P25rDZi4XfNrnkeaRO5wFf07+X8/e70r/pO4o+8/nuueGQQOej81BzYEc4F3YRc3CvAUvdj1f39r0Gpur83DTYC2bCYXA6vADOMPPF+uyrz+d1YfPFn9L514lwKLwQavx5znSO/wCN/0CN//kaf8w6b6bPdTBb3dvnzXpquL3gANgbDlfzKDXPgv3Uv13m+YfnL/UvAe4M7EWk83BZMAkugOfBIjgIlsB0uNw=
*/