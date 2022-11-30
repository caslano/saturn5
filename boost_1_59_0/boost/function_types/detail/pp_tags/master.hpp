
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
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
*/