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
HUxeXxM1HdA0GV6JIUkdJFL1GoJpHrT2HpCJKWlpFh5oJsKhLLpqKgX0Kq00LcqbkbJskLp4k2Zs5PkOGiXawQQDECQDHNQ6QiCBWqenFGmRL48SYcmZZJkB/pPojgP2z9XktKPpxgD1YaVOAwWQL/DveOlOpkAgDdWBEm6UAtynAKfaoKQUpapJARZcl5LCHmaARJmHd1mP7ZxWIntU7n0BXZilRMQIkpPDvzKmhLKlOFmnTn1ngrJWqDJCeW9SDZBAMuPufGUmyLZozuzu3DizAveSAgQqJqBHS/4H16200O4K8O5iDmJqdZdm9SZlTqZsKYZhpVuFcKc/0qxxmGWae4UXAdeR4J3j6Zle4ZMxse5SypsMaX73H6BXQnfRUs3zisv5/DWv0TtRwX9Xr/XXMmVOcm7CB/sSrTux90OikD34o3G+c4R2FPjfEyugefwfWd/hGkpp43p5S7v+hcpmXNp5x9k8/NgMfsODJoF7gliwMdiRmRj3rliU79j3fkbMuCyL8SxoZUwLnOwqRUy+3rbWn7ILg8PD51nhwrEJ2+zIen7KtziHpz+miKelC4lkUpym9zmlFmREtqdi3Rr9xWl3ulwUcJAjEYSSbwoCsiQiBUDJnTUe8KSIUSCOz9q+HGXzV+R7FOCSXwvZgBq+QxovGdOOPMA1RvrNx6naEvYOyAIOQVoAEOm/pvc3WyqRKSIHBTYRAPdWMCNW0TEcK55VW7W4RlMbJvLIAoLhjUbXQOOSgnpGOHzOgzmM7vnQ3DgoRKZhr52DAU0jAfjQLCI/p9WVXtNVXcncXtKYHnoc1Iod7uAa0rOb8kcah6edD6dcOica0r32SX316N31x4DtMIjm8DmQS9NZaZJY9avt5hL/AxuA5H8Sa1V48J57DOW6d1M/aZv3+Jz7pJPa4nvAk2nTJ9+oPSe6nu7lPm2ef7pj6rLV5XmZ64k7nvdcm3/2t+vJlwAvqLQHmfTT23l1YoowOSJLCzaR3jlJhcZ2ju/e/NI+eVk+rIFMooGPWb77mET5Mnz1Fe72I0L7Kkn7qwX6cn/306DxkzcLsAz0N6AJMLn005IOtM7zf34ZECztGxgY4HDp323KnktG41VBiwJS5kvTJVTT5n4XKwrU9Kqgzs8L1rKTK83TzM4Ijh8W07ILqfkesrHH4j6A9ONkD9mB/zJkT0WHjJsh8/MAu99Djy/Dkzee82+G4S798TBxkHyz/qEwcI8ZHy+WaDOidj2MKIowdoMOyh7/RlQ3z/th95zYw++SHRJh/OgwIraYf6Df7/FyJoGPcC5Uhi/bAjgogvP8Oa0WHlrSBjf66DgtGFBQxT++ivNYEHFYiLe7Ygkwf+gmQxwRlBBtHp+zkGAblJhmnpC4EBdJm1S2kFgUFPe8JwnfKOGHcWzJVfI72sSRnmRfmZTPQSnTPSm1xymLMi9+BL341vFi5+rFT5nU3oX446uEy3yRNBDNJB4lZuA5zo4q1QB5r0wbhaTDsNKlklHHVIRzmkfVqvDVRmuiWOl4gqmoezOf7tOEA0hnukOXAgO+7EWnkeX0SefkmSGZC3IEZYXV2NjVezyOykM/HrEcYTEfW0ObRNm/9EcSDzLu9/ssJyFf60voBjGtSUR/y2DYx/jYXaXhZjM4ywtMPEYLmq9T2mULM/KKWoJ1PgQXNfYWfdUvnr0qnpApeVdQPBDMOb9YvBxcXNZbTEFV+udx6bRs2bfgssWC0gE6UTA9l3FBeTQGSSKXQ1FYTlVYQUNP3+4Z0DCtx/imgs6C1s8OPPgo97Yys589QCHETL2abRic79JPzrFJF1lNN57OZaiVAx+Uh1i8dCl86a16GIPOduylf3hN6/STY5W1VqvaN+iNh7pctRoI3LPFookhcF4nN7SIWH9Ro7NZ5TJY8wxU4GHR2F3YqAMq6GdrZBjiIgym0xpgTHWNTPvkESIL16qm87mhFenXM7bj894gL1wCNfGt/vrDgbN4ymFIwF55wxL1ppFouZX0lvt1Jv+D6Lr4JQ7mEC40WoFxK7RO5FXEBs3mb/yZIVqtS6w2q+C7pR+qKq/IljseMXSupZMRbjJ9FObYnohDx+cIDIKOLDoWP9caWXYHFnUbyD+oe9rFv0kugUIIrHcZbN5pR9U9L+otWu5dazVHqHddfgFJYPBSbnvbLfu65TubnUc1tdjj+nr87Xt7l99+ZXjnHz/0to+tYbl+mfB1/ZuG2aL3v5ffN6q9qX3OMczQ13LzHsfQD2Z0mH+eA7fv4cVyT45+gBYPMKwMaIBZPz36ILiZ+QVFwJxP3/KmbajqLcvKkBLjcGJUQtI+PqrCF+eoSbBCNeS0F5rwpqFeZNjB6qPLW+6EumENdBwfCkCIGUmW+62HfqUc/zG+eCzZij3TktX8IQcP2ygUCQ5R4LJ/gxxcGmtc+USnQBQ2EpoOCyi8G89bYUso/NRSPDmx8n7LckIjJOwravQD46Sa/eRnqy97Cn00VnW3g3U8fUhzldHgUI5qxo81hV/wS6a6lz1iQurCR+qENgWXQ0d6ne+k+qa4S2a+FjXLutSJ/avZef2Z7C3y499Gfus5jQed/+RnP+xOEW/Cncu/QgfotJjmHd7NDYVW4z/h0MR+C1yZdSr5/vxddyJfpZllGKG9ofyP72lMiw8t5cI3aKdC1JKsv+OyrJdq/4kEv1kk3lVVBS2JY77X/1j+UILDAxCxTLKVvwO8YVqZtf7hvWeGWaJLK1iJLQKlhP34/WP1aXyrhtvoxfPVqn+rOKb1zrEWm5SF25JlMPMGBfMH/PdD2uMr09Yb7DabxJwfPuut/gzbFLfZiqjeYGgyuWXclLbZ1rBRDA1ZVindNrLZeTi0fftvxYx516FUwoJ5y2l199k9v+vqmnfp3vN7rqbPUdySI/yAnbDV/bTwFTlmU7P1NxmrP8uYD0kmolhjKT/2P65g/l2hOHyfyYAApLUzH4QpdhOhF4ZWD9LCD3BA4JfSPyPMXJ/e/9lS3B0tpXyyTj6jcXgavokTb2ILoqEWwMALbf7iK214pNRLgJhIGfsIyo6Bq99V2Syn2n61vD/mj/hBBz+2Zl2bXz2RXzteWz1VWVudLT1VWzv78ODPxv2ZGcviz9XD49Jzhw8z1/f+OMUjGtsL34gpYtySANuxJLLD3/Yq0HYRuSbDbWseb3vdyHgaZntqXXGWZ3uzo3Beu3bzufisxfa2+e1N99pt/Mr53/vb0bUBN1zgU9ujcdt/f4ouG/cvoyP+bZW9Z2E5Tlv7lWV7f4rrLfrwFzhIJWAGu6dTSBCpGIyFM8iFwkQrhxMp+S3eJohWfXzBKB9yBxOrHsvg0ClUSBSr+ZQDi9Z0HBZ7OVkggfNYepsoXvulROH5zd34tNNwFCqZ/kGSRP1MjW6RXJiFEY9qvn6jxbskycb5Zqs++pxf6dkvdHreFj5Ilmpe6nyy/AoOkhZaiG7tIY5xspuEE3ne3vwjkmldH5DfuRef9Fr/oEPPc8QJl329PZ7Nj4t9LnOINsdRZtGrRGJ3pqt1ihRfFNasfCP+S65LLN91sNjh8fWpZmfX4Y+3z28PQ4pYp9eGkxmUUhWcj2J7s+QjSB68OcslG8ksSX3Qd/En18zB1PzSc/XdykSRUlp4o91wkbWg553Mu7vrs9+/hyeZWV2+lqst40gxWBDezo/AP8QSK1hCoTFMNKFgrb4viZ6mHS52XzlfP4rac8wufswuIT2GOVXTPrE+0jXd36lgzD5ZyGb3h3MAgYRNqPBqgkOqaXPtY/tD0d38VDSJ1rbB1Xn+VPhhGLVFhp4iQY0PFL1fGGdgk+iUy1rhmp5gEU7gnI/wvk7LsS9NdM53DClwLvKUG69JevZFay8Z+omn1EZqftyljOLEFRmkNLjnUhEnFuRY7uff5RgRr0j4M9TIkHfKI8MmqT7Uw/mTW+1ShtvL2srUX8svq0uTfnl6p3baN7x6r71Ysv45Ia+0dTWJH4M1vLFJ770nbLJIxKvdVtK9oXny+pONpJtHTtybJx0zUk6/OuZtGinrFjwn/jz6FkDkqd8j3hxS0rNb2ueU0r6rxfzm8L3H9KsvF2+4316s9k21Fom6N1Vd3RN5tSuywbwG8IxoyIrwhVNedcGV4H+7EY8YhXqbDVNEu6wsypX76EapEf9/kN0xb0x6Gk4xSlfzv0AEk1GD1fj/BdldFIGpmMP2jxi1O+qm/w9kF6QWl609w6FdZ97u/uNTZ+P3FsxQ11kvok6/zXW2wXqiq3m5260miSO5dVurJ+j014+J7pa1D34Uhf90/geyS8H/nifP3box+X9Hdl9FkpG8n+xt3/tarqL0ROHk2Hq6zqjR5vObZ7vRRZYTpQ/7uv6UVNtSdDw/7/q71h9NFF/XhznYGMvityWR60avTv4X2X3n5R012uix9uXdc6M9k0fPcSyP3r8NLvyO76z09f2720uCgaJD4g/v/93uzhJZpX34gMPxeoN1NCG/4peN8S62MzTHaVW1RXEo/PUYSvXLdaVWCPCTUrlX+yelRhiMLX48ewHJ1MoRnSxiFMyBEDIgyGITKu+Pso8edIWxPWaIMqxMoCPsYE3m2aU1TGN8SQtJZomCkAuswDoIhXoWYMkp5VYyyGSG8PzJHHbPoNy41icwuzRtz3y7eMMbSkiMIZsIJtZvnq4Y++xefFgJBECO0/gCbjQInqSLfqHZgiTts+jenY4yJnLdjLBE3Kl8ZMnEk8OnN6akdyOPTz3VoDRYKK+v1hIhm5TPL33DW+GjigvhY61WJKyrjughi63auiL/yeJ6NxRTkX5D+JNFVNWu8WUWM8VIzWuupI/yjukZqm0fxCoEqlfCj0e4VfT1ieK32dz2evfDXzqIVsNA8Ry5dydf8VkmLVtQl4SQIfwKOGgIVXHU+Kj/H7lCwgDsVH6MjKXj5FG/BvxOeRguHzqsRC1992iEwUPh2TDiN7v+8PmM5etx7jUd4ffIRwInH2+q374ev6jUfcZHcFBECAdGpKvAXQVEY+khU+aH0wwvG89mEsKMdRGN6fYwGHn6UTLlORdKn59ij2hJAp/Ju02xOeHphSQFC1nSggItvQYjvFgZkOmXtTxtRSDWfLkq3Ybrm1RyC2VNn8cdHX39UF7PpM2DY/TqV5K/c1ATlrybJRLPu5yZYJ42t4PyFR/xdylqaLaNyECr21JW/L9/JluNzOla1yiHRBI99hz0lEe/2ft8+RcweP1VzOLuVI2g78vtIz6NxJKZkTQGDnV+J1v2KSnZO4fPqGn40IRSHTYtCQ5aZNPfJoFt998cyCPBfHX7/UQ7soyIJAKOt2SegiMd4X7J72eZoo6k5MvebrK0iACUYWP9vfAjTRCkFDLrz2k4uW6dC4vbGNx8+4Jq2x4yPQpUbAXzwxxpVpPjUIM0inQ9wmHpyRU39xsAahlMqMQKUAz2GkA9ZY8v4LVBgnPvUbyqiKJZ8FIjXxXpsD8jdcNFj8tb6L8wMz5OahHBV7YZGHE/qkqyKtZQnhwgEXoPAuGwWLoPGah0/Yzku4RhJXi/mhSfV1TQGUkKDFRl36/pbsyuvPFaKiHebvgJg4qjNmh3IFKmyif3Fl/4fW10BMA+VpgDnwiCTo1Mr8oSWXG8UliPVBRYZ4m9w1/AAw0mdxo+mZVBA3r6o46b06A5Xv0k5KKJ3o5I4ud8mjNj0BrgZwIVWPAW/8Vxmmb+MVWG10u6KoKPLhZkL0Bk+LR/69SFGraQoyJbVNYieUudQynXPQPijZGfw7wyCoJTXII1lakN7wS9OKc+CXH04ohOB76GrsuvodikVSN70pEZt/iU99Mx+5I+yPm+hU02+66kJGWWWVcVCBZLaDkFosq6QuNtttaK01bTKYl814XBKNzoUTVmb6sUXD6VzNx9DoIeL5m95s5iTxjIgdXX6Y90SbWFYejH8ofIX6eDskjWWR6F8aENtYtX3n3UInLkRe8aqAXp+3MOMXI9HJVjpC04Z3nOOA3dyDGaqcCDdSASePXtlMrknjiqUv3aHP7YyT6M/O+/e3qO42RvAo4GIuAIKSwmA6gmwiqE4CYZ0158dw1JN+mzUI0DaiW6+iBFKGGU2AEqi/xcZNfVqlJc21ftQpTfd9qGBUPvGEEcwLQV3goAEophgRIqDSA3PGPRKPkFWdVCqzMNp7zGDh6oXfcl5YoSzEXmoySkvOROg7t9Im+KzS9LALDJ9bQCbHlgT5MNHgR+yU3SHwO2hmuCwbBWS5LmTbckSXy8e1ardbHtRnB1yQFtESIiIYv5JCnRKn9ifRFAoIm7Io9JoMEfULZ3psoAXh9VzsZwnLFcXuEjkLUTFy/+JvT1f2QPESXoN7SnoPRiy5NQdWijhvS29GOfPZ9wwBESsLLRa3KkH+lyIMsHNG3oeSGZKQF26YSGPCuqTRNTQ/qLyO0rO864sR1y0ulYjW0ov9gxAbAuNUK2oaQQP7MjbX0cB4XFcHlF8lttMEMo/47FS14ek+QsLXwUGXDPxBcsQkrss+RzKlNWI5MiRUgFaBjwiFz2f5AycIR9KddkTcM8EEVAqKStWBCL+EpM+wC661k0Xq6yreT3hUi/gng6y9Z0ZN1pAdMCoCKQ6asiiSOdt4iNIkFtC0T1gEU4eoyP9cbNDRsSNyWkeZHySfLjQ0rW1AV1Tig6mXhIJNu7Ru3M9HFLclh/BQ4T504BSvhLrIL/i2lBSYjeUij/9Y/JhRFQBytU6srwPQQJzYsZYBNqTlD5oYAEKYIiiShVmWj1Y1ODQxHyNJDAt6bEbrBik0af0ADYTZBxMcd+ctbKQ3zcYo+ncelJVrLCNpEUbMLp8CTn+9sd5u7gL94kvqWNK5ECN/FQbEnklhYr8CxqYJA+V2pRrmTW6bmcQS0Z4LhXP0/+yhHx47uBjUgVHonXSn8S33mSDytIYQrIlw6MhSL8vevLmwmw/Y9dRaLfdqFi3eI1SYRvmRJsd98IVlaA/9YEvnOW/zVMjoRy7z+y+geG8niJCpnhb9DctVZKSkcAg2iR5A35yXzh01vO+eGjH/6Ipv0sqKnd4RIfYeo9UEc/H+3YvyCxmhpzYulbUNK/7OkO+xNc9u0HbvWqs+zdX9+0u02+D9dfScPPstae75vZ3nyvDT9usw39N0lAPTo3iQsfJC06zhu5I7xWvCauvD91cP33UfkDZlv4/rKP5e4yXilg3zb8trYMd4CPfYLH1tNqSufnF431I+gHs5T7AY2e1k+ZGWrIuQzZVEzZPNSQI0IAt9MDhaq1JCVUpY3dpxHE8+ngaC8AfruIo7hcAo0/FRXhhTgxCgMdmiLaiyWc9lIRQxGFfXdCXQW+GQapaqqqnSnWjxDFmoFlp/Aq0gH1/cJK0XjE61B3BNEjCCEkXhcbpwtpY+3pJ1amIQvYdYCQcdpckSZ3siqvs7q56o756a5r4BtERXhphv8JjD92iQgZcwRnmIbR2kXUMXvLIOLjTGNg8eFXbIn5cfE4WEJsT0JCD0sGT0KKZmKSa2KWecLoWcKLhcTohMRU2qRi14Rq2oRSnqTyoMQankS3WEQPyvZNjaVOAKJNE9BO69XKk9xTl9w1ltzRk/yONuWDTMp7V0R3fnJnQkp/UAo0I+VdT8rXhZSZMY05npRPCS+m614Mj6V8NH8RoflicBYpYkj0WsZvCyVBfQQlB+AD1lO9kEBuZeCfq1Sv9VRbFKBzHXx0lfq3LvVgIe2YB0aNAt4vpF2bE7kDABdBaVsIEM4LT8srjTI4jdILz+iIwEkE6DSVwfgYz2Y9g0k2E8mbyRicyfQTypOYyRGcmXCU5oICZnql/+X5r5BHifNKk7iGUmOAiiIkf2WAcC/yXvPsniA8Lk4EV2c2GV2GZi+EWARo+BhIoQ90QuWYP84xWQRQTf2nzbGqz7F+DLQiyHX4mWO+CKCcSjY+IT3Y1BBAEz4IJpiGsRuAWZ2/ZS2apzz/+SJM9sXa2Isvri8ix/OWXfN/wPIjtPKT6VJjf+bFExQkjudn1OfnaBVk/czvzfe29ObCISntB1kl8dTujQqrgwv5zkktKK2GYs0JK9iVnAtfJxaWaRU1qzi0uSF00rPdvFmLr4vgF0lhFSEEx8b02Oz+guJPBCx1e5aE3nijj4kIuornHpf8mLYkD4T7KwMpMM6UmJJ1utIZnJ0VvjJg5WfJZkHpLzrGbTfE7mKJ21HJb9mys0X6P48RfxNLz3vL7sbpuF2e93mXHi+WQSzKczOYr+nKBt3K4UvlwawsX3nytJHMJBYV1Ek0eIMsNG8qGN9QIX6Vpk9XsMlVWmVUKCtX8hRWah1XXNFV8t1Uinyi4AqhFrWokrohF3jDIBRSpbBUxStapUhfjdYmk5VDkItVaxZWExpSczdU691Ui+CXC2pX6FvUaBJWmxbWPLCoBnlXW9zUSCfVYORe8n6qIXtd5Vj4koPvpfvSS2r3lza/XvpYVDyRqw1wL580K3UNqQ1tKJWld5RCeBEt1cYUln5nZetJh1CjCKNxFnWphMURctyRn+rSLOo3guvAmXXJS3W5S/Wa1PUg0friX/XVN/UEkXVJ2vU1bxqI8RpwyIYm+katuHrXnIYqvsaeG/lXhI29S40Oao2FDQ3v5Zre3JThA+uitJs+ySn3uzdO3DRptzeOEzbP0TfXFtZ/sWhekmOd4WtavmkGzDQVEb7admf5EdK4U/hqm/XVasOrw08UbFE+740oWMjZWoyQ+ltFIIMXWTev7n+R+RrCH8imQRezgPHJD4LxQrRs0TRZ0PpWoBl8ry4PT4cQ9jyDaKKOUic72T1VQ7aVypII3NhKJZ9CupxVvd5GjXpNx+/H7dHag2yj1Hl9I9NGieuzhPX9Z7Q1JLGNOh1ytlNgfdUyZ5GMqMRzwxql9xvFZIEJ0vGjo4U/+SIU+o3wlYXXj0jXjzoIWrEw5SeQts5ZaOf6lJ3cTgdEWSbBAWEB7prt7IIYdM7GCnvKd/v0YfWWO4OnOkXSxYOey9GhCE4lpWu1OqbcXftOpaleImKrJauzhMnP9SkMArL5/XXNRJmkxPL6esNGeq2HJJV3evPl3wi1S7GIiMj248lMAYiRBJD02Ng+slP3nkcNeDh94BYKYTPbqwBEW2xo42NACiKEshgQ/paMRr9kgoYUMS3U9YgoSLYoMKs=
*/