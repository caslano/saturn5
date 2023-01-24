//---------------------------------------------------------------------------//
// Copyright (c) 2013 Kyle Lutz <kyle.r.lutz@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_FUNCTIONAL_FIELD_HPP
#define BOOST_COMPUTE_FUNCTIONAL_FIELD_HPP

#include <string>

namespace boost {
namespace compute {
namespace detail {

template<class T, class Arg>
struct invoked_field
{
    typedef T result_type;

    invoked_field(const Arg &arg, const std::string &field)
        : m_arg(arg),
          m_field(field)
    {
    }

    Arg m_arg;
    std::string m_field;
};

} // end detail namespace

/// Returns the named field from a value.
///
/// The template-type \c T specifies the field's value type. Note
/// that the value type must match the actual type of the field
/// otherwise runtime compilation or logic errors may occur.
///
/// For example, to access the \c second field in a
/// \c std::pair<int, float> object:
/// \code
/// field<float>("second");
/// \endcode
///
/// This can also be used with vector types to access individual
/// components as well as perform swizzle operations.
///
/// For example, to access the first and third components of an
/// \c int vector type (e.g. \c int4):
/// \code
/// field<int2_>("xz");
/// \endcode
///
/// \see \ref get "get<N>"
template<class T>
class field
{
public:
    /// Result type.
    typedef T result_type;

    /// Creates a new field functor with \p field.
    field(const std::string &field)
        : m_field(field)
    {
    }

    /// \internal_
    template<class Arg>
    detail::invoked_field<T, Arg> operator()(const Arg &arg) const
    {
        return detail::invoked_field<T, Arg>(arg, m_field);
    }

private:
    std::string m_field;
};

} // end compute namespace
} // end boost namespace

#endif // BOOST_COMPUTE_FUNCTIONAL_FIELD_HPP

/* field.hpp
OZrplKU3/Lx+9UMpiovc7z2Tm+uHnnLJoGSDf2x4+On9KmK8+hspZLW6hOWrn62VvN7f1JbzCU4yZb90Kzo5bOYiDHFj9OZkDezVu7iu82UVsIh+5c89eWclPVRVcvm49PShlzZyXv2fAp4aKir8zOLjYoxsPY7McXlqFh/x2bWu3ct2HPKqaaq4b3AznnahEZw4gSCgp1svT8iWdEKXSJ1n3BjvFZ54naEHY8dcme2s0HyHc9OCKt3MefepoKd8dSzFwQjnt7bl86jzDBhRR9hv3ku99iJhLfsessRD2Dl1mmmSo9weg2c6bYIc8cU7bo+Sqw0djCeF5c/LFyiTZfaSaHWH2t0PK2ZmL3p+dRL+jk1+MjfW9RlrBvL41KCb+bbzIgZV7pX+MHipDAVCtjCqJH8mx4U/R7cgse+9raoVh9sDX5px9m6MkjdUFX3PYenFt3SmPGvgPKNl2KX5lPRj8NY6vvrJuq/89YFBv5i0ZwODQdo68OGnwhaJS3Ef8p82ienZiZbUCi1kvS77XPcLleiaOn7BFv9SfRNTfMhlvX5l7YzPnMexhaxr95CV+pKhlYG7vznY9k/BNm+TzzMJBsqo1lOiPsOHdV/SBzcs0+CXTFkk7uvhqtwYaEpr+mjZs7bTB4OCdZqOVItalDtK0GzeVXNQrfhfIaZ5ybrPI9tsY49jUXTtcs/0TUJZ31a3fybE7c59PUZW
*/