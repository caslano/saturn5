
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