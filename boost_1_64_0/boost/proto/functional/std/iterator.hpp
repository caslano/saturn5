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
G8w3JgtYfXne/hzB9zy8ZvU8fB+0LN6wHIgrgFyKZVbPDoX5amRWXy4D63we/v8BYCMyay9NgflesHNZQWat3yYya8+XvgDvq70A76uBtbwAP6POqkGPfpk/9P80W1+/u21E5gtZThjCn3PJwvtlr8jnUrI4w6Jf1JiGxcviDUuDuEywHJmVZwHMt4cs0bBKmVXfKTDfBZDnlbIkw+6GXPplCYaNyryGjUMNX0EN0YN2XILMikuTWb1eByxflmzY3jDfETKrZ3VgV4J1ygKGDchSDPtEZq3RvJdsS5RZ860JcZuD7Sqz+lkps2o/C+JarTg97pOF/5+Je4chfL2WhV/f3SfyvR6wEbD3wCadGiJMj9iXtQdDee77izw39ATCpriDPXsd4LbVZLG/aZsXZbvsMM8Cie64TWTe34rTx5auuEMiciky5zuicA/XmEd6Cg9z2/5OnGPOfBUR87ntOGfMCNPjFFfcMR5PjTuuXuYz4ppcdqBnnt9tra4xI+3WCHP3pcvsy2Z7PuKyozwF27rj+iPi3PZyxBq5c3nDZcdG1PeeM6ZjzpiTMOY0jOl5xe6ZT2b1JVGWbMyXCXHrR8a596ArLtL2kEXW5zz3dtl+Eefv0Ihc3FYFdopjTs+cda93WeS6X2zmmTXfla64A/Tv7nPU5phzjpwx73CtUWRfHoSe9YG94Moz0obB3gb7EOxzyGUGLHrIHjNOZvUlWWZdP9OcuIjrpz4yZcnGNWtLWaph5bKAYXVgrbI4w+5w1RBp3bJ4w56V+V3mrv0NWYJR++dQX8KrrutuhAVlVg2rybzGPWcdV1zkvSoPxtwerFRm9ewg2WrWvUMWfq5xuOewQ91n81aZ3zibD7ossoZnoWfDrrjIXD6UBUPPGco9m+41Z59/Fjs8ZxWeAyvdcSvLUkN26C/G3GKHAldcpWf+X8xXLlshZFW/iNtz4wtcYx7k2azYFVfT6Yo7+hdxlYcNu+KOc9/D9Zhx2f4Rtae8NpdnmWc+1zV52202lIXjjvBsnxe2+XUP8OhX1Kxl9qyte8B+B3R3hc2r34Pz/WS5PVmyA94ZOjFs6fPpfjW/TLaW7KJP9/o6bMUasMUjk60pOzOxe9GwTctGo2WyNWTr773RA2EbWkhxofkyZfd3bl0atqqFZ5sxa6vL1n3xzhedMWXhuNVkUXsUZ4StaRGPxx+yVWWBbZ/aKmxt/rn6MmTrrn3lWmHrU8Y9oflWkc0/cldV2Op0ASkLxa0s+3bp/O/CNrmYx1McspVk2931kVNf/uIaM2TpshXfPbvD6fUS6ktovhVl69/kiwvbuCw3ZCvInrjk4vOdddAnqQ0hW1523QbnHRa2LtlAyNJkV+Vv+LBTw5Jza7Sc7KYP7rjYGVMX8sKQpcouWu2pVmcdfrIFZLJlZZX9Tx7o9GwZ9dMrkwVllyWUPuHUsKL6EhpzGdn3x/QdE7bc9Llep8j2Tl4o09mfK6m+eTLZ0rK7n9ulJWwNq3g8HaG4gOyj55KdPHMzlGeo10vJ5m/0r+zErao/hCxZtuetVy3tmC50FaExl5Qt9VzeO04uq8/tsyRZwyVjx4etJXNuHZaQHfHSOy+HLXONOUuUHT715uth0yFw6kuQbTyx4i1hK8yaq2Ex2YlnLLaRM9/aHk9pyOJlX2489LGT57oeT3vobC4qC45t+FrYOvSiUu2CMplfdtQtjVNhy9aVoTtki8hOfnCDY50ztvVczxaWPfZgYY5j28ztJZ9s9SuXS3LO37bag1Ey2UKydRZ95tawlRXpHO0ok8XK9hoqvjJsAzfO7d0FZd9sMej0rOUmj2cyZF5Z5ujDjzjrd7PH4w3NFyO7YqU=
*/