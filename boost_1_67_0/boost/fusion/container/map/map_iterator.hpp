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