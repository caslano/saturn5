/*!
@file
Defines `boost::hana::all_of`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_ALL_OF_HPP
#define BOOST_HANA_ALL_OF_HPP

#include <boost/hana/fwd/all_of.hpp>

#include <boost/hana/any_of.hpp>
#include <boost/hana/concept/searchable.hpp>
#include <boost/hana/config.hpp>
#include <boost/hana/core/dispatch.hpp>
#include <boost/hana/functional/compose.hpp>
#include <boost/hana/not.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! @cond
    template <typename Xs, typename Pred>
    constexpr auto all_of_t::operator()(Xs&& xs, Pred&& pred) const {
        using S = typename hana::tag_of<Xs>::type;
        using AllOf = BOOST_HANA_DISPATCH_IF(all_of_impl<S>,
            hana::Searchable<S>::value
        );

    #ifndef BOOST_HANA_CONFIG_DISABLE_CONCEPT_CHECKS
        static_assert(hana::Searchable<S>::value,
        "hana::all_of(xs, pred) requires 'xs' to be a Searchable");
    #endif

        return AllOf::apply(static_cast<Xs&&>(xs), static_cast<Pred&&>(pred));
    }
    //! @endcond

    template <typename S, bool condition>
    struct all_of_impl<S, when<condition>> : default_ {
        template <typename Xs, typename Pred>
        static constexpr auto apply(Xs&& xs, Pred&& pred) {
            return hana::not_(hana::any_of(static_cast<Xs&&>(xs),
                    hana::compose(hana::not_, static_cast<Pred&&>(pred))));
        }
    };
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_ALL_OF_HPP

/* all_of.hpp
EOkFJku9T8PvjZLetmgfHYBdgP2B3YDjgD2As4F9gMXAvsC1wH7A9cBBf2fvXKCjKs44viHhIaJGXkZEiRAQEEKC4R00QIIBAsQkQkAkbLJLspDHukl4WFSsQFGoIqVKLW3TSluqaCOgxYptqlSpRQkYBBUVESkqtZRSS1ts+9u539x9ZJfW9l7a05M95+PHZOfuf2bu3HnfGfggHAY3whHQrzsKPgvT4a/gDfAQHAvfhdnyPOYIh2N1F8m4gqRnHBwg4Ytpb5THrWA8jIWdldu4fg3WINffJvHz57Nlcv2RCygf4YdwMvw9nAtPwUr4GVwIz8A34TEYE0M5AlvD47A9/AheAj+BneFv4RR4Fs6En8NZ8G/QH65GLOMSI1y9pL64TOUZ4/N9/CXAx+AcuA0Ww5fhHXAXvBu+Ah+Fv4abYCN8Bu6Fz8H98HfwAPwrfBP6Rd+CF8K3YTw8BC+H78De8F04BD4Ovy/up8Ud38pwd4F+d4JyG/HajnkvlXdpHNL2gpslXp+3MZ7jVrRPRsNYOBbGwTzYBk6HbWExvACWwfZwIbwQfgleAu+Cl8KvwS7w6/Ay+DDsBn8Er4DbYXdpH10Jd8IOcDe8CB6AV8FTsF0M4VfvtKuyV4X/Kn+7KnC2srovE+AVcBLsCXPgQEgeUuUEZZN6HvPhU6o8NcLhg7tgNXwV1sB34M3wCJwBP4KUCer+UOaq+1MEO0Mn7AtLYDJ0wRtgKRwDy+Ak6IH5cB6cAefD2bAc1sAK+CVYCZfBKngfvM2h2ncqXLrdGq/2W6DsidBu7RBnlNPxsAe8FI6EneAtsAucLW6nuG+DXeGX4GXwTnHfLe4VMAE+ArvB78DucCNMhE/Cq+FzsCd8EfaCTTAJvgP7wJOi1yqG8gq2g8mwO0yB18FUmA47wjHKHWgHzlHrhslrEdqB4ylf/MyGF8MJUt4cxLxy3QdyXQLcLdftaGuk1wvSzn8R9oL74XXwlzADvgRvhi/DOXAXnCfuCnH74CuwFv4K3i7uu+Cv4T3wVekn7IHfho3yXOyFW8X9jLifg/vkOXkd/ho2wYMSvlNytNwcNa6o0kLFrw1Ml/jRZVfl8QOwI1wHu6pyWD0vyt1DtTUC7Y818nszI7Q/7pLfWergvsG7YX/4ZTgA3gsHw3tgFlwBJ6q/G+m3UnQysJOikyw6rWGa6Hws4f4EXq72eTDuz29hP9VGDbQTE9U4IGnraN5O/IZct0HKgW9JuL4Nc+F3oBvSNlX363twNaQMV+XWRvgDh+o/q/uxKTj8ojsoQvhLLzDaTWWwM6yEvWEV7K/cgfo0MUHSIUJ9Ok1+ZzpMgjNU/ajcZjhyE6KHY5Zcf6uEo0TC4VLhUG4zHEvld3pFCEcC/i6Cl0s92A12V+5APqyX60dGyIf3tjGez/tgJ3F3hatgD7gapsH7oW4HnZTfe83RvB30QFujfboOJsGH4ED4sDyv6+FE+A2pvx6Bql0IF8ANqp5S/tX9rYNPwO9K/fQt2CDul+DX4S7lDvQTGi43wvd4hH7Cte2NfDcQ9oPJcBC8Dg6BaXAYHAMnwmGwBA6HpXAkvEu+Xwsz4HrlDuR7bzdDf2+EfB/bxkifODgCtoVFsD10wq5QrReC6+Gl8GewE2yQ71+CXeCvldvQTcS8Vxi6/UQ3BnbW8W4d8Jcr/rpF8Ndf/GWE/V54/k3CH2BcSNq9sJe4+yp3oH6ok9/pEKF+6Ca/cwW8EHYPCme9XJcdIZz9Av64yPjumgj++oq/w+ZZ++qMf+Xvcn+5Lf4KWhnPz82wHyyEyXAmHAVnwSxYBCfCOfBW6IS3w2J4Fyzxf+9vb8B8WAoLYRn0QA+8Dc4=
*/