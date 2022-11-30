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
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
*/