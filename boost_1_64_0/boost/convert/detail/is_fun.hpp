// Copyright (c) 2009-2016 Vladimir Batov.
// Use, modification and distribution are subject to the Boost Software License,
// Version 1.0. See http://www.boost.org/LICENSE_1_0.txt.

#ifndef BOOST_CONVERT_IS_FUNCTION_HPP
#define BOOST_CONVERT_IS_FUNCTION_HPP

#include <boost/convert/detail/config.hpp>
#include <boost/convert/detail/has_member.hpp>
#include <boost/utility/enable_if.hpp>
#include <boost/type_traits.hpp>
#include <boost/function_types/is_function_pointer.hpp>
#include <boost/function_types/function_arity.hpp>
#include <boost/function_types/result_type.hpp>

namespace boost { namespace cnv
{
    typedef ::boost::type_traits::yes_type yes_type;
    typedef ::boost::type_traits:: no_type  no_type;

    template <bool has_operator, typename Functor, typename TypeOut>
    struct check_functor { BOOST_STATIC_CONSTANT(bool, value = false); };

    template<typename Func, typename TypeOut, class Enable =void>
    struct is_fun { BOOST_STATIC_CONSTANT(bool, value = false); };

    template <typename Functor, typename TypeOut>
    struct check_functor<true, Functor, TypeOut>
    {
        static yes_type test (TypeOut const&);
        static no_type  test (...);

        static const bool value = sizeof(yes_type) == sizeof(test(((Functor*) 0)->operator()()));
    };

    template<typename Functor, typename TypeOut>
    struct is_fun<Functor, TypeOut,
        typename enable_if_c<is_class<Functor>::value && !is_convertible<Functor, TypeOut>::value, void>::type>
    {
        BOOST_DECLARE_HAS_MEMBER(has_funop, operator());

        BOOST_STATIC_CONSTANT(bool, value = (check_functor<has_funop<Functor>::value, Functor, TypeOut>::value));
    };

    template<typename Function, typename TypeOut>
    struct is_fun<Function, TypeOut,
        typename enable_if_c<
            function_types::is_function_pointer<Function>::value &&
            function_types::function_arity<Function>::value == 0 &&
            !is_same<Function, TypeOut>::value,
        void>::type>
    {
        typedef TypeOut                                                   out_type;
        typedef typename function_types::result_type<Function>::type func_out_type;

        BOOST_STATIC_CONSTANT(bool, value = (is_convertible<func_out_type, out_type>::value));
    };
}}

#endif // BOOST_CONVERT_IS_FUNCTION_HPP


/* is_fun.hpp
7cUF5HCxlRWpVKOjPaD79HSyDxbOo7j3Ha0k1Y0y//6omNjblUnYScLFNzKNtQ5sE47Mvu2LTgObQbGRr2my8K1f6zulM2nmckdNkeB2KON18wE816ZUdRAyu3NSd/0xIntGA9R77wCuivLEcYRI1XVs6PqfXqBMSNthlp1JhB4NJPykGOwBOSPaYOMdrmIugV9mCm/QoYIpiqbgpwsJ3g2umio4VM7rYFib9dVyx3VLdoPbE+B0BR8Bfmh44NA6of7a+RP3UUfVmdP4IFhaEpctI3PaSjVAFUbkn51AJvDdpBFS+zjt95arfnTjKUEjOWlec2SI9diDCAhSyvZx8oCXs158o3xHNI+Kw/sgKpvWhYzl3wsej95whsKQivk92xgrtv/olsXl6M++KjibqNwtLjA++Qoh88jyw1uEGMgUw+4HwvOArL5RcW/j1z/8v9bCzextje3KYjrgtFl8HQI2nT68XgvLoRL1/ywDoTv4wv1FCKpSgG3zW+4AmEqmjHqAOkrK4+p3FZCpAkX0kIZN23MfuiwaaYbDPlvoZOuCL2zVtwKsIZEupw==
*/