
// (C) Copyright Tobias Schwinger
//
// Use modification and distribution are subject to the boost Software License,
// Version 1.0. (See http://www.boost.org/LICENSE_1_0.txt).

//------------------------------------------------------------------------------

#ifndef BOOST_FT_DETAIL_SYNTHESIZE_HPP_INCLUDED
#define BOOST_FT_DETAIL_SYNTHESIZE_HPP_INCLUDED

#include <cstddef>

#include <boost/mpl/at.hpp>
#include <boost/mpl/size.hpp>

#include <boost/function_types/config/config.hpp>
#include <boost/function_types/property_tags.hpp>
#include <boost/function_types/detail/cv_traits.hpp>
#include <boost/function_types/detail/retag_default_cc.hpp>

namespace boost { namespace function_types { namespace detail {

template<bits_t Flags, bits_t CCID, std::size_t Size>
struct synthesize_impl_o
{
  template<typename Seq> struct synthesize_impl_i { };
};

template<typename Seq, bits_t Bits>
struct synthesize_impl
  : detail::synthesize_impl_o
    < ::boost::function_types::detail::decode_bits<Bits>::flags
    , ::boost::function_types::detail::decode_bits<Bits>::cc_id
    , ::boost::mpl::size<Seq>::value
    >
    ::template synthesize_impl_i<Seq>
{ };

template<typename Seq, typename Tag>
struct synthesize_func
  : detail::synthesize_impl
    < Seq
    , ::boost::function_types::detail::bits
      < detail::retag_default_cc
        < function_types::tag<nv_dcc_func, Tag> > 
      >::value 
    >
{ };

template<typename Seq, typename Tag>
struct synthesize_mfp
  : detail::synthesize_impl
    < Seq 
    , ::boost::function_types::detail::bits
      < detail::retag_default_cc
        < function_types::tag
          < typename detail::cv_traits< typename mpl::at_c<Seq,1>::type >::tag
          , nv_dcc_mfp, Tag
        > >
      >::value
    >
{ };

template<typename S, typename R = typename mpl::at_c<S,0>::type,
    typename C = typename mpl::at_c<S,1>::type>
struct synthesize_mop
{
  typedef R C::* type;
};

#define BOOST_FT_variations BOOST_FT_function|BOOST_FT_member_pointer
#define BOOST_FT_al_path boost/function_types/detail/synthesize_impl
#include <boost/function_types/detail/pp_loop.hpp>

} } } // namespace ::boost::function_types::detail

#endif


/* synthesize.hpp
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
*/