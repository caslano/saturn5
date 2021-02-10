/*!
@file
Forward declares `boost::hana::find_if`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FWD_FIND_IF_HPP
#define BOOST_HANA_FWD_FIND_IF_HPP

#include <boost/hana/config.hpp>
#include <boost/hana/core/when.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! Finds the value associated to the first key satisfying a predicate.
    //! @ingroup group-Searchable
    //!
    //! Given a `Searchable` structure `xs` and a predicate `pred`,
    //! `find_if(xs, pred)` returns `just` the first element whose key
    //! satisfies the predicate, or `nothing` if there is no such element.
    //!
    //!
    //! @param xs
    //! The structure to be searched.
    //!
    //! @param predicate
    //! A function called as `predicate(k)`, where `k` is a key of the
    //! structure, and returning whether `k` is the key of the element
    //! being searched for. In the current version of the library, the
    //! predicate has to return an `IntegralConstant` holding a value
    //! that can be converted to `bool`.
    //!
    //!
    //! Example
    //! -------
    //! @include example/find_if.cpp
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    constexpr auto find_if = [](auto&& xs, auto&& predicate) {
        return tag-dispatched;
    };
#else
    template <typename S, typename = void>
    struct find_if_impl : find_if_impl<S, when<true>> { };

    struct find_if_t {
        template <typename Xs, typename Pred>
        constexpr auto operator()(Xs&& xs, Pred&& pred) const;
    };

    constexpr find_if_t find_if{};
#endif
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_FWD_FIND_IF_HPP

/* find_if.hpp
FTt4IlPGRGucSvFNjtIsLuWUVl5YWQfTSWrkOpjvDFR1eWqIN/cVR1Ov7NEsMW8UOmTv8vwTxrKM3Yh/4J0Tan/SoCK9gEChyBD6TY4hjA3o/PKa7/ID4SVgYO3ApS320m+q+zhqQ79R6KPf5Pvy25i+padhjWe+yfeaAlXp+ESU5AhvvMlLiLZTRbJn73CPHe/+YdXyv1BLAwQKAAAACAAtZ0pSIzLMWS8CAADSBAAAHgAJAGN1cmwtbWFzdGVyL2xpYi92dGxzL3dvbGZzc2wuaFVUBQABtkgkYK1U0U7bMBR971cclRdAWcP2NDY0rSowqqEWNUWoEpLlJjfYk2tHtkOLxMfvOhTYJFBfcJRcx77nnOtj2Xu6thXVuDgbnp7NxOh6diluppfnRXEpLnp7PKUtvTObH35c6+EQO5voXsGNY4e48u4PlfHtbCEe8fQw6pbjLpEcr5BHcYDdkEfsdxCxVTlJfSF2Cd2m2tInT8hbkbo8wrCEHLnmwes7FbE/OsDn4+Ov+IQvR1+OMpxKq8mgiGSX5O8ynFTdyE8lN5tBoB8ZKEKawZZqrnRAcHVcS0/gvtEl2UAVZEBFofR6yT/aIipCrQ1hNL1ajCe/MqyVLlUieXAtgnKtqaDkPcFTSfr+iaORPsLV
*/