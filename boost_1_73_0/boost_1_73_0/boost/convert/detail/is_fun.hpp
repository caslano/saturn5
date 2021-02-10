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
imxANBq0gFZRH4y9DytRsNJckSJcbNplzVTl79LCgLwYCAmK1nUHh66MKlcChaRjyzeW0GD2TJuLElyZaOtKrO4YIq0dUNlKjuGQFrQrBBLvQ8sLKq29JWIbpWPZUv7Ilu1yL0BwzAp6YQJR0oMlUUz58ClKL+JZCp/C6TQcp3OIzyEczzu8D9H4DLXBMKoEetNIqjALCWzV1IwWd4L/0E73gvQCTmfTUTxJM1PvJE7S82g4OkvgOfQOX8KvLUd1H77oQa9mS7P9cBw8Pw4OcME8ZZSoTaaoNhuNb9SUQtjkAsbh5dD7DvbimdPoFtIoAwqiidkVY2cRkvk4niRR4v3EeF63BYXXxtqJsHrrWfRc4Pr9TPrmG9ivUB41quThLFCQFZGwb+LundiIZ8PkdBpN0igeexOCm0A6m66JyIqiRLq+23bbkrrObOsaFmVk4BblxFTSCKVN4xLvIk0ntjDkiEriWi/S6Gt4UAbeYKD7Ntddnv3newbPkesDqswztgJbj3FSO95QhIwrTUnhegXT2lhIpFgSif1G6lqsGb+yq6RBZeU2Dw8TFddUriXTrpK7yKTEkrEXtXbOGMmlEnjeO5oTbO3OEHvBxUZmzcOqVdqyQ75QjpzhR6vugWDWXi7455bn9nGNTfAw
*/