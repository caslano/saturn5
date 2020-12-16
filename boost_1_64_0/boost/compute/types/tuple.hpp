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
kTjntnFlnHPDGb0A93ggXk1UoFRZ6sGunfLnZJjAfHCuwxPWVLJiyhC/8uTN9RiRJvmCO7N8ajSv+6ec90DT+FBXjE3vrO3RDuI9/45sKOkUNRUtbJwe2TiReGBDyNqL4PTURo92EDd846viGC5aU0pbQThtZdNYik9ZTXZWIeY92sm5WnjrvJFkNU4mbm5urKDTVjH3iYVdJ0RrjApgF50eirknC7stNbKuvAW7HRfbHcr0bYVdZrmyzoPZ8lDMwaYpbDLe1lbrCmz2xLl5LbjSMU6lrsAoOjEXcy8VXOVV7WrnwS46ORdzX1dwvbfeiKBwGc+3+8GCG1yrayc5LuP5dj9TcEUrqGqNxIU83+43Ci4PxlreClzO8+3+quBq3/CqUn7UltXY7rX+gbnGhVoaX4FddNIu5t6x4LaOe+9bjst5vt2lguu81oIahct5vt1QcFmoaMukwOWM7cL+j1GaLQtBlsUMZmFPEeJxImtP28pZsFmuVmfpfVvBjQZ1bfi8Mh5xP1pwGxHSHDLFZTzf7ucLrte+9VIwXMbz7V4uuLyqjDWqwmU83+6fCq5pLfNVbXEhz7d74p+YWzWcG16xOeW8VHLvWXBbLyRrNZ1TziMuKbg69UqZrXA5z7f72IIrDPcqmMIvz7e7W3CDVUq0jOJynm/3ZQW3dlIo7hku5/l23424jHCpJddel+Xs57y7n8DclN82WJXbhVPAS+5XCq41iWlqXM7z7f6o4FayoTa0riznsd30z9URVympjQ8NLuf5dm9ZcKWmvqayxeWM7cKZujl3UXT9pcDJo5yQauhLwn4TZKchmlaydrwa7uqAW47gSLn98R1GuY7ltok6qBTkMK42nt/YhgD6PVhzyPFckuSGheE19Anhvg+wDreo5Oc0vinX80CtZVvrurtya21/Y2r0Srh3EeWzIp764Flruhjl2N/NN8SEFLY15cN9D59BfEvawBz3lnULeYtd9PoiXEp0MnVrV8/0/b9DNfg3lG9OLG2NbSoH+bbTtER9WWrOLKb05Pm+1vFMz2nN66Y1WpDdJ8O9hdl9KDmWceJopWtqfH5Ozryzpe+JeI5IZiou+b/P7mKoebGfKSA9NZGtky0XFvKMgg2ylGRnre7mOk5xx7Vj2pNWLOC1ogNULsaYurI1JbU9S0dnST8L6WyUqoRtKNlaK3Q+D+lsGklN7Sx5MoRqZjq/kvd3T2mujTR1RVqxWMQD5TqXKllrpnRDzkop8o7axqD30uOPZXpDzWztjYlpLfS+DenlddtQKVNU7voadOJyve9HZWC0rLipJXkkP12si5zI8rVUV0wy1rI+vZzxUu8HkV7vhW69qcneaqH3oyi9zJiKUs+79Oad+w24/yDHexK4ca2pZHrhy8XwdZjjQjaCc1QYL7u0546XwhxXjn9QxXjjZdDT5XpocBn+V0i/FI3jujVdHnLnTOGbcJWrF2ekVLX2VazMI2MJ9mD+NucuNYZqa1U71APkZRfmb3P8g5xPHUDBhrzA/BTgCdJf6aaqTOiygvrEu9AnLvIiJTXc1Ty1zCMyA3nZRbY4ZRUzNnXbKM8T93SI3cjxLWlap3mImQlMTitmWcje9ezA/CwurzTfQQWZXp8PL09WN+8e5ycwJhXZvXI95Seaodtr0Q60+mztLecuC6Hq2vguO3BzTDIm4cxTnJ+aOcGCrYb8LGb54dA2kY2a+bbRzPUZipEKUyPZ2UVFfgStTLBtPcvP4ig/0Ce+as6VxHCnfGumdzqHeFrq0+KprCyeA7/W0p4K9zveM+eedlorw2x3qyW2cRLZEERRV/GKBrLb6z+zeGW0EP8HNuAeTIO4DXGVMcH45og=
*/