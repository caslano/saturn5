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
iJwBbmxWVosFHIjzJC5rg68FJjoXLAsIEr/TD1zGowp8XOVAOqH+X1EzuK+ND3OBouDQGijPZqThvNUdFPtcH6pTcm5ZRE6d5FNvXhnJUXLarFUwymz6NiWZGwlz6Dsc/W7OdRvXnsatLNu736s2s4oaG86Hs6vN0CHXpNUn4qum8Q48X6++nKue3VrV+Qd8eK3jt+ceIntRtVvkqp+dcVj7DT040BlArVjfVn09Cy8rOxIRc4xzfZYp4rfCn9wiudWgoiZCQYJ2w8bk3gefPXwYnYo2/5ibtq7QBYysZOHvATU5IKBUlv5Y29ZRO/Nl9vUI7odlTPOwy9lGgUnwW0oTMyX2Twtxs1oZOhKycDWr5t7vxO5O2ncRDOZFATTW1mPUr7yngn41PVOlqKL5QycvroDSVyDDoKuQ8CWj7Qu/40zyhC5nyGizmJ+Lv2ALAoH3/6EFbklMc3W7TWyRioFArXONrP+rpl0qLwUJKBFBNmkWsoA8chRNxGKF2tAL50MStav2lXaYPkp7aghKQKoUStipBsgwmuDqDDd4QFE1Jecd/Z6kikOjCA==
*/