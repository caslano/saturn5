/*

@Copyright Barrett Adair 2015-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

*/

#ifndef BOOST_CLBL_TRTS_DETAIL_FUNCTION_OBJECT_HPP
#define BOOST_CLBL_TRTS_DETAIL_FUNCTION_OBJECT_HPP

#include <boost/callable_traits/detail/pmf.hpp>
#include <boost/callable_traits/detail/default_callable_traits.hpp>
#include <boost/callable_traits/detail/forward_declarations.hpp>
#include <boost/callable_traits/detail/utility.hpp>

namespace boost { namespace callable_traits { namespace detail {

template<typename T, typename Base>
struct function_object : Base {

    using type = T;
    using error_t = error_type<T>;
    using function_type = typename Base::function_object_signature;
    using arg_types = typename Base::non_invoke_arg_types;
    using non_invoke_arg_types = arg_types;

    static constexpr const bool value = std::is_class<
        typename std::remove_reference<T>::type>::value;

    using traits = function_object;
    using class_type = error_t;
    using invoke_type = error_t;
    using remove_varargs = error_t;
    using add_varargs = error_t;
    using is_noexcept = typename Base::is_noexcept;
    using add_noexcept = error_t;
    using remove_noexcept = error_t;
    using is_transaction_safe = typename Base::is_transaction_safe;
    using add_transaction_safe = error_t;
    using remove_transaction_safe = error_t;
    using clear_args = error_t;

    template<template<class...> class Container>
    using expand_args = typename function<function_type>::template
        expand_args<Container>;

    template<template<class...> class Container, typename... RightArgs>
    using expand_args_left = typename function<function_type>::template
        expand_args_left<Container, RightArgs...>;

    template<template<class...> class Container, typename... LeftArgs>
    using expand_args_right = typename function<function_type>::template
        expand_args_right<Container, LeftArgs...>;

    template<typename C, typename U = T>
    using apply_member_pointer =
        typename std::remove_reference<U>::type C::*;

    template<typename>
    using apply_return = error_t;

    template<typename...>
    using push_front = error_t;
    
    template<typename...>
    using push_back = error_t;
    
    template<std::size_t ElementCount>
    using pop_args_front = error_t;

    template<std::size_t ElementCount>
    using pop_args_back = error_t;
    
    template<std::size_t Index, typename... NewArgs>
    using insert_args = error_t;
    
    template<std::size_t Index, std::size_t Count>
    using remove_args = error_t;

    template<std::size_t Index, typename... NewArgs>
    using replace_args = error_t;

    template<std::size_t Count>
    using pop_front = error_t;

    template<std::size_t Count>
    using pop_back = error_t;

    using remove_member_reference = error_t;
    using add_member_lvalue_reference = error_t;
    using add_member_rvalue_reference = error_t;
    using add_member_const = error_t;
    using add_member_volatile = error_t;
    using add_member_cv = error_t;
    using remove_member_const = error_t;
    using remove_member_volatile = error_t;
    using remove_member_cv = error_t;
};

template<typename T, typename U, typename Base>
struct function_object <T U::*, Base>
    : default_callable_traits<> {};

}}} // namespace boost::callable_traits::detail

#endif // #ifndef BOOST_CLBL_TRTS_DETAIL_FUNCTION_OBJECT_HPP

