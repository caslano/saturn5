/*!
@file
Forward declares `boost::hana::detail::nested_to`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_DETAIL_NESTED_TO_FWD_HPP
#define BOOST_HANA_DETAIL_NESTED_TO_FWD_HPP

#include <boost/hana/config.hpp>


BOOST_HANA_NAMESPACE_BEGIN namespace detail {
    template <typename Algorithm>
    struct nested_to_t {
        template <typename X>
        constexpr decltype(auto) operator()(X&& x) const;
    };

    //! @ingroup group-details
    //! Provides a `.to` static constexpr function object.
    //!
    //! When creating a binary function object of type `Algo` whose signature
    //! is `Object x Object -> Return`, `nested_to<Algo>` can be used as a base
    //! class of `Algo`. Doing so will provide a static constexpr member called
    //! `to`, which has the following signature:
    //! @code
    //!     Object -> Object -> Return
    //! @endcode
    //!
    //! Note that the function object `Algo` must be default-constructible,
    //! since the algorithm will be called as `Algo{}(arguments...)`.
    //!
    //! @note
    //! This function object is especially useful because it takes care of
    //! avoiding ODR violations caused by the nested static constexpr member.
    template <typename Algorithm>
    struct nested_to { static constexpr nested_to_t<Algorithm> to{}; };

    template <typename Algorithm>
    constexpr nested_to_t<Algorithm> nested_to<Algorithm>::to;
} BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_DETAIL_NESTED_TO_FWD_HPP

/* nested_to_fwd.hpp
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
*/