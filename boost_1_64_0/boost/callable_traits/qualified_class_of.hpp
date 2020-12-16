/*

@Copyright Barrett Adair 2015-2017

Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

*/

#ifndef BOOST_CLBL_TRTS_QUALIFIED_class_of_HPP
#define BOOST_CLBL_TRTS_QUALIFIED_class_of_HPP

#include <boost/callable_traits/detail/core.hpp>

namespace boost { namespace callable_traits {

//[ qualified_class_of_hpp
/*`
[section:ref_qualified_class_of qualified_class_of]
[heading Header]
``#include <boost/callable_traits/qualified_class_of.hpp>``
[heading Definition]
*/

template<typename T>
using qualified_class_of_t = //see below
//<-
    detail::try_but_fail_if_invalid<
        typename detail::traits<detail::shallow_decay<T>>::invoke_type,
        type_is_not_a_member_pointer>;

namespace detail {

    template<typename T, typename = std::false_type>
    struct qualified_class_of_impl {};

    template<typename T>
    struct qualified_class_of_impl <T, typename std::is_same<
        qualified_class_of_t<T>, detail::dummy>::type>
    {
        using type = qualified_class_of_t<T>;
    };
}

//->

template<typename T>
struct qualified_class_of : detail::qualified_class_of_impl<T> {};

//<-
}} // namespace boost::callable_traits
//->

/*`
[heading Constraints]
* `T` must be a member pointer

[heading Behavior]
* A substitution failure occurs if the constraints are violated.
* If `T` is a member function pointer, the aliased type is the parent class of the member, qualified according to the member qualifiers on `T`. If `T` does not have a member reference qualifier, then the aliased type will be an lvalue reference.
* If `T` is a member data pointer, the aliased type is equivalent to `ct::class_of<T> const &`.

[heading Input/Output Examples]
[table
    [[`T`]                              [`qualified_class_of_t<T>`]]
    [[`void(foo::*)()`]                 [`foo &`]]
    [[`void(foo::* volatile)() const`]           [`foo const &`]]
    [[`void(foo::*)() &&`]              [`foo &&`]]
    [[`void(foo::*&)() volatile &&`]     [`foo volatile &&`]]
    [[`int foo::*`]                     [`foo const &`]]
    [[`const int foo::*`]               [`foo const &`]]
]

[heading Example Program]
[import ../example/qualified_class_of.cpp]
[qualified_class_of]
[endsect]
*/
//]

#endif // #ifndef BOOST_CLBL_TRTS_QUALIFIED_class_of_HPP

/* qualified_class_of.hpp
7kTTQsdOIP+l0j8cM2jMpGm+mSLTxkkzdU0P/AS8jCebn/Kqxk93YN9dnyHpu50M+mcAfjJexpfN28xV1wprXyPff15OE2rWE5+Nl3Fm87Vx9W+x5PP6elPSnnMaMW90xo/GV/X1GfllJfJdDllX+IdPltZ22R4odtvDbyDPbk2trYKOEq4XqC+u1NrmqCtpza0Ni+OkrY+hrZNVxua33+YYJTIXuOo3uxt/rN3ud6R+I0wGI6EfPjCGD0i+YXa8t5ZwHdOb8VrX6Byoc14q/jgvXubCKj9U4mANbMjLnBcylit1LNs5r2osd3ev0+h4jq65hFlz6StrLhtPeWXaXz/fsn35lXva7z1044PRNZf/Zs2lReDeSO/ZauFbGnnGFpes9rOPhr1hGuwPm8BBsBnMhi3gTNgSLoAZcClsBf8A28INsAN8CHaFW2E3+CzsDXfCvnAX7A/fhAPhHjgI7oVZ8CM4BB6Cw2Bdh2dz2AyOhM3hKNgJjoGD4ClwEpwKZ8DpMBfOgAvhTLgM5sErYD68Ec6BtBNrN/p7DetrOzUQ+wN+d5raDyiB3WAZHAAXwpNhJSyDi+FCuASerekr4dnaPkv59zhcBl+Gy+Hf4IXwU3gRPMohrPXKsvM7v29arzaGaxEaff+8BbwOdoY3we7wFtgLfgSHaHgEvB2OhXfD8Zo+VcM58B6YB++Fp2n6Qg2fCTfAm+D98G64Ed4DH4BPwQe13x+Cf4WPwE/gJj2fJ2Ab6v4k7AufgtlwCzwNPg+XwpfgKrgLPgJfh4/C3fBx+AZ8Gb4J/wLfhXvg+/Af8O/wY/gR3Bxds/hNrlkMW1zbTMdXLv7/Wrv4dZ7/CwrnVPw83/9bZPX/8lsmbrnvtwguhV2acX29GXj+L5Ijm/BrACrntTrOhRIucToYj5mHD6ffLxeZcqeLTxIv95+2rIZBz2rJpBXYtPlikUzvT4O+qeV5y5e+0/3NIft9u3mkfyL5n3U/X1k9fbrkHcL6aAN7z3mrxCWHtUF4rqR5XfWYI2knkPa1HGexhm05rnoVSb0C37jZKvJNnVST4JIpXmRcaxsPiUytKptpaqNwmN7b9jWhLvQ5Lfh5foroE8M+pwXZB5sSa8Q9gG+IX4N/rSn3sW8Hj41u4ceGyh1tbZ0VSvh6nhoc97iwz29zJP1a05o6SFvbMryu5+bcoO82rpH0aWGfq7NJ3yDpJ9p+rGVm27J3kybtyrIIVRG3TuIaGa/EIYTbLHHDTappVu35/DRE7pP0kwlPTfKQMuQ/stXm75u+rr4J6osEI+4msSEJ9TrNeifQF2XhrlN7zU0VuXOdTvx9Eq99pPnTTJg1O01Lsdf2ZAkvd7pQsy1493Xq1fE8SWQucjJNjHkab5+FJb5R6LUrfdj9bzIuNEyEhJtWu5aT9Xp4QMpq70w19apdz8n8byD5SefoGfb6L5K4McYrMoFjvMhRenLGJ5lkkXPHX+deX7FlD5b0IfRBY5Metqzm5vemLasQdULnDpkfCkR2POURDnM8nU/s+O0n6Vdq2LZN2PmkhOTbpG36s1OgVtj5pBiZO0XmKLVJaNcxbb9fJsdIo60IB9Uxz1wWsKWn89B2/BDZG3Hkb2f9N3PRd7o+lKS2CuOhzEV77PgPOxfZuUXkDptW1kZhIK833NgnLWTukvBXpo3MXbbdbFmN5Zks0ebfJ/Lpdm2lr6S3DzePye/XHSKfo2GVJ3+YeU2O96rID9WwLT/smuBNInuv/n7oHpr/yM5ttTkquu4RZt2jQNY9Tqk8ddlbpXfs/Wp59jsn9Dz3xOi6x3+z7rHd6D0gXB7G/uEk/X7cdNgEzoD94KlwAKyEI2EuzIE=
*/