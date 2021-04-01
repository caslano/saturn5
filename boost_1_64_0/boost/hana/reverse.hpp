/*!
@file
Defines `boost::hana::reverse`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_REVERSE_HPP
#define BOOST_HANA_REVERSE_HPP

#include <boost/hana/fwd/reverse.hpp>

#include <boost/hana/at.hpp>
#include <boost/hana/concept/sequence.hpp>
#include <boost/hana/config.hpp>
#include <boost/hana/core/dispatch.hpp>
#include <boost/hana/core/make.hpp>
#include <boost/hana/length.hpp>

#include <cstddef>
#include <utility>


BOOST_HANA_NAMESPACE_BEGIN
    //! @cond
    template <typename Xs>
    constexpr auto reverse_t::operator()(Xs&& xs) const {
        using S = typename hana::tag_of<Xs>::type;
        using Reverse = BOOST_HANA_DISPATCH_IF(reverse_impl<S>,
            hana::Sequence<S>::value
        );

    #ifndef BOOST_HANA_CONFIG_DISABLE_CONCEPT_CHECKS
        static_assert(hana::Sequence<S>::value,
        "hana::reverse(xs) requires 'xs' to be a Sequence");
    #endif

        return Reverse::apply(static_cast<Xs&&>(xs));
    }
    //! @endcond

    template <typename S, bool condition>
    struct reverse_impl<S, when<condition>> : default_ {
        template <typename Xs, std::size_t ...i>
        static constexpr auto reverse_helper(Xs&& xs, std::index_sequence<i...>) {
            return hana::make<S>(
                hana::at_c<sizeof...(i) - i - 1>(static_cast<Xs&&>(xs))...
            );
        }

        template <typename Xs>
        static constexpr auto apply(Xs&& xs) {
            constexpr std::size_t N = decltype(hana::length(xs))::value;
            return reverse_helper(static_cast<Xs&&>(xs), std::make_index_sequence<N>{});
        }
    };
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_REVERSE_HPP

/* reverse.hpp
oX70CEzF4SVDyRO3GyDVNWl1VPm3eCfSSJ2mgc9Sv2P4MazmBrv9yP6CUkTcGxjh2fhPzmnC2y9na365RDF4l9PMxdiJMM7q14gEXYGlqYTW8FmFgA82EjnOmYHp5/ifem5zgrhMnp5o5r5GnlpEIR0gSt+oC51qInLlQPs+MRhEt/Co9lXmaSwNKfl+VLHwALXBC/tVKsOr3PCzmolAmhzHbvE+4iRV7iWXyATBspHE6PWsdEN8ZC/3VpAUriz+1U8O3bqzs9u1TKS4MaatGHb5SE/eVmF1q5Fas7C0HUVgqj8RfAQa/hijxviRljwjyjVqabD7FBuNiwOhgSEi0mYRrWMQM9h4Pw4u4ef2L+q5lgQAk0Wa32WZtT6oS7TR9P1jUeErSjArNHtgoeh8+m3kjp+FOFL5+mbz7G34nuSO7YOiV08eiFEgPk7CpwvcQE6P67qBchRvz9M1+AqzxSnR3VdjowXCHNLSA/F4K+HFWmQd700V88cFNEZ6ZtaS4qeVJkWbNlkAMwLPv4xSRQ10etblXKCUbPQgO+XbD9Bpko8VlwzCDQeU7Q==
*/