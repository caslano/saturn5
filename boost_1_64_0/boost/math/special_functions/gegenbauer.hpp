//  (C) Copyright Nick Thompson 2019.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_MATH_SPECIAL_GEGENBAUER_HPP
#define BOOST_MATH_SPECIAL_GEGENBAUER_HPP

#include <stdexcept>
#include <type_traits>

namespace boost { namespace math {

template<typename Real>
Real gegenbauer(unsigned n, Real lambda, Real x)
{
    static_assert(!std::is_integral<Real>::value, "Gegenbauer polynomials required floating point arguments.");
    if (lambda <= -1/Real(2)) {
        throw std::domain_error("lambda > -1/2 is required.");
    }
    // The only reason to do this is because of some instability that could be present for x < 0 that is not present for x > 0.
    // I haven't observed this, but then again, I haven't managed to test an exhaustive number of parameters.
    // In any case, the routine is distinctly faster without this test:
    //if (x < 0) {
    //    if (n&1) {
    //        return -gegenbauer(n, lambda, -x);
    //    }
    //    return gegenbauer(n, lambda, -x);
    //}

    if (n == 0) {
        return Real(1);
    }
    Real y0 = 1;
    Real y1 = 2*lambda*x;

    Real yk = y1;
    Real k = 2;
    Real k_max = n*(1+std::numeric_limits<Real>::epsilon());
    Real gamma = 2*(lambda - 1);
    while(k < k_max)
    {
        yk = ( (2 + gamma/k)*x*y1 - (1+gamma/k)*y0);
        y0 = y1;
        y1 = yk;
        k += 1;
    }
    return yk;
}


template<typename Real>
Real gegenbauer_derivative(unsigned n, Real lambda, Real x, unsigned k)
{
    if (k > n) {
        return Real(0);
    }
    Real gegen = gegenbauer<Real>(n-k, lambda + k, x);
    Real scale = 1;
    for (unsigned j = 0; j < k; ++j) {
        scale *= 2*lambda;
        lambda += 1;
    }
    return scale*gegen;
}

template<typename Real>
Real gegenbauer_prime(unsigned n, Real lambda, Real x) {
    return gegenbauer_derivative<Real>(n, lambda, x, 1);
}


}}
#endif

/* gegenbauer.hpp
eG48XqfXHGu3GquOHy88ud47X3vlVZu/zXwu3zkvvM571bzOqdXfbh/TngG36G/7TzbHJ7st/3mdeb75fdN9k/7z+tJp5v3t92qP8C+Z3+88qL0qq7Tn2IVnmHS1J+jeO4tM/DPH93rT3yK/QHsLfcHEs/Ej5vX8tPZq+JT2dLrTpL9ukgl/55uVj7NN+D1Z7U263Pw+P26OHz5bewHPN+8f9pv3lzxnXm+ebt7fltKeGiUmna3vMq8P3Kc9Sd5hjt+/XnurXKs9IPbpb66/rL2pZpp4Z52nPYq+aH5f8KHTzedrtId8u0l3zX7z+sTF5nX/eu2tndCeBYV1kkK8Z2jPoV/pOv7NvD7Sf5Y5/jMT/7YB/e3u07UH7m79jfsF2su5QX8rfY/yt1x/E3yr+fz0ehN+zmztfVFt0t8RMq9PdWpPK7f+Bv0Onc93VI92m3iLPlhkXjt0fpuUz83m/eVrtbfBq9rr+hKVR2eRKaeXVH6vam+Jefqb/3fpb+NvP928r3I/sNN8ft7vzfsbF2vvY5X/eQvUDqbqb5Yrvuk/Np/bcqnq7aEiU87Pm3BnT9YeSKus5v0x7Rkyaj730IvaY/tbSuf35v1nL9OeNR/Q37T/fpFpHysmmXj/al73z9OegTUW836HCbeuwbzO/KDO8yrt9Tdi3l/0M+3ps1t7DMzRnqml5vj6M03826eZ1ydeNu8f2K/rr72hNm7QnhwVqk9Fak9h1R+v+fzupDk+d5H2UrlFf2v/bdqT7I/aI9atcNvMddj6A+3RdY3FHL9nkimPg+Z10ZM6z9u0l/zj5vPP/c68bjt0unn/r9qrokR78lyrvXVmF5l06lW/+0w6m9P62/9rVE9nm3imqj5P0efOvd/8vjqt8v+Q9hp+u/l960Um3vN/of7lw9p7I6X2/JD20pivPYkj2mt6h/aC/6WJZ+pcE37Tdeb3BX806e9onmLO81H9zX/tFbR4lTk+X3uZb79Ve6u8rD2X1J+fvVL94p7TlI7+pv5G9TtXqJ9bbdJfPsOkf+9H1M6ax/fo0565b1G9nGVeZz9pPjcloT1+3qt+daH651+a31+8XHvO/VN7J1yhvTR/q89/24Tboj2+NtVO1nXWnjZvUT+yzmLK70ntkXufeX/qTO1FWGZ+X/wR7fFwWNelwcTzUoPNpJvQ/e2j6tduVXt6m/bgWq/72oUmnv0/Gt9zVXtm/EH3N5f5/OGM+o312ivwQvP++ZervReZ+FZfacKtf4/2XPib9oIYv/9qr8GiJrWzr5r3Z+s+NGOxeV30mOrBo2rP/9ReeA/r/nu6+pHzzeusKboPz9X5bFS70P1hxyOqR2q/05vV3r+h61KlPUO1R9mM3yif96rf+KTOf6mJf9129c+vaE/xz55p3le4TZ/WHnbnFJvruUzvO025XfZOE8/09kkmHeX/kQoTfv0L5vNPvlH9wU91H/yj9vRaouu6WXsAvcP8Pkf1d4Xq7+G3am/4mepHEsrHFSa+5X83769Lao+KWo1/iotN+1C9eHLExLe6xxx/SPf97WoPT6rfe/AxjV/OUnw3aY+YRdp7b7rui6o3T7+i6zSgPbEqJpvzLsxjCvl7f7F57TXhJ79bey73mngP36N8f0/3p+tspt++VuV4mXmde6b2WM1pj6RfqN79Rf30IY2z3qE9A7W33OI27VF2hvKv+rZ5kTmfnWonT01WOpPUr9xo0tm2Q+OuD5n3N6i+T31ce9WtUX33a/zwE7W7C83rs5/Uno+/156XV6s9zNLe8M9qPPGJSaZcSrTX1AKNAyuLTLnGtefhWdoD6R4Tbp1T7UnjooceN78/6dCeOP/U/VHtoKhC9eg=
*/