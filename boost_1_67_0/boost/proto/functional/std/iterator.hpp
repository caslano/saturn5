///////////////////////////////////////////////////////////////////////////////
/// \file iterator.hpp
/// Proto callables for std functions found in \<iterator\>
//
//  Copyright 2012 Eric Niebler. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PROTO_FUNCTIONAL_STD_ITERATOR_HPP_EAN_27_08_2012
#define BOOST_PROTO_FUNCTIONAL_STD_ITERATOR_HPP_EAN_27_08_2012

#include <iterator>
#include <boost/type_traits/remove_const.hpp>
#include <boost/type_traits/remove_reference.hpp>
#include <boost/proto/proto_fwd.hpp>

namespace boost { namespace proto { namespace functional
{

    // A PolymorphicFunctionObject wrapping std::advance
    struct advance
    {
        BOOST_PROTO_CALLABLE()

        typedef void result_type;

        template<typename InputIterator, typename Distance>
        void operator()(InputIterator &x, Distance n) const
        {
            std::advance(x, n);
        }
    };

    // A PolymorphicFunctionObject wrapping std::distance
    struct distance
    {
        BOOST_PROTO_CALLABLE()

        template<typename Sig>
        struct result;

        template<typename This, typename InputIter1, typename InputIter2>
        struct result<This(InputIter1, InputIter2)>
        {
            typedef
                typename std::iterator_traits<
                    typename boost::remove_const<
                        typename boost::remove_reference<InputIter1>::type
                    >::type
                >::difference_type
            type;
        };

        template<typename InputIterator>
        typename std::iterator_traits<InputIterator>::difference_type
        operator()(InputIterator first, InputIterator last) const
        {
            return std::distance(first, last);
        }
    };

    // A PolymorphicFunctionObject wrapping std::next
    struct next
    {
        BOOST_PROTO_CALLABLE()

        template<typename Sig>
        struct result;

        template<typename This, typename ForwardIterator>
        struct result<This(ForwardIterator)>
        {
            typedef
                typename boost::remove_const<
                    typename boost::remove_reference<ForwardIterator>::type
                >::type
            type;
        };

        template<typename This, typename ForwardIterator, typename Distance>
        struct result<This(ForwardIterator, Distance)>
        {
            typedef
                typename boost::remove_const<
                    typename boost::remove_reference<ForwardIterator>::type
                >::type
            type;
        };

        template<typename ForwardIterator>
        ForwardIterator operator()(ForwardIterator x) const
        {
            return std::advance(
                x
              , static_cast<typename std::iterator_traits<ForwardIterator>::difference_type>(1)
            );
        }

        template<typename ForwardIterator>
        ForwardIterator operator()(
            ForwardIterator x
          , typename std::iterator_traits<ForwardIterator>::difference_type n
        ) const
        {
            return std::advance(x, n);
        }
    };

    // A PolymorphicFunctionObject wrapping std::prior
    struct prior
    {
        BOOST_PROTO_CALLABLE()

        template<typename Sig>
        struct result;

        template<typename This, typename BidirectionalIterator>
        struct result<This(BidirectionalIterator)>
        {
            typedef
                typename boost::remove_const<
                    typename boost::remove_reference<BidirectionalIterator>::type
                >::type
            type;
        };

        template<typename This, typename BidirectionalIterator, typename Distance>
        struct result<This(BidirectionalIterator, Distance)>
        {
            typedef
                typename boost::remove_const<
                    typename boost::remove_reference<BidirectionalIterator>::type
                >::type
            type;
        };

        template<typename BidirectionalIterator>
        BidirectionalIterator operator()(BidirectionalIterator x) const
        {
            return std::advance(
                x
              , -static_cast<typename std::iterator_traits<BidirectionalIterator>::difference_type>(1)
            );
        }

        template<typename BidirectionalIterator>
        BidirectionalIterator operator()(
            BidirectionalIterator x
          , typename std::iterator_traits<BidirectionalIterator>::difference_type n
        ) const
        {
            return std::advance(x, -n);
        }
    };

}}}

#endif

/* iterator.hpp
+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
*/