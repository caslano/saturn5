
// Copyright (C) 2009-2012 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0
// (see accompanying file LICENSE_1_0.txt or a copy at
// http://www.boost.org/LICENSE_1_0.txt)
// Home at http://www.boost.org/libs/local_function

#ifndef BOOST_LOCAL_FUNCTION_AUX_MEMBER_HPP_
#define BOOST_LOCAL_FUNCTION_AUX_MEMBER_HPP_

namespace boost { namespace local_function { namespace aux {

// Metafunctions to manipulate data members.

template<typename T> struct member_type {
    typedef T& reference;
    typedef T* pointer;
};

template<typename T> struct member_type<T*> {
    typedef T*& reference;
    typedef T* pointer;
};

template<typename T> struct member_type<T* const> {
    typedef T* const& reference;
    typedef T* pointer;
};

template<typename T> struct member_type<T const*> {
    typedef T const*& reference;
    typedef T const* pointer;
};

template<typename T> struct member_type<T const* const> {
    typedef T const* const& reference;
    typedef T const* pointer;
};

// NOTE: Do not add specializations for T const[&/*] (ambiguous on VACPP).
template<typename T> T* member_addr(T& data) { return &data; }
template<typename T> T* member_addr(T* data) { return data; }

// NOTE: Do not add specializations for T const[&/*] (ambiguous on VACPP).
template<typename T> T& member_deref(T& data) { return data; }
template<typename T> T& member_deref(T* data) { return *data; }

} } } // namespace

#endif // #include guard


/* member.hpp
8SdK/ElwmYxbvAoXif+L4i/jNjKnhrk3NuM2f4lw53MMjINjYSocB6+DE2A6nAgnwClwKpwKp8E74FJxf0PcV8HxcI2cr4O5cIOcy7iNzBNR82H8xm2+K+t+/zoFK8HvoRHmB9gQnoEp8J+wBfwRtoJREe5y/FdZd7v9CXaGP8MeUMP/NhAJMyV8FgyDw2A4HCnuap4unGhEg3dLvJniL+M2MteBNqr5j9tUIJyajy/jYpVkXCwbNoYj4SUwDl4Gb4R9YB84EPaVfN4s+esHx8L+8Gk4EL4EM+HrcAhcAYfCtXAY3CXpHZD0pN+R+Qb0tzb9js57o0EXjIFlYSyMhFVhOVgNRsMasAJMCaN+GXBbgKxBDiBnkQQG31og6Ug2MhNZjBQiB5AzSJWkSC0F6YIMRaYjBcgaZB9yCompGak1QTojmchUZAGyEtmNlCDRDPAlI52QDGQyMh/x3ZN+ZVaEuS99ErK5e7iWA6cimasjbPep70Lh+u5VP52w1v3qt11dxnbP+m1URAbx7fauPzwiQis8Ee64h/3yiyID2sd+MXkJTyOfyG6u5yiD0/lfhnvtb7/5osgL2uO+CN1rrip9r/v50Lrf/cxREX573i/A7TBl0bkvccjLGSShVqTWGumHTEYWIGuQA8hZJKl2pNYWyUCmIgVIIVKMhDOQWx/phGQi05HFyEbkMBJZl/aAdEaGInnIUmQbchSJrkebQrog2Ug+sgwpQkqQ6Pr4I+lIDpKPLEOKkBIkpgHtFumCZCP5yFJkG3IUiWxI+khnZCgyE3kO2Ygcbhja9z90hI7QETpCR+gIHaEjdISO3/L4D+z/nzlsSNbY3KajBw7/lfv/G3t57zFsDss+cxlhmjrukzlz9yKD1WBdlCb7zHVSacvasWoxhDPWBg+ws/km8Sxrs2R9gt1aEQlrXUs2MtN2jbOvXhV27LDbs+zXhVjDDqom65YkbBVL2Co+YRu716uMzMl2h02whE3wCXurcvDeDyFW+edqkTb2neI86+xUmJqai3/x2GI0xqKM3y6akEjYiLKu6Jiy5pqj4TWUvURlTzFOwk7EozFho2NbK3ePjgLcLzbcK+rRYcQphw6jPp/xxOfcqOpkwjRCLqka+P51Rp1XlTqXtS6yHk3Vrax1kfUgUofmujXDTeoKN1X+1Il1LZQqF6Psq0rZG+vbOqly4reHBj77IcuCq/rSXushs7gXlvm212uGjRqALqmrUu0ULrNrh052qG3boV2blbA2bcGzpn6z8i8v9a3qhDo//xozT71wXbbrCa11EO1TB9Y9LNPKyviszJvNkbIsti3L/lmk412elmv5XMUZYb8PSBDlW2xfvubapqprDf8k+31BnMpb7r1EFfdyzXMvvBDnvh9ejQn8XriQMjfac6W1Mg+nmfu8mZy/0My7fTeJ8F8DtrgudbPWp06uY6WfFlj7Jq5Nf2hf/hLW2gfRX5zf7pBj+Vjvd5/2t0D2ZF8k9ikXwntpfwV216qan9/1mus9n1FxHtfHcMWFpHKfHmFvk9S+LMy166uUf3u9Gzmepj0l66NZCfqW2hNSj2GW1g4evvX1SLvyQ7/t88S0c/al8v8RDVXVj/bTtZHi50njT+zqlK7SuMTOZosljXJyDYzMm8+XPykdzVn3GlZq3sudu0fM9X+x6wiHf5zYCYtX8WrphgWFVNpDeWPujGE/kjQXIMag/V7O9yH8rdw/iXc/c/pUO79NwXjs/JxRaWhjRwzL6Z87Wq1fDbgtyb3m9+xos87+3tpXTn4vQTycYTw71vm0t945POyybPs6Q9FyFT7crn2JLt33XcmurRDW9l3Jts4l7HnXZjqWnc1zPNo=
*/