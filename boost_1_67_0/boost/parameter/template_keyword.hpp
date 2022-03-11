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