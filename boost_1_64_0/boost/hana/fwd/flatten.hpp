/*!
@file
Forward declares `boost::hana::flatten`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FWD_FLATTEN_HPP
#define BOOST_HANA_FWD_FLATTEN_HPP

#include <boost/hana/config.hpp>
#include <boost/hana/core/when.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! Collapse two levels of monadic structure into a single level.
    //! @ingroup group-Monad
    //!
    //! Given a monadic value wrapped into two levels of monad, `flatten`
    //! removes one such level. An implementation of `flatten` must satisfy
    //! @code
    //!     flatten(xs) == chain(xs, id)
    //! @endcode
    //!
    //! For `Sequence`s, this simply takes a `Sequence` of `Sequence`s, and
    //! returns a (non-recursively) flattened `Sequence`.
    //!
    //!
    //! Signature
    //! ---------
    //! For a `Monad` `M`, the signature of `flatten` is
    //! @f$
    //!     \mathtt{flatten} : M(M(T)) \to M(T)
    //! @f$
    //!
    //! @param xs
    //! A value with two levels of monadic structure, which should be
    //! collapsed into a single level of structure.
    //!
    //!
    //! Example
    //! -------
    //! @include example/flatten.cpp
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    constexpr auto flatten = [](auto&& xs) {
        return tag-dispatched;
    };
#else
    template <typename M, typename = void>
    struct flatten_impl : flatten_impl<M, when<true>> { };

    struct flatten_t {
        template <typename Xs>
        constexpr auto operator()(Xs&& xs) const;
    };

    constexpr flatten_t flatten{};
#endif
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_FWD_FLATTEN_HPP

/* flatten.hpp
4WOxx4FC6TcGf02zJohk8qTZ/FpJzgldMrXrYOXHLe8JxIBDk6u3p6kqMk0pruMGbl33dKmuBWz1MPUUrvnIumhEjqrTWuMBu7a16W3a6p6FEBYLQBTc3YKtTEP/0LUtmfw6YbIadmRi2m3UQ79WfxSHPav0qJSV7eS1DQW5vbEPKtPfWc0T/RT0k4cUg/3IHrSgCSgkcBPFl5RrAPYOBUET/Uc0AksFggduTqQvN50115C6fDgWbraMTxltCUEle+m6xwQc0j5wjs36SCC2QxnhcNNH7AuC/nZ9gKwouGvNZajgOqSws9l/W1rFU1qybE7K7aCx9fuHCxms0fzRN3WPuQOa8CsB6mDf2oQwElW2SUBVnMAPo0EHYw0OG4vhhmU6RpfHmheLWmz4auvYE1r+FxFYg2qRaGiFEMva5Zmik35FpJQbY3FboyNa1HCdoPn/J+Xs6j9WUR8CGtcjU7kzqE49dPsAzbY/2/1XQ7AjHjPgV5AHcvaD3fqunbnbTl49lZtJRE4QiOGGfbQEpq7IDx7A8VZtmqXOMsEVTeu/9WHsgV7qVa4Ueg==
*/