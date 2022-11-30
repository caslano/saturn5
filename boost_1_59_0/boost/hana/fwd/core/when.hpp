/*!
@file
Forward declares `boost::hana::when` and `boost::hana::when_valid`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FWD_CORE_WHEN_HPP
#define BOOST_HANA_FWD_CORE_WHEN_HPP

#include <boost/hana/config.hpp>


namespace boost { namespace hana {
    //! @ingroup group-core
    //! Enable a partial specialization only if a boolean condition is true.
    //!
    //! You might also want to take a look at `when_valid`, which provides
    //! similar functionality but enables a specialziation only when some
    //! expression is well-formed.
    //!
    //! > #### Rationale for using `when` instead of `std::enable_if`
    //! > `when` is used to control the priority of partial specializations
    //! > in a finer grained manner than what can be achieved with the usual
    //! > `typename Enable = void` and `std::enable_if` pattern. For example,
    //! > a partially specialized tag-dispatched method will have a higher
    //! > priority than an equivalent specialization that uses `when`. For
    //! > more details, see the tutorial section on [tag-dispatching][1].
    //!
    //!
    //! Example
    //! -------
    //! @include example/core/when.cpp
    //!
    //! [1]: @ref tutorial-core-tag_dispatching
    template <bool condition>
    struct when;

    namespace core_detail {
        template <typename ...>
        struct always_true { static constexpr bool value = true; };
    }

    //! @ingroup group-core
    //! Variant of `when` allowing specializations to be enabled only if an
    //! expression is well-formed.
    //!
    //! `when_valid<...>` is always equivalent to `when<true>`. However, when
    //! used inside a partial specialization, SFINAE will cause the partial
    //! specialization to be ignored when the expression is ill-formed.
    //!
    //!
    //! Example
    //! -------
    //! @include example/core/when_valid.cpp
    //!
    //!
    //! @bug
    //! Using `when_valid` seems to trigger ambiguous partial specializations
    //! on GCC.
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    template <typename ...>
    using when_valid = when<true>;
#else
    template <typename ...Dummy>
    using when_valid = when<
        core_detail::always_true<Dummy...>::value
    >;
#endif
}} // end namespace boost::hana

#endif // !BOOST_HANA_FWD_CORE_WHEN_HPP

/* when.hpp
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
*/