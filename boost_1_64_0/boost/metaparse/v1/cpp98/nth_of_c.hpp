#ifndef BOOST_METAPARSE_V1_CPP98_NTH_OF_C_HPP
#define BOOST_METAPARSE_V1_CPP98_NTH_OF_C_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2013.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/cpp98/impl/nth_of_c.hpp>
#include <boost/metaparse/limit_sequence_size.hpp>

#include <boost/preprocessor/repetition/repeat.hpp>
#include <boost/preprocessor/repetition/enum.hpp>
#include <boost/preprocessor/punctuation/comma_if.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/preprocessor/repetition/enum_params_with_a_default.hpp>
#include <boost/preprocessor/arithmetic/sub.hpp>
#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/tuple/eat.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      template <
        int N,
        BOOST_PP_ENUM_PARAMS_WITH_A_DEFAULT(
          BOOST_METAPARSE_LIMIT_SEQUENCE_SIZE,
          class P,
          boost::mpl::na
        )
      >
      struct nth_of_c;

      #ifdef BOOST_METAPARSE_NTH_OF_N
      #  error BOOST_METAPARSE_NTH_OF_N already defined
      #endif
      #define BOOST_METAPARSE_NTH_OF_N(z, n, unused) \
        template <int K BOOST_PP_COMMA_IF(n) BOOST_PP_ENUM_PARAMS(n, class P)> \
        struct nth_of_c< \
          K, \
          BOOST_PP_ENUM_PARAMS(n, P) \
          BOOST_PP_COMMA_IF(n) \
          BOOST_PP_ENUM( \
            BOOST_PP_SUB(BOOST_METAPARSE_LIMIT_SEQUENCE_SIZE, n), \
            boost::mpl::na BOOST_PP_TUPLE_EAT(3), \
            ~ \
          ) \
        > : \
          impl::BOOST_PP_CAT(nth_of_c, n)< \
            K BOOST_PP_COMMA_IF(n) \
            BOOST_PP_ENUM_PARAMS(n, P) \
          > \
        {};
      
      BOOST_PP_REPEAT(
        BOOST_METAPARSE_LIMIT_SEQUENCE_SIZE,
        BOOST_METAPARSE_NTH_OF_N,
        ~
      )
      
      #undef BOOST_METAPARSE_NTH_OF_N
    }
  }
}

#endif


/* nth_of_c.hpp
W75iAn/xCTwa4/mnXeacMKO2Pd0L7tkMu8fPeu4zmumaGYd+vZPE/XLg0p/wLC6pvMts+As93gSv1YDRGQJ+xjHg7z7JNW2er5HZnBh/3UhfJ8Flam1PDL1bjl4a5tnkxzSDunp5ES/jjBaeE7qEB57m8zzS1/r0mXP73vaQUP/kodnSw4x6vLOc9oRzgfLqjCa+Q7M8U2/hh/BzdTqe/t2Ho/LtkCN5zXDbGREvO8P7546hRfjSnLznGGfUTdaIq/4eNsnMx5zmfV7+QJw7q8fqKe016Jdp+c0V5ATOvJPHGPxDRzy1lWaMsRymDeAH28NyuRrZAXctpGHx9PgpZm7B/bfgcZwB5w/+DYUZ+n6Cvanp0nXFSu8nqQWvoqtnfJbY7KvQBHM5M9nqZoH14WBDOiVN1//hrr+1SkPj4w767Q28eloRP2bjGbLKofW3uInrxsES/basszprEjBPU991xD3MDEg9fm9W0z0R7+A9jb6hN0/huGI0VFdzDvPoqyn0Eu30udfsLuZsXmxnHub9buu1j7zXEXUpHiNhcT1rrGJfPc1R++RXU9awF3783p6fjdCDbQK8fQitw1N5T/VcZgb6rZDab3LYPzj0XUEaDa7UUQvL3L9qWzW6WIyrmvfquYRivWqEmsWT14uaDz62dhp7xkLY8SV9FYDL5unpe8hJBXvaB4teqQ31kUq87+fzvTJ6Z4Y5xEjnzGI3oxL+oMm7dDSjnuvZk1LieImv/Q0vwqbEEXpZzV4IoTvoNXEPRPSDjWbuk7P62JFGhD3F2uI186tn6isSJn9Gd/yQIMwzWrBVPEIbywndMS6E5uUv4qeUKziX/BNrHYW3xCX0RfCZbev4i0Yx895LW/9aV06s+/AR2o0HGFMepnjOpyF+zNzbWt7RBfX1l3nkIbmKXgOPylfCrHCe3ou87tn+GeLqOfFyZmA746p9vFjjHG6Agfvh1ydivks+DzUIw0eeKwkzs1In6bwn5Rv18zsfj59nPVc/8GDfKFp8vDUWCtBDZjI19FleHE2LhQbwPA7ptow2XwEPxL+QWFXXu69gw4FwfBGVvtLrj5wr+NvR9Ie5G1+a2/57beGfd9IZNMEX+PFkE3quhXmfPA8M47/GwG76Yx5NVrEvP7/ILAnv/viYToqjFo/A1oS8QSWcwet8qO9Z2y/g0Ldmsg+dh9C15fHJqdi8K2z/awA+yU73eLBp6mUzInxXsrdZiu+nW2jWnYQuSgSjtprt0Ht5YVjkW+sKmMFHoZG7qE91H2WN+XgG6/iTJlAPN9V7ilU+byNXvEf755491cuzg74l3DNg+HkGDdp2Gx7yHFDPo2KUgFbIbPZRQq3QO6f1YUQBWrszbVXFfC+xWhkIL87TBWp7wnI8RG81PICzE8InfHE/eJYkDyfhcmua8y1cbtfOHnvLRz5c04jPG6Km5KYr/ZQgE0yJoKHpgdNiNQE398vmY4heVZudmzrPiaSnU3r/UvOPP2BvT3utoK/gfYg6Sv69WaD3j9YPy8TrPh6vdtiZakq9X8gsfRjM/qDu8/PlaqFvcz3ha9XNDsLMAptu0pN/6DsaqFkrM4zfXFeckuiVSa2t4wodvTLEOYMaUtfP+f1icHKCOo0mpo08bzLcfZfM4sPVy3o8f0td7B0Go2Pya3d51wAtAz+u0ZdN9OWaLThtN3zDCXP1+AA92zv4vtR0FC9ylW8/31Kdn8Pb08wo5GMT3rz2lK4+IiawOfoJMw66v+4ydQyfY9MHSc7TVWZIC3F1poZigvPvJhWDffpW7PPx3R2G49YSegyHtflO323AN/vUYkHPTbjO6g0wUIwjN/Gj45zV1qFBcEojeFE=
*/