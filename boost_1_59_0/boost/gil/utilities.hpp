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
oF5h1WAkXCdZrfvRE324BjEWzm7gC6eMFhkqXkeRkAVQAcEwTUGM9m3lu28GRmw2SOiPXbrmK7EGFvqlY60RIKBRL4SDrfCO5y3Z3sR67BMZ7JCsbiiE3EEROawDA4JBQHCjwi9x0Wkt7O+DGaNVdd3TB6Ne9S7k6hjYEh9tvgBWrZwt840lUP0Gd3fFm6i1RJ+ov4Y+6mCeBG2X3+XiQUOMJiRJvyb8trkH7m7zsuUk12N0JU3XMODYtu0JJ7bNiW1nYtu2Jrbv2LZt27Z1zpfn/Xr19aOxundXVe/aJWwgD9UeAgp1Gz6dYa9qEYUdbFvcs1hFSQUYcJ2+FNHCgScFflA6txL58j0Xfzt1jcClMU0mEdyt31QLpU4iBPM6LVV8kv0KDOteb8nR/U8Qiynueh7k5YNkCSqMpfJKZK18rw1ZOrZTz+gS/vGQFgWvzSxRzQjsMbGK6f7BAWmnA9jjSbNHogpiAg5bn9LPdx+KsDc9SIrhtfiJ5ZaARqTT70hmVTBtA+XSasbZwP+RSz7jma6taISLtBruWi/Z0b9lghz7mQ/7hC3CZPUy9OulVtdTIQzbhoniotSOO8V+GWaA107n5iMjkQuSFPsiMMLv86hB9gRbsHWIeBA1DbL1QUFJIl/P5TJoV3LO0kvhZNAs7bv0wHg9FJGOtSnAm2J66e+47zHQG9ScEzJB8poJQaeX00IByXTN0ojdlQTJAEWQgpBalw+rS7eKXNe1fTSSS6/bY3OXlxzyfVIsjBBzMI79aXdJcwod9oLov+sp/cfVIyxMo4LqibQH7IcZkH9BdLWIvEquh+wplLu7vkEhL3+e5BNUrPawWdI1uQ0WKVYtMXpMhWqTu9Dr1MeLHAgo3uIgWoVuXPZFd8+rVdPa3eKBLlfX8pg27pLkEd4FICgchn/HWRfS+je1d6UC4WZHko758LKuZJs2GroWyOGqoODDUcYtXp0WJGCkW/FE8tnTbbCRtIh/heAto0cUbFbbzEZTdnuveAVECuNMSN1G9+H18sx0GG84P27UBRCr8bpiM9oXVvbDncWckLX2S94YAX0p/dNoa+4mN/3SoBtv54J7zfzzdKvuFsEcCVJBrOnmcasPHC8P3fo/KF1XvcYyoTsKrJe1YgwCG6qhWQDseop279XqxqKSREvdEp2H+Ql2+wg8pBugzvl0SmYsEYIUl/n6e/DH5PiTPM86O/ISBLWkW0N48QXpaJcofZ2Dd0JPcv/xzWxNQn6gXF1vDA/itZole3bA+ciJTWO/VQUoQHB0kqiINRGMgTxe/3EJDf5sbweVHvmg3SaPg7wIXb9+HYFYKBUF8vzqQwC8oSvm5eSJ6tuuqfw3lKengkvJYz10MZpGmIyocdUwxisXSPAfjO7SK2rm+PlZYtCOpUV5KRNmMuQ7JhpicF14mEqorxXaOTAs+dFv+huB5iGReIVEGVGhGVaLyFXO5vzXgAamu1leXm838cWe7Pfi+0rqjWtiyQFnHji6IJOyuyyT9Z8/qzcX01fblYKiwcGFE8MqZeUYZ19t6vl2UeJuODhv7QaYJXkAXW42FmkH2ghsGGvumPHQeYu3DFh3/G30l8OzDGNzkeIJ2TMS2cMWRUUzi5kG1OXQUCbM/H+QIOUD1UMMkcvYZx9om6jHxLW1FZm3GVFrqDOjCVX1JnfjPY7/PTUw/grIDAZ95SAlVEvtlQdlWHYbFXnzLXUWF9NcxDOuqJr5N0wLnSpKd+w8eGo0ViUWSe3fUACz6vlCA4aPxyzp54ZmoqurJyxivPLdX++TDqqnYm6wzEvM6tVgGn9QDPQH19xQ+a/RM++Xg7Nj2EFJ6dN9cOWhtsWaU7z4MUUQrN0Wdo9MEiSit7aU0nE5erivkunnyLzkoLP5PhXc2+t2ISwy+rBpR3KI+QCS84lFByZpasoxCjZyXtGILNZw+NInBXJ05vD7JncPtOVNw7DNDlND5wBq9sTUWc7dbMImXRyFxXMOk2AChrbHrvM/p97SmyGDdRyXzzS3fDnEX6wBmzhq50+H3oveKZJXfda+4n09RjZY/WknaGVrwnOnUe/c2wdnFClvuM7SzB9C6b7EA7y+KSZeGCNvcAc190iXtifdstnlA3/zlgCqHUgfRkZI93MpLsFlAtcRxR/+bn42D2t9BsD7G7PPv7z62Edx23+T5TVmxepKo57t74ymN/Z3iCDxBHuQCTY2/4qfqL0HOeIDHlS4qjI6lMCfV0zGnb//Il10SB2r2I9nq7xVij3/rWU9mk4yu3F8v+WlPcl0iLmOuT2ulMWSOysTuBnYFqqTS21or5p18+OLVG7x9XQgyYORf7o6mMnNNtGE6IvDF8eWFY5k+Kf8IKUA1moBtvAx5kHxaVve/OvlQJIPqrGtilrersbsdgYp/o2OrQEqPdJKSHdZdJIS33ejR9a3lR3b8PnFHaE+ehXfcTY6ddPvSU1wyU7RIp9je/esZq+yw4koPvcAJfomuddWVNxwzQJMETJ/uQ4P2Ewo6OzQ2KPMMQM6n6bVVRFmKYlinaTF/7nkfabvtB2Zj7+pZY9MlTteAeGjYSMCUVkTzccmxCL2d2r/z1uda9Xxbt/2+L+40ngaOvA/B6UJLF1cD3GB/6191u8lkonG7X8v7ep77pnwf/yKLArQojTPqRBc7cBhOaAuyJ6koEJjPEukJ8kZEsKvC78dF3LUFX6d/sIfDQE7n+TSUtu1EOHCV0+TF28ho+8mQk9zpYdMq/6aTdaSJfinokcv2MPL6ArrrhNNxnp0cysvR2I/Ppra7ikV5Ll7BU/aHZx4BjZ8EpcrGFfwDu2b9GYIZcJZU2FMvR5cW1rLzuqCFvl4mS5wG7u5BhFzh0gvA6eNWK+wG7o5wCCEcBG37Xj6ezonXsuJBikq74TBZAlZzH94MnWZGc7oexxHKA2918jd4br9YWpEUhzaDDUkcEFyDbPDzHyZL+dyPoFwtEsHppSM6kbmsT7YKuf5m+y7j3i0+C7reTHsPxPRraPtAr43bMIRNdziR5k5+8NGe0aYAchct5gpl6uFa5yqpL8YByaMgq6oI4jyLDtxDo2zUw2F4/+oA8vvnHobwHJks0ck2ltey10oXSJXFWbYnHtZBr/SK1TKUAURzQPhbLwJ2MoKnHu8NxclS5+s5t9dFAgPcU81kX55jpc1dDZUyUpuGWruh2wS4ktPYSMgOm2RQlXIxfKcQy6FbzVEuKzRC5KHItaDjAwGGu9HDGq9kvaPNJ8hSGMNvTyuGbOIm47uJvlA+hanNa2iQn+ZJnk6vo9a5YoBPUYCOwbV6Wi/WbW37sm+gDVaz/3fFBw8YFrSsSMTg5uWaLYrSVvTezBlxK3//SN9qIHGc2WMgBABkYGtDzXRBbOvV45gRk8qrJSBCw8/1Sm1OlDZy//H7qJq+XGk7qs/cEnPYDgKNtBAFP22BU9zSDMlfj7sIzl19nZl0QyUWTqCNO3kOLtni3eVmaW9xiocEGqF1hUKgx3mRUDkDSPkGfUEaSfZoqfxdFblJaiN1/D//k6CGYv5LPPUNeikCwgR+bVMZ0jD6VC7eXhVz1RdXoAULYp1nF8qd6Sz7FnCEwSz4MbnwtlZbGvGwzmtp1L2My9vphAFQq2fP/D05r73cP3FJ9vAMj1TekyCvXMVGxNpmTUuxmCl04UlZN1PflGTOmKe41Nau5VSUBpJ7LV6P1E/tOu1wMK8naFFKHSywc7EFoYVIvpIvEsGIBBqsHBeJLk7reXloAICS4PD+3DZZOI9SkZ2BvODCp5SgeR5BH437ZynnFG53zA+b0F/4KHbTg/ynw4Q48woUHlt7tUuYptnKXG3XMn+Oj6XMaRmmDDzolrcEuTeSwhvo+N/2eX6Lb6gZx/a1O/PqBgISph6X/TcTj0BMA66+rU/wkUXpG3tHr8G6uTrezI8vq0QNyI/52NXa115TrWBorO8AswyjcjajrFvupsN0o1K7fHQiVZc/766fkEsXBSguPnWBCx+7mM8qvfkLKCBsfisEaR4lU7Z86gPNRe5Pd3VwTmCeD7fFGfnU4DzMEdGmimZNpobGIEbIcRqMS8uGcQXD7Ekpg6qnEUfGFrtnpuNEVGRaDF9XrwNbJOlvBc/aj4jkb0cGe20KJSEfJdcnauCireg/960t69+5/0MHWZnJRLhDcS3XbKwV8R0ZS6nluIsXXRLObE4CHtghx1//QIgkj+V9VZtuzki/zJhr1DZekEfdHfZPPw+RN+FOykm1FcQ3wix6xJuEAuNiR03SZMuqYH7+idEuEQLc4T+FGMhIcwGZpHEllIHeXFOXGoLTHHtff6kKEfmVcKJIDqOl6iwdyPCsiMC/sFrinVf/WSu95QFim2c+2fbG/MZDRYbteq/ulg76R0tvcDC3h5ehoX1XABRojALz3nFH21NuzpkrYp9khpDSQeu5FDxIVP/7U0iY8t1XxGtavqbBfy72x+ypNRpfOMeLtcsYKsEh4L0bs2TeCxH6yE4SnjkbHfkcJe3wy+YrBnu4yx4gsHtT2wqgLdm/bgwQQJjF2YrWleH6TtfZkog05SSChBm1QISEPcICCn6ys6g2z+/8JxQF6Vextu/6FcfID1C2rErW0z+sVKfg0yJ36KHiFP0LDqlDc+J/DtWudkpyiglh0CLFODbmvA1bTDbbv42ffefYGzRVL6/VqgRhRtD50QzmczvpqTOkSRwYt3O6vaq7VLimV+8xN7Bb7xhjbVSVZC7Hr/+mjUmZbm2Qo6ov30rqzdEWpf/pjUSetLGOowcmL120jiSGEnUAwmJaiwQRV0cjLdurZiKFztasi01nhjgACxvOs7sW9y5qMNHrEP5exsAoyrlWIamw1Bw8+L0P7zzjwMuW76DKreNDIrZn0LoYDKHpHver2YE1fx2wivkH6q7BcmrAF27zXGw+evJMfHpaIrPJRr/mCAofCk3v5JMcFL0B82hiCI+YSAXs0iPfFV8Ob2GzqAF/ao8R2j3UTlXxdPPEcYXGWiQpAdqG/iIbMrKyIW+kNw4gZjgxWws/VbVgc+OWXohjYB0Snb/8RmWuy8+yGM5EL0PHQ2Y54g+IlO31rN0eaTjxowS5plMi/6SSsduYiXxXo/4F03H6RA/B3NZexbN1vYEMC9vMEy+sKAz0KH9whMd97cj6grNTT9e4+MUNdCqqGo3YbAMLUSNIxfFGWJuvl2BDND5I39w1wGM8cCLHUqHV61uh2+Nc+u/FryfhO7+SPacIv8GjY4r7MjbPcdKxcLls0WlFlAeakqe77h5EZDomfFdk2FPVjmEQKvnJDdLlrWwuHPw+a/eWtWMbA0YlHXIlfXg8Bx1xY9iBXiIauOw3VL9MPdzbABa99b7N/DfdSqnC+4VFEEVqgQY0JmT50V3pIl4XyAyrceDXdvlqHJ/ZKhanUArSfXo9D33C9xV6utpqeCfaSa5GWpp2pnJ56JnAAAs/9PtDZrIOXWSauc/zQi0yB/bQFQqocKfuta1UT8UR92tekmD4V3HXq/14h4o1JCav5tZXWfKVDTS8XCx4+NswHr5cbrm1mQPF8Pwom53OzqqJNKRYNg1a2WcVrV8KNKEGKfUkU+Opv50ya0TvL2dV61AB8i1tbsSYqUQQCpIEnfNwDh842053f/Np3hDjBFqusbGEZVNBnue7NEQNKX0IWKHv+WFqs0KIXXYbyGtPayaaJ/oUER5ZjCO9QARYrRDzFdRRm+tiUL46gQZIStRj1FWMhhRbL3B5Waa/fiKqu6bEpUMqnIKLy2u95LD4wKh7k/VPOdKEXTCUhIHWvaxcp28IYKflwXVP547kmlsAr4PMtOyzz4hm6WYR+rJbPNPrbY9qShS2PaeoN9N8HtWCoF2qmQzaepltF24Rc06LLgBW5zF/XX6MzaC1817xHkC2eeQyN2aD+BhhVwlhRL+KGvGGdnibLsPOnc7wuMjCu7UWTuhdY8M2ceXcXktn/GPRTH1fn6vCL+p9rGiAg5k9Dr5tpjOwN0dw6kH6PqiBDiuiDKxDRF79Iy5K5wsjdIPQCR8IaLkfzNZBvdbO3J+raCkyYvu/mc/jPwkiqkXhxK+tXKw4zMt7LWgGA7bzcifudmh447giO7KqQt5/kmBF+a36RqfjE3wihwHi9/h+lw2PUPquQqN/66ysiQVFxqSUES7HB09D4V0fuNulsJNyCgJM0rKkwagC3p105Lcry90hFBNPhRcoLs/S30jhzpsonyDMNmFvCkFZIkpNYiXlD7CoR89a7ycZXVZ9efvOKLv9C+98zgUtXk0HyjW4Exv9vphKWnLCrx8CpXhNPMrklBVmtgIKMHdh9yY3BmgJ0ez3nonEACHn8aiyJpuvDVsnb0JVnh94dJjm+Qu8DkmQVlYaErN3mL/uYAQfNMde2EDeJuqiiRcra0yUEnUGNnGpS3C1V4KHYXzwN3FKzJyny3q42pP68GeWQWdD81BP1q2XpDyf7f71/lQzd+utf0eUg3eplRn5je236/rCagqMA13JvuSDwz5L6rYmQ/Dhjwylq4Q78FLNfJwukLr5cyB57nJeBPO+EiMlk0r1jfEqcbzPVNPQKoSoQ4E+gSThW0ywaM3Waj6jkrmqqnCQgjZvuurqY00AjCfbp//DUZOl7P1JgxXweakjchR1spIsQc3EnX5NyHVrgezM4vxcDPpwDvpA+BJ2bx/gXTWv9Dc+hF501pcTqrBidrrBgqonMvLPot9WRvy9qlSHg6NYovWLv+blNed47M9UEDcC/3V09aESF3O7ektzd/Cm3DgF2Pg4HFcZDrsQb0UOe45wkGkORbXmyOTORIW+Cql90bv5h6d8ZTnkI+RbKN+cpMWFVoOftWt5jPyxAvtn3UnTOlED/2BZ20huCIijZlnZXe+43FpntUDnJSKiXxHVgq2GKyYG79H2zUZvxwc1G+3z4uFai3fiVjMHqPCavJGHxMAkAuGL/GDXsKpt345BKnC6oq2IWMDYx6Tk0xh6CpupZnResxOinUExcS/KUdj6+Kittjye31QBqYeAV9ODnSyji/Hm+1FPC6JYaC3zNk589HkJ1tX3LB/Q9/yj+D65SMR13lYBmBghcMqXBbbEirt5F/1ZPV7soRWcpHttPhkCHJPJcmqMfc9sIiM/jBM2RKIg28SpcRD9ws2ne5sok0jeSfzGSIXTgC9dCXFZsjNbw7WUDwSXqgv+stg3WZIEyeXr0eVApCDXuas3KxOpcCZ9xe+ngigds9XlD3ZDC7R1N3S9JPtj7bwsbHbO+IFwxyuK0JhjBAqKMJN3nTVgWgI/4TsQT3x/wO2+NSnOJ38A4xBgw993KD+HSxmnEbN3oB0HYJQHUZ+b0V74WlOaxboF3HPaO9lhn+uvnS1PgfQCuq8R5cWDqwIpYE96tAnpQ8lFTQ3Ds+z/krZlIscUIp5cfsDzc3ShECdEngWjqSoTjy3fgS7uU5vMhnTGPuYqPpfjinHjh/O8O9dO9D2HSbWDY8j0u17EsfstbB4Ny514TVx5b1lpoN85LQnkK8vwomz1Iu/5gbl+TldmUxW0v0Ic86ILf3QpbFaTzHxEygy29IMnFyDhHH8yMRpz+kBEWzuR+r/BHKe9Iy+2hIjg2XjW5ffGQiS
*/