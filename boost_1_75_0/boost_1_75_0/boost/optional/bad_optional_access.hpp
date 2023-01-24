// Copyright (C) 2014, Andrzej Krzemienski.
//
// Use, modification, and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/optional for documentation.
//
// You are welcome to contact the author at:
//  akrzemi1@gmail.com
//
#ifndef BOOST_BAD_OPTIONAL_ACCESS_22MAY2014_HPP
#define BOOST_BAD_OPTIONAL_ACCESS_22MAY2014_HPP

#include <stdexcept>
#if __cplusplus < 201103L
#include <string> // to make converting-ctor std::string(char const*) visible
#endif

namespace boost {

#if defined(__clang__)
# pragma clang diagnostic push
# pragma clang diagnostic ignored "-Wweak-vtables"
#endif

class bad_optional_access : public std::logic_error
{
public:
  bad_optional_access()
    : std::logic_error("Attempted to access the value of an uninitialized optional object.")
    {}
};

#if defined(__clang__)
# pragma clang diagnostic pop
#endif

} // namespace boost

#endif

/* bad_optional_access.hpp
FqFB9NuU2K1tLaGKS72XZRGUpqwv8aWUo9+JFInVXEvPTo9d/IZIfx71C1k4RDp2UVbflO0BNAio380zwLuq99+ZdUfHGSVIkk9d4ufWHLM1QVHgo4OBntga6JevP3z+wd4LbCNcBohfK1xZO64N/tRx+Q+T4D3MbJvBbYuuJ26UPWGTruuPCRmh/04L2xJ90P2XlGTNe67gi7tcGZGnD8T5eNA+Z1BFr5d5QezrwHloP11uMg8fy3/oACLMg5os58ha4rMvUFFN1KoDxkOC6HToXHDZurwu9iTFXgE4IA1VmpxOnC8bsL8pMEOTBTB70PbWbHKj48nc0/LDxtg1QLIFUffOt+gLLBKtS6/OxwrAJA+USa+UVsfBjH6vnQ7mJCn1fRlzcBmdcBpVcxxVcxptcRyFTUfURjVWHDVXODiNYlxGoc6j75xGV51GQ+or5Jsr5FsqapsrahsrQuoqQhoqKM6opm23bV+j7QdGtQ0VoJYKq6YKq8aK4caK+XtG7kFG7sAEs2OqAtkpcudxol9k+Pzh0uQdv0P0smlvot9/ohqHcuG+SWZZBpBQXx3TLLvT4qmQO5eAYtjZzYKjyqFNl4GYln5NIVgBrHFbvF9W/eJu7Fm0yaks4NWU+88laLFT1T75NqVspakssA6C2EbCI+Oni6ZMzx3UG6U5t+WGH36HRGK94h3zlQWut86tPGoc0XO5MAcAFN70
*/