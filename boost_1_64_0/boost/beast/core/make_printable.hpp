//
// Copyright (c) 2016-2019 Vinnie Falco (vinnie dot falco at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/boostorg/beast
//

#ifndef BOOST_BEAST_MAKE_PRINTABLE_HPP
#define BOOST_BEAST_MAKE_PRINTABLE_HPP

#include <boost/beast/core/detail/config.hpp>
#include <boost/beast/core/buffer_traits.hpp>
#include <boost/asio/buffer.hpp>
#include <ostream>

namespace boost {
namespace beast {

namespace detail {

template<class Buffers>
class make_printable_adaptor
{
    Buffers b_;

public:
    explicit
    make_printable_adaptor(Buffers const& b)
        : b_(b)
    {
    }

    template<class B>
    friend
    std::ostream&
    operator<<(std::ostream& os,
        make_printable_adaptor<B> const& v);
};

template<class Buffers>
std::ostream&
operator<<(std::ostream& os,
    make_printable_adaptor<Buffers> const& v)
{
    for(
        auto it = net::buffer_sequence_begin(v.b_),
        end = net::buffer_sequence_end(v.b_);
        it != end;
        ++it)
    {
        net::const_buffer cb = *it;
        os.write(static_cast<char const*>(
            cb.data()), cb.size());
    }
    return os;
}

} // detail

/** Helper to permit a buffer sequence to be printed to a std::ostream

    This function is used to wrap a buffer sequence to allow it to
    be interpreted as characters and written to a `std::ostream` such
    as `std::cout`. No character translation is performed; unprintable
    and null characters will be transferred as-is to the output stream.

    @par Example
    This function prints the size and contents of a buffer sequence
    to standard output:
    @code
    template <class ConstBufferSequence>
    void
    print (ConstBufferSequence const& buffers)
    {
        std::cout <<
            "Buffer size: " << buffer_bytes(buffers) << " bytes\n"
            "Buffer data: '" << make_printable(buffers) << "'\n";
    }
    @endcode

    @param buffers An object meeting the requirements of
    <em>ConstBufferSequence</em> to be streamed. The implementation
    will make a copy of this object. Ownership of the underlying
    memory is not transferred, the application is still responsible
    for managing its lifetime.
*/
template<class ConstBufferSequence>
#if BOOST_BEAST_DOXYGEN
__implementation_defined__
#else
detail::make_printable_adaptor<ConstBufferSequence>
#endif
make_printable(ConstBufferSequence const& buffers)
{
    static_assert(net::is_const_buffer_sequence<
        ConstBufferSequence>::value,
            "ConstBufferSequence type requirements not met");
    return detail::make_printable_adaptor<
        ConstBufferSequence>{buffers};
}

} // beast
} // boost

#endif

/* make_printable.hpp
oowwkc8xtC/wpEXksx/+XYBwat0SZcmKZybv10P8z0Hap9jIEPdJET+bGiUTETYyEWsjE3pZr2EjCTUMIwPcZ7U9eOfZEaHKGm/sLGquZwrJ8itLpnVApOQpy98bR5Zqf0rFfa2qTzFNpH0xvXtjRCo5ymf5euMYrZXvWCOe67K+lvDTjFg8DdsB+e0X+wlGO62824vdE0iN2xiNaxUuvexHRnr2iE/U2pvOEibRdEPrMk1rZzLEfpfZ1giT1TvLwOeRjkRt74BK8dMJPb2b60v0PT5OV+vteoi/AZCYOF935mmhuHeFe7St++XifjbcW4iMxDZibWOIrDvRy4963GFiL2bZG0bkZuwx2QN9m+hSXzG185mtW5aPOemdVQN2Fw4d/9vaA32HQR0AoAP3QG+FaxszfYXbo2N2E9gFvBnsBj4HDgJvBU8E14BTwbXgHPAOcD54J3gOuA68AFwPLgc3gFeDd4HXg5vAteAD4P3gg+DfwIfAZ8GHwb+DfwVfB58A3wafBHeAT4HW8zwDHgSfBX+20kn7Fep7t3zbl+fsjmsp684lIUZNc/BKsBN4FZgNrgIHgTeAE63nB+dbzw0uAdeAV1jPB64AN4FbwM1gLXgfaD3H/eCz1vOAO63nAb8Gt4D/BB8Bw6zv5uAU8FmwBnzRih98CbwSfA3cCG4Ht4D/AF9iuC/BHeD34E4w0oX5FzAWtMxtaM4GPwL7gx+DA8EvwAngXrAU3AeuBONCUT5gPLgOTAA3gC3BOrAt+CqYAn4DdgTDkb+DwXjwMcTTEtwKtgFXg8niTp1H73dMfrfNBzNwTWK5PAF/LcAXwWTwDbAb+CZYAL4NzgTfBReC74GLwQ/Bi8HPwLvBz8H7wC/Ah8EvwUfBPeA2cC+4C9wHfgHuB/8JHgLzrG8v4FjwR7AS/AmcD4aH4T5gBLgJjAYfAmPALWAs+DLYBvwUbAt+DnYCvwM7gzF47nQwFswAk8BMsCvYFewG5oAFYG9wNNgHnAcOBJeBeeC14AGkazX4HXgLuB28Tdyp86++SeH7G+tBFq5q5vdLbo+u4xtgRyufwe7gDnAguBOcYOUvWA1+DC4GPwEvB78GrwL3g4+AB8Fa8J+sz9+zPh8C3wd/APeAP4GHwJ9Bq42OYj2IBqvAePB8MAG8EGwJ3gi2ZX1IBmvBNPAA2AmMsPYFA3uAWeAgsBs4GOwJTgZzwXKwL3g9OAC8GxwL/gk8E3wGHAc+B04G94BTwX1gMZjghhyDXcDFYE/QBPuCLnAguMuN+9LdKgf1rYPfafK5XnUoy2EY5X4U5X4C5X4i5b6Qcl9EuZ9KuS+j3FdQ7isp91WU+zngFnAu+Ao4D7TKYT74KbgAPACeT7m/ADwTvBCcDC4Drwcvs+QLXA4+Cl4JPgleDe4AV4K7wFvA4yydfzAJ3AB2ADeCvcG7wFxwMzgFfAicCj4MXgQ+Bq4CHwfXgovAjeDZ4D3gJPA+uiNf8U7EeW1wGvuzWFxXsD8binog8/RgBjgc7A+eBo4EC8CJ4HiwEJwAFoOTwLngZPAnsAh0If5iMAksATPAUvB4sAwcBs4CTwbLw1juBudrwSSmLxzXUKbveZcnfXVgT3AbOBJ8HxwN9nZ7zgzpC7YAYaYuN+clOSea76fLvQD3bweeDQ4AzwFHgOfxuc9n+nINzvkB6YwnBFdXxlMDfzHgYjAZXML8XMzwsWrOC/ekXFv+QijXA9m+5IOdwOF8nzgF7A2eBlrpG8X3itHgSeDp4HjwDLAYPBOcBY4H14ATQUueJ4Cf0LwHnAT+AE4GrfyeArYHi8Au4FRwKM1TaV5K8xqaN4PF4FawBKwFF4CJLuQf2Bc=
*/