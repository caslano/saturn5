#ifndef BOOST_METAPARSE_V1_UTIL_IN_RANGE_HPP
#define BOOST_METAPARSE_V1_UTIL_IN_RANGE_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2009 - 2010.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/mpl/less_equal.hpp>
#include <boost/mpl/comparison.hpp>
#include <boost/mpl/quote.hpp>
#include <boost/mpl/bool.hpp>

#include <boost/mpl/vector.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      namespace util
      {
        template <
          class LowerBound = boost::mpl::na,
          class UpperBound = boost::mpl::na,
          class Item = boost::mpl::na
        >
        struct in_range :
          boost::mpl::bool_<
            boost::mpl::less_equal<LowerBound, Item>::type::value
            && boost::mpl::less_equal<Item, UpperBound>::type::value
          >
        {};

        template <class LowerBound, class UpperBound>
        struct in_range<LowerBound, UpperBound, boost::mpl::na>
        {
          typedef in_range type;

          template <class Item = boost::mpl::na>
          struct apply : in_range<LowerBound, UpperBound, Item> {};
        };

        template <class LowerBound>
        struct in_range<LowerBound, boost::mpl::na, boost::mpl::na>
        {
          typedef in_range type;

          template <
            class UpperBound = boost::mpl::na,
            class Item = boost::mpl::na
          >
          struct apply : in_range<LowerBound, UpperBound, Item> {};
        };

        template <>
        struct in_range<boost::mpl::na, boost::mpl::na, boost::mpl::na>
        {
          typedef in_range type;

          template <
            class LowerBound = boost::mpl::na,
            class UpperBound = boost::mpl::na,
            class Item = boost::mpl::na
          >
          struct apply : in_range<LowerBound, UpperBound, Item> {};
        };
      }
    }
  }
}

#endif


/* in_range.hpp
XuOh7fXeZfl3Y8g+aUlqR2/4nQ/T91ve+p7kMNVeiWSqmKZk636kJwDfSqH0bmuyb7RnW5dT/8l+8ffW+8ROkAxTG5FaJL+11ve6MnYueyqeJ+/b1Ar63lSqXlz86z0SHdsup/ydNoASr/Te4rG+D9C86lqXjlggEqdhpF7OBrHQAVYTdBQtzQ2DTMW3UhL1vq6h4tMhpK4odFT2mvZndcTQRfLHVtN9S8+OzBU6Km+l70lG2iNfCyf4KUQXLUfUhmBae+is+NsYxeMrk9otl8ByY6p1iYNfwxbwG2eu+SdWVXqTPeZuRf9dJLvvD/IXb0DV/jK3Evrp9y0ayd+pB1zTdNFudwLOrXR/+y4uj11J1dFUyTNc/hIRG1uAOK9z1aK3vgdTzOvwORrKFOKhFaMwIFz3remKL5QDjNXbxhotQHx6Kn/ENuqWVDBimISsm6b9L7/eS1nIX/xI9pX2iNO99L2ztpsxYfo+73fpW5O6y1shbjMFmts3ACRXAvGiCKz6aEU5HUYg2zTKrmsCO8uj6dVF9y1NZZdRin9YAp7NRmbX8pIvRf4hjfmee6TeygMZ1gTiDuqDdBn5Px4jwb7KcLn8At2WRlCt0xVr+MWQainnd+dOzuo/GOTThz8b6+j8WC9+jTzQ93cEX7AfUKAMYMlAxfc36z1hHZ2XDyAOGUvfZ+guFNcRVsVl/k6aIvu0NancNWktVW+Kclyj2otZuh/dVDx+lyXn2y9+mruXxSDQlFQxhaYLmis+o55cpInuqlPtqDVlzcS0t3b+OvoU1qaL9tNYxcu0jeSdACh6X+/r9PZopjatTnP0fahOe+9JVui7D7V6DUbBLF2mcvfS91b74Oe4TeebjvwieWTfqztfPtP8cyPlrFCKnSMpSxn0KbJU7RV9sFoFosEC7Vfz9Z66IiRmfUCMKwZdnqH6PiUAxLvhiHH+pu4LsjuDUmCwRWftfmd9r6Hn0HH6yLH6VUAlrV8jJ80/d1JupaVvkN7HOmt9TCL7TjcqPwUesvWR3oQwsDONaShTv4RQX5Mrzl7fa6ibCk1zoP9MZA9VcmH/Ow+XHNn06Yxoa50f+j6gnc4PC1KnyjJ4FfR5WC09qaqmt/EfOuv9/RaE/HaRNlxlkmwbrP2gMKn56yCOUOTMRpuM+24YHJNj4dBNS+TTbK+gJxkXQpD0az6dv1ayN/aSOqMPQuc56ntdleWur/fZSXo/3kDxwSDp66vvpyvA9Lch2q9e6Hv7jyAuyH55quhXwXaAuxflb29AWTs9Qcknx5u13gqZVSE7W1vfLQ3KtTuKf1QkZfsHfT+YRh/U08f+drPInj4AYvVTUgPkY7wxRO+R9LK6eymyUfchHiqNIoK13+vKGCNbqrVqnO+s+EcrR32frHiZn96zhup9dmsQY+oDRk7Te5Ujsockc26J4SYrvFwJrV/dMIoMgGm8wuQvqxvJ36nvcX6InxycTXQ8rd7tTP9pGHMJcSIIcPSODfzkf94j31w51bUpLftFvuEC5eQv6Wit7ytg71OHxmvpWlqtKmCwvtC/qNnZVN7BIT6KrybJnnQAsbYf2RVbFV/4rv2vg95Th+p92G7N51Tdt+IB0SdBTK0P3eopOi9H0drIo9pfLJ30/RbZjWX03lsbRTlFDxfryN+bQ+u3jb53+QPVirYG6+Oi7yEq63tdB4BLQUBcGfn/bHWf1tk4MFzfQ8hIbajZec8XMEPYDgXkP/hoKv8V1TwctT4qUPbKHpBQVvazO1hjGTGLEvT7NNoFloukmQ6Mq/Ew3a5VUTNG71nbyv7bqPmnp/xf9MNTx1213x/T9x86RDL6oMxFfUN0Jh7QoLLsK+2n0w0=
*/