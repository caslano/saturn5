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