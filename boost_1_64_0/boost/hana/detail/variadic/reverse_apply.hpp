/*!
@file
Defines `boost::hana::detail::variadic::reverse_apply`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_DETAIL_VARIADIC_REVERSE_APPLY_HPP
#define BOOST_HANA_DETAIL_VARIADIC_REVERSE_APPLY_HPP

#include <boost/hana/config.hpp>
#include <boost/hana/detail/variadic/reverse_apply/unrolled.hpp>


BOOST_HANA_NAMESPACE_BEGIN namespace detail { namespace variadic {
    BOOST_HANA_CONSTEXPR_LAMBDA auto reverse_apply =
        [](auto&& f, auto&& ...x) -> decltype(auto) {
            return detail::variadic::reverse_apply_unrolled(
                static_cast<decltype(f)>(f),
                static_cast<decltype(x)>(x)...
            );
        };
}} BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_DETAIL_VARIADIC_REVERSE_APPLY_HPP

/* reverse_apply.hpp
Aq2ySfPypQy9Gm9rb5G/28g9sJMCll/53+h+qqW3zkK9qLkpHG815QnB4F8ZCQJEaalHwB1T2D5Es9lc4Y29GK6j4qlSw1s3YAb3VGAJ9VWa0YpamtCa8eOM7z3gpGMckNXJmXAX6EbWdRDV9ZBLf5sRbGiGgZevebL9VDbVhIxtmmtvWxteECoCluGjtKCF7V+rTKqojdV0LKiPRZR9VC+7TjO7lbWXTnv/SrmdAHug0yO2zqE/xoMNqB17tHCD/LaA9L+D2dxkWPiQMUQUhChgQy6Ndu3lZ4ZBQcGIx749hfTxEtrHzGFtplGbpCiXwZgl7a7UrEcOWl5lr5X8amzMpYW2yPHPAwy7RBNIPnkSVlNXVVUNJ5hiivMjYdXFMyoR+AFQ6VdHd98AN15MnQEQxT6RsIrKGoRRqawmmN+E1Rr1VlbXoloDnme0j7dWqZ1lMo0X0hGWRIzGGu1Ba7QeOIDJVHasFsEnzDXJAHINeq6BLs5RRWd1mJEh8svpA1pMiTKN+qa75rwGZlt42sVN20QjgClyXx9yn1+GDP2aUSflFRB/aOL0oHVtjRfw/hg+dM7+LcVI59rpVCM9Vlj2xDQjPU4MJ1tRs3svNK2ujGyt8i+05emzsxn0K3WIeWyPU+Fz8xNoEM45HNLzYvFy+FKF4tbW8Bu+N5wRjnrm87Vnmv84PI3gZbYUMU1nNr+hfFxQVErYdQBHtNgrmwxDlMHBWH6GgNmKtW3bqZhNi8piLMQr2fmGlTfUoCk7w57PESZuKnGZzNgF1nTAlLmA7Z+p3EiJoyTKjTLrMzpHuXZbo806PPNyzO9q2utbzZqV/Fz5rXc++X3MCkfH5hJ4prwvZedNoHkwGma43Yfg5mpy7KB54PWhhvk10OrscRUJu2m7TyWiKBJRxQL3A6H6a2TAFTKD8Pwqni/dFcOYF8qb7fSthT618+awPPrMHlMzzvjkaAzLNhtrxJZ91YuC+dFGWYOVPx8FWox1XBSOGyf+HULyvJ2xdCJsPa/7AzzP20+ytKwCnLoCMawCRhUsTfpCtFMbGClgi+ECbgbPaIlFwg0dZne881CvvLdgxHazx8buLYAX9oE1dSHy4KXfFJ7bHje/x/sv9E50nH2nbWYfrH1YDHXhP+W9S9wVoD1UO42/yTgLOd46C6nF8+QIj1iQX7gvpPfMsmpYGWeOnTTJOUqEZW73djpfVIB5CT43dFaNyQLFjvZQH1PHsnw+hiMN26wM0NDeMg0vhtOe51HAB7rghUEcREcKsbuqB6nTGjDG7IcdpSGEdURtPN5H8qR8sLFFxokemV5MP0Dk5YCPRSUnNXOpRjMWxmJ0Wh0rtWXkTaCz1G7pKCesb6vi4Zh89dpZQ3mka8n57gmPnSVsvksT4d6c74SIPQN12fOHf12cRxXSSqfSCjCvC1ON+wlc7tNZmMTjUgDUmgmPyJNlWyU9IjUw9RCkU5IfR5fpEXgz7hqu7mPhrEvt/Sl46094M9dqe7S91byfY70jf3gW72vnPM5Lt2Q7T9yJWOzJVdRclbct64S3HenB2yqo70dx3vYH+nGA2KQP+bQyeP7nq4fynRexbXnHEF/0vicjNdzaMvOYmf4mebKcvltFc3gs0uwcyfAodt7ENyQz6Vjkr2DCysOQupyPDZT6gakU1YbrBeNvJeF6Oumz9TTOV6kceF68PoyL9/GOOkh72sia9Rxn2Mpxr6UJvsDki3M8m6cJXuNlvsXm9C9sj5l6AvmSxEOIIWX7Fq9w7ycjjeFFZFegv1HfPJcMInFPz5WRtFfX24xwa4O96FV4nmcVpi1npMZ9xCvwpcnjT0I/vZpAWeTJvss02/Mn2lM=
*/