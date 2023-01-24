/*!
@file
Forward declares `boost::hana::any`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FWD_ANY_HPP
#define BOOST_HANA_FWD_ANY_HPP

#include <boost/hana/config.hpp>
#include <boost/hana/core/when.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! Returns whether any key of the structure is true-valued.
    //! @ingroup group-Searchable
    //!
    //! The keys of the structure must be `Logical`s. If the structure is not
    //! finite, a true-valued key must appear at a finite "index" in order for
    //! this method to finish.
    //!
    //!
    //! Example
    //! -------
    //! @include example/any.cpp
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    constexpr auto any = [](auto&& xs) {
        return tag-dispatched;
    };
#else
    template <typename S, typename = void>
    struct any_impl : any_impl<S, when<true>> { };

    struct any_t {
        template <typename Xs>
        constexpr auto operator()(Xs&& xs) const;
    };

    constexpr any_t any{};
#endif
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_FWD_ANY_HPP

/* any.hpp
aAnCr4HZ5Gsk5WLrc1F/dsQQxmtI+rbOfy0eLI+I6xEzhBu3Pj0KzQQPxUzZgMHSGINniw2tiyFhcCho+RxGJLd418eBi5ALRi1VW9QanoYapIXNEWfc62L7+TBSkVh3vRxsYnrcjj3hl+WVMGE+ohVWmvaDCF6CJ3iq4v9PbxVqKqqA+dqtQofQYj8uFeIxn4GdiWUwk2NlvFTPVsah//L/glWjmzRZ2SGpUJU++fW4inSa+bhbE1dQtWx2fJzT4lK6tUncLC1MKW8SlneMBOMSWIms19ll8ioGLx1Mz2AwNUxxVJUa2OlxnY5zpRgKNciCGpANv/1+jRcrotZhy1lRhz/eQvc9UweldxdfXcJAk4EwGxSj66zb2UBPjbNLg3rFc+KRiXPQqIpnET9IVz5tjpqiwPUwD9yEqpnWCCCH8SAERQw5rny+T6RarmggX8Ggz8cytNlKgzyB75Rw9syGgU5PrnuVK+teKdiF53KRp+hK53jcvz/IW+Ddr639xXj4HYaojoG1ER7msXjAjFOgvFCj8Y1/UwOihVcqNfBr7xa36+vJToOAdep7qB2peWGODyEHnfstxpYYcAveiW3lqy2kwMsa7VEcTttgedjLRzqBsV14Z63EolEDPsUA1HyxR4unmYKKHLx3F4lkraF1Bk1wke/5CTjavHQNNn3rkiWAN1uIekzwJeWZmQuNm1gW8dkLKQEqFM43
*/