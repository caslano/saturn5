//---------------------------------------------------------------------------//
// Copyright (c) 2013 Kyle Lutz <kyle.r.lutz@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_TYPES_COMPLEX_HPP
#define BOOST_COMPUTE_TYPES_COMPLEX_HPP

#include <complex>

#include <boost/compute/functional.hpp>
#include <boost/compute/types/fundamental.hpp>
#include <boost/compute/type_traits/make_vector_type.hpp>
#include <boost/compute/type_traits/type_name.hpp>
#include <boost/compute/detail/meta_kernel.hpp>

namespace boost {
namespace compute {
namespace detail {

template<class T>
meta_kernel& operator<<(meta_kernel &kernel, const std::complex<T> &x)
{
    typedef typename std::complex<T> value_type;

    kernel << "(" << type_name<value_type>() << ")"
           << "(" << x.real() << ", " << x.imag() << ")";

    return kernel;
}

// get<N>() result type specialization for std::complex<>
template<size_t N, class T>
struct get_result_type<N, std::complex<T> >
{
    typedef T type;
};

// get<N>() specialization for std::complex<>
template<size_t N, class Arg, class T>
inline meta_kernel& operator<<(meta_kernel &kernel,
                               const invoked_get<N, Arg, std::complex<T> > &expr)
{
    BOOST_STATIC_ASSERT(N < 2);

    return kernel << expr.m_arg << (N == 0 ? ".x" : ".y");
}

} // end detail namespace

// returns the real component of a complex<T>
template<class T>
struct real
{
    typedef T result_type;

    template<class Arg>
    detail::invoked_get<0, Arg, std::complex<T> >
    operator()(const Arg &x) const
    {
        return detail::invoked_get<0, Arg, std::complex<T> >(x);
    }
};

// returns the imaginary component of a complex<T>
template<class T>
struct imag
{
    typedef T result_type;

    template<class Arg>
    detail::invoked_get<1, Arg, std::complex<T> >
    operator()(const Arg &x) const
    {
        return detail::invoked_get<1, Arg, std::complex<T> >(x);
    }
};

namespace detail {

template<class Arg1, class Arg2, class T>
struct invoked_complex_multiplies
{
    typedef typename std::complex<T> result_type;

    invoked_complex_multiplies(const Arg1 &x, const Arg2 &y)
        : m_x(x),
          m_y(y)
    {
    }

    Arg1 m_x;
    Arg2 m_y;
};

template<class Arg1, class Arg2, class T>
inline meta_kernel& operator<<(meta_kernel &kernel,
                               const invoked_complex_multiplies<Arg1, Arg2, T> &expr)
{
    typedef typename std::complex<T> value_type;

    kernel << "(" << type_name<value_type>() << ")"
           << "(" << expr.m_x << ".x*" << expr.m_y << ".x-"
                  << expr.m_x << ".y*" << expr.m_y << ".y,"
                  << expr.m_x << ".y*" << expr.m_y << ".x+"
                  << expr.m_x << ".x*" << expr.m_y << ".y" << ")";

    return kernel;
}

template<class Arg, class T>
struct invoked_complex_conj
{
    typedef typename std::complex<T> result_type;

    invoked_complex_conj(const Arg &arg)
        : m_arg(arg)
    {
    }

    Arg m_arg;
};

template<class Arg, class T>
inline meta_kernel& operator<<(meta_kernel &kernel,
                               const invoked_complex_conj<Arg, T> &expr)
{
    typedef typename std::complex<T> value_type;

    kernel << "(" << type_name<value_type>() << ")"
           << "(" << expr.m_arg << ".x" << ", -" << expr.m_arg << ".y" << ")";

    return kernel;
}

} // end detail namespace

// specialization for multiplies<T>
template<class T>
class multiplies<std::complex<T> > :
    public function<std::complex<T> (std::complex<T>, std::complex<T>)>
{
public:
    multiplies() :
        function<
            std::complex<T> (std::complex<T>, std::complex<T>)
        >("complex_multiplies")
    {
    }

    template<class Arg1, class Arg2>
    detail::invoked_complex_multiplies<Arg1, Arg2, T>
    operator()(const Arg1 &x, const Arg2 &y) const
    {
        return detail::invoked_complex_multiplies<Arg1, Arg2, T>(x, y);
    }
};

// returns the complex conjugate of a complex<T>
template<class T>
struct conj
{
    typedef typename std::complex<T> result_type;

    template<class Arg>
    detail::invoked_complex_conj<Arg, T>
    operator()(const Arg &x) const
    {
        return detail::invoked_complex_conj<Arg, T>(x);
    }
};

namespace detail {

// type_name() specialization for std::complex
template<class T>
struct type_name_trait<std::complex<T> >
{
    static const char* value()
    {
        typedef typename make_vector_type<T, 2>::type vector_type;

        return type_name<vector_type>();
    }
};

} // end detail namespace
} // end compute namespace
} // end boost namespace

#endif // BOOST_COMPUTE_TYPES_COMPLEX_HPP

/* complex.hpp
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
*/