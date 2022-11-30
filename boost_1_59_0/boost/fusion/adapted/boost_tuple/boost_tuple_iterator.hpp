/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_BOOST_TUPLE_ITERATOR_09262006_1851)
#define FUSION_BOOST_TUPLE_ITERATOR_09262006_1851

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/iterator/iterator_facade.hpp>
#include <boost/type_traits/is_const.hpp>
#include <boost/type_traits/add_const.hpp>
#include <boost/mpl/identity.hpp>
#include <boost/mpl/if.hpp>
#include <boost/mpl/eval_if.hpp>
#include <boost/mpl/or.hpp>
#include <boost/mpl/plus.hpp>
#include <boost/mpl/int.hpp>
#include <boost/mpl/apply.hpp>
#include <boost/tuple/tuple.hpp>

namespace boost { namespace fusion
{
    struct forward_traversal_tag;

    namespace detail
    {
        template <typename T>
        struct boost_tuple_is_empty : mpl::false_ {};

        template <>
        struct boost_tuple_is_empty<tuples::null_type> : mpl::true_ {};

        template <>
        struct boost_tuple_is_empty<tuples::null_type const> : mpl::true_ {};

        template <>
        struct boost_tuple_is_empty<tuples::tuple<> > : mpl::true_ {};

        template <>
        struct boost_tuple_is_empty<tuples::tuple<> const> : mpl::true_ {};
    }

    template <typename Cons>
    struct boost_tuple_iterator_identity;

    template <typename Cons = tuples::null_type>
    struct boost_tuple_iterator
        : iterator_facade<boost_tuple_iterator<Cons>, forward_traversal_tag>
    {
        typedef Cons cons_type;

        typedef boost_tuple_iterator_identity<
            typename add_const<Cons>::type> identity;

        BOOST_FUSION_GPU_ENABLED
        explicit boost_tuple_iterator(Cons& in_cons)
            : cons(in_cons) {}
        Cons& cons;

        template <typename Iterator>
        struct value_of : mpl::identity<typename Iterator::cons_type::head_type> {};

        template <typename Iterator>
        struct deref
        {
            typedef typename value_of<Iterator>::type element;

            typedef typename
                mpl::if_<
                    is_const<typename Iterator::cons_type>
                  , typename tuples::access_traits<element>::const_type
                  , typename tuples::access_traits<element>::non_const_type
                >::type
            type;

            BOOST_FUSION_GPU_ENABLED
            static type
            call(Iterator const& iter)
            {
                return iter.cons.get_head();
            }
        };

        template <typename Iterator>
        struct next
        {
            typedef typename Iterator::cons_type cons_type;
            typedef typename cons_type::tail_type tail_type;

            typedef boost_tuple_iterator<
                typename mpl::eval_if<
                    is_const<cons_type>
                  , add_const<tail_type>
                  , mpl::identity<tail_type>
                >::type>
            type;

            BOOST_FUSION_GPU_ENABLED
            static type
            call(Iterator const& iter)
            {
                return type(iter.cons.get_tail());
            }
        };

        template <typename I1, typename I2>
        struct distance;

        // detail
        template <typename I1, typename I2>
        struct lazy_next_distance
        {
            typedef
                typename mpl::plus<
                    mpl::int_<1>,
                    typename distance<
                        typename next<I1>::type,
                        I2
                    >::type
                >::type type;
        };

        template <typename I1, typename I2>
        struct distance
        {
            typedef typename mpl::eval_if<
                boost::is_same<I1, I2>,
                mpl::int_<0>,
                lazy_next_distance<I1, I2>
            >::type type;

            BOOST_FUSION_GPU_ENABLED
            static type
            call(I1 const&, I2 const&)
            {
                return type();
            }
        };

        template <typename I1, typename I2>
        struct equal_to
            : is_same<typename I1::identity, typename I2::identity>
        {};

        // silence MSVC warning C4512: assignment operator could not be generated
        BOOST_DELETED_FUNCTION(boost_tuple_iterator& operator= (boost_tuple_iterator const&))
    };

    template <typename Null>
    struct boost_tuple_null_iterator
        : iterator_facade<boost_tuple_iterator<Null>, forward_traversal_tag>
    {
        typedef Null cons_type;

        typedef boost_tuple_iterator_identity<
            typename add_const<Null>::type> identity;

        template <typename I1, typename I2>
        struct equal_to
            : mpl::or_<
                is_same<I1, I2>
              , mpl::and_<
                    detail::boost_tuple_is_empty<typename I1::cons_type>
                  , detail::boost_tuple_is_empty<typename I2::cons_type>
                >
            >
        {};
    };

    template <>
    struct boost_tuple_iterator<tuples::null_type>
        : boost_tuple_null_iterator<tuples::null_type>
    {
        template <typename Cons>
        BOOST_FUSION_GPU_ENABLED
        explicit boost_tuple_iterator(Cons const&) {}
    };

    template <>
    struct boost_tuple_iterator<tuples::null_type const>
        : boost_tuple_null_iterator<tuples::null_type const>
    {
        template <typename Cons>
        BOOST_FUSION_GPU_ENABLED
        explicit boost_tuple_iterator(Cons const&) {}
    };

    template <>
    struct boost_tuple_iterator<tuples::tuple<> >
        : boost_tuple_null_iterator<tuples::tuple<> >
    {
        template <typename Cons>
        BOOST_FUSION_GPU_ENABLED
        explicit boost_tuple_iterator(Cons const&) {}
    };

    template <>
    struct boost_tuple_iterator<tuples::tuple<> const>
        : boost_tuple_null_iterator<tuples::tuple<> const>
    {
        template <typename Cons>
        BOOST_FUSION_GPU_ENABLED
        explicit boost_tuple_iterator(Cons const&) {}
    };
}}

#ifdef BOOST_FUSION_WORKAROUND_FOR_LWG_2408
namespace std
{
    template <typename Cons>
    struct iterator_traits< ::boost::fusion::boost_tuple_iterator<Cons> >
    { };
}
#endif

#endif



/* boost_tuple_iterator.hpp
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
*/