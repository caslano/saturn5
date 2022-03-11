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