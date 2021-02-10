/*
Copyright 2019-2020 Glen Joseph Fernandes
(glenjofe@gmail.com)

Distributed under the Boost Software License, Version 1.0.
(http://www.boost.org/LICENSE_1_0.txt)
*/
#ifndef BOOST_IO_DETAIL_BUFFER_FILL_HPP
#define BOOST_IO_DETAIL_BUFFER_FILL_HPP

#include <iosfwd>
#include <cstddef>

namespace boost {
namespace io {
namespace detail {

template<class charT, class traits>
inline bool
buffer_fill(std::basic_streambuf<charT, traits>& buf, charT ch,
    std::size_t size)
{
    charT fill[] = { ch, ch, ch, ch, ch, ch, ch, ch };
    enum {
        chunk = sizeof fill / sizeof(charT)
    };
    for (; size > chunk; size -= chunk) {
        if (static_cast<std::size_t>(buf.sputn(fill, chunk)) != chunk) {
            return false;
        }
    }
    return static_cast<std::size_t>(buf.sputn(fill, size)) == size;
}

} /* detail */
} /* io */
} /* boost */

#endif

/* buffer_fill.hpp
U7K03+6Sqr9MahnNySP6mromPz4ZyyBwafFiYfYmKR8Ej4WhrLjFDQz72LdhEPhYg/dEnUm3a5pebl9dlNuGqRm1q45plNV207xoW3qn3tBrxGRYmuRTg7moKjeji041Fm6FmLyVDaJd8qskt5ptPb5BBiscD9ZwfPd0D3TdkXpN+ARdE3lfZirfAuyRLHa7JJ8kj4r6fUx6YYUAh1G/DDwP4slayVgrAbWe/CKTiILQ75WpSTObWFSOtmqV2VwratWo6R+N4q9nUr5i/KFrH2v12fIaJEPmEABjFmLjQT8sFnJkqKSvrgP6w3RQ6CRJ8g+CQXJBxnp8kYxvbvgeJW8uNbbJ14xZ4RCJDnKOm/SB9omYHoY96IXAHdn0Ss2OO5OM55TRL7DQWdiYwKVFdrukStJSGKqP0P4SRL3J9hm9vo/Dka29e98C+AEyZQzTsSqo4haN+LWhmePxXvHWrKm4+Nm694Sw71Gtj3ROUS9pcNyAhcMXuovb3PCDkNmy/kSELzVo0qH1S1JLWV2wCQM/wjZ8DrJraU+N3DDCRNLxUbG48CG3sGtB/IRsSLTybXAFiYoBMb2lLSOVyGvn+oPeVB8u81PMs4pFNdiNHqY5VLDmXNakmeRxrGXDVvBFlSvssrOAC1k2y52k
*/