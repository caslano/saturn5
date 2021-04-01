// Copyright Cromwell D. Enage 2019.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PARAMETER_AUX_IS_PLACEHOLDER_HPP
#define BOOST_PARAMETER_AUX_IS_PLACEHOLDER_HPP

#include <boost/parameter/config.hpp>

#if defined(BOOST_PARAMETER_CAN_USE_MP11)
#include <boost/mp11/integral.hpp>
#else
#include <boost/mpl/bool.hpp>
#endif

namespace boost { namespace parameter { namespace aux {

    template <typename T>
    struct is_mpl_placeholder
#if defined(BOOST_PARAMETER_CAN_USE_MP11)
      : ::boost::mp11::mp_false
#else
      : ::boost::mpl::false_
#endif
    {
    };
}}} // namespace boost::parameter::aux

#include <boost/mpl/arg_fwd.hpp>

namespace boost { namespace parameter { namespace aux {

    template <int I>
    struct is_mpl_placeholder< ::boost::mpl::arg<I> >
#if defined(BOOST_PARAMETER_CAN_USE_MP11)
      : ::boost::mp11::mp_true
#else
      : ::boost::mpl::true_
#endif
    {
    };
}}} // namespace boost::parameter::aux

#if defined(BOOST_PARAMETER_CAN_USE_MP11)
#include <boost/mp11/bind.hpp>

namespace boost { namespace parameter { namespace aux {

    template <typename T>
    struct is_mp11_placeholder : ::boost::mp11::mp_false
    {
    };

    template < ::std::size_t I>
    struct is_mp11_placeholder< ::boost::mp11::mp_arg<I> >
      : ::boost::mp11::mp_true
    {
    };
}}} // namespace boost::parameter::aux

#endif  // BOOST_PARAMETER_CAN_USE_MP11
#endif  // include guard


/* is_placeholder.hpp
ZEl/OhbqNxBYrC2B4p1N+HjexMeRmXtP4TKpK+VP/qCUHC9yLzfAW737bZDFdcJlCQv7thmqfagngSnkcExdKqpYNrW5/bRTcw3TqLPqmOFn7xEy6eOuoCvceXZKPaeVh6gDRiCFX81zbSMvyNW3mL26peC2XBHQ8OWxMFgryBfNmyDPbE58jloJ66bRJVyw0/tL8l3wtlk5Wh7+EUCE+qJt8GfJFlRLjGv+toUfcpfuofaC2ZwHwtrC43WhB+VdubJ+Gt4CcIKGYj/ZHVdTU+9L4wdd5q6jHxN8OKHDwrcb1LjHJyFzsFEjZbEFxAu1JuLKNyHJK1hWHNWWeGxjxsrtzIduD8sWnjZD5LCJhKYp4J3mBTSBD63CGa+TKVgWMxB52cI0PC9+26n/PwkQoG27Foh2LncnGjCkzlqYkyKFPdKO5hnJzPftHQ96Iz+unOhAdILqrIWBgUsKKtflisIfYZM3dcA3r59bAcLIJhvmBat2FyT7C9Pgfa2QaKxPOeqBkohC7gfD5svH/JaAZAKcPjjR15VqwN2HZSOCdJy0dP+poAKQJww/4w==
*/