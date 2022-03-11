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