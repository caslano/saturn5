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
G72kYbbP33H7cJviQSbaLFy5/jHZRA/jh2ri/n/KfsqVWEmkeNs8rN8tLaaTQB4Ww+HSDXs7iygU2x4Ex/h4+5GVUvnKMDnibMBR+3Hb5UqSxApiGuDJ4+TH3NtiGGceDBei1NatE6Ipz0zgGAxJ4n91z0RH6kgwVIPYeJ6YIiVSlGVzhiXzPIoWT/0B7PEg4X7JTPOHdmksH5iRhrV2P15PelQtz6cblDpfvG+GTQZKwMRqSGxUQReOkkGc8DEzdDD2bPduMHyx4/Bs9EOKrclXh9/NA7QrFcPKqljah5Ka/V6y6xFx9T2EPK/8icRgb4MvkjqJrmlGB2u1aX5X5f2JzEvqkd/SxMy3+tF8XU6kYU5Boj5QTQ+zvvGasfFdBKtcwH0gj8Pqvrmj9Vqdt6SwL894iSUTKdfx4SszzY+SczLWWWn1Hwtr892q5wNaP7OPoppNUq8Jm7iPWDIsLPcoUydTDcR76+GM85ByQlbML4q48xZ1pBLQhpjFnq2K/XijLLaHBC2ka86QSDAoDgalwMxzkcrzmJHnLX6YFfVELYybNzB/7GOdpkLSafopB/dUDUNwMb/bqdNtQHklPRQUIyGDUQ9YjjFxi850VIUnyQqbz+GTGlAoLvdIVR2EEieaUHpUJq+RaST1BGcYwhk8xIdrFWaGn6kM77+UdaAzIyK6/ZHQuPf9SkcDJzqkj3hoGodV7t+/pM7xvuNXjv/5n6SP577J538R82n53UVbxeo7pfxHF0kopBJpXIIofb6Xbr2L+J+Nu/7n0Rn7xWCnjFuqsRkQBh2pDv1ip4TFlDvVZvtDvc5DOkyUZfJDJjbGjtRRQ4gGLlxDcec/pE7YvMn53mSdxyQtDkpJt2jinfGuwn1c8Mj5XjKl3fAG+2Dh/A/qcI2Eld/OQirNd3nKTfaX53hIS+PVBxm6/b8Pxhb2nGIbDjOwMjImQ0llqslulGl2iRDXvGCe16atYb8tzy2SRrZaM5tdZZuhsh3MiwYdwMeP6nRHIfpkb/rlx+WjbWtSdnD1Iw17QiPoRZ/zhkWC1eKHNzNMMNICrvFEE6JZmkNC9Bw28sogw8Erxyh4mK1OrFpJqBfvra01d0mF+E/U8yi7kChMWzxKxbu72v3f574ZXUi8Y6Mjj8qkbVgeaxlcSkW/Ym7Adhvv30royZLPJbS7TaUWzRuk6WbaWzPSvvucmbaahguLgb+a7f+oR9BXEe6FI3AFEO6tVmszfzeSMXakI9Wd5sOJYJBr1DMIdrornwnyFoTN/W/J60L22bTrFRhhqEzUt5gGRL4T8z2M37tLHdZYL+0eVVFQXIYNc8c6KsSrAkU6G/vCdjYYYKvByXvgzbiuW+ZM2hDgkh4XezzS42GPV3q87PFJj489funxJ21fK9/KgCfwNfDkZ8JTkAlP4X4qUvYnpM2J4kwDFCUdGaDQblK9GB0tnn9TbmORAdszY+s8hC3QWqX92TIPvgF8A7vcC0sLz3K/Vlaol5Yky0oSJzms+pqvHeL0/iGvzf4Byoj4uJJlLlaTL/NIXUWvVFT04eNPlvkbDlBeIKu8fFlegSyvELFt44tlfJZ511Vz0BUZQbe+0ruf8pv1ZQhZw9GTZe8VslhEGevwRyfL4DLtc0P+ud6kgY0VrL4t3nyW6G0BvQgTDWUlPxLJo2EOBAP7BAvyKS/Dw3tk6CGlYiWwoHCTWq2GRGtlKUNUKR80cqWwI9XcYhpkSS50NDvFGfdS5Q55Wb9XULz4CKdg7SZH9MfNf4YwCirYBCjJpBor/EypvnhKyQvvoV0Qv0QihVckSIvGJQAVTReBKH2ri/kHwJ9HaYzAbE1Yn+zGw5NNnzsQvY0=
*/