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
4o+05ZoJy4RQwtLId6f26eLIbUW+yA7NqTLBG27l0yK2G7HBjdddVgSUNW06pUjKRQ45raVW1P477G07ls9NOf3+5O7//v76b+Wz6P7sYvdnfOlU4tBP90ZbT499Fnby5NH0Xou+/qnO/MYu/3tX7vglnSxjLPv3jmjhqXbywxxHhP/EspRb1cdOHlb3Hpi9OHlPwvQcYlngo9dO6fKmv0XzFMF8LKmx2vuD3c6Jt53oV0rjkp95rn/S38epkTXg8fOxosfFmhfbpeDxc8V54XrMi1jGl3IrY/z84+e7c8Yj5Z3DPDWkvLyY8TMbp6Kvnk/qCbIDSIVPd0y98+BQYuc63JGxe2Wk3Asj48h5E+WStbuFkVGo1KFutVweqdXiiG6wVFvhW+3Qz9TpeS1Fm5hc/1sxZaVwNc/Ge07f9+COrKVN9Rs0OV6dGCnROGdPnRl8sPWP2P0a/azRdN3jeMfaSB2/OKWnpV/kBLk7/MZpkRNX7gjvLGUvm9IRAhFdZM2EtjD1i5mRnp26epnpmNQTfYbMnTrjM/cHyV7Y8Ts7x8t2TKTM48+PjeQ/6c/2v7c/p89iz5rhSrzaExGYov1Prsarp9G+Ixyr9FB1Yk/4UKcJxbHuSI/r+UydIUhqX0SLnJQLoo0uJqUqndJbA5YlnFon3W7w3yjPo+0+sifND5vg8RW0qlCtzAXe//JcvS+S5+xIDmsjFFka
*/