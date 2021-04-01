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
YAWITQPoRDQEVc63zTWg8IiO1MGugRCCS5T0QFU79bw0h+eppmwdYLYNTUuZHxHEWgYuHKlkSmhT3Y5zn8Z+/X4/YtoAWSJ7aG0SGmx1aa+LcfJvgOxslufbqSAH4KSgfnmDOo0HnsW+x/81qGsr+2eRCnoaacX/AFmlcyEgM0GqF3fZg51IhpaIXRkbgB7qdmxOT5NOtt8hGrzwFWga/103nJS7ZkRSzG0t6dZFk9SVFrlVdDcdbBJYddMr/vgQZsgikm4l3ZQdvLnSQRS8cjqm9+OJf/SmVyYNe0x9OXptYVE3rvAYZxRGTzgCWFRlbgN+zGU7HB8LcZbAsM2M33e3MS+ZP7PA66R7ORQ+QOMdCk8ilkYLWbTYdlEszw0rJZ/RwXw1UPj97H/9rfyI9vYB0pGfSjI33K1whmilZ6GnURvftubEvESO9auCWRnpaPh0bewV+9i9sWV92H3dhNqQsXGFnntVukPW1pKVXri4okmP6VhQL23Mg7H8YYnfIUhVD4iy26EMju7rHmp4fdKiQw2IWyXtp6Pqsn0WNl+ZMlrJSrIz+9iPIw==
*/