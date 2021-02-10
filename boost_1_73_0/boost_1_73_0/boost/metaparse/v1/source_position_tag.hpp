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
8lgj2ktXkm0q6Ugq6aSoyPDPFkySZZXDc3AAHm6yWyKZVSUBReleWof0qAbV5EqmQppXN8paR7ooSBQOpq6UlkStW+V3yd8wuP7+fP/v+uHq/v755p/1zeOXP+Pp5z7RIc4i03UtVD7cIImi09vVOr17Sk597k+r5zSaxNOz2fnFp/n7Aosons5nFN7SyVWt1ZY0SmKoaTeVzGjTyiqXamtRZRKUsXECK6f3akz7UmYlFdqglKpD/YXVCpYO3VFVtGFqTJuj52CP08J418Lommpsot0BPCbUyp8PYHeDq7BWbhUpjd6AMGDbWvINNfYNY5jQF1oxfDPf01VHvuraJ0a1tq5P0I5pi5zQOoZsLQDrw0iHkITp8lIClC/7+P5KvteO27QXljbaqEvEgX0uut4QLcjHVBVzjhwRzWjQxVR3lqtiuG2DyGMAC1u3sBY9L5lQnhb0Mq7WaNzSu2VgzWtHZex9vSSQd85mfEzMOrHt/fzhprVSsYU0HPlr8Q4c2Mv+TDquvV2tUSmos0O2mCg9eZ61BnWQvzg/BPKzZMDFYVaKxvmJeB7HJ9DUUUpYvg6Pfqz8YCOLrtfjUancj1EqPW/Mik5sqR1Adr0tIBqjnc50tQz8/HgX4f+I8PASGwW3aOKEfhtdo+A7
*/