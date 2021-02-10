/*!
@file
Forward declares `boost::hana::detail::nested_by`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_DETAIL_NESTED_BY_FWD_HPP
#define BOOST_HANA_DETAIL_NESTED_BY_FWD_HPP

#include <boost/hana/config.hpp>


BOOST_HANA_NAMESPACE_BEGIN namespace detail {
    template <typename Algorithm>
    struct nested_by_t {
        template <typename Predicate, typename Object>
        constexpr decltype(auto)
        operator()(Predicate&& predicate, Object&& object) const;

        template <typename Predicate>
        constexpr decltype(auto) operator()(Predicate&& predicate) const;
    };

    //! @ingroup group-details
    //! Provides a `.by` static constexpr function object.
    //!
    //! When creating a binary function object of type `Algorithm` whose
    //! signature is `Object x Predicate -> Return`, `nested_by<Algorithm>`
    //! can be used as a base class to `Algorithm`. Doing so will provide a
    //! static constexpr member called `by`, which has the two following
    //! signatures:
    //! @code
    //!     Predicate x Object -> Return
    //!     Predicate -> (Object -> Return)
    //! @endcode
    //!
    //! In other words, `nested_by` is a `curry`ed and `flip`ped version of
    //! `Algorithm`. Note that the function object `Algorithm` must be
    //! default-constructible, since the algorithm will be called as
    //! `Algorithm{}(arguments...)`.
    //!
    //! @note
    //! This function object is especially useful because it takes care of
    //! avoiding ODR violations caused by the nested static constexpr member.
    template <typename Algorithm>
    struct nested_by { static constexpr nested_by_t<Algorithm> by{}; };

    template <typename Algorithm>
    constexpr nested_by_t<Algorithm> nested_by<Algorithm>::by;
} BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_DETAIL_NESTED_BY_FWD_HPP

/* nested_by_fwd.hpp
2gPoyU59hiQEgqyKNNdSogCV1ObrAZzCaiaiJH5b7K/N9ceXfl4Xlgq2pH44SnG3OEfRkGiklVghTZ8hAxYl5ZNc1shfYaiT6JInqd68l4pfz8StVP0mq368WHBbNV2N30o+sXSUiutm3Y0ZG7UumgO2g6N1OLbx6dm73uCMTe+IkcGkS5eq4cX16Kz3rivUzJSzpTxsTY7yRz1AB+7P1JIy2vGfUli2uF5KJEFV2eih1G3znCQxhxhFfVuF81H40Qu+mZ8kY0xBtEmutQLjKi+Q4y6UGQkVXK88NJh+U3OpOIBVs69MFkDznzAJw/Xo/AVmeYhxLDW5JrRsFapqKqSo1VVKbqGWCGg5/sIyLNbm3rtGzCjVTikVYUuYa/EfHjxY431hEUjQEj4wvVllwwPm0p1Cm3yQzaop3xxkvugZqQ426NTASaaaSuWY1yKGGUGULZYSicKVPPCRrdDWnJBDTkaY03RGmEqna4a3LkUHInkwHeuKZFsrWWWCd54ocn1Q5BGOycSfrJSdiAqJR8rTJPKKhNCUjjjZiYWQ6k+/+meNPIKYTXWJBeSdExX2pYI3hJ6oM0F8dEPMKDXubSZizIj2eZgZsuNMpAiWMCqhqWWD0CTHeNLih8TFo/UqWagJPyKxRpUniLiW
*/