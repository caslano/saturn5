/*!
@file
Defines `boost::hana::zip_shortest`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_ZIP_SHORTEST_HPP
#define BOOST_HANA_ZIP_SHORTEST_HPP

#include <boost/hana/fwd/zip_shortest.hpp>

#include <boost/hana/concept/sequence.hpp>
#include <boost/hana/config.hpp>
#include <boost/hana/core/dispatch.hpp>
#include <boost/hana/detail/fast_and.hpp>
#include <boost/hana/tuple.hpp>
#include <boost/hana/zip_shortest_with.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! @cond
    template <typename Xs, typename ...Ys>
    constexpr auto zip_shortest_t::operator()(Xs&& xs, Ys&& ...ys) const {
    #ifndef BOOST_HANA_CONFIG_DISABLE_CONCEPT_CHECKS
        static_assert(detail::fast_and<
            hana::Sequence<Xs>::value, hana::Sequence<Ys>::value...
        >::value,
        "hana::zip_shortest(xs, ys...) requires 'xs' and 'ys...' to be Sequences");
    #endif

        return zip_shortest_impl<typename hana::tag_of<Xs>::type>::apply(
            static_cast<Xs&&>(xs),
            static_cast<Ys&&>(ys)...
        );
    }
    //! @endcond

    template <typename S, bool condition>
    struct zip_shortest_impl<S, when<condition>> : default_ {
        template <typename ...Xs>
        static constexpr decltype(auto) apply(Xs&& ...xs) {
            return hana::zip_shortest_with(hana::make_tuple,
                                           static_cast<Xs&&>(xs)...);
        }
    };
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_ZIP_SHORTEST_HPP

/* zip_shortest.hpp
BCHL2NaubiyZy45ck5OjxQwN3KaT0FjWDjLJeAfiIB2N9w3nh8FQo9bxOUYCeV8WLfAbRRZHfeCqkhvCZGWdl+dwbhP+5W8vkQXulqCWvN/e2frgeMTTVm6R2+C94jTPKNVE+lBwjPXNZ7MxJZvopTO0ISGNp7MRxbz3N1bo9lvdZ78gLCe0elmtITaNLUj5+aBFyvaligQF8vPJ2MU6EWzksW+8/EyhL1msQtPm4l57fcYe5z9hm6QUrIn2WQc9iDwLBFmHFrXLe/TJw/A+FWuqaB0oPQSyjRNtLrkkO8GPAafOv7EWS84UPK8ShbpeUAnlK6aIWFK36M7AvNpklMwz+EdD1Tbs3EWdYTobTW2c7by6ylTkxyivhvwjbNXor/g1Pv8DtViYnj9AfzUdRw3WkbqSIuuKY7eIHFiLYWUUJnxWkJuVAHGlYXPq5++1euvuJpuqXJaSaTXll4FK8dPKSnDruNXc5fRzrHVSHoVR6CRRiB5BBRRTfto8vzht7YqXkHZYniTzPfovB2kW4w0yDHcBpXWi/BCMrombzJvD07Nzdgs5FY4kYHKTS5GHSeqwVnEF4ABAauWWepczSGopUd8q8cGnVE2N7TWU/F331jlAysnwiMOESRtPlBIbQQMTMiej2/QmtmwA
*/