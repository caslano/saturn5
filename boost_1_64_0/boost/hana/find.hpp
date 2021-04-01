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
m4E1vDeLup6bYN7pZ4KGj3ET0IsYIavAy6blV21jNeXpm4xjyENoXJn8BpTZbWc0+/j5yRXaMJ4ZnEWuC5aGVLogTC8TujO9DeVI3Svurem4ic07i0f4kwF/XRCsUihrdS0cso98H8M600TotGV3+eV+JYBQOoU1hvNxu6/RBXM3V94nKM9TfzhDmxYaJaGxSymT2FELlBKNisk7QlgWrgWrh8MgZEC3Vfpk2mCeK0wDdbshIthjlXCoIgpBqsTqhai3eghAodtMvWwfanhioHU+GzEvIARZJ30gKHgAJqj3OSOo36C6kpX0RzuDzd/HbPzu50CsTCm/yJ+/M7WIPpOB/29VJtWt6tBkkkIGWwEtFhFyh81L0cEQ7PlvZhKDY/wHifj6Fo3aMldxTChqZlKLcEFEvYKz3PYM/Vnp5t6QW1OOpxasZGiZEGC9si1Y4mQDefHTiTV1gUZUEMqJ/fi/FdSYeuOgci2K1+wcohTsoJajpPXx+9VjRe8q0pmklcQ2dobcy2ecQxfyeK66IcoZVhxEpAxzYemn6PvnwJWK8SVx7xITGHjKTw==
*/