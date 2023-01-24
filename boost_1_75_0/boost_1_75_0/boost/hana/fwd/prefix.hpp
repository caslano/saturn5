/*!
@file
Forward declares `boost::hana::prefix`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FWD_PREFIX_HPP
#define BOOST_HANA_FWD_PREFIX_HPP

#include <boost/hana/config.hpp>
#include <boost/hana/core/when.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! Inserts a value before each element of a monadic structure.
    //! @ingroup group-MonadPlus
    //!
    //! Given a monadic structure `xs` and a value `z` called the prefix,
    //! `prefix` returns a new monadic structure. `prefix` satisfies
    //! @code
    //!     prefix(xs, z) == flatten(transform(xs, [](auto x) {
    //!         return concat(lift<M>(z), lift<M>(x));
    //!     }))
    //! @endcode
    //!
    //! For sequences, this simply corresponds to inserting the prefix before
    //! each element of the sequence. For example, given a sequence
    //! `[x1, ..., xn]`, `prefix` will return
    //! @code
    //!     [z, x1, z, x2, ..., z, xn]
    //! @endcode
    //! As explained above, this can be generalized to other MonadPlus models,
    //! with various levels of interest.
    //!
    //!
    //! Signature
    //! ---------
    //! Given a MonadPlus `M`, the signature is
    //! @f$ \mathrm{prefix} : M(T) \times T \to M(T) @f$.
    //!
    //! @param xs
    //! A monadic structure.
    //!
    //! @param pref
    //! A value (the prefix) to insert before each element of a monadic
    //! structure.
    //!
    //!
    //! Example
    //! -------
    //! @include example/prefix.cpp
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    constexpr auto prefix = [](auto&& xs, auto&& pref) {
        return tag-dispatched;
    };
#else
    template <typename M, typename = void>
    struct prefix_impl : prefix_impl<M, when<true>> { };

    struct prefix_t {
        template <typename Xs, typename Pref>
        constexpr auto operator()(Xs&& xs, Pref&& pref) const;
    };

    constexpr prefix_t prefix{};
#endif
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_FWD_PREFIX_HPP

/* prefix.hpp
XC/yyN/rP8Fm5CkyLQBr9bJpJndHILWI1kl2gUbX3DR7X9oCfaYlvMXczs+Vlq0oq8Msqz5P0R/wy2/vuZX5/nTbZHidVtNdVoL6qWLFfpfuQvLUvm10sJ/zFi0/I+tdpwKN01B8niybVJlOrBzVOKqQZ4rZPFlt1mg/1VesIYCg9ZsFdhjcTSK6ys8TEw7x3E9LEBxnlMTSvga1qRVcKjwv47w2SMJ5w/yL5U4uKUhjzcBlp8737RrtoV7DRqIO6fNHnzNnkVoyZ1KwdDUeqfw/5HIHUxJgROzL1hKqXLOea0cIbgYJbjOdeUTh7tGOK5veV6VeuxTglnc7N+fizgwkgIbQM+A/PFX08VIHKZze2SEd+/E/w3OIUkuHUK7zn9jXnGFots/c1w5720MzBry0/tGGl1HUz8+cvks04P7GF2rd8K0rfUJkTnw2HlChWs7ZkC8PJdsTGmmcprrXRCrhfE+XQ8aEX4hJf0RUALidnM2zxuNwtuLjQG7mg2KQmEMg7qFHR0lHiQaz7jGzp73HoWireZQwygGJ2gZKMTjjTGUUbz65teApmuCtbpTViDO616lt5FQ+vXWBYt5AntLXt66IrhQLWPIJUrjqGBUIF294f34Y3UBOD02q7vNCjfTs2fheVJ0XdvJHdr6pa/xvnuCFRtl7avxSrWONDvlodawYTUeyNyMU3qS3NzGeWl0MJYOtgxhOahvi
*/