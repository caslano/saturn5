//
// Copyright (c) 2016-2019 Vinnie Falco (vinnie dot falco at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/boostorg/beast
//

#ifndef BOOST_BEAST_UNIT_TEST_AMOUNT_HPP
#define BOOST_BEAST_UNIT_TEST_AMOUNT_HPP

#include <cstddef>
#include <ostream>
#include <string>

namespace boost {
namespace beast {
namespace unit_test {

/** Utility for producing nicely composed output of amounts with units. */
class amount
{
private:
    std::size_t n_;
    std::string const& what_;

public:
    amount(amount const&) = default;
    amount& operator=(amount const&) = delete;

    template<class = void>
    amount(std::size_t n, std::string const& what);

    friend
    std::ostream&
    operator<<(std::ostream& s, amount const& t);
};

template<class>
amount::amount(std::size_t n, std::string const& what)
    : n_(n)
    , what_(what)
{
}

inline
std::ostream&
operator<<(std::ostream& s, amount const& t)
{
    s << t.n_ << " " << t.what_ <<((t.n_ != 1) ? "s" : "");
    return s;
}

} // unit_test
} // beast
} // boost

#endif

/* amount.hpp
lfZyqeS8D9j00qoZ3+xK9O6uYfTYF1r1vHYLckD16jorzmtyaX9RcDyMhhNgKz0ep8c76vFecCLMggWwEBbCyXAOvBEWwSWwGG6C18LtcArcCafDUngd3AdnwA/gLPgFvAHKPAae0Hhxc9+se/JgmOYjFLlL89FV77fOh8mwJ7wYpsDL4UWwCPaC18Eh8BbYDy6HqfAFeAl8FfaHu+EA+DYcBPfBy+AHcDA8AC+AJIr49D7O7G9jzqjz+I7ITJ3H/5H8NIRLYQS8D8bo8Vg93k6Pd4f3w6vhcpgOP4bT4ANwHnwQ3gkfgsvhSvgQfETHpbXwKfgo3AIf1/p4Ar4LS+B++BQ8CDfCr+Em2Jg0vwBj4RZ4LnwRJsGXYC+4FfaDr8A0+BocBnfCTLgLToGvw5vgG3A+fAuuhHvhGrgPPgbfgyXwffgC/ABuh/vhLvgsPAr/Bn+EB6DL/Y0VGAo/gi3hx/Zx9cuqx8EgFz9Uj7mW6F2InNZ64/mL3G8XwCg4CbaGxTARToFXwOnwFjgLLoW/h3+BN8LX4Fz4JrwF7oML4WG4CH4FF8OT8A7Y1D2fg7HwbtgO3gO7wD/CbnAJHAbvhVfDpTAL3geL4f1wNlwO58EV8Fb4ELwTroJL4Wq4Aj4MH4Rr4Db4CNwF18LdcB38GD4Gv4GPw+OwBJ6GG2Cii3qCXeFm2AM+BwfA5+Hl8AU4DL4Ir4YvwRy4FV4HX4Y3wVfgfPgqvAO+Bu+Gr8P74NNwLfwzXAevg6WwFH4Cd8Nf4VuwlnveCMPhHtgK7oUd4VSYoG6xT+3SPTayzweBKUiw2rJnrVj68QkYDb+HzeFJmAhPw1T4MxwMf4WZ0En8k6EL3gAD4FxYEy6CteC9MAiugrXhWhgMt8F6cA+sr/fnofAzGAaPwobwNAyHnMsRAevBFtqOWsM2sA1MhHHans6BF8IOsD88Fw6CHeFo2AmOgUmwCHaGN8BkOBd2hYvg+fAB2AOuhRfCJ2BP+CxMgVtgL7gH9oYHYB/4CbwYfgsvgR0o64HwAngpTIGD4EB4GRwEL4eD4VA4Ag6DGXAszIWXwNlwBFwAR8Lb4FVwKRyl7SgLboF58HV4DXwfjoeH4Cnq71N167jCvo7qXacLv6v6Oj0bWaF6L/m4b5+r14ub9DpxM2wD58O+cAHsB++EQ+BCndcugrfAW+G98Da4TPVWw8Vwo7r1G2P63J268PGNsY66DtkJhsEEmAQT9bqbDM+DnWEPdV8kbo3fqc+9QTvpVxChnuXvU9LRHH4GW8PDsCv8XOfzX8IL4FdwNPxO5x/H4Sx4QuchJ+FN8Eedj5yG98Of4WPwF/gkdJKurbAGfAPWgodgEDwOa8NTsB78FdaHQaS1AawHQ2AUDIXNYDhMhhHwPNgYXgIj4QDYFF4GY2A+bAYnwRbwFtgSLoWt4H2wDVwJvyG9O2Bb3B/BdvAUPAcGuei39vXwH6q+3u1w+6leus6nIpDNqpen68njYXs4QdeRJ8JLYQEcCifrfOpauAhOh3fA6+DjcIaW60z4FpwF34Wz4Y/w9zCG898Im8O5Wn7zYFd4M+wBF8Ce8BbYCy7Ucl2k+S5EeN7ose5VF8nW/AzT5xPDNT8ZsB/MhBNgFiyAYzU/2fB6mAPn6fHFcBR8Ut13BZTb6Z/WurZfW/1L8NuCHEBC2vAtLyQDmYusQXYhR5HwONzoB89wObrx227b/2iBy8O+/6b1/34b//ObBPzT7fynkU9/tv73rf/X2PvP5pzeNv9Prrfb/UcfnbsQb/v/RymDkD7Ez7fK4588828BrIur/Q9/DyBFvwlQGlf7X/JdgCPEG9yWb9MhqUg2MhdZgWxBDiA=
*/