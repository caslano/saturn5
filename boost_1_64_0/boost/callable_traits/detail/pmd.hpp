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
2r3Xv1/jGxng+pM0vq4aXy+NrztsDXvATuqOEXsf2BMmq7ueR5+B1LEA5ymv44WqwFYwRq8/CnaH0bC3ul8Pq8N8tc/x2Ev74X+RfviL6YO/1P73U57+9RXlrHhMJ8wozDzMDsxhzNuYrzHVVpb2w5cepUfpUXr8vxy/SP9/bk7G5ej/j7EipO229yOW5bI88SJSmCqL33n9CuN8/GRRvjj161syHJNUpxv/GSXCirdVR/2TA4TPzhmXjZeJY06JOETExJFSMg6Z0WKPY16JOERExj9YtvUPRjl17DomUjnX0wbWxdtuc03P/t27FU3+17bvSvjTdpJhm4ek8vXU7rBOiN2hbSnFc/wbXsTc1Uoyd5X4/drrTmtaQ2z17kZkz/ildRwTh9PzxwVLq8qHSHqsC6QnrGR6TPste6/I0R9zBeZazE3IWlf7pofJ+5oW02dg5u/VEdkr1c7MUbGHmLa81IrF/T7tg6XVL11L3WZ9NDnKY+Zz7jy/dDHB2pZH47ImcYmaRypbQfq0qhTlYXpubka6mUvtJ+MKLcpnyXgzZ8zIXGJeF6UlCjdPoCriZs4v7tXMfGY9p19dWR1SMg9qxuJeMg9SJ+dmBs0H5M01VgiSD6svIh9WX4Z8qPAv5EMP/DioYUVHPcwNnvvb5INnrENOgU71DbTGqcpeKX6p0m46Xa/d+J3vuq7ztpOG2duW9ZqID/t0rb++/chziD8KTvKuA2rSnJEzqcQ6oAWaXq9cbTM315FUtOf2AP4vxZh9h4vW15RwRK/hWptxIuMlnFvXBWUGudgLrAq4DbbCrPHqVwXXNPH7kvS4OXNZ2pqGlpw3re3T38t56hT3Z4q9pva3eM/zE+1iTuIze5WbvusfRb6X4zrOk8GZzpMGW/gcM991s8jRk67x697p2ndOf7P4d7difcbEFOV3lPajfiNpSHMM5imzCmPOo230k5C5W+LZJ2uS9Pa07YYVrVHqqs96JHGxoaGu5qHuCFcZr677XHWdOafmm7cfKk7i68zYCWegvJJ1TCL1XLvDiuagRlSZ95z3GRQSbYlMY5XJpJ71QMY1v1l4D5JUxh3eJ3xkaDlXaHh3jxUR7dPXuZCphZPzbPUlvqs880y+VRJ7a0rSrTL01ohbNb1fjN02b3hsYa5NT9QU/4ZqN/I+a7T84yLHASRb3nVdC7TfwdvvL/Ve+35959za78PV+ikfo8+3Sro28uGutrWRuRWDrI2scjHYdS1kXTNJ8sLm772u0OgLvyP4rycc6bOeMPH7Pwt1DENdvYYYzELP+jR+15CXnhnoGlSubtBrsPuTf+JP7up4EuN/2a8x0mfMmJzTR+8nar/9S5g4zKN63RW72a47N0uvPGD5qWxjM86ig9i3BcsLlW9g9Fw7sW8JmDfRnjSK/52aV97w9ezrChhdnCl+46wY7t0VlOmJiKIxMhGuuPCI8DHokSpubx73jrICxtFZ4ohSO/Pxu+lzmzhzie845ognTmczud885mL7UP+VsvL2nR7Tsmqj7ystMAeIr2J3b1mN4bso39Z3mm7Gq9QRmTrFZSb2SFPfykReaj9wus/9k6AvULM0wExMumfNF9+0eT5CSqSP9Kicy/SxjhH79BLjRQmmsleUKLtIT96JX5hVn7I6Tn6dLq+6u4NXdfcvUt1iDStzPr29X+JqbPT2FrF3op/LHVQv3y8yLaVeXOAdzrzrVLe/65jy971PszWmDZhoJWXPxfnmr35/BcpjlY0x912M2GerP6PgxE7NJ+8SKc/DmPFRnnsnPcJV0ZJrilG/MOzhJMTVMbxDeD1uq/Ar9FsE+Wj5jpP75Tlk3RU1HmdPc79EajzxXr8=
*/