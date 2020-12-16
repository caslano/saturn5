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
YsKv8DWO8e9dTxz8wfnMz+Zrlu1497Ng69Nqx4LgZ9SA4bnO7O/wnEu7xBlxsCc/+v9wPGe4PhNsfB8aGasvC+fGnFu6jPl6QV+DrIFXJMn80sbR/itxTJoWI1YkTM7R+dTHtmXb6pozl/IakUubd6Qp02FyLrEv5xgupw4p2yYLgp6fQYYKXaZs2TvruQKzoPefK5hfJMhTY23N6YHtnJD3v6txTIqw/0d9LWL0rqFd90v3/xPHe+ONiJKmRJtjxwSvJ/8buA7+f0/zFbma469uS8QxQ6/v3VBbHDHc3Qt9I+sbtRxf3d3nXnds6z/HXVXOVOkyvrJadL0nXUkbTNiStL/NRC6H2jwhS4cJW/blEKPFiDXX006KAofX1hZ5Avp7TIoll9K3mxElRfn62mND5AbicDdSFGiydyP5c0SFo6ecPbCvnxntTrW34XLXtJ8kRZoMWRK+lvOJcUqVHjMC15YTK/LyiVxZfhQIX0df5XwtSjSpOWbxJePNtbze8XxzZTlf53/3uG+uKp4apTxfe16wrbOnfz3bK9nGd/fAzzzP2iZuKGea1mxKU6RvnccCdRZr8+pPanOG9u/8v3uI85xa46dmYZIzbPvWD2qQb2Pf0r4RJ1RoqduYLZe7sTEiSZEWU7Yc3MR4kabM0aHHVOixIHxb84wTOo4Zs2LvpvrHEcHbeHw7fWPv1mJ3XVe2zd093aH/39NNhsHt8Xr5SPzXnTMQuZnXuRspijQZsSJyc/UgRpYqfVa7e+qvR5Qs13qVGvn/RO3yOQPXO/9ZA0X/Uz/yi6C5dI7AqKw+rAm/Sq3lm5N/lS4T1kTOsJ8KLbZEbyU3CtTpMiWuH0XCanU1Crf1GhM2hLXRYri79z1K9o7G407Gle6xY9kQubP8uRspxlzP2Keo0mHMzNiHnqovxJ9xzkDpaecMnOpfWuwibXUd8f/75G9ElTEr7qbdyi3EY/nCc/ocifbZv6W+6Uv0Dv9bW+Bq8jyk/gLzk0MSFLV/KdsAfY6Mf5oKPRaUnNdixIqwNq9FQn0vdxtx1aPA6bPOGRhSI3mGOjFn/Z863xbn9Hb351/Pvpn81h5HjvWLu3GGvNNqcGKb43KOyd5B3bx2KfW4EQWPaxTUtO0auZzade5g/p/h/P+MnxzjdLxeE2PAkkt9Qv5qvndXc5xjkhQops8Z2D7W9UbS45HtNvu/e1iPSFFiQocth09TW/rOD95N/2wXXO5u8iDB5B9n97kN/eVupCjT2t3rPydwD3n86RzWcPK+8a9zBAYkznxO60icM3Ds/1Vnb3jOQJWDcxoj2yPblW3GtkbRsfm/nMNnVIytOC3OEHNyT/U97zkDwZh2HyR/uiyInHi/JEmRDnOOHqz+VBmw5uAh9pOiQp+E9fGLzM9k7txT3+RzOfbkcjXPC1F9ZMLJvbVNjxWXuo95SYspufupz/2N8wOM75n16RyuazW4lLWrDz/hWPFyNNgydvzhA4299rdMyG3+83lU34Nd2/jKeXmd/33GLHVj3wfe3PeBtPwMdDU/AzX+88O579MOuJz8Yrt1EG5EkgpDtlzr3mLJp8eBmiYosLqvusjjiARb9vXhUnF1pf8A9eRK8kxRpMGAiPof/idv/xOhSf9Mxsj4XY4jEsTl2NafnPo0/hM7cM7AlWLmLBmqDFhzqfvazyk1+sTv7zl1+tQeoI/aXhL4s7b/pGa2x1yO1n/mC0vHhuQfI0uZDjOCYlyOQ064nn4ccyX1Xu3WJ7hSQl38b5XkJ9TO82PSlGgyYsVeQvwfniPQIUbl6+cI9Kh4fCMi5/A9JkVxzkjoD1m6TNlyrd16BQlqu7UIjp2TokCdPgtC5/Q=
*/