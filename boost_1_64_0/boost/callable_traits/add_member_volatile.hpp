/*

@Copyright Barrett Adair 2015-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

*/

#ifndef BOOST_CLBL_TRTS_ADD_MEMBER_VOLATILE_HPP
#define BOOST_CLBL_TRTS_ADD_MEMBER_VOLATILE_HPP

#include <boost/callable_traits/detail/core.hpp>

namespace boost { namespace callable_traits {

//[ add_member_volatile_hpp
/*`
[section:ref_add_member_volatile add_member_volatile]
[heading Header]
``#include <boost/callable_traits/add_member_volatile.hpp>``
[heading Definition]
*/

template<typename T>
using add_member_volatile_t = //see below
//<-
#ifdef BOOST_CLBL_TRTS_DISABLE_ABOMINABLE_FUNCTIONS

    detail::sfinae_try<
        typename detail::traits<T>::add_member_volatile,

        detail::fail_when_same<typename detail::traits<T>::add_member_volatile,
                detail::abominable_functions_not_supported_on_this_compiler,
            this_compiler_doesnt_support_abominable_function_types>,

        detail::fail_if_invalid<
            typename detail::traits<T>::add_member_volatile,
            member_qualifiers_are_illegal_for_this_type>>;
#else

    detail::try_but_fail_if_invalid<
        typename detail::traits<T>::add_member_volatile,
        member_qualifiers_are_illegal_for_this_type>;

#endif // #ifdef BOOST_CLBL_TRTS_DISABLE_ABOMINABLE_FUNCTIONS

namespace detail {

    template<typename T, typename = std::false_type>
    struct add_member_volatile_impl {};

    template<typename T>
    struct add_member_volatile_impl <T, typename std::is_same<
        add_member_volatile_t<T>, detail::dummy>::type>
    {
        using type = add_member_volatile_t<T>;
    };
}
//->

template<typename T>
struct add_member_volatile : detail::add_member_volatile_impl<T> {};

//<-
}} // namespace boost::callable_traits
//->

/*`
[heading Constraints]
* `T` must be a function type or a member function pointer type
* If `T` is a pointer, it may not be cv/ref qualified

[heading Behavior]
* A substitution failure occurs if the constraints are violated.
* Adds a member volatile qualifier to `T`, if not already present.

[heading Input/Output Examples]
[table
    [[`T`]                              [`add_member_volatile_t<T>`]]
    [[`int()`]                          [`int() volatile`]]
    [[`int(foo::*)()`]                  [`int(foo::*)() volatile`]]
    [[`int(foo::*)() &`]                [`int(foo::*)() volatile &`]]
    [[`int(foo::*)() &&`]               [`int(foo::*)() volatile &&`]]
    [[`int(foo::*)() const`]            [`int(foo::*)() const volatile`]]
    [[`int(foo::*)() transaction_safe`] [`int(foo::*)() volatile transaction_safe`]]
    [[`int`]                            [(substitution failure)]]
    [[`int (&)()`]                      [(substitution failure)]]
    [[`int (*)()`]                      [(substitution failure)]]
    [[`int foo::*`]                     [(substitution failure)]]
    [[`int (foo::* const)()`]           [(substitution failure)]]
]

[heading Example Program]
[import ../example/add_member_volatile.cpp]
[add_member_volatile]
[endsect][/section:ref_add_member_volatile]
*/
//]

#endif

