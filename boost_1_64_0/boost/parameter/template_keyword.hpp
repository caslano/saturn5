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
SSQve09u1l9rHZLUSD9g5zPF52/RqGsq4sFucRodP9FnSbMIERugzh6lS7QFl4lXf/E+O70KErdc9kCgIl8XseR3MxTiDA0WuIbPdB3thWg+ttVTeResWx8qizpqNhNOCJQMsDg9ViPjJ0r1Bnh6Ra3oL8Xo1Jy5C/Os4zMJNbBdm49asm/G5IB/W0pB4XDXF117hfgC9Y6a7QpEOHrC7+mijBsnuDz8AY9YzGroIVkmjZAsSPy9psD0ejUtP2o10HwdDeWR25qgJKCGAyxsxcdrw5wbdj6z73K4isPmJ0NqBP27tmjFzPlWTsRt25lf8KKVZYjVLRp8jb9Xhz4H+VAPhFzrYVY9VIapg3ItPb4GLn00bNzDfj4MwVBSWjOE2k0HFCimUoO5wVbtNwdVDsTxr4+z3bk5hlw2fH5LjRy+oSKlfZfmcTsvNUtdMR6cRwgegSI95CrHtIQ4TzGCbkKPXyh+S8/B39UwC9Zs8xjkwcuBKekI1oymPsTW3gn6P7nyx8rVE5Gydv/+qp3z/k7cIAViHyEArmZI1ecydLhAT1fuIdmPo1zOQQ==
*/