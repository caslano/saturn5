/*!
@file
Defines `boost::hana::intersection`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_INTERSECTION_HPP
#define BOOST_HANA_INTERSECTION_HPP

#include <boost/hana/fwd/intersection.hpp>

#include <boost/hana/config.hpp>
#include <boost/hana/core/dispatch.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! @cond
    template <typename Xs, typename Ys>
    constexpr auto intersection_t::operator()(Xs&& xs, Ys&& ys) const {
        using S = typename hana::tag_of<Xs>::type;
        using Intersection = BOOST_HANA_DISPATCH_IF(intersection_impl<S>,
            true
        );

        return Intersection::apply(static_cast<Xs&&>(xs), static_cast<Ys&&>(ys));
    }
    //! @endcond

    template <typename S, bool condition>
    struct intersection_impl<S, when<condition>> : default_ {
        template <typename ...Args>
        static constexpr auto apply(Args&& ...) = delete;
    };
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_INTERSECTION_HPP

/* intersection.hpp
jk/kOe96OWUBOPZey+0Zr+GKLt8NT1q5ntGFyiFt2JfDt36/3X5v22ko+ToWvM5GibzyqR2qGsfQ1Rt526I2RvahNuhsTqGRRXXMJxGz8UGxcWFK7T14F/oqdUaTKmbUTjBNg+ZbCpDLa0MU1CYgygkR+/AmIRIlYjUtyicjLpZFXa3KomJfOc1s4+S6wewFKlzialXeobYpBKNanKUe5VfENWRNqwJI813ZmyE6CiK0UJUxSSfmZZe84kooORioISy7q8Wtowin8nWrKGaphdq0FPqg9SiDrlKdgpE0Zbo7Vu/Exg9n7iltvLkX6Oz3yHxo3ZuIpEJyFe14iwDYYLycoX8umnivQ+QSXX/v+kGwFqKAoW+YH2Eh3OexUKYElI3hsJJGSQP5bY6nyzDOlsSZAeZWN5YBabNxiLinofBY04AKaBMPsieE8ikygBkR7yjrRY5U9Mbl7dwRUSKlD1fscEWcGPMlSoaae3HFfoNJRYUSimXshN+GvWGwnCjnHNUFQb9VTnkrnfzX7AI6IzzliYwxLSJp0WedIaWK7A96f/24AVhMbPT5QQOnX/1SFzJZ4VeJoS2ZFVs6rJfX0+pBkByyEFbQNQCdT9FQdlE20NTxFo5jCnMO61QOcAiAVfIol1GftETmQfrJ
*/