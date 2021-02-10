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
vDnMcvD6/hKtyuRSjbPHtLBHOBSCoFi8VhyiXXU5CL3Z9tYrhXqu5iXOQYuuUfGgMxKV5HNUTEEKKMzQN4jNgz++ketFWYrljUpuftaVI5UxabCmTFHJKs0TZ6T7teuh97zqRtWSKEpAmZqtqAFA7SpHRkl8pF6rlk5MIYmiBxjKv3EJsqIXJESVNlyvGy03AMPOTz85TxvOt479ov1HSbfQ4kaCmDvzk6mkPHPR86eumqhOR7D96C1TnRZ6Ci3QH1lXUCtjtrIYNbOV38hsycyLFmyMYyk232cV94L4w5y4mckNP9cGl+Pas1qvv6GWQThNJ+MeuTFQaMmfnutBoJuzclRrqIc/5YeRzSuJYCTxiKUbTce9/tnAHYNe03Q0ItR1UIFpTNJHnT7NhGPITZStyvk5A41EgEKzi0mIcoE6i4V6/czvl7qimpeY7tBFy9JciEn3hbHDymzF7ONIEQjwPsXO31Q8OGSwbhIG9bsGsNUQjznhq9xRLy9FqAsj9GBaplaWU30zwgwgdygRTvCop3N+0VcXSdiuvQ457OXIxXcPZixip56Dg3Pxttns0mkMQLXgtB/ucdvocb+6w/0t+9veur+bC6HiTnp7v/sqP7S+NTIdTJQ7KSpaQDuspxOKyOXsVezTfRGV
*/