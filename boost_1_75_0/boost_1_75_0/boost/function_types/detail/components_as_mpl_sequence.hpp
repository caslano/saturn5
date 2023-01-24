
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
wLo5YbvYQfLQdAMkr7o9b4rxcCJvo8jydGD5K9oJkogKUsnXIZ0BORiZ9ubRHt75LPyWSVkHFo4SZy2FoxBSAAAs/9Ol3oOqOe3bJOPFs3h/T4Jt6V8s25plkY7dHRm62wWpjiTgaAqcIudQmX/Zy59CVm1TAHh9sFe5xFV8xLUqjgRc5aUoRUApOQ8VWs2DlK8QpHwZKOUrlVI+0MedH6vsvy9B49qWycCQZqB17Wa0rj2qW9fe17yNDcTH8yPU3IwVj+rjAKpM/7jmpjR9ADmhLZREXQrqcDBGRZCEjGVdHNI0sFZ0Kbf4iBil8WZHpH1dox0Z1Ex2ZGyvBjpitX+OIzPhvSaSvSkeefxz6JAlOPvtysB1Mz5iDB4bFyQzEwemwXFtbLocUTtlpfOrWWZDGXHSYnUWs/kFQWSHpV5iAb79JTHptXiK/GyeLcRidWc3YlDG96Dr/XzN70FZAD7h94N7oFXqG91wx/F2D8PHTPuDOhAz+CG1lGk4jkvH1rmCcM1FOWBsaEBolGU9HmHjhHykdc1D7E6T1nZqjadRGAM/mvBcGdtGKjkpfC2GVk7TjUrX8SRk0DTf1ZaNSsXX/25GsrFcZZNNhjLYaDu90QJy1xefFQScG5pxo/KTAjb9q8e56r9fqe19WB1mV9rJ8yi+L5HfS3PmAVY4AP1TwD6ehH1o3tde3NtnQYoPMENjWtylGVvxib50
*/