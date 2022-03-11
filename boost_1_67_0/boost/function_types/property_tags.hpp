
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