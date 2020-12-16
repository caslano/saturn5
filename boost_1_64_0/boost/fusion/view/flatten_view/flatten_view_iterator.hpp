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
YRRYpV0E4okGGWX8MXFZGd3At8Pgqv3M1IWEHt3wrJnP0nPzIPVT0bRn7su56dptSI/U+kPafnQH6nxV7gtQuLWUH1Zv8dNllWfRx+bISjUvXdMYOUPLouXocV7Xf2zuLGnbtm5bduXIeiXbb2H0N5yXju1OnA7VVKVfCF+ckuFPBIDzVRmu8q/SQfgPphHOfIstzyBclgnhL51FuNJdvFm4D+HIK+YiCiM/JbSxNxp2dyXL1IOPvsDUgyJOQy/OBe3uP/hIS2c+Y3KP+m5O6uVb4rEGG9wvsnj9wkpsu7RkxEdhOAS9ZfG6XpzEbq6ibXO/ybiJH1tplsbiiZPy8GOT+9CgDKX7AeIaGQb3Vyze0rfsPM49GS8yAe4VFq9bFvRldohr5hjvR183RXM5avbuLrUM7fpV7fNEjV95ocSpmRu47nsd1vdSUbi55QbuVdt8NvveQ1i/j2y/jF0/qvqe0fn6mv9IxqfBLfUTu6z5u2O+rhvX5D+4zIKg9OJY8RG75oaMW9iR4+Z5obiIWY8B50lipiPr6MFHaBRA+BWEU91RuOzDfzio9gazKPO6oWe53nHsOir8Ty1c9T/gszcFXr1LamxKSvyBTbwSB74IHPEjAok/rimP7BlvstOP3VGKWo8lWCdTuFI0Fv5FFf5YCMBH0LQK1wIIf5sKf6LJx3kZhYMPe8sqfJyA+VYrsEqIvUEzS5huN+oGwKozdWD6BIww2GECk9VryhmYGiEVhnesgDVtfX9jYPVICeyDcxqjIjTyeeF6JsbzuXh9A2vk84KBNfN57gYG1sjnoRuOMZ1P3Bt7XsP+v8z8KPKu2v5TjQeN+YZVzSdwuMrnGwxn843XPI/Z+oVFJJ/aETTNzx+bNcbMN5nch4ZR6iWZEwkHZKOvH1R9mlwQ0GdL9unb6XmACl8BYH6Tf0M/olPFZurtiSkZ7gBgb6Ep7OSWbm/4yp2uwo231jBPl+G6LeHvVoc33lobzVbhTV2b31eHV2+QyuSBze3nGEWJsfvHz2XrQSuw4jAKRfNyNvi/MfmpsP2wyN2ynrBbaVAc5z5o/tzg54WdxX4i1OJufbS2OeR79XNmm2Yiy4o0SL3AiH+ptSa4/BwpM2aYa7tFOoMsVR6MGKjN+pvEkHEY+8nHGpwOW9dxvLuyOWC+Rpv46i7D16Y53lw3/qCBq9WJ+WbjDMdl9pD3Btb0fbs828CHKm7gnX1tvLu5Cvy9ClfrGHBU/PD72caXDPybEsdapy2fHgDO5PEm3YfVXjaNMvWJ17Y6kqeduBV6xBE88oEP3nACD3vwHcVDfOTtYGNVus6T3Qt2U+8BZ3WbzExoo3FVY/PvMzHl0BLY+Q8A6+ttSI0dZFhtc6Lj/CDDdvrqCe7ODmQ/xPBh71n98Z275/C3+GzH8VL3qk2WsV407VYfzcsO7PKUxlB2YF+ZBoby3Q5+zBnGbMv/CMwsu5GfWY2j7DgHGu0DNkk3sGa5xX7Go3hUi2Mv46PAWzqBtNID4EzSL4xhi2fYGGbHeSH3tYRaAxZ2TK+Ite7wh6bMoh+5TulGcSVi5U/QfIF32kx+IfLYd/ws8CqBJe8xj/Vyx2v4zlszZUqRu0nhWF4s9Lo2X7bstBbCfhsvi2/lvht5nnCjpTK1nrDsnUBZxue0Zxo+nuzQsR1LCh33HDr3pxcXKbWgudf4QVMuF2FmlVkW+FX+7KJIPStv+u+5wOvBjtzUDqyykllmQpC5yGXixMrDrIwqGZ/LPFp/J1mZQhF6tuWlgVU3qrPsLXerUnVz1/N10f4K/1VM3hFOUQaZm7q8wdDUqJOD17E6ScLIIWWKtNgyJAx/dIeu42mVnu0luVM=
*/