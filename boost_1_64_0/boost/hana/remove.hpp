/*!
@file
Defines `boost::hana::remove`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_REMOVE_HPP
#define BOOST_HANA_REMOVE_HPP

#include <boost/hana/fwd/remove.hpp>

#include <boost/hana/concept/monad_plus.hpp>
#include <boost/hana/config.hpp>
#include <boost/hana/core/dispatch.hpp>
#include <boost/hana/equal.hpp>
#include <boost/hana/filter.hpp>
#include <boost/hana/functional/compose.hpp>
#include <boost/hana/not.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! @cond
    template <typename Xs, typename Value>
    constexpr auto remove_t::operator()(Xs&& xs, Value&& value) const {
        using M = typename hana::tag_of<Xs>::type;
        using Remove = BOOST_HANA_DISPATCH_IF(remove_impl<M>,
            hana::MonadPlus<M>::value
        );

        #ifndef BOOST_HANA_CONFIG_DISABLE_CONCEPT_CHECKS
            static_assert(hana::MonadPlus<M>::value,
            "hana::remove(xs, value) requires 'xs' to be a MonadPlus");
        #endif

        return Remove::apply(static_cast<Xs&&>(xs),
                             static_cast<Value&&>(value));
    }
    //! @endcond

    template <typename M, bool condition>
    struct remove_impl<M, when<condition>> : default_ {
        template <typename Xs, typename Value>
        static constexpr auto apply(Xs&& xs, Value&& value) {
            return hana::filter(static_cast<Xs&&>(xs),
                    hana::compose(hana::not_,
                                  hana::equal.to(static_cast<Value&&>(value))));
        }
    };
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_REMOVE_HPP

/* remove.hpp
Px/hD/HKiK5qgyyE/mheCbC9FYNICQlI4AAMB0eu7KgNqct4Vcy5tiqNlczu7/03zCiv+qm5nGEbY0DirL3PyxA/agyVu4VzDl5ygj0qyhiU13EJ4oppbMOgOMz2KBsidg/0IdNdFVprqSvsQ14v6vsRuycrXzDetp1z3M9tF4p534IkkRK920uzcg0zhXYO1vFYBqZ8kj1iqvt9GY+S8R5UWpUs8sqxzxtlku2hXLampbRSiBL7fHDlOG4/fcrIBxb23tKDD4ltH4ok2rzFb5WaQDAHFp6ay2dO9NoJDo0ZysEJTj406B1HMsiln0jvG21Tu95BfnByGNsXXm9031Bdof22i7Ic1BPUmxO4ssNRlwYafftoWw2zum+kgW+984iHQYj/vd3tqcwyQdxvWob3TIimAfU8zOfBVhvMsU8MJZdgKdwX4nAFRUXYSjfXHxHmM9oaPC3Da2ocHHSuHKp/5Ppq6u8W2sw/LV/jfV/oShWK1H0/KDa/5vXNrO6lrO7WVr1tejXUvYX+6tN3yZrSl4bVnag9jmaaF1AZ7Aqn10dVo73zDZJ8dCLucdMNrk555y85jfW/Ew6NhTrJE6e+lMlFkyQXJXnibJ4PEe6n8b4vjfJKmEbxvh1jKmNemNjo+3EopG8srvlaiDsRaL+m8ZSRBhdUIkGaG1Eafw5A6wIF+mcBbaCRy8tBVBo6jjGhf5Dy4HHiYTETbJGT/8ltsSyc2JPtrYEiesPA90t82NVAmx90d/5EXQFbk3XPZ5LG4Td/u8Qgjw0Hy3byITnz3Zn49fmIAEmivdNsrPtsZKif3dFZWjJCC49K43f5bw/jd4r4TMXxa1Pfroo02UfA8b0W5sPcHAqvqCS3/WKE/ydl33elZXZr81G5uAmbJ8C0wMUD/hlBQNkUb4Dy6RjnteSuDQbsabPEMMNlkp9omVIw3ivtSk0KHfgu+rC7Jxkq41Eyw0FVXxchuMh8gZPEr832E8P62lWmty2DYRoO+SG6GhhWwPYyvkFN5cDnZW1QzHWyVG2nM/+V8JmzhuwvJ1s2Wp57TJ2i5UbU/7UgCKbLgWWUBX+JchzMJkCGHtYapKOMBmMSl6Lup3lXHuVBUeQXsKbD/PGw/NN6rorp95NFO+V1NUwHbb3tq4DVG/OuGfL8DGmB/ipXn0DazL5I9NdXhkl8S1ybBHPy0fl53/e8lEbbkcwHIRujfLa9G2S9sX/9+zI+hoGoIZQVjZcb/htGaS7e/zsjnFM4GUF4KHPfI5gN4ZE2v8fsZGULBpqVzglYQLCYB5sebEZma/pSKJfZFgupuNMM4GYQxGL8rvlGKJPpkHTddKqSyQvGyyUQC3gUAXRBJhnlY7T8cdE71cMfBp1DgWgddaJZXZpZWBcOdKhMbUyjK8agRTg+0Q4DMQEyHh2rmso2vMl9umhw7Mn2PhzFM7rVS3+XtttVZV3YumFwVqIEvI74Ad8d4U84XpXesc/bxwbhanUSQTXuivixxOby4lfkfkkcRBUDsjrUBBM815M98+v5+q8cqNXarmGOXgziuhgq9jzuSrCa8I7w4DKTHztjit5CiKfg5BZIpziht6V95JaVxui+L1uQaaJvHKCrhsCSe+GlHFRn/lSN82oqs94/G9eqkSWvjB/Ws2u7SbeAMZOzOj2uglKd0BrXmn/O7+X9/A8vI8eJcRau44Ml09b6hNqxP4Xy6/w1voA+m+EIObe9tr+J79K8TPs1lKFzspal5LbrUW4mGCPb/rog741x2lOfX/7xzL+qsaYR0kfCWEO4lIegT0xWnw9KyNvG1IbIjlG/Bn2dKkZxUiKuRsaHs1JVqq4dx++FRbHF+xjz8gW5Tt0=
*/