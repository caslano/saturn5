//---------------------------------------------------------------------------//
// Copyright (c) 2013-2014 Kyle Lutz <kyle.r.lutz@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_TYPES_FUNDAMENTAL_HPP
#define BOOST_COMPUTE_TYPES_FUNDAMENTAL_HPP

#include <cstring>
#include <ostream>

#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/comma.hpp>
#include <boost/preprocessor/repetition.hpp>
#include <boost/preprocessor/stringize.hpp>

#include <boost/compute/cl.hpp>

namespace boost {
namespace compute {

// scalar data types
typedef cl_char char_;
typedef cl_uchar uchar_;
typedef cl_short short_;
typedef cl_ushort ushort_;
typedef cl_int int_;
typedef cl_uint uint_;
typedef cl_long long_;
typedef cl_ulong ulong_;
typedef cl_float float_;
typedef cl_double double_;

// converts uchar to ::boost::compute::uchar_
#define BOOST_COMPUTE_MAKE_SCALAR_TYPE(scalar) \
    BOOST_PP_CAT(::boost::compute::scalar, _)

// converts float, 4 to ::boost::compute::float4_
#define BOOST_COMPUTE_MAKE_VECTOR_TYPE(scalar, size) \
    BOOST_PP_CAT(BOOST_PP_CAT(::boost::compute::scalar, size), _)

namespace detail {

// specialized vector_type base classes that provide the
// (x,y), (x,y,z,w), (s0..s7), (s0..sf) accessors
template<class Scalar, size_t N> class vector_type_desc;

template<class Scalar>
class vector_type_desc<Scalar, 2>
{
public:
    Scalar x, y;

    Scalar& operator[](size_t i)
    {
        return (&x)[i];
    }

    const Scalar operator[](size_t i) const
    {
        return (&x)[i];
    }
};

template<class Scalar>
class vector_type_desc<Scalar, 4> : public vector_type_desc<Scalar, 2>
{
public:
    Scalar z, w;
};

template<class Scalar>
class vector_type_desc<Scalar, 8>
{
public:
    Scalar s0, s1, s2, s3, s4, s5, s6, s7;

    Scalar& operator[](size_t i)
    {
        return (&s0)[i];
    }

    const Scalar operator[](size_t i) const
    {
        return (&s0)[i];
    }
};

template<class Scalar>
class vector_type_desc<Scalar, 16> : public vector_type_desc<Scalar, 8>
{
public:
    Scalar s8, s9, sa, sb, sc, sd, se, sf;
};

} // end detail namespace

// vector data types
template<class Scalar, size_t N>
class vector_type : public detail::vector_type_desc<Scalar, N>
{
    typedef detail::vector_type_desc<Scalar, N> base_type;
public:
    typedef Scalar scalar_type;

    vector_type()
        : base_type()
    {
        BOOST_STATIC_ASSERT(sizeof(Scalar) * N == sizeof(vector_type<Scalar, N>));
    }

    explicit vector_type(const Scalar scalar)
    {
        for(size_t i = 0; i < N; i++)
            (*this)[i] = scalar;
    }

    vector_type(const vector_type<Scalar, N> &other)
    {
        std::memcpy(this, &other, sizeof(Scalar) * N);
    }

    vector_type<Scalar, N>&
    operator=(const vector_type<Scalar, N> &other)
    {
        std::memcpy(this, &other, sizeof(Scalar) * N);
        return *this;
    }

    size_t size() const
    {
        return N;
    }

    bool operator==(const vector_type<Scalar, N> &other) const
    {
        return std::memcmp(this, &other, sizeof(Scalar) * N) == 0;
    }

