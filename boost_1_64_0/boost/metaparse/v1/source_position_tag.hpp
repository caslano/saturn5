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
jAJRKrYtkW+w6ZzI+iWo5U30P+qEtLs+ZSCPMbeSntY5r40i1lD4wlV4scYxHMdRp6g+6+eYLq2oiGiTocePr549EkMbH5LWTS4eaO9NK12fm/By4Ir5pVqrD7a+IVNkRVc3+197e5yrAojjvJ1wKaibuSpGsN3Wp+n8ZX9xATxKN7W098heilgx4KPl601q53oKcJNmD/xyorJs6OAXQuyDp89/Ag3/XrrorMwjyJ7HqE1RukicYPyKBV7TvCASUgVd+hGXV69nVXF/yf2wIpljTMy4ZxhfyIec51EuSxObW0Obkm9rqeKkdhQ14GhuvGksRoW4WaW1nKV+xcnujHyMvctMC9yNjy3x8Knfe0UKyujixa2ZWyHAuKpqfj+gvl673qCNwGi7KlHQJ8GO7VBzvYHeKb8Kbj4FOwmGnflGg9nrVhXkTwOpm0IvhlTW7kL1ypEkWgUtwkmGMLKZjHrgpxsSy04ETvfblr5QnWvlUQMFbjhtZ6YC4EzJ1n2eGL7mX/Ml2qHhl5RMKFUB6Fi2PDHFvwLbDpCjRpuBksvqc+phJbs/9cfcSQ==
*/