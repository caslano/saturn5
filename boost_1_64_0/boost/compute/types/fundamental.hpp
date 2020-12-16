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
ZcvMQEIV0o+v7SQGN1wg9N5754FeJCRAAokHHkDwABISRTwg4AGk0HvvnZn9d88/Z/Y37d7r3HjP950zbc9OOTPjrRKhpmT34g7cyw93zu/m2GXOg26NbLs6ABebrxs+C5Wl98I3VUvJxXn7gV92Ga0jh7TOZQLZ6qbvi3W4t6H6FaSVodJcenAQ430Id4VzKXGdMWEFZZQD9dzGweZ6MS/7GWSPEm18U6sWOI+O7jQ7L4tA3xfXXzQkqlox4E2vvcF+7FfIFiPcq1qoCjjF4VwE2vy3i3in0NC6canvsbV+Ls6hxhrdXocWgOr1jjl3WbZMCVfz/m7ZFfBHh9Duc7wjXPpaNiqQ7vgs1OyP7YF//jbOV2MayrgNJDacg3ZnrdsVNgt8pjAmzHmBSN7IilYVorGnF/uXc86DLHMt8xUjMXpxdWdvrZjPQ+lSpLW2rUTF5vRbFh7U+wpYC825S2kmPTRBkK3HZoYi7ByshSK8Yo13jaZk++wR+M+gevFcGVFViux7igjnYJ4vx7fdEeU6eElWHW0ltrEw1Mvlol5aqVrLak/i+7yzupE+ZvmHkMLYCdeLr7xXTrOMNpuAgTnl7+BvkQtVTXmlujYaoldY2UROGfoDOc8Tzk0jmNZkCEHL3lnoUy4hW5oIHihrGk22duKFjvPfCDjnDnEVqSwXQqqW7CZfNJcK3EuIK0mrBVWat+U3flY6M+7rCruWuoZVrSI78J1O2UWr/eDXcq4jQjvmmK7Ik1bigaz4nTyEuN3Cnlfe1ILb7msX9vozN/vQ9vKMCGwveEobbzi58nBjM0VFZvnbgTMick5DmpZzw0xD1s7SR0y7CkUc5neLuHMjfKCiJvvRwOZ6sx63XSJiVpa3RFxNTOslZ61KaycH8Z6jNp4Vt3W4NdfuUsFVjQpSBwnclUsjLpwbj7iccOaVdYpDY8VRDFCeu98t5yKYF56RNXvukevTFfVRnNbzcs5i7SyltQ0kbVGEeFiI+S3SVXNuKq1n38wwPZi8fBfejXiKSMU5FXV3s/PJR21vxEjY0dcW/FfOXTKNd4EJS/oD6C/ul33xryC8cIxyGS1Nr2JtzdmyL365yJOzquVMVpmF5YvrK6k5DrZmcUqIS0nrFXdWyoyb7rKCcQaM07+H4w5twytpWIoVTcYudTetHGysbEYd+VYcOBsL8StS8zRcDTP61uHmwUbSgRSguPOAdEgiqDTKexLDW9f3kpMY35V4BtYYcu6yc610xhoStx8eru1sP30YjJ0f2thBjn9gXctWKNqfKrd+gOdRnhex+O4Da6rg1DTKIC7byrSUu7ezvZF2R8KeAIish9gGlEZZBWaripJoL214hhmE2X7iHO+JqXTTUlGRfo/4mcVsyRnmMnNOQ0Kar5K2Ska6Q7BjiNXIp3wD5U+QRlrRNM6ToaIW18vNAqvg+3LuklfC+tr2eUqL42WsybHvY19J07vN2ylhuj46in04kXPaVPxMCJ4o0905WZ72YU9ezmGGBBGs1IGSVTgPdF6+tiGmJ+cvV8YLHZyf2rwyVnHf47g0pDHkeE9kTYNmziVCFwhLHQwT4V19Ys4JpKFpZqL1GSfbTJbH62BbQVWc17TJeH57s4hfflnOcUSbhmrR8oHj8wBfWCfLOUutqypnJVCCLff0fhDbCJprG7wCQm4D7tBD9aQIE0qrVlWY9Kjt7ujcNVx+3yjKL7C6tgzKwXhht3cPZ98XmM8sbEplGl17sNkdwLS+z1YuXAA3BX7yB3g+U8iWKldj6lPjrg9gT9vVwD9Z8Llrau5UWyoA80XMbEB8nuYkVE058PnK9HTps9l9xTDHg7iCaCu1qbSAsk7nnUY=
*/