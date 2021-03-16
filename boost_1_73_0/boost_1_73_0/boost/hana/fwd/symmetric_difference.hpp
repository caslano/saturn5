/*!
@file
Forward declares `boost::hana::symmetric_difference`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FWD_SYMMETRIC_DIFFERENCE_HPP
#define BOOST_HANA_FWD_SYMMETRIC_DIFFERENCE_HPP

#include <boost/hana/config.hpp>
#include <boost/hana/core/when.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    // Note: This function is documented per datatype/concept only.
    //! @cond
    template <typename S, typename = void>
    struct symmetric_difference_impl : symmetric_difference_impl<S, when<true>> { };
    //! @endcond

    struct symmetric_difference_t {
        template <typename Xs, typename Ys>
        constexpr auto operator()(Xs&&, Ys&&) const;
    };

    constexpr symmetric_difference_t symmetric_difference{};
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_FWD_SYMMETRIC_DIFFERENCE_HPP

/* symmetric_difference.hpp
m9EaG/yrka1hYJact7lhHhU772zhcc4X5mGyc3qwHGg2tJ82o7nQ4fSkkvp4U6nTfENdsLe5u62zs72zNdCcaJrX5M9kSV7KFHJxzXxtJJsW1jXVk//7Bpv8pCjejBcMNodbWgKBJR29zU315H9+/l93WpM/T4aWPtBULwLMaw0HOwKd7R3NfdEAep/fvFBPW1ugJRhqbrV5Gjp7Wtq623t6mkNB4VPVcCo2pLXEDA2du/MTdyK+Ok/fH5efmxk=
*/