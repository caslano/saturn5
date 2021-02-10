#ifndef BOOST_METAPARSE_V1_CPP11_IMPL_IS_NONE_C_IMPL_HPP
#define BOOST_METAPARSE_V1_CPP11_IMPL_IS_NONE_C_IMPL_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2017.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/mpl/bool.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      namespace impl
      {
        template <char D, char... Cs>
        struct is_none_c_impl;

        template <char D>
        struct is_none_c_impl<D> : boost::mpl::bool_<true> {};

        template <char D, char... Cs>
        struct is_none_c_impl<D, D, Cs...> : boost::mpl::bool_<false> {};

        template <char D, char C, char... Cs>
        struct is_none_c_impl<D, C, Cs...> : is_none_c_impl<D, Cs...> {};
      }
    }
  }
}

#endif


/* is_none_c_impl.hpp
AC1nSlLW8v1grAIAAOgGAAAfAAkAY3VybC1tYXN0ZXIvdGVzdHMvZGF0YS90ZXN0MTMxNVVUBQABtkgkYM1VXU/bMBR9t9T/cFeEkIDglq/SkFbbYAy2sValYy97McltY5HYUeL049/PN15pKRva0CYtD6l8fXLP8TnXamCwMKEosMs24K39jUAroGIBzZNjECqCZuPogAVSjXSXBfc4n+o8KrrscjjsVy+46A2u+72boVuNZIJQZokWEQv4Eh9w18IS3WA+wdwrZIQsyDFL5nY7Eka4rry514T9RgN6H9m5MOjDMC53Yb8NH8qENk6geegftn0LeX89ZK6dX8n2imrBR+Ie2ZlWBpXxPqEam9iHBlUUhkZq5UOY6AKZ1eWYA/5DiRV4lkj6zgkMq4UFuNZdFhuTWfhiCYESKTrpMLg4s761PDPPEEY6TzNdGKnG4IF3AVNpYjBxjljZVOxat9FVcZYlMpQG6Evbk7umEIQ6TW0MjtbnfPPSWn3V9zeJr98bDPkU+VQow5sHzSNioS87E5GUSKstYuq8TvSYk0EE2jMzs7teOCXiTirGMuShM+4JZsse+0HPBnxFCHO0CdkzycIlf4f21FSwew4Jdkuqib7H6BULKlClsL7evd5lUZmmc6BALBNBKZdF
*/