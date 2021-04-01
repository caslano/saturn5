/*=============================================================================
    Copyright (c) 2016 Paul Fultz II
    function_param_limit.hpp
    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_HOF_GUARD_FUNCTION_PARAM_LIMIT_HPP
#define BOOST_HOF_GUARD_FUNCTION_PARAM_LIMIT_HPP

/// function_param_limit
/// ====================
/// 
/// Description
/// -----------
/// 
/// The `function_param_limit` metafunction retrieves the maximum number of
/// parameters for a function. For function pointers it returns the number of
/// parameters. Everything else, it returns `SIZE_MAX`, but this can be
/// changed by annotating the function with the [`limit`](limit) decorator.
/// 
/// This is a type trait that inherits from `std::integral_constant`.
/// 
/// Synopsis
/// --------
/// 
///     template<class F>
///     struct function_param_limit
///     : std::integral_constant<std::size_t, ...>
///     {};
/// 
/// See Also
/// --------
/// 
/// * [Partial function evaluation](<Partial function evaluation>)
/// * [limit](limit)
/// 

#include <boost/hof/detail/holder.hpp>
#include <type_traits>
#include <cstdint>

namespace boost { namespace hof {

template<class F, class=void>
struct function_param_limit
: std::integral_constant<std::size_t, SIZE_MAX>
{};

template<class F>
struct function_param_limit<F, typename detail::holder<typename F::fit_function_param_limit>::type>
: F::fit_function_param_limit
{};

}} // namespace boost::hof

#endif

/* function_param_limit.hpp
+A/F0RHcaWOO8+UT+Ya8HSwC3QPBM2OGJg6S4e9ahMVaf2b+EU8fhgNBNERsURZC80rI87BVwDpngZXotkJFCTZ5zQYAjLMqcGFv2R9zmS0wyXOntLbna2PChZp7Ms34pgUEszRGMUQH96Dmef/7ckPto1eZLI8hrj7KBMMmpxfX7KeLbKKcxZrpIAs4bILk7LQJ9MjSUyyX4Jv0HP0YVDV/2+vyy5LRU6+5ggBybKrGmBKjb2BUtp21rOjaaDgegg53FLujjgP5NIL9lPU0pmQm5hj+ManI4k+QJVl/RxefZD2Qe7ZUnyxISGtDyVlhhBGTV0l0aoNEFxiMqxNW3k4FRumiwWjGXy1ipNflDzqBrkg/ydwr5J4QzlGMnOQ2NMpEJiW56MpgDh9JYUvo3matR19lX7OUeHMMVYanVt4J5uU7wRi20FC6yOVtpVYvph13zNafMhahJak4T7DAN0I2mww4IZEHRZYRdzI90/TUCc1E5hECZpOKselfvKhFwsu7s5+fLXGMJgfpecLvoClmuFQ55wi6tKKcE+37eAig9fFhJrGJpN9ftA==
*/