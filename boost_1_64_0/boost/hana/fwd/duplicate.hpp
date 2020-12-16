/*!
@file
Forward declares `boost::hana::duplicate`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FWD_DUPLICATE_HPP
#define BOOST_HANA_FWD_DUPLICATE_HPP

#include <boost/hana/config.hpp>
#include <boost/hana/core/when.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! Add an extra layer of comonadic context to a comonadic value.
    //! @ingroup group-Comonad
    //!
    //! Given a value already in a comonadic context, `duplicate` wraps this
    //! value with an additional layer of comonadic context. This can be seen
    //! as the dual operation to `flatten` from the Monad concept.
    //!
    //!
    //! Signature
    //! ---------
    //! Given a Comonad `W`, the signature is
    //! \f$
    //!     \mathtt{duplicate} : W(T) \to W(W(T))
    //! \f$
    //!
    //! @param w
    //! The value to wrap in an additional level of comonadic context.
    //!
    //!
    //! Example
    //! -------
    //! @include example/duplicate.cpp
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    constexpr auto duplicate = [](auto&& w) -> decltype(auto) {
        return tag-dispatched;
    };
#else
    template <typename W, typename = void>
    struct duplicate_impl : duplicate_impl<W, when<true>> { };

    struct duplicate_t {
        template <typename W_>
        constexpr decltype(auto) operator()(W_&& w) const;
    };

    constexpr duplicate_t duplicate{};
#endif
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_FWD_DUPLICATE_HPP

/* duplicate.hpp
VbSMAI5CxwrbDlro0o0VqMaF7zfxPQvfZfgaLPgY8TWZnzqdj+r/4VygiSVP5W4hrbbJ2fKL6w4K7oFvhgCdsLPDkoa55oCQOnCFT16DbYpP+dtYbb29gA7XgGU/PJ9bwAxoucMjVtl8tzIC7rt8FUorZ8DlntpnZBKMK68e7+QOLAcsGtdmhQSPs1YrCq9dNgR//G1JewhlJ76XofLE90MFPdEvo7Eb+iX068adczKmUzKrpmHnVp7mzTUZ85iNLmztRouFkMr+qBWUauV84j9BqJrzQahmWIE22UeN5F4pOBF4G9stkq14JRJGnnaXmVX4KJU804YfOwXHDnBkNkWSbVzuQJqXX0Ghv1G/f8C3Cd/b+P3jzUtGCYyRuAifAaoLiottq/3R/tSGPMCfNcZEcUPkEr4wyMrpNMeYxt2DTtQZZwyplS1G8QbhG+jK6D4ixl7mj24zcX9Hd9BBGOiek8VOBl3sVMyHGKbAPUyZcPVpBegc6NIvr3Zwvhz/F6SyHwrj8aXnib1UBmUsoBWBaOulzD6wm2QJ85LLN+rl7zUkgSqAyEkBghRkmAqfiwJSAMnRAfmmDsgDoxMAIQMtXuKg1hXrZi4aKMynXJGFGbjYil6DuE/X8K47B4Q+FzsR8E2lmseiQDX7HIhklYTxCzlu7YvUoh+eTG1RQwhBKLtsCk9H1qgFYHzyvBoC83RnosAcCYeqCb+vJ5zGCV8ZnJhw45zRJscH+AbwLcP3XHy/wGEfD7f+GR+sBzSzRrO4PdBPrANDwwiN7Qfhh+xrNezf9aXJA73YsDWSMI26K4/lGbo/iArSo2ALEajDKQrP8+qLjOa6qoSx3puw+Kz9XJpYb8yy19JUCsFB35XwA7225HxeWArwA+WtFzJZzIQ1Pn6Hm1elOVmaAwt+h68JehYB0mijNnow0penK69eAoSl3oBhaOGpgpemMDyrTzVigxbhFiDe7muRjfYBhrDb0lZiW0tbPftcpemDzjgoBD01yRKaYSuh/IupgI33FkAnAd/b8P0mvocKPr11qqcPNf+ogahmIDNh6GgPtJtJo3w81sXeMHbIfKpHl+SbQIpkRTbLx9a9KZa72XQMDwzBaSwoHxQnC+/g8h01WJK1bqaJwGXgXCofVWijzTPkDkO36TenByYrr4Iy8QnWa/FJJjWIE6xgVuI8qwmn61l9ULH+BldjOz2TSu015yWvd+OlmwEDL3j11tTb9Zp9AGsk6d0QSYm3RJLfbSnv8WXQfy7qYz9ft2ioCW+MoxHIHfEn0RHLBqodkdpQfb8UngGYEt/xmhwPmJLebSnvAia2wBWAwVfszPlAbsdRI02mACY4Jmeps4qtoMzVFcLpQckGmN1f4xTngXZczlBlMXQBifYzBfIcWrxHhFY7DFgr6ayoVpzDkKNVeSZpm06J8iEYqP8U9m3bH+xRYT00UEN1OAZw85n7rA6zMTAlxHpZQz2aRRfscM7O0N1ENtMh8m70qE/JOdCpWQz5uYnRM241XNsxfRMRWMdrXeBD5hC1HOKpcuNC9vI+aonBHZoJ8niFXiSoMfMhIRL8WkvAgKGDS4I5nioVssZ0HbLhqIpiBTvhEkcgBR7VeAP6i7dDnPQ9wMnGvGeATvF14fbz8UTnZpPwWyW9zA1cO0yjcNePQDDLkxgSeMac9Zq2dbuAjjsL9eNOxD0BvtDjVSH8tlVtiL3hRayZWmPc0vuiE4d1uVKe3FggT3FwmKdqLsq6KU1vLUzZ69ENe4MWdO3kDrMpkCM5f0TlXveqCt91uXG4uak4z31VHziycqTeCx3RhMO7Km+136orNj6pcSS5gDx+7ulQzz2z6jw486xWfnY=
*/