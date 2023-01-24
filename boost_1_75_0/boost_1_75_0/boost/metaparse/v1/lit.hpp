#ifndef BOOST_METAPARSE_V1_LIT_HPP
#define BOOST_METAPARSE_V1_LIT_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2009 - 2010.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/lit_c.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      template <class C>
      struct lit : lit_c<C::type::value> {};
    }
  }
}

#endif


/* lit.hpp
oh572Ch9Hl733FE0l++slmLn84eYi50nGWkg5vrmvLT5ACpt7h/VdD6iwt0KeCPxMj8uSZGA50bV8y8rKcWJVxEH9jFqFK+9rm7Xmj5TrLUImKj14B92pcoVh9bTgE39lp0q+h24MeuPK4b9uhh+BebBwLXosZ9vYTLu/YW6fmQzFPbm4oH2Bv8w5lsL7IA0tYc3GLVvfSQ6C9SYtKHd/Qnq9ZFDXZH+OPX6mKGuGH+Men3Xoa6ueWe79E3phZUxrsKj9oe/ooqrUKE91TAtFh5gqlGUnmvkn/vUQ261AVMDDlGGaKpMYhkxkgwhqcWVHod7O8pNKS/DrDiKoY4FYvScZxOCSDDq6kNk9ErEOJ6SCRSQlaQ9GkHCC21MT1KwKWxygQWEKjg6G2Bmju9EuQdmmr3NWdGd82V4dCuwWUiR96gjmQoxKt8THNnGjrli40E/AW6U/8DXd4IUTg+iAjH5Iosim57iSogHWwxhyyJ1Y5LbrpiYMPWIqwKRKnJkawKHKSl++Se4uLOl2YdnbCyuEoJFcRUt8rerUYZ9nQ6bv8DDsmqTzZ7nO8LyGP+gnCYmXLd4qZI7lzRvZXIHa/aLaRS0RYCpycpgfe5HMEGKf7ZYxbtp1c9RgLUFb/JgVAdB0mu2X8COmHcnDAO+b0KaAaEpM0EjMdlPxNJb+p+C/f/YyGRMJYGL+r8Vdp0vBhNUjbH2GYVHzXpA
*/