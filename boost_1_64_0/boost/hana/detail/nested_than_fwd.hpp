/*!
@file
Forward declares `boost::hana::detail::nested_than`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_DETAIL_NESTED_THAN_FWD_HPP
#define BOOST_HANA_DETAIL_NESTED_THAN_FWD_HPP

#include <boost/hana/config.hpp>


BOOST_HANA_NAMESPACE_BEGIN namespace detail {
    template <typename Algorithm>
    struct nested_than_t {
        template <typename X>
        constexpr decltype(auto) operator()(X&& x) const;
    };

    //! @ingroup group-details
    //! Provides a `.than` static constexpr function object.
    //!
    //! When creating a binary function object of type `Algo` whose signature
    //! is `A x B -> Return`, `nested_than<Algo>` can be used as a base class
    //! of `Algo`. Doing so will provide a static constexpr member called
    //! `than`, which has the following signature:
    //! @code
    //!     B -> A -> Return
    //! @endcode
    //!
    //! Note that the function object `Algo` must be default-constructible,
    //! since it will be called as `Algo{}(arguments...)`.
    //!
    //! @note
    //! This function object is especially useful because it takes care of
    //! avoiding ODR violations caused by the nested static constexpr member.
    template <typename Algorithm>
    struct nested_than { static constexpr nested_than_t<Algorithm> than{}; };

    template <typename Algorithm>
    constexpr nested_than_t<Algorithm> nested_than<Algorithm>::than;
} BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_DETAIL_NESTED_THAN_FWD_HPP

/* nested_than_fwd.hpp
BgWrt+iEfJhthQmc212CPwMtKqfrjG7WoW8jnDw+J/L/K+UctDHKVc3Uoyb0P0WX7IUJI+ffFEyiNoJg28+VQL0q7UZ4Gdn3I4V3cPak/SSEgBqjqgCzrvh0/GDXvyO/9dAj4QQLZnNBPtlHV71C+Rr9mw/E3nMkOdqrSlJvJTxGyM6uO/VJ96kNQiE9T4hvVxqZ+JhLhA4CXzwYh8xKGLStHEH+jviMPHhV8XNw25Gu5gfSi3Wa1t4d4lQds678ER0CkQfv54TO1aiJmmABE9WDYPqhe+zgb9laAYfPF/FVNmyMYI0K/dSJ4H3sVW4hAioc79mpbZh4kJ4SB/iqZeYJZnG3WT+rK5B6bU4i88CwW7kNE/boQ9OU145TTebmBEB3ZeyeaJM9x985HIDjsyPp2VSR71vqce1kTI7XlEXRDPswNwDKEpQnjmAyMip8MnPeG8JHg0+xlyYF1CqR+Z+FwHJfiGqsiW+zHSZLvRV8lTLl5c/ZKeDaFyQ3af/CWd0DE6YQb4bzGuTCy2sKj/soTIo0PJmK4UzW2c9jAo3kdq9JMVRkHzS0Ng==
*/