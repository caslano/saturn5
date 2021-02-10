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
fs7ubUQogOwG+3ueVsXq1hNol+4q0h3DxS2/w8q3tBunT2jtbqd1mERgdcM96jeIPa/Dz9KYYz3LrKZMkVrn9mm71885bVxalbtipxhs8846pjzJCQxCcgIt7iykPeFDLudpdxgNOm+hU3+Q6osiyqNu/9guCczhzX5lJu4eibpxQW+2yTUPY/m9fCKhuSPnGP0rXB++jJyYQ3NxxTERbkmVhbNVMgFrUZFbXXtkpezQik4/fM2Nbxzk0idxyq8xKlxklEH8Wqm5sVTq0Zo7WN2jhjnHAqy7kbZmFscP/1ZKG2b5T1TX2Ib8D1DYGUE20ttZcw0soKoeVr1lZTD41Q3TRjpmqsK532O0OPXcWJH/rTscgCIfXwz7h6ilQSku0BViumo1nN6m888yBKq06Q+yAwj9m83ARqp/2O38+hDVT4tnOXqW+lf+JasfdsSWScSyx3oRPiLg7BAaQF7F+NU33JUuNAed2cCVRjBIY9OvtJWTzhukamSK+x+qETHsk39sdLfpi1arlU1zEQf8pUE1E2R22d4u7UrqlMTcv0wRUfmHkis71bD1h46S75/mLQyqoPBpkviBnzCtn/yjqpozX8qJd8Vb95UqDNOTNz0EWs/nnqsZwZtLN1gtUzyy/E1HvakfbYoc+xSl
*/