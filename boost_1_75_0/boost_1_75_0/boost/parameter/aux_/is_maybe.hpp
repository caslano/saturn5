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
S0ljcwJ7TZ8zEzHFM5ebcWyPtG1xKPgitP9628ZmQOjd13WBJo1h3IsDqseRnyLGeU00tClsx4+3M/WcZwrvZCto8XmCPM5p6BDjc4FF4kgLEo1eanH8D4du9/57unR5UOzFzdi7tQwV1vguE0a9N4W2zTsph3WbNJ3odX1UiTSuVPa5cqKyfA6589j+4UbJUPj+Cv4v+npENRUlO/Fs/nifHXRndZ5qkwkQOtlzrRzEFtVZ/4CMuYlC/KGq68cTCfAeWFVzKhWvMve9VHGj1EcBtGrdPEv/PC5n69ukhiZDQTwTfrXTlTCAHp7pRw8HXinEJoyT1oXnth37kVfJnzVdzoPVuyTqEW+E74XtxNiuTf2ZiIWC3zICronPCddfJdx31c/k2acoNk2dzvWGEn3xn8uPMw0Dh0wyS/Nj5oVRTWHX/ea64DAPmKsHkPoz7HQYV9e3vT4NJuXAgVwwXVnIaVVq508Xva+N6rSt9aKBD+ovu4n97uLdyGXn2MUicOBDlx6e7BeXu+Qd1jlXDypM8uQa31B6PxislIqTNZFnlhuIgkcOGnUHNeU6r8GIUSpwa+jX1pYisYZJQbcyOBbb+UX3736TzQ61VZzuoX6QOVdURw9aVAf4ZdQjGJ0EHjT0dpU8F91N7o7mOcIM2y3Ph64ftL0R1qr/RB3V0ZJetzp9dR78xNwKIf7TTSukzXw0HMvk8grYvlMo
*/