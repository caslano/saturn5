//
// Copyright 2005-2007 Adobe Systems Incorporated
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
#ifndef BOOST_GIL_UTILITIES_HPP
#define BOOST_GIL_UTILITIES_HPP

#include <boost/gil/detail/mp11.hpp>

#include <boost/config.hpp>

#if defined(BOOST_CLANG)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wconversion"
#endif

#if defined(BOOST_GCC) && (BOOST_GCC >= 40900)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wconversion"
#endif

#include <boost/iterator/iterator_adaptor.hpp>
#include <boost/iterator/iterator_facade.hpp>

#if defined(BOOST_CLANG)
#pragma clang diagnostic pop
#endif

#if defined(BOOST_GCC) && (BOOST_GCC >= 40900)
#pragma GCC diagnostic pop
#endif

#include <algorithm>
#include <cmath>
#include <cstddef>
#include <functional>
#include <iterator>
#include <utility>
#include <type_traits>

namespace boost { namespace gil {

/// Various utilities not specific to the image library.
/// Some are non-standard STL extensions or generic iterator adaptors

////////////////////////////////////////////////////////////////////////////////
///  Rounding of real numbers / points to integers / integer points
////////////////////////////////////////////////////////////////////////////////

inline std::ptrdiff_t iround(float x)
{
    return static_cast<std::ptrdiff_t>(x + (x < 0.0f ? -0.5f : 0.5f));
}

inline std::ptrdiff_t iround(double x)
{
    return static_cast<std::ptrdiff_t>(x + (x < 0.0 ? -0.5 : 0.5));
}

inline std::ptrdiff_t ifloor(float x)
{
    return static_cast<std::ptrdiff_t>(std::floor(x));
}

inline std::ptrdiff_t ifloor(double x)
{
    return static_cast<std::ptrdiff_t>(std::floor(x));
}

inline std::ptrdiff_t iceil(float x)
{
    return static_cast<std::ptrdiff_t>(std::ceil(x));
}

inline std::ptrdiff_t iceil(double x)
{
    return static_cast<std::ptrdiff_t>(std::ceil(x));
}

////////////////////////////////////////////////////////////////////////////////
///  computing size with alignment
////////////////////////////////////////////////////////////////////////////////

template <typename T>
inline T align(T val, std::size_t alignment)
{
    return val+(alignment - val%alignment)%alignment;
}

/// \brief Helper base class for pixel dereference adaptors.
/// \ingroup PixelDereferenceAdaptorModel
///
template
<
    typename ConstT,
    typename Value,
    typename Reference,
    typename ConstReference,
    typename ArgType,
    typename ResultType,
    bool IsMutable
>
struct deref_base
{
    using argument_type = ArgType;
    using result_type = ResultType;
    using const_t = ConstT;
    using value_type = Value;
    using reference = Reference;
    using const_reference = ConstReference;
    static constexpr bool is_mutable = IsMutable;
};

/// \brief Composes two dereference function objects. Similar to std::unary_compose but needs to pull some aliases from the component types.  Models: PixelDereferenceAdaptorConcept
/// \ingroup PixelDereferenceAdaptorModel
///
template <typename D1, typename D2>
class deref_compose : public deref_base
<
    deref_compose<typename D1::const_t, typename D2::const_t>,
    typename D1::value_type,
    typename D1::reference,
    typename D1::const_reference,
    typename D2::argument_type,
    typename D1::result_type,
    D1::is_mutable && D2::is_mutable
>
{
public:
    D1 _fn1;
    D2 _fn2;

    using argument_type = typename D2::argument_type;
    using result_type = typename D1::result_type;

    deref_compose() = default;
    deref_compose(const D1& x, const D2& y) : _fn1(x), _fn2(y) {}
    deref_compose(const deref_compose& dc)  : _fn1(dc._fn1), _fn2(dc._fn2) {}

    template <typename _D1, typename _D2>
    deref_compose(const deref_compose<_D1,_D2>& dc)
        : _fn1(dc._fn1), _fn2(dc._fn2)
    {}

    result_type operator()(argument_type x) const { return _fn1(_fn2(x)); }
    result_type operator()(argument_type x)       { return _fn1(_fn2(x)); }
};

// reinterpret_cast is implementation-defined. Static cast is not.
template <typename OutPtr, typename In>
BOOST_FORCEINLINE
OutPtr gil_reinterpret_cast(In* p)
{
    return static_cast<OutPtr>(static_cast<void*>(p));
}

template <typename OutPtr, typename In> BOOST_FORCEINLINE
const OutPtr gil_reinterpret_cast_c(const In* p)
{
    return static_cast<const OutPtr>(static_cast<const void*>(p));
}

namespace detail {

////////////////////////////////////////////////////////////////////////////////
///  \brief copy_n taken from SGI STL.
////////////////////////////////////////////////////////////////////////////////

template <class InputIter, class Size, class OutputIter>
std::pair<InputIter, OutputIter> _copy_n(InputIter first, Size count,
    OutputIter result, std::input_iterator_tag)
{
   for ( ; count > 0; --count)
   {
      *result = *first;
      ++first;
      ++result;
   }
   return std::pair<InputIter, OutputIter>(first, result);
}

template <class RAIter, class Size, class OutputIter>
inline std::pair<RAIter, OutputIter>
_copy_n(RAIter first, Size count, OutputIter result, std::random_access_iterator_tag)
{
   RAIter last = first + count;
   return std::pair<RAIter, OutputIter>(last, std::copy(first, last, result));
}

template <class InputIter, class Size, class OutputIter>
inline std::pair<InputIter, OutputIter>
_copy_n(InputIter first, Size count, OutputIter result)
{
   return _copy_n(first, count, result, typename std::iterator_traits<InputIter>::iterator_category());
}

template <class InputIter, class Size, class OutputIter>
inline std::pair<InputIter, OutputIter>
copy_n(InputIter first, Size count, OutputIter result)
{
    return detail::_copy_n(first, count, result);
}

/// \brief identity taken from SGI STL.
template <typename T>
struct identity
{
    using argument_type = T;
    using result_type = T;
    const T& operator()(const T& val) const { return val; }
};

/// \brief plus function object whose arguments may be of different type.
template <typename T1, typename T2>
struct plus_asymmetric {
    using first_argument_type = T1;
    using second_argument_type = T2;
    using result_type = T1;
    T1 operator()(T1 f1, T2 f2) const
    {
        return f1+f2;
    }
};

/// \brief operator++ wrapped in a function object
template <typename T>
struct inc
{
    using argument_type = T;
    using result_type = T;
    T operator()(T x) const { return ++x; }
};

/// \brief operator-- wrapped in a function object
template <typename T>
struct dec
{
    using argument_type = T;
    using result_type = T;
    T operator()(T x) const { return --x; }
};

/// \brief Returns the index corresponding to the first occurrance of a given given type in
//         a given Boost.MP11-compatible list (or size if the type is not present)
template <typename Types, typename T>
struct type_to_index : mp11::mp_find<Types, T>
{
    static_assert(mp11::mp_contains<Types, T>::value, "T should be element of Types");
};

} // namespace detail

/// \ingroup ColorSpaceAndLayoutModel
/// \brief Represents a color space and ordering of channels in memory
template
<
    typename ColorSpace,
    typename ChannelMapping = mp11::mp_iota
    <
        std::integral_constant<int, mp11::mp_size<ColorSpace>::value>
    >
>
struct layout
{
    using color_space_t = ColorSpace;
    using channel_mapping_t = ChannelMapping;

