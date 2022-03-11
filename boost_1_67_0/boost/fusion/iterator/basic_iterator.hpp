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