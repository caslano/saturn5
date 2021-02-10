//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga 2005-2012.
// (C) Copyright Gennaro Prota 2003 - 2004.
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/interprocess for documentation.
//
//////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_INTERPROCESS_DETAIL_POINTER_TYPE_HPP
#define BOOST_INTERPROCESS_DETAIL_POINTER_TYPE_HPP

#ifndef BOOST_CONFIG_HPP
#  include <boost/config.hpp>
#endif
#
#if defined(BOOST_HAS_PRAGMA_ONCE)
#  pragma once
#endif

#include <boost/interprocess/detail/config_begin.hpp>
#include <boost/interprocess/detail/workaround.hpp>
#include <boost/interprocess/detail/type_traits.hpp>

namespace boost {
namespace interprocess {
namespace ipcdetail {

struct two {char _[2];};

namespace pointer_type_imp {

template <class U> static two  test(...);
template <class U> static char test(typename U::pointer* = 0);

}  //namespace pointer_type_imp {

template <class T>
struct has_pointer_type
{
    static const bool value = sizeof(pointer_type_imp::test<T>(0)) == 1;
};

namespace pointer_type_imp {

template <class T, class D, bool = has_pointer_type<D>::value>
struct pointer_type
{
    typedef typename D::pointer type;
};

template <class T, class D>
struct pointer_type<T, D, false>
{
    typedef T* type;
};

}  //namespace pointer_type_imp {

template <class T, class D>
struct pointer_type
{
    typedef typename pointer_type_imp::pointer_type<T,
        typename remove_reference<D>::type>::type type;
};

}  //namespace ipcdetail {
}  //namespace interprocess {
}  //namespace boost {

#include <boost/interprocess/detail/config_end.hpp>

#endif   //#ifndef BOOST_INTERPROCESS_DETAIL_POINTER_TYPE_HPP


/* pointer_type.hpp
bq5fs48idPYTeovmPXrcqUJXg5djwBbmEirFuLiUOOc3xknU/5gBGkjK6HTQHSEpG7mQ2GA8QKkxeapNaK3HD4truO/wIjhMqFuUo6mBGgwk3dYnZg04OQtdXP8aAffjdB0aBRyUU/cGxqldqp53H64+QIw4P2ZhxlmAlwDypUvO1wwu+yjaSJDCWPRK0N44TnvUSMp7rK40nLd5DdprqSUu4/mcQ+WmmGqCmNqQIjgAWIeucdBh0inqMsL4AOM+EgsRoTbhAgIEQvcTLt4M7oI+DBMImJtwgSW3sdU3sN8cDS0FDGsDk6iE177lY1FN1ikfU9KwqmKCAlvdiCUvNt1sEC6Bbvb0lMG0PcslLjslnC74aAO2uLB3VgBILVTQDg4+K8KL6a27StMdiqAdDF7XDY3dUDO7vc7YO7OGHtaOO8pIrUfh+Qv28y22Jq2mq9+QFLUIV4pOWJzho+8YpoxegibThBaVqYJqgH7pKn4vXLy8XBoLHly7kBHzTbqKjLcCvfszMFxOpEJMU2MtaXYJCsRj0M8qyKGDS4UkRW8eKioDu8NdqiG7o+7QeXGk2Omts4P/AVBLAwQKAAAAAAAtZ0pSAAAAAAAAAAAAAAAAHQAJAGN1cmwtbWFzdGVyL3Byb2plY3RzL1dp
*/