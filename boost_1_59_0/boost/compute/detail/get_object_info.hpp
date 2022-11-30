//---------------------------------------------------------------------------//
// Copyright (c) 2013-2014 Kyle Lutz <kyle.r.lutz@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_DETAIL_GET_OBJECT_INFO_HPP
#define BOOST_COMPUTE_DETAIL_GET_OBJECT_INFO_HPP

#include <string>
#include <vector>

#include <boost/preprocessor/seq/for_each.hpp>
#include <boost/preprocessor/tuple/elem.hpp>

#include <boost/throw_exception.hpp>

#include <boost/compute/cl.hpp>
#include <boost/compute/exception/opencl_error.hpp>

namespace boost {
namespace compute {
namespace detail {

template<class Function, class Object, class AuxInfo>
struct bound_info_function
{
    bound_info_function(Function function, Object object, AuxInfo aux_info)
        : m_function(function),
          m_object(object),
          m_aux_info(aux_info)
    {
    }

    template<class Info>
    cl_int operator()(Info info, size_t input_size, const void *input,
                      size_t size, void *value, size_t *size_ret) const
    {
        return m_function(
            m_object, m_aux_info, info,
            input_size, input, size, value, size_ret
        );
    }

    template<class Info>
    cl_int operator()(Info info, size_t size, void *value, size_t *size_ret) const
    {
        return m_function(m_object, m_aux_info, info, size, value, size_ret);
    }

    Function m_function;
    Object m_object;
    AuxInfo m_aux_info;
};

template<class Function, class Object>
struct bound_info_function<Function, Object, void>
{
    bound_info_function(Function function, Object object)
        : m_function(function),
          m_object(object)
    {
    }

    template<class Info>
    cl_int operator()(Info info, size_t size, void *value, size_t *size_ret) const
    {
        return m_function(m_object, info, size, value, size_ret);
    }

    Function m_function;
    Object m_object;
};

template<class Function, class Object>
inline bound_info_function<Function, Object, void>
bind_info_function(Function f, Object o)
{
    return bound_info_function<Function, Object, void>(f, o);
}

template<class Function, class Object, class AuxInfo>
inline bound_info_function<Function, Object, AuxInfo>
bind_info_function(Function f, Object o, AuxInfo j)
{
    return bound_info_function<Function, Object, AuxInfo>(f, o, j);
}

// default implementation
template<class T>
struct get_object_info_impl
{
    template<class Function, class Info>
    T operator()(Function function, Info info) const
    {
        T value;

        cl_int ret = function(info, sizeof(T), &value, 0);
        if(ret != CL_SUCCESS){
            BOOST_THROW_EXCEPTION(opencl_error(ret));
        }

        return value;
    }

    template<class Function, class Info>
    T operator()(Function function, Info info,
                 const size_t input_size, const void* input) const
    {
        T value;

        cl_int ret = function(info, input_size, input, sizeof(T), &value, 0);
        if(ret != CL_SUCCESS){
            BOOST_THROW_EXCEPTION(opencl_error(ret));
        }

        return value;
    }
};

// specialization for bool
template<>
struct get_object_info_impl<bool>
{
    template<class Function, class Info>
    bool operator()(Function function, Info info) const
    {
        cl_bool value;

        cl_int ret = function(info, sizeof(cl_bool), &value, 0);
        if(ret != CL_SUCCESS){
            BOOST_THROW_EXCEPTION(opencl_error(ret));
        }

        return value == CL_TRUE;
    }
};

// specialization for std::string
template<>
struct get_object_info_impl<std::string>
{
    template<class Function, class Info>
    std::string operator()(Function function, Info info) const
    {
        size_t size = 0;

        cl_int ret = function(info, 0, 0, &size);
        if(ret != CL_SUCCESS){
            BOOST_THROW_EXCEPTION(opencl_error(ret));
        }

        if(size == 0){
            return std::string();
        }

        std::string value(size - 1, 0);

        ret = function(info, size, &value[0], 0);
        if(ret != CL_SUCCESS){
            BOOST_THROW_EXCEPTION(opencl_error(ret));
        }

        return value;
    }
};

// specialization for std::vector<T>
template<class T>
struct get_object_info_impl<std::vector<T> >
{
    template<class Function, class Info>
    std::vector<T> operator()(Function function, Info info) const
    {
        size_t size = 0;

        cl_int ret = function(info, 0, 0, &size);
        if(ret != CL_SUCCESS){
            BOOST_THROW_EXCEPTION(opencl_error(ret));
        }

        if(size == 0) return std::vector<T>();

        std::vector<T> vector(size / sizeof(T));
        ret = function(info, size, &vector[0], 0);
        if(ret != CL_SUCCESS){
            BOOST_THROW_EXCEPTION(opencl_error(ret));
        }

        return vector;
    }

