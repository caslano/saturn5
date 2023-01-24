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
3Kdz1l7nRFM5VjsSU3OrgFKUPk91BiuSEIFsBcoT096xmmKVxfTpDzRxlfFSff7mPuw8JDrmKcdfelpAmYJZlwkga7NsWTmOA08mDBXyQA2p+jzzOYpdGNMddmMqyfXV8hDTnKsQLak7/Exf7Ilm2e/WO/t7SdWJJYdLrRHBAYsIiQkdDG+MYbzNU2OMtF9PdbLfslUzTCb4vdNz3L98fNDeOkhCgD1kTNkt11ylK2lLnl0vIcelRI3sPeU4ZZazl6lhtFWmeyeeUp8JOFOLwNbH5OrT/q1zXzaJii5OR0uihoY8PKYWHHb1D1Mqk1C/V90QVX8UaG+tMKzo7Bk7HJHsVmNS584OXlKgi+X26gpumKT70VQHhk6kuMVYw9lHIo3J7FwBRciSSGgEmuTpyoLAJcXYz9ywS86gbpP9+SlQkelfKDmroDgYKwojQVIsCcEtuEPxkIXFw48Hd3cI7rpokODui7u7Q3Bf3C3Y4g6LLdt2OtPOdCrTmfty3+/LN9+5J9QJe1p2rzPq8xpTrANz6RRsabxNTXzydb00oaEL2/lq3RBJxTll1NecjCw0TsU+zu03Vo4ufVz8yRszANaeHnsBXzinOLNiDa264khykeSQYNcipyGrG2mc7+Kj1wIQwiISva/1GwJV6Ea8O158tlUN3oqV1U7lo4yzDYhzEhuHc40PrXCCdzQf7ZzW8B6ALY/ccBrpPixP
*/