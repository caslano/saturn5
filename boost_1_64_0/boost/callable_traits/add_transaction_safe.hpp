/*
@file add_transaction_safe

@Copyright Barrett Adair 2015-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

*/

#ifndef BOOST_CLBL_TRTS_ADD_TRANSACTION_SAFE_HPP
#define BOOST_CLBL_TRTS_ADD_TRANSACTION_SAFE_HPP

#include <boost/callable_traits/detail/core.hpp>

namespace boost { namespace callable_traits {

BOOST_CLBL_TRTS_DEFINE_SFINAE_ERROR_ORIGIN(add_transaction_safe)
BOOST_CLBL_TRTS_SFINAE_MSG(add_transaction_safe, cannot_add_transaction_safe_to_this_type)

#ifndef BOOST_CLBL_TRTS_ENABLE_TRANSACTION_SAFE
template<typename T>
struct add_transaction_safe_t {
    static_assert(std::is_same<T, detail::dummy>::value,
        "transaction_safe not supported by this configuration.");
};

template<typename T>
struct add_transaction_safe {
    static_assert(std::is_same<T, detail::dummy>::value,
        "transaction_safe not supported by this configuration.");
};

#else

//[ add_transaction_safe_hpp
/*`
[section:ref_add_transaction_safe add_transaction_safe]
[heading Header]
``#include <boost/callable_traits/add_transaction_safe.hpp>``
[heading Definition]
*/


template<typename T>
using add_transaction_safe_t = //see below
//<-
    detail::try_but_fail_if_invalid<
        typename detail::traits<T>::add_transaction_safe,
        cannot_add_transaction_safe_to_this_type>;

namespace detail {

    template<typename T, typename = std::false_type>
    struct add_transaction_safe_impl {};

    template<typename T>
    struct add_transaction_safe_impl <T, typename std::is_same<
        add_transaction_safe_t<T>, detail::dummy>::type>
    {
        using type = add_transaction_safe_t<T>;
    };
}
//->

template<typename T>
struct add_transaction_safe
  : detail::add_transaction_safe_impl<T> {};

//<-
#endif // #ifndef BOOST_CLBL_TRTS_ENABLE_TRANSACTION_SAFE
}} // namespace boost::callable_traits
//->

/*`
[heading Constraints]
* `T` must be one of the following:
  * function type
  * function pointer type
  * function reference type
  * member function pointer type
* If `T` is a pointer, it may not be cv/ref qualified

[heading Behavior]
* A substitution failure occurs if the constraints are violated.
* Adds the `transaction_safe` specifier to `T`, if not already present.

[heading Input/Output Examples]
[table
    [[`T`]                              [`add_transaction_safe_t<T>`]]
    [[`int()`]                          [`int() transaction_safe`]]
    [[`int (&)()`]                      [`int(&)() transaction_safe`]]
    [[`int (*)()`]                      [`int(*)() transaction_safe`]]
    [[`int(foo::*)()`]                  [`int(foo::*)() transaction_safe`]]
    [[`int(foo::*)() &`]                [`int(foo::*)() & transaction_safe`]]
    [[`int(foo::*)() &&`]               [`int(foo::*)() && transaction_safe`]]
    [[`int(foo::*)() const`]            [`int(foo::*)() const transaction_safe`]]
    [[`int(foo::*)() transaction_safe`] [`int(foo::*)() transaction_safe`]]
    [[`int`]                            [(substitution failure)]]
    [[`int foo::*`]                     [(substitution failure)]]
    [[`int (*&)()`]                     [(substitution failure)]]
]

[heading Example Program]
[import ../example/add_transaction_safe.cpp]
[add_transaction_safe]
[endsect]
*/
//]

#endif // #ifndef BOOST_CLBL_TRTS_ADD_TRANSACTION_SAFE_HPP

