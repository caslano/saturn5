
// (C) Copyright Tobias Schwinger
//
// Use modification and distribution are subject to the boost Software License,
// Version 1.0. (See http://www.boost.org/LICENSE_1_0.txt).

//------------------------------------------------------------------------------

// no include guards, this file is guarded externally

#ifdef __WAVE__
// this file has been generated from the master.hpp file in the same directory
#   pragma wave option(preserve: 0)
#endif

#if !defined(BOOST_FT_PREPROCESSING_MODE) || defined(BOOST_FT_CONFIG_HPP_INCLUDED)
#   error "this file used with two-pass preprocessing, only"
#endif

#include <boost/preprocessor/slot/slot.hpp>
#include <boost/function_types/detail/encoding/def.hpp>

namespace boost { namespace function_types {

typedef detail::property_tag<BOOST_FT_non_variadic,BOOST_FT_variadic_mask> non_variadic;
typedef detail::property_tag<BOOST_FT_variadic,BOOST_FT_variadic_mask>     variadic;
                                                                       
typedef detail::property_tag<0,BOOST_FT_const>                     non_const;
typedef detail::property_tag<BOOST_FT_const,BOOST_FT_const>        const_qualified;
                                                                       
typedef detail::property_tag<0,BOOST_FT_volatile>                  non_volatile;
typedef detail::property_tag<BOOST_FT_volatile,BOOST_FT_volatile>  volatile_qualified; 

typedef detail::property_tag<BOOST_FT_default_cc,BOOST_FT_cc_mask> default_cc;

#define BOOST_PP_VALUE BOOST_FT_const|BOOST_FT_volatile 
#include BOOST_PP_ASSIGN_SLOT(1)

typedef detail::property_tag<0                , BOOST_PP_SLOT(1)> non_cv;
typedef detail::property_tag<BOOST_FT_const   , BOOST_PP_SLOT(1)> const_non_volatile;
typedef detail::property_tag<BOOST_FT_volatile, BOOST_PP_SLOT(1)> volatile_non_const;
typedef detail::property_tag<BOOST_PP_SLOT(1) , BOOST_PP_SLOT(1)> cv_qualified;

namespace detail {

  typedef constant<BOOST_FT_full_mask> full_mask;

  template <bits_t Flags, bits_t CCID> struct encode_bits_impl
  {
    BOOST_STATIC_CONSTANT( bits_t, value = 
      Flags | (BOOST_FT_default_cc * CCID) << 1 );
  };

  template <bits_t Flags, bits_t CCID, std::size_t Arity> 
  struct encode_charr_impl
  {
    BOOST_STATIC_CONSTANT(std::size_t, value = (std::size_t)(1+
      Flags | (BOOST_FT_default_cc * CCID) << 1 | Arity << BOOST_FT_arity_shift
    ));
  };

  template <bits_t Bits> struct decode_bits
  {
    BOOST_STATIC_CONSTANT(bits_t, flags = Bits & BOOST_FT_flags_mask);

    BOOST_STATIC_CONSTANT(bits_t, cc_id = 
      ( (Bits & BOOST_FT_full_mask) / BOOST_FT_default_cc) >> 1 
    );

    BOOST_STATIC_CONSTANT(bits_t, tag_bits = (Bits & BOOST_FT_full_mask));

    BOOST_STATIC_CONSTANT(std::size_t, arity = (std::size_t)
      (Bits >> BOOST_FT_arity_shift) 
    );
  };

  template <bits_t LHS_bits, bits_t LHS_mask, bits_t RHS_bits, bits_t RHS_mask>
  struct tag_ice
  {
    BOOST_STATIC_CONSTANT(bool, match =
      RHS_bits == (LHS_bits & RHS_mask & (RHS_bits |~BOOST_FT_type_mask))
    );

    BOOST_STATIC_CONSTANT(bits_t, combined_bits = 
      (LHS_bits & ~RHS_mask) | RHS_bits
    );

    BOOST_STATIC_CONSTANT(bits_t, combined_mask =
      LHS_mask | RHS_mask
    );

    BOOST_STATIC_CONSTANT(bits_t, extracted_bits =
      LHS_bits & RHS_mask
    );

  };

#define BOOST_FT_mask BOOST_FT_type_mask
  typedef property_tag<BOOST_FT_callable_builtin,BOOST_FT_mask>            callable_builtin_tag;
  typedef property_tag<BOOST_FT_non_member_callable_builtin,BOOST_FT_mask> nonmember_callable_builtin_tag;
  typedef property_tag<BOOST_FT_function,BOOST_FT_mask>       function_tag;
  typedef property_tag<BOOST_FT_reference,BOOST_FT_mask>      reference_tag;
  typedef property_tag<BOOST_FT_pointer,BOOST_FT_mask>        pointer_tag;
  typedef property_tag<BOOST_FT_member_function_pointer,BOOST_FT_mask> member_function_pointer_tag;
  typedef property_tag<BOOST_FT_member_object_pointer,BOOST_FT_mask> member_object_pointer_tag;
  typedef property_tag<BOOST_FT_member_object_pointer_flags,BOOST_FT_full_mask> member_object_pointer_base;
  typedef property_tag<BOOST_FT_member_pointer,BOOST_FT_mask> member_pointer_tag;
#undef  BOOST_FT_mask 

#define BOOST_PP_VALUE BOOST_FT_function|BOOST_FT_non_variadic|BOOST_FT_default_cc
#include BOOST_PP_ASSIGN_SLOT(1)
#define BOOST_PP_VALUE BOOST_FT_type_mask|BOOST_FT_variadic_mask|BOOST_FT_cc_mask
#include BOOST_PP_ASSIGN_SLOT(2)

