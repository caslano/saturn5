/*!
@file
Defines `boost::hana::members`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_MEMBERS_HPP
#define BOOST_HANA_MEMBERS_HPP

#include <boost/hana/fwd/members.hpp>

#include <boost/hana/accessors.hpp>
#include <boost/hana/concept/struct.hpp>
#include <boost/hana/config.hpp>
#include <boost/hana/core/dispatch.hpp>
#include <boost/hana/second.hpp>
#include <boost/hana/transform.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! @cond
    template <typename Object>
    constexpr auto members_t::operator()(Object&& object) const {
        using S = typename hana::tag_of<Object>::type;
        using Members = BOOST_HANA_DISPATCH_IF(members_impl<S>,
            hana::Struct<S>::value
        );

        #ifndef BOOST_HANA_CONFIG_DISABLE_CONCEPT_CHECKS
            static_assert(hana::Struct<S>::value,
            "hana::members(object) requires 'object' to be a Struct");
        #endif

        return Members::apply(static_cast<Object&&>(object));
    }
    //! @endcond

    namespace struct_detail {
        template <typename Holder, typename Forward>
        struct members_helper {
            Holder object;
            template <typename Accessor>
            constexpr decltype(auto) operator()(Accessor&& accessor) const {
                return hana::second(static_cast<Accessor&&>(accessor))(
                    static_cast<Forward>(object)
                );
            }
        };
    }

    template <typename S, bool condition>
    struct members_impl<S, when<condition>> : default_ {
        template <typename Object>
        static constexpr auto apply(Object&& object) {
            return hana::transform(hana::accessors<S>(),
                struct_detail::members_helper<Object&, Object&&>{object}
            );
        }
    };
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_MEMBERS_HPP

/* members.hpp
9SncSzbeRJwbYs8INtN8Yo/xEIMaGb7Q4m8ZVYi5jTBgVEdh2cGaUXy+1OKznxd4ijxPafMBM7BGo6cR+qH4vGuN8wRtwFqcuvATj6OL/XpXOeO7Z4BcTPr6gRMgbeKv11pnMFhuMHj2eJyQREjvadOvf0rxqOK4fAdnZ5mPsHusXVCc/DzD3ErS/sPqqH6+1OhnaVWIKg+qNP3v+wkjB4cP6KfG+WkDZwVbDetdVFVjcWIY0NKVs8p6W9E4gbKxjS6tmTIa4KElO41CiuM31CL1cgy1pt/7HmnGoWfi2U3cD4hrV/l/g0w0FG1s+n0COLk/wcND7l4Jman+M66p3qP4OZDWWec4Th9uggRzIbC9/3WcP2z0V+DBc/vYYvw/46zXZODk8xSPcQYF3jPYSZ5PI/QFsgxFqzva1/7+R7XuqJV4KT2CV+Eo1xbQN2gcVmXOq0NavwMH538Wwzqq4pwr+PYegWGy1Tp21YyvY26Gg7cQyw7Cckz/kWXQw5Wx2BUPt8bWfHcDO2o8I87I0ECtjKG3y6BXFSnOhwPH6q2vmPrsEa07rU6JAxoIhNUQQe9MImrNOmPUdSy8kI9nQu1S8pfsT7Lem9r8HQzUN/xHcYxLLPBSyKUSZuwGAnGH4LK6i7KMF69G8Q3F2cyD943xldI5wUPV+QplpL1J/Y3OVkDsmDARCFafryC7YYdgm/MVH5kyAEnf9fkKkuPRWQPhoDOWDKmi6Js+XwkLVp/OVkT2V5VXHN/1+Uplz82JUxTK73wr6ftHg+VGZqH/GDOH/c0B85oG5hTP1Xw9lD1sT4e8IjW+N4ziaw4TiOZbTHyLy6uj+d3fBhiOROVTejvoVXinwaGzKoHvfWNotvOJfZDRbOe1+ujY9ph5AT8OmBqgxvcZsw5BEyza6DkyXbbsy5cAy5Hr/Glj6LZznb0WuFwb7GV+/0cgvvneHVjZ5LJRZw/nryK+1zFk0qOBb6rsLVdTZVSLlb38Gk2ZYGCHnbGcuCbKhPyTb4sA9NnE9HVRrn1ETT3vlvSdDmaonqZp7RPltRqgBjX5j2yuZ/BCcJFkeF0fEWGmj/HCojnXizxARiDodZfWmrkKu1exjmG+mzcSaZo3ftXOEvcneY4fRjE8tMursL668DdSBf327G7Acz0FWz/F6+igrWqo02vzTuD9PH4HsUCiDTeGL3zQf9TicvsdprsstdYa33ZKHPNa9rrcj8PqUp3kJwxTSg9bRn3YIniDqQxh6HhYnqaxZsohJwyk61XdZ3yvY9b1wsLxqlz7b/vbS4iX48y0VbtPtNodVjhNwSuJZAPpJqs3JlW7td+e1z+Md+fxakDlCh5ho9TyM58DLLc7Sg8pK5IQyXlwUUYdVBB36HxC0YcnYEXKgDoXuwJ9hq4XQ6G0vfYdf0H4b42sj3CTI1xe+Uofqe+LbKxMsZj1lW+I74U/j8RRuD4DyjHNCMRIq7pjYJaQnnWlKxanzlkF97WfjYXDXDfh+mPwCW2BIcNoNXDfGYNvwOBUH344Bo4C2B+lYC6Ow4Xx7QBG8fA3ozBGDPE7RtutYogfpd9qOwUYGiM6Dl1QcrOO1ZK/TeEibDD3LCbendUJZaN83rgLj3vtBVwrgTWiJNh5zweMfFEJ3utCvqgKHhQJ2NggH15q7VPD3I0Cu/gvfa5SFUyCsH4/2dBNPnSTiygL1S+vMFyZ7B7mpSXzLBfv/8RIp5jDJq/n/0koXj0bcdwAr+ZOjnc1t/cum/eUcQIU4YmGoh3vQlhV9Tuovuzn9Utcf4MRacO3Nad0AX9aDCzQumy5ZVPauReEScorBmaojy1spAdqewqRH2Ldom/XVDEeGfajSBU=
*/