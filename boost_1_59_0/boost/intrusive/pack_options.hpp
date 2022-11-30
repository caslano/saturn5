/////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga  2013-2013
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/intrusive for documentation.
//
/////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_INTRUSIVE_PACK_OPTIONS_HPP
#define BOOST_INTRUSIVE_PACK_OPTIONS_HPP

#include <boost/intrusive/detail/config_begin.hpp>

#if defined(BOOST_HAS_PRAGMA_ONCE)
#  pragma once
#endif

#include <cstddef>

namespace boost {
namespace intrusive {

#ifndef BOOST_INTRUSIVE_DOXYGEN_INVOKED

#if !defined(BOOST_INTRUSIVE_VARIADIC_TEMPLATES)

template<class Prev, class Next>
struct do_pack
{
   //Use "pack" member template to pack options
   typedef typename Next::template pack<Prev> type;
};

template<class Prev>
struct do_pack<Prev, void>
{
   //Avoid packing "void" to shorten template names
   typedef Prev type;
};

template
   < class DefaultOptions
   , class O1         = void
   , class O2         = void
   , class O3         = void
   , class O4         = void
   , class O5         = void
   , class O6         = void
   , class O7         = void
   , class O8         = void
   , class O9         = void
   , class O10        = void
   , class O11        = void
   >
struct pack_options
{
   // join options
   typedef
      typename do_pack
      <  typename do_pack
         <  typename do_pack
            <  typename do_pack
               <  typename do_pack
                  <  typename do_pack
                     <  typename do_pack
                        <  typename do_pack
                           <  typename do_pack
                              <  typename do_pack
                                 <  typename do_pack
                                    < DefaultOptions
                                    , O1
                                    >::type
                                 , O2
                                 >::type
                              , O3
                              >::type
                           , O4
                           >::type
                        , O5
                        >::type
                     , O6
                     >::type
                  , O7
                  >::type
               , O8
               >::type
            , O9
            >::type
         , O10
         >::type
      , O11
      >::type
   type;
};
#else

//index_tuple
template<std::size_t... Indexes>
struct index_tuple{};

//build_number_seq
template<std::size_t Num, typename Tuple = index_tuple<> >
struct build_number_seq;

template<std::size_t Num, std::size_t... Indexes>
struct build_number_seq<Num, index_tuple<Indexes...> >
   : build_number_seq<Num - 1, index_tuple<Indexes..., sizeof...(Indexes)> >
{};

template<std::size_t... Indexes>
struct build_number_seq<0, index_tuple<Indexes...> >
{  typedef index_tuple<Indexes...> type;  };

template<class ...Types>
struct typelist
{};

//invert_typelist
template<class T>
struct invert_typelist;

template<std::size_t I, typename Tuple>
struct typelist_element;

template<std::size_t I, typename Head, typename... Tail>
struct typelist_element<I, typelist<Head, Tail...> >
{
   typedef typename typelist_element<I-1, typelist<Tail...> >::type type;
};

template<typename Head, typename... Tail>
struct typelist_element<0, typelist<Head, Tail...> >
{
   typedef Head type;
};

template<std::size_t ...Ints, class ...Types>
typelist<typename typelist_element<(sizeof...(Types) - 1) - Ints, typelist<Types...> >::type...>
   inverted_typelist(index_tuple<Ints...>, typelist<Types...>)
{
   return typelist<typename typelist_element<(sizeof...(Types) - 1) - Ints, typelist<Types...> >::type...>();
}

//sizeof_typelist
template<class Typelist>
struct sizeof_typelist;

template<class ...Types>
struct sizeof_typelist< typelist<Types...> >
{
   static const std::size_t value = sizeof...(Types);
};

//invert_typelist_impl
template<class Typelist, class Indexes>
struct invert_typelist_impl;


template<class Typelist, std::size_t ...Ints>
struct invert_typelist_impl< Typelist, index_tuple<Ints...> >
{
   static const std::size_t last_idx = sizeof_typelist<Typelist>::value - 1;
   typedef typelist
      <typename typelist_element<last_idx - Ints, Typelist>::type...> type;
};

template<class Typelist, std::size_t Int>
struct invert_typelist_impl< Typelist, index_tuple<Int> >
{
   typedef Typelist type;
};

template<class Typelist>
struct invert_typelist_impl< Typelist, index_tuple<> >
{
   typedef Typelist type;
};

//invert_typelist
template<class Typelist>
struct invert_typelist;

template<class ...Types>
struct invert_typelist< typelist<Types...> >
{
   typedef typelist<Types...> typelist_t;
   typedef typename build_number_seq<sizeof...(Types)>::type indexes_t;
   typedef typename invert_typelist_impl<typelist_t, indexes_t>::type type;
};

//Do pack
template<class Typelist>
struct do_pack;

template<>
struct do_pack<typelist<> >;

template<class Prev>
struct do_pack<typelist<Prev> >
{
   typedef Prev type;
};

template<class Prev, class Last>
struct do_pack<typelist<Prev, Last> >
{
   typedef typename Prev::template pack<Last> type;
};

template<class ...Others>
struct do_pack<typelist<void, Others...> >
{
   typedef typename do_pack<typelist<Others...> >::type type;
};

template<class Prev, class ...Others>
struct do_pack<typelist<Prev, Others...> >
{
   typedef typename Prev::template pack
      <typename do_pack<typelist<Others...> >::type> type;
};


template<class DefaultOptions, class ...Options>
struct pack_options
{
   typedef typelist<DefaultOptions, Options...> typelist_t;
   typedef typename invert_typelist<typelist_t>::type inverted_typelist;
   typedef typename do_pack<inverted_typelist>::type type;
};

#endif   //!defined(BOOST_INTRUSIVE_VARIADIC_TEMPLATES)

#define BOOST_INTRUSIVE_OPTION_TYPE(OPTION_NAME, TYPE, TYPEDEF_EXPR, TYPEDEF_NAME) \
template< class TYPE> \
struct OPTION_NAME \
{ \
   template<class Base> \
   struct pack : Base \
   { \
      typedef TYPEDEF_EXPR TYPEDEF_NAME; \
   }; \
}; \
//

#define BOOST_INTRUSIVE_OPTION_CONSTANT(OPTION_NAME, TYPE, VALUE, CONSTANT_NAME) \
template< TYPE VALUE> \
struct OPTION_NAME \
{ \
   template<class Base> \
   struct pack : Base \
   { \
      static const TYPE CONSTANT_NAME = VALUE; \
   }; \
}; \
//

#else    //#ifndef BOOST_INTRUSIVE_DOXYGEN_INVOKED

//! This class is a utility that takes:
//!   - a default options class defining initial static constant
//!   and typedefs
//!   - several options defined with BOOST_INTRUSIVE_OPTION_CONSTANT and
//! BOOST_INTRUSIVE_OPTION_TYPE
//!
//! and packs them together in a new type that defines all options as
//! member typedefs or static constant values. Given options of form:
//!
//! \code
//!   BOOST_INTRUSIVE_OPTION_TYPE(my_pointer, VoidPointer, VoidPointer, my_pointer_type)
//!   BOOST_INTRUSIVE_OPTION_CONSTANT(incremental, bool, Enabled, is_incremental)
//! \endcode
//!
//! the following expression
//!
//! \code
//!
//! struct default_options
//! {
//!   typedef long      int_type;
//!   static const int  int_constant = -1;
//! };
//!
//! pack_options< default_options, my_pointer<void*>, incremental<true> >::type
//! \endcode
//!
//! will create a type that will contain the following typedefs/constants
//!
//! \code
//!   struct unspecified_type
//!   {
//!      //Default options
//!      typedef long      int_type;
//!      static const int  int_constant  = -1;
//!
//!      //Packed options (will ovewrite any default option)
//!      typedef void*     my_pointer_type;
//!      static const bool is_incremental = true;
//!   };
//! \endcode
//!
//! If an option is specified in the default options argument and later
//! redefined as an option, the last definition will prevail.
template<class DefaultOptions, class ...Options>
struct pack_options
{
   typedef unspecified_type type;
};

//! Defines an option class of name OPTION_NAME that can be used to specify a type
//! of type TYPE...
//!
//! \code
//! struct OPTION_NAME<class TYPE>
//! {  unspecified_content  };
//! \endcode
//!
//! ...that after being combined with
//! <code>boost::intrusive::pack_options</code>,
//! will typedef TYPE as a typedef of name TYPEDEF_NAME. Example:
//!
//! \code
//!   //[includes and namespaces omitted for brevity]
//!
//!   //This macro will create the following class:
//!   //    template<class VoidPointer>
//!   //    struct my_pointer
//!   //    { unspecified_content };
//!   BOOST_INTRUSIVE_OPTION_TYPE(my_pointer, VoidPointer, boost::remove_pointer<VoidPointer>::type, my_pointer_type)
//!
//!   struct empty_default{};
//!
//!   typedef pack_options< empty_default, typename my_pointer<void*> >::type::my_pointer_type type;
//!
//!   BOOST_STATIC_ASSERT(( boost::is_same<type, void>::value ));
//!
//! \endcode
#define BOOST_INTRUSIVE_OPTION_TYPE(OPTION_NAME, TYPE, TYPEDEF_EXPR, TYPEDEF_NAME)

//! Defines an option class of name OPTION_NAME that can be used to specify a constant
//! of type TYPE with value VALUE...
//!
//! \code
//! struct OPTION_NAME<TYPE VALUE>
//! {  unspecified_content  };
//! \endcode
//!
//! ...that after being combined with
//! <code>boost::intrusive::pack_options</code>,
//! will contain a CONSTANT_NAME static constant of value VALUE. Example:
//!
//! \code
//!   //[includes and namespaces omitted for brevity]
//!
//!   //This macro will create the following class:
//!   //    template<bool Enabled>
//!   //    struct incremental
//!   //    { unspecified_content };
//!   BOOST_INTRUSIVE_OPTION_CONSTANT(incremental, bool, Enabled, is_incremental)
//!
//!   struct empty_default{};
//!
//!   const bool is_incremental = pack_options< empty_default, incremental<true> >::type::is_incremental;
//!
//!   BOOST_STATIC_ASSERT(( is_incremental == true ));
//!
//! \endcode
#define BOOST_INTRUSIVE_OPTION_CONSTANT(OPTION_NAME, TYPE, VALUE, CONSTANT_NAME)

#endif   //#ifndef BOOST_INTRUSIVE_DOXYGEN_INVOKED


}  //namespace intrusive {
}  //namespace boost {

#include <boost/intrusive/detail/config_end.hpp>

#endif   //#ifndef BOOST_INTRUSIVE_PACK_OPTIONS_HPP

/* pack_options.hpp
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
*/