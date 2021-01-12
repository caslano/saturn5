/*=============================================================================
    Copyright (c) 2014 Paul Fultz II
    unwrap.h
    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_HOF_GUARD_UNWRAP_H
#define BOOST_HOF_GUARD_UNWRAP_H

#include <type_traits>
#include <functional>

namespace boost { namespace hof { namespace detail {

template <class T>
struct unwrap_reference
{
    typedef T type;
};
template <class T>
struct unwrap_reference<std::reference_wrapper<T>>
{
    typedef T& type;
};

}}} // namespace boost::hof

#endif

/* unwrap.hpp
7FDRgNiE5y+LL14aRMFjyzfPL8ZqUL0JQ36jjp7w7TzhpAZK/BbEb9b447cxvuVHaIReT1KMU38TQvj3dvmHqvQFsbJoVFh0l7DojJJsFn3P9BOdlp9E8pI8RvWZY2SdbH6qZ2RjBj+9ZnNrHyE/nbHfEg0xMtJqKbiKEdNCjAA/mQjwk0QIP0GN9I5u+IljoZljoZmsszh7LDByx6J/aCxMP4uxsFjHwiJvLMRCOji8sbBJ
*/