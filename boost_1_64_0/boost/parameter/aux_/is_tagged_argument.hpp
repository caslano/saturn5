// Copyright Daniel Wallin, David Abrahams 2005.
// Copyright Cromwell D. Enage 2017.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PARAMETER_IS_TAGGED_ARGUMENT_HPP
#define BOOST_PARAMETER_IS_TAGGED_ARGUMENT_HPP

namespace boost { namespace parameter { namespace aux {

    struct tagged_argument_base
    {
    };
}}} // namespace boost::parameter::aux

#include <boost/parameter/config.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/mpl/if.hpp>

#if defined(BOOST_PARAMETER_HAS_PERFECT_FORWARDING) || \
    (0 < BOOST_PARAMETER_EXPONENTIAL_OVERLOAD_THRESHOLD_ARITY)
#include <boost/type_traits/is_base_of.hpp>
#include <boost/type_traits/remove_const.hpp>
#include <boost/type_traits/remove_reference.hpp>

namespace boost { namespace parameter { namespace aux {

    // This metafunction identifies tagged_argument specializations
    // and their derived classes.
    template <typename T>
    struct is_tagged_argument
      : ::boost::mpl::if_<
            // Cannot use is_convertible<> to check if T is derived from
            // tagged_argument_base. -- Cromwell D. Enage
            ::boost::is_base_of<
                ::boost::parameter::aux::tagged_argument_base
              , typename ::boost::remove_const<
                    typename ::boost::remove_reference<T>::type
                >::type
            >
          , ::boost::mpl::true_
          , ::boost::mpl::false_
        >::type
    {
    };
}}} // namespace boost::parameter::aux

#else   // no perfect forwarding support and no exponential overloads
#include <boost/type_traits/is_convertible.hpp>
#include <boost/type_traits/is_lvalue_reference.hpp>

namespace boost { namespace parameter { namespace aux {

    template <typename T>
    struct is_tagged_argument_aux
      : ::boost::is_convertible<
            T*
          , ::boost::parameter::aux::tagged_argument_base const*
        >
    {
    };

    // This metafunction identifies tagged_argument specializations
    // and their derived classes.
    template <typename T>
    struct is_tagged_argument
      : ::boost::mpl::if_<
            ::boost::is_lvalue_reference<T>
          , ::boost::mpl::false_
          , ::boost::parameter::aux::is_tagged_argument_aux<T>
        >::type
    {
    };
}}} // namespace boost::parameter::aux

#endif  // perfect forwarding support, or exponential overloads

#if defined(BOOST_PARAMETER_CAN_USE_MP11)
#include <type_traits>

namespace boost { namespace parameter { namespace aux {

    template <typename T>
    using is_tagged_argument_mp11 = ::std::is_base_of<
        ::boost::parameter::aux::tagged_argument_base
      , typename ::std::remove_const<
            typename ::std::remove_reference<T>::type
        >::type
    >;
}}} // namespace boost::parameter::aux

#endif  // BOOST_PARAMETER_CAN_USE_MP11
#endif  // include guard


/* is_tagged_argument.hpp
UF3Lo7z4qvzuY3BUTYQdzH/6r9kiVsVYCA5DpOgTbzZYzXtp9H3ci9QbwRrrc2EVN1jM+npRJAknwTFL3SrkT3faTrNP96e8Zcg/Ju0ZqMhIJQ1rVX+tSJ19GOBEymLUtxY3Js1Zt3FiAPGr+Xjt+GB9cS80fwV271vR1vsSJlVc4uXfkGGHZsejdp2ok4jsFoYNF9MELDzMO5qbpQtIOlVd91nKtLkU+rvtUPR1QOgs9sB4I8plDL5+bTopI9m99t6mJJN8Iy4PZizBudNvBcpOV/u6MDlzERHSjJsgZeCs/lLkghbctbN1081jgO5eGXhM+tQ8a1qwNSusGBcRAluVRd5LwdrC6t80/EDH/qvMvQRl9QUC/WfZYw+9ob0GIH+tthzEg5hvA6nRyS7DJrryYCHeclxhHCpc3n0bVDVQ+IoPI0/YG7hWhR8pyRVgue3fVf36/NXxGjg6lyAnaEu8fdHHpcEI9SufFdDgVB9V2BtAD0EC9nd/q6Rb5n+ZyYtwYGmsH2L8pzj1J6fEpbBX5sWepNs8VaeSiObG5oNT5AUUxllfHY4YlA==
*/