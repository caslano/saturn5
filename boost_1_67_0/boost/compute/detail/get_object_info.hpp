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