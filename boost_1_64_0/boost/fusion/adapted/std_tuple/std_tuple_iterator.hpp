/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_STD_TUPLE_ITERATOR_09112011_1905)
#define FUSION_STD_TUPLE_ITERATOR_09112011_1905

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/iterator/iterator_facade.hpp>
#include <boost/type_traits/is_const.hpp>
#include <boost/type_traits/remove_const.hpp>
#include <boost/fusion/support/detail/access.hpp>
#include <boost/mpl/int.hpp>
#include <boost/mpl/if.hpp>
#include <tuple>
#include <utility>

namespace boost { namespace fusion
{
    struct random_access_traversal_tag;

    template <typename Tuple, int Index>
    struct std_tuple_iterator_identity;

    template <typename Tuple, int Index>
    struct std_tuple_iterator
        : iterator_facade<
              std_tuple_iterator<Tuple, Index>
            , random_access_traversal_tag>
    {
        typedef Tuple tuple_type;
        static int const index = Index;
        typedef std_tuple_iterator_identity<
            typename add_const<Tuple>::type, Index>
        identity;

        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        explicit std_tuple_iterator(Tuple& tuple)
          : tuple(tuple) {}

        Tuple& tuple;

        template <typename Iterator>
        struct value_of
          : std::tuple_element<Iterator::index,
              typename remove_const<typename Iterator::tuple_type>::type> {};

        template <typename Iterator>
        struct deref
        {
            typedef typename value_of<Iterator>::type element;
            typedef typename
                mpl::if_<
                    is_const<typename Iterator::tuple_type>
                  , typename fusion::detail::cref_result<element>::type
                  , typename fusion::detail::ref_result<element>::type
                >::type
            type;

            BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
            static type
            call(Iterator const& iter)
            {
                return std::get<Index>(iter.tuple);
            }
        };

        template <typename Iterator, typename N>
        struct advance
        {
            static int const index = Iterator::index;
            typedef typename Iterator::tuple_type tuple_type;
            typedef std_tuple_iterator<tuple_type, index+N::value> type;

            BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
            static type
            call(Iterator const& i)
            {
                return type(i.tuple);
            }
        };

        template <typename Iterator>
        struct next : advance<Iterator, mpl::int_<1>> {};

        template <typename Iterator>
        struct prior : advance<Iterator, mpl::int_<-1>> {};

        template <typename I1, typename I2>
        struct equal_to
            : is_same<typename I1::identity, typename I2::identity> {};

        template <typename First, typename Last>
        struct distance
        {
            typedef mpl::int_<Last::index-First::index> type;

            BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
            static type
            call(First const&, Last const&)
            {
                return type();
            }
        };
    };
}}

#ifdef BOOST_FUSION_WORKAROUND_FOR_LWG_2408
namespace std
{
    template <typename Tuple, int Index>
    struct iterator_traits< ::boost::fusion::std_tuple_iterator<Tuple, Index> >
    { };
}
#endif

#endif



/* std_tuple_iterator.hpp
WREmQp7qrTHi8CEBEsB0uOUc35XGWXlMUKDLIsSlrGOD2NRj88AoA5hUaNx3rEF+rQLku3ZtskQfIrfi5JwAflwhIpx2Xx5eS1smAtYw29Uk4BsCIOi+772qwng+9WGyq+yg4v4lL1PfhAjgSud0M3KRdFR/RZCG+zdEUo4ncZe3cclG9Z3FBrRRhnJmOuQ5IcKRnoCpMrS+8+Cflt9z0XGKHBX7X7zjpCtCijP6tCjFLhIrRJ9uIn9DBDdlM/iA+vlvOOBOlKaC/8t4JuhiarUiIuVykjeVVGkhzDafDkvXygOm3VY3c5Rk22uHvU1q7lpmWUCvLsUGJ0jvuxfnujNdhMUy6CJf8P530Hkl8q/zRcDPcjQSeSx7uGggqcGL2HSk7irb4RLu+2FHDX6cKyM4K7t0ym9iTjh4tHCmpOgWj5/tKXTzYB1beBbEeMRL+heXt1BLiZe7BqkxAgfsd1gK+FTSZSPpNfDEsPjrd2vcqHAvQkmAbbhGognIFfFqqUiQiTgELUNx/RpgiBLDsBuLU+RaqN/xk6SQ+EByqfjWcCE4fC1xmtun+g==
*/