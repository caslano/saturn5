//---------------------------------------------------------------------------//
// Copyright (c) 2013-2014 Kyle Lutz <kyle.r.lutz@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_FUNCTIONAL_IDENTITY_HPP
#define BOOST_COMPUTE_FUNCTIONAL_IDENTITY_HPP

namespace boost {
namespace compute {
namespace detail {

template<class T, class Arg>
struct invoked_identity
{
    typedef T result_type;

    invoked_identity(const Arg &arg)
        : m_arg(arg)
    {
    }

    Arg m_arg;
};

} // end detail namespace

/// Identity function which simply returns its input.
///
/// For example, to directly copy values using the transform() algorithm:
/// \code
/// transform(input.begin(), input.end(), output.begin(), identity<int>(), queue);
/// \endcode
///
/// \see \ref as "as<T>", \ref convert "convert<T>"
template<class T>
class identity
{
public:
    /// Identity function result type.
    typedef T result_type;

    /// Creates a new identity function.
    identity()
    {
    }

    /// \internal_
    template<class Arg>
    detail::invoked_identity<T, Arg> operator()(const Arg &arg) const
    {
        return detail::invoked_identity<T, Arg>(arg);
    }
};

} // end compute namespace
} // end boost namespace

#endif // BOOST_COMPUTE_FUNCTIONAL_IDENTITY_HPP

/* identity.hpp
aA7LC3xJrmk5aZmBjonyZbnBGcaN4zS5HVl26je1PC1j8HXYt3nGcoZ9giSXZQ3jJ8lDXXiOv40to5M56MnbWhxyB072A5sXZA+cVsRh+cN9scv5vLwpAZ9Gkj3xvRI82HuUrsAgdARx+X5oOWeBhHY1HCuYGB+Wx43agS78keGwQLIfluFYYYT+jXiqWLz392PLY12Bdy4NJy2EPH/Uf6L4QQDHAj5LsmXxo2L876ZwUXyM/2sdyiu9Z8Hd0tykMENn6/KHBplCP93cpMVFuxN0nE7DCCbrhNZPIx4LJfFgU1gej58zaFeSScFxAplld4Leu63CWSDlW+8/U/lAICUn1xwIpLSn9oZwaPDcneBxzNuX12UiAed4878+m8XciqDokzJY47XdO5WcY5KFzKTxkAzn9/MLW57UC5xekse6AX4DMc/qB9Yjv0hxWUdANpI81hOQjV/GPKsrAnczyVXFZL2S5LLOGAnj+leGN3zy5rPV+DfQHYg9dqlamhN6k7jYr9EyLyf6Puyba8ccq28QH/v/c0udA379Omm+1TuQvV9H9YfuwTi5RZwm9ynrn+YtI57SUyOh7w/ltfsbc4vkJ9Kj5TX7ieRxOY1+Y+5+mss6jrgo829SXNZz0GOk5wwPug42VDPFYX0HmzWRJ+s85mW/TfFY78FHNOYZ3cfjvbZRlZFGxJERKtfMHaZHb+e8DLO7YC6VnGOjt/eOit2A7z9Q4+7njLei39M+jrSXJV7ekGcvxbtwfNAEx+UDzk4yHcpL1GX3tOC0jvlbW2z/7FmcfAi7pygasMhnX+ZTtleoM3HQB++KOf7AnM7ij9LmCI/Pg0O5D1gojjJ3891DucG3g+OSD+fSP6tY42TvGcpz2SMoAPfZQaINwt0WjP/3xhz/ykK/9B2CzA0O44n9mCHp+QYFb3MILzQm2mcor5hb6nC+2fuG8NwWFHi1ITzvdcPlG8qjXpFz9xAe+VMsh/fs0TbvT3M9bxH7DA+Meer+ahHj/sxmEfai7C+SnzZ5MkyQ9i+PWmVe+YM0zzcD7INtkw6Nny55OayeWUdi62iLQ7m0tS+4zVOHcuksgPfT8wcb7gP03t6WTWu1RxufRKJmha3+EM2pho84O9p+aAIveF++/jDGvdzx2vMBjCG6RkH5y7vWos+8DPJZzrbASI2V0dEzUbbGSxVOY5oIjJMPosad6LK+3D+VwMuMMmHTntYc1R9UVqyVn8Q8d0zMMRo2ZR0JgSw9Vn3vrKGR9N25vcdZHrn/Qq8xL3+A5eW0x131GEmd8CV8suBRd5RV9uN/HnPrUxMcGqqSs/usFIeGqOAcyD6i7qHt7w45K/Uz4uBsR7YPyavs453XaSyn15zkGez2KuOuunOD/oobpIGTrVlOfjP/hi3rjvWYQy2s7rgePFtxyLsxuxnK+QSJzXfarnMW+d4F494bS+mb7ZdrfJCXDNZbWc449YOpKbfHpuVxbfm894Exh2sr/NNeyTzvcVgVCrL//VrA23e+/e2OyPuwzQ9c0GM3gakCvcCYNlOk7H+YOe4UrV0GIOL59BNJvD19h9EjMp3G9NnBo26p2lbu++cJnJ62Z7/Ye8a4f6aSx8WE5Jh4ZZMR1igvVvdIEaEMd5OcBywuuVIuQ15FXU9py47Xlfc5u+D4EoLG46P5Sd+ntOIbnZmZqm4gOPsP+bUs525jU+O3uyex2I9nljnkwXd73F+D3f0Ji+s7eVvR77Xf9q7AaZU7dc+WzyDjMjQ+EXHUPZaDOA3lE1//lMLLACsUsg75cGyNj6d4Li+0WTotHV9Cce5Gt0ta8d2RT8QcaePsJNLwOpPf07raJcApow3RaeToxIk=
*/