
// (C) Copyright Tobias Schwinger
//
// Use modification and distribution are subject to the boost Software License,
// Version 1.0. (See http://www.boost.org/LICENSE_1_0.txt).

//------------------------------------------------------------------------------

#ifndef BOOST_FT_DETAIL_TAGS_HPP_INCLUDED
#define BOOST_FT_DETAIL_TAGS_HPP_INCLUDED

#include <cstddef>

#include <boost/type_traits/integral_constant.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/mpl/bitxor.hpp>


namespace boost { namespace function_types { 

namespace detail 
{
  typedef long bits_t;

  template<bits_t Value> struct constant 
    : boost::integral_constant<bits_t,Value> 
  { };

  template<bits_t Bits, bits_t Mask> struct property_tag 
  {
    typedef constant<Bits> bits;
    typedef constant<Mask> mask;
  };

  template<typename T> struct bits : T::bits { };
  template<typename T> struct mask : T::mask { };

  // forward declaration, defined in pp_tags
  template<bits_t Bits, bits_t CCID> struct encode_bits_impl; 

  // forward declaration, defined in pp_tags
  template<bits_t LHS_bits, bits_t LHS_mask, 
           bits_t RHS_bits, bits_t RHS_mask> 
  struct tag_ice;
 
  // forward declaration, defined in retag_default_cc 
  template<class Tag, class RegTag = Tag> struct retag_default_cc; 
 
  template<bits_t Bits, bits_t CCID> struct encode_bits
    : constant< 
        ::boost::function_types::detail::encode_bits_impl<Bits,CCID>::value 
      >
  { };

  template<class LHS, class RHS> struct compound_tag
  {
    typedef constant<
      ::boost::function_types::detail::tag_ice
        < ::boost::function_types::detail::bits<LHS>::value
        , ::boost::function_types::detail::mask<LHS>::value
        , ::boost::function_types::detail::bits<RHS>::value
        , ::boost::function_types::detail::mask<RHS>::value
        >::combined_bits 
    > bits;

    typedef constant< 
      ::boost::function_types::detail::tag_ice
        < ::boost::function_types::detail::bits<LHS>::value
        , ::boost::function_types::detail::mask<LHS>::value
        , ::boost::function_types::detail::bits<RHS>::value
        , ::boost::function_types::detail::mask<RHS>::value
        >::combined_mask 
    > mask; 
  };

  template <class Base, class PropOld, class PropNew>
  struct changed_tag
    : Base
  {
    typedef mpl::bitxor_
        <typename Base::bits, typename PropOld::bits, typename PropNew::bits>
    bits;
  };

  template<class Tag, class QueryTag> struct represents_impl
    : boost::integral_constant<bool,
        ::boost::function_types::detail::tag_ice
          < ::boost::function_types::detail::bits<Tag>::value
          , ::boost::function_types::detail::mask<Tag>::value
          , ::boost::function_types::detail::bits<QueryTag>::value
          , ::boost::function_types::detail::mask<QueryTag>::value
          >::match
      >
  { };

} // namespace detail

typedef detail::property_tag<0,0> null_tag;

template<class Tag1, class Tag2, class Tag3 = null_tag, class Tag4 = null_tag>
struct tag
  : detail::compound_tag< detail::compound_tag<Tag1,Tag2>, 
        detail::compound_tag<Tag3,Tag4> >
{ };

template<class Tag1, class Tag2, class Tag3> struct tag<Tag1,Tag2,Tag3,null_tag>
  : detail::compound_tag<detail::compound_tag<Tag1,Tag2>,Tag3>
{ };
template<class Tag1, class Tag2> struct tag<Tag1,Tag2,null_tag,null_tag>
  : detail::compound_tag<Tag1,Tag2>
{ };
template<class Tag1> struct tag<Tag1,null_tag,null_tag,null_tag>
  : Tag1
{ };


template<class Tag, class QueryTag> struct represents
  : detail::represents_impl<Tag, detail::retag_default_cc<QueryTag,Tag> >
{ };


template<class Tag, class QueryTag> struct extract
{ 
  typedef detail::constant<
    ::boost::function_types::detail::tag_ice
      < ::boost::function_types::detail::bits<Tag>::value
      , ::boost::function_types::detail::mask<Tag>::value
      , ::boost::function_types::detail::bits<QueryTag>::value
      , ::boost::function_types::detail::mask<QueryTag>::value
      >::extracted_bits 
  > bits;

  typedef detail::constant< 
    ::boost::function_types::detail::mask<QueryTag>::value
  > mask; 
};

/*

  The following is a metafunction which checks whether a
  property tag is in a possibly compounded tag type.
  
  Here both the possibly compounded tag type and a property tag
  is given.
  
*/

template<class Tag, class PropertyTag> struct has_property_tag
  : detail::represents_impl<Tag,  PropertyTag>
{ };

} } // namespace ::boost::function_types

#include <boost/function_types/detail/pp_tags/preprocessed.hpp>

namespace boost { namespace function_types {
#define BOOST_FT_cc_file <boost/function_types/detail/pp_tags/cc_tag.hpp>
#include <boost/function_types/detail/pp_loop.hpp>

/*

  The following are metafunctions which check whether the
  specific property tag is in a possibly compounded tag type.
  Here only the possibly compounded tag type is given.
  
*/

template<class Tag> struct has_property_tag<Tag,null_tag>
  : ::boost::is_same<Tag, null_tag>
{ };

template<class Tag> struct has_variadic_property_tag
  : has_property_tag<Tag,  variadic>
{ };

template<class Tag> struct has_default_cc_property_tag
  : has_property_tag<Tag,  default_cc>
{ };

template<class Tag> struct has_const_property_tag
  : has_property_tag<Tag,  const_qualified>
{ };

template<class Tag> struct has_volatile_property_tag
  : has_property_tag<Tag,  volatile_qualified>
{ };

template<class Tag> struct has_cv_property_tag
  : has_property_tag<Tag,  cv_qualified>
{ };

template<class Tag> struct has_null_property_tag
  : has_property_tag<Tag,  null_tag>
{ };

} } // namespace boost::function_types

#endif


/* property_tags.hpp
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
*/