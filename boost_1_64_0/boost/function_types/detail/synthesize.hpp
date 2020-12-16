
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
l99rk3o0s6yWfEp+6hfxc9CR0pdVzeZmlA02ZvTPpVJmLnwUSH6482VxSMKxlGw4+r+ej/9y+/c+Nyu+KKyfLrVjiHlteeJtH9vnlSsaVQI1PRI19oxIbb20sXmagzjRTOaTIgR96OxRvMWldd3MbWsYA2XGfgYLOakjlC36NB4h9Ddqy0kbb13Cy4NOcOrdte06V+gaOXspvPNY+T5n/edSF5Jz3LOenJY88jnzg2GvPWkxUw53wnTMls5DWnva4yfzV2fUn9pmcyK356a6MGMpnVgN9ea1KXlELUPP4thOVI2xWXcwf+h8FXyJR9juwRfbmydze5JKWGCqSOS/nY8awg1ZzOWFvweRaZ4r1xI4VfZC7kHgt+a3X8QvE/htAmfNWZrfIfCCRfwpgd8lcJkrS/N7BP5+ESdvmSvXEXha7qLxEXj9fP9XF3IHAr8/79/5hTyNwBsIHPIW+UfgjQQekLbIvweE3ykR+MP0Rf4ReDJGGF/qovgT+BmM0H/mQl5G4Gfn19uFpXnKfOXFhfwNgZ8jVHb/hKcSKmsuLc3PY4R4ZS3kDA/nys3z+VOwkGsQeMt8/hUuzR/Mb7+IBxD4w/n8u7Zo/ATeOj+/i/gbAm+bz4+ihZy3da78aH7+FnE9An9M4EbXF/IYAm+f9694af6EwLsX8RoC75j3v2Rp/nQ+PqULObTNlZ/N+1e2kAsTeCeBa9xYmj+f5+ULuSWBv5hffzeX5i8JHCoXrS8C75qPv9vSPHc+fh6L1h+BX52fn5/wvPn16bk0zydwYa9F6/fRXLlgvv9FXJzAC+fj7700vzYfP5+lefF8/vsuih+Bl8zvfxFPIvDS+fzwW5qXzfvnvzS/SeAOAQt5PYFXzOdP4EI+ReCV8/zYovXzeK5cNZ8fxxetHwKvnh/fiYU8lMBfzc9P8KL1TeDdv1jfPb84/vT+Ir/6fnH+fP2L81P//PjyFvlH8H9gPv/zFx0/2+fKg784Prz5xfFhaH7/i/rfReh/dH5+FsU3gMDfzcc/ZNHv75/MlZOJCP0v4kkEfobAjUKX5mcJ/P0i/pDAUwg8Jmxpfo7AhcMXxb9jrpw63/9P+HkCLzi5aH4JPI3AAyKW5ukErhG56PxN4BnzPGppnjnPoxfyAgK/ML//mKX5xXn/YxflF4FfInCZuKV5wh9+n4IBgLBinn29nNCR0f3xvI8CWd/2sCW0o4XC57/8pH7mCBsJY39KwODqrKErTpzCKnhZ10it0o1ChsjLlAXCMZ98qlmH5dNDYQJRfDuGqGjIGDfGo/pOD1Mq6lFrzuZ25y/u6Syeu6jRH5TcNbV1jfX9wuttvJthXt/9//H8stJRTDm5vW7mhWLx+cwbV6KtTp+8ixbpjy83/mJs+HUSiqCVxEVXJmVFdDUUCko7qp+W86yQkOfQQddLKVdWWl+v9hehjbmxm6j2ke4tanYxkYAn1PrMbJXbTEOLP3N8VWV/NdAs75p2kEz5iEJ7YHIQ+ImhBaLL6C57L0X7kk9RX59/54/x/Lj/z9xyyiqTMcOLGcKsLJwvHPNqznVGfy38j2NEv9bi9jNFm4WyeqUGXydFkVj3TQkwMjCn2OGBsjREa8ijNWhDDt7TlYgMF2w9xx9UP/pohH8sJ6SBveokybaowjqWj6xXXeyYt5uczDqbdOCzbPcxbX5xnWUfDlfr8NlIahuIO7lRlG6l79qdwL3J/nBqUvWpUy/4piaYK3nPrPEZ6txMW/y+rIbCqLCF2S/wnJc8s0/MW0pD9BPVmaoFTmwTeKW3btW1XQVZXiMjjFZNd/mcl8oPOUI8H6aGAt/6Mq2EJgt6CZETOWmdR8ox9N/qv+5hBvY=
*/