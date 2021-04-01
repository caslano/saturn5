
//          Copyright Oliver Kowalke 2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_COROUTINES2_POOLED_FIXEDSIZE_H
#define BOOST_COROUTINES2_POOLED_FIXEDSIZE_H

#include <exception>

#include <boost/assert.hpp>
#include <boost/config.hpp>
#include <boost/context/pooled_fixedsize_stack.hpp>

#include <boost/coroutine2/detail/coroutine.hpp>

#ifdef BOOST_HAS_ABI_HEADERS
#  include BOOST_ABI_PREFIX
#endif

namespace boost {
namespace coroutines2 {

using pooled_fixedsize_stack = boost::context::pooled_fixedsize_stack;

}}

#ifdef BOOST_HAS_ABI_HEADERS
#  include BOOST_ABI_SUFFIX
#endif

#endif // BOOST_COROUTINES2_POOLED_FIXEDSIZE_H

/* pooled_fixedsize_stack.hpp
jzcdDJaMErDBx681vW6ueyYuo9t3xuPkB7twkal11VTa7/i9Ur1yzRn9eiOe0N/ZM/X8w7gu1B8h5iIdyLxNhfjzWXDf/EqLMF+cHML2oHeQeTob9F0XAQSf2pEdn86DO85wI7tg19j6QNXsELaZDK++OGK1JP6FUrYc8+pvx8egAUtrPnyprX5iLwcdIFXgB+Wc+uHx6ujoJcu7i0ZSLlwtJWIgz6JcvMwMX06UuOJASN7JSbCWSVxuIccc/0XXKunTMeYNmxfpRVkLfdjVI+RswQX/y3hE6i9+3cWl8DBeEi+oVzGgp7vTRQqKll/OfjByC8PRYVVUa1dv9tNxBSJHvSWuTrmOl/UoonkpOU9XVyeEg3RTa511bSpIzmEtv7yBLFk9j4HN2uI/OgJIPoBeKYHrkFpdEpGK3AGAZw+5nF6UkJZoO0UdmlIHJuNH5/eZADQKIV3XPP1dyhmWQUuWYtLsmVSFmy3zbf+Nnbz52HjtaDz2fupQ9OCHvAzh3RJBaMXEMYElC587EcSfhLyOLCsfaan5NTJMc4s6bWplQ76jqB7zO+Yd+w==
*/