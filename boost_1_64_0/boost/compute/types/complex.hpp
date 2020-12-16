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
JedKcQPklNfpiY39MN96bCB1ggqqua8H6frojb4ItkDIQY24ChHSq8QlcE3HaXgvV0dyqqMd6fG37keYN7BYZwR3pCplq4NzC+n3ePCTg70XYwzNXpuiCE079vZWxdzcxPztN/huo0PTvreP3eQuU/0CjvcXDOhNfovXvan9GT1PpKkZduvCr1v21VHTIb/4DFexviM/tK+jkCmpuY2re/nB3srQA1aRbv3f6nGBKKW4Vcys2luzeSw6A/DzwuVNNiXpJNflb+Dyz8DldQu4b5xalx/8yA5x+VrYaMvcqvyNx22P7bl7qF8pL0LyUH5sz5uG9kfJqHcByo/t+RAu75ySNuUyl996/NweuPt9aS4P3y/d0reXSFb+yNtTLOLtdUoL8KHvcU9gxbecjZ7Uqw1kfVnn9kIcghghW6xNlFNzddUE6G2wZ85YeMOdJKOZdbnz5JJ47QTsVxgTcyrWaw757yAGVIe5+/5DPjmtmZQBpz0eMPf5HeIpQiebo8UpiwfMgzHGBM8F17njyWqU5xEY4413dZEm4IFYTh3mFsa0C4FNSffybPAYjMnJFGaU6uXZ4HkGxgQmrTYmQe6/68bnEGN0kqKkkiF533Xj8208PjYWr0UyOFXzOKaYR9HCilMSeK4bnzdhTLIiS1U48Fw3Ph/CGClUKoYBTTc8a8yXMMbxbIuXHniuG59vDjw5txTPDoiuG5/vDn0tipa2REhceN34/GoY01Kaha5A3sHrxuc+D8DvT7KUMioNPNeNz18wj+Wy7c0Kp3we1/awFizV3gig6Yana9vv8ZhqGwotFHiuWz8PxhhJVW1ZDL08m+sUY1xUzZZse3mAB+yRCwZicckSmoL6sPoX2HYWumtORbp/sJFfEmF1C2hZRMuDZyr29hagIdPrYAM+H7h9bWwxxY3cqd5gNmzXA7fkzJqk/XXcHZ5ADgyE90Qm6Y2JbEPu3ePjPjYj+BwjfCLW+VSs4tfxtzpQhMcudvPfBjmYoJRbJ8d2PPkAronr/N1/wHYXKWnTe4nr2tDjIX93j79ZXA5JND++LgbZxcOXedKXfRyzgjNXyF17x8Nd/Yl9uS1vmRK5KHJ+dAx6vgvQjc5lIW611NZkalel4erWxzZ5GPhlIawiXEhlDFcDdjblYPvIqxCWkWaAp1bEFXZ1IefHuxB/CfbZHheJCFEKqvgKppuNatNu/iXERSf/s7r+PTmiVQV7Uc/7XRN7/z2E86TlT9LNy3KvupnZ552eXRzY62qAszhua+Rc8eJLLyLE4oSzOMYkrgWXdsaUyXYLGPAb/WN/DitRBMnaFro3mS6H+Hl92VtOSlHXDKs6h727Tg6uiVX2kL78TekVjyoXUn1RNn1xH9GXLSTTIoUwBSqvqnbIxwQ+OzMGxsbSducV5ELxWzduTGn9yi74NFzBGb3HbbPMtdbRk/2006tEupxRc3mwQxVaTOJ51rY8+eC4ZTZHg7Keq0Mbgze2BWmAJIdzjujRlvehGQfrI6eQjLDksjkdHiw6vJ4UOL+JsJyUIDyPdp47F8/bPT16aXfNpRB7Ao1vLO0V8rw64OUi+PAMfSKEyrFyTK895jB9x6vXEbD2l73onz32cdEJnYVI5KmLEQzei/blHh+KDNx6Se66bF7nq6LH4D/2p8GvR1jrnbDN2bx5J5/t1xF6cnOUB70H2D4f9ifsD+1Dad52J51+ch9sSH3ZTIpISmYTyMVz9+qUixXynLN5KYM++HMHfdyLZIVTqeV6ue7tAvkT9n2hUXHpC3nu7ovO2ogfiIvqCDLcOf+E/cWbfjWpPC20dNeUOQC/C+3Lb4l/c3ZdsXksVTihd0LvvfdcJwabluk=
*/