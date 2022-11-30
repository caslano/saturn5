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
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
*/