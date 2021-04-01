// Copyright Daniel Wallin, David Abrahams 2010.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PARAMETER_IS_MAYBE_050329_HPP
#define BOOST_PARAMETER_IS_MAYBE_050329_HPP

namespace boost { namespace parameter { namespace aux {

    struct maybe_base
    {
    };
}}} // namespace boost::parameter::aux

#if defined(BOOST_PARAMETER_CAN_USE_MP11)
#include <type_traits>

namespace boost { namespace parameter { namespace aux {

    template <typename T>
    using is_maybe = ::std::is_base_of<
        ::boost::parameter::aux::maybe_base
      , typename ::std::remove_const<T>::type
    >;
}}} // namespace boost::parameter::aux

#else   // !defined(BOOST_PARAMETER_CAN_USE_MP11)
#include <boost/mpl/bool.hpp>
#include <boost/mpl/if.hpp>
#include <boost/type_traits/is_base_of.hpp>
#include <boost/type_traits/remove_const.hpp>

namespace boost { namespace parameter { namespace aux {

    template <typename T>
    struct is_maybe
      : ::boost::mpl::if_<
            ::boost::is_base_of<
                ::boost::parameter::aux::maybe_base
              , typename ::boost::remove_const<T>::type
            >
          , ::boost::mpl::true_
          , ::boost::mpl::false_
        >::type
    {
    };
}}} // namespace boost::parameter::aux

#endif  // BOOST_PARAMETER_CAN_USE_MP11
#endif  // include guard


/* is_maybe.hpp
vUYprvkwZbWeclWriNk5Q3rvpzOyv2dPZ2YlR/PRC0fJfHAE3iuDOl/vC7pPvECDjPiX4HkgTn1iwajAmg1abTtlfKTCrqUxKAGcESJBj9S/h1iLa2nD5aV/amoWcLMW1fjdd+bMVBTThzEIMyxzfq+BFxBJqitiTp5PgVlB/JxWuyKyLoA1nQniiS265HZJQULw/F66kLnnPF7Vs0d8xfFl6EOnimv6pOG5lxpU0HtKFS9iNUa32HBAq3kLUCPwTOc2NN69p5DMoMf9obt9Tg12cnPjyM8rzLwTtQ0zMpvVYPPzFgEm9O+FdDAtGf+s5uWOkydVDcFV3+KqKJdQ+0kcDNMlxoy9y6Zv0Z5bF/7upcSUGULS4U6AgTApzJsb+iBDD9tuL0PxxtGpPvZmA3VwCG38wtINjDiYb/0zibtXAcUP+4UKmBwzbL/AZnNpN46MErfkAzo0ombiP2/8zsadqrCY1OBbAnmnGNIX7m1Ct42l6RBaSYCFFEGPQqjKrKZb/Hde2+Spy+4V2nuU6nU9aNBjlgT5IhNg/9ySvkGti83zFxb2iSk6pQ==
*/