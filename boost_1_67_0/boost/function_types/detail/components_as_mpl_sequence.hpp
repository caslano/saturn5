
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