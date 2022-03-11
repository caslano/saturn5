//---------------------------------------------------------------------------//
// Copyright (c) 2013 Kyle Lutz <kyle.r.lutz@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_TYPES_PAIR_HPP
#define BOOST_COMPUTE_TYPES_PAIR_HPP

#include <string>
#include <utility>

#include <boost/compute/functional/get.hpp>
#include <boost/compute/type_traits/type_definition.hpp>
#include <boost/compute/type_traits/type_name.hpp>
#include <boost/compute/detail/meta_kernel.hpp>

namespace boost {
namespace compute {
namespace detail {

// meta_kernel operator for std::pair literals
template<class T1, class T2>
inline meta_kernel&
operator<<(meta_kernel &kernel, const std::pair<T1, T2> &x)
{
    kernel << "(" << type_name<std::pair<T1, T2> >() << ")"
           << "{" << kernel.make_lit(x.first) << ", "
                  << kernel.make_lit(x.second) << "}";

    return kernel;
}

// inject_type() specialization for std::pair
template<class T1, class T2>
struct inject_type_impl<std::pair<T1, T2> >
{
    void operator()(meta_kernel &kernel)
    {
        typedef std::pair<T1, T2> pair_type;

        kernel.inject_type<T1>();
        kernel.inject_type<T2>();

        kernel.add_type_declaration<pair_type>(type_definition<pair_type>());
    }
};

// get<N>() result type specialization for std::pair<>
template<class T1, class T2>
struct get_result_type<0, std::pair<T1, T2> >
{
    typedef T1 type;
};

template<class T1, class T2>
struct get_result_type<1, std::pair<T1, T2> >
{
    typedef T2 type;
};

// get<N>() specialization for std::pair<>
template<size_t N, class Arg, class T1, class T2>
inline meta_kernel& operator<<(meta_kernel &kernel,
                               const invoked_get<N, Arg, std::pair<T1, T2> > &expr)
{
    kernel.inject_type<std::pair<T1, T2> >();

    return kernel << expr.m_arg << (N == 0 ? ".first" : ".second");
}

} // end detail namespace

namespace detail {

// type_name() specialization for std::pair
template<class T1, class T2>
struct type_name_trait<std::pair<T1, T2> >
{
    static const char* value()
    {
        static std::string name =
            std::string("_pair_") +
            type_name<T1>() + "_" + type_name<T2>() +
            "_t";

        return name.c_str();
    }
};

// type_definition() specialization for std::pair
template<class T1, class T2>
struct type_definition_trait<std::pair<T1, T2> >
{
    static std::string value()
    {
        typedef std::pair<T1, T2> pair_type;

        std::stringstream declaration;
        declaration << "typedef struct {\n"
                    << "    " << type_name<T1>() << " first;\n"
                    << "    " << type_name<T2>() << " second;\n"
                    << "} " << type_name<pair_type>() << ";\n";

        return declaration.str();
    }
};

} // end detail namespace
} // end compute namespace
} // end boost namespace

#endif // BOOST_COMPUTE_TYPES_PAIR_HPP

/* pair.hpp
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
*/