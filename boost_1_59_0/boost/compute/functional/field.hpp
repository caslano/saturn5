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
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
*/