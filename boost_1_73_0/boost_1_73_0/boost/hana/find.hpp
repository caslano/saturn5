/*!
@file
Defines `boost::hana::find`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FIND_HPP
#define BOOST_HANA_FIND_HPP

#include <boost/hana/fwd/find.hpp>

#include <boost/hana/concept/searchable.hpp>
#include <boost/hana/config.hpp>
#include <boost/hana/core/dispatch.hpp>
#include <boost/hana/equal.hpp>
#include <boost/hana/find_if.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! @cond
    template <typename Xs, typename Key>
    constexpr auto find_t::operator()(Xs&& xs, Key const& key) const {
        using S = typename hana::tag_of<Xs>::type;
        using Find = BOOST_HANA_DISPATCH_IF(find_impl<S>,
            hana::Searchable<S>::value
        );

    #ifndef BOOST_HANA_CONFIG_DISABLE_CONCEPT_CHECKS
        static_assert(hana::Searchable<S>::value,
        "hana::find(xs, key) requires 'xs' to be Searchable");
    #endif

        return Find::apply(static_cast<Xs&&>(xs), key);
    }
    //! @endcond

    namespace detail {
        template <typename T>
        struct equal_to {
            T const& t;
            template <typename U>
            constexpr auto operator()(U const& u) const {
                return hana::equal(t, u);
            }
        };
    }

    template <typename S, bool condition>
    struct find_impl<S, when<condition>> : default_ {
        template <typename Xs, typename Key>
        static constexpr auto apply(Xs&& xs, Key const& key) {
            return hana::find_if(static_cast<Xs&&>(xs),
                                 detail::equal_to<Key>{key});
        }
    };
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_FIND_HPP

/* find.hpp
6/pHr0wiweAmy0VtG768O9omWla2PPYPKtser2mL8umwoj28uzvcO0AIQhBXQzhc38nhik4OqRNL6FcDOlrfl5uY3NfRY/o6Xt/X8Yq+jo2+PBS0wXKWW9+z50vAbly17YPPTw+++wwcKngGJ++LwX8gi4bw0xLO6GHuCyP1iqWgfVXQ3TKcib246o9wY+FrbLr9Jj5exll0E5M5IPcick8ZnCbJTF14A0rhL/ZN+m/GZ1P0vDPcZKgVyQCQmyglg/EYVnWSkt9mQMt+8gDrCkY8i2KSmlGWLUFhCqY5CNcg9paLCd7wJ+TuxDo8Cya9EpdzH/0oyVcjnEhqgbjCyXwb5t3lvKPftwQxecHYoHZWwqkCAtLviaOhJQ1hQs9BPC3TUNLjPEqh60mUsbPtbKbvIsj1FOgFZIAPptMwRS+UefDZuyNHDDhTI7Mi/B0iSzAB4T9P0lDCgM0p581pksTPc+8+iMlJam74914/MACYFNpq6Dek7zRJaxF52niR91MVfeHlixcs7PhSj2nST8PpMMxrzIaeo+Ev0W8kg8+bF8O24HxxtR7m5Fb64EED+BvGmSxTduZBR68AVAgnijZLWphZrBv9xpsYda16Fqr6a89YEDRL7IBiPPWePfPM39FDRHbEH9cE19fp
*/