    template<class Function, class Info>
    std::vector<T> operator()(Function function, Info info,
                              const size_t input_size, const void* input) const
    {
        #ifdef BOOST_COMPUTE_CL_VERSION_2_1
        // For CL_KERNEL_LOCAL_SIZE_FOR_SUB_GROUP_COUNT in clGetKernelSubGroupInfo
        // we can't get param_value_size using param_value_size_ret
        if(info == CL_KERNEL_LOCAL_SIZE_FOR_SUB_GROUP_COUNT)
        {
            std::vector<T> vector(3);
            cl_int ret = function(
                info, input_size, input,
                sizeof(T) * vector.size(), &vector[0], 0
            );
            if(ret != CL_SUCCESS){
                BOOST_THROW_EXCEPTION(opencl_error(ret));
            }
            return vector;
        }
        #endif
        size_t size = 0;

        cl_int ret = function(info, input_size, input, 0, 0, &size);
        if(ret != CL_SUCCESS){
            BOOST_THROW_EXCEPTION(opencl_error(ret));
        }

        std::vector<T> vector(size / sizeof(T));
        ret = function(info, input_size, input, size, &vector[0], 0);
        if(ret != CL_SUCCESS){
            BOOST_THROW_EXCEPTION(opencl_error(ret));
        }

        return vector;
    }
};

// returns the value (of type T) from the given clGet*Info() function call.
template<class T, class Function, class Object, class Info>
inline T get_object_info(Function f, Object o, Info i)
{
    return get_object_info_impl<T>()(bind_info_function(f, o), i);
}

template<class T, class Function, class Object, class Info, class AuxInfo>
inline T get_object_info(Function f, Object o, Info i, AuxInfo j)
{
    return get_object_info_impl<T>()(bind_info_function(f, o, j), i);
}

template<class T, class Function, class Object, class Info, class AuxInfo>
inline T get_object_info(Function f, Object o, Info i, AuxInfo j, const size_t k, const void * l)
{
    return get_object_info_impl<T>()(bind_info_function(f, o, j), i, k, l);
}

// returns the value type for the clGet*Info() call on Object with Enum.
template<class Object, int Enum>
struct get_object_info_type;

// defines the object::get_info<Enum>() specialization
#define BOOST_COMPUTE_DETAIL_DEFINE_GET_INFO_SPECIALIZATION(object_type, result_type, value) \
    namespace detail { \
        template<> struct get_object_info_type<object_type, value> { typedef result_type type; }; \
    } \
    template<> inline result_type object_type::get_info<value>() const \
    { \
        return get_info<result_type>(value); \
    }

// used by BOOST_COMPUTE_DETAIL_DEFINE_GET_INFO_SPECIALIZATIONS()
#define BOOST_COMPUTE_DETAIL_DEFINE_GET_INFO_IMPL(r, data, elem) \
    BOOST_COMPUTE_DETAIL_DEFINE_GET_INFO_SPECIALIZATION( \
        data, BOOST_PP_TUPLE_ELEM(2, 0, elem), BOOST_PP_TUPLE_ELEM(2, 1, elem) \
    )

// defines the object::get_info<Enum>() specialization for each
// (result_type, value) tuple in seq for object_type.
#define BOOST_COMPUTE_DETAIL_DEFINE_GET_INFO_SPECIALIZATIONS(object_type, seq) \
    BOOST_PP_SEQ_FOR_EACH( \
        BOOST_COMPUTE_DETAIL_DEFINE_GET_INFO_IMPL, object_type, seq \
    )

} // end detail namespace
} // end compute namespace
} // end boost namespace

#endif // BOOST_COMPUTE_DETAIL_GET_OBJECT_INFO_HPP

/* get_object_info.hpp
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
*/