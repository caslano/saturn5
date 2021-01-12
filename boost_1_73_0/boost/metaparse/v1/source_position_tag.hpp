#ifndef BOOST_METAPARSE_V1_SOURCE_POSITION_TAG_HPP
#define BOOST_METAPARSE_V1_SOURCE_POSITION_TAG_HPP

//    Copyright Abel Sinkovics (abel@sinkovics.hu) 2013.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/fwd/source_position.hpp>
#include <boost/metaparse/v1/fwd/get_prev_char.hpp>
#include <boost/metaparse/v1/fwd/next_line.hpp>
#include <boost/metaparse/v1/fwd/next_char.hpp>
#include <boost/metaparse/v1/get_col.hpp>
#include <boost/metaparse/v1/get_line.hpp>


#include <boost/mpl/int.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      struct source_position_tag { typedef source_position_tag type; };
      
      template <>
      struct get_col_impl<source_position_tag>
      {
        template <class P>
        struct apply : P::col {};
      };

      template <>
      struct get_line_impl<source_position_tag>
      {
        template <class P>
        struct apply : P::line {};
      };

      
      template <>
      struct get_prev_char_impl<source_position_tag>
      {
        template <class P>
        struct apply : P::prev_char {};
      };
      
      
      template <>
      struct next_char_impl<source_position_tag>
      {
        template <class P, class Ch>
        struct apply :
          source_position<
            typename get_line<P>::type,
            boost::mpl::int_<get_col<P>::type::value + 1>,
            Ch
          >
        {};
      };

      template <>
      struct next_line_impl<source_position_tag>
      {
        template <class P, class Ch>
        struct apply :
          source_position<
            boost::mpl::int_<get_line<P>::type::value + 1>,
            boost::mpl::int_<1>,
            Ch
          >
        {};
      };
    }
  }
}

#endif


/* source_position_tag.hpp
4fB80+QbTksvnNcs86hoXm+Yfkav+G/L2aa73HQ54XdoNG1X09Y00axj49Pmm/ZGa52aWTg8y/Auhq1bwXejiD+rChl+k/ntzat4pWXVl6e2mc0Vq3Uuidt+VhXlb7QfJubvFeYpDbFuKaP9sn6FeJ6X3Mev4QrxPirjfb0Wzt/oou1Sv2C6cZkj43Vgw2/6STkqd6anDTFx4raN0mjhsfzsIy/nVrD+hi/oE+VnvA/sNJux
*/