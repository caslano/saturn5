
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
iC6vC2AeoMWwJlZd3ns2Z+m9FO/N1VBYFNCUd5vew8VlcovDTq4012ayX5Mb+2eJN390kGPnJjY1ZcKvpa3EMv0smhovx0Lvb3iT4ygmXxeYF9UH04tiqfJfPRXLG/k4+Be6/GtFm8ddxfZmXtA51guf7Kt461wOD7V6h5VNWeBOXDgrOlzh0j2GdFPtKhqzY/FfUXMa3gij/5ET0nbzcE5fZ0YV4/7o3D+AtvG/UBhrifyzLfn6eaac5HCa93q7cWDTDN3y4QJql3aDhcUHhNi05eaRunLXNGPYHDDCcKejCGt7STqtToePhi9r436wTXowkpc9ossrBwxs1MPpQ82xy7cazkJTfjn8nPEeHWlQfRHe/Stw568R5AlPGbK+P11WjMeLQxoMfZqPATdO4eEAAy5bdoM3LYpYOcoHH9/UiHsKzaGzbrhsHr2d2mbnZWzIIuZXqGB+ohJeZo2lssIYrFm1mn/cWuNTQHue6HYPPVK1RPHkevp3HCyDjXWY0PajWHuyD3+ZTcbjAC/scN+OoroerNqzF2OPL2li3Tfx2ieBfXTWyewJM9Fzwytp1fUE06Puc+L9f3CfdVyoZffDc7Pboss3e+wvUoaJfQHbzLrGoPL19H60T6y9PI6Tdl7G+8hlWGvtzrzQgXBVvMrHi7ez/eK+cLoXx0c/ImCet4/b6hrQ7KwK2v5OxZ5WEtrZGrR7XAz7IEN2Su+BvWXPxO/Pf1g+oae8mB7Mb48Nxa4ZA6F2sUj2qhmPn56VGKSlyFLvWaL5RGX2XXoLrXwMOGuGKkZbjOVRbQ9O+6HAEr0GsafzE6zzfyq6yW9ssWkj7d+9YEy7W5j7fTKC02bJQT9OIf/1M3rFHEHuYl/ETzLm3RaGmHThJzeqH2W4swlj/A7JUFUn/CezpfWBGKwduE/mXJjOuPfH4d6hir825rHEpAA+RfdwaFIV3vTUkCrzPzEjf4wwXVzHOZpzIS6tRPjsXmLK1dtY++M90qq6MnWxtfiiM42N2zugom49TJel4L82ylg57osIWGUCM93TSHL/jmZDrtNAeTcyd11h8F93uCx4x6LIB03n6csZB8dj/Z5XjPxVjZ0DsuVMHRdu8DpD7Z223Nw9gj9spzPHpYO49FSdv0sD5cK1s5nf5HtUU1Kwb9oFOe+wCl/dOIPllSbU6l3TNNe8eDJwhshJUoJup53SfU0Z7jvt4Lab8QyP/SyuLeyHa2+GS77bhpjXfnJ0dUt8WDKcDe3r0LxPkAjW3oInBiaincs1nH8ZzMWHBvJAgz367nNCn5y+Mjl0NjsH1XBqmA6WaXeRvk1cwSL9I5efLODgUxaMPNeI62rt8OpELM9r1Qnnth0Q+8gHhctvs9b/klik4I7kny5smLqZz6cNEH9nWHJ07UyxdHEdzEJGiW/2BVAxceUZm2lQ2zpYjky6xzTzVEwdk4sLSXkyyUoHO7s+l/sDMqE0bxbiHy3mwIKn4suv4eihVULFjZYoCXCU0T4dOfKPlygfOoanF8SJ94Xl1F63FyNaD2SD+CWWucbCavkyadR8OOcnHxAK6/xZ22Ke8P5rRnnYWkxrp4aR3+YLp+JyfDUcIt32n6ZfrrZor5rGKR2tcL3NYgweGkT16mec9jWIntNyaDbJhfeLGjjgRQ627XvAkeXh4suiLIRP1pIrsjry6oxntHYLQd2Ki+ijZsoOVt4y/tx0Hq3uyMj+8Rjl1w0zUrbzk18wE5+6smb9TZyPe4z8NUPRfcU4xry7KlTWdkJBv3rK4jJei83CtptDsSFvJdcmzaHiUz8x9PwN/jdxuwh5PYxX7XdL/eOToOX7i17ppTTZ0RM7Bp2Ct5upbF0=
*/