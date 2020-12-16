/*!
@file
Defines `boost::hana::length`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_LENGTH_HPP
#define BOOST_HANA_LENGTH_HPP

#include <boost/hana/fwd/length.hpp>

#include <boost/hana/concept/foldable.hpp>
#include <boost/hana/config.hpp>
#include <boost/hana/core/dispatch.hpp>
#include <boost/hana/integral_constant.hpp>
#include <boost/hana/unpack.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! @cond
    template <typename Xs>
    constexpr auto length_t::operator()(Xs const& xs) const {
        using S = typename hana::tag_of<Xs>::type;
        using Length = BOOST_HANA_DISPATCH_IF(length_impl<S>,
            hana::Foldable<S>::value
        );

    #ifndef BOOST_HANA_CONFIG_DISABLE_CONCEPT_CHECKS
        static_assert(hana::Foldable<S>::value,
        "hana::length(xs) requires 'xs' to be Foldable");
    #endif

        return Length::apply(xs);
    }
    //! @endcond

    namespace detail {
        struct argn {
            template <typename ...Xs>
            constexpr hana::size_t<sizeof...(Xs)> operator()(Xs const& ...) const
            { return {}; }
        };
    }

    template <typename T, bool condition>
    struct length_impl<T, when<condition>> : default_ {
        template <typename Xs>
        static constexpr auto apply(Xs const& xs) {
            return hana::unpack(xs, detail::argn{});
        }
    };
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_LENGTH_HPP

/* length.hpp
W5ffB+VqbmGlOsqFV/DpATvxSbWc6Pavjja5kT1LPPHreqYaItw76GRTNRD96AY7zFs+d1rrADZ403wQlL5MgMv3YtSff5AYSDV/H0h9bETE1D/HUD6qNwlGrR0jOEwd9zCU8zVTl9KYLqO8mT/mnF9lY0Tqz8C9iXK+brVleNAu92E6PMjU+08CjFyMSGc9A7/ztY469Z9kn5Yhs/3PZvTd2awhTPP+uYK2UkJQrocI94tG596cxkzz45WAEQvSPEwcNZ6vY3NNzDKujwTed+7QZq5Hbwtcx8tZDz9aut+equFrWu+9gWlHaUrExw+TXLiuPze34Plz7mxcicZqcjWerwKOWcAYomPxLKCOHah58S2Uj6yBwMD5+D3AMP0ZT8zVuH84Ih+oyObuj1FeufWiIdr86x3mXNtG/H1bZoFV6bJ/oKwo52MXei4gOjcUOkLoN2rvvwBjDDt9v9YNAdcYRnoMroPvWXV8zi7RqgwqBUWif9fHd1OHqUGo27mnLj/dW1sZsRtuVpd58dw8lBUWdlZX9OPmKK/Qtlqjog6XBZLM+MG+Jy79KP18q2YdE22i1a6Wh1vfcMd1R40J+gr5Axwby8I/XuO+o+INJBvXEKXMqXVvH346D8KWuS2zTqwsaQn3gj2djmiYqndngdMVww8aY8Zl4fhEOlcdkO2/J2DH6wVTFvcDTtz2QRsjMm0hx2gTvpNsNZ4rNiqi7hEJg1Y3s6mWH7IDFI0H4INuiLvaQ0iTHB8X3017siGANkAejPnvZOhr2xaJtQ39wKMYYTS//h6Z4zI3EdcykTMZbE1PU2YqDIMccaVFaC2s65skTb7IvXVZKw+8XoSpRfL4kIantZeC1VM2/RyEdGG+hn8Ep8WVFtFZ0jKGIBi0U7VxldGx59F85+i839JjvfZ8YuU35HygCSNk6jE33FlH8n7cDvAeKWUDF9v7PAW4DB14rK77BmkDSlmV7fwMfq+YwoWEip00eFrD3+DqKJ+Lylni2bOB11zfmR1NbQM62mzX/HruWDkz9xtPB0y746r+C3bgN7crXzYWhsaT+HbxBkpu5iTNV9yQ7ynNufHaHeYnH+M3A4bbMk0x7cXY/IP+5/aMHO93oXyHPTsQNXL4PsBV0rhdgOd73ifbEvVNW69dWdS9hD4zIaQ7UliPTfnwMH9r2cJ4Z1UtXQLuI1y3yPGu+/Ypzu8sLGebrqEceydlRykfG7wz5P2Vbb+A+qO2pDkGPxrbP9OGuQiYUZvO1Dm/AQyzu1hLSS+o+XRoEnIBngG+rdjVmva5er5gRc4r6DY1bSSvzmEeqg5xu7pzo4Y+36uqPlylLudVm07SHP8R1iq+iN4N366Oei07AIpXtEsqDQjMPDyStW65NmDH+2NMXuzDz6O0f7kJ7WfMjQlbY8tS7LxkH68L/NUYw02tUY8ET3GIpWYKPNo2+gX9ciPQg1zUNlKHbE58I50j972AaQSto/f3GW3wBf29gDHnmrlmXgX9qI6VsUdz59YNP2BBHCtT8K69du+7kZJhdMbPwIaa9hDlOMHb7C0M5e+Pxu/HBc8UDwWt2gABHswphkfeWKfvd8F3Wt+NfcK98N1cl8y5dRjlpl1v7u/uABnlN1KUr+0+O8iAYpSS8edyOxE84XL4AODQRj7Jtzsi36aeC1C+g9+DkBNdQx+bdvQfUNbosY62gyIw4Gg2L8c0BZ1RXWDy5r2o1HJcGrqmfYGe28gV8Ju2jamv3jWKo+nEZfxqyq6YG5XJ9tjQWt9eMDC+vA/tYsKi5Oc46Ji621zXHoxy5isxfRzMDwV1ibGp902Z2jgRzO2UD4fb4KYiR3+wtu9mcwOsBdswvKg=
*/