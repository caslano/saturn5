// Copyright (c) 2009-2016 Vladimir Batov.
// Use, modification and distribution are subject to the Boost Software License,
// Version 1.0. See http://www.boost.org/LICENSE_1_0.txt.

#ifndef BOOST_CONVERT_IS_CONVERTER_HPP
#define BOOST_CONVERT_IS_CONVERTER_HPP

#include <boost/convert/detail/config.hpp>
#include <boost/convert/detail/is_callable.hpp>
#include <boost/utility/enable_if.hpp>
#include <boost/type_traits.hpp>
#include <boost/ref.hpp>

namespace boost { namespace cnv
{
    template<typename, typename, typename, typename =void>
    struct is_cnv { BOOST_STATIC_CONSTANT(bool, value = false); };

    template<typename Class, typename TypeIn, typename TypeOut>
    struct is_cnv<Class, TypeIn, TypeOut, typename enable_if<is_class<Class>, void>::type>
    {
        typedef typename ::boost::unwrap_reference<Class>::type class_type;
        typedef void signature_type(TypeIn const&, optional<TypeOut>&);

        BOOST_DECLARE_IS_CALLABLE(is_callable, operator());

        BOOST_STATIC_CONSTANT(bool, value = (is_callable<class_type, signature_type>::value));
    };

    template<typename Function, typename TypeIn, typename TypeOut>
    struct is_cnv<Function, TypeIn, TypeOut,
        typename enable_if_c<is_function<Function>::value && function_types::function_arity<Function>::value == 2,
        void>::type>
    {
        typedef TypeIn                                              in_type;
        typedef optional<TypeOut>&                                 out_type;
        typedef typename function_traits<Function>::arg1_type  func_in_type;
        typedef typename function_traits<Function>::arg2_type func_out_type;

        BOOST_STATIC_CONSTANT(bool,  in_good = (is_convertible<in_type, func_in_type>::value));
        BOOST_STATIC_CONSTANT(bool, out_good = (is_same<out_type, func_out_type>::value));
        BOOST_STATIC_CONSTANT(bool,    value = (in_good && out_good));
    };
}}

#endif // BOOST_CONVERT_IS_CONVERTER_HPP


/* is_converter.hpp
Zn/T1UWlCBdopsURkmRnT0rfHxQjwK4Q+2A3O/6OBYmdhUEvIlzw7CW8CzdAm2+CjrQzXwJtL/6dKEta8x3RVg8Al7W3aw6X2Lzt4f/46WcwGooIT5MNUHbNGIuE//0MKo0OIjrzvLA4Erum8aL/Cyz+/fz9/P38/fz9/P38/fz9/P38/fz9/P38/fw/8tjBv0ZCaoMgoNso5X4NqUkM8MFbgJfagLs4NAOa4cvgbR8QGuVh8U/vdAUe2lhiOpEMMgkoxpEkkghua7IsPsOevzzRhffWo4j5OkWS2YTSGnDqS4K5d2EuEcrHeMI0w/l4SggnIEQAcBmEexCyIe0h/C1Q4GcOhBsQkoDmPgi+bQmphnAJQqQjIVshODsRooFwBsJgcMDXQngIocCFkOMQwlwJWQzhDoQMN0IOQghwB14gXIOQ4EHIbghe7QgxQTgPYZQnIY0QHKCeSiGcxHmc9oSshHAfQq43IUcghPoQsgDCLQhpvoS8CMHfj5CZEK5AiO1AyE4I7h0J0UM4C0HqT8h6/HXXTlB+CCcgRHSG8kO4ByG7C5QfQlAAlB/CDQhJXaH8EHwDofwQLkGI7Ablh+AMFauBcAbCWqi3wcFcnePPrV7qC2Wzt3wvkDD5Mn8/7AN82lm+T3bn2kj4TgoFuk6W7yN46ZsovyMDoX5iLd9hVVAnnUTpQdjuO1q+8S8R5R+7Bsoo+j4B3+6k
*/