//
// Copyright 2017-2019 Peter Dimov.
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
#ifndef BOOST_GIL_DETAIL_TYPE_TRAITS_HPP
#define BOOST_GIL_DETAIL_TYPE_TRAITS_HPP

#include <boost/config.hpp>

#include <type_traits>

namespace boost { namespace gil { namespace detail {

#if defined(BOOST_LIBSTDCXX_VERSION) && BOOST_LIBSTDCXX_VERSION < 50100

template<class T>
struct is_trivially_default_constructible
    : std::integral_constant
    <
        bool,
        std::is_default_constructible<T>::value &&
        std::has_trivial_default_constructor<T>::value
    >
{};

#else

using std::is_trivially_default_constructible;

#endif

using std::is_trivially_destructible;

}}} //namespace boost::gil::detail

#endif

/* type_traits.hpp
aIw1WRVm8XuG9cd4Ckvr2cZesyhh3atuvIMxE1bv4antmqWT2TFr13nhJM1yhV3KmX5cM0NDvb2Yd36IZg7CvDPPDMS4kDkyezrnwRHELszH5ckexC5s3b7bPohdmMu9G16InYzH3tqp4xXELmxJ90//Rk2Q8VpaW+5ke8Turrcl/W6gL0YyXksJu+0cNHMTtvuFxyjUBBmvparTz0zHuAhb0/qoI+YfmT2zf2rcydIsTNiQfiuOYczIeF2/fXG/hWZxwrJ3p3bDGUXEUGbGuSWYY8Ic69x7g/EkMzL7T+b2DMyxRnprvCb9IOYYGY+hzs2JizXzFPZzfOn7GDOyqszSB06KQi0JO1/R9wbGhcyBWZhT1grUkrBXfXc9Qy2RVeY1/0OZhYhd3O+n2KWBqJfGejtWsMMWc4WMj6f1tMP/auZNxu93dnZYOc2ChV12HTxDswgyntvjtQ8gD7FktszCI+Zs1ixR2Mb0gHTETsbnX7l7Fd8jdmH9r2y+gNib6MfTZsy9HYhdWN8hPWKQW7KazJ7dWNocNS/si8Pfd0R8ZE7MKvx6/DT2DmH7Hp46ixjIyjP7JcGAmjd46Mel/4DjGGsHYYFWLoWIj4znNrrSIMTuLaxfTst7mO9kvF4WNtttjT1VWLdTx3sidmFlSzlfxZwWdibfZ6Nm2WRVmKU+6Ik5Zmiqtyl7Pr+DeUvmyPNQ9ZcUrHXCnvXemYr4hPUr//d0xCfs8cA/pyA+0Zc7btGzEZ+wIZPWTkR8ZEZms/yPoCYKhKVeeNIVtdtM35dhGdP6IbfCspZPHoraJbNn9vTrMT9g3grrlt+mGmIX15x9weYxYheWvMrqJmIX16xdN7o31mthqw8c/wM1T1aNmb1z6ArE3lxvGZcd/kTsZHwebXL60k0zf2F1uw9yQXxkvOZPrfcehPMgGc9fzvR+q7EuCfN9UqIq4iPj8bXv69sP8ZE5MLu5udQqxNdCb4tjV/yL+Mj4Nd9ubVcJ81a0qzNgQgZyK+yzgW+R9wgynr+BT5cWYi8m42MW12bzd1h3yWoy8xv/YBJql4yPy/igBruwLrXUX7OKb847zE0y3pd7MRcWYm5qhjPfAU/kj4zn7+nZb08gf2TVme37Y+Ui5E+YvZv1KeSPrCqz5z+MOoj4xP2qj509Eflrpb/moFHjWyJ/wt4tfzkVc5OM369a+9UWODOQGZmFXUssQP7IeG473J6civwJ659zo/h5hYzX0ogHi4rXXXG/4YvWL0bs4pp1j/Q5hNy21pt30smXOC+R8fvN3LflIWInq8WsabVlAdhThU2oX3cc1h6yGsz6PJqci/iEVbx69QrmHxkf68Ul/Ncjf556u9z05S7kj4zn7+XznfcQg7C4kxaZyJ+wnzOqvMWZT9jbnMQ0nPnIeAz7Wl1MQX0Ke1R69gvNDG30MbgZ3uJc7kxWmVmDEWXmYP6RVec2coYt5p9o98n4jFuYf2TlmfX94WE9xEdWltmQnoOvI39ktsxcHh7ojLkprH7u+VisPeJ+Hu9sBqN2yeowq/n8n2ofrLHBqm2xVTA0NewcavXHB2tk8CCLKvnhHURFQ5BhWkB9g2be7fF+sMjaH3t2QDN/MhtmK/deuqtZMFmZIvMosqmuecc1CyErx9ql/hLxH83ChT0pSGivWZToywLrZu0020Bmye5Xtc0rO83iRLtX82N3aLZftOv0ouM2zZLJKrF2R/++XEmzTLIKzAZe3eqqWS6ZkdntcXufa2boYDDYMbu6fnqAZg5k5ZkNXvrTDM3cyBx5u8YjHyFHZDwPcYe2jUaOyHjsd+v9exg5EvfbfTx7vmZhZKXZuLy1neuNHJHZsnbL0wI=
*/