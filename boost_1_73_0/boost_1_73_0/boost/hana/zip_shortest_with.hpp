/*!
@file
Defines `boost::hana::zip_shortest_with`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_ZIP_SHORTEST_WITH_HPP
#define BOOST_HANA_ZIP_SHORTEST_WITH_HPP

#include <boost/hana/fwd/zip_shortest_with.hpp>

#include <boost/hana/concept/sequence.hpp>
#include <boost/hana/core/dispatch.hpp>
#include <boost/hana/config.hpp>
#include <boost/hana/detail/algorithm.hpp>
#include <boost/hana/detail/fast_and.hpp>
#include <boost/hana/integral_constant.hpp>
#include <boost/hana/length.hpp>
#include <boost/hana/take_front.hpp>
#include <boost/hana/zip_with.hpp>

#include <cstddef>


BOOST_HANA_NAMESPACE_BEGIN
    //! @cond
    template <typename F, typename Xs, typename ...Ys>
    constexpr auto
    zip_shortest_with_t::operator()(F&& f, Xs&& xs, Ys&& ...ys) const {
    #ifndef BOOST_HANA_CONFIG_DISABLE_CONCEPT_CHECKS
        static_assert(detail::fast_and<
            hana::Sequence<Xs>::value, hana::Sequence<Ys>::value...
        >::value,
        "hana::zip_shortest_with(f, xs, ys...) requires 'xs' and 'ys...' to be Sequences");
    #endif

        return zip_shortest_with_impl<typename hana::tag_of<Xs>::type>::apply(
            static_cast<F&&>(f),
            static_cast<Xs&&>(xs),
            static_cast<Ys&&>(ys)...
        );
    }
    //! @endcond

    template <typename S, bool condition>
    struct zip_shortest_with_impl<S, when<condition>> : default_ {
        template <typename F, typename ...Xs>
        static constexpr decltype(auto) apply(F&& f, Xs&& ...xs) {
            constexpr std::size_t lengths[] = {
                decltype(hana::length(xs))::value...
            };
            constexpr std::size_t min_len =
                *detail::min_element(lengths, lengths + sizeof...(xs));
            return hana::zip_with(static_cast<F&&>(f),
                hana::take_front(static_cast<Xs&&>(xs), hana::size_c<min_len>)...
            );
        }
    };
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_ZIP_SHORTEST_WITH_HPP

/* zip_shortest_with.hpp
29IjlXvY+DGMSLUpIASbeKP2mgiY0/3hAHOfRSuDNL2JOiYXYIbxTZtcvaMoYQVs0t6y4s11FdwDT6nywA8q6l5GhlCEOAGsqFKez++Qw0aEMkQ6yhwa92F3uSVn1JQTunWnrF1idi8jAKyOah5ibVKHLVfJV/UnnXokrdijs2H9B52IkHe++IHotPn6p4oHIo4EAhbrxZezPuwPyaCXcVauQTKdDmIJ/uVEdCaT7QjDv103c5O8QVXGdx3UzaEqiRQcdu7ZJ0jLWi9YSF19ncvJbIwRingfET3FnYJlm9tA9R8k6DKB3nJ5zifsKsP4wcyFLvdS3mMu7826tBF99c23O98ofDkM0eyMKE8TlaUr/bN+zJFSMPSIIGRoPEgqmBlMIdXQufoi2Q36eFqANSy+jUci2aQbJiY1G4XSoIT34lvxMoO+kPFlTFcb0moUf8S8qHKu3I0WRr1vb+H/traOaO0WiDSy5e9fHB4duEWsVFofYnv5E80eXyCX52u3Cws7GrbTkQafI8hBuytR7Q1Ffpg7LEbX6VBcjJbA/N2RP2wRUMdmkzVPSomq/Vgj/9K/DcMdHe6fNvMsSpc2St7hdnq3s/VX5N6rI9cnN++6SQKG2HwyuNuQ/4qTsepZKyxQK+nNy5c739Wf
*/