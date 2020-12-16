#ifndef BOOST_ARCHIVE_DINKUMWARE_HPP
#define BOOST_ARCHIVE_DINKUMWARE_HPP

// MS compatible compilers support #pragma once
#if defined(_MSC_VER)
# pragma once
#endif

/////////1/////////2/////////3/////////4/////////5/////////6/////////7/////////8
// dinkumware.hpp:

// (C) Copyright 2002 Robert Ramey - http://www.rrsd.com .
// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org for updates, documentation, and revision history.

// this file adds a couple of things that are missing from the dinkumware
// implementation of the standard library.

#include <iterator>
#include <string>

#include <boost/config.hpp>
#include <boost/cstdint.hpp>

namespace std {

// define i/o operators for 64 bit integers
template<class CharType>
basic_ostream<CharType> &
operator<<(basic_ostream<CharType> & os, boost::uint64_t t){
    // octal rendering of 64 bit number would be 22 octets + eos
    CharType d[23];
    unsigned int radix;

    if(os.flags() & (int)std::ios_base::hex)
        radix = 16;
    else
    if(os.flags() & (int)std::ios_base::oct)
        radix = 8;
    else
    //if(s.flags() & (int)std::ios_base::dec)
        radix =  10;
    unsigned int i = 0;
    do{
        unsigned int j = t % radix;
        d[i++] = j + ((j < 10) ? '0' : ('a' - 10));
        t /= radix;
    }
    while(t > 0);
    d[i--] = '\0';

    // reverse digits
    unsigned int j = 0;
    while(j < i){
        CharType k = d[i];
        d[i] = d[j];
        d[j] = k;
        --i;++j;
    }
    os << d;
    return os;

}

template<class CharType>
basic_ostream<CharType> &
operator<<(basic_ostream<CharType> &os, boost::int64_t t){
    if(0 <= t){
        os << static_cast<boost::uint64_t>(t);
    }
    else{
        os.put('-');
        os << -t;
    }
    return os;
}

template<class CharType>
basic_istream<CharType> &
operator>>(basic_istream<CharType> &is, boost::int64_t & t){
    CharType d;
    do{
        d = is.get();
    }
    while(::isspace(d));
    bool negative = (d == '-');
    if(negative)
        d = is.get();
    unsigned int radix;
    if(is.flags() & (int)std::ios_base::hex)
        radix = 16;
    else
    if(is.flags() & (int)std::ios_base::oct)
        radix = 8;
    else
    //if(s.flags() & (int)std::ios_base::dec)
        radix =  10;
    t = 0;
    do{
        if('0' <= d && d <= '9')
            t = t * radix + (d - '0');
        else
        if('a' <= d && d <= 'f')
            t = t * radix + (d - 'a' + 10);
        else
            break;
        d = is.get();
    }
    while(!is.fail());
    // restore the delimiter
    is.putback(d);
    is.clear();
    if(negative)
        t = -t;
    return is;
}

template<class CharType>
basic_istream<CharType> &
operator>>(basic_istream<CharType> &is, boost::uint64_t & t){
    boost::int64_t it;
    is >> it;
    t = it;
    return is;
}

//#endif

template<>
class back_insert_iterator<basic_string<char> > : public
    iterator<output_iterator_tag, char>
{
public:
    typedef basic_string<char> container_type;
    typedef container_type::reference reference;

    explicit back_insert_iterator(container_type & s)
        : container(& s)
    {}    // construct with container

    back_insert_iterator<container_type> & operator=(
        container_type::const_reference Val_
    ){    // push value into container
        //container->push_back(Val_);
        *container += Val_;
        return (*this);
    }

    back_insert_iterator<container_type> & operator*(){
        return (*this);
    }

    back_insert_iterator<container_type> & operator++(){
        // pretend to preincrement
        return (*this);
    }

    back_insert_iterator<container_type> operator++(int){
        // pretend to postincrement
        return (*this);
    }

protected:
    container_type *container;    // pointer to container
};

template<char>
inline back_insert_iterator<basic_string<char> > back_inserter(
    basic_string<char> & s
){
    return (std::back_insert_iterator<basic_string<char> >(s));
}

template<>
class back_insert_iterator<basic_string<wchar_t> > : public
    iterator<output_iterator_tag, wchar_t>
{
public:
    typedef basic_string<wchar_t> container_type;
    typedef container_type::reference reference;

    explicit back_insert_iterator(container_type & s)
        : container(& s)
    {}    // construct with container

    back_insert_iterator<container_type> & operator=(
        container_type::const_reference Val_
    ){    // push value into container
        //container->push_back(Val_);
        *container += Val_;
        return (*this);
    }

    back_insert_iterator<container_type> & operator*(){
        return (*this);
    }

    back_insert_iterator<container_type> & operator++(){
        // pretend to preincrement
        return (*this);
    }

    back_insert_iterator<container_type> operator++(int){
        // pretend to postincrement
        return (*this);
    }

protected:
    container_type *container;    // pointer to container
};

template<wchar_t>
inline back_insert_iterator<basic_string<wchar_t> > back_inserter(
    basic_string<wchar_t> & s
){
    return (std::back_insert_iterator<basic_string<wchar_t> >(s));
}

} // namespace std

