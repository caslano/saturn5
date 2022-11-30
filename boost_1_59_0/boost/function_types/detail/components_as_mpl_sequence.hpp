
// (C) Copyright Tobias Schwinger
//
// Use modification and distribution are subject to the boost Software License,
// Version 1.0. (See http://www.boost.org/LICENSE_1_0.txt).

//------------------------------------------------------------------------------

#ifndef BOOST_FT_DETAIL_COMPONENTS_AS_MPL_SEQUENCE_HPP_INCLUDED
#define BOOST_FT_DETAIL_COMPONENTS_AS_MPL_SEQUENCE_HPP_INCLUDED

#include <boost/mpl/size_fwd.hpp>
#include <boost/mpl/empty_fwd.hpp>
#include <boost/mpl/front_fwd.hpp>
#include <boost/mpl/back_fwd.hpp>
#include <boost/mpl/at_fwd.hpp>
#include <boost/mpl/begin_end_fwd.hpp>
#include <boost/mpl/clear_fwd.hpp>
#include <boost/mpl/push_front_fwd.hpp>
#include <boost/mpl/pop_front_fwd.hpp>
#include <boost/mpl/push_back_fwd.hpp>
#include <boost/mpl/pop_back_fwd.hpp>

namespace boost { namespace mpl {

template<> struct size_impl
< function_types::detail::components_mpl_sequence_tag >
{
  template< typename S > struct apply
    : mpl::size <typename S::types>
  { };
};
template<> struct empty_impl
< function_types::detail::components_mpl_sequence_tag >
{
  template< typename S > struct apply
    : mpl::empty <typename S::types>
  { };
};
template<> struct front_impl
< function_types::detail::components_mpl_sequence_tag >
{
  template< typename S > struct apply
    : mpl::front <typename S::types>
  { };
};
template<> struct back_impl
< function_types::detail::components_mpl_sequence_tag >
{
  template< typename S > struct apply
    : mpl::back <typename S::types>
  { };
};
template<> struct at_impl
< function_types::detail::components_mpl_sequence_tag >
{
  template< typename S, typename N > struct apply
    : mpl::at <typename S::types, N >
  { };
};
template<> struct begin_impl
< function_types::detail::components_mpl_sequence_tag >
{
  template< typename S > struct apply
    : mpl::begin <typename S::types>
  { };
};
template<> struct end_impl
< function_types::detail::components_mpl_sequence_tag >
{
  template< typename S > struct apply
    : mpl::end <typename S::types>
  { };
};
template<> struct clear_impl
< function_types::detail::components_mpl_sequence_tag >
{
  template< typename S >
  struct apply
    : S
  {
    typedef apply type;
    typedef typename mpl::clear< typename S::types >::type types;
  };
};
template<>
struct push_front_impl
< function_types::detail::components_mpl_sequence_tag >
{
  template< typename S, typename T >
  struct apply
    : S
  { 
    typedef apply type;
    typedef typename mpl::push_front< typename S::types, T >::type types;
  };
};
template<>
struct pop_front_impl
< function_types::detail::components_mpl_sequence_tag >
{
  template< typename S >
  struct apply
    : S
  {
    typedef apply type;
    typedef typename mpl::pop_front< typename S::types >::type types; 
  };
};
template<>
struct push_back_impl
< function_types::detail::components_mpl_sequence_tag >
{
  template< typename S, typename T >
  struct apply
    : S
  {
    typedef apply type;
    typedef typename mpl::push_back< typename S::types, T >::type types; 
  };
};
template<>
struct pop_back_impl
< function_types::detail::components_mpl_sequence_tag >
{
  template< typename S >
  struct apply
    : S
  {
    typedef apply type;
    typedef typename mpl::pop_back< typename S::types >::type types; 
  };
};

} } // namespace ::boost::mpl

#endif


/* components_as_mpl_sequence.hpp
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
*/