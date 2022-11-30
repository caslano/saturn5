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
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
*/