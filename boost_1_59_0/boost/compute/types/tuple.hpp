//---------------------------------------------------------------------------//
// Copyright (c) 2013 Kyle Lutz <kyle.r.lutz@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_TYPES_TUPLE_HPP
#define BOOST_COMPUTE_TYPES_TUPLE_HPP

#include <string>
#include <utility>

#include <boost/preprocessor/enum.hpp>
#include <boost/preprocessor/expr_if.hpp>
#include <boost/preprocessor/repetition.hpp>
#include <boost/tuple/tuple.hpp>

#include <boost/compute/config.hpp>
#include <boost/compute/functional/get.hpp>
#include <boost/compute/type_traits/type_name.hpp>
#include <boost/compute/detail/meta_kernel.hpp>

#ifndef BOOST_COMPUTE_NO_STD_TUPLE
#include <tuple>
#endif

namespace boost {
namespace compute {
namespace detail {

// meta_kernel operators for boost::tuple literals
#define BOOST_COMPUTE_PRINT_ELEM(z, n, unused)                                 \
        BOOST_PP_EXPR_IF(n, << ", ")                                           \
        << kernel.make_lit(boost::get<n>(x))

#define BOOST_COMPUTE_PRINT_TUPLE(z, n, unused)                                \
template<BOOST_PP_ENUM_PARAMS(n, class T)>                                     \
inline meta_kernel&                                                            \
operator<<(meta_kernel &kernel,                                                \
        const boost::tuple<BOOST_PP_ENUM_PARAMS(n, T)> &x)                     \
{                                                                              \
    return kernel                                                              \
           << "("                                                              \
           << type_name<boost::tuple<BOOST_PP_ENUM_PARAMS(n, T)> >()           \
           << ")"                                                              \
           << "{"                                                              \
           BOOST_PP_REPEAT(n, BOOST_COMPUTE_PRINT_ELEM, ~)                     \
           << "}";                                                             \
}

BOOST_PP_REPEAT_FROM_TO(1, BOOST_COMPUTE_MAX_ARITY, BOOST_COMPUTE_PRINT_TUPLE, ~)

#undef BOOST_COMPUTE_PRINT_TUPLE
#undef BOOST_COMPUTE_PRINT_ELEM

// inject_type() specializations for boost::tuple
#define BOOST_COMPUTE_INJECT_TYPE(z, n, unused)                                \
        kernel.inject_type<T ## n>();

#define BOOST_COMPUTE_INJECT_DECL(z, n, unused)                                \
        << "    " << type_name<T ## n>() << " v" #n ";\n"

#define BOOST_COMPUTE_INJECT_IMPL(z, n, unused)                                \
template<BOOST_PP_ENUM_PARAMS(n, class T)>                                     \
struct inject_type_impl<boost::tuple<BOOST_PP_ENUM_PARAMS(n, T)> >             \
{                                                                              \
    void operator()(meta_kernel &kernel)                                       \
    {                                                                          \
        typedef boost::tuple<BOOST_PP_ENUM_PARAMS(n, T)> tuple_type;           \
        BOOST_PP_REPEAT(n, BOOST_COMPUTE_INJECT_TYPE, ~)                       \
        std::stringstream declaration;                                         \
        declaration << "typedef struct {\n"                                    \
                    BOOST_PP_REPEAT(n, BOOST_COMPUTE_INJECT_DECL, ~)           \
                    << "} " << type_name<tuple_type>() << ";\n";               \
        kernel.add_type_declaration<tuple_type>(declaration.str());            \
    }                                                                          \
};

BOOST_PP_REPEAT_FROM_TO(1, BOOST_COMPUTE_MAX_ARITY, BOOST_COMPUTE_INJECT_IMPL, ~)

#undef BOOST_COMPUTE_INJECT_IMPL
#undef BOOST_COMPUTE_INJECT_DECL
#undef BOOST_COMPUTE_INJECT_TYPE

#ifdef BOOST_COMPUTE_NO_VARIADIC_TEMPLATES
// type_name() specializations for boost::tuple (without variadic templates)
#define BOOST_COMPUTE_PRINT_TYPE(z, n, unused)                                 \
            + type_name<T ## n>() + "_"

#define BOOST_COMPUTE_PRINT_TYPE_NAME(z, n, unused)                            \
template<BOOST_PP_ENUM_PARAMS(n, class T)>                                     \
struct type_name_trait<boost::tuple<BOOST_PP_ENUM_PARAMS(n, T)> >              \
{                                                                              \
    static const char* value()                                                 \
    {                                                                          \
        static std::string name =                                              \
            std::string("boost_tuple_")                                        \
            BOOST_PP_REPEAT(n, BOOST_COMPUTE_PRINT_TYPE, ~)                    \
            "t";                                                               \
        return name.c_str();                                                   \
    }                                                                          \
};

BOOST_PP_REPEAT_FROM_TO(1, BOOST_COMPUTE_MAX_ARITY, BOOST_COMPUTE_PRINT_TYPE_NAME, ~)

#undef BOOST_COMPUTE_PRINT_TYPE_NAME
#undef BOOST_COMPUTE_PRINT_TYPE

#else
template<size_t N, class T, class... Rest>
struct write_tuple_type_names
{
    void operator()(std::ostream &os)
    {
        os << type_name<T>() << "_";
        write_tuple_type_names<N-1, Rest...>()(os);
    }
};

template<class T, class... Rest>
struct write_tuple_type_names<1, T, Rest...>
{
    void operator()(std::ostream &os)
    {
        os << type_name<T>();
    }
};

// type_name<> specialization for boost::tuple<...> (with variadic templates)
template<class... T>
struct type_name_trait<boost::tuple<T...>>
{
    static const char* value()
    {
        static std::string str = make_type_name();

        return str.c_str();
    }

