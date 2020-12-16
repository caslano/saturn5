/*!
@file
Forward declares `boost::hana::zip_shortest`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FWD_ZIP_SHORTEST_HPP
#define BOOST_HANA_FWD_ZIP_SHORTEST_HPP

#include <boost/hana/config.hpp>
#include <boost/hana/core/when.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! Zip one sequence or more.
    //! @ingroup group-Sequence
    //!
    //! Given `n` sequences `s1, ..., sn`, `zip_shortest` produces a sequence
    //! whose `i`-th element is a tuple of `(s1[i], ..., sn[i])`, where `sk[i]`
    //! denotes the `i`-th element of the `k`-th sequence. In other words,
    //! `zip_shortest` produces a sequence of the form
    //! @code
    //!     [
    //!         make_tuple(s1[0], ..., sn[0]),
    //!         make_tuple(s1[1], ..., sn[1]),
    //!         ...
    //!         make_tuple(s1[M], ..., sn[M])
    //!     ]
    //! @endcode
    //! where `M` is the length of the shortest sequence. Hence, the returned
    //! sequence stops when the shortest input sequence is exhausted. If you
    //! know that all the sequences you are about to zip have the same length,
    //! you should use `zip` instead, since it can be more optimized. Also
    //! note that it is an error to provide no sequence at all, i.e.
    //! `zip_shortest` expects at least one sequence.
    //!
    //!
    //! Example
    //! -------
    //! @include example/zip_shortest.cpp
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    constexpr auto zip_shortest = [](auto&& x1, ..., auto&& xn) {
        return tag-dispatched;
    };
#else
    template <typename S, typename = void>
    struct zip_shortest_impl : zip_shortest_impl<S, when<true>> { };

    struct zip_shortest_t {
        template <typename Xs, typename ...Ys>
        constexpr auto operator()(Xs&& xs, Ys&& ...ys) const;
    };

    constexpr zip_shortest_t zip_shortest{};
#endif
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_FWD_ZIP_SHORTEST_HPP

/* zip_shortest.hpp
BDAgl5v5LlT5rDtNtrqF2Qc/C8WNoA84yKk3HuxBrLl/LMxgQZ+SVV23Q+0fARvfOnfIk5CGr6M/q78g+sMGocmUz3ZStClKZWoij7HSwu9yLymGY3eFzxbvPLLW417Cs5f3ZF91N2y5M1v5WQZbSbQDS0wy1zgC7+pozZjXX2Vwe+8rA4ukCvfWs7wIERSo0BofgtuwdFI09O8GtyjnrtORzn+bxQDuLNEFugJgWTmJx5EGZjErePCMTc2DtvAqKIfQ1PTwvOydLqx5KjjIaloe8eXlEWw4cavlJlxevssr1nlMrWkUMSijiEOV/gbUjXfY0wNWLwfsw+1yPRyqsrCwStwJTlnLd2QuiCchiLs5Ih7gK395bMbP555AAqH/4MRloMz59US3tvNLvc9etJ03Kudk4Oz1hv7PRwbO4sn0cISXHoio/anzPfTmwxXYehALCgZfbyU0/IOxLt6B78ij46XaRarIiBizV44LHXsN0n6WHnNV1zxVFz/QzpemwZCmRqTrG7De2Eyg5J+nx1EVcNxHiv/vqy1R0eDF7t3GNcszMuOWM3DbZh3Lu4lvtyPs+HypWh+B/0+mA9jYBOpkL+/To6T2FBYPvqiOUQ/TfpTRjl/Ldvy02egI7NcbrAP1Z+irTU+PjkpY3vxNxTvG+fduRU+8RdvTHI2es9tiizlrl0+w0v6I+R0yFCZub6CVXv8KndY/2k/z/ISH7R4JxOq/MxBNHvk2xIL3jFUZSQfJpPNU0muMpGwopsLBafJlmrkqzRwjzRp4I6BGXzxq8LqL+kcLZNqzVdpyI+21vKv96CVThIKdEAe9ukWyINLU2tygeGItB/Bt/eO5NL4joQrcJdmz5kpGdeMRlVdfUor1hfBF1qr29Y2OlfBcpLI/ZGR3qtchQuKdDehq0bS+Rdl7/PfuPVcV03gvAmNPozm6qB6z8wraOj8q7sACd9XIkbHupYk1nkRr9Xm7ms5FxJptjqLdnSiWTiVrQkVb8aVrdPj48Bfg23L0vh/eg9ziwAOQT8OTl4S1faBHARlYQk/1TG0MihNl7+s7mzwouKgeF6bNkH20IZ20poXVN3kj83BXjMNDDYxa98v+nCXk+C4kNnuCQ5/BG71EPXTk7QK2LW77lHFDnZycYOO1wzEMwqRlZpSPogYaUTMIz+1PI8GPP5ULi4vOzuhM9UsMmAF9GUG/JC2PjQ1kOwY58oI1PZPko4+yJxTXtOdM4D1NZLDMsHtQUE3pLikhrp5c8YHigSdaTBlhobYxI9+lSCTOfEZFE/P9Rka0xlq9uS8ojPbz2rktI0UFUhhNjKKR9gY0c/Enqh+qqB9yrNwPrpu4H16oqRZ1ZoICSvChUkzHf/SXHxZX84z28sXIv6erU4O0+q98hDWdBupVC0FwUxsI9u3k+NO4En6T5sd00R78T43o+SpPJn48Rj1bBCMZbyry2F/b1b7CyX+Vs+xskiAg6znBYQKnhKnX1aZ4htaKXM3rtR1mZrvK3MPIfLT213RkUyEdEDW0T/3+h8Z5EAyHsCgdc4N5AB8kIHyhLAUHhxR/Yug7D5OOQjFIOkpEHzhgQF56q0QXOGi3PA1DPETzu4xaNZKlaX+QFUdRsXm/s5ju4ry2S7Kiz3DIv42AfM9+9D43WCvX05e7+3linUsTre7zPqETGcfTyxDS0KH+qyv9nrvu+pzS6Y3ugYvJf1mPEzzxvks2x3peVm09IWiNd0+ssSXqbUs2xz+ADn8nvOSx3krmnSoS+9znrSENVNT1OdV+UFsCqp50QscaaiQjah6vpqfgGsLuE7cU7YZC4aDHPgOtNeE78bPlp3qSjhZ94s7kpBZHxahd5zU=
*/