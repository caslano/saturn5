/*!
@file
Forward declares `boost::hana::scan_right`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FWD_SCAN_RIGHT_HPP
#define BOOST_HANA_FWD_SCAN_RIGHT_HPP

#include <boost/hana/config.hpp>
#include <boost/hana/core/when.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! Fold a Sequence to the right and return a list containing the
    //! successive reduction states.
    //! @ingroup group-Sequence
    //!
    //! Like `fold_right`, `scan_right` reduces a sequence to a single value
    //! using a binary operation. However, unlike `fold_right`, it builds up
    //! a sequence of the intermediary results computed along the way and
    //! returns that instead of only the final reduction state. Like
    //! `fold_right`, `scan_right` can be used with or without an initial
    //! reduction state.
    //!
    //! When the sequence is empty, two things may arise. If an initial state
    //! was provided, a singleton list containing that state is returned.
    //! Otherwise, if no initial state was provided, an empty list is
    //! returned. In particular, unlike for `fold_right`, using `scan_right`
    //! on an empty sequence without an initial state is not an error.
    //!
    //! More specifically, `scan_right([x1, ..., xn], state, f)` is a sequence
    //! whose `i`th element is equivalent to `fold_right([x1, ..., xi], state, f)`.
    //! The no-state variant is handled in an analogous way. For illustration,
    //! consider this right fold on a short sequence:
    //! @code
    //!     fold_right([x1, x2, x3], state, f) == f(x1, f(x2, f(x3, state)))
    //! @endcode
    //!
    //! The analogous sequence generated with `scan_right` will be
    //! @code
    //!     scan_right([x1, x2, x3], state, f) == [
    //!         f(x1, f(x2, f(x3, state))),
    //!               f(x2, f(x3, state)),
    //!                     f(x3, state),
    //!                           state
    //!     ]
    //! @endcode
    //!
    //! Similarly, consider this right fold (without an initial state) on
    //! a short sequence:
    //! @code
    //!     fold_right([x1, x2, x3, x4], f) == f(x1, f(x2, f(x3, x4)))
    //! @endcode
    //!
    //! The analogous sequence generated with `scan_right` will be
    //! @code
    //!     scan_right([x1, x2, x3, x4], f) == [
    //!         f(x1, f(x2, f(x3, x4))),
    //!               f(x2, f(x3, x4)),
    //!                     f(x3, x4),
    //!                           x4
    //!     ]
    //! @endcode
    //!
    //! @param xs
    //! The sequence to scan from the right.
    //!
    //! @param state
    //! The (optional) initial reduction state.
    //!
    //! @param f
    //! A binary function called as `f(x, state)`, where `state` is the
    //! result accumulated so far and `x` is an element in the sequence.
    //! When no initial state is provided, `f` is called as `f(x1, x2)`,
    //! where `x1` and `x2` are elements of the sequence.
    //!
    //!
    //! Example
    //! -------
    //! @include example/scan_right.cpp
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    constexpr auto scan_right = [](auto&& xs[, auto&& state], auto const& f) {
        return tag-dispatched;
    };
#else
    template <typename S, typename = void>
    struct scan_right_impl : scan_right_impl<S, when<true>> { };

    struct scan_right_t {
        template <typename Xs, typename State, typename F>
        constexpr auto operator()(Xs&& xs, State&& state, F const& f) const;

        template <typename Xs, typename F>
        constexpr auto operator()(Xs&& xs, F const& f) const;
    };

    constexpr scan_right_t scan_right{};
#endif
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_FWD_SCAN_RIGHT_HPP

/* scan_right.hpp
VdqVNoYUPf05wCoR9gLgU44CvAvfNU6LvUIde/lJ7J1T1zh38E5Le9N08Eq691w5ulx48E6NPb1b+AFnOVr5bagBXgCIAEt9rne0dyrYAPa7wd4cHXuzkth7j7vGaWlvvo7Bee+3nsvgLdCxF3pfYq9aAreQKe81rVcor8t+8Z4MLKfF3lIde0ve3Zx77uB1YE8D7spdarvKUD3J7I9kWn7H7M/7kG/5HTNfso88yfzYuxsDTw8hqnAqIFXJFCp7IRRzGdVtEFfudda9+kYiEd9ojm82qxs7RPjKdvMmJQ6VZAv20688wEJ4CNPtynZ1IwqiZCyF3x4/YJLpsDvf+fgmSuRCoqPxVy3KaytfduIH0F6GSB5ryK9x5atid1kq58ZSZ6/8U+1/z1rig98Hv3f7W5vD9z8s6JDXSFVDXszixaMQXg+eJfKoPz7y0oWnP8YHs0KhBInJErpwZT4Og8ExraSOUGsMmsx/N0n2T6NVis5J3sTi1mT+bnnCyxwU14SOC6lJ2nYcz3ydflr29SyOxstY/djscfqx2eP1Y7MnMITlfN57LsmOXtekMICzBGcS4k1JyPsBqWJ+3PI5n27IpGuZ8MyEy/aLP13TwzlEDAlldZbQFFMVCQwCq74wJ8c3pshAZ59aRhQRlICubgmkIXUJugmvOgdh2ac8tIgCg2b90CKSlRen4NAifJMuD00lqTukIq9+isRyOQRnflWsxiDPtdstQy/u4LY2i+Uf4c70lsn3yzK95Wn0lU90V1ahKyyJslhTXN4jYaljk6RFSp3O5JV1duQ1Wievq/UGvUZv0Gv1Bh2jk5fCHUKSVzaR1yGdvLDYGfUck9dhPg9T0lcJ6KtSntYmb7AOjD75cicJBOVyloAUUe0IAoIIlJXlG2NjwhpXTPDhSsBI3WG6Can6OvgzT63Uo9AKMyv1dFVVSrSiK1Vlgn6+djvRTxbBmBsbqx2WGJGBF42o5Pj19CfbE7QRpzDYUGSj83gb8kzxhJkO1eKrPh400YXOGcsy6WLoBH4IXZoKj4c8rUrD9P18xd7O/dRentYP16TqKVv7cYy6Vca56SNqWDr3tCyg6zxjULGd1dG9J10iQjSpHd9LIjsgt5zOD63b5Fz9cxJz4wx7PoN41HrqKWsz9NfshmIMGTwg5zBtzWnAcE1yvpvwfQlpGuaJwyNZ0+ClQ3yP0iG+DSFU3ba4HE9oqae1WF1ncWfdWdx8p9JRrkvhjuqd+FpQMh0dfYV85pOOXtl8JV1kgyNSbUT3pMNePKMhTKAsACgz5QGgNn66tKcdz6hTRY4zOVJ7c+lvlICqSD0HCUEEfvMxtHWNFae37W6dhZauYR2nuq11KtGAV92J5qaBfechouyd++FN27azFblkyYDWDFZfNlHb7NyPpj9Efj4c1sv+Vow51FCIR0Pdt/SEPHmUzh6OurSzSbk3sQqelZqmaKWu60wePJoSrbRWzq6aS6OycyjoGOeKvmJ1/RPuH3B/hdsJtwkuDhdD/L1wd8J9Em4+3By4crhp4n9D36md//5xtl/J4DPeISgHcj1Qk/H9j85a1cgX95zRriC9u11BljYJZHWxXvEiJoP629dolGhPXiJ5tfOxSnk3oH6JpNAvkaSXFO7F+iWS9GLjGUheIlmQMP9L2acclpdIFtAlkgsPU2+rRMd5Ue9K+E7vStobPe5AwEsdSUQyiZBJhLpeAV54qmxS1slT27VzFD1+0XZV50Pb3TBVWB91UrR6CO+tfOyhZrFQrFkszDTjg4xoEFck2zk+pYPDsEaDNpi8xMiiY5eGqvt2geL167x7uHIR+D011yeSdyd5+bpFOnwcs+jqS9Gsawg=
*/