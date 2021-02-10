/*=============================================================================
    Copyright (c) 2014 Paul Fultz II
    remove_rvalue_reference.h
    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_HOF_GUARD_FUNCTION_REMOVE_RVALUE_REFERENCE_H
#define BOOST_HOF_GUARD_FUNCTION_REMOVE_RVALUE_REFERENCE_H

namespace boost { namespace hof { namespace detail {

template<class T>
struct remove_rvalue_reference
{
    typedef T type;
};

template<class T>
struct remove_rvalue_reference<T&&>
: remove_rvalue_reference<T>
{};

}}} // namespace boost::hof

#endif

/* remove_rvalue_reference.hpp
xu6nEHniQ499wr6LCvdQSVQP+6yiYrLCOMMxDrLsc0tHCQPVaZMG7DBmhvl+HcFF0oVDipZWtT7c8He4pcYebEuGRX2FDqNklj5uBoQ+ynXQWMuNSFE6WmIcwFwYtuTScm5iaSKlQV4yL267iDXpHbArO923C2+pzjd6gNztEXsrVfSvTwVupEqKa1IHmZTeQre4b7NxXBVre5qClZNRwFuThJPt0KSCDKb5WjIzDUUucIi+6VT6qfcRZdPidhV8TMIHfkzJijU/GfnRKy0mTIeXojR654EDXeFx1D2Sq4/KC4trtLUe/QBQSwMECgAAAAgALWdKUqTcgiS5BgAAdBAAADAACQBjdXJsLW1hc3Rlci9wYWNrYWdlcy92bXMvYmFja3VwX2dudl9jdXJsX3NyYy5jb21VVAUAAbZIJGC9V21v28gR/n6/YkIIkBNItJ3mgDati9ISZTMnkS4pOUiDgKColcwztWSXpGP9+3tmSUqU7AuuQHGCzbedeeaZl53d7b2hSZKKj3QdxY9VHm7kUxhXKg0LFZtxtv2p9wZ/1HNWvebxTmWxWFVKUJlRrERUClpqZSqiJ0GFKAtaZ4oSWZRRmiZyg0eK6G4UOPSYlGYDNId6ts3THX1PygfaZkVJXi4kBVmlYkFp
*/