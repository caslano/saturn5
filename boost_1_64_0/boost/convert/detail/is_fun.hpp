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
23wtr/rS9nIusjb1UpXeLyREzWX2ay8ARR1U5iZ1qfeYZKiSFDLqGlDHRwCigD5eF8CfpLeoTahzFrL9DFLRhdI9NOUqHUjTcb2pp0zMQe5Tnv8u6tThqcjCoiUfc7enn/J5RgOf76Ecv2a6jsDL5eZK8mwZIvtAo4X+xkcdQ9keH59IZRDcpIFHbS1zGNkpY45QrzYQNqm+g9ccCjvR13C/cTagOOdDJqQg3/DVD4RIcXIyUV9Y/ECFT/us5+OJ4sNJopG0hm7y+Svjm2POcPlsLJw+0rw+ZfGOtIICWc5RYo83eRPUO0Tlctxxq3fqlrjP12ck+oRIeXI8nxzHxEjnysWDWLXp/kLoH10oRwMlXY6jnHyEfCdh0lmh+vQoQ7zH/4mQwsu+y9X09oHe72eUizlL/J5g7E3NmrsNXUkMMfcXdxGyLiSFmN/VufLSXBkW7pNsGUNQB3UgQ76XLHfcudBeyKxpHu96dEvKX6WE6DyOVyri8Yih0/0s/d2sgX3ccH6hkvI+B3j6K3lIwR+hn0AeQKRzs0G0EZTIVyOZcw3yjAUokgf2bizpzxCPfBGaRyj6/UyI9L7CxW4lfBuq9aPO06+MOgY6eulYcE1fb+/T9HUIQDVsIkNfgygP1dedaWpvvtvLoY77RLFst7yf4fpYImep8vcmlpyfV55KkmNeiPG+xXMLaH7P540llnqvl51eNmbUeX2WqFCd3zO1yktC1Bz9IX/iRc9nQrSynVLZaIEtFYjnbUbZPyh7jrKqUtlTWrtmoqyMnMGRR+7K67xb1PSV25wh9sIDReW9vSIVjw0an43KdKQ53S4eqEoyeMZztrgr02e0ZH/CPaRy807M48HJWVo/XKFua7NDwCZ7nLYGOukEn57SWp+jXXKckqArys1UkgW6rs2lTsBWIcaDb/GxByA+01Uk72GsuhbM0ayf8/V5WIC6FV3fX6JOiNeRnVGkBv/SfZrqq5WefexhfKZa9XeyfJZ7txGj6Pq30rseUZn97SrPGpRwUumv6/+bRn8+iZ0UFmfhC2951Yvuhp2vU+sRiyAz0v2GXm7sSX/bZtSxVvNd2GajTin3nc8y170n7Q9MQdLG+j6gTqFyDndhLm7d0+dDYS/osTgxBbclTPtIP89i10jp7e+nermh/fJZbVfXLj2/QSTSuF9Sn8QnbR3iazLcxrg7PfimDIs18kUWcgz6laeeh6Rgo+I+5Xm/8ZpXiNyQz3chxjuN+Eh7lNz3e4/s0sRXPKv+SK7/QdZfUnqIWLGxG+uHsHBDD3oEGv2tn3G4WsOos+bYD3mNi6pYuMsRaW3WHP6P1v6Wu7IqgSabYGXGuB1Mdea3YT9525sY+Gb2qghE/6yajjv4enTAZznr9C7n9UORob8ndDvR4wx9jlOSfTG392dXSRbmldlHFPh4z/GwyUc0sL7JEClgutE3oyTX0MfTnhhPLRfN9DWeEZy5wPPU2JDDOZXTaxWGvL/g/40pHIJHme7pfwkx1QuapWPnec86ctRaPeKQP1NHm3jRSA6XGP/v3wMI2XGzkevrHiDbytu95ac+evGI8KxFTsWKPCS+/YdX/GfYTbD07gJZ8vk+8RTZuzxXLTf4sR6TyVH5OdMZiB1aDoF64wxEvXwIZc39KVeTXvpXZJKf4EFXmGsbPChExPla2XWtrLlU5ldHKYMrUVYWW4BuKP7Cay0jfNpCOebB5vT0MxyWryYZadwxUa/UMS71ysO9G/Z1Q0lyjPpKcr3be+wq0tjUM/ZN+qpje2FFptLC0K9JIdKY6QRaaZyLlhMPtnC2fLynjMmT1HJLN4lHBRpjW+uqqetFDN7+r7plnyWF7FTOc8k=
*/