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
kyNyVi5ZIS9eda9h7IJFEasWwx8NEjE4YsXKiOkzZ06MWLRAXnCvYcsWkqanoT8a9PSAsPjCVeb4Jmnjrd81qDeCsheGQIkRfJJ/Q57HbYUVMMBQkWgK5MatqN7DXl8EVdyd58NfvlzBixFio0Aw3MH4mDMQRk2Vb71AoSKK5ptUg4oXV1YkmAJAHaIBZbYFspfDgWsWM58IEEfQLEAWQAFZXvs93jJDUY3GL0MOVbPtz+JbDladCz8pNUpyLf/e06C+NhfavI4NufUFMoRygZjCggDQCY8AoOhCAHZ8OIDv92DDOv4N/ML4x6WOjDDMYItzcV/KRfrXPgj0W8FIOAAY+K3nGtRisB9qizBCXAAf7fYfCQ4D3OpfNjaoqRgliH0mBoK67xwAlXaQAa9rigldriMIKe9v6GEwjMKQ/ZJrNB43nmGiyIsC3B4VxBgTJjtgjWisMRRrhOJkKGWfsxsndhnlmDIeeOPz62VGeYjH8rGVvd4DqfZYPrDaImAHY8/ZiU37KHDUB27LKcXyodtyxtsRqzC7qJ18igUVETuiD/N/QaoIPIVw7PY8ZKZR1flPio3xAyv2Y3sSt0JgzqENhD/djtf1AZ4/uDH6FNQfNAgcJxxdums4UmwfrbcdhITVy9Qwggj72G35QLGUZg+04+QCmR8ye55AhEgTAWn2ICo7xeZqBeyXp/Gr0hbsABsan5uUlTGTyP4M
*/