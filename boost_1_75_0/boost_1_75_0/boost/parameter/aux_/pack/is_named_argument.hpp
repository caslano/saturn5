// Copyright David Abrahams, Daniel Wallin 2003.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PARAMETER_AUX_PACK_IS_NAMED_ARGUMENT_HPP
#define BOOST_PARAMETER_AUX_PACK_IS_NAMED_ARGUMENT_HPP

#include <boost/parameter/aux_/template_keyword.hpp>
#include <boost/parameter/aux_/is_tagged_argument.hpp>
#include <boost/parameter/config.hpp>

#if defined(BOOST_PARAMETER_CAN_USE_MP11)
#include <boost/mp11/integral.hpp>
#include <boost/mp11/utility.hpp>
#else
#include <boost/mpl/bool.hpp>
#include <boost/mpl/if.hpp>
#endif

namespace boost { namespace parameter { namespace aux {

    template <typename T>
#if defined(BOOST_PARAMETER_CAN_USE_MP11)
    using is_named_argument = ::boost::mp11::mp_if<
        ::boost::parameter::aux::is_template_keyword<T>
      , ::boost::mp11::mp_true
      , ::boost::parameter::aux::is_tagged_argument_mp11<T>
    >;
#else
    struct is_named_argument
      : ::boost::mpl::if_<
            ::boost::parameter::aux::is_template_keyword<T>
          , ::boost::mpl::true_
          , ::boost::parameter::aux::is_tagged_argument<T>
        >::type
    {
    };
#endif
}}} // namespace boost::parameter::aux

#endif  // include guard


/* is_named_argument.hpp
PeDoXEVrRK3+FbGEu9iYGpWcmCpLkrAciw+0KAnDdMX9R7vC33S6xWRM2oIaj/pvOi3XKZwkXL9Xa+fdc8dF7WZC9B2h1EfbJ/iTctVv0vkbpGLCqlZKeblMa48hOWiBK93/eELvKHiPkUsnT9eVjc+VO4NSgIw1kW8U0z1ON1bxvBcfJrrbEO2A+qm3ZH5NNTfBwpEkPrQxoVd2wG/w+MPPRmkxa1HzTdU9xjpA/bxNXm6LT9PC+4DCG4ktgPAgCCUTZfax3n2bvALznzStvN5y6n74FYEYsvrhCyu8KcQ2wRQjdC4YAbzJCJd4bMtCAxREC6htS+ixTh0gmCVv4Yi9xu2zYtLDf7o01rYYIbRd5AdfWC0ys6AI3LtBop6vZlYZCpR1xAHfIj498iPOPB/wiBCImNWOOIPro8D4ChTEAfwqsu91l+gk4nlfi+8B1LWdi4aw1Tzr3a1HIBa937bwNbQ6tdE3+OHu9ceOXiCC/xrVy+CQEFS8/yXTdP9l6pmyg5WNq6fNvyU1lZ63uG9LKpvEgV3ecHIj1aSP88SCYdv+eFNZsH/+QyQjleZYIXfG6MKfRe3tu9JEgE0f47AzGZIkPVU63fTHHgqj0e4fFO8YVDbmKtjZwSnqmC6ofOXscwTtZhiM1o+FgXZy1dE2tTn1tNfus762V5uBM2LJgUcFPL5HrGamT7dyHECwSo46RJ28t6C+JK6E
*/