/*==============================================================================
    Copyright (c) 2013 Jamboree

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#ifndef BOOST_FUSION_FLATTEN_VIEW_ITERATOR_HPP_INCLUDED
#define BOOST_FUSION_FLATTEN_VIEW_ITERATOR_HPP_INCLUDED


#include <boost/fusion/support/config.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/mpl/eval_if.hpp>
#include <boost/type_traits/remove_reference.hpp>
#include <boost/fusion/container/list/cons.hpp>
#include <boost/fusion/support/unused.hpp>
#include <boost/fusion/include/equal_to.hpp>
#include <boost/fusion/iterator/next.hpp>
#include <boost/fusion/iterator/deref.hpp>
#include <boost/fusion/iterator/value_of.hpp>


namespace boost { namespace fusion
{
    struct forward_traversal_tag;
    struct flatten_view_iterator_tag;

    template<class First, class Base>
    struct flatten_view_iterator
      : iterator_base<flatten_view_iterator<First, Base> >
    {
        typedef flatten_view_iterator_tag fusion_tag;
        typedef forward_traversal_tag category;

        typedef convert_iterator<First> first_converter;
        typedef typename first_converter::type first_type;
        typedef Base base_type;

        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        flatten_view_iterator(First const& first, Base const& base)
          : first(first), base(base)
        {}

        first_type first;
        base_type base;
    };
}}

namespace boost { namespace fusion { namespace detail
{
    template<class Iterator, class = void>
    struct make_descent_cons
    {
        typedef cons<Iterator> type;

        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        static inline type apply(Iterator const& it)
        {
            return type(it);
        }
    };

    template<class Iterator>
    struct make_descent_cons<Iterator,
        typename enable_if<traits::is_sequence<
            typename result_of::value_of<Iterator>::type> >::type>
    {
        // we use 'value_of' above for convenience, assuming the value won't be reference,
        // while we must use the regular 'deref' here for const issues...
        typedef typename
            remove_reference<typename result_of::deref<Iterator>::type>::type
        sub_sequence;

        typedef typename
            result_of::begin<sub_sequence>::type
        sub_begin;

        typedef cons<Iterator, typename make_descent_cons<sub_begin>::type> type;

        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        static inline type apply(Iterator const& it)
        {
            return type(it, make_descent_cons<sub_begin>::apply(
                fusion::begin(*it)));
        }
    };

    template<class Cons, class Base>
    struct build_flatten_view_iterator;

    template<class Car, class Base>
    struct build_flatten_view_iterator<cons<Car>, Base>
    {
        typedef flatten_view_iterator<Car, Base> type;

        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        static inline type apply(cons<Car> const& cons, Base const& base)
        {
            return type(cons.car, base);
        }
    };

    template<class Car, class Cdr, class Base>
    struct build_flatten_view_iterator<cons<Car, Cdr>, Base>
    {
        typedef flatten_view_iterator<Car, Base> next_base;
        typedef build_flatten_view_iterator<Cdr, next_base> next;
        typedef typename next::type type;

        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        static inline type apply(cons<Car, Cdr> const& cons, Base const& base)
        {
            return next::apply(cons.cdr, next_base(cons.car, base));
        }
    };

    template<class Base, class Iterator, class = void>
    struct seek_descent
    {
        typedef make_descent_cons<Iterator> make_descent_cons_;
        typedef typename make_descent_cons_::type cons_type;
        typedef
            build_flatten_view_iterator<cons_type, Base>
        build_flatten_view_iterator_;
        typedef typename build_flatten_view_iterator_::type type;

        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        static inline type apply(Base const& base, Iterator const& it)
        {
            return build_flatten_view_iterator_::apply(
                make_descent_cons_::apply(it), base);
        }
    };

    template<class Base, class Iterator>
    struct seek_descent<Base, Iterator,
        typename enable_if<
            result_of::equal_to<Iterator, typename result_of::end<
                    typename result_of::value_of<Base>::type>::type> >::type>
    {
        typedef typename result_of::next<Base>::type type;

        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        static inline type apply(Base const& base, Iterator const&)
        {
            return fusion::next(base);
        }
    };
}}}

namespace boost { namespace fusion { namespace extension
{
    template<>
    struct next_impl<flatten_view_iterator_tag>
    {
        template<typename Iterator>
        struct apply
        {
            typedef typename Iterator::first_type first_type;
            typedef typename Iterator::base_type base_type;
            typedef typename result_of::next<first_type>::type next_type;

            typedef detail::seek_descent<base_type, next_type> seek_descent;
            typedef typename seek_descent::type type;

            BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
            static inline
            type call(Iterator const& it)
            {
                return seek_descent::apply(it.base, fusion::next(it.first));
            }
        };
    };

    template<>
    struct deref_impl<flatten_view_iterator_tag>
    {
        template<typename Iterator>
        struct apply
        {
            typedef typename
                result_of::deref<typename Iterator::first_type>::type
            type;

            BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
            static inline
            type call(Iterator const& it)
            {
                return *it.first;
            }
        };
    };

    template<>
    struct value_of_impl<flatten_view_iterator_tag>
    {
        template<typename Iterator>
        struct apply
        {
            typedef typename
                result_of::value_of<typename Iterator::first_type>::type
            type;
        };
    };
}}}

#ifdef BOOST_FUSION_WORKAROUND_FOR_LWG_2408
namespace std
{
    template <typename First, typename Base>
    struct iterator_traits< ::boost::fusion::flatten_view_iterator<First, Base> >
    { };
}
#endif


#endif


/* flatten_view_iterator.hpp
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
*/