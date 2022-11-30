/*=============================================================================
    Copyright (c) 2009 Christopher Schmidt

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_FUSION_ITERATOR_BASIC_ITERATOR_HPP
#define BOOST_FUSION_ITERATOR_BASIC_ITERATOR_HPP

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/iterator/iterator_facade.hpp>

#include <boost/mpl/and.hpp>
#include <boost/mpl/equal_to.hpp>
#include <boost/mpl/minus.hpp>
#include <boost/mpl/int.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/type_traits/remove_const.hpp>

namespace boost { namespace fusion
{
    namespace extension
    {
        template <typename>
        struct value_of_impl;

        template <typename>
        struct deref_impl;

        template <typename>
        struct value_of_data_impl;

        template <typename>
        struct key_of_impl;

        template <typename>
        struct deref_data_impl;
    }

    template<typename Tag, typename Category, typename Seq, int Index>
    struct basic_iterator
      : iterator_facade<basic_iterator<Tag, Category, Seq, Index>, Category>
    {
        typedef mpl::int_<Index> index;
        typedef Seq seq_type;

        template <typename It>
        struct value_of
          : extension::value_of_impl<Tag>::template apply<It>
        {};

        template <typename It>
        struct deref
          : extension::deref_impl<Tag>::template apply<It>
        {};

        template <typename It>
        struct value_of_data
          : extension::value_of_data_impl<Tag>::template apply<It>
        {};

        template <typename It>
        struct key_of
          : extension::key_of_impl<Tag>::template apply<It>
        {};

        template <typename It>
        struct deref_data
          : extension::deref_data_impl<Tag>::template apply<It>
        {};

        template <typename It, typename N>
        struct advance
        {
            typedef
                basic_iterator<Tag, Category, Seq, Index + N::value>
            type;

            BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
            static type
            call(It const& it)
            {
                return type(*it.seq,0);
            }
        };

        template <typename It>
        struct next
          : advance<It, mpl::int_<1> >
        {};

        template <typename It>
        struct prior
          : advance<It, mpl::int_<-1> >
        {};

        template <typename It1, typename It2>
        struct distance
        {
            typedef mpl::minus<typename It2::index, typename It1::index> type;

            BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
            static
            type
            call(It1 const&, It2 const&)
            {
                return type();
            }
        };

        template <typename It1, typename It2>
        struct equal_to
          : mpl::and_<
                is_same<
                    typename remove_const<typename It1::seq_type>::type
                  , typename remove_const<typename It2::seq_type>::type
                >
              , mpl::equal_to<typename It1::index,typename It2::index>
            >
        {};

        template<typename OtherSeq>
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        basic_iterator(basic_iterator<Tag,Category,OtherSeq,Index> const& it)
          : seq(it.seq)
        {}

        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        basic_iterator(Seq& in_seq, int)
          : seq(&in_seq)
        {}

        template<typename OtherSeq>
        BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        basic_iterator&
        operator=(basic_iterator<Tag,Category,OtherSeq,Index> const& it)
        {
            seq=it.seq;
            return *this;
        }

        Seq* seq;
    };
}}

#ifdef BOOST_FUSION_WORKAROUND_FOR_LWG_2408
namespace std
{
    template <typename Tag, typename Category, typename Seq, int Index>
    struct iterator_traits< ::boost::fusion::basic_iterator<Tag, Category, Seq, Index> >
    { };
}
#endif

#endif

/* basic_iterator.hpp
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
*/