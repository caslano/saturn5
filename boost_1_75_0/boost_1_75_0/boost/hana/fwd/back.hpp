/*!
@file
Forward declares `boost::hana::back`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FWD_BACK_HPP
#define BOOST_HANA_FWD_BACK_HPP

#include <boost/hana/config.hpp>
#include <boost/hana/core/when.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! Returns the last element of a non-empty and finite iterable.
    //! @ingroup group-Iterable
    //!
    //! Given a non-empty and finite iterable `xs` with a linearization of
    //! `[x1, ..., xN]`, `back(xs)` is equal to `xN`. Equivalently, `back(xs)`
    //! must be equivalent to `at_c<N-1>(xs)`, and that regardless of the
    //! value category of `xs` (`back` must respect the reference semantics
    //! of `at`).
    //!
    //!
    //! Example
    //! -------
    //! @include example/back.cpp
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    constexpr auto back = [](auto&& xs) -> decltype(auto) {
        return tag-dispatched;
    };
#else
    template <typename It, typename = void>
    struct back_impl : back_impl<It, when<true>> { };

    struct back_t {
        template <typename Xs>
        constexpr decltype(auto) operator()(Xs&& xs) const;
    };

    constexpr back_t back{};
#endif
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_FWD_BACK_HPP

/* back.hpp
L8P1QX1oT7c92nls+eB6iNh08hdo1q8Kld6KWJXCiIpmn+Xwt96gSSgwj484M+2yCzvEQpC/7yd+yQxH15kdNWsNwd6xtN0IA2dMw2o6CE3YN8JzNiERl45mA4qh9sXTFszpDlyLifPMMDZmsIO4qcvvCaEsvE5fVFjt4r8JC2NRl+7nGk8BNc3ySgMILPl8YgD3dIck9nShxR/BFt80GOaj01KwFWWrKKrWGz2+A8DL/oGuSBE0S5dvB3xJejLaaxFmUcR+1e/+hMPdjLFof8dajvpofg1qjfua/qpRdD30UeVrEqYSfm3xpOz6tPHwreQNLBf5vIk83h9Of7NSzsi3UsuhryvmY0a3D22z+rXM7PVrXHL+7QKDE6+j9FjDRw9KMV74PJBFNV6Y1LRu63Fd8bRalfFUld3joex/X/9IrgGVx3+LNvZyzfj6FN7W6oPmx0KjE4ZeUu7OiKszP74WRWExtY6tPIHNNnUQamtY0IANLIhhcUwWw4+SxfATZAt8T7uyH2Jy8/Y/Uh9t4n+agqs6qaQh0WwvKM3WvCv+d8DBk8DB88NtUCwyzf4/ZZpMmVy+BW+nNhx9XTFfLI0KwD0elAg8Xro6+87kxPzbiANK46b9OKC4+Rd/QIUZA39tMq6AJfSUi7sWer/Ww38/+fLtjbf/QGSx+XUeXnKF+F+L+KN+PcztV4hfLeJP+A0ePvcK8W6M9+Dm
*/