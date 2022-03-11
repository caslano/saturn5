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
+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
*/