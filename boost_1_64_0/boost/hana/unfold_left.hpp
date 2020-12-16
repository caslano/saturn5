/*!
@file
Defines `boost::hana::unfold_left`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_UNFOLD_LEFT_HPP
#define BOOST_HANA_UNFOLD_LEFT_HPP

#include <boost/hana/fwd/unfold_left.hpp>

#include <boost/hana/append.hpp>
#include <boost/hana/concept/sequence.hpp>
#include <boost/hana/config.hpp>
#include <boost/hana/core/dispatch.hpp>
#include <boost/hana/empty.hpp>
#include <boost/hana/first.hpp>
#include <boost/hana/functional/partial.hpp>
#include <boost/hana/optional.hpp>
#include <boost/hana/second.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! @cond
    template <typename S>
    struct unfold_left_t {
    #ifndef BOOST_HANA_CONFIG_DISABLE_CONCEPT_CHECKS
        static_assert(hana::Sequence<S>::value,
        "hana::unfold_left<S> requires 'S' to be a Sequence");
    #endif

        template <typename State, typename F>
        constexpr auto operator()(State&& state, F&& f) const {
            return unfold_left_impl<S>::apply(
                static_cast<State&&>(state),
                static_cast<F&&>(f)
            );
        }
    };
    //! @endcond

    template <typename S, bool condition>
    struct unfold_left_impl<S, when<condition>> : default_ {
        struct unfold_left_helper {
            template <typename F, typename P>
            constexpr auto operator()(F&& f, P&& p) const {
                return hana::append(
                    unfold_left_impl::apply(
                        hana::first(static_cast<P&&>(p)),
                        static_cast<F&&>(f)
                    ),
                    hana::second(static_cast<P&&>(p))
                );
            }
        };

        template <typename Init, typename F>
        static constexpr auto apply(Init&& init, F&& f) {
            decltype(auto) elt = f(static_cast<Init&&>(init));
            return hana::maybe(empty<S>(),
                hana::partial(unfold_left_helper{}, static_cast<F&&>(f)),
                static_cast<decltype(elt)&&>(elt)
            );
        }
    };
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_UNFOLD_LEFT_HPP

/* unfold_left.hpp
+27n4GV4f4B5Sym/Zb5SunEVHwdSOjNP6/O6ok/Cxa+uRc82a7GcKjLvmwreOmTJqqxlYGLCN7NcmyjvE7Rw3namYtP3WN0tv8cbLjFwdq7uh53iRqZ98EZIC8ATkMFqA2k3J7SwYz+eL7EMTr8TzgIxV4SDzUoITkLaRyONGxetbFdP4j4q0X6GNEA7PriGGAY3/258bgHo+OA8mCbBYzlYDLPcnTL9yvF1V2bHeG45/m6BlSK2nx3nyWBVRDyONyKGCWzU3OYIDJNNlABSGHO257yEU17QmHLfRefgnbN4UKuuy7g+/4YfVuUT4J+dJblge8FchShDlZJSwAoR4vZzGZ/7D/wweZ8SoYPcn19cyhyencHUGE5rgDGT++0rSI/Gbcqzk9/jN76bz6CRL573MA8h0uBe0kcXG4DZLXl+jjx+RD1IHDQ/6K+WPM/g8AYTfZ51/BXrGZA1YFtunE2HZSznUd9DHuiTazsIxkx4HjfhycjKNOfpE79HsVUCX4HFcZp19ciXeRAkBTF5Nld4Nq5k2guRFlFCIi33x/6qbuicDZ7r+JJEp/1BoFDwOzuJfPG0UmD2vGZ8jqBXqb/PEHs+0iMZME/PIagnsiHWyTu/N82XSzIpkpy574180myFCzRjt/M7y/SPfI9gpoxHngArj/IfR3rCuDmEtZ3o/9SUHqNTlvTPTukz2E8s9rAdn0d6uuDbsU6S/MH5XX/1eyt5dqNQ9Yxno67vr/LQjwL5frrCRz4MUuYvVvjSx0HysP468lxZ/bbIHPA75Ck+UJyn/7ykP7MLFPLt3zRimflOQJKZ8f0saXeMtGeYOL0DetXhfB/H3V0TLb1vxNu5V3oeR3y8AEGQLGzTAwhPQrLKTMjzsMyzN0+34vDOYHN2Rtp9geqJE2TE/jnJ9EuZHkcuMmC/PDnTEzx++Cxz+3iixVVmY4kHpfNzB6srpFsIMrk8izIRWT53GY7V7UzfP4Amza/PDLnNz0309DwuX2ERh9kL++VFqzwRgo7yXF3liSOM8hyt4dk7mi8oz+mE58Vr6vPKKc+a+rx2yrOmPq+f8qypz5vJ+0wDJucHRp63EZ40/q4e7b54sUHyHr8r8aSOWcB+CvcQH4o0ZRtjFdBePFtAU+CEMqJxBmyrjaP8Pj9BeOM4AUCmfejaPA98m9Dj7EoBvEju4R+u8sXvOLDRtv2M8i2WaHFhD4GYcpgHBDYolCl/aIALQ/coz/4v/HFDSPIfv5Dyx8pmxhy2vtjI+5n9f6cbOuto/uK4EEz1v2Qqs8p7hvtdsm/deemVw9kZzEOZtrGkNQdnW2f7OuJ4xzUwn2UIj4y4ZTUU8KyNTGeEXoP5U8B4BAVI94S+CeO5DtUj9ENCjyHsiSHX8ZVlHf04CwV4ywXeLb6u5BHnpxAIl1nNPpb1JsIXpqbEgWW9bdIf1y/gRiQUBXNb1vEewjPMXz72BuzNH5bPEIS+VLA9D3xRFfQt+ulRXeHAwq8/A9ZngXuSgOBPbN8nCZ8/OHipgAE0Pzow4cuFsvGM8usbkHe9G0NLcB7/JcHjjBMLWWP/QGh5Xo5wOCQP918Iz3T/8o9Ic2LLx70iDMq4zTrA88wPpvS4x8by73PLDaCDhX78VsZQHzDDzA7O0F72wUdP7Jy+952vGdwRvLyIbCC4SZ+kMiLEBDrJVSP/x7sC+D+gXRCb3a+LczKX3HppDES/ZbOmtLkORxgbXdRBMm2srL3uWFobY4DUETrWhwU43tsfnF7dDZg5aLO4UPpqdk3TBAijkBsVLl8OT5fgb3P0jaUynumu7mQrBHMZ+QIOnQT86jzHB3kqxxumrfDaiZY9g9Zuj0T2lRg=
*/