#endif //BOOST_ARCHIVE_DINKUMWARE_HPP

/* dinkumware.hpp
Mvsa9CgHuFXC3PzOqCCQMPRkZQeD1kG6plN/qeaWd7i8tIuBIzK15cT/JnME2B7x9D2Vg6Y9ulAdgqqqSmDwe4kCGrbNveBRvjkm8d40bfyTttDOfBP0oIqNebU77xlR6OuEgrQrm6L3GBS23jNjRXJHWm0ZtGV5OgCkpkdiUitxnnUuMdeyK5+UXfnVXNqVz2BXHtB3PEdLRLKC6o8ZPk2uLySN4enSjzlzpR8vLCdvTlQLWfP4a9K3h1hMPdW0vx8bNG/QpKm/SlP6PWiGNM7uExXDB/7OWhud/j21Nsrxv++Wo58KRoZ6/3u3HP1U75/kXQlclGUan+EcARnUUDMPPFILRRR1ETwYARsUjLI8KzXTtKw8ZrzywEZS+qTsrq22u+3a7VyXyAokU9PULEu3S7N2P5zuA69y9v88z/t98wETomvtNb+fMvPe5/M+91PVkPzPbH+mUX5SQ+0nmu0PNMq/BpboKXhPFP73dD386dt1DeF/ZvmnjfKVDZW/UMpTVI8FQFzKwoL6d6HxP6P9yJ8MfMjdUPs/PmWUb2uMp3VD5TdIedEn9oXwf2XJb74wBP/Dkv/ggyH4H5b8K7QQ/A9Lfvd1IfgflvxPrwvB/7Dkz1kQgv/xZDDfHmJ8Gyz5j78cYv6SD//HXCQFl7eWf89iVR/20w4AgJccSBQO4Uy8xabDzgbw12zVghY5PAUYibaHngyKdeGPJtf98wg+RvZCFkvQCNS0IyAzXYDMe8+xk9A9pcPLdQcQEQMHdbM3XP1gCeNvMVStI8GqjUwkngieWpt+kzHf9ASPWTsM1vWCq2shobnPyUN3PyOhV8gzN02feTuNzYIuusoeEiB7Giq4St1v6MvQkNFK4Flp5WFrKy69a91WnAnhmKazmc2ZMCLB2cyd4EzITnI2y0rC71T8TsXvLPzOwu9C/C78DgmTvkPKJJ87wl6SHmyreuUTJ8Yw/4X9nPu4qBkMCGAvPbmmfg82eEYP2cXW2N2mUSgb5uXdPU/SPZ3VrrlWiewKsq3pvsyA93XLphkHwO/gPZVXR87Cm8/QShZ2o7PwEwjlE6NHFPz7ozqNTdclY1CwP45E6sb7kLox8lEk2QyA1RB9f43Ryh6duIM0J88feE6z8XXYTNPu9lJ6Xt+/j4sQvtIfw0YS4xj6W8BScLCUAVgHcmW6if2EwcMFdGLG/fWAlRGARM5M2xwYk3QKfN6p+/8Yz0SvXiLT+NN9fKGi04TrhgERWPCAqVSv/uMM/6S+Gwz4VCI1ypBYvHlhDOovf51KVAnMIO0GAJFWEXwnivQ4mzI5Ws1VcktdXfU2c/mCeKD8ZzNqY6NanI2NAg/laWHvH11E5lgBz33IOnRWUxvkJtvBRFAVGr8CJn9KnP6RdDfJahGiPcozI6UWFwI8+vY74foUJFSO9h1ro/zoO2onu+om8EimzwAw1L4hX7q+oxFeR2n2z9U/2jhCcayr7GayFWW9x6OR3mQ4f8eQD97Nc33JzppxOW9pldWv4ysqPvEzMCdx8gBsFA7QyIvmpodNIJRA9+JcO6oxxedfVFyzoBc1+p6+8S+yiZM89NcJ3A+Jk2bX7cl/sds3xOZtrs9ebCCn3kiXtsGfKyHR9QeBytaukewqI1WCGjgZTfC2Zc0C5JavlovZ+2nCBO/QL1/Dl9L0A8+RrUjmPN00MfntiBvFNbXut3I1bI2G++jD4qfwA7gXBnGTA+KGOXbeDuS9Otq10Y7doEif9N2Gr4TbbuBHkOwfOF2zByr8YVpVcQVrtGlHnXmH9A2zyH5iySITPoqyR5cXFSzQ9XmLZLcygD+7Ml/3NiVqsyt5lIDCzkcoDCuMZdzK4io=
*/