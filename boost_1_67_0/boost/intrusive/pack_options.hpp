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
template<int... Indexes>
struct index_tuple{};

//build_number_seq
template<std::size_t Num, typename Tuple = index_tuple<> >
struct build_number_seq;

template<std::size_t Num, int... Indexes>
struct build_number_seq<Num, index_tuple<Indexes...> >
   : build_number_seq<Num - 1, index_tuple<Indexes..., sizeof...(Indexes)> >
{};

template<int... Indexes>
struct build_number_seq<0, index_tuple<Indexes...> >
{  typedef index_tuple<Indexes...> type;  };

template<class ...Types>
struct typelist
{};

//invert_typelist
template<class T>
struct invert_typelist;

template<int I, typename Tuple>
struct typelist_element;

template<int I, typename Head, typename... Tail>
struct typelist_element<I, typelist<Head, Tail...> >
{
   typedef typename typelist_element<I-1, typelist<Tail...> >::type type;
};

template<typename Head, typename... Tail>
struct typelist_element<0, typelist<Head, Tail...> >
{
   typedef Head type;
};

template<int ...Ints, class ...Types>
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


template<class Typelist, int ...Ints>
struct invert_typelist_impl< Typelist, index_tuple<Ints...> >
{
   static const std::size_t last_idx = sizeof_typelist<Typelist>::value - 1;
   typedef typelist
      <typename typelist_element<last_idx - Ints, Typelist>::type...> type;
};

template<class Typelist, int Int>
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