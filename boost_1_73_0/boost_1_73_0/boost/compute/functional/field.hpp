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
hvNt7Z+ugO6w6fvfDe3Jc3829tepR151dr01GCAK//rZ6Iex+8Hk7JstAcsseGZA2ZVBGOl7nnB7/hAQeT8Wu68oigNAyrE4EHtKOPtdNbSZgcuxtoFSe1WzMdZ+/8kb3w+RIrfHdbz76QdLUPhbDPw/UEsDBAoAAAAIAC1nSlIbk49FAQ4AAKIkAAAoAAkAY3VybC1tYXN0ZXIvZG9jcy9saWJjdXJsL2xpYmN1cmwtbXVsdGkuM1VUBQABtkgkYK1aa2/bxhL9vr9ioS+OC1lu2n64DYqL6zhuo9vEDizlBgEMCBS5lLamuCp3aUVAf/w9M7NLUrLzKNC8JEvk7jzOnDmzzORupL/7x36pCS2nv/prwX8X+IXXdNO7xv1h8vD0DYvFX1p+48Y7vH7DVue6v+uvxan+prv+0s/4rkXc6xd6v1h8w3Z3ZCT9c0433y3oLT6RO+P9l267b+xqHfSzy1P9/Oef/6XP9A/f//D9WL/KamsqPQumXppmNda/FPzJf9bZp08Tb/491iborJocLDhfW6+9K8Mua4zG+8rmpvam0JnXhfF5Y5f4wdY6rI0ubWX05c27j9Pr38Z6t7b5Oq6zd632a9dWhV5nD0Y3Jjf2QZbZZk3QrsQKWL+wPmDNNlhXT7C90cE0
*/