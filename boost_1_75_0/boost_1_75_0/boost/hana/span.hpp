/*!
@file
Defines `boost::hana::span`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_SPAN_HPP
#define BOOST_HANA_SPAN_HPP

#include <boost/hana/fwd/span.hpp>

#include <boost/hana/at.hpp>
#include <boost/hana/concept/sequence.hpp>
#include <boost/hana/config.hpp>
#include <boost/hana/core/dispatch.hpp>
#include <boost/hana/core/make.hpp>
#include <boost/hana/detail/nested_by.hpp> // required by fwd decl
#include <boost/hana/detail/first_unsatisfied_index.hpp>
#include <boost/hana/length.hpp>
#include <boost/hana/pair.hpp>
#include <boost/hana/unpack.hpp>

#include <cstddef>
#include <utility>


BOOST_HANA_NAMESPACE_BEGIN
    //! @cond
    template <typename Xs, typename Pred>
    constexpr auto span_t::operator()(Xs&& xs, Pred&& pred) const {
        using S = typename hana::tag_of<Xs>::type;
        using Span = BOOST_HANA_DISPATCH_IF(span_impl<S>,
            hana::Sequence<S>::value
        );

    #ifndef BOOST_HANA_CONFIG_DISABLE_CONCEPT_CHECKS
        static_assert(hana::Sequence<S>::value,
        "hana::span(xs, pred) requires 'xs' to be a Sequence");
    #endif

        return Span::apply(static_cast<Xs&&>(xs), static_cast<Pred&&>(pred));
    }
    //! @endcond

    template <typename S, bool condition>
    struct span_impl<S, when<condition>> : default_ {
        template <typename Xs, std::size_t ...before, std::size_t ...after>
        static constexpr auto span_helper(Xs&& xs, std::index_sequence<before...>,
                                                   std::index_sequence<after...>)
        {
            return hana::make_pair(
                hana::make<S>(hana::at_c<before>(static_cast<Xs&&>(xs))...),
                hana::make<S>(hana::at_c<sizeof...(before) + after>(static_cast<Xs&&>(xs))...)
            );
        }

        template <typename Xs, typename Pred>
        static constexpr auto apply(Xs&& xs, Pred&&) {
            using FirstUnsatisfied = decltype(
                hana::unpack(static_cast<Xs&&>(xs),
                             detail::first_unsatisfied_index<Pred&&>{})
            );
            constexpr std::size_t breakpoint = FirstUnsatisfied::value;
            constexpr std::size_t N = decltype(hana::length(xs))::value;
            return span_helper(static_cast<Xs&&>(xs),
                               std::make_index_sequence<breakpoint>{},
                               std::make_index_sequence<N - breakpoint>{});
        }
    };
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_SPAN_HPP

/* span.hpp
hZXX1NFnryzA/JMeOuj3YaOSjIH4FFi9GwzdqhDz0MEf42jAJntzwf+VQblTZ+TbsvK+hL/kf+avp5k/zFJMa44yMUhSoqE3SsEuxWC7BAI0Cx5MEqcDsHCwNWP5VJ1BqOA3NAib8izMBkHgoLloAcvzMezr5jYYQod4JQ+wjuGFoHd1/QrfnVsq7WGFh/uX9lDxv1itgQhZrWOwbeuObdueN3VrJu5WWvfq/221jvn8f16tuR4AIqzWXMuu/3XLdas1bvmyohVHVdObG2cshmILkFd3bKC5hV/KSvqZ207Aw4haG4QFqHDksNilaHJsxGUh8UjZ7lF1Y6PDa79OAyu8sqO6ymp5C86Ps0AWrspS2UNdyVvmchHrHQ8y0L6Rp7RO90L2q2QBGmllRPrHq+g+HOEquyB5WadPoKyoEilXr5kA3Y+AekPS+1uhex91lTWp9wWtISXduXo1tui+HdRzTi9tiu6F6iobpa3GmJ7SzIZS8HWZ0obejrw7UnZ2HJ6LQq7XqGPxM5CSyD0711la67fgTnAO57igr5dUsjn7L5bUSq4mFwaRgAdBtD4eIhtyO2Tt5T6d60zcinl8jINdANOqtqxqFp8KJgbulhxPwGC2mzOa4joNMHoGVodInU2kbxPYRl2GdcYf6fgYso26gNaZy422UUp7PcaUsn2bUVSIKQ372lM6183zRK4ZvQYYl5LKjdf7H9GS
*/