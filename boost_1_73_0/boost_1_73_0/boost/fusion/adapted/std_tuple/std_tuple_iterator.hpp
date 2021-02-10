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
PB96SEzUptWgEuBVvaGs8czOKATjl12L+2rtwNBSIhlBydDZxvQXARifZGvIZN+4Z5Aj4RFWFBI2JgEH/1rCzVVKkhGsDzNV9C1rMNFhai8kKyTiB+faSKKoZaHqAlsFtINKDYKhiAUcYHfykWWVx0JcLHLgLRgVSHBJVLaAaVp6gsbTtatMh1fxCnnK4pgXVim8vdN8NtBLtw0s4Xce8Uy5VcjfCMJQj5mew9cM8aKuDAE8XSVwKlzNj8SEsDcGNWV2IU4Bzx6SPkk8oxZxJcUbzMlrbMpecf86zOrS3NU5xmmJprTIMHmjiiztfsptXBFs4WKookoH3KNmDMQ9IBpEQqHoch8KjzheuCoOIVZxtra7c8aOhRgtKcBGc6OMFu86qVgdh0/GhbxXMGHN2hdgTBPDOE9iE44tUPT4/10c6swfRWTv/iXPoKl0DKnzkne2Mj7i1KS25P/RYBEWfV2hTpB7aJ4MPvfYCudOO9RDjljektk/h73wcnR9PXp/Pep1eZ9qOgdCcXBm0r8YTB4NI7FlxUK2e6u6vPRz5/pn92Z83VedIlNhu5Ni+7eD3Q9FuTrBVmezE354Sv9R9Hg15AdfrISt5v8ZKMLYsU0HUWmB0RF5M/UJ65/Uf1Uns6JZ9113cN19O7hG
*/