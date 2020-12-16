/*=============================================================================
    Copyright (c) 2012 Nathan Ridge

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#ifndef BOOST_FUSION_SUPPORT_AS_CONST_HPP
#define BOOST_FUSION_SUPPORT_AS_CONST_HPP

#include <boost/config.hpp>
#include <boost/fusion/support/config.hpp>

namespace boost { namespace fusion { namespace extension
{
    // A customization point that allows certain wrappers around
    // Fusion sequence elements (e.g. adt_attribute_proxy) to be
    // unwrapped in contexts where the element only needs to be
    // read. The library wraps accesses to Fusion elements in
    // such contexts with calls to this function. Users can
    // specialize this function for their own wrappers.
    template <typename T>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline const T& as_const(const T& obj) BOOST_NOEXCEPT
    {
        return obj;
    }

}}}

#endif

/* as_const.hpp
HMHpaxwli6i5XcD9S5cmu+WM87YszqI0yJNmV0vWAegcqjdIcykLXjSxJwKqr8Lz+xXSXyErCpWInMdMq6iS4UaPb/Dwrt1cPslUkVSijnijdpVWOWRjqLj4ihVJHBelDJi5uRFrw3XU7WJ9tsi6Bk2exsIc2WHGJZKEa7vLsyDKOghKHjRNoJ1ceu/PHrzVi9MSJVWu8q76Lg/WZYHyiCCuihSkYXS60SsSnnuZuBdfvKB5oOSqnW7gqZKOftG8Lfg8vFs7vOHRu1ASmMZfMI1mGuiSwFgVz9706CSexccAc7XB0BbsUA/s4niMOgwOWAR1fgB/fWyqj2i+/xy+09TpfP6LAa0jqDOsPdEE+tq25R9Nd3SsH7Bb+m88Oo0FsThj6KRe1O7tq5MwkAzxtb5vEobGEXgrYmxL9H1x3mo/wWBW6P9mAr0fI+APDUb7YyfthvSXHkC60y5YTnj7g3RaHzeGGmJoWdxysFmNAf/ee5Tjq4TulyM+hPQ9y3EFMV450D+OvIXGNMq5s66PLbXWvRnVdzGNumns2n2deV5PH5bWvFBh1r1LMo+RXDUVrr8jlzcqWRoGecBv+KnBVN6thaQsKctTGedZXTHTricfA0138pHt0yj4I1a0hcw2/C0/+Sgz7eK+2U1roS7iIsiLGG+DH9l/L3wN8ESfC/NnLdKItVsPbm5/O8Yo7+Z3wpcwWKLqKKoVa/v6ZhTZlvnwulvmJCtlJgFR9so8j/E5XfxjYh1nVtU165d1HnW663TNg5VLpmmad/G8LSNds1OX79GqklAwwZob0mN97BmCrfIqFVXZYo8Dlp7fXKxkdVZHZVIo1l21Q+LeurXb4ykKnmYqQZ7jE3he6/JULKmCMlepYOc2h+chYv6aU+X7591Zb52e3YoyhGGRlKztyqyCMIcQ0mteK6Hmm+HIF/mp00QW0a6p1+6qLONUFilLl8dwR4tbDS0npvCLHe/V9Z6dGw9KWQimPfK0RTE2sDrnlhl5/9LLN9W8kQKJgkV+j3w72fqXy/uoMIsTmRU51P6FwIHwqQvot+CC2+9xVccyKUrWtRO1ObjQs/0EQeSVjJk+SnY5/JcKos0ASSfQ93a5iKKcnW7uwM12DCo3t9uVd6cbC8rlrViUyFolkh078T/yfDbJM2LaPKYI0oItGlOc+WZL5+a6g7YxNE8hsjRPRcHCyMsUy6t90D33jnvP43dz3nr/fLCy2d3nbWxb2uUB0NCfC40XdP9pl0bPYJca2oRLwimLiWc8zHDDYPC9d4PpXYw5a5faZ+h4TjblNt/JhZOTLjvg0vEAinUDv+GW3j5ZQN5Xz7o0fK6A9PgQ0rd3dYlHY9LeZ26h6XippRO35b4loWHi+M78VoYOzQBJt63i0O94a0Lvnkci/RrSNQX7BOnpbVw6Nrf1P4x0bSCE/PZt/207ur4MpW/7P3vY0Kg8IH3ldoTuycLh2xO6kVTnfa+lj8eYvKMXuINDb58WdIlgGgt3RAxqDt2+u+lOSN85q524u+/S7+zSMH+k/4XQsXqY9pvu4tBNybBfjhgafTuBvJ9FOoiT4dVnizs+FM4WmeJlfOxRc403OOqH52cDpDbr8LSep4q7g/5ra200vLCiuXwXc3YPexn+/NSmgY7l7PmF0Ds3eFZfR+nWyRyJ90cwnaM5fPOrZjT9v5cXz65r7r6nDNO8SFXBts6d0LMoxHrewinUnl1dnoU0ScNERrLjgZZGltb/yDMfBG0endAu7Ih+6NpAf91s7HHG7pu3QUdDt27EP95PNM34NtmZ0mmDu8Zqsfnvpz+k/W/Ii+g3fzzQXzfPg+fgbnYj9B819HOEfmetg4Uxev0=
*/