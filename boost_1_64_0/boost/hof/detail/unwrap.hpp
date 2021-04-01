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
u/WKdopNtR93zWf+/6y56Vq19TF/O4XMk1FSdt/rVffXCgEvayPXr13o6lLs/MyontkZHxGfBHyUhffYNhTiTlG77GaLg8XV+QGt2/XN1nzclCKKYVICDXyvVhWnjV7ObcEe6HQjpZLouXKHQmZF2ArKbsZyNsag8oTCzmjBS8lCAbFEdbaCscSUQwbJW4s9mdZQpYXROubBueqXlCXHKFKPJ2vtOVP/8iTsILRgKPM2ITc8eTdJ2QfAcXvv+m/8sArW4Q4+MJlr3NcsYeE7owZ+7sym/JEC0eAWpb04t/nkdxNH2+iIkE9RBzURVggDXQ3RZA2cQAm8di4ew2GmbXMhWxoMEadokAKzER3+/aoG35Uz9po9zObogUt+8EFFifY07q/h6uUt/04FOcIDN8v9QgR2g8qv3fZfBAnUJn9kdefsA9F4DNL+NwwxeHN0hmH8LBG5Iiwc5OlAT8T9Q7QbKDbRUsBrsMtx7EWthzVv0K5L5K1IKxB8gOYgSGR2Kav5yJuF9tZcQtQ9d4yzfvA4G8G3hOe7D8nznPk0VM5u8uCw4Aw4A8JtJQ==
*/