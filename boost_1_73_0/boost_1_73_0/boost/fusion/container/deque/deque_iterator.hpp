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
Upa/3jJ5jNLZBzpB7sqcBdT2oiNY6c01nLBWcks3OSt27SrRheQtH1MJ2FbDkBXTZ740YiAzjCpnkNe2H/9i5tFyMuFh0pmq4ITs/J/SLeAgMqcmTi+85ZF/t7m5mZsoYJZQeLVNlJ6Y5BAGnKTZrss9Qj5eXVzA0CPRjflsEnoA+SIGmvkAk14/ODYMSLKJ1mF15Tj6pH6sOI9KoxvHzFUw/VtCsX1lE/HZEc7ikfPsKlnscB7fcnQmKHEJZrQ7Izom/S9G6Jp0ehN6514yy+W1N9qHcmyfK6yUk/p2/2MRXG42dskZqVA/02V8OH7M4gAlhXAJKb8adPvN9hNVfhpWxBVTRhAbYNz6AakTrVQ9myUYc5VqiOuwxovb/TknfrMumrLI0QHrvti+TmSwjP44ajBiLSXfEeti8b/moFMWBEv/XlVdBFYgEJ0vONxFc07fD6LyrwjFEfcmlD5jl2rWBiZeYHJGlnnYERO8XWHQhhUbZNWFuQ6ZogkrqNNmAGjqnVvVdRURK4T7SAbOepcZOD4v6PDw6OBt6ooJZeNRV7thllcAx5dHbyd8bPy2e1dT2hLM1/vJj6nJuafZGDef2B2PPrcmrXHJAbSCfgxcrt+WieZSJcO5lKqwY4cSGFCW5U66rTqjVgyQ
*/