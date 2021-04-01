/*!
@file
Defines `boost::hana::empty`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_EMPTY_HPP
#define BOOST_HANA_EMPTY_HPP

#include <boost/hana/fwd/empty.hpp>

#include <boost/hana/concept/monad_plus.hpp>
#include <boost/hana/concept/sequence.hpp>
#include <boost/hana/config.hpp>
#include <boost/hana/core/dispatch.hpp>
#include <boost/hana/core/make.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! @cond
    template <typename M>
    constexpr auto empty_t<M>::operator()() const {
    #ifndef BOOST_HANA_CONFIG_DISABLE_CONCEPT_CHECKS
        static_assert(hana::MonadPlus<M>::value,
        "hana::empty<M>() requires 'M' to be a MonadPlus");
    #endif

        using Empty = BOOST_HANA_DISPATCH_IF(empty_impl<M>,
            hana::MonadPlus<M>::value
        );

        return Empty::apply();
    }
    //! @endcond

    template <typename M, bool condition>
    struct empty_impl<M, when<condition>> : default_ {
        template <typename ...Args>
        static constexpr auto apply(Args&& ...) = delete;
    };

    template <typename S>
    struct empty_impl<S, when<Sequence<S>::value>> {
        static constexpr auto apply() {
            return hana::make<S>();
        }
    };
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_EMPTY_HPP

/* empty.hpp
akjsurlNDZI6eT4tMcLfXa2urVwcNcCelEDzZVQmJit76k3EJCT+QK/WX8o5qzFJVyB1eZZ3mRrUwMjsLbrQWT0Ec/GAA/AIHDGsk7V+xM0tc2gG9dAgbD3yqM7OVaePGievRXThqyv65hSeA6PmFI4sjQ2/5JuymxhxSCJfkcVDXmXl2L3QSIm/pp63dC3tRFLmjHZ86+Vod5977YWjFNEtZzCvzQGw50e+MbmXRIiASxBsdHq/4rwk4uJYiPs8O9ct8zEolDjnY50lxfJnNMD0S2E+wYackPCBwYF9IMqTjtqbmSCq+hHRTURgo4IGBH1Kf2/QAx9VLDtwsiD4TX6xw/Sb6nHjM4dsOnh0W4dVPDnDthHY0gadVIQSJkRw9iVFhG+Yue8DdLKl+8wJxEwdRZdUsNMst7KJtQS6RZNaAYhU1Z58FfnKdPfPUuCnvvxtjQaq8AWAxd108LwVDMjTTi9ZFUJwER+j/I+RQFe9b3zIs0jr3pdlHYpjFUMB/KQGI0EX1suKSjWH2N8cV7vk94LnAirWKK5qNuKYp6PbC6O5wTBrlgnbmA==
*/