/*!
@file
Defines `boost::hana::zip_shortest`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_ZIP_SHORTEST_HPP
#define BOOST_HANA_ZIP_SHORTEST_HPP

#include <boost/hana/fwd/zip_shortest.hpp>

#include <boost/hana/concept/sequence.hpp>
#include <boost/hana/config.hpp>
#include <boost/hana/core/dispatch.hpp>
#include <boost/hana/detail/fast_and.hpp>
#include <boost/hana/tuple.hpp>
#include <boost/hana/zip_shortest_with.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! @cond
    template <typename Xs, typename ...Ys>
    constexpr auto zip_shortest_t::operator()(Xs&& xs, Ys&& ...ys) const {
    #ifndef BOOST_HANA_CONFIG_DISABLE_CONCEPT_CHECKS
        static_assert(detail::fast_and<
            hana::Sequence<Xs>::value, hana::Sequence<Ys>::value...
        >::value,
        "hana::zip_shortest(xs, ys...) requires 'xs' and 'ys...' to be Sequences");
    #endif

        return zip_shortest_impl<typename hana::tag_of<Xs>::type>::apply(
            static_cast<Xs&&>(xs),
            static_cast<Ys&&>(ys)...
        );
    }
    //! @endcond

    template <typename S, bool condition>
    struct zip_shortest_impl<S, when<condition>> : default_ {
        template <typename ...Xs>
        static constexpr decltype(auto) apply(Xs&& ...xs) {
            return hana::zip_shortest_with(hana::make_tuple,
                                           static_cast<Xs&&>(xs)...);
        }
    };
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_ZIP_SHORTEST_HPP

/* zip_shortest.hpp
Bub07H/ZYPOOc3t2v4y+fo/fwoOeIpREz2Yqfsco0tHZP18/a0Ms+VsVHGPDhsVuaL/UEp1n7xulzbNtrwt6EFB2tYXbGQ+DuIsZQgnRDNfqGX4TkwE3hMVmaI7JMF7PcOfrJPFfjTW+lOKUspISJ/C9Qid0j3SY1Y+M3Ut/+0i+6qGdaYWkZUSFHAPgkk4e1fOfWkob7G+K6vnJu8+n5++u+A8b7LWt9XFDKvOxlfT9UdOH6vsdVm1N75lMNJFfX/8O0uCvpnNbJ23JVhz7WH08RYe14whQKtpx5YPFLn7QSW1x8Eb9OLqKn7QLmUA/IIbH7BF0FvKSUtHCgzQTL3kJJTrHYeIlFE5n4lncZH89ddRhVdrveTSH4h9befiQIoZOS7iGByhd4cmQ0GwKKYsBFYupUmNd2kKKy6r14haEpkoMhwmu2UULfi5FL3hUPRbsBObi5KkP77LNh0HY9D2OfGqOxCpXHcfEmjg8DyA0TPTjcXq7enL+11CkcpgT3J7eHB7hcjtMLmoRBu9Y22RVh4e334T7ObavnIMrS1L7inDhDLWdL/r4xOozaOzzJagfd/nQgY9wgVAcIzRsrNuJylIxivAFx9Y2WBXHdrUKQcpMEGs+xChzTPBNkJnJN5Yz5Kt3InOsL1ELXu06jN9Px0u3unX7ibDJ2uw4hkE6urZh3DhAL0YGkdqYHNJcxGiOLDdH58j64doc
*/