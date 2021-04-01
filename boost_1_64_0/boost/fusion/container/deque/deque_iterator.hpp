/*=============================================================================
    Copyright (c) 2005-2012 Joel de Guzman
    Copyright (c) 2005-2006 Dan Marsden

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_DEQUE_ITERATOR_26112006_2154)
#define BOOST_FUSION_DEQUE_ITERATOR_26112006_2154

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/iterator/iterator_facade.hpp>
#include <boost/fusion/container/deque/detail/keyed_element.hpp>
#include <boost/mpl/int.hpp>
#include <boost/mpl/minus.hpp>
#include <boost/mpl/equal_to.hpp>
#include <boost/mpl/identity.hpp>
#include <boost/mpl/if.hpp>
#include <boost/type_traits/is_const.hpp>
#include <boost/type_traits/add_const.hpp>
#include <boost/type_traits/add_reference.hpp>

namespace boost { namespace fusion {

    struct bidirectional_traversal_tag;

    template <typename Seq, int Pos>
    struct deque_iterator
        : iterator_facade<deque_iterator<Seq, Pos>, bidirectional_traversal_tag>
    {
        typedef Seq sequence;
        typedef mpl::int_<Pos> index;

        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        deque_iterator(Seq& seq)
            : seq_(seq)
        {}

        template<typename Iterator>
        struct value_of
            : detail::keyed_element_value_at<
            typename Iterator::sequence, typename Iterator::index>
        {};

        template<typename Iterator>
        struct deref
        {
            typedef typename detail::keyed_element_value_at<
                typename Iterator::sequence, typename Iterator::index>::type element_type;

            typedef typename add_reference<
                typename mpl::eval_if<
                is_const<typename Iterator::sequence>,
                add_const<element_type>,
                mpl::identity<element_type> >::type>::type type;

            BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
            static type
            call(Iterator const& it)
            {
                return it.seq_.get(typename Iterator::index());
            }
        };

        template <typename Iterator, typename N>
        struct advance
        {
            typedef typename Iterator::index index;
            typedef typename Iterator::sequence sequence;
            typedef deque_iterator<sequence, index::value + N::value> type;

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
        struct distance : mpl::minus<typename I2::index, typename I1::index>
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
        BOOST_DELETED_FUNCTION(deque_iterator& operator= (deque_iterator const&))
    };

}}

#ifdef BOOST_FUSION_WORKAROUND_FOR_LWG_2408
namespace std
{
    template <typename Seq, int Pos>
    struct iterator_traits< ::boost::fusion::deque_iterator<Seq, Pos> >
    { };
}
#endif

#endif

/* deque_iterator.hpp
y+mVEgs1dCVZGMPdE9QInKUUV24nFxWzn+yO9h6wKQOgUFs0Q04iZmmBHJBFZr9oykfPEwCulW/hPMuPuEL2fmOnaSCueKMN/A5zbCrDf5Ii+Z3ycgxKBcjQ3HhoZ8ejywtikevrDk0DztRsxplqik1XHvRa8Fqt25H61YXOmp14Mzaf/hgANBveNn80FOenhQ3qwPBPl6ZCL23RhW0aZ5PcXhoq+yZShI47B+d3l+aSMhURCwPw5vwrXdiO6DCEBz3bIeeRzXadBAbcFXQAutKydygeR0i021mPA0u8h/J2bRoqTUnGx5uKAKY72em+KGGnKN+wgop7F9c0i6153Fkr2yNGqfmudSUcqJ7IRyP9z+2FQebXxbmb9pe1dcfn4iGqH/EKU4HKxx0d7TgYyPwyWtFR4blWLpx/kizs6kCkuD1xAEFjL6NHWfVSUv/OXW+7VM/CCU81Y/1eAoHAMK9x5/n55Ux2lbS8hT8Tgsn+FeA3dPc3OapL4WhMEBJTX3IdOWr9mmJPFcMC8zFydSO+uZVkX5IZW7dX0x4mzD36Tj2720D3Q2VfTw==
*/