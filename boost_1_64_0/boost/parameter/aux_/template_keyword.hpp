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
Q3pDmT6Ma6BxYHWWztB0lotETnJDY60sl5A8VF4/viwN3CLpYN6LdUv21KnCrcbA2X8QObkMBAjFqDwqeR9bthwRmuEcz0BG6yhNKx/K91JiJ7Txscr0Orle1Re8bNWE5qQb1wV8U+PoJ7PCfPS1258Lx3Xdd2NqVClt4OoerJQ3Ltlem59s1smwCVu4nMcabDAqoet6/WaIPMr+MTk1FI8iZVJCNoMCN1a6OMN3QsdwTdpdY0GTYgWsYcEFhvKBodEU6wPMbrNWmFA9i0S1Z5Zj8tpS97PKukW+L/O9uZDoPiVu+gTeWn7DxExvwRZt6fGzva5yb8HHakOAAeB6Ug92blqZ5zrc1NxYjEJoaBgdjMhSakGFVUFLHXZTNCT2ucO09WB+5DbsGItbQLG8B3QP+kkZ7vHG4nsab11TJC31exBI7bd3N+LpVc/tBRi8uhL/cYc+5/ICp4BtwCQX3jd0Uqggqsbcsi+e7Y+0yFsQq8cYOxdLFgDCUfSfOoUlChGxuGOBgxoEPoitQckqhRzbBtJaJqnDrZTl6xZkg/3SKD1Li4WQPAgJiw==
*/