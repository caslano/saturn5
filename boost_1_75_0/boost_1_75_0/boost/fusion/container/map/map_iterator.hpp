/*=============================================================================
    Copyright (c) 2005-2013 Joel de Guzman
    Copyright (c) 2005-2006 Dan Marsden

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_MAP_ITERATOR_02042013_0835)
#define BOOST_FUSION_MAP_ITERATOR_02042013_0835

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/iterator/iterator_facade.hpp>
#include <boost/mpl/minus.hpp>
#include <boost/mpl/equal_to.hpp>
#include <boost/mpl/if.hpp>
#include <boost/utility/declval.hpp>
#include <boost/type_traits/is_const.hpp>
#include <boost/type_traits/add_const.hpp>

namespace boost { namespace fusion
{
    struct random_access_traversal_tag;

    template <typename Seq, int Pos>
    struct map_iterator
        : iterator_facade<
            map_iterator<Seq, Pos>
          , typename Seq::category>
    {
        typedef Seq sequence;
        typedef mpl::int_<Pos> index;

        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        map_iterator(Seq& seq)
            : seq_(seq)
        {}

        template<typename Iterator>
        struct value_of
        {
            typedef typename Iterator::sequence sequence;
            typedef typename Iterator::index index;
            typedef
                decltype(boost::declval<sequence>().get_val(index()))
            type;
        };

        template<typename Iterator>
        struct value_of_data
        {
            typedef typename Iterator::sequence sequence;
            typedef typename Iterator::index index;
            typedef
                decltype(boost::declval<sequence>().get_val(index()).second)
            type;
        };

        template<typename Iterator>
        struct key_of
        {
            typedef typename Iterator::sequence sequence;
            typedef typename Iterator::index index;
            typedef decltype(boost::declval<sequence>().get_key(index())) key_identity_type;
            typedef typename key_identity_type::type type;
        };

        template<typename Iterator>
        struct deref
        {
            typedef typename Iterator::sequence sequence;
            typedef typename Iterator::index index;
            typedef
                decltype(boost::declval<sequence>().get(index()))
            type;

            BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
            static type
            call(Iterator const& it)
            {
                return it.seq_.get(typename Iterator::index());
            }
        };

        template<typename Iterator>
        struct deref_data
        {
            typedef typename Iterator::sequence sequence;
            typedef typename Iterator::index index;

            typedef decltype(boost::declval<sequence>().get(index()).second) second_type_;

            typedef typename
                mpl::if_<
                    is_const<sequence>
                  , typename add_const<second_type_>::type
                  , second_type_
                >::type
            second_type;

            typedef typename add_reference<second_type>::type type;

            BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
            static type
            call(Iterator const& it)
            {
                return it.seq_.get(typename Iterator::index()).second;
            }
        };

        template <typename Iterator, typename N>
        struct advance
        {
            typedef typename Iterator::index index;
            typedef typename Iterator::sequence sequence;
            typedef map_iterator<sequence, index::value + N::value> type;

            BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
            static type
            call(Iterator const& i)
            {
                return type(i.seq_);
            }
        };

        template<typename Iterator>
        struct next
            : advance<Iterator, mpl::int_<1> >
        {};

        template<typename Iterator>
        struct prior
            : advance<Iterator, mpl::int_<-1> >
        {};

        template <typename I1, typename I2>
        struct distance
        {
            typedef typename
                mpl::minus<
                    typename I2::index, typename I1::index
                >::type
            type;

            BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
            static type
            call(I1 const&, I2 const&)
            {
                return type();
            }
        };

        template<typename I1, typename I2>
        struct equal_to
            : mpl::equal_to<typename I1::index, typename I2::index>
        {};

        Seq& seq_;

        // silence MSVC warning C4512: assignment operator could not be generated
        BOOST_DELETED_FUNCTION(map_iterator& operator= (map_iterator const&))
    };

}}

#ifdef BOOST_FUSION_WORKAROUND_FOR_LWG_2408
namespace std
{
    template <typename Seq, int Pos>
    struct iterator_traits< ::boost::fusion::map_iterator<Seq, Pos> >
    { };
}
#endif

#endif

/* map_iterator.hpp
5Cf7wCNyJWXo98WQlYSGFe9Kj2BY8Q4Wkkp7nuQ0n4cHNjTaPWWWWd5jhMk6a9rv+uLyZSvfg8dbNBdvGF0aJQBCKUY7xitHc8p/IGX5nEDNQtwM2gCQF3uVjd6e287ofj7aSkbN+r4K3K59yJ/3Kp9D1IZXgO80C6cBROxet+hOzD3ewAx9OfyQ0/1nnicPzRNwet0reuA0bfQqz/M0kRDcGlwLYgEUjWRU365Wm5oy11T6iWhuRMTKQHwNBPriUDut98NycvvojNmLHzbsyYgsiQ/HsX1MT5NXn026yMWL14RY2c0Lc7GyOUDPPfc+R7aPnzPZ2Q2bx8JfzzaPMx86wzxW/2/zOOGVJvN48qX/u3m8uOXzqL50tnlsUlnoPN5f2HQe7ywMmUdPYUvmcXefM86jptA8vjob53He7GbegWkq3/jFPJVNhSY+fjDMgD7KSvSCKQksJyn9c/Hpt3y3v73YeD3auvz0828sOgpyrB/iRKMDDpye1+CHfCMGwwrPkGDCgkntWaRr/csWC4t0wVLiwprrWz/t5kmoEJvJyZpPnJ3F3fQE0lRII1U62p6BCGmMAlEl3t4SWJBLF0VtIrOA9BbMtsmt+vIJcqNsRs4LZybt6jNboB37FE1NzLPNzgmYIGsb1Ockjx2DgzefWvG/WsxLNQDUawINSJqh+ZyGN8+7cGpqaGokjm3y9tx+RhwjVxXb1VYv
*/