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
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
*/