    static std::string make_type_name()
    {
        typedef typename boost::tuple<T...> tuple_type;

        std::stringstream s;
        s << "boost_tuple_";
        write_tuple_type_names<
            boost::tuples::length<tuple_type>::value, T...
        >()(s);
        s << "_t";
        return s.str();
    }
};
#endif // BOOST_COMPUTE_NO_VARIADIC_TEMPLATES

#ifndef BOOST_COMPUTE_NO_STD_TUPLE
// type_name<> specialization for std::tuple<T...>
template<class... T>
struct type_name_trait<std::tuple<T...>>
{
    static const char* value()
    {
        static std::string str = make_type_name();

        return str.c_str();
    }

    static std::string make_type_name()
    {
        typedef typename std::tuple<T...> tuple_type;

        std::stringstream s;
        s << "std_tuple_";
        write_tuple_type_names<
            std::tuple_size<tuple_type>::value, T...
        >()(s);
        s << "_t";
        return s.str();
    }
};
#endif // BOOST_COMPUTE_NO_STD_TUPLE

// get<N>() result type specialization for boost::tuple<>
#define BOOST_COMPUTE_GET_RESULT_TYPE(z, n, unused)                            \
template<size_t N, BOOST_PP_ENUM_PARAMS(n, class T)>                           \
struct get_result_type<N, boost::tuple<BOOST_PP_ENUM_PARAMS(n, T)> >           \
{                                                                              \
    typedef typename boost::tuple<BOOST_PP_ENUM_PARAMS(n, T)> T;               \
    typedef typename boost::tuples::element<N, T>::type type;                  \
};

BOOST_PP_REPEAT_FROM_TO(1, BOOST_COMPUTE_MAX_ARITY, BOOST_COMPUTE_GET_RESULT_TYPE, ~)

#undef BOOST_COMPUTE_GET_RESULT_TYPE


// get<N>() specialization for boost::tuple<>
#define BOOST_COMPUTE_GET_N(z, n, unused)                                      \
template<size_t N, class Arg, BOOST_PP_ENUM_PARAMS(n, class T)>                \
inline meta_kernel& operator<<(meta_kernel &kernel,                            \
   const invoked_get<N, Arg, boost::tuple<BOOST_PP_ENUM_PARAMS(n, T)> > &expr) \
{                                                                              \
    typedef typename boost::tuple<BOOST_PP_ENUM_PARAMS(n, T)> T;               \
    BOOST_STATIC_ASSERT(N < size_t(boost::tuples::length<T>::value));          \
    kernel.inject_type<T>();                                                   \
    return kernel << expr.m_arg << ".v" << int_(N);                           \
}

BOOST_PP_REPEAT_FROM_TO(1, BOOST_COMPUTE_MAX_ARITY, BOOST_COMPUTE_GET_N, ~)

#undef BOOST_COMPUTE_GET_N

} // end detail namespace
} // end compute namespace
} // end boost namespace

#endif // BOOST_COMPUTE_TYPES_TUPLE_HPP

/* tuple.hpp
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
*/