  typedef property_tag< BOOST_PP_SLOT(1) , BOOST_PP_SLOT(2) > nv_dcc_func;

#define BOOST_PP_VALUE \
    BOOST_FT_member_function_pointer|BOOST_FT_non_variadic|BOOST_FT_default_cc
#include BOOST_PP_ASSIGN_SLOT(1)

  typedef property_tag< BOOST_PP_SLOT(1) , BOOST_PP_SLOT(2) > nv_dcc_mfp;

} // namespace detail

} } // namespace ::boost::function_types


/* master.hpp
YKER5z+5W9lNH1ekbPKGN09H9nebjGq0kI6YAu3id/Im/3x9CDm5O9Tu1lMEHoS7eRCtSZ+L/tTA05QCE5LGRuE6FSklLc1hyyovrMtD0cp95iFSoE6fqyk0OlrnaI11khhe+ViAwqfc7O05MTdE4btOMU1jtEn8EgR1UU28kHDnsOkWtl3ZIg1nd3o4hIyOcVVK+3phifnm63Olkxnf/VN2uG744C6ct7D+uKSH6/c766gcd3VzvX673g0/kOgG4pd0cearifps6+GSH0G06h3X/Eii5W7Sjye61Q0/hWhFDV9YPy5Q/BvzcPmKu8yO+/+Q9uL5ZZuc148vuslvqerm972K9+Htn8z5ru/DqwJfvC/Py6E+1QKfl7fS5O79Hj0W1/f3tbPcvLyBAl8sb0QN/x9zXvZf/aC/yGIfes6SIS9NmXPhT48/HfvLN4eAgE6WqWFyvpnRfODbCH1BlLhvxAqcUmBKcdsUPJLhiOcHhKXsnO+FG15YoCUnT7/Gy5xmKrRo9cxd535NmzepXucbKJ7zpkZ6NLyiUr7BKs9XHc7LSfJuzBp3rqFIr+MnxexLQTV8M/7YVEGSL9cnf6NJO0mZKhuU63z4J1nc8kMd+fJEfKK8G4dNKTUFbLuOZNQXcD4/C2bUWOjSJhf+bELK5qLsoBMFch+OhgAC35pPn0p25e8+fZp/6kx6pXbUxCKfpZRjmCinA1HRyTXSUzmiFvNMS6G+gIWVaBBE+ntTvqSvzXaQQK7BguxNWpueLQTZr1kyGNmlY0YJ5XHaMkUrMPY9U8L6CdXHSKYi8kl7avsbNTl6o4ObT+zFhDhfHlfk62r5mzR6s2S2n4cV+VQBwd9FxUS+1SokW5vPMII0k/vLflQJJ3/Cj1rpFA0KC+GrGRyXaJVuCjLWS6ZcabJD+bjSiTpq1LgUK9ad+AFRPnIkf6yL8RvOFJukE54q4ttVWD+5EIphpmLQw9pdOXGLOA6LS7xd5XPodOZMXLdyGU9SToryRX0YhX3Nxuq43OScnkN7C3nW5luQLRq12DkIhbMap4RJFpNyylvCSwQQznRYR7LjJ63+CHyG9yRPJ39qFyGWu/OnFMxlOLIdySp3JK74rAz2grrm25Vb5DuuKIrrXpwj2im/d4BqmWU3VHozIG+9VPTexq4lsK9M02My6mR/Nk/KcjjJzc7oyQy2ICm6s6z0ds7BnxWR3C4yEv1JJezlYCy56bJsJl4N7p9TaDBiuTkLSdD2a2UcoNQdvqIbr3Ic42vzrfwNilO6bBOoUzkpHTad5R9V4W66M9LutrIrFgsgSnt6DCudik/hEVWOYxL8kzISE53CARuyaMLKC+yWry9wzVdQR4wu8p2jU/lNVqvb/EU+JSDyXecv8il/sXxci0HYdaDUsq758j5aeeR5K74sllukgxHlrfg8mZuGY3abFXLrcsvhQm8WDmsxU0LD3PMzB4W5y4fsgFrQHd+pBesWjjeB+3C8BW6dHrWA+3DUAm751AJOfAtQTnTTbSoc4+iVKYUif6uVma3WVqRy9i/MIUh0yocOXUCNC2iIQ/4EgU5u5XKT5Jj0uPSsNGwOSRph5xP0CG53McRwrlSzbvMTgOhtzWuw++C24jHsq895bIona7AYL4mNn9AI9UoHcW4nfzbWEuPxdVLW+N1C5OXSwFyLKV+Ks2Csh7dFBRN71Tsfq/W2ymeeFIJo4nq+sr4QOa6jsp6QqdDS8Yy6fyoynPmR95Kb8zWC+4GO9VqvqNQ5hy/NdR3fHK/4lyfXL/16tZsLhYS/fRRFFo8UZAQy6TVmGnvLlM0dRPxwnJOQP41X2KVQVlf+gBfMDVTC+IEGD1z/ark=
*/