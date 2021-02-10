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
5X9SIU2R9RW11vIzFTxfe621ugzOV6FpcNnawXFWv2JRm0Ym5jRI3dTEXMTjE3PjtXBqT22FijdNTG4IIOv6a5TQqdv3YmpCA33HAKHvTeY6kDvN6B3FV5Xw+QeCHvGsFWnMPkhWBmYuRz/JmpGeA1NlkSaxSIZ7s+nb87dzdpK4mB7mEJ6Fm3g4GqnBKqHlxncPO7NRQslMrrdpQAYLSN+uy0nwv12XQ+plo9flFC9VacDeLSD9Me5dqWsVACyP5Af8nVoGgYBVuCSlgrv54PeeBx0A/IQiD/g1tILn0d7yAv52KsY1vmyLiam17NdKDgnWx0EPnjwrCcyby5utO3tIqbFvf1gyIo87Lq+Xu5uOYVkksHTQ1y+4dbV3IwmuGNJgw4PcKIqOyQHPf+hS0Yqbl4v4pZ7gevv49LrqJoegiPdVDEPNS7AbGQYIszU1BDusr4L98CN+ocQ+/Fdkf7iCPqv7suBBRqAA91UMAqe4PCx1lEGIL3xvZgR2WF8F+8kxpAJC6Q30yvU6Gl5gmhzZIt5XMbr/4QUmCeA1MAAFpG8JPwc99RKzmhj7qLGxj76NfZGwhpK96MGpn8PVfPHwp/8PUEsDBAoAAAAIAC1nSlKagyAUJgsAAP0mAAAoAAkAY3VybC1tYXN0
*/