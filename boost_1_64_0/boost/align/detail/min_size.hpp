/*
Copyright 2014 Glen Joseph Fernandes
(glenjofe@gmail.com)

Distributed under the Boost Software License, Version 1.0.
(http://www.boost.org/LICENSE_1_0.txt)
*/
#ifndef BOOST_ALIGN_DETAIL_MIN_SIZE_HPP
#define BOOST_ALIGN_DETAIL_MIN_SIZE_HPP

#include <boost/align/detail/integral_constant.hpp>
#include <cstddef>

namespace boost {
namespace alignment {
namespace detail {

template<std::size_t A, std::size_t B>
struct min_size
    : integral_constant<std::size_t, (A < B) ? A : B> { };

} /* detail */
} /* alignment */
} /* boost */

#endif

/* min_size.hpp
vOq1p/A/vvx6nWXi/9n2+B9XHj5Yx8D/k0Fb/I+Azzpu4H8ze/yPgG9mwP/Nvv5uEfA3lhr4b1//+RHwZxnwde3rPxJbHv7HwwrebV//kgj4UgP+PaxK5fgfa8XXi5ZXgv/bq4uv15erb8uySvC/rLr1HYyx1rf+Z/v6Wle7f5PL1ReopL4VetX0u1tM+fk+9wdj/Zvar38E/OHvjfVHJyofv7Pc+b+1kvFvq/b4y9U3vJL6VnxT3fo6l6svtpL6xnxV3fpCjnLnfyX0+KJq9296ufrOrqS+g1urW1/PcvWtqoS+P1X1fa+C/Vm81MziO6DHNwtcDgR9mdbYVLftgqellUeCpAmvJ2JClYrWeTCLcJHR5cYdIg8x1bOW82hLgk3AfU5EdewFa5EoKT70FT3C/TY2W+r9PxSk/gtyX4jmGLk/Qv8rof8CTzfTTxVwm0W20wYz8i8BUhJx/z+pytedb5QfZq9/o+wfBB7Pr08b8LvqRYH3G/DxPQz4idHgMwVe7J+IHln7Xyb9N3+nLbSOJ5XXX5XXFmWRKUlhV/FOnaUtxxBrAl5fJlfv1JLK9D9F1Cjes2f/wtV53IkOZezwD3z3JkKz210f9SKoEISP/3DXh1m0PmsloY7/XITr2UyFW4OPZ6uHPBAWI/GTWLGVoHfwZP3P6Iy2GUoF5M7gXk4v+KjFcFY8XREkD3UdzPgyYk/RELPnMyPL3PezNEmeFgVdZ7nYB3drAofV8INcS94iwlKp2PCADc/Xf20D79ci9cwmS1HE305ZCLNHl3v8wtDC4KqVv+VH6b/8zBNK6ry16DG7Kc0pv24HjsX76wCP/1SDHEksDkZYMtjrCxr335/VqjcNlCGkV60YKN2WxcDW04kvx2Pc+ZlIEa3AM6EmT4HEC/lZEEGuaT/vBWeKr3ivmCvh1eF6ny45BQEjBE9tlOEozfDEIJD45Snseoc+bDeXBSzNrpnRXe9rZkyUjLlPO6TuLKn7FVV3fW9gHnt79dcYcWMer5E2IDUlxDqgy4LsnXmIKDoqnTayFxbN+Dj1lqXp+q3AJXzVm0KspR269vZYVaEjUULtxnzJlK3xiJM0xpy6gZN35LhGnKRO+RNRF9wBpqM1uAN8I8jlYqy+Najft2NpWNcRCCb6AGZwai0gHpW7uEiTuyagQ+vQ2Baqx6ms1W3hE8vBv+PVNMZ+EjDh+yjeR41Nj6P65M84nePcj5PvU0XBox5wQL8UIpOKbcX3Sq3nSKGQCFQf/lATBY/lFcwby7/RF05eK3+myp+J8oeaKg2QX/Vhw8MD+f3iWv9eH8X/HzPPi7mKHjvmR7P/MeDrrjTge9rTb9rELaXQcCl01OnMaeApIm/YtK/ng/j2QVne0tU9z6+QquQFCjpIpFc0j8zcZ5L5j9eF1yn91k8AQ07evQX9UEN/VJCL95juyaWO0zCptupDT/9RnUqD2hj+sRJJChyDvE6Lg+LzRruRCdkfyDfWmC94r51Z2h7P3wprrAYMbytVpmvEgCEJQ5pTV+LWTtS77An+ChMGpf/3o4V/eHuOWrKcupXxDxuPGviQZwAfmmPPP9irvo9XFWgzaRPhTU7ZSASGJjlyLvUpDRf9iXiO8036bLu28vMkXgx9HAIsdGsSLxGZnpyGRrsav9GdEcuYjnZJygZ9qZUpTgx9od2V6kyhCO1/K39xf1EFfmnKEWM/ZBWp+epcu7L9gCo+TYHXCXdmMXyabcXXEut8PsPtRfA/R8r3Pz2ZbWGl8ztV56ON3yjfwNAyqwWyH+X95wcLvhTMUkPKsBmSGj/gBV96GMALPw5G4f8M+LoXG/DNa1Wp/8mYdbUU9QVyWzpk//s=
*/