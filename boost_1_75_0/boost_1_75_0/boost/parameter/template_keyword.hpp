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
RICppqrG5RTOkuW4Z5JHNcLftLYnjS1S8mYmDzeODl5mbIQMxej+1eFicSrsh1608C4pwEpXinx4wZaZ+kyN8dWw4hUygOeKTNoWYThy34ik5YMf4PsemPgApKiGE6aXJIKxgYZ0L97IbeTaTw7nBBxnKptOuqos8YYGcRxIvOoVSmaf+lirMs4uIeZgQGg8ICpfpf4rhMdCv95B2bRi3zW8sEYPiucZn1ZUnDXXkFbdz2ZAV5Uq8pGC8gZPlGFyL8B3hTbpJ9cSU3PsuCX+krZoM9LYgMsRW9dcQ3y2sy6tfons76eY0xzTXKpHUx/T6wW6yVJ/524EFgYlrgG3+feQEox0XIPa/Hdj601odB+9cZ30+CmC+a5XgqRkGryekYLPLFjR4rCiFJ67tqUdWZMJT7vLrPQ088vV54oIMKwQ9JmM0yyxsZ3iu+odCaAPvX+8CcFujnPGMmH4cIizWvxa71v/s/ropzV3XXO1hfqmaiKEKdYb25NFtlh7iStjJV75aDy0jH3ZFaltOvsGeBSU6oKiHvN2Kkpim4Ea49np+xDtR8StZAcu9L2ohu/XAMXU7wHf/wh9knXbACc721qr2VYtuXeKybeLJNYSzXz6SzIuTSMEH/h1nW8T871P9XMGdOmt0LJ8FJGiS1C0rC9uwAhWHsdv25gLX3TWzwDiqK5ZMql9zM9lu43HMbBPPQsmF+OqmwO/S2QZ
*/