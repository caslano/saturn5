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
StepNsjO97UuXCOc1gdK06lWyMYPI3SYEKfzUTSvTWTdx510Mjsu+ydKF1lL9HyQNDy4UV/5zIfJ3sLPCQU30G88jKU4Xxi4yIcXNyL3ZZAz9ot8ZXDmfuevJS6bCe33Qu4b5sTdaTiDEcPpfcucyAdXXDL+nYGba7e/l/h28LVM1v6AWLaXFsrr9XE/+vARtWb/J8bRH1xHPzOGA6J6k4TYmuuO4tI4TtMaR+t48SHaOJaBi7uCYhIkx+6xFeffyz2OxF3a7Ww8ZUN+3Aje3Dc9XoBXPuT2NH4U3/aa2NTl88kIDV1A8/PJAK/vYFIeE4V5nQf7e2KpqdSLcm/1JCZm1NmkPnxE3fuZTOKUjej+mP/kGg+bKJ9JKk24iLL9TunXiOWQcL98M+SmCnBYNvbf1FEcNRiMO02Qb9eEAm2aljlagIrL1DHN6SSuX2rC/ZPiTW/wvH0c480g8FyfncrA/bzBAbVTT9o4Y5hX95hmCnH6ntzMyG0wWBiw4Zuj/ElQtn+WKM5uqHqe1c8LFtOczY9zLKrT2TVXWCOXTqTU/tCKuIOPmjmCGhx44HpSXEpxn54zqPHtI3XVPtO5InU6r7lDPLQNFqj9ZCGNGOT0+xPmjeTRxcjPF+RxVTCKkJ8/zLdrNi5CQH6BEO9JG5BfMMjzijvZRxYK8rxBizVYZwtrTbFVr7ol7IWU/yKKE3e6oUrlDJ75RYO8nIlz2osZfKkq+KLqY2OCXOA+2eKdeHG49JKYRldQE7i32R3F6zSwjD0hjVuT/WeJICf8z2vklgxyYoM527aU4uTnh9VnhpFfOsQv6+OX8fFhvy6reb12h/NeLsCJJleBCpdtenmDbzXDPluhEy8Ol+jBNFY0NV647lbqxNvDqu2v7NOEy7FKJ96Yg6wqNbhlTi4Jp/NTQnF6fdBqfkxGwPIkQ5zaWoVxU5ofDbbltI8L+6M3gg/6dHWfJuyPNSL4YBqZoIZPeOpbmiFet/W1Qpzeh94X4poOtC1Pzjv7Q7zuJ1mT0/0EuQHJ+bbFUZ6DQU7vdkN/rO3jxaYGfATOT6v5ObHWVLETMJ5XuIiH2zwQL/hw/Q6qdXy4fu/JugoXhVPlx/Kt9wtj5wEmV1XFcVCkCgqCIEiVJjXZEAhgYbM7SRaSzbKzCYmAw+zM282Q3Zll3kxIEATsvWIXEZEiIEUpNsAGAjawIIiKiICiSMcu3nfO/95zbpno9/F9ZP+/8245t7w77zbFzBjAbwd4l60IbeK2QmGtTNkFcwavi2zSbeZ4sWvVxv16fELIgnv9Tox5a4a+nDJ/vcfj90Ul4llT85M8HtffasSl/o5HTOb1axGT+lmPmPTjmWJBP8zz2sLRy3LZT4qONQbVWqdbnaKDUxD2qsiGAqh2Mv691oi4nM9wcshc9eb4V/fglXqrmcFmqocNuRTzMdPrs2nwGW62bJqRbTc3lNLbithpFI59dkbxsB84RTFu57zV2+a1HfG4H8iVTadt2i/0jqc3DeA4u6Kv7eRxua9xHBlBPk4t9LHFSxdWymNLR3HcGNK51mf8eWKqNVl8LmjUuQ2v8234Zwd+K/DPD07faQk75phT97nby3i60+Vu/DOsJikyycE8usfoVyjFf6avz3THpxo1+iiMOXXH5R1yttZoiS42roO/iXiF1g6srJSW9y92Xzf4vs0k5wTgMz/ZvWU9do0872ZtrttvTdqJE/JOq23bytt62lY6Dfjk7Wkbk1lO1zuSnD+t6vS/s7edS3+fsXtXT7tKTlNwFVUD7Bx9z2ckH+8pbExBT001qsH6FuLvVTwYnRJ/X8iDPv79AQ/fAR9QPBiBUn39oOb1zEvbhxQL1tI=
*/