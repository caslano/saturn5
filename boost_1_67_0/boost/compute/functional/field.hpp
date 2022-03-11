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