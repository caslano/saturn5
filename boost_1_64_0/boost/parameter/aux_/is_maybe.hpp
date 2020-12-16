// Copyright Daniel Wallin, David Abrahams 2010.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PARAMETER_IS_MAYBE_050329_HPP
#define BOOST_PARAMETER_IS_MAYBE_050329_HPP

namespace boost { namespace parameter { namespace aux {

    struct maybe_base
    {
    };
}}} // namespace boost::parameter::aux

#if defined(BOOST_PARAMETER_CAN_USE_MP11)
#include <type_traits>

namespace boost { namespace parameter { namespace aux {

    template <typename T>
    using is_maybe = ::std::is_base_of<
        ::boost::parameter::aux::maybe_base
      , typename ::std::remove_const<T>::type
    >;
}}} // namespace boost::parameter::aux

#else   // !defined(BOOST_PARAMETER_CAN_USE_MP11)
#include <boost/mpl/bool.hpp>
#include <boost/mpl/if.hpp>
#include <boost/type_traits/is_base_of.hpp>
#include <boost/type_traits/remove_const.hpp>

namespace boost { namespace parameter { namespace aux {

    template <typename T>
    struct is_maybe
      : ::boost::mpl::if_<
            ::boost::is_base_of<
                ::boost::parameter::aux::maybe_base
              , typename ::boost::remove_const<T>::type
            >
          , ::boost::mpl::true_
          , ::boost::mpl::false_
        >::type
    {
    };
}}} // namespace boost::parameter::aux

#endif  // BOOST_PARAMETER_CAN_USE_MP11
#endif  // include guard


/* is_maybe.hpp
asuV+FwvV/zq5TqNyJP8/7hyfW3Bf6dcj5EHeYWD/fdGpVwjbJfKNc2ampw1QRlxOL2WDFP+m5uPx22ul6n4veI6ECj9+Ci1vxd3abUpl9p6eV7kOH65incbXE0ZVciitTZSRqGOtrfwUhmlpyVn2OwntUv9UfFC18sEv/qcg7ZOfTX56Qt9anvr/XSpzDk4tn/9k8ridGPzsqi4oizUiehSWVRcRVlUGMriJOWwpvHvl8Vvf3BZ6O+XkJd6XCcR9ZeysGRXKYsJabMyEmzzspIHpc/KzEqzpc7lVt78GqXekaLCdyTN+mblRfyulxd+zc4nPa0QtT/MQunp55Ib5bXPhfmgqymz7lJmEUHmZRZtKLN5WfOTs6spn5jfKZ/oqyif6N8pnzn/pfJxnF9lTe0RFMp6581SPr6L9PIZGhmdkMW4x5acle10Pq2J8v8g8/OeZmVEfK6XkdHvV+qI0zL4p48F+6v989X+yWp/UqoqQ+kbmqr9G9hf27ScA2GI8rOeoa2bfl+6jTJ+Ch3RSiZAlbkq+29J412/358zJj2/DSpeS3JG0tXVh+OdJhtD7BEuFnu2RY55zkvtddiQy2rE+djjIxWmCdtO5jjN261ejo+r/V1ojbVN68kYvg8BOOxEakLvo4+q/ZH6+PgNte1hqJOMNIpJz++zan9zS4CqN9z0MO5O5xu+U/sDLbVwCZa2uE25zWXbwzKEPZNQM+pYK889HOcu5Gao31oBf8Sc65XnVtQ18ruxMoYc4Ribz9PrckxCTnRWpi0zMTO9mrG58j+Y42lrPjaf5/q5hV99DFmgtTXy6M7x+7jX9vb0HsrI0bMOI0ePuj4+nrx9yJv09euQB/7aNLIY5i1mZs7LSNLHkNepuAcQN+81V7Wi13Pygrj5NNa0zAxD3U1R/gMs9Si1YN0vzTo1M8ngXZ9TiVL+G6i+9s+or4vNzOurzHapvtIyfr++jtmqr6+yqxif4levr2jqqrjZH1dfH9qurr5+sl1dfZ22/Tn15ejbw8JUeP2dID2kvvIvnV/aY2llUO7sOfBjym8z03rKNz+v9ONbo/Z3Nq03CauPEa/z++P6b+3Z+XmO80yU49l5pjpM3oiUbasydxPZwp7AOBk/j3X075fuY6Oz0uYzbzM6eaFZXyJtpbHyP1z1l6b9+1Xcx+K32nuuYLV/mKU5Z2Efwz1XbdqzZ8AfO7Z2tKVpLe0RdJCI2jva0qVzXz/xnbWlNcpvC/O2dBXnfL7tz207P3BcffW2Y5XDUq3nsrFIeit7Au0kobZSJrmX2s6E5CxO/JEZKZnqTtS1udHcq2gr+K12vHy72t9M3Z87yqtOwB9XXsZ3oK1vbX4vUZyll4fJnZfz+4qSrGrvK4jX9XLCb7Xl9FbWf/e+4kwbJ/OSl+7bb0zOSktZKHMYTsc+C39nXvIq7uXxq/elG6nLwjZ/3PzZ4IX/nfmzyHZO5iVzqparPh9iPi+Z8zvzklcx34tfvVwrKdOLbf+4cn3tvzTfm97efCxRMa9KuY7JTEq2OB9PnK1mPFHxO+OJk9WMJyr+xPGEZqd3Qbuu63Z681MWymDC2B/kSufYWxLphT4jXEGuvYxsWeliwScDEhf7A8Lr5fJxiP6szLQcjH7FPi2JaPXnPYVqfwfODXdLQ0N5ef2HfQL5uuzZWFfH+djJHkGqRDQLfY3fM/YyScrUXk+Zley0vVTmOn1OLHGwV28vQwalqG7WrGzM/VvV0wnzd/eKfxn3q/aomrhkWYXxNYTxNYSpcr7q/Yzbcnsb5nyVds3suXJreMU5X815PMpZfQQa26+hPAKNz/oNxx2Mu6/8pnjjKsd32Zy7/AjuUMk=
*/