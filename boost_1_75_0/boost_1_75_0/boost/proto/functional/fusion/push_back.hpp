///////////////////////////////////////////////////////////////////////////////
/// \file push_back.hpp
/// Proto callables Fusion push_back
//
//  Copyright 2010 Eric Niebler. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PROTO_FUNCTIONAL_FUSION_PUSH_BACK_HPP_EAN_11_27_2010
#define BOOST_PROTO_FUNCTIONAL_FUSION_PUSH_BACK_HPP_EAN_11_27_2010

#include <boost/type_traits/add_const.hpp>
#include <boost/type_traits/remove_const.hpp>
#include <boost/type_traits/remove_reference.hpp>
#include <boost/fusion/include/push_back.hpp>
#include <boost/proto/proto_fwd.hpp>

namespace boost { namespace proto { namespace functional
{
    /// \brief A PolymorphicFunctionObject type that invokes the
    /// \c fusion::push_back() algorithm on its argument.
    ///
    /// A PolymorphicFunctionObject type that invokes the
    /// \c fusion::push_back() algorithm on its argument.
    struct push_back
    {
        BOOST_PROTO_CALLABLE()

        template<typename Sig>
        struct result;

        template<typename This, typename Seq, typename T>
        struct result<This(Seq, T)>
          : fusion::result_of::push_back<
                typename boost::add_const<typename boost::remove_reference<Seq>::type>::type
              , typename boost::remove_const<typename boost::remove_reference<T>::type>::type
            >
        {};

        template<typename Seq, typename T>
        typename fusion::result_of::push_back<Seq const, T>::type
        operator ()(Seq const &seq, T const &t) const
        {
            return fusion::push_back(seq, t);
        }
    };
}}}

#endif

/* push_back.hpp
dkM2W50ho8wl0HhZs5Sv6vXXo2I2rJdIFD3cvkKnTPeaACeedlXSszCjTOtnzXvQzcNhksvxnESqUQDp5q2a+UsHtDxXp7zLyhMhN/+yX/RR7mc/AQvYFQj8CQJFjDmOb9n71FF2vWv52L+n09/uCHJq7lBd7PY++ObAK470RyugwfW/tOtIqZ2Hix3jqT2Y89K7Tg6+e3vwvThfrDxo6Qv5i7L64Wzermimj1QRu+0ZzEUOSbpVChKFr3vBwekfMtcd3sL6cpwQCw5ShwwetzxxypuHcKebD9gAMDhonrbau0/SY/ZZcCIlQJgU3JmcLB/XmPNoPNpyM8Ey29dCR99kaQGeQ1xhz3g8ZxlJU9DOKwOjlz5CjpBIRK7TOspgqFqsU8zYzbiNy0puXA2Gqp9XhKOKYFTdbW44PZdbarR1q9xB3u/OUwFroQl+8MYy6+XcpaSXPfkgORZkobBqqSGBO8tBAskwW/q+mpWYaA7spA7B1JCysHY5O3azdUb+7bmgqIF8pHv5OWuhWH6UgRzYvXEMbWr84EjyIpoh3Ef6NOXzc5UMUJqsKPQdO6nWX550876hA8YdKXIZtYVS22ybGoV335JMadNMZF31ackvVUY0I9xJ6xCLxoqnZO72keZ9mq6fEWmjhDeYWIKFzw30ap3lo0qPu9ROx1olrnRLVehevoylQXRtXuxgk/pL76x3Ai+L0m/OM/71
*/