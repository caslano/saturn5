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
O4Yps2AdEf/Z2asibsAy1W9l8NRVc7qm3rAxxm5+kbyc3n565Rt27bOvdGk58V52NH8k/ZNxmIcvT0v53tfld1r0K/lbv6pYKnS/Y0ze0P5wDTNNMMj9Mb+B48lIiu301jAm01CZJi5U4QHLwYo5K4rija6s4yjRX8qMjHPw+zjd1udKUHkxbcJeDyT/Sl14l92QdtVkTx4PzSvb55IIF4xYkI+dlc8l8WO4O+EbtLJw4sBvMlUpPKMIh4hhgVxI9t+hl6vf8NzrallQiw32KUIsPysIUiClkZyvsKAPpdBBueO08gQuBDXvF1b1hmN4gJ76aTTbVRltVufNdtwc2KCHmb8668m1LTKTW1tbOo8ic2vUhy7bKK5Nftqh+kJfBikP19/2BA56WbeqnTxGNLpBL9yk2e1ZEt3Gk7w87hfuS6mFrTaOil7SavZopKUSSvd18QdU4wFfnPncWL2Ip7fyW/n+dDODs9NSNudiciL+XOky1O/2zjuxTg/zG3o/PR80lnT4gvq5fP8CVCABb1svmfXDZ+u94ozAquMMZMU3KrKjqReB4+CBJ+42AW6Ysxo1qCQvSoin2Lj03H16oaUOO/ZX5Jn04KyQHkcIkBi5BLwTwIcyZD5lY8k2Ct4N4IwCUvEuG7GDqe6s38aX4yY1YD3m/2JlSvadYYi1LFgFs1g94TWzJdho1ufIobooke5vb3LlcmDuZIXN
*/