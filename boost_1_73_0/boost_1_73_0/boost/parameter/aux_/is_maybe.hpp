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
OhUgF0OBTGafXVUL+BzDo5x03IXnGxS2yyPWBWGuUXvZQHlau9OxbPyb09KsKcoKEzc0A6uil/XF05P7KYw5JzShyWR/MgFay+ZgCQTV52bJh8f38OFEoBSjwKbSGN6fBTqYzLmuXRPrngINF0JTPtpwtdmgpy3n2IDcXZIgKkSV/ilYxWbwBI0HJOC8vaYLudfvFR71QMGeHuC87vd2cPsE793B+pbLeb+3cDFub9/LFkjg3C++hzCsTz+oT3+3vpqADJwDtoSYmWYc1QDLzTJPWtwqebVB3yrTNkHYQz/CvY5xDee8331kHpmX1etpdIdbj8YYeGTwAo2A8tgD/oC/p73eU6/3zOvteb3nG6BfZbAzuoGHYiP1PqryKRSFvjwtDugrH6hZYFz+2Th3BzFjlgjbNGfzQCYP+zJdcaSzfld20seTwUFT+pcqGDxuw/9El2Zs3u8F3tO9AYVpRvXIjEe+bToqeAeUuKobzrr3xGOzj+Huypny/uMZP07UK+47VMpnB/7fx1ctVf/HH73GdGt3yqgg1g6ralBrTxppVH/uHWrb3orIt9V2vP5nRKupC3Wa8ibVLborRvV/Bf4CUEsDBAoAAAAIAC1nSlL8M7U1UQYAACMQAAAlAAkAY3VybC1tYXN0ZXIv
*/