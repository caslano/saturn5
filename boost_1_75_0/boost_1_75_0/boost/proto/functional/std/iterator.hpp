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
ouUeNDy4cH/kxnn2/QLBn7bOwgXW7aobmFrRV1vGGWDmThE3EezAqr/wgzJMsSu+cn52Cj86XalA8yMZ6Hnxqx32eidQ3oJmMlBNHha/90pYix/XXezwK3wDQoFdSKjB0E2ccERAglToJzG9T8UNw/FveoXMm8wG7KvTy+vF60h54rNiOJw5Bub0Gr0M2x/k5XhO+OJEvC388Y6PpPdiEIKBbHxV0PVy0hD900AQvbOFsyGhs+WNf51lrQuhXCsBRkM2326HWTzRa//vZlrnAdVYIJxt25WGGxeMoAQcGIDjeTFyxZR015xtTAtEGdKLG2I29ayCbYIH3lGn6m3MXE7Kw0ZVLQ6+b7wSIdtgXy5BWI2knE4njbS/SbiXt6osTkGDwcalZvVL9WIPB3W8WFJ3+lI0J/xju7augU313aHaYeeHauBin+o+mCuBgtPVVjwEiBCeEGl9UtgqFvuz+niKDrrLkdydths6Dd1pR9z/Nv428dT2D5nk5D8NE5apKEMG6DW1zZUa1JIBemM22EUFXcc+WAp9GGE09AjtSN3PdOheIVc6Etl9nUdjXa569SsHMnWexJAqpwL1TO3RzFOdHvjBN13/2Zts5tRUDHHw5cPxg2k9y4EAdnTCt8q4jTdZSvOXIkOmc9QbSgbylGIOaxGZ3SkaNyYAEcvh6W8pf9oWmt1wbJprpcS3kXB8JH+wlfnYF++wl0WQ
*/