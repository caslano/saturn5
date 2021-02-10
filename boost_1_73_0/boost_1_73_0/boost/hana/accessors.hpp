/*!
@file
Defines `boost::hana::accessors`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_ACCESSORS_HPP
#define BOOST_HANA_ACCESSORS_HPP

#include <boost/hana/fwd/accessors.hpp>

#include <boost/hana/concept/struct.hpp>
#include <boost/hana/config.hpp>
#include <boost/hana/core/dispatch.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    template <typename S>
    struct accessors_t {
    #ifndef BOOST_HANA_CONFIG_DISABLE_CONCEPT_CHECKS
        static_assert(hana::Struct<S>::value,
        "hana::accessors<S> requires 'S' to be a Struct");
    #endif

        constexpr decltype(auto) operator()() const {
            using Accessors = BOOST_HANA_DISPATCH_IF(accessors_impl<S>,
                hana::Struct<S>::value
            );

            return Accessors::apply();
        }
    };

    template <typename S, bool condition>
    struct accessors_impl<S, when<condition>> : default_ {
        template <typename ...Args>
        static constexpr auto apply(Args&& ...) = delete;
    };

    namespace struct_detail {
        template <typename ...>
        struct is_valid { static constexpr bool value = true; };
    }

    template <typename S>
    struct accessors_impl<S, when<
        struct_detail::is_valid<typename S::hana_accessors_impl>::value
    >>
        : S::hana_accessors_impl
    { };
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_ACCESSORS_HPP

/* accessors.hpp
Xs+muO2Px/3RdI7rn+iP5kns13B0xq3XbOZBq9pTYHMPvayNJrXx/LiRdzp72hamUYRu6p4IFJu6V3XTRpnuktnkXFyMZnxVvMUyVMkoWyCtuEiWu2FDBJ+94Q950GoF87oQ97aJJnxjEbLcaOSHb6TBmWzj/95Raf8PUEsDBAoAAAAIAC1nSlL8wnQBGgYAABsQAAAdAAkAY3VybC1tYXN0ZXIvbGliL3Z0bHMva2V5bG9nLmNVVAUAAbZIJGDFV/tP20gQ/j1/xTRIRwJuXtAeNC26NCRt1DQgkqrlAFmOvY736ngt7zqQK/3fb2bXzgNI00qVzih+7M588+28dqnu/b6rAHuw9bL1z8YLn1rjPBH/MFc9LW3b92D+UOsan9uMVGGpcm+XYbvKPZS0ip1ZeU3vtr3N0DVxo1uVNK9tesURVCPNtojnCZ8ECkrtMtSPj4/gOTRqjZoFp07EWQhDxaIxSyYWvPb0yF+Bc3dXkezEAqbACSsZ1CjgEqTw1a2TMMD3kLsskswDR4LHpJvwMX7wCFTAwOchg/bZ+WVv8M6C24C7AYHMRQoyEGnoQeDMGCTMZXxmMGInUSB8VEdwj0uFgKniIqqgbQaKJVNJGGTeCaUAZ+bw0BmjIUdBoFQsX1WrbpqEyL7q
*/