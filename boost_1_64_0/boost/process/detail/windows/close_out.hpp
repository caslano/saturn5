// Copyright (c) 2006, 2007 Julio M. Merino Vidal
// Copyright (c) 2008 Ilya Sokolov, Boris Schaeling
// Copyright (c) 2009 Boris Schaeling
// Copyright (c) 2010 Felipe Tanus, Boris Schaeling
// Copyright (c) 2011, 2012 Jeff Flinn, Boris Schaeling
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PROCESS_WINDOWS_INITIALIZERS_CLOSE_OUT_HPP
#define BOOST_PROCESS_WINDOWS_INITIALIZERS_CLOSE_OUT_HPP

#include <boost/winapi/process.hpp>
#include <boost/winapi/handles.hpp>
#include <boost/process/detail/handler_base.hpp>

namespace boost { namespace process { namespace detail { namespace windows {

template<int p1, int p2>
struct close_out : public ::boost::process::detail::handler_base
{
    template <class WindowsExecutor>
    inline void on_setup(WindowsExecutor &e) const;
};

template<>
template<typename WindowsExecutor>
void close_out<1,-1>::on_setup(WindowsExecutor &e) const
{
    e.startup_info.hStdOutput = ::boost::winapi::INVALID_HANDLE_VALUE_;
    e.startup_info.dwFlags   |= ::boost::winapi::STARTF_USESTDHANDLES_;
}

template<>
template<typename WindowsExecutor>
void close_out<2,-1>::on_setup(WindowsExecutor &e) const
{
    e.startup_info.hStdError = ::boost::winapi::INVALID_HANDLE_VALUE_;
    e.startup_info.dwFlags  |= ::boost::winapi::STARTF_USESTDHANDLES_;
}

template<>
template<typename WindowsExecutor>
void close_out<1,2>::on_setup(WindowsExecutor &e) const
{
    e.startup_info.hStdOutput = ::boost::winapi::INVALID_HANDLE_VALUE_;
    e.startup_info.hStdError  = ::boost::winapi::INVALID_HANDLE_VALUE_;
    e.startup_info.dwFlags   |= ::boost::winapi::STARTF_USESTDHANDLES_;
}

}}}}

#endif

/* close_out.hpp
S9T1DPgJnKvk18Mv4Hr4JbwNHob3wa/gg/Br+Ag8Cp+Gx+F78Hv4GfwRfqmuv4I/wO+UPNZLfQbToOGinEMT1oNu2BxGwNYwCp4PvXAYjIHFMA7OhAlwPkyEV6rrq9T1cpgEb4TJ8BaYATfCavBumAkfgdXh07AGfBbWhG/BWnA3rA3/An3wU1gHfgXrw+OwAfRGU3/BGHgWzIRnwwawCWwCm8JmsBlsC1vALNgS9lXXA9T1INgeXgjPh6NgJ5gHO8MJsCssht3gFNgDXgZbwVWwDVwPz4O3QH+7dCdM9acXfsz167C3P52wD3wX9oPfw/6wEQ3obdyvbvB22Auuh4VKPkfJ58HN8HF4D/waPgEbxtLuwfPgMXg+PMMfb/gl4V8KD8Er4GF4HRyM/X1wGHwCDoeH4BBYN476EZ4FR8Fz4UVwAsyFhXAsXATz4Eo4Ht4PJ8LH4cXwBVgAX4OT4S/wEhgfTz0I0+FUWB1Ogz44HfaGM+AcOBvOg3PgJngZfAfOg3+BBw2eB+jPp2/h7fAkXIh9ZgL1IawN74FnQ38+nQOp40t7wKv84cElcCxcCifAZXAeXAU3wdVwK7wRPgVvgq/AW+AeuAH+BW6EB+Dd8KgK9zi8F/4I74fRVagHYQ34IDwDPgw7wUdgbyXvBx+FA5V8iJIPh0/CMXAbLIXb4XK4A14Pn4V3wefh8/AFuBvuhB/CV+Cn8DUYkcge4zAFvgEz4G5YE+6B9eBeeCZ8GzaH78C28F3YHu6HneB7cBJ8H06FH8Hl8GO4Fn4Kb4afwXvgQfgU/Bw+D7+A++GX8BN4CH4Hj8If4DfwF3gMepLo+8Mq8DjMgCdgE/g97Al/goPhL/BCaLhpR6AJ50A3XAg98CoYCdfDr9DfCP8K74YxyB+DsfA1GAcPwHj4E0yCscnUgzANpsAaMBWeDdNgc5gOO8MasDusCXvDWnAAzIDZsBq8ANaBJfAMOAfWh0vgmfBp2BC+Ac+C78JG8BBsAo/BpvB72Ax6U+jPwXjYAtaC58I/qOsW8EXYDr4E+8CX4TDof17yYUuuC5W7ObAVvAK2gUvhefBO2BbeD9vDZ2AnuBN2hC+p69dhZ7hXXb+rrsthF3hAXX8Jn4CHYVf4LewJI1J534HxsDdMgn1hVdgPNoKDYGc4BPaE2XA4bA8L4BOwGI6AM+EF8BaYA2+Do+FdcAx8AI6FL8NxcBccD7+EBfA4nAwT0+j/wTRYDDPhJbA3LIED4Ex4IZwFx8DZMB/OgfPhZXAJvBxeD0vhvXAefBAugk/Aq+BOuAS+BZfCd+DV8D24HP4Ar4E/wxXQfxbTdTAFroTV4SrYAq6GreEa2BfeAPtD//3Pg+u5ngJvhovhRng1vBVeo65XwtvgDep6vbreCO+A2+Gd8Bm4CR6Gd8Nv4b3QqMp3LuiB/utY+ASMh3+CafBB2BQ+BNvALbA93Aq7wEfhMOVuKtwG58Dt8Gp4M1wBd8C16nqT0n8IPgNfgc/Cw/A1+C18Hf4M34CR/nFTmAF3QR/cDdvCt2FH+A7sBv8Cs+B+eBF8D46B78MJ8CNYBD+Gl8MDcCH8BF4FP4eb4BfwMfglfAoehs/Ar+A78Aj8EH4Nf4DfQE816ktYHX4Lm8DvYQt4HGZB//29CP7gjxc8CRfAn+EK+At8FBro7YRRcBeMhvtgDDwIY+GPMB5GZtJfhF7YDlaHibABTIatYArsCNNgN+iCw6Eb5kIPnA7bwkuVP8uU/iqYDrfCqvA12Ab+GbaH5bAD/AKeD0/AjjCyOvUNTIadYXXYBdaFXWFr2A32g93haNgDFsCecCbMgvNgL7gE9oYr1PVKdb0W9oUbYD94G+w=
*/