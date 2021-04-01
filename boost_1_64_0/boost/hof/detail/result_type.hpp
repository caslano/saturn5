/*=============================================================================
    Copyright (c) 2016 Paul Fultz II
    result_type.hpp
    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_HOF_GUARD_RESULT_TYPE_HPP
#define BOOST_HOF_GUARD_RESULT_TYPE_HPP

#include <boost/hof/detail/holder.hpp>
#include <utility>

namespace boost { namespace hof { namespace detail {

template<class F, class=void>
struct function_result_type
{};

template<class F>
struct function_result_type<F, typename holder<
    typename F::result_type
>::type>
{
    typedef typename F::result_type result_type;
};

template<class F, class G, class=void>
struct compose_function_result_type
: function_result_type<F>
{};

template<class F, class G>
struct compose_function_result_type<F, G, typename holder<
    decltype(std::declval<F>()(std::declval<typename G::result_type>()))
>::type>
{
    typedef decltype(std::declval<F>()(std::declval<typename G::result_type>())) result_type;
};

}}} // namespace boost::hof

#endif

/* result_type.hpp
QBy8QCPVSxxOO5Z+YFIInQbKtuFnEvkS16tTC8Z5tJC5AnBYyAqs72Bit81ZGuDakLPF+LpoD1boYJ2amLOHhaXbkRcxzP+YbMv8DSmcaolGpmx1JF6x3lnYPuRr5Q2V60gCjHd9qvqOQjtCmXrWdMovV4g1VkEcgHq9QRnyYLHmjAhyGl4u8cLsYNPHCe/iK9E1bIP3qQsK1AayjGC0mQUT3NYvpuXIeDIZdHjkhD+1CEGDl6F8bduzRsWQdUy2RamsHyYuc7aL6ALXHFLJ0iHQG2lnDW0PRzk+Fw1nSdU3p7mR61RKzb1Y8PuKXLY6QwbPrOnr46YR55YNQkavvUnqLcIOmbYywLfKY/qqHZHvX1E+dUQuHNQdyyWoFxlFhbDzHyt1THU/UXG+aClBOUr7k9XyI+rBXscKShU9UDoCgkzi71Kdubj5qR9O9aMNjZeN1RnemL93lcJuhlQ5nk45m8v9MQx5bGQ9gfxLElpGbcyV0UPCjtNo/tkLiG1fbus61Qdn5UITWjYzd8mR+csx+Mms8CqVMfXmyH1NrQX+EGh5SuX1JKYGjw==
*/