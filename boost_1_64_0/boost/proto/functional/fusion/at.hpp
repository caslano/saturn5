///////////////////////////////////////////////////////////////////////////////
/// \file at.hpp
/// Proto callables Fusion at
//
//  Copyright 2010 Eric Niebler. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PROTO_FUNCTIONAL_FUSION_AT_HPP_EAN_11_27_2010
#define BOOST_PROTO_FUNCTIONAL_FUSION_AT_HPP_EAN_11_27_2010

#include <boost/type_traits/add_const.hpp>
#include <boost/type_traits/remove_const.hpp>
#include <boost/type_traits/remove_reference.hpp>
#include <boost/fusion/include/at.hpp>
#include <boost/proto/proto_fwd.hpp>

namespace boost { namespace proto { namespace functional
{
    /// \brief A PolymorphicFunctionObject type that invokes the
    /// \c fusion::at() accessor on its argument.
    ///
    /// A PolymorphicFunctionObject type that invokes the
    /// \c fusion::at() accessor on its argument.
    struct at
    {
        BOOST_PROTO_CALLABLE()

        template<typename Sig>
        struct result;

        template<typename This, typename Seq, typename N>
        struct result<This(Seq, N)>
          : fusion::result_of::at<
                typename boost::remove_reference<Seq>::type
              , typename boost::remove_const<typename boost::remove_reference<N>::type>::type
            >
        {};

        template<typename Seq, typename N>
        typename fusion::result_of::at<Seq, N>::type
        operator ()(Seq &seq, N const & BOOST_PROTO_DISABLE_IF_IS_CONST(Seq)) const
        {
            return fusion::at<N>(seq);
        }

        template<typename Seq, typename N>
        typename fusion::result_of::at<Seq const, N>::type
        operator ()(Seq const &seq, N const &) const
        {
            return fusion::at<N>(seq);
        }
    };
}}}

#endif

/* at.hpp
s+j+YwLlfibX11hd8onh3XeOQILB1dvXGU6YGTcx8A8mcvZW8FqMqTe2jMbru5ddsBzmAoG54DmQovoHgL0OERmr1RTOEWMblrsjC8xG4f0EV1IOeHCnMDrYvDzQalhaWY0oSrzLpYFErQYl+0LOjaZ21AUloUe3WM5RN4g9+Jib3hCrpMyiGttdkSJxv11vMU8Iv0AMVaMNSLVHMeOiUmVqAZNOT7+9YtSQA2/8Z3xWDToPDWFTrDLayZ+4rCMrql4TFJOw6fj3PVjHMLDXHtK8cP3reFf+0s9RmctP9RZNcw0hy0UuzcSVNNy4fhbHaMz4zBVYRUjN3GtnbjtNKcN38q0xApldlLpDT5MfrVcm+fQe0lFlyYkoSDUAU1/LUqI4kCtE8Y5KDVUZxWiTeJ4G7AlMCaawMC0watliWXCWd2JnQT7CDdF1euRUikdgUteirmI8iVG0He0Q0jWmLphu53dIwooQP0lpbjE9ctDmMUEm0bQIGzJzjVPI+cUT2q5n3iUs1fcyE8iWpm06DIl/um/AdqLfjwBBJRjKgwOwzTYrRGjZ8252yw==
*/