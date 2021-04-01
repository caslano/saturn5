/*!
@file
Defines `boost::hana::remove_if`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_REMOVE_IF_HPP
#define BOOST_HANA_REMOVE_IF_HPP

#include <boost/hana/fwd/remove_if.hpp>

#include <boost/hana/concept/monad_plus.hpp>
#include <boost/hana/config.hpp>
#include <boost/hana/core/dispatch.hpp>
#include <boost/hana/filter.hpp>
#include <boost/hana/functional/compose.hpp>
#include <boost/hana/not.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! @cond
    template <typename Xs, typename Pred>
    constexpr auto remove_if_t::operator()(Xs&& xs, Pred&& pred) const {
        using M = typename hana::tag_of<Xs>::type;
        using RemoveIf = BOOST_HANA_DISPATCH_IF(remove_if_impl<M>,
            hana::MonadPlus<M>::value
        );

        #ifndef BOOST_HANA_CONFIG_DISABLE_CONCEPT_CHECKS
            static_assert(hana::MonadPlus<M>::value,
            "hana::remove_if(xs, predicate) requires 'xs' to be a MonadPlus");
        #endif

        return RemoveIf::apply(static_cast<Xs&&>(xs),
                               static_cast<Pred&&>(pred));
    }
    //! @endcond

    template <typename M, bool condition>
    struct remove_if_impl<M, when<condition>> : default_ {
        template <typename Xs, typename Pred>
        static constexpr auto apply(Xs&& xs, Pred&& pred) {
            return hana::filter(static_cast<Xs&&>(xs),
                        hana::compose(hana::not_, static_cast<Pred&&>(pred)));
        }
    };
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_REMOVE_IF_HPP

/* remove_if.hpp
3BwY46OHjVYdRti0SPQ2JVL2z7xsZ97zx4mN39JaoaLLeqbPOQBbIDYmEUrtj0PrTyQmA6QA74NYuIrdAVXPWx3lU/CAB7PAdXfISbSQKYLYt9qBSD4aT+VFJYebDbVQQZyL++un8IYNBVxBSd0xU8Ir5WEP4szNsUOuyF+LWx9pq56f3LfwUzcxKmQtTkZSUEwuoF8usGNTslFRXhcc75jgygMV4KYazyYCfU0eyrWmC61wma2KAZcU7NBJKcfgJqhULs7cKVbrAMt3Fd++wcSIQ5QOSYqQGSK5nGMiNVD7NcvW//tViZsRV95k4nAkNJtMOkRv6tkSHkEyXqsdB4HXY++yex7ZT29NmWOeSPBWEAYcziuSW/iBYOuCnYdooZajlDl5LoCYHGleh5C8C8M3+vRUHlx/TZbsR8K3XqCPMAaJa5biJliONYOIaQ3XDM1HqdJ945VyvN1UlIUBrf8z45+jIKC/w59cutdPTUEPy6eNWNIPhoSUSFPf7hXLnvRz69RiB5CGAy7IQBWrEDLftqy4HIZyk+c0V0dpsMaZ2qfBWnbVlyx3wg==
*/