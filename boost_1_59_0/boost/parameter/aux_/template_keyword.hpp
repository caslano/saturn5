// Copyright Daniel Wallin 2006.
// Copyright Cromwell D. Enage 2017.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PARAMETER_TEMPLATE_KEYWORD_060203_HPP
#define BOOST_PARAMETER_TEMPLATE_KEYWORD_060203_HPP

namespace boost { namespace parameter { namespace aux {

    struct template_keyword_base
    {
    };
}}} // namespace boost::parameter::aux

#include <boost/parameter/config.hpp>

#if defined(BOOST_PARAMETER_CAN_USE_MP11)
#include <type_traits>

namespace boost { namespace parameter { namespace aux {

    template <typename T>
    using is_template_keyword = ::std::is_base_of<
        ::boost::parameter::aux::template_keyword_base
      , typename ::std::remove_const<
            typename ::std::remove_reference<T>::type
        >::type
    >;
}}} // namespace boost::parameter::aux

#else   // !defined(BOOST_PARAMETER_CAN_USE_MP11)
#include <boost/mpl/bool.hpp>
#include <boost/mpl/if.hpp>
#include <boost/type_traits/remove_const.hpp>

#if defined(BOOST_PARAMETER_HAS_PERFECT_FORWARDING)
#include <boost/type_traits/is_base_of.hpp>
#include <boost/type_traits/remove_reference.hpp>
#else
#include <boost/type_traits/is_convertible.hpp>
#include <boost/type_traits/is_lvalue_reference.hpp>
#endif

namespace boost { namespace parameter { namespace aux {

#if !defined(BOOST_PARAMETER_HAS_PERFECT_FORWARDING)
    template <typename T>
    struct is_template_keyword_aux
      : ::boost::mpl::if_<
            ::boost::is_convertible<
                T*
              , ::boost::parameter::aux::template_keyword_base const*
            >
          , ::boost::mpl::true_
          , ::boost::mpl::false_
        >::type
    {
    };
#endif  // BOOST_PARAMETER_HAS_PERFECT_FORWARDING

    template <typename T>
    struct is_template_keyword
      : ::boost::mpl::if_<
#if defined(BOOST_PARAMETER_HAS_PERFECT_FORWARDING)
            // Cannot use is_convertible<> to check if T is derived from
            // template_keyword_base. -- Cromwell D. Enage
            ::boost::is_base_of<
                ::boost::parameter::aux::template_keyword_base
              , typename ::boost::remove_const<
                    typename ::boost::remove_reference<T>::type
                >::type
            >
          , ::boost::mpl::true_
          , ::boost::mpl::false_
#else
            ::boost::is_lvalue_reference<T>
          , ::boost::mpl::false_
          , ::boost::parameter::aux::is_template_keyword_aux<T>
#endif  // BOOST_PARAMETER_HAS_PERFECT_FORWARDING
        >::type
    {
    };
}}} // namespace boost::parameter::aux

#endif  // BOOST_PARAMETER_CAN_USE_MP11
#endif  // include guard


/* template_keyword.hpp
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
*/