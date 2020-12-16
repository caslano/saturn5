/*

@Copyright Barrett Adair 2015-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

*/

#ifndef BOOST_CLBL_TRTS_ARGS_HPP
#define BOOST_CLBL_TRTS_ARGS_HPP

#include <boost/callable_traits/detail/core.hpp>

namespace boost { namespace callable_traits {

//[ args_hpp
/*`[section:ref_args args]
[heading Header]
``#include <boost/callable_traits/args.hpp>``
[heading Definition]
*/

template<typename T, template<class...> class Container = std::tuple>
using args_t = //see below
//<-
    detail::try_but_fail_if_invalid<
        typename detail::traits<
            detail::shallow_decay<T>>::template expand_args<Container>,
        cannot_expand_the_parameter_list_of_first_template_argument>;

namespace detail {

    template<typename T, template<class...> class Container,
        typename = std::false_type>
    struct args_impl {};

    template<typename T, template<class...> class Container>
    struct args_impl <T, Container, typename std::is_same<
        args_t<T, Container>, detail::dummy>::type>
    {
        using type = args_t<T, Container>;
    };
}

//->

template<typename T,
    template<class...> class Container = std::tuple>
struct args : detail::args_impl<T, Container> {};

//<-
}} // namespace boost::callable_traits
//->

/*`
[heading Constraints]
* `T` must be one of the following:
  * function
  * function pointer
  * function reference
  * member function pointer
  * member data pointer
  * user-defined type with a non-overloaded `operator()`
  * type of a non-generic lambda

[heading Behavior]
* When the constraints are violated, a substitution failure occurs.
* When `T` is a function, function pointer, or function reference, the aliased type is `Container` instantiated with the function's parameter types.
* When `T` is a function object, the aliased type is `Container` instantiated with the `T::operator()` parameter types.
* When `T` is a member function pointer, the aliased type is a `Container` instantiation, where the first type argument is a reference to the parent class of `T`, qualified according to the member qualifiers on `T`, such that the first type is equivalent to `boost::callable_traits::qualified_class_of_t<T>`. The subsequent type arguments, if any, are the parameter types of the member function.
* When `T` is a member data pointer, the aliased type is `Container` with a single element, which is a `const` reference to the parent class of `T`.

[heading Input/Output Examples]
[table
    [[`T`]                              [`args_t<T>`]]
    [[`void(float, char, int)`]         [`std::tuple<float, char, int>`]]
    [[`void(*)(float, char, int)`]      [`std::tuple<float, char, int`]]
    [[`void(&)(float, char, int)`]      [`std::tuple<float, char, int`]]
    [[`void(float, char, int) const &&`][`std::tuple<float, char, int>`]]
    [[`void(*)()`]                      [`std::tuple<>`]]
    [[`void(foo::* const &)(float, char, int)`] [`std::tuple<foo&, float, char, int>`]]
    [[`int(foo::*)(int) const`]         [`std::tuple<const foo&, int>`]]
    [[`void(foo::*)() volatile &&`]     [`std::tuple<volatile foo &&>`]]
    [[`int foo::*`]                     [`std::tuple<const foo&>`]]
    [[`const int foo::*`]               [`std::tuple<const foo&>`]]
    [[`int`]                            [(substitution failure)]]
    [[`int (*const)()`]                 [(substitution failure)]]
]

[heading Example Program]
[import ../example/args.cpp]
[args]
[endsect]
*/
//]

#endif // #ifndef BOOST_CLBL_TRTS_ARGS_HPP