/* add_member_volatile.hpp
BS+Bb8Ni+Ad4KfwM5sBY4jYX1oclMBmWwhRoyR2V9lfnM8GPND3NpH33/O7Q/sd92r7dD8+FD8AL4Q6YCx/S5+rD+pzcBZ+Bu+EB+Bj8HdwLP4S/gp/AfTDCTfnAOFgOE+B+2B0+A/vAZ+Ew+BwcAV+EufBlmAdfgdfBd+AWeAjeA9+Au+C78An4HnwSHoZanjrPhjoTojwv0vQXwK6wSPOhGKbDEpgNS+E8uBheAZfA6+FP4Fp4hfYbroIPwzL4OFwG98GV8E24Cr4Dr4HfwZtgInG6HraBa2FHuAH2hptgX3izpifOzAvhGarpael5LspvntbzPNgSztd6XqDPlSJtxy+B02AxnAUXaTt+KbwEXgaXwaXwp7AMSnrgO3A5PAyvgXWsdbqwNVwDO8C1cCRcB0fBDbAAboTr4Ca4Ht4GH4a3w0fgz+Cv4V3wGbhZ2+Mt8FV4N/wT3Ao/gfdCzRedF0GZh8iXdto+dNL2oYu2C2fBFvBsOACmQdljBI6E3eEc2BNeBHvDi2EfeAXsB6+C/eFaOEDzaxDcBofBF+Fw+CkcAf8OR8EGxG0s7ATHw7PgeXA8zISZcBK8BE6Fy+E0uBKeD1fDmZqPs+CDMEufZ7Oh7oWjY/M8i3F5AXvhLNfnzio4FF4DM+C12j6vhTnwNrgY3gGvgnfCa+BmeD3cos+fe+AmuBXeA++F2+F9cA/cDvfC++GzcAd8Ce7U9n6vd+wbfqDxTZRwz68Hcg1hb9gC9oEdYV/YFfaDPWF/KO8R+vwZCIfBIfBCOEyfp8P1eToCroNj4AY4WNNxHtwMR8OtGv6sHn8VDoVvqP8oRFbHjWljNP7xcKO3/x7piX8D2ATGwzawIUyHSXA0TIYTYGM4FTaBF8CmcKbKz4ctYRlsBa+HreF6PX6X+rfANvDnsAM0eyRt1XiGqBedkWsAu8GmsAdMhb1gJ9hX49sPjoH94RQ4CM6G6XCeyl0Kh8KVcDi8Fo6EG2EGvA0OgPeqfwccBn+hft0jRcf6eHZofO17pLTW99Q2sDFsq/WhHTwHtoeZsAOcCLvB6bATnAk7w0LYRes5uhLfNLha5depf5/6j8JMl47BwQkar9pwmG2PoQTYGLaETbQ+NtP+UEvtD7WAY8Tve384qOcdHuL94UrypR68CraGy2A3uBz2hCtgX7gKDoRXw3T1614kOv7keR4uCdiLhHpt5DKrKFfkk+M56i/X2ia3vopyu6ood7ACuTY2uSOVyKVFV33vlWOf1cz+Km+9F+G0x8qPan+ViuyaDqOyTr8ystI9VqLeP3X7rKS977zXytIrIyvdb2X9lZGndc+V7YRVtO/KTNLn3XtlD3GtaP+VA4Szj1DQPizsK3Ta9mJJaVAn5H4sa94Pbb816qrIk7IvC/sqmb1Zdr4fcUL7s+y57zTs0UK+2O3Fsj/UcduMrcpeLVXdp4U9qo5rr5ZyXF6fGNd63F7cYVxc3xhXOq4Itxl3EBfVL8aVhpuJW4nbiTuE+xbXrH+MKwO3BLcd9xauzgD2fsFNxpXhtuIO4I7gEs/l/Lgi3C24ctxnuGYDw3Zv/59+p8z+X07N2P+7JMVl1lVmRvjmNDfX75C/sNZVrqRP5LX/JxHRdZXMfuzmZM9B56M1vtrS3e6bN7BS54z72Qw0c1QI919/nSz6j9psR+n1dB1BQwl/RPyZRr9NKJsmZh57nOiUi3+C0Ul1eef5tdR5fsztw35glebLVWpXzmc/0Ld2hPT4ra2fXomdk0/U+Mc6LR9Lby/Xiltl5tuZ8hlaWFDK3BqdMekyaz7csubDVz7niu4ELR/vubo62nQcY2Q6mzLqJ/5ZjmXUW8Jnahl59Ts=
*/