
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
Oto1Da6TsQ+x09Rhp7vDTpDa0f4Aa1aQn/CcatnWtCJvnGdHW35nRJs41fyW6FADS9QUAtACjoKp+NvpOpNX+gj8uPyb8Sax28+71RPllj/4dfQxz7ep36eJnQ7e6rO3R4u+3PMgrY79tA9TPNpGxJQDH/hb2y0vuZfb2IGOY3GfUrne3Fvdthks+nSrtxXsmtfOsHeypGzm5xfNGjgyzX0s1Xn/lDjsV71T5P57uf8sud7E
*/