/* args.hpp
rhO6tjNsHOvCl2t07Q/mctzeL+a1+IXZhDlD0jCG+hGPm+PaR/vYmbb5J/k7WG/eVWmbiL325emnqEMZEerQTNgmQdelax3Kgn3ta9XVfhkkf7E3+WvWxpNH2EseyXrmPb4+X/ai2VhYyULodeF9mQ73pbjwQ/kZ3DSsC9bDJRUFfG7mVA9Vl3aZqu35eTG/R07HWt2QdxCtk+G/o+p2IeZAHSyQlKYG6qzcP0nc6DGQvyJaB9Vtd3Hrlh6deObiVuvuc3L/b9yPsXohf0YknGDdML/fnvXoMtv+TTSCOmUlhauqJbxL0OkkOhfhxmdmdayYy9h3vH1Yf4Kc5u96y3WBvBI7e12Q/Akpw3j9Rv5TurZuDHIXfibUBsuQDQlqSp3LUHUHBNaTUpdP//wne/zta+UPxOucrf5ObkJ2o5vjj1dp7prC7DWkJfj7smaE7ZwR1etv+rftYi4jjlLe/F2i9Sigm27W+R0U84jgmTa2vqAooE/MvKavKJZ7JNvaKvdWyT1/+eVLmV+Kuz1yL9M6h/8S9duYKrFby3N5Mn4YN2WFtdVm3eK9okOOitml/owkt3ra3eRWVm4QN7Klhei0Oe3nFf9vkOYhdgnQLfWoRHRSzFpByQuz1m8ZD6NZQ6gDrq/uvidzqzv2o6n5Y79W9uuxtKW/yxq0k698r91tW66uv+il93KLl5/XxNq34T77YzvTvjT0YNnJq9/d+51P7+31dfRdPvuKI6Xb/3J8wLM/vWFa9yG/GfeE8xrAm8WfHi/kx5WsnLP1l+23V/Q7P+vLzmsATw722d9z66qF+91/ePWxu/v/44s37bjbea3iFyVdM+blp/5m2Ykh7Su6N101+n3i86bYx9xd3KfflvfGp76f2rHLQ3m/cFpj2Po1gxPPlbWBJ17JGHPXB+Xbvh97R8nMyx52Xqt4heTb8anzu9cMvG7n4ykTr2vf9NHbvOsN9dk/f+VPn/3HX64/seHaXsnf2rmcct4h9qlPbtp5su+yx66pnf3N7Y88cNhpbabzWsItsT77u5Y+7T5n+4ff6LP/hT4D75zNy8I/xP+Vj1y5N+GFpK/M/vRbl5e8v2y30zk0La89XGbp+6C+Z2aFrSWYrGsILoSptnNcpsAxcCrMhNPgQpgJV8Dp8F1YZ+n7GHxA/T8HSrvW8xs6wWWwD7wU9oP5cDi8DE6GK+AceDlcCVfCMpgNt8AceB3MhbthHtwL8zUe9NH6fkSaNB5tYabG42L0fJwHO6k5CWbBbnAB7AsXwnFwkTkvRN9doNunH+E8Gh9nwVg4W91VIHvUXaG6i4MFtvN2OsAR8Dw4Eg6Co+BIOBqOhWPgbDgWzoWf0nIYr+UwAWbbzs9ptPQZX99JspAu/L1fw/0Oel3hI3AwfBQOhc9rOTwGF+lataXwCfX/SbgKPgWvgAdhHfw+vBk+DW+Fh+A98Fl4AP4AHoE/hK/rGpq/wR9Dt+85AbaDP4HJ8HlNxyHzbMlzuqYjSeKraxG1/lwBL4YlGt9SeDksg5thBdwBK+HnYQ18ENbCR+BGeAhugi/ALfADXUMUQ5hXw15wKxwOt8GJ8DNwJrwGFsLPwSp4LdwMPw8/Da/T9Byx9JkJpmh6kiUfg2smE+FN2j5uhv3hQ5rOW+AoeCscq/YZcBdcAr8Ic+DtMB/uhlfBu+Bn4d3wWrgX1sOvwAfgfbAR3q/p/wZ8CT4AfwUfhMfhfhjn8ofbGX7drNnT5xf4KSQrbM3ez3St0gva3n4OU2AT7AFfg2PUrP7p8wF5EMG/3tpu+mo77q/5MAAWwEFwExwMa+kX9w1iDQNyDOk+mLUUSB2yH2lCcgaZtURmDdEypBo5hLA=
*/