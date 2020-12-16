//  (C) Copyright Nick Thompson 2019.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_MATH_INTERPOLATORS_CARDINAL_TRIGONOMETRIC_HPP
#define BOOST_MATH_INTERPOLATORS_CARDINAL_TRIGONOMETRIC_HPP
#include <memory>
#include <boost/math/interpolators/detail/cardinal_trigonometric_detail.hpp>

namespace boost { namespace math { namespace interpolators {

template<class RandomAccessContainer>
class cardinal_trigonometric
{
public:
    using Real = typename RandomAccessContainer::value_type;
    cardinal_trigonometric(RandomAccessContainer const & v, Real t0, Real h)
    {
        m_impl = std::make_shared<interpolators::detail::cardinal_trigonometric_detail<Real>>(v.data(), v.size(), t0, h);
    }

    Real operator()(Real t) const
    {
        return m_impl->operator()(t);
    }

    Real prime(Real t) const
    {
        return m_impl->prime(t);
    }

    Real double_prime(Real t) const
    {
        return m_impl->double_prime(t);
    }

    Real period() const
    {
        return m_impl->period();
    }

    Real integrate() const
    {
        return m_impl->integrate();
    }

    Real squared_l2() const
    {
        return m_impl->squared_l2();
    }

private:
    std::shared_ptr<interpolators::detail::cardinal_trigonometric_detail<Real>> m_impl;
};

}}}
#endif

/* cardinal_trigonometric.hpp
j1e7PrF7quijp/mBXaNnK1f62/bxgnHb1Nu24tY+7iPeksa2scFwTc9dWqjKUfKLqAdCda0qPfXsUv2/PeKHd85i7v1bJ2YLRdLHZPsZD9x728tSEc5grU9qV+8bMvdU3VmPvqiWeZ7n/LeEo1o6JrYIe3h1GCJz+zHSMfk9azpq8azb3E/88KRjS03HNDG73KTjKnta4kfd01LtmjtaSUej7qhHenb4Eun5fCvt5/TMwUbUQ6FzdUelZ43fS40clsPv1fitCP/qNv/aY08/c17piJjn8TXPb+3P1X2t85NkytD6lpH5yYDgomPMT1oeEhkSTrqrj08RvanY7VljO5Iodtqas4bj5L2dzEMi4RjXKhyOwKxgiQajWjjSXeH4u8RtFmWyK6pqrvSW6J9KrxFk33jrauHsLr/ZnzA0ds+ZVD+pxrBni3lza9jd80DvXCrxC8yldJ7sGb9ovuu9YuQlepKX1crvi22Onk8/HjoHe8hafrU9sM+nnzpU43wa/+o2n8aerfzayip2j11W91A+8trUfS79hPg5uNpc+tei1whVfS6955B3Lm30aiwXu8V84DHLgauvnFjXctDhC5SDwVoOxrU9+j7tR0KyN/7hLQdM1Liz2LImYuRX9Q+7cXrx7wL7eXT8rfucPPsfde8TPP66ZNzo/WBiPlxuEXT3G9tRIa7KcI4et3zB+b6t73CneRcVSPeOpsnbqB+T5vvD6Ve4NJTUrpS3zP/NWL7VYfSQ1HQO/262pzn+2ufK6Zo2B8T8DWc7rn9qP6+OH968KLDnheX3NC/MHXwfi/kLkibXM4t5hG/+njuEzV3J0yR+K50cYjIXF93IuwQnLBvoXDybi/+vpUtdknw8OyWsty/dm5/2O0DX4X/4Hse6z/mr5a+mg/v786gOjjzP6W/uRk3K4u9/OnoPbvUvHg2N/LoCU15Hi90rnTnWM/bil+0eUFMu2or5Y6QB5wJQtjzFD9udtybtO4r5A/RmAWp1rC2v8cOa12Z9bqKYf9eZgeuqedsKMweeK+YNzBpQyT8j7WiutHsD5P0C7/qfMX9MzNs5kfsVf0A6L0upXh7Qk7IQc4yysBK/vHd6lqXX/z5Yc3cnYfXKNfk0y5yncnwwwD8/H0Z43jdlo5RG2jsvlPyZLXaam373PXnPtJcPzEx9FX/KCUyVzK+RYt6Xvj/VWjbUvVsehAlHzL/CeZaq670nid1fcGYywV5G3vd+jygnsarag6Zi/rmTxb9zUS+hQvmbbNyWufp/T9wkvOUFxTBDw7dazNfjfytnMKaLCNc6J9ak29Vi3krjgz8Snzjpz/1aKO4XO/H4gZ72+z8SvZlOF/zjhmcTxnNEf7O3jJq6OFnMtzuZcp+zH3vom9/1e79nSByu0bz2zhe3ZdX9nkqdX1fJa5B3KQdiJ9Ej0yHZfOeQ/KnWpmV2idzXw996vu3VIaz7/CtSbnWMmM+/7nmjqz1Ih+eF7Ttj7WvN+Ocpt676LuMYMZ9t2o818p5hK8P4ZW0jTRu7TsxXI2e0ia3c4t7SPtq/h2LXOyalFrvCfUDMkfJh8hpz8a6qrbxe7BSL1JPIGOUH+u0TMret37yh+jxX88FdFiRttR2ztG3JlrbNjCU1fu5v/R27O/Kc5AuHawgM9Xs5HzjV7ro+repTv7vvM+ORPLHfzZdOnX2MOqN3y6o/I2V1y5QZo2/P53S4Wswd3wYnwVpOcF+vu7CxX+td2DeJeabehe339o1mvHy62MvypRCLh1GeO7NteyfMb2wTtxPwPZHy18Elr6xKxsivxc52bPQ3bc6rotejHvdoh9ujDh/qXg3Ni/xwHH2ee7VNvWwl9lubOZk=
*/