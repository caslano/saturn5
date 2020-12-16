/*
@file remove_transaction_safe

@Copyright Barrett Adair 2015-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

*/

#ifndef BOOST_CLBL_TRTS_REMOVE_TRANSACTION_SAFE_HPP
#define BOOST_CLBL_TRTS_REMOVE_TRANSACTION_SAFE_HPP

#include <boost/callable_traits/detail/core.hpp>

namespace boost { namespace callable_traits {

BOOST_CLBL_TRTS_DEFINE_SFINAE_ERROR_ORIGIN(remove_transaction_safe)
BOOST_CLBL_TRTS_SFINAE_MSG(remove_transaction_safe, cannot_remove_transaction_safe_from_this_type)

//[ remove_transaction_safe_hpp
/*`
[section:ref_remove_transaction_safe remove_transaction_safe]
[heading Header]
``#include <boost/callable_traits/remove_transaction_safe.hpp>``
[heading Definition]
*/

template<typename T>
using remove_transaction_safe_t = //see below
//<-
    detail::try_but_fail_if_invalid<
        typename detail::traits<T>::remove_transaction_safe,
        cannot_remove_transaction_safe_from_this_type>;

namespace detail {

    template<typename T, typename = std::false_type>
    struct remove_transaction_safe_impl {};

    template<typename T>
    struct remove_transaction_safe_impl <T, typename std::is_same<
        remove_transaction_safe_t<T>, detail::dummy>::type>
    {
        using type = remove_transaction_safe_t<T>;
    };
}

//->

template<typename T>
struct remove_transaction_safe : detail::remove_transaction_safe_impl<T> {};

//<-
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
* Removes the member `transaction_safe` specifier from `T`, if present.

[heading Input/Output Examples]
[table
    [[`T`]                              [`remove_transaction_safe_t<T>`]]
    [[`int() const transaction_safe`]   [`int() const`]]
    [[`int(*)() transaction_safe`]      [`int(*)()`]]
    [[`int(&)() transaction_safe`]      [`int(&)()`]]
    [[`int(foo::*)() transaction_safe`] [`int(foo::*)()`]]
    [[`int() const`]                    [`int() const`]]
    [[`int(*)()`]                       [`int(*)()`]]
    [[`int(&)()`]                       [`int(&)()`]]
    [[`int`]                            [(substitution failure)]]
    [[`int foo::*`]                     [(substitution failure)]]
    [[`int (foo::* const)()`]           [(substitution failure)]]
]

[heading Example Program]
[import ../example/remove_transaction_safe.cpp]
[remove_transaction_safe]
[endsect]
*/
//]

#endif // #ifndef BOOST_CLBL_TRTS_REMOVE_TRANSACTION_SAFE_HPP

/* remove_transaction_safe.hpp
iTBvBi0xbew8n2brhp2HirLC3CLfh1kKy1HX2nngUSlnudOLvzlOnJRfaMtvYvWMt0n5HzjDzJlOmPEg82lXkRntcc31lBM814fq0TJUX7pD5B6MaWri+KU5ypzqiTFXe142c2NiyYMM59hlg9iuCZ3v7V7AP8nxjwrXJpLnsab+ebK4gjz6m/ehlJlBeKiMy61Sj20xIb8J0lZPiGyltkmgPtMZBY4T7psrte+XNvTP/1Z+sMhnOA1dez+GMDdX7f3YLfW+mP0T1FviaGkpq5krj4w3yTOJPPslz4nOCPJU1YV0bd85cuzXWAv2VGvPZFc9ckpk+rI60Q+l3Nd5D6mzxgWfd7IZKtfv+yJ3hzNR27qV8be1+/5iGjLAGcJulb+x2p4u8fzaSPwATx0zmnvauqzvX+s0o/8z2Guxshb3NHX9c37MOa/XGR6fXLe2N75ezNLb2HFRv55vv8TVzD+tOc6f1b7A9sSa+3XIv4afnBL0G6SeeHwH0ra57BrchH8A/yB+CmmHSDsFUkf7m7TJW7N9kwPuD95/tzRkbrwgwty4MsLcmB707nb1615+l0LvmbkHXvWn4HviCRvC3xOvVuVZP7VrnwJfQGblxoBumW+LzMqdVRS4J84riGSXRfN0tXtpn5DwD5Huh1W+v7UX8JyEV9j9PDc/IL9HIfe39vdM8/e1drm2S/j70HtZwvqdMUm/ScITbf5emh44Xr3qtrv0mtwk8nUd13xIGUf+nk0Jsi+K3Feu672im/2eDelv+9vbH7Z1SQu99uw8V0667r0kTE0lPIynsGNMF66f2q7voXyCvwGfpd9RGijXB6zhN1J891szH6h+v0Udg/cBhrFFMCXM/dbMMPdWBUH3VpG/izNUx+1byUacT0/ihefAvzBuWzwYcdzykC//jTR+NW+GHb9DJXyaE2H8qnxz28eDJVzgRPjem8o3teN1oITnh7XBVkR6P0kvc7x2zOhqhSwjVI2dcpHrHyJnVzXs7+kKkavtRBpTox+S75vZMdVdwkU8+Y23NtSGJgbNqTKePtF5dAb+IOEGOocyxiTt7Bp8w883xvY8WH2MXf3Qfz7GIowdlJxG3J/wDfF3GB07D0ceO/RMGfrqyGNH8ja3e4UGS/hydJJOpPlP8zS133AbKOHLzJnUNeIYEpk0a9suUl9Wilwb/a1mVEp4qknk/nUA+fVbg/SP9lMN+sjXHxsedvUH4fyHg/tM1nCC+yjc3qBI3yS0NqLOTTHi1quO9wr4HH1kHpE+Cu6gyP2i8t3sNddNwosjXdMq38Ve010kfIYTeC537HM5/WHL72jvmTtK+Bwn3LsnhyStk0mTMDuyJNzLqctv3p2mH+sqya7+zMsvqsi1v12viOxm/z2bzTvF6WoyyGXHQG6lZKu65gf9m73zgK+iSAP4vpIQSKQESCCQEIr0EiAUaYYqSgsYOpJCAgkECEnooBQp0qQIgiiCoKBHOxuKeGIF7yzo4R2nnscpthMVkTu73v99+d5k38t7lDv0dyWb3+T/Zuab2dmZ2W93p4pcmiMGmTyR4VupgKZU8m765Hz9Puwm91BbvVb/OuVdq3KO+He0mvFOHqP1Kk/c6nIN1zPO4xreLK+zojR8mFWQM4uFCWm8layI1DF4eyRMHSsEyShx461e3LZY1YhjkayB1Z3yKDqeEj+XVXydlLGkvug6BxHn30SmLSGx2/K2inWz5G0d6nsZW32vYDPnLnqvzZBKJx73q++4Jalb+rj0nEmWdcl6inqFm6de6Xev3gPHYyw5Tug98IS+m8U/ofeAv5KS5gv7GMA8vQ+8YRJMvUgW+3r/+0DKiKAqv5k3il5mT75McfM=
*/