    static_assert(mp11::mp_size<ColorSpace>::value > 0,
        "color space should not be empty sequence");
};

/// \brief A version of swap that also works with reference proxy objects
/// Where value_type<T1>  == value_type<T2> == Value
template <typename Value, typename T1, typename T2>
void swap_proxy(T1& left, T2& right)
{
    Value tmp = left;
    left = right;
    right = tmp;
}

/// \brief Run-time detection of whether the underlying architecture is little endian
BOOST_FORCEINLINE bool little_endian()
{
    short tester = 0x0001;
    return  *(char*)&tester!=0;
}
/// \brief Run-time detection of whether the underlying architecture is big endian
BOOST_FORCEINLINE bool big_endian()
{
    return !little_endian();
}

}}  // namespace boost::gil

#endif

/* utilities.hpp
dqEzJfK2jOiCYPtx8pHLY/bLdLMNu+Xg6uinnPCpYiGX7ypknPB25Ahv7Pdtz+H8sRdekqfU8fhgv1dfqsPxS+olnc6bUpl0Ot/Vo/TQeUdztr9Ntox+GKOSPX1KxryjOd/mtmT0o+3nk73prNIXFtKMKWenKycH+2shpfSFhTTl0Fa9ybFV9+eKff3dUk5T/fpqK2xPvD+Z7U5lijknrNsCNvONVyd8OpHPqEvZ0eGReCf8KSt8Ot6XyvRhTCj6ns8uoWMLtyo2s01sct/nS+V706m8Ck+NK1pIgm1isy0jm+kr9nZ39ygZtGVFy+B40LHZGQ9SXT39XVmZj6gmxTRk3DRku7t6UkUrH64QNx9jjgxlKepJ9ob5WICMQ5ud9UN/r9I++4QthremL+Gt6UBGt7GrWDL640UY5nJd/pptfimif5y05BTiMB0ksJ4piHVItCRnrD+72bFh9xf7k32ZLn+uah68g2/CbrHzk+3qyeWz4Mg23jw/od5iyenDXKuWksl0fH4pceotjoyebF8P7IFZMd42lcHxYouz75NRTjZ6QidvjYuyDr4LbYXNxXtSXZmeZLEo7L4RUpw3RW0ZiDZbzHZ3C3thcxkcNywZmHbVqJFIa9tx0+Dr+K6kUwbdsMF1Y6ElHd3ZQcV4sdVOfz5RyMGg0W2XQbQU6jCOjN5UJpVM5ZIRZdB8z8mSkfEfwSj09CVZBtHB15m18emncu7F2dzyuPYU728X0B/FVucMUQ4tpS+ftMuJ48gWjiNWuGy8F1M1yqlrjjJq6C9HHRn5XL6Y78qKsai5DL4/v9XR89QbhsWutCwjNzh1YyfvvX2woCf7iw39RJcr36Jz0l3o7ilms8X+6D4Snfc1Fzt2w76i2mvIRPeR6Lxvu9ixv/ZnC/lMoje6j9j+hopW2CJsAplcui/jjL3NOxrviDhyirk8lgrJRBM5DaYc2mgsOXnkJZ/NZ3ydawGjhrDROHKSeRjmMvmeSDkRhiXaVC921uKZhDomqNc/MiHRelPbNjs8dNDeAoZyO7ybgFDv6bDC56C3FbsLOd01mqXBmeuLjoxUHjNboSDmo+YJ4V6iI6Mri5Gst1DkfLSA+eCwIyPZm8qne3NdlLGA9nFsm12vqUQmm+jvUTbmBRRJ2D5OOXK68j2p/pRaHiygUOTbeJc49p6uviSWVoEHKd/z3SXacY3+r/P+aPsljt06Uezv7u8uMLzRqqV3Uy98yz9uhc/Fi+lisb+vp4deaEy88l+OrWe3k4buPBpZujtFGTINKrTjy2/2Evu9pZ6eTDKZ1A6DqYA6vstlmG2owP4+KH2+XyDrTAjt7FYau+IZ2FsLyZ4eMda6YeO0szthe3vy+UJPT45jbERY+u+y89bXh8VoJp1XQ6sbiuek7npK+skMzuunMl7czMePsnFYqrEkDg6rP8zIGI7ieOI+5Cc4p0ddIk8bOW2fIQ9XOnhH/KDB26PkeCF+4rPEw+cpK97B9Sb856Lwku+oA3CaPkGfQZ46iKldtATXie5k0nqDkFUe5ff2MA84b305zz50fFF9F4f8cN7WYLM3EquPzUyPTl4xQXnF1xDzvbaaNB5+mfnOewg+Qe4znDxhOLyzoM+Lh/dHT19inx/sy3SnYbrKLfT8IHy7qvODaE+rzr3HHZqdqwveGUrfEXn19H3GTaxf/4zrQaQGoTbhzDAOq4bnUG/An9UR79pkYuo7/Tvsww1t652RWxVOfxWWCyDKmG5p5KDhhec/I3B9wYqc2iJw5rnv5S0mR97BIv4oiTO4eDeGOO9S8T7J6BIfw8nvGjytXoHrUMHbJ8r1BC7U8FznGcWLbi/k4LwsOWOTk3U=
*/