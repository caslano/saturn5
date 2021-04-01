/*

@Copyright Barrett Adair 2015-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

*/

#ifndef BOOST_CLBL_TRTS_DETAIL_PMD_HPP
#define BOOST_CLBL_TRTS_DETAIL_PMD_HPP

#include <boost/callable_traits/detail/forward_declarations.hpp>
#include <boost/callable_traits/detail/function.hpp>
#include <boost/callable_traits/detail/traits.hpp>
#include <boost/callable_traits/detail/default_callable_traits.hpp>
#include <boost/callable_traits/detail/utility.hpp>

namespace boost { namespace callable_traits { namespace detail {

template<typename T>
struct pmd : default_callable_traits<T> {};

template<typename D, typename T>
struct pmd<D T::*> : default_callable_traits<> {
        
    static constexpr bool value = true;

    using traits = pmd;   
    using class_type = T;
    using invoke_type = T const &;
    using type = D T::*;
    using function_type = typename std::add_lvalue_reference<D>::type(invoke_type);
    using qualified_function_type = D(invoke_type);
    using arg_types = std::tuple<invoke_type>;
    using non_invoke_arg_types = std::tuple<>;

    using return_type = typename std::add_lvalue_reference<D>::type;

    template<typename C>
    using apply_member_pointer = D C::*;

    template<typename R>
    using apply_return = R T::*;

    template<template<class...> class Container>
    using expand_args = Container<invoke_type>;

    using is_member_pointer = std::true_type;
};

}}} // namespace boost::callable_traits::detail

#endif

/* pmd.hpp
3vewA4PqieQFl9gZU4mlG9orrkR7qlG7YScZXT8PgM8ImK78mJy35GyH+0YoQmb7zYeYBqI8ixrjOLinocPT6o18Qq/4uhYcPAF89ZTJ/jMg4kf3ukpAhaPSMCx1Bo68ITPK/Hew94s3b7XJ2d4Lp0Xuycs2wt2f4va82j2GBoYjljmBnKIbtCNMbJEGuEoLwkjxUHUI00jrtHSE2p5y5RhV5jhcIq/vS/t7Lh5Sek0lXoSJiLzW8qXhbsotT8Wb7G4wi1C7dWm6xZLY+t9pkboj0qGQFwVdQqUNVTLH4WCt/htd5Up58SgrA6O0drYkPQagr8Ufbxb1zhkTaUteGR8e3MUsy43BTvLF9Wmfjyi1Io19v/3uVdDhA4rQcKD7NhP3jab/A0ok23suA7XevpdI5MbojRqhAqwF0lAtroulxgCKzjNoWi70UOVkfLOnRorPgeisKkQzX6LSEsFucnagLyhQhFekfJTopam5EvEWAxj4uPY7I96+5IY4MeCUGwnEeCUnLXUPE9R/u3rU+jexGTiOoI1ibdI6rCSsIRiDdSFX8fprWFeIQA==
*/