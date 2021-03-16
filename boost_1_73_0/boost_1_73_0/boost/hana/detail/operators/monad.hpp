/*!
@file
Defines operators for Monads.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_DETAIL_OPERATORS_MONAD_HPP
#define BOOST_HANA_DETAIL_OPERATORS_MONAD_HPP

#include <boost/hana/config.hpp>
#include <boost/hana/core/tag_of.hpp>
#include <boost/hana/fwd/chain.hpp>

#include <type_traits>


BOOST_HANA_NAMESPACE_BEGIN namespace detail {
    template <typename Tag>
    struct monad_operators {
        static constexpr bool value = false;
    };

    namespace operators {
        template <typename Xs, typename F, typename = typename std::enable_if<
            detail::monad_operators<typename hana::tag_of<Xs>::type>::value
        >::type>
        constexpr auto operator|(Xs&& xs, F&& f)
        { return hana::chain(static_cast<Xs&&>(xs), static_cast<F&&>(f)); }
    } // end namespace operators
} BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_DETAIL_OPERATORS_MONAD_HPP

/* monad.hpp
1ruc0/u80lfcLb64X+877tf7jHtrwMde1lWB0c8wbhSO6eArtWe62Kd1J3y54OGIPnLRnVKddmf9tO7l3kjsh8nXBhxtszYtBEhbXcQrdX7lE70kdmSe0qdOXgl6mxMJV2l/uXDdS5+r6ZyK+T2jHc/kik95us/K8jwZa+/OYcbi53kWyDrlWI9/yUxK20m7Gpm0lDSG0qeYu7boLkoOkUlIiX/nakaPuWZZaCemvOOqDBdL5rxNZjJ3U64213M=
*/