/* add_transaction_safe.hpp
/vhpeJz0+MdJV7v0eQnvD7HmPkltYKTAFrAxbAPPgt1hMzgUtoAZsAucArvCaSo3B7aChbAdvAZ2gLfDTvBOlTsq4676HNDnG/GRdmePxqcPcr1gX9gfDoDpcBAcDtNhDhwM8+AwuACOgCvgKHgHHAu3wHHwQTge/hZmwlfgJPgRnAyjdRyxLpwO68Hz4VkwC/aCs2EfmKPpIB7a1pE3mq+1YA9NRzcd/+oO42EPmAR7wsbqLwqPe4XHvcLjXuFxr/C410kd9zrMWFeddNZkpP94x7xO0ft/Tk29/89Nsezz8PsfmMcY+j3ih9c/D/fDf5j98AHhfl6N9PPCfTzTxzu+/l01+3bhfl3N9OtOR58uRH+uRvpyVe3HVdCHq3b/LfwL/8K/8C/8C//+X3+n6P1/dmlpzaz/H5HiMvu5rPTawdNxxlTcCmuc8Uqz/r8kf17B3FzPlurEoVjGD7+StcslfnvRoWPGF9NlboCIm3Fqwv32B8ioxvgi17P2B/Dbz41rcEyu4Td2WkfXzHfVNFnnv4Y0HXFOU9acy7LGjxrmckqb6iaF3Oe6IfSEt7CFy9Y3uue7f3i0jOHPuax0bomudQ+l791fdXj8eW5Jg8q4Zeyb4jf5eGZDTz72qYKdgsB8zLDvua3HMs0xSYPZ15B4c0ziLceyjZzE1a8M1kQFl8G1lEHaVRWWwXlDRjuXAbqmDBqLnQK5HbR+abhjGWi4cxkQXnkZIBOyDMaknFgZkB6OkZ4aLIOU6OAyWEsZFFVcBqVLSp3LoEjLIIHwjnHee7xg9sK5vnIoqqQciioph6IqlEORQzmMO85y8Np8IE0c86bpxMvCO8/qiJZFEy0L6+CNlMWuoLLI5SFQOtfT0jqWg+rF2/OoMMfXHml4E5Mv551gW6vp4hr+dWxAneB0bSJdBwPTJduZyY5uld7nB03azH1u2toxJrwJcTNpn11SWsTm+aaOGZlQdTBfw+35M+EE80fvX4lnstYvzTMTN9Pemrrkv7da3BnBeXmr9dwKlZdaQaz09WoZ4nlVSf04EpD+SdVIf6+WVa8fHWOC03QH+nFlDmkyj2LHtKluvNOzmPDK64fKmPRPqZH0FziXf0C+pNcNzpct1vPRMV/0tnHOF9WNd34+ViFf0gLyZdoJ5ot5rlUxXz4JkS9bOW+mc77kFC4q4JSO+aK68SZN5x9nmuzteXls6H5zkS+eiwoCnq7O7bnqOfedCT+5fecR3vmt9UP3nTc7pct+yzqmT/Wd+88a7txnINy5zyDhlfcZNpf98PvP3nI42CB0//lwZeVAE+FcDqrv2IcmvJJyOFxJORyuQjkcLvvh96G95ZAdH7oPnbrMuRxML9q5HNCvvB+NjHNZmHDHsiC88rJIXfbj6kf3SQjdj862l0dwT9qhHFTPuZ9E+MntR3vr2eqGwenaTrrKQqTL9KSrcL+X2dJXL7gvTXjlfQJknPvSEl6zfel6J9CX9taT7MTQfenNofNTKolzH0L1nOsJ4aemP70kKXR/utwxXebx7JQ21XXuT5dXoY6ULzu9/en1yaH704cryRduH6d8Ud1452dlFfLl8LLT25/u0yh0f9q13DlftEftlC/o1lx/+ktZg+Y0T8xpnpLTPC6n+UtO87uc5jU5zU9zmq/lNN+s+vPZWlxjHd/WcOvA7FtjR3brmtV2z2/f6e40b8pp/pXTfDOn+VFO8+ic5o85zU9znsfl2ZtOxwD0valOwN50Z+m8/LNhKjwHevWOqF7XEHqDVC8ddoRDjR7uKme93qrXR/X62/SKKtDLUL1RqjdW9frgdqleE9WLgl1Ur5PqdYbx8EyYJH6f/sEK9DNVf4LqT1Q=
*/