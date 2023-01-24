/*!
@file
Defines `boost::hana::union`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_UNION_HPP
#define BOOST_HANA_UNION_HPP

#include <boost/hana/fwd/union.hpp>

#include <boost/hana/config.hpp>
#include <boost/hana/core/dispatch.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! @cond
    template <typename Xs, typename Ys>
    constexpr auto union_t::operator()(Xs&& xs, Ys&& ys) const {
        using S = typename hana::tag_of<Xs>::type;
        using Union = BOOST_HANA_DISPATCH_IF(union_impl<S>,
            true
        );

        return Union::apply(static_cast<Xs&&>(xs), static_cast<Ys&&>(ys));
    }
    //! @endcond

    template <typename S, bool condition>
    struct union_impl<S, when<condition>> : default_ {
        template <typename ...Args>
        static constexpr auto apply(Args&& ...) = delete;
    };
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_UNION_HPP

/* union.hpp
2FGcuLNpRDOAn1LbtwUe+kb0M2MM2B8MAduHWh8kAb6V4GY/OyrQZnPE5/0jVD+hr/tyHF+IDL7YH/6AUwz+HtZ+j2m/7fQr/3X/t9qmPzLWNXuxyO3Ud5tHcpubK8ZMn6X6H/1W24pIjCvto/OZ6bffqJvpj6rE5FQ/Qovdi4jP+l5EbAB5C3fNJJN98vVksneyGTtoUyGH8BJ12z9mah7CvwalEF07q7aYDb7Eqi1xBpAZruR6Z3lzHoiWZZp15E6cBoddj/KXlSta6B6omygqR+KiD3/vSZuD/i8D7Kok1F3kMzCIj6G/uqYpdXJOIvC9JjBjTkrXnDAu1Dybrp6GPhE/g0oWsy8/FGgXAjfvorIJkvDPbiVWrB6oPbrlEvWJqN1lepvffG25WhOHD+VKTQH+5ma9cz/j+oU6GNk/cbn/qVJGNNtJmLNulk9fLsXnyYNG35hyZcQSp9xo5KmzQus/5IYbTd1lv/pzROPR9smTotluNRrYw9ei7JCOSDuMSFt4HckOqHJjnMOIS9Ln7Siv9umPR/HRrQFKxRXP53HOi2qluovkO+y29IiP5QWXALm/STO/k62ZoU3Au9rJE4ne66qRPpmanFwD9QpswrIYWzBhGJ2/Mm/BX32aoTZyC7dBC8bxInnIpJEL5U+nQvlQdNd0reirsWj5+WO8zMjkr3tS/WFaxPtypZb1ZT2rCbPyEtV3nHyk
*/