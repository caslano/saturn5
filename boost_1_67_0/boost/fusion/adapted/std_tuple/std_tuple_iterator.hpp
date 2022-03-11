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
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
*/