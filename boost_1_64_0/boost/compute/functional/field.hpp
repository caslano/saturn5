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
z7UB+uiVMi/1TjeX+1WKY9/oBq95CI8Oi9l+1Tz7NjfLzxvPJnhuZ4DIDRUH4E1JDmma7lwh9+diXljqzKEtdiKO0zbEwR7MW9KcSqhFfvtvTfBIcFX8l7dFnBA7jN9HG8JxI0v4sLw9ycOb39hrSPBoUCOd/B0RjplZ7cGmeb6OzNsawqPXS9ckbyfNC9vVPBbfmeDxtWjwagkeX3nmeb+V5pnIjbxG3P/8BTXfxItofUHi1WtJpDDY33BH4Tou5IHG6A6zaMc9i6l4vGewb2x4NMQFkeeuxi8kD2/msCz8MoGbWKGzn0tyequLwudTybp6W5/jP//KcKgvaRD1kc9vErgrCvf3bxMc1+M0E4o5/UDywgmjeDPhDxHO9caeuOVwvXGu/iXJcWIBO+7LEnMij/LFGDkjsR9D7SsRrnwiZxM4ORjR/8W5c4IzJdMgmTB4JRgq3sBX4zRW1uYWMqlrIs6Rsi4LsL9iXNflazFu67Kf4FBdWL6/HuP9VbqTWu0ALYZ73izfr7J8N1ihf14d4zwV8rq2PpxHUyHzmmle0Ns54oDZeljvcLcJj3h32TcUnzDeK60r+wLxfQdYU/0jgTsRgP2xrWwLt6rxczM49XNFHD/nMic/d8Txcy5zGueJOPDtwLwVc+Q8WUCPpnnR25/bw3hUfjVvJXnxfLmf5kHxQo+dN8mDUsS4SfOg0NAuSZ5XaHI+T/MwOHD2b3k2WLc4O9xNcTmWE8fzO4RHO3kse+fTPBu8G/ePDuW1ywA49F9eyzcP5VMJxN58HnOV/bSfwIvE+DpI8uLxlZ0/zbPjq57kxeOrmeTF42s2yYvH12aSF4+vrTQvHl8pnh5fHIc9yY3H126SF4+vvSQvHl/7Sd7w8XUwlM/jK3BrWm+v0WuQ5AEiTDji4txTc2kY8h7c/j8s1qbZ2b2Pw7HgJQdNzGPv30k89O0G5otvgofoUI5dsFzEHBjtMq3Nb0U8GO0Y699WnILiS4oG4rVTS/GMSS/fijY8b6fwHsx3NG7tlG2Ls51SII3vao61U7Yj/HA7Jfue5btNNcyZabxapsJG+KPmkDhwnf5kMfQ7xwtTeejziW2FubKh7N+XGAJ29wPe/LPEIX597O2kcLMe2PpLzGHR5P3vxt8O4bk0+6jTjwJ3mh6z1vuoBwqrdkmBbf4EGE6EMZ/8LGDiFFe+V/1Aj/tdjWWOx9JBGu8VHO/AIvF9iXtzUeK7ZwNOsXWqV87nFwjn+TmBV9Z++frsEfYbPd9hPHqbTsZNi/NcWJN2eIzTk6vZGsZACqd/lN/I2ROco9nRgNdinKSD8XqE0/ulAm9E+DLVgfFmhPfU71sxviTx2Qg/vTGXZ0dhOydxUoWL3AabEYce15b+MRq/+Yjre+DbMU51ZHzH4q6fcoxfiyf6ac9yTD/tW9z004HFTT9l5zC46aeaxU0/1S1u+qlhcdNPTYsn+qmlOCQrvh9gL57X4mkZrJ3P8obL4KzN08hgbnEjg5sWT/TtluWYvt22uOnbHYubvt21uOnbPYubvt23uOnbA4ubvs3OafG4b2uW42UQcTouHPD5JdftPOc0BeZePWasJTDXLIzNCsxVifu9fo9zBmyVQqCNzN/kyIj0mds3eFENG5bp+qVD2gv+nWtMGgXsjyEcGiC8FklyMIhugj25obyjvFc0hEODCZw84rBSx5hOc6gFmbMVcaA42X5KcnT9d5KcuP67Q3lc/70kR9d/P8nR9T9IcnT9s8tYDhQWOLUkR9e/nuTE9W8M5XH9m0mOrn8rydH1n01zqP7Cnrsic4r+TaqKQ99pzIssx6TbNjhljnR3NEaZMta6LrCVOfo70hBljjA=
*/