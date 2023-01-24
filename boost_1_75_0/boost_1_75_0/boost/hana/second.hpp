/*!
@file
Defines `boost::hana::second`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_SECOND_HPP
#define BOOST_HANA_SECOND_HPP

#include <boost/hana/fwd/second.hpp>

#include <boost/hana/concept/product.hpp>
#include <boost/hana/config.hpp>
#include <boost/hana/core/dispatch.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! @cond
    template <typename Pair>
    constexpr decltype(auto) second_t::operator()(Pair&& pair) const {
        using P = typename hana::tag_of<Pair>::type;
        using Second = BOOST_HANA_DISPATCH_IF(second_impl<P>,
            hana::Product<P>::value
        );

    #ifndef BOOST_HANA_CONFIG_DISABLE_CONCEPT_CHECKS
        static_assert(hana::Product<P>::value,
        "hana::second(pair) requires 'pair' to be a Product");
    #endif

        return Second::apply(static_cast<Pair&&>(pair));
    }
    //! @endcond

    template <typename P, bool condition>
    struct second_impl<P, when<condition>> : default_ {
        template <typename ...Args>
        static constexpr auto apply(Args&& ...) = delete;
    };
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_SECOND_HPP

/* second.hpp
tATluXVEebO47yZR4QIqFWjOw5Xgs4iwlnD99fScHYkEdXIW4Y+r0x/rwWwBpy9cnhcey9mNaOE/peQSiXiyrcvDH4GAJ+GY3rLly2a7efaDrGSUZxTU5fWn/pd/cqQQwtMJyPKxu3rzKTmSoZBtvo+iQjLlg+HeEt+fzvFH97N7oBrBkPtuL851Go3uQ2ag3JmQew/nypVwf427j4P78/g+B/7JEyEjlUNPn4ruDVcR+j7I3cOhpML9Zu7+B7hfz9V2mQ75UDsLchdwNc7AfXhdA5N1r3UBdrrzusnCT7m+F5Zbp7fkW6tCM3USG4srWhsvY2gmqiIL1sXaaEyKQJ3ETmOMHqNTCjUViuGDBiq6+0qc1jpH8aSmgeyvC3mUrlSdZYfKPEpsUM4OlBOiHRg2IzQT6n1E9diVKE9rHRKiMSpflFjLgylrVYmlvBlK2P6WFIU5ktj4SuwU1lJ2MhDALKCWP0UINbeUzdSVppW2ugAbLQ+4I/xyWPoAYWAUZVLayQVoPkpZBZoL6iyn/yiOcpWyvzUu0/J050MvCCjorU5pE6yr0l1nT7lRiFe1H6UQaIwKG90l1BNUh+M2XsBxq461oWS69wqnKJNJacMeRy1rraB/CrsSC7U7pbvYAGlCYyRlk/oKCNnknD9TINRaIdm84up3hPrqTpTufCaqXmKvazlRx9dasaIFSDCIMeXbGZn6oYJBPIWN
*/