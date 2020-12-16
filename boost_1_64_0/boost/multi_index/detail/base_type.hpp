/* Copyright 2003-2013 Joaquin M Lopez Munoz.
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * See http://www.boost.org/libs/multi_index for library home page.
 */

#ifndef BOOST_MULTI_INDEX_DETAIL_BASE_TYPE_HPP
#define BOOST_MULTI_INDEX_DETAIL_BASE_TYPE_HPP

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/config.hpp> /* keep it first to prevent nasty warns in MSVC */
#include <boost/detail/workaround.hpp>
#include <boost/mpl/at.hpp>
#include <boost/mpl/apply.hpp>
#include <boost/mpl/size.hpp>
#include <boost/multi_index/detail/index_base.hpp>
#include <boost/multi_index/detail/is_index_list.hpp>
#include <boost/static_assert.hpp>

namespace boost{

namespace multi_index{

namespace detail{

/* MPL machinery to construct a linear hierarchy of indices out of
 * a index list.
 */

struct index_applier
{
  template<typename IndexSpecifierMeta,typename SuperMeta>
  struct apply
  {
    typedef typename IndexSpecifierMeta::type            index_specifier;
    typedef typename index_specifier::
      BOOST_NESTED_TEMPLATE index_class<SuperMeta>::type type;
  }; 
};

template<int N,typename Value,typename IndexSpecifierList,typename Allocator>
struct nth_layer
{
  BOOST_STATIC_CONSTANT(int,length=mpl::size<IndexSpecifierList>::value);

  typedef typename  mpl::eval_if_c<
    N==length,
    mpl::identity<index_base<Value,IndexSpecifierList,Allocator> >,
    mpl::apply2<
      index_applier,
      mpl::at_c<IndexSpecifierList,N>,
      nth_layer<N+1,Value,IndexSpecifierList,Allocator>
    >
  >::type type;
};

template<typename Value,typename IndexSpecifierList,typename Allocator>
struct multi_index_base_type:nth_layer<0,Value,IndexSpecifierList,Allocator>
{
  BOOST_STATIC_ASSERT(detail::is_index_list<IndexSpecifierList>::value);
};

} /* namespace multi_index::detail */

} /* namespace multi_index */

} /* namespace boost */

#endif

/* base_type.hpp
0kcgHnr/IU6Kwo4KFQ8sAuEOxNIKVCj330nlSlEmrp/avivgJpwUhGukbbxmRNrvLEsvEH4YJEnm52JrHW6mgCdF8IO5bvSyBfSlfNZo/zJ3w7J0mXylbTT7aVu331dYHJ6wEz/y8yBgcZxstzuytz+lzfvPD4z0o8z1oqBwmKzuxNuk33gVnxtC18+cOGJRrMs5cLWF3R/9dO9nsp4IyyS0LYvJbrblcINOVPsU13U/yWQDkZWe5QWOyvtTWiurVQwrHTkRt9ZWcOzhWiil8gWYE4Z2EkK1wYJmRdbW03U3aen8Pt4oa+xkiZ9miRQ6uS532zI99QHCWYj43e4Z+S3jMk5UVXe3OtA3ZWo8u3z9eobJuyKys9QOyoJHUOmAdFltbWPDZOEOe5LmWZJx2Y683CzvQ6zyLNi6n7E4QhEnZe4EXiBgFYBt1VqsZ7ppOewG9hE/oXGkwvP81AlDS8A1ZvB+p/dQcI53q4fI+W036GRlTMRpp36z8NYS339jxNFxJ9W5Xm5IfBT9dkoiOu7Esf/Gl7J1ZBaFZewLlXs/lZYDvsyTnz/iQY+Y5nPGu6hcKvzIzTI3t4UvtRqSexT4jt99xJG6Fh6rfT5QOTsWdgnu/71YVIs2JwKxxUdMwv+tbsnfmMQmm0Zy3FxxMOqRWK8rWNyuiJ2yyNxri7mOzNX5vMTiSoQfOKnl207V3v8wumEZHcG3t17Gx32SJGGWFdY1xq3LfXc9tg7S+HJRemVse1khYHMGsW0TwSNwjfIyY1/sBE7h+LC2wAiuko8jOp7UiKewQjlInEjAwvoa4tHleSKLxxZeGhexZ0eqJfWqoJJexdol8j2QZ77ZC88J06Ku3+EREPnTRvp5VqZ+ENX1sX36D9HrIVPeLqPciaE9thXHNZEhW/qBFTlOrOrwKmkf077eqbwjy16mVuEHqVDLGa1Eq6ofp201YU9jx4MGAn0G+geE/aDScy7KrdIJVMXRe8qn6XjJhJvnVmZbgchvSFM5GlZW9QKC3Dl/PMignQKsNpbYXdYdKs0lhVA/FgdHAFN8rhYkZ+hfJBzzblNnFDGlhaXYtwhWnWCQuxNjiLH7TF8h4eZ9JnccMbUvpdhFgunDSF/vv1/Kv1lOFJZFmcCacP0RR5XPDrXqh/sUoNHGOjbvVdB4nER4pe2lUXjd9/R0m33jJazNJLykbD/2y+9RDs0158H9HeY3Y6JuR2Ar9Ttpy/uNAA7I9m35FeQMtmVvFLGBtvwOYoNtuTyGGGvLixg+2JbHxxEbaMt9OzSGbYnf/TMvYd/K0rWcIIoyVD3oVkN7IODTuzBunPnX3WKyjrU9EGuzfqoq/7Lt7vCQ+pZVlMOjUr53DFy/kTc84TpR1YZUGs/FD48A3kfMhryTHlsGr4YRf+cYx007oQPjHFeNSvBzJo52ROj7l+PQwPRuoIlDIxM8nOB43dC4Z747bbcjYRGWeZw6gnn3QDsdo42D2C3dKLz2t/MNm6/Lp2kb8/Y9ULev3yStS98Dhr1s1b5akoxPwIa3K45PxuFjd9c4YKw9EXs2YtiWiD1xB2LYjjhHI4ZtiFg5ARhrP8QO7EQM2+5O+vtF7fSqzbuQHg5vpvEXUBz2tIA2+vgXCa5PnYCi8a9QvNpTihli1/UNiqu9JoiT9/xPG/N4nruFf/2+YG4t7fjuLvvDRCMqy2PFnJywnbLRD783hkflo47w9113j7ITv76/3xGNEQNH0r+eOIo4vTeJ31SF1ZXCbVs1hlGiXeU7aX2tbCz0VrHSkHOJcoi+jbbLecpZ720sd5XfgPY9tf6f4kxvqHiY1lnK62/ooI0Pa84Zg+NUp8NiUnJ0Oy+ydo4=
*/