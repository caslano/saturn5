/* Copyright 2003-2017 Joaquin M Lopez Munoz.
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * See http://www.boost.org/libs/multi_index for library home page.
 */

#ifndef BOOST_MULTI_INDEX_DETAIL_PROMOTES_ARG_HPP
#define BOOST_MULTI_INDEX_DETAIL_PROMOTES_ARG_HPP

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/config.hpp> /* keep it first to prevent nasty warns in MSVC */
#include <boost/detail/workaround.hpp>

/* Metafunctions to check if f(arg1,arg2) promotes either arg1 to the type of
 * arg2 or viceversa. By default, (i.e. if it cannot be determined), no
 * promotion is assumed.
 */

#if BOOST_WORKAROUND(BOOST_MSVC,<1400)

namespace boost{

namespace multi_index{

namespace detail{

template<typename F,typename Arg1,typename Arg2>
struct promotes_1st_arg:mpl::false_{};

template<typename F,typename Arg1,typename Arg2>
struct promotes_2nd_arg:mpl::false_{};

} /* namespace multi_index::detail */

} /* namespace multi_index */

} /* namespace boost */

#else

#include <boost/mpl/and.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/mpl/not.hpp>
#include <boost/multi_index/detail/is_transparent.hpp>
#include <boost/type_traits/is_convertible.hpp>

namespace boost{

namespace multi_index{

namespace detail{
  
template<typename F,typename Arg1,typename Arg2>
struct promotes_1st_arg:
  mpl::and_<
    mpl::not_<is_transparent<F,Arg1,Arg2> >,
    is_convertible<const Arg1,Arg2>,
    is_transparent<F,Arg2,Arg2>
  >
{};

template<typename F,typename Arg1,typename Arg2>
struct promotes_2nd_arg:
  mpl::and_<
    mpl::not_<is_transparent<F,Arg1,Arg2> >,
    is_convertible<const Arg2,Arg1>,
    is_transparent<F,Arg1,Arg1>
  >
{};

} /* namespace multi_index::detail */

} /* namespace multi_index */

} /* namespace boost */

#endif
#endif

/* promotes_arg.hpp
rMPX341rBmX58n6iBtHkWtD/G/7gsRk3JgoNf6SXwThYDvOAyevDoD/qMPj3M4IpFVHS//4tfzBq9RLYePmJWqEnbE4Q+g/ZgK4/WmSzLN68N30iiuwB+3eIP2jS9NCdsAKiK0HbVOj/lR8gxjKKCuZ5sTIHmcqXa8EjUSQW3v9hzS+0NO8zoeEpWh4FygbuYpmLrj+fpDiwUoYoEpQxcE0UOQwcHNFyb5+ouVpoeZqW1oN5EIyByfPQOcjJ7oCUPctUvlwPz40iFhgDtdzTy4qGQB65n+n7UdAbqgv9SSm+/lhhjLJ489mG16NIP8gh9x1/sGB1jEegZ2hSIN80jAFl+Po7ijwdMAmQ5cs5sD+KvAbvX/N7ba/VbqjQ8Bd6oCb4huuJuK2ldBb2GOAoQl0Ki+KVMcAfJX3j3yu+8V9pX5NvPBfVN65VENEtLos3+QNdUWRwlND/uJYn4Kc7ugj0rNxTrAB/mGcBevu3O5Gi+WXxl3yvfyV93xCXU0+zA4fw9UcKWZSlKzE5eVFkArT9k/xB0UPRcHf1OToF3v0QC/iBFuLrjnYXk6l8afsyo8iDoP8P/MHaJjtPCg1/o2ujYf0P85+iRej6o+XMk8Wbxz5blDzT9iN/0H6nZ7ZAf6dTwA+q3clm1ewEZu5QqKC7ANcBAgJUDoboHPyk3cFT570NAj1PY2Mgfh3usC/HbwOZLieuMxQEqH6QI5GkB+yJVPAH8xqdhhyyf9DpoPL0moKD0sXoHNiwEsjK4s1xE+WRZAe0gVP8wZqbtsM6+E+6NgL8QDAHHLcEX3+so0yyePMc4OtIeb/Aac0OzhqwGEZGOjWQP9UC97FZMOeALlueo0Nafrr4AemAp1mKujfylc7FzwoXhJm5GBIRPi6wXCMmKQoXpFskmQNcnOEPojatAv8AZfHgH+sdTcRddhsw98pFLcPRKi7aJhpEkMXAwy/8wW3zI5+BJsEGAg8ZwENR2HjAbREXaw+ptSNILvDwq+YrOLguFwK32XnwFSRDPNUxVDvp5H99PF+FG+vySkWC0hbiI4gVODjLH6yc/fNTQssIdjgi4DOEfGIfhoGDgkKsrGqKBOUsQ2QEOQMcaHfvpJT1vxGCp1j3ahDBHSM4WBoODvIdWDMGXcAlrxuj2CL4qSET+bOmo64bRRXxMs0qAtR5Y6WFPAHt4Df+4LUGh8eB05hthLlziZWI/ClLw8BBttOFtYlsliD3kE5ZZI6c3/mDhZ98fiKQCcIq95AEBxVh4QBr8qiWL+MJyy1kPeh/nj/4ImbYLULDGJZRE3LPxwr9hywLg/72HK8N2RqACDWucpeFvAQ8/MEfHNzRIkWg1VhGdbCJwMPacPDAF7tYeylmCXIvZbFF5qD9kz9obBu5BxJsssN1oC3UEhwkLQ8DB5lYSXIUAWqs9RsWMgo4uKDdRfLCkiYCjWUNq8G4ECc4mBoODmxZWLe1mSXoHBRbyEPAgeY7dd3xVl2hZRy7tXpg3SA4qETnwOlOxzsKrkhQclE/ZZE+Bco5aNx4LNxvXYMdhjw58XUEBxkrwsAB3u66IkCJr5pikXsrjBn3Vmoy87mDYtS9FVFFxN0VRYDiX5xkIUPh7LdFmw/OHPc2vH0WYYE5EtxNlLwyDO0A6zCfLN+0ZpxoIS5oAxFc/3un5MBJpFqsCHzMuZFC/+no+mdjL5dAgCnO6mGLXC9Fcg4O2Ce1EGhtdgA48MAckawKAwe44yIIMOXZ9VvIFRBrE8U5mH/6MChah02OBh9rINbsQ8yzN6KKrsxCpKzLigCFA5JlIT3Bzx7NP8+1HAuzorrsJHBQFBtYL+FzwGuIywEIUGLOhlnIL9AXtFw=
*/