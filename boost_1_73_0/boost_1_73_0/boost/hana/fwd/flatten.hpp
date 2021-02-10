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
ml22+OLTS0dAo9uEg6OjQ/gFnu4/PWjBqeVR4sJIEG9K/MsWHNtq5A/Hur3d4+SkBUSA5e6FpsYO5cDZXNxYPgH87tIZ8TixweJgEz7z6RR/oR4Ih8CcugS6g3cf+xevW3Dj0JkjjXxhAXCHBa4NjnVNwCczQq+1jYXlC2BzVEfjNuUCDQaCMm8PfRMQxL/i0oZ0b7mcgXVtUdeaoiNLgCPEgr9st2eB7yL6ts1mvD2Lpr/niKvlTD4iiCvrC7CFAMEg4KQFUrIFV8ymc3lFQnBwEUxdyp1WjAZdeXab+cCJ60pbqEcJ17AJjEJ6WlIMFoiYCnnhzOPS1Y3DrlKCyKO0Mg98Dx0hDyhkM6S5BYFnE18Jq5lHLkJOFcG5oYnx2sA8BAPbnRH0R9swtTjlLfjQH58NJmP40BkOOxfjjzAwoHPxURp70784xdBTdOYDuV34hKNzH+jVwqXEDn1u7tPe2npCvZkb2AS2ZfRMTkSw2HO25Y05ptacesTG4uhfjHvnZnfw9l3/vDdsws5O4mbg0VvTbCodHIWzzvueedEb9/EHNc2zrScAkZ9jjwjUE23q7TknW0+Ih3FPaXaG7zqm0k0rWv7CakvVhF54hfYurIKUGCNsoKaqEcOfk/75KcbRxAhcnPdGI7ML
*/