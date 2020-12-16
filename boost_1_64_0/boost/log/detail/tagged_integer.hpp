/*
 *          Copyright Andrey Semashev 2007 - 2015.
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 */
/*!
 * \file   tagged_integer.hpp
 * \author Andrey Semashev
 * \date   11.01.2008
 *
 * \brief  This header is the Boost.Log library implementation, see the library documentation
 *         at http://www.boost.org/doc/libs/release/libs/log/doc/html/index.html.
 */

#ifndef BOOST_LOG_TAGGED_INTEGER_HPP_INCLUDED_
#define BOOST_LOG_TAGGED_INTEGER_HPP_INCLUDED_

#include <boost/log/detail/config.hpp>
#include <boost/log/detail/header.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace boost {

BOOST_LOG_OPEN_NAMESPACE

namespace aux {

//! A tagged integer wrapper for type safety
template< typename IntT, typename TagT >
struct tagged_integer
{
    //! Contained value type
    typedef IntT integer_type;
    //! Tag
    typedef TagT tag;

    //! Contained value
    integer_type value;

    //! Conversion operator
    BOOST_CONSTEXPR operator integer_type() const BOOST_NOEXCEPT { return value; }

    //  Increment
    tagged_integer& operator++ () BOOST_NOEXCEPT { ++value; return *this; }
    tagged_integer operator++ (int) BOOST_NOEXCEPT { tagged_integer temp = *this; ++value; return temp; }
    //  Decrement
    tagged_integer& operator-- () BOOST_NOEXCEPT { --value; return *this; }
    tagged_integer operator-- (int) BOOST_NOEXCEPT { tagged_integer temp = *this; --value; return temp; }

#define BOOST_LOG_TAGGED_INTEGER_OP(op)\
    tagged_integer& operator op (tagged_integer const& that) BOOST_NOEXCEPT { value op that.value; return *this; }

    BOOST_LOG_TAGGED_INTEGER_OP(|=)
    BOOST_LOG_TAGGED_INTEGER_OP(&=)
    BOOST_LOG_TAGGED_INTEGER_OP(^=)
    BOOST_LOG_TAGGED_INTEGER_OP(+=)
    BOOST_LOG_TAGGED_INTEGER_OP(-=)
    BOOST_LOG_TAGGED_INTEGER_OP(*=)
    BOOST_LOG_TAGGED_INTEGER_OP(/=)
    BOOST_LOG_TAGGED_INTEGER_OP(%=)

#undef BOOST_LOG_TAGGED_INTEGER_OP

    //! Inversion operator
    tagged_integer& operator~ () BOOST_NOEXCEPT { ~value; return *this; }

    //  Shift operators
    template< typename T >
    tagged_integer& operator<<= (T const& that) BOOST_NOEXCEPT { value <<= that; return *this; }
    template< typename T >
    tagged_integer& operator>>= (T const& that) BOOST_NOEXCEPT { value >>= that; return *this; }

private:
    //  Protection against improper usage
    template< typename T1, typename T2 >
    tagged_integer& operator<<= (tagged_integer< T1, T2 > const&);
    template< typename T1, typename T2 >
    tagged_integer& operator>>= (tagged_integer< T1, T2 > const&);
};

    //  Relational operators
#define BOOST_LOG_TAGGED_INTEGER_OP(op)\
    template< typename IntT, typename TagT >\
    inline bool operator op (\
        tagged_integer< IntT, TagT > const& left, tagged_integer< IntT, TagT > const& right) BOOST_NOEXCEPT\
    {\
        return (left.value op right.value);\
    }

BOOST_LOG_TAGGED_INTEGER_OP(==)
BOOST_LOG_TAGGED_INTEGER_OP(!=)
BOOST_LOG_TAGGED_INTEGER_OP(<)
BOOST_LOG_TAGGED_INTEGER_OP(>)
BOOST_LOG_TAGGED_INTEGER_OP(<=)
BOOST_LOG_TAGGED_INTEGER_OP(>=)

#undef BOOST_LOG_TAGGED_INTEGER_OP

#define BOOST_LOG_TAGGED_INTEGER_OP(op)\
    template< typename IntT, typename TagT >\
    inline tagged_integer< IntT, TagT > operator op (\
        tagged_integer< IntT, TagT > const& left, tagged_integer< IntT, TagT > const& right) BOOST_NOEXCEPT\
    {\
        tagged_integer< IntT, TagT > temp = left;\
        temp op##= right;\
        return temp;\
    }

BOOST_LOG_TAGGED_INTEGER_OP(|)
BOOST_LOG_TAGGED_INTEGER_OP(&)
BOOST_LOG_TAGGED_INTEGER_OP(^)
BOOST_LOG_TAGGED_INTEGER_OP(+)
BOOST_LOG_TAGGED_INTEGER_OP(-)
BOOST_LOG_TAGGED_INTEGER_OP(*)
BOOST_LOG_TAGGED_INTEGER_OP(/)
BOOST_LOG_TAGGED_INTEGER_OP(%)

#undef BOOST_LOG_TAGGED_INTEGER_OP

#define BOOST_LOG_TAGGED_INTEGER_OP(op)\
    template< typename IntT, typename TagT, typename T >\
    inline tagged_integer< IntT, TagT > operator op (\
        tagged_integer< IntT, TagT > const& left, T const& right) BOOST_NOEXCEPT\
    {\
        tagged_integer< IntT, TagT > temp = left;\
        temp op##= right;\
        return temp;\
    }

BOOST_LOG_TAGGED_INTEGER_OP(<<)
BOOST_LOG_TAGGED_INTEGER_OP(>>)

#undef BOOST_LOG_TAGGED_INTEGER_OP

} // namespace aux