    bool operator!=(const vector_type<Scalar, N> &other) const
    {
        return !(*this == other);
    }
};

#define BOOST_COMPUTE_VECTOR_TYPE_CTOR_ARG_FUNCTION(z, i, _) \
    BOOST_PP_COMMA_IF(i) scalar_type BOOST_PP_CAT(arg, i)
#define BOOST_COMPUTE_VECTOR_TYPE_DECLARE_CTOR_ARGS(scalar, size) \
    BOOST_PP_REPEAT(size, BOOST_COMPUTE_VECTOR_TYPE_CTOR_ARG_FUNCTION, _)
#define BOOST_COMPUTE_VECTOR_TYPE_ASSIGN_CTOR_ARG(z, i, _) \
    (*this)[i] = BOOST_PP_CAT(arg, i);
#define BOOST_COMPUTE_VECTOR_TYPE_ASSIGN_CTOR_SINGLE_ARG(z, i, _) \
    (*this)[i] = arg;

#define BOOST_COMPUTE_DECLARE_VECTOR_TYPE_CLASS(cl_scalar, size, class_name) \
    class class_name : public vector_type<cl_scalar, size> \
    { \
    public: \
        class_name() { } \
        explicit class_name( scalar_type arg ) \
        { \
            BOOST_PP_REPEAT(size, BOOST_COMPUTE_VECTOR_TYPE_ASSIGN_CTOR_SINGLE_ARG, _) \
        } \
        class_name( \
            BOOST_PP_REPEAT(size, BOOST_COMPUTE_VECTOR_TYPE_CTOR_ARG_FUNCTION, _) \
        ) \
        { \
          BOOST_PP_REPEAT(size, BOOST_COMPUTE_VECTOR_TYPE_ASSIGN_CTOR_ARG, _) \
        } \
    };

#define BOOST_COMPUTE_DECLARE_VECTOR_TYPE(scalar, size) \
    BOOST_COMPUTE_DECLARE_VECTOR_TYPE_CLASS(BOOST_PP_CAT(cl_, scalar), \
                                            size, \
                                            BOOST_PP_CAT(BOOST_PP_CAT(scalar, size), _)) \
    \
    inline std::ostream& operator<<( \
        std::ostream &s, \
        const BOOST_COMPUTE_MAKE_VECTOR_TYPE(scalar, size) &v) \
    { \
        s << BOOST_PP_STRINGIZE(BOOST_PP_CAT(scalar, size)) << "("; \
        for(size_t i = 0; i < size; i++){\
            s << v[i]; \
            if(i != size - 1){\
                s << ", "; \
            } \
        } \
        s << ")"; \
        return s; \
    }

#define BOOST_COMPUTE_DECLARE_VECTOR_TYPES(scalar) \
    BOOST_COMPUTE_DECLARE_VECTOR_TYPE(scalar, 2) \
    BOOST_COMPUTE_DECLARE_VECTOR_TYPE(scalar, 4) \
    BOOST_COMPUTE_DECLARE_VECTOR_TYPE(scalar, 8) \
    BOOST_COMPUTE_DECLARE_VECTOR_TYPE(scalar, 16) \

BOOST_COMPUTE_DECLARE_VECTOR_TYPES(char)
BOOST_COMPUTE_DECLARE_VECTOR_TYPES(uchar)
BOOST_COMPUTE_DECLARE_VECTOR_TYPES(short)
BOOST_COMPUTE_DECLARE_VECTOR_TYPES(ushort)
BOOST_COMPUTE_DECLARE_VECTOR_TYPES(int)
BOOST_COMPUTE_DECLARE_VECTOR_TYPES(uint)
BOOST_COMPUTE_DECLARE_VECTOR_TYPES(long)
BOOST_COMPUTE_DECLARE_VECTOR_TYPES(ulong)
BOOST_COMPUTE_DECLARE_VECTOR_TYPES(float)
BOOST_COMPUTE_DECLARE_VECTOR_TYPES(double)

} // end compute namespace
} // end boost namespace

#endif // BOOST_COMPUTE_TYPES_FUNDAMENTAL_HPP

/* fundamental.hpp
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
*/