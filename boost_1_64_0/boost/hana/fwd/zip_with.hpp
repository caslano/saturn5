/*!
@file
Forward declares `boost::hana::zip_with`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FWD_ZIP_WITH_HPP
#define BOOST_HANA_FWD_ZIP_WITH_HPP

#include <boost/hana/config.hpp>
#include <boost/hana/core/when.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! Zip one sequence or more with a given function.
    //! @ingroup group-Sequence
    //!
    //! Given a `n`-ary function `f` and `n` sequences `s1, ..., sn`,
    //! `zip_with` produces a sequence whose `i`-th element is
    //! `f(s1[i], ..., sn[i])`, where `sk[i]` denotes the `i`-th element of
    //! the `k`-th sequence. In other words, `zip_with` produces a sequence
    //! of the form
    //! @code
    //!     [
    //!         f(s1[0], ..., sn[0]),
    //!         f(s1[1], ..., sn[1]),
    //!         ...
    //!         f(s1[M], ..., sn[M])
    //!     ]
    //! @endcode
    //! where `M` is the length of the sequences, which are all assumed to
    //! have the same length. Assuming the sequences to all have the same size
    //! allows the library to perform some optimizations. To zip sequences
    //! that may have different lengths, `zip_shortest_with` should be used
    //! instead. Also note that it is an error to provide no sequence at all,
    //! i.e. `zip_with` expects at least one sequence.
    //!
    //!
    //! Example
    //! -------
    //! @include example/zip_with.cpp
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    constexpr auto zip_with = [](auto&& f, auto&& x1, ..., auto&& xn) {
        return tag-dispatched;
    };
#else
    template <typename S, typename = void>
    struct zip_with_impl : zip_with_impl<S, when<true>> { };

    struct zip_with_t {
        template <typename F, typename Xs, typename ...Ys>
        constexpr auto operator()(F&& f, Xs&& xs, Ys&& ...ys) const;
    };

    constexpr zip_with_t zip_with{};
#endif
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_FWD_ZIP_WITH_HPP

/* zip_with.hpp
oFSUAdgjRiavTHlbl5M5j4K/ziRQbD1oT1A3RrruskmcUGwe7PKUBIPqNjLsHbXhLx20n6OYDd3Mu1UqrdAz4zk4mxtnL3fBvLwV1wqzZeo0CulQKmbdEMUy/yWPVETc6UZTk8xkv7R8lo342EFkRqY3+Y8N2ewnIPhluw8kOMTze1mtFPFYLGNALsj+4XWrS8l8OKxvh02YqJ4/+TeUwEQ+tyIdfw0pDGdrZ3kCXBrA7m5WFDwU5DAFi2zW+4j/A/P2Hb8PqdZsy5ZkqstZJyLc0Yw0YXSaKKe8kV/7rTXpfU9RnSAQl/YFhExJJbJX/v+ESBeXPEN16hcovqFm74psr0Kl/46pau05PMN8XB9uZJKIBOBHDiSKjVUWZ8bfeirJCipDPuQYarw9dqbhn1YKKEZSwwT/v32vKfvCVP7ZXDYWvP/afy7XDdtMFdvmqlwz6k3rwumQX/C01tSI2Hbbn3IFUowNfBwBXd8PfIhI/QyTdijYGpZVzqtgQRKM7x76iiW3AzuSe1aQ1lTu/WiXRxCt4bvhnoXNLs0D9W4QEJVBI6DJ/lQoCg==
*/