/* function_object.hpp
Zn7XeeZole6V8582PytlKXOyMCswuzBHMacxYbeUs5pi+t5SOh+r9Cg9So/So/QoPUqP0qP0KD1Kj9Lj//1w/yLz//NyLtf8/xbRlpnTSfutHOsx1bRtv1Nl2p4m6fx/lu5sRVicS8zpp89J5eLMOJouYp8ssvFFa33ip+sbi994sfcxYWvYxxtPnWgVj43bIP7lzHrGW8UeZpPPmgHNeMMkkxbs/Bot9iGSlkiRz/X4ye+x4tfQPk89p7DAMv7XiH8ttcu5dRzbiEpO/I9WpH2v4sWPVbHP826PnbzBnukzv/aMy5Kjq4MShW1hIj9OmrKgIFqxvKyWhbui5K+O3/HKnWUU9QtmzfxvxO0FmaG0GOOd0xKRZ+abmTkAMfhxOo3nkJVATDNoPXxY579WxvXOyR6/Rbh2t3QdAezpOSTKrEX/Dwnf2NGK/6swZpyUuEfZ1lVIN3Ocbpd4Z5EfLuRNeWVJvFq+XUXmDWTKWO3ocapDWZTBfVTFIvMF5lnMPzBHMeWii8on4QLlkwTJSykP//lnOk5I5+3LddrGCf38a6te6niXS13LNPB4o8s3nulyjVtaLeONju4Y+OenFqz+dl3Xzl1XV7yvVrDxRpdvnNOlrrUbeJzTpY830r3iVUdSrtJf47tXfAVP+ziMhPGwKmwAo2BrGA3bwWqwC4yB3WEs7AXjYG9YG8ocHJgJ68Js7V+YBq+Ec2B9OE/7Gc7Cr42uEJ0l6avp6Se1OLT/oTpM0HS2hJ1gK03PEHit9j/kar9DAWwHN2r/wx0q94D2Q+zTfojHYRd4CCbBp2FX+Lz2Q7yo/RCvwJ62/oi3tP/hK9gXfg/7QTdp7w/DYDKsAAfCSnAQrAcHw7baL8G6hRds408r3RP/P66d/xDt+MdL2/JLj9Kj9Cg9So/LcPwy3/+TJ12O/f893/8Noi0zt3K/w5JjIaYyZgZmQyxxj/F+c/Yb0D8ltXvKsNQxk/NmyrfZkzWL9thA1Hy/fSzymVYcZ9C2AY2jui3M2PzJE3UfD+MfZeb7fSD2XN4zHbiNYFinZw02NRcxLyRSv7U5l+ylYalbe+Mm5/eZWzpD2z8GYSoru3tekDNLXP/Y/Kws27V4CsQybRsbRL6jXrs3fJTamc0jdly4LrfnXFWKTfpFtCP4Xpuc23fPQG076KPXkaTXcabkdeRMyinU6zDrJ5rrCM0y69SQbm/4KFMeK6PUnL88riuZZjmPptm3vaMAUwEzEdOBNCdnlUjzpKzplkmzWbNR0zxd5PtwDzhkn8oE4j2MaUQ9d7UKbxHeiA2bwspGhIVbga5D9mLyzj9KvYiyMNeg7TgcMkcgGp4lkk5cw8mS11BAogPWH/JZ5WPMfu/fiv0jh6wzZtrd2B7J0vvHhKlr1gJzjZW5l8yzcpv9V/eP87gl+K+Xadam+UHi+DNhykmYZBNvrGnf4a7IsWx1pLOcZ53D479DyqOQhPnuD5+Je5juE6j7bMnxBwlbTmQTsPcn3yPhkYrF6zUO1XI5ittZzJv8Poa5K6pIrnF0kfudUcZfft90/v3UzTqNh8eZdRmljs7zu68ifdZmlEsTt9UB9spLgjvETfLA1PlMcZPr91lj5O0ylhyPYupiNmM2UV/ysgPVFxYzGjMhK1Pz9HbkHFaeJFLrjYarb+YmbhD7LSLvKlrPjii0zhj5Vqa99h6xzwhYx5KNfAuzxsvdYl/sX5/MXMdN4j9H7ANN+Eb+966pSw+I/1iz3lBTynYS5fgI5lHMIUy2ctIlPAPIK/Jf8so8A8gP3CQ/tOxKlnHv86y5eWdZS45luq/LNEwXzpOW4y07z/NFntTjJk/Myp+Jv2kj1evWctM=
*/