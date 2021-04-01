//
// Copyright (c) 2016-2019 Vinnie Falco (vinnie dot falco at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/boostorg/beast
//

#ifndef BOOST_BEAST_DETAIL_ALLOCATOR_HPP
#define BOOST_BEAST_DETAIL_ALLOCATOR_HPP

#include <boost/config.hpp>
#ifdef BOOST_NO_CXX11_ALLOCATOR
#include <boost/container/allocator_traits.hpp>
#else
#include <memory>
#endif

namespace boost {
namespace beast {
namespace detail {

// This is a workaround for allocator_traits
// implementations which falsely claim C++11
// compatibility.

#ifdef BOOST_NO_CXX11_ALLOCATOR
template<class Alloc>
using allocator_traits = boost::container::allocator_traits<Alloc>;

#else
template<class Alloc>
using allocator_traits = std::allocator_traits<Alloc>;

#endif

} // detail
} // beast
} // boost

#endif

/* allocator.hpp
NY7V3phfkGgBuYC+IoWVX6BLVvWxncQPRNGEgw5eQFmNB15mY9IeBHpRXF9uvaI+Qs8F3/WeP9drEh4OmXPMnmnlGYyT76XElqUX1THtQKHgochE4y4fl/ZSstESEHGWTXgQz6NyBH7KajGwUS7j7w2+gdqjMAncgByF1pSDViBHdG/7Sr6S1V0vqyfO86pVzupqA+vseQZOHM5wVb35M4ZPKdodDCqg1ZcHviI9JNm/gLditCgZs76rr2QkVsF4ZLTyFmshjIkOjAFSKZgXo7qc4Goa4mWQBbo53g1Mqx6PUfZZ1mbtuHisCwpbcLwCsPflPVAd8XL6oO6D8BYJGeK8QF5eupY6s5XpidUtx+3E5fczlY4Hulj+POuetvpa57u2eRmv7iu+5dz1m0hDTJzlkN1EMXLhiCTP9GAB4FKRSXwJOINzwUfpTlJNoL+YFg+l5bQ9KjneTG5gkvGH9BvzqfkJ6I8SSODw24GDBbQefGL2BDFclqmx7oYy91RZM+56htG3ReAxPS3gkQCBKVgzyOxaecDNr4u+69qvoljrcjKl6l/SZ0R0gQ==
*/