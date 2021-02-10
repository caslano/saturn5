/*!
@file
Forward declares `boost::hana::zip_shortest_with`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FWD_ZIP_SHORTEST_WITH_HPP
#define BOOST_HANA_FWD_ZIP_SHORTEST_WITH_HPP

#include <boost/hana/config.hpp>
#include <boost/hana/core/when.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! Zip one sequence or more with a given function.
    //! @ingroup group-Sequence
    //!
    //! Given a `n`-ary function `f` and `n` sequences `s1, ..., sn`,
    //! `zip_shortest_with` produces a sequence whose `i`-th element is
    //! `f(s1[i], ..., sn[i])`, where `sk[i]` denotes the `i`-th element of
    //! the `k`-th sequence. In other words, `zip_shortest_with` produces a
    //! sequence of the form
    //! @code
    //!     [
    //!         f(s1[0], ..., sn[0]),
    //!         f(s1[1], ..., sn[1]),
    //!         ...
    //!         f(s1[M], ..., sn[M])
    //!     ]
    //! @endcode
    //! where `M` is the length of the shortest sequence. Hence, the returned
    //! sequence stops when the shortest input sequence is exhausted. If you
    //! know that all the sequences you are about to zip have the same length,
    //! you should use `zip_with` instead, since it can be more optimized.
    //! Also note that it is an error to provide no sequence at all, i.e.
    //! `zip_shortest_with` expects at least one sequence.
    //!
    //!
    //! Example
    //! -------
    //! @include example/zip_shortest_with.cpp
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    constexpr auto zip_shortest_with = [](auto&& f, auto&& x1, ..., auto&& xn) {
        return tag-dispatched;
    };
#else
    template <typename S, typename = void>
    struct zip_shortest_with_impl : zip_shortest_with_impl<S, when<true>> { };

    struct zip_shortest_with_t {
        template <typename F, typename Xs, typename ...Ys>
        constexpr auto operator()(F&& f, Xs&& xs, Ys&& ...ys) const;
    };

    constexpr zip_shortest_with_t zip_shortest_with{};
#endif
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_FWD_ZIP_SHORTEST_WITH_HPP

/* zip_shortest_with.hpp
q1YW6jclnFMK9gA9FqiQqlhkMlvwfcdIJ3Vb4qikZkgXjTw9OermXab5bOq6iPq2ZqWp2jqXpJigiCSt0FkCmjVm5JpUVwuVNBbx2WEs4mGWsajBpUUu2bNtDy5nRGpWJBmfOOPh4nOWP/ory0viDF8eVesKhZO2sraejGcpNxftNiG+z407nw7LyWxxVUg1DnkrPyX3WSUyuutsnIqGNpKLZcnfg7+aT1N61kWDtHF6nU5n85RMqGVRSo2xycdcJMsJzbsYjpOr2Yx440U6Gi6Lqlmeb2OQCOWSp6TjkdTShDhs8bUo06vkMl2k96UiMolP+j9VTU2yBVlzxtk4f1jSdE4h7vFJPhOPvVjM/iR/pVk92uQXMgeIYlubT36U2mPKkAlxsUiHfybDT8MsF1Jb20+EXNuHlWcCdOM3x/iv6PabFsORY01nM7njm3Rom3y7NVyTw6Dr/H4cBRV41CEj5gw5qCCUE1SLo4foUjEry20gxHFczTtwBFf1Hz+7DQFlJWy1RsvGVS1O1xlRDYTdNG1vywEB2rg3cSQgGR5+XPD0EdlEynTEN5fZIvuU5cN6+2IrMWUd6veMdDfa2gR/y4rSueT/SMKqAmytd/XenFCQEV0PKVEhGyllSBOyfb6S5Og9F4uR/BP6
*/