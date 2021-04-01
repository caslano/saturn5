/*!
@file
Defines `boost::hana::lexicographical_compare`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_LEXICOGRAPHICAL_COMPARE_HPP
#define BOOST_HANA_LEXICOGRAPHICAL_COMPARE_HPP

#include <boost/hana/fwd/lexicographical_compare.hpp>

#include <boost/hana/bool.hpp>
#include <boost/hana/concept/iterable.hpp>
#include <boost/hana/config.hpp>
#include <boost/hana/core/dispatch.hpp>
#include <boost/hana/drop_front.hpp>
#include <boost/hana/front.hpp>
#include <boost/hana/if.hpp>
#include <boost/hana/is_empty.hpp>
#include <boost/hana/less.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! @cond
    template <typename Xs, typename Ys>
    constexpr auto lexicographical_compare_t::operator()(Xs const& xs, Ys const& ys) const {
        return hana::lexicographical_compare(xs, ys, hana::less);
    }

    template <typename Xs, typename Ys, typename Pred>
    constexpr auto lexicographical_compare_t::operator()(Xs const& xs, Ys const& ys, Pred const& pred) const {
        using It1 = typename hana::tag_of<Xs>::type;
        using It2 = typename hana::tag_of<Ys>::type;
        using LexicographicalCompare = BOOST_HANA_DISPATCH_IF(
            lexicographical_compare_impl<It1>,
            hana::Iterable<It1>::value &&
            hana::Iterable<It2>::value
        );

    #ifndef BOOST_HANA_CONFIG_DISABLE_CONCEPT_CHECKS
        static_assert(hana::Iterable<It1>::value,
        "hana::lexicographical_compare(xs, ys, pred) requires 'xs' to be Iterable");

        static_assert(hana::Iterable<It2>::value,
        "hana::lexicographical_compare(xs, ys, pred) requires 'ys' to be Iterable");
    #endif

        return LexicographicalCompare::apply(xs, ys, pred);
    }
    //! @endcond

    template <typename It, bool condition>
    struct lexicographical_compare_impl<It, when<condition>> : default_ {
        template <typename Xs, typename Ys, typename Pred>
        static constexpr auto
        helper2(Xs const&, Ys const&, Pred const&, hana::true_)
        { return hana::false_c; }

        template <typename Xs, typename Ys, typename Pred>
        static constexpr auto
        helper2(Xs const& xs, Ys const& ys, Pred const& pred, hana::false_)
        { return apply(hana::drop_front(xs), hana::drop_front(ys), pred); }

        template <typename Xs, typename Ys, typename Pred>
        static constexpr auto
        helper2(Xs const& xs, Ys const& ys, Pred const& pred, bool is_greater)
        { return is_greater ? false : apply(hana::drop_front(xs), hana::drop_front(ys), pred); }


        template <typename Xs, typename Ys, typename Pred>
        static constexpr auto
        helper1(Xs const&, Ys const&, Pred const&, hana::true_)
        { return hana::true_c; }

        template <typename Xs, typename Ys, typename Pred>
        static constexpr auto
        helper1(Xs const& xs, Ys const& ys, Pred const& pred, hana::false_)
        { return helper2(xs, ys, pred, hana::if_(pred(hana::front(ys), hana::front(xs)), hana::true_c, hana::false_c)); }

        template <typename Xs, typename Ys, typename Pred>
        static constexpr auto
        helper1(Xs const& xs, Ys const& ys, Pred const& pred, bool is_less)
        { return is_less ? true : helper2(xs, ys, pred, hana::if_(pred(hana::front(ys), hana::front(xs)), hana::true_c, hana::false_c)); }


        template <typename Xs, typename Ys, typename Pred>
        static constexpr auto
        helper(Xs const&, Ys const& ys, Pred const&, hana::true_)
        { return hana::not_(hana::is_empty(ys)); }

        template <typename Xs, typename Ys, typename Pred>
        static constexpr auto
        helper(Xs const& xs, Ys const& ys, Pred const& pred, hana::false_)
        { return helper1(xs, ys, pred, hana::if_(pred(hana::front(xs), hana::front(ys)), hana::true_c, hana::false_c)); }


        template <typename Xs, typename Ys, typename Pred>
        static constexpr auto apply(Xs const& xs, Ys const& ys, Pred const& pred) {
            return helper(xs, ys, pred, hana::bool_c<
                decltype(hana::is_empty(xs))::value ||
                decltype(hana::is_empty(ys))::value
            >);
        }
    };
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_LEXICOGRAPHICAL_COMPARE_HPP

/* lexicographical_compare.hpp
xEMuunm8XN5WRVMnbvsANmlUYLDJqrk7oP30Vj0/d41X4PkinJCkWsTU/arRxF43t1PIofZG+prpeZ+u1PkFTPUQNBIoXex/Rlw2jm75Vt541VKYtQlN0xRKF8BYbCPUy6aOiBppAuhdBKSWMhfd1/+qV90dZazlrG1hyw+Tk9JxGMTqV4XjdeJ8Hk5xLMambBv8iQKlUT3P6+bB75y3axjf/8BoYVrg2Wz1F+/6z0L5DERJL9MrWeVakidH/ujhAtBpgmuLgG74THgev22Rga1bn80OECEKu2X6geIBQL/7tDB478BCfsMbSGIkHI+xeA34EzjKCpV0e/BwpwVCTPMdhuurede6xm75QogVaggPi8aB1bWCFSC65yg35SXG4q23//l+0jWmEAjJ+AtuSFz4uPgS22q4pLm3qseeyISUpMGl5B4r3OLd7HMMkgz9PiK60LUcAHsKlegGH6ynI2axhvoi9PaKjfdoQod+6JnspwnBshq+DffZ2rHjUQtxEOljYJIKPjDfImSm/YG9rnmFqKAY9icbc6jn4Z2nwPA0p6L7H3Bt08aBRg==
*/