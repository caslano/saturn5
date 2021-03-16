/*=============================================================================
    Copyright (c) 2012 Kohei Takahashi

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_CLEAR_10172012_0100)
#define BOOST_FUSION_CLEAR_10172012_0100

#include <boost/mpl/identity.hpp>
#include <boost/fusion/adapted/boost_tuple/tag_of.hpp>

namespace boost { namespace fusion { namespace detail {

  template <typename Tag>
  struct clear;

  template <>
  struct clear<boost_tuple_tag> : mpl::identity<boost::tuple<> > {};

}}}

#endif

/* clear.hpp
1sjvC+6uPxA8NDogOPXDQcGxoT4U3J6/TDLtSUfcjTOWD2wBsGpgW4C9AixnvGN1hgkV7owttmNZV00rd3yxHcsGmWvLtvex+1RoANATI9z3lJLLEc6gYvTLcjQmsSaZrOSBodhf/C88q6y4qFKHyHPvwiKlpjyZcsgZ27xnuYOEZanYXynNBwk7J05FewiyBCssPOZzbMyRY6tJf7Nzxu1Fi2fWfmsxM2y2eHwsB3Qqp8tLFjPFOL9hCjriiVE=
*/