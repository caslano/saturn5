/*!
@file
Forward declares `boost::hana::extract`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FWD_EXTRACT_HPP
#define BOOST_HANA_FWD_EXTRACT_HPP

#include <boost/hana/config.hpp>
#include <boost/hana/core/when.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! Extract a value in a given comonadic context.
    //! @ingroup group-Comonad
    //!
    //! Given a value inside a comonadic context, extract it from that
    //! context, performing whatever effects are mandated by that context.
    //! This can be seen as the dual operation to the `lift` method of the
    //! Applicative concept.
    //!
    //!
    //! Signature
    //! ---------
    //! Given a Comonad `W`, the signature is
    //! \f$
    //!     \mathtt{extract} : W(T) \to T
    //! \f$
    //!
    //! @param w
    //! The value to be extracted inside a comonadic context.
    //!
    //!
    //! Example
    //! -------
    //! @include example/extract.cpp
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    constexpr auto extract = [](auto&& w) -> decltype(auto) {
        return tag-dispatched;
    };
#else
    template <typename W, typename = void>
    struct extract_impl : extract_impl<W, when<true>> { };

    struct extract_t {
        template <typename W_>
        constexpr decltype(auto) operator()(W_&& w) const;
    };

    constexpr extract_t extract{};
#endif
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_FWD_EXTRACT_HPP

/* extract.hpp
epa6dzhIesp/Dw/pwBp3l0tFVw2XlHsHk0Ozsjwpyk4ER5P4IIZDEEMpE0PtJCK4iVbGvaeiQylxSgq0s6c4jJIaskipyXbm98oNhh7MD4M/au6DwGDB6d6sTLGC3v85ggAaGewKwpHICn4PWREWWfOVHoEFmhSU9y7DII8PsJFZywusUNMJnkr476UlAgx+6e8UxRT8lD/xC2Kn9m6bENTgkz9Nm3Z/O7HF0tJ8rJ4Tv6D5u9Hne84tPUNrwX/J95PLv8Hb7wd9QHvpWMmVtgWlQZ7SguoIaSUtEkW0SMB11EvZghD2v2JBAAGXgfMScGZhezcP6nR+P6GiJYLcPi0TIOYi6k6h7iewe5SWBJRXUGAC+i5Jp4nBQiktKAXXhSWjptJIgG9QQuFFHce3u5gr1k56i4UHB4UK2MjOHn6LoR+NtdCIqSKWvbfGtOdaIKaia61gItVMb1pmi0V5Tihh/byFhIEwQjNd3ahxMrfY4OlIvc5rzJzZBfX2JrGCnJOYjUm/NtlNq+HNE30v+XzsJaHciKX7uCplUeRYN6Q1MplX2H1EyuOmpb/XMWWAb9KUNnqnZUPoVwp0vNqa9AA4LMfT/BysOrsm01nzNdd8syU7iin/HvLpdWd9vh3ldPkyLvcGVyC7xkY/hGdnNIj3ExalLV0csjVIKHa1Q+YTZNxJ8g+mNHjiGgrqHJuWuhzvymBa7rZFTwtC
*/