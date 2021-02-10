/*!
@file
Defines `boost::hana::zip`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_ZIP_HPP
#define BOOST_HANA_ZIP_HPP

#include <boost/hana/fwd/zip.hpp>

#include <boost/hana/concept/sequence.hpp>
#include <boost/hana/config.hpp>
#include <boost/hana/core/dispatch.hpp>
#include <boost/hana/detail/fast_and.hpp>
#include <boost/hana/tuple.hpp>
#include <boost/hana/zip_with.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! @cond
    template <typename Xs, typename ...Ys>
    constexpr auto zip_t::operator()(Xs&& xs, Ys&& ...ys) const {
    #ifndef BOOST_HANA_CONFIG_DISABLE_CONCEPT_CHECKS
        static_assert(detail::fast_and<
            hana::Sequence<Xs>::value, hana::Sequence<Ys>::value...
        >::value,
        "hana::zip(xs, ys...) requires 'xs' and 'ys...' to be Sequences");
    #endif

        return zip_impl<typename hana::tag_of<Xs>::type>::apply(
            static_cast<Xs&&>(xs),
            static_cast<Ys&&>(ys)...
        );
    }
    //! @endcond

    template <typename S, bool condition>
    struct zip_impl<S, when<condition>> : default_ {
        template <typename ...Xs>
        static constexpr decltype(auto) apply(Xs&& ...xs) {
            return hana::zip_with(hana::make_tuple, static_cast<Xs&&>(xs)...);
        }
    };
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_ZIP_HPP

/* zip.hpp
Tul+vM67BED+EPiukhRfOIrSguH24pYye7FK3gj7uekWoKNUodHW3MUYE7aFZhfMguhMXpn+EBfTh69CVZcMpjbnsZsLGajAK+cUsgK6hoca/M3dIAJi0zGCwdqzTtLjuASi3Sp0eFWULFOKouNx9HUpJQrfKndl1V1GEo9rcdw0vvGTSQBZqZSxZ8HADdymDdkuk8bIJLHEPz7X+PbYAOzivDg8DAQQpWyboNYRneqHrfP2j3s/oyNJfo12PZBRClB085PD/KXoUK7dmonhGx0O5DvUS7KzTLrGmCEoCSrLC92gLUjYslv6lhKqGE+XuRFibO0WdtZqN+4WzfnR2Saepg43j6Or2Yi0IMfScjnmUo4yPT5wYB50vFZzLjcrLjtZgu/vMSth8x/HF0cH+0fHlFtIfjCxNuj4fp5CKxbW/7L3du/QuqlFGNYFdTcYtSCn5+8WL0RlNwxflODDVkLqJT3WPn4/Ls6UeFDyAQkMdNDwVbDfH1y9PopjXtR83oYcejs73RdU7qeHeF9UOlqPtlH5Xf3X1mrR6X4BRj1JHUYYiBWDjBjBGhvQQ+joGssz1lmzdRBGpgX8ZfoY8tnZkRKraM84uRBA36aWSy4nncm9Td+EySJnLA8O3Zw6vaFGcq7uLepUNWiy
*/