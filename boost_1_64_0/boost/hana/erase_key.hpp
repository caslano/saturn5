/*!
@file
Defines `boost::hana::erase_key`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_ERASE_KEY_HPP
#define BOOST_HANA_ERASE_KEY_HPP

#include <boost/hana/fwd/erase_key.hpp>

#include <boost/hana/config.hpp>
#include <boost/hana/core/dispatch.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! @cond
    template <typename Set, typename ...Args>
    constexpr decltype(auto) erase_key_t::operator()(Set&& set, Args&& ...args) const {
        return erase_key_impl<typename hana::tag_of<Set>::type>::apply(
            static_cast<Set&&>(set),
            static_cast<Args&&>(args)...
        );
    }
    //! @endcond

    template <typename T, bool condition>
    struct erase_key_impl<T, when<condition>> : default_ {
        template <typename ...Args>
        static constexpr auto apply(Args&& ...) = delete;
    };
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_ERASE_KEY_HPP

/* erase_key.hpp
6AWD4AoY/YQMxP1BEAgDESAPFINqUAcaQRs4CjpBD+gHw2AE3Aa+S4SYCkJBDDABK8gGTlALGkAraAcdoBv0gSEwBgKeEiIYRAEjsIBMUA42g3rQBFrAIXAcDIIrYBSIpUIEgTAQARaDZJAB8kA1aAR7QRs4CjpBDxgGI8DXKEQomAesIBsUASdoBq2gG/SBa2AMGGLRdxAMwkEUMIJMUADKwWZQD5rAIdAFesEguAJGgYhD/8FikAHyQDGoBnVgL2gDR0En6AH9YBiMgNvAN16IqSAUzAMxwASsIBsUASeoBQ2gGbSCdtABukEfuAbGgMEkRAAIBuEgChSActACDoFBcAWMApEgRBiIAItBMsgAeaAONIKjoBP0g2EwAm4D30T0HYSCeSAGmIAVZIMi4ATNoBW0gw4wBK4BQxL6CoJBOIgCRmABmaAAlIPNoB40gRZwCBwHXWAQjAKRLIQ/CAJhYDHIAHmgGFSDOtAI9oI2cBR0gh4wDEbAbeBrxrhAKDABKygCTlALmkEr6ADdYAhcA2PAkCJEMAgHUcACMkE52AyaQAs4BLpALxgEV8AoEMuE8AdBIAxEgGSQAfJAMagDjWAvOAo6QQ/oB8PgNphqESIUzAMxwASyQRFwglrQDFpBB+gGQ2AMGFKFCADBIBxEASMoAOWgHjSBFnAcdIFeMAiugFEg0oTwB0EgDCwGGSAPFIM60Aj2gjZwFPSAfjAMRoBvOsYBQsE8EANMwAqygRPUgmbQCjpAN+gDQ+AaGAMGqxABIBhEASOwgExQDjaDetACDoEu0AsGwRUwCsRyIfxBGIgAi0EyKAbVoBHsBW2gB/QD3xXoP5gHYoAJWEERaADNoB10gG7QB4bANTAGDCvRbxAMwkEUMIJMUAA2g3rQBFrAcdAFesEVMApEBvoNwkAEyAB5oBhUgzrQCPaCNtAJ+sEwGAG3ge8qIUJBDDABK3CCWtAAWkE76ADdoA8MgWtgDBhWCxEAgkE4iAIWkAkKQDnYDOpBE2gBh8Bx0AsGgVgjRBCIAItBBsgDxaAa1IFGsBe0gaOgBwyD22BqphChYB4wASvIBkXACWpBA2gF7aAD9IEhMAYMWUIEgGAQDqKyxL3Pvc+9z73Pvc+9z73Pvc+9z73Pvc//8XlI3BfoJYToxUsXiki3JqStXGnJjS0vd/9+vhBiFuWWn7vluevtztwqp63S6SrPtVWu35RbUlZgF+P5JgZWzhDCS+TmVzqlzF5dbistsBe4v7lK7KXOKne+mYGC76w8/l/qm8t28yYr7nZzi8vybcXIWuAoyy2vdJQ6C3PLyp2OslLU+QjyCnzqvcfbz3WUlOfm5trc/XCUrcstdJXmi4eYZ8zLkye/2G6rtFdWCiEKH6S8UVdHYX5xWZVdVKqyZr3MXlYoBGXuj16GOssqPbIivayw2FVV5JG16WXr7c4qXZ2++vEUOortpWVClQXoy5WV20uF0GRBelml3Vagk4XqZVV2+0adLFwvc9qLi3Wybr3s2UqH0y7EXMqq9f3kGuWXlZSUleZuKpSLJT7M9QwYf49OvSqcav3H9XXIec9VZTF6WfF4pzWZUS+TY819iLJkvazK7qRulahlrXq5HJNdlbXrZXJ+7doYfus9rpP5RRurnBuFPVHVv0BFeIuluelSMVc6yypt6+3GpZFLl/43BTYaFxkXCXzuE76BM4QQz+YX2SpznePfyycIscmWW+yocor78f31+4WQddmRQ5b59ANCJJotCWod7kecVY7nxjM8xP12CET/m/39oJgt51Fxy23l+l3xYcoGKaPWa2WcXvK6pvGyPuonZVRcveyQRyZXRSdrMFDmnqrxXnj6Mao=
*/