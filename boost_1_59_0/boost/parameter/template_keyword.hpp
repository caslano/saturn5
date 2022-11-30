// Copyright Daniel Wallin 2006.
// Copyright Cromwell D. Enage 2017.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PARAMETER_TEMPLATE_KEYWORD_HPP
#define BOOST_PARAMETER_TEMPLATE_KEYWORD_HPP

#include <boost/parameter/aux_/template_keyword.hpp>
#include <boost/parameter/config.hpp>

#if defined(BOOST_PARAMETER_CAN_USE_MP11)
#include <boost/mp11/integral.hpp>
#include <boost/mp11/utility.hpp>
#include <type_traits>
#else
#include <boost/mpl/bool.hpp>
#include <boost/mpl/if.hpp>
#include <boost/mpl/eval_if.hpp>
#include <boost/mpl/identity.hpp>
#include <boost/type_traits/add_lvalue_reference.hpp>
#include <boost/type_traits/is_function.hpp>
#include <boost/type_traits/is_array.hpp>
#endif

namespace boost { namespace parameter { 

    template <typename Tag, typename T>
    struct template_keyword : ::boost::parameter::aux::template_keyword_base
    {
        typedef Tag key_type;
        typedef T value_type;

        // reference is needed for two reasons:
        //
        // 1. It is used in the body of arg_list<...>
        //
        // 2. It is the result of binding<...>, which we mistakenly told
        //    people to use instead of value_type<...> to access named
        //    template parameters
        //
        // It used to be that reference == value_type, but that broke when
        // the argument was a function or array type, because various
        // arg_list functions return reference.
        //
        // Simply making reference == value_type& would break all the
        // legacy code that uses binding<...> to access named template
        // parameters. -- David Abrahams
#if defined(BOOST_PARAMETER_CAN_USE_MP11)
        using reference = typename ::boost::mp11::mp_eval_if<
            ::boost::mp11::mp_if<
                ::std::is_function<value_type>
              , ::boost::mp11::mp_true
              , ::std::is_array<value_type>
            >
          , ::std::add_lvalue_reference<value_type>
          , ::boost::mp11::mp_identity
          , value_type
        >::type;
#else
        typedef typename ::boost::mpl::eval_if<
            typename ::boost::mpl::if_<
                ::boost::is_function<value_type>
              , ::boost::mpl::true_
              , ::boost::is_array<value_type>
            >::type
          , ::boost::add_lvalue_reference<value_type>
          , ::boost::mpl::identity<value_type>
        >::type reference;
#endif  // BOOST_PARAMETER_CAN_USE_MP11
    };
}} // namespace boost::parameter

#define BOOST_PARAMETER_TEMPLATE_KEYWORD(name)                               \
    namespace tag                                                            \
    {                                                                        \
        struct name;                                                         \
    }                                                                        \
    template <typename T>                                                    \
    struct name : ::boost::parameter::template_keyword<tag::name,T>          \
    {                                                                        \
    };
/**/

#endif  // include guard


/* template_keyword.hpp
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
*/