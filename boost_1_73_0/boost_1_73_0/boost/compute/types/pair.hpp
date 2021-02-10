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
2q9p/3AqjoEdLQ5ECmJJJKigv2ii0CQKYtOt7EMc9jAuYOMgCR/aroRomLnv0FflfCFun2J5OIJXlyV2kzmCnneuZs1hx8/397eaoeX2Zna/v6dqLclKPzgDQUpo60FRyKdLPesPCLT+wazXKJo4hO8MfEzzyLYK8XAxXfSAjEp30mp0M4jLYQ289EkxnT66urz+lVoUai/01eWHC1DuI3XToKq4p7PaPRLpK5DpVuhCa4/pxOh9rRtDluLAgicqtxDQYTc7YmZEFhSrSXEILIgZdNjzIXZVBeGQDccr82jzpmOdcIddgfgcX0FRWpbSfcmmyEhANIJYwBoNT2H6KCVD7fFZReFWIgVrT/0er7GmzTHQAw5WjXoIFyHGXQdBx7KcwUDzcEyLKKJIsRMI5+h2U5+Kl9qeRBC+NZZFV4NctIu6a1d0AMg+5v1A7bDveGMHkwpqpQZhJM/Jj884/yG2QYvfeseSAWAphHDYhWhX4r6wdOvBDOPO37p2r/UPCg0snFf65jgS3G+oZ8vu7WMCoTJByEdC5HW9y3rwQkn2HeP6EohHHkmwhVq88qQJbFQxeaCo6Nq1NARfqBW5QgF+Yl+l+pI0Cey09eNiEKKXj3NIWAF8oLJzevcL+KQFYoXEpIMYCDbZ2pqm
*/