BOOST_LOG_CLOSE_NAMESPACE // namespace log

} // namespace boost

#include <boost/log/detail/footer.hpp>

#endif // BOOST_LOG_TAGGED_INTEGER_HPP_INCLUDED_

/* tagged_integer.hpp
Jom31D6f+8lXJx/dJWVmhZVsq5K+N26UcBk2X3xb2Rb3h66bKpLHFVYldqiVsPielH5Q02qkenMnnWf67c2Sxg/uHra/f3wheV1mT7L+FHx/ZPr3E/2bhGlp56i3VCvWWelhvaLb19cH+5l6iBX/SLtx8Xsjy/+N3Skpxx2uy9WH9ihXkqqqnz+vSrmfcqUpNzm9az1D/2vsusC8//TV94jjsyjo2cA3ZboNrpH6uZC8e0sdrMzQNvUAu3pCKfYIlfYO8Deb5d8j9MhMs0eo2W/z0MzQfUPpTyH7hu6ZGbpv6LszQ/cNfc0v8++3OTN039C1M0P3DT3vrtA9QtP9MlPmcn6ZKXPUXaF7hP4yI3SP0ON+mSnzV36ZKfOBGSXvEarHLYLXqvUKS79erXk3quDwbpQa/G4Ufr3aEsc46M/F5mHGyP/8ZlMQN6wCaxB292zzXqVfp7Ic3++90fdI2GjzrLxlsdd/rdP7PumGX+8rFRbM8Z5/J9Hh/Z+4Du8Uzu//hA19py/0PRfkXHJSb/WyGmMtVcPspWqIa6nqz29G76ilqptnqSqMrm+9EbOUtZOWqpfilqqN8UvVmoSlanWZpeqJxMfVo2UHqQJ9/+dKmZ8q+7Lqzu7F3dVau7t62tVdrXB3V0ujuqslnu6sc9VdnRPbXZWP667KxHdX0QndlVWmu/oJdyKxS9C6Xnf51uORdJPL9ucJ/hGut5Wu3sd1s9PVW7hCV7p6DZfvTlfbcO2i0tXuqATV0pOu1uGaRqeqHtEetTE6XTWPSVdrcDmx6Wo1rmFcunoCVzc+XT2Kq56QrhbjGpRJUAvLpKuKielqfmJK0Fpcd+n27SrlOpiYjX6yClfHYp0wK191tauoR+x8leHKV4twld356jF3c1UhKl/Ni2LPaU++uhsXE32J6hXtUrOj81V8TL66JaZQRcWSVmwV9SucHJevTuImxOcrO6G5GpWQr/6R0FpdWyZffYEblFgQqGuZfnhQ+l2MWRftBinnjERaQXWmnTvSzhfSzq1o5zzaOcuDi2bn7uilagVtvZS2XkJb/4m2XkBbz6KtfX36I+kzA1Sh/q1rLWk/VrYlbd6UNs+kzevR5rVo86q0eSptnhzdRy2M7q7m0/Yzafs7aPtptP0NtP042n1EYs8QnS1bX8snkt9H1FI0Y3cJfn0NtoAdYCd4s7okOpzed+fi0ul9b0q4JN4XYop0vFKvTeSs45mx2qBnUfBzZ4feUG1A2aJ7uz+sQXz1SPHnTnbY507XZ2ROgVm7zyNxE5ztDI+U/NxJkPOfOT13iFv65w5hQ547HXQ9vyrn7i6hP9a3wvfFx1WB7ntlJZ2Cshvoe3+h762i7y2n7z1C31tE37uPvpdCnytHn4unz0XR537FnaTffUu/O5LYw/F5c+4j/5nPmzqP/Gc9b3zPlz888vufL4W67yZLWrsTz6dNm9CmjWnT82jTmrRpehTt6aE9eZ7cx/NkHm17N217O207lXadRLuOpV2HJ/Y8a/fvpSnOdsE2awLu39+wC3ZYE9YuSDqltwu2WVN6u2CbNaW3CxI2rF3wmTXBdsG8tcF2wc5rSrYLrlgTahfsuua37YKXrSmdXXDRmt+2C360pnS/DzXX/ufZBX3z005UU3IkYA9M0WyCXXDuWtMPRzjbBIPtSj897w1/s2uO+quxbVRbX7THha+/bpI0Wxsb0+SNwfp+hvib6f7NTrfrZL1Lx/5N+Zz3uvHZuTbIuqHmt62KLouvf62T+C+7q9jTbafyVDLlydPzysx5p3uI8vy2/bIozC739dYrWIX+qk64FvrvreA09L3Vz7dZp9P9RfiSbY2PyPk7sDUm2k0=
*/