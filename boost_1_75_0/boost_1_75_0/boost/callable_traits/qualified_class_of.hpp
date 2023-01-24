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
KaJ01AKgJZ5Ld3olVynVs4uF2BW0Cn5BawwT2+AQY9Srjuv5ujih52eA/Kon3Y7h+FMKLsOBwAoiHwbzmXiGHwgfDG9T0CGKnrktvH4if5WIrzAW/D1uxk0UcirQvcbEilJK/2ZFzDFaNyE+hHOFtBOMxcUP50vmDSZjg6isT9eTqpQM9LaP4CllLWWyljzpwdac8qDaTvC8HQbt714BYNmGDbF3RtR7HWI7PJ3K4ZoJ8a0JURZMvk1phhNB+kqxesalwUGTmSb74G5R6a2spSHYxRCrqyd72lY5D/ChFVzESeadn7iCOp+scEf2MGGFPCKNnj6AP0zxf4Qynl+cqHBTGfVKydDL8O4qM+Jdtl+8u2WSjHdDlF8DlV8W5VePSYSNr3HsvHkyXa/n12smY44BkWFislFwpUXA6YLRcH52Tko445mJ4dJVwwBBMh8AmiKo59ImIvymMtq4LIhWT18hZwvkB711DFPZJ/Zt8OSWME7nHs3WuV58bmUQCECRWCtatSYiGABhRDQ8gJyRsz0azw18ZhIev3VsMl5yJ9F6AhgaqZc5d0cJOlwi0uNW7GSMTydT8HNRTX1O/pKFvpQ1mT6B3wgHXhGRJIjH2bfYPBnmWmTLVB2emjnDlcVUXUgRCRKexAaesQhOpWQf7ISMHm0glZ4CI2MRNY8j0cyqxgPwbExuNxe5+Lm9rEIH3NcoVwBLea2Vla6i
*/