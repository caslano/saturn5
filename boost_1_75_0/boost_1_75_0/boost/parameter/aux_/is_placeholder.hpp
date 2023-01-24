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
2U5FKyxoyFPRX3MaZQHl82ft+lO6pHoKsRsYPbW+5fQHmSj4B+ESo1lAwNZmQ8zHbP4xXePrFhuW9qzVmiwQHeBecRQYM9XnsxrDwjfZ9rrUAaCxQLU1MNysRRwQmnAuTfwSVwj0Ia8p9eNyjnKMMYmh5q2AkJH2pB3w09CZFJPlIzKtbdBnuhttSZHq9cohhtUrkxAnD7OQztendxtm0kt3V3IINGUiBMMFGldg2Xv7dsvAE0exIGHbznuXcA+Pn9liLk/H48PeyHtot+MGNEDE6npG2hMCLnlp7L5eO+qLqMmRO+Y/ag+fSFIMfhKesYS0uDuyTMsOupvtnwxInYGCuLxxPYYBxHxwjeAf+LuhymWlWISaVZB9IL+YhIyE+lk2q0yW/3OJhc26Qskn0HA6GopwRDOExpcsZFGGilB/C8/Alb6BHzcYl2+HGmbog8u7s8zQd+OZCM0ccmsKxPYOiWn1sEl/3RFIiNoz9kXwzptSz6e9E7X03Qo2GHWMTtMj2waLD9BAKBR8ZLzzz673F0WUgtqvB+maPkrp+Dfdcp5F4cnpXHz7MT4eLaPd2xWpcoqYCVo+0HQ5jZ+qmWoJU1068ULfEAo5TxoOznhE9PKTn4SHIhB9WxdQphb5jWNDSKPEDEXnUssq9LVoPlJELaCoHoCw/XFnY06KWFvrvbWzdVXgJ6HDb+Hr44ymldMtQMGkEePTG+9n
*/