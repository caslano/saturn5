//
// high_resolution_timer.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_HIGH_RESOLUTION_TIMER_HPP
#define BOOST_ASIO_HIGH_RESOLUTION_TIMER_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>

#if defined(BOOST_ASIO_HAS_CHRONO) || defined(GENERATING_DOCUMENTATION)

#include <boost/asio/basic_waitable_timer.hpp>
#include <boost/asio/detail/chrono.hpp>

namespace boost {
namespace asio {

/// Typedef for a timer based on the high resolution clock.
/**
 * This typedef uses the C++11 @c &lt;chrono&gt; standard library facility, if
 * available. Otherwise, it may use the Boost.Chrono library. To explicitly
 * utilise Boost.Chrono, use the basic_waitable_timer template directly:
 * @code
 * typedef basic_waitable_timer<boost::chrono::high_resolution_clock> timer;
 * @endcode
 */
typedef basic_waitable_timer<
    chrono::high_resolution_clock>
  high_resolution_timer;

} // namespace asio
} // namespace boost

#endif // defined(BOOST_ASIO_HAS_CHRONO) || defined(GENERATING_DOCUMENTATION)

#endif // BOOST_ASIO_HIGH_RESOLUTION_TIMER_HPP

/* high_resolution_timer.hpp
qrdbRq5S0QhTtWEmky+KSnCU9FpCYjU1yAVWMe3MMh1EApQvrWH1trjMltKFaDGLw2YuuqqISW2ifITiOJrhkLfnQ7EopbxK8iWcOntBSDH5HiwNdLlqd9WrE/MJo9vdyweQ8W3GJeC4mR9aFbuMeWWofw9L9zIK4V/5h/BNXb33XnnBfDIVTP5HUn7sxzI8R/GRH105ofqc+/GF5fIV/972ZYmZ2vbPKe/sPRcubxcxH33tpZU38pPS+eY4nc9jxDzed2nllbuOXKS89xDzjP7PKe/cvRPTq/+0C9OV3G5LgKE4pi5XXKLchPBgqCEiQr5/Lk6bjnlWhLpHxi3X1sY2v68nqDvcRFpn8Cl6KZ7znK1O30EXZ3DXImT5ISbP7Ya627aKPDYHt5MU0be0tLf5iUwXpwVKpie6rxsnWXqC3Q4/VdDvJIs4T07pW91y+ERlY73OqLj64FeImwTyFA9t3RzB9/+LcZw9LPLllr1PfKUrg4TEYHRKoPwWov+a6IOrWNxQ3uX5/TniZSMo3nlPSSmeyvZFxGenaLWp6LmdTTksF1mcskXcal42LgRU3M4mWd8nCJSbjFN/kD8IXzRODtnjGeyI+MKddZE8cuBxkYrL7c4n7Z06p1MCouOEewSnXVN9UfqwsKJnqb4UhxcjEtwKt1VbqDXYHSE3oS1PVbPjVDUejwRac+IL+6YS5vyQ4BpY3ZME59tjqHE+z1vReRpBFz7ejUlsKihOXab4dle54rxwW17YstUrqic4nQ8W5/PBEXYRlUe01zTq+BY7vb5LdBwt1oXzSMWTQ8LHgk6jeDo6AL9Mxv5mHdGLZ7+pmoo+JJelrhSoiy5qxf0XeH87YcDxZEKaXuG1/U3C+YLMCsKpRB9EJreNLTeMbRcX0IWpaZxvfbSWsbEfRBl4gVQ4HXTSUtq/CSkicbeMzRcOFBP7Q9pgKn8YOnkn+tHl35I08Xo0xYunfSmO7WFMuVGFn6qAF+LVwICH7/qmTR3GI5tDnU/554Z2Wj4pXiHQXSQxVM4+FHS74WIfK3sMmwO7Cczva7A3GThfdHFMfSGaDOhC82XOSIu/iOgbmi/ZvMYmMVw93VvCPcEAZ2noFSiM0D6hZwb2PThLCoyvxSEm3K3Qn6DXN4h/9MfrNgYBISMQgsepFo0TQnUN+oZrdRPb/my/3jfYr5W5vHX1DY2r16xtWudr8duvA2khjKV0dtE82Onv3h5CjYkfCG72iDfiiU0XfY9bhzVbA6zLXwhZP7F9CPUj80LJS2YEO7O1YSV8wUZcEOCa1aNQNezRCvC4SetXW8DS9e9o83v87UFftyPe1dm+Xcm3+AKenu2h4Pn9oTeudLaf9nO+zu1sYcDK5Vy6OJWvQcRcrS9bq4tHkMiEnsIgX4UL6/UyelNeO6AYtfAjrZDaUZscYntZfYb4kz5KhPhbqXnE1RLc1NZplSfjMykMdgb0SxhffHN1VewS/J6UTiwsLjOdwbe1wh/Lu17R7SGYYP7Ct70qdon1GtrZn4YX91L8v+K9ibr6HXhfXTx7QtoJXPx8Cz+XcPrpdP6C9k9KZjqFdz5Pnoe4dSk7H7at3PkKSkf58utuohdqS58fWvTChew8GtWXQp34/Lzi6EXqcx+VO8rK055B53t6ZX5vJDKXqyE5Va8jZeRqmdybysg1kZw698Kv5u3u9ujbJ+Zf7qXzOcX9MP75Gy7FD1G543vnuM/vbC97foXSTaz/Xl2mvb0kd4bOQb2mjFyO5JR+vJ7or2ByB0nuoZVS7nCZ/A6T3FaPlHvtBOVeN0E5fo081f2coFfE/4HxOkrlafvkeFWxcfkE8WsNdv7paWXsgeVbzfg=
*/