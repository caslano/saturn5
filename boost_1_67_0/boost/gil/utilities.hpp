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
IUZALoA1ixEPe2ADFww3CoY7DPp3VqnwmhhR3ad1sblUsRfjQSUwNsjt+HRQPshedBpnVgl+ZBCYz0M8H9C22DrSjqhT7a5xUada7imug7bc5WHPBi7AC+Iu4TV3BLSgC6DTn0hr80II/u0WnvIwSBnKwisBoGJXr0XKjBXpOQfNZljFO3kVf7aeV3FutIq3YoOp6CkPNUxb3CO5I45ocosdvBy/iiTU8A84RQp+2gcMWnyZ1Bf/E4VAe0IteCw/dI598TJLj2zKYtmcSeHZjDeymTEWOj0ijzBeHhv3MsuOvYbkxOzzIWa26FUeDvWn/u80+z+xSdZ4/90meS0lmqlolNXfmdgkeDKu28JCtMbbjG7mV6VwaRYCx3F5XD4Imeji/lLf8MWWoDQ5qZBdlhzR1XBAh4e/SUYjrg547DRo5bZC9t1/8OPL6+IP6ebncX2ea5yfvsUDwnquSJcb8z3s3IILehFrcdI9bVmc03o46rTeTs7WrVZeWLWdTU+hIE/uq27224EkXsWnz3dRkKewr1FZFJF+QHGeAwGbpq7uA3/7CT97LInoYTTUc30SESK1AVDUJ45Z736muqtqAOq9ZneCrL+fXRM4LviLk8x2yadvGGh9HkVJGZSXp41JivqYr0kyXMpnGYGapeaF053cx3wEjIlIaU6KEPgDOZmf5ekuR7O+uAOdzEvs8fXOzYX5ZIns8NUl1Ynv6+jfIA9ZbsmESa3SZqykVwl+dC0DYGrsL0H3yywFLJ9OBUqDJErkvmUluUtz62b1zQytVb1PhVaDLEDqILnygtKALs0V9vUH5V4izRL2vQk3XB1rkoV9NaEUmJ+FfR2lrvDaa7LqZwr73hf2haGV1APQTrYa9S1yQT/6mTPj1vnyl5B7th4aKOxrwKfQPf0Fck//1FbrTCeNXmKRA3j+GHeXIvf0PdoQBMo0LIZBl8pp1MEpMA9Y+cBoCJsDo2z80tIcb0QI3GTlff4XfqusfEkpbjsbkaaRPXJSjswMRCwNpOScmLIN5iilhNG6OQiUh52maE9vRPvG0GAl4S5yU+fZwVT643ASzBZWL70qM/Jzv70sOSgeLso+4VFKDrPwo4QNXbUwGYLkp4LkC4HFgGP4aXdfzuISjkcr2XD5p1FzoX97rjaJHNwtt7NSihNtF/zboqK2iGR6P48TNeUu5uA+2XBwH0cO7uesfGpJwcnG1DC9N6W3PTbHYOgFHi5Pk3PgPZKeCMVQLqUYymLCJELgedMd+qtyw+3992b86LBSX+dUwff4Rdze58a5vV//y6jb+40c7PyQEr3kIa7d5iU4v6udhvc7On8L+44rJajshH21Pja+m8d7WBqCNXumrct4UEOLPDRsAeuXRMGY34E2a+BuCb25vP/FwtsAHwpsi2uGCdQMWby05VTaL9fy0pbxgFKs/pol6P0+Dr3fR/NH3fRoDm8t6eaaZQ1QH3amFUMKG6KV4WJWi87vitwQV5MPzkVrIps1mWU1asJ94HlYaTOpbmkZigz6v+8n//fDPf3fz8X837vEswCDcnNDGZjVTyCrUrU/VwauBpzF+nMKIgQ6oLyhVFC9rM5CWncndz6vYi4bOZ9XW/HnaTbG1jNodL8aRNxOC7cDbke+0ZDU3dc8rTdf8/az/CLffeUHxu4rdo98A3uvq7P33VfUFFu1x9iA5bOU6AYsU/VOYwOWI+YGLKUbMRgVo1Ffau3Sawt1B/tRK7Z2S+lGUEJS/zJnIfvMWEmSPylFhoK0ZDzRktnxtOQw0RL0KS3IPlGkdrhAYncFxXTciUVsMbdlKdmvlOxRSrYrJfAdo1ZPdXQmnLl0dmaUnAxNQ3JynMjJZrZ2JJITR6mrtrLkHEYmlBwU/Oi0U4i042ZztWus7nYGvU42gfZmGYxhq96G4rw8eBWfG7QlSk++QxcUb0OpD7dp+QoZShvtvFetyKcxzlbGfVLqxFOgUFrho8NHgE+bBQE5InBQf5jusHiq8r4UT1WOxVGV/zJCWNfzzTSRpvyEaMoT8TRlJZAEjeIt9s3nNGVgMI/TlH66yHDvliZFbo6SlDyTpIT/FZKi90JSBCApeZyk/A4yR9YCJKW9y+2o8Arok0IkRccddZCk7FIzzNjRXbg/HSoKpeQ4tg2SFEc8SXEQSXFAt03xvZ3p6/qJIu+WbvR1IUnpIpLiZIqxn4uTfXcmjqRAxo1IR4DzextUebfqPsa3dUGi8hfcXAeKJE/EtPr4ujC6tcuIbs2Ii27dZUS34hrmYeGRcfCer2ul8PhtxG3eQKzXZXAbX9d9nO0IjxUis+m6f32OrwuZTRcwm1l2nqOKUbc/R2azC20M9y1RSwBAdQK3WUjcptWqLTC5jYW4TUsct7GY3MbJks8Y8w6orGMxbmMxuA1MxcHVvXIbjOrVAe0SkUCf8XSCuS24Acn7se1NfkHcxsl+2xIHcy3IbTYDt9lcL+7ojdvs8LC3yonb7AC8Z/kebuNks1qQ27TwSmCYYa9Fmh0rkoVciqiKd/Iq/umnvQD5FgDyFqohAvluyZ2LbbHyvIOX45VvE2r4Bx4GZXAbC+c2lotwmxaT23TL5rFYNrcZ2Sz8No7bWJDbtJjcxnyZFcVeu9RhcBtLb9wG+v9bs/8Tm+RXq/7dJvm0I5rp71J4WXd+k9gktBWDkwmxEFophcuzEGhGbuOtgkx08SDnNutuTipiU8OdutoSaIOH89BfFE8alluKCrOBpAz8Cec29fHchlaYWOo0g9tsRm7TXghIB7gAEizt080V4gUd6FKkk5DfT5PN7WuA2RyzGmgDEX4b377GCejgHqxWVzQa91gCw3k7iVf09a+78CEiOBZpLiiCRH6z3eQ3E0A9CIFglN60ARTPffcL1b0nRm9OAb1pEfzLcR6Td/PWWRiNyR2SbEBRfx9MVLl01ixQK9pSnGDqiO6sNtnNOIPuLDMvvG/QneEqdHcO7utGbOccz+MeuxFSu0srsse3RV4ezE3IduqB7ZzS1ZI9gRPyME53nmzrNE6AEvzPEd3ZTjP/8SjbuaODtlsrKykuzRHk1DzFXZ2HfIfm0BrBr9IkUw2ZIOm5Q11UXRo4Kt0u7BOI98wB3gP3XEc470lFo+m+Iwo85WpcOzJLrBb2ydUzSYSZ+jYG59a9YD36KbIg4Da5upvJzLes2hK6AtgP5A1/exIgBxIgIYCoDqoKbXvSxnW+vBumG+3bC3i9E0YQYvc+MAEAchesfATVhgxUiAp4vBAYbeUy8Wd+HS6Wwz1pMnxZLI33dUXjdS8haTL5j1C2MnQjiFwBa8F40LLxd2onDQ13dwi5zzELzyWR+wjAsLS9OHMvY5bbaYWdFXhYhFh/OlIef4i8VxjI62PTkescHy0eRpG5ATfFydNGEdtx3s7KMV9Xp+A/lWQOyvnmrji7YXa61SBBgGENtjPeYDujiO20W41JCPlOqzWUctEm2/KV2WSAmDG6nIYeTPIB3DcAmkgq8XWtkhYbPGe3yXOSVhg853f0WDea06S6m6M0p0lxN5s0p1mXm9gsBWlOk7KoOZHmZK2I0hwjAZPmYBLsGDNoDuq9KM1pGrComXrPJAdOtl8z66S5iBxAT47kAbK4MFEbLWKU42D6tJsRr/o2o+o3YtXH8yJ6qYh9f8SLuBKr3J+ozX1AOaGeoQnwP2C7RIKz+EdRgtOIBCed1wFtiFQNLkuHuI29Ma4OYRatw2qzDve0GnWQbO0ljb6uhCDflywGABqN++aUYBbYo8hzmhSbKjYrs4jntCPPsSHPAZE9B0gqLw/GVegqzNTHkOoIXAUg1SGEtwgHJbKd55DteEgZgUBdi7G7Ngub8E2nGbs7ycNeOxuL3B3OLod7KKexyN3rLKH+dQ4LkiYL+/lZsv5sty5BlrSHpYAGg9/7iTS1sPZzndEA3kNfd3ZzyfxokuEEso1I1dboTjyHOam6k+2fjaSqsQepmne2F1KVwy+WOZdX4JHJz0yOUJRFWrbuekd4otpVLw9judFC8JntDl6E7GptElkNnb5wl9yPDaPHUrEJml3165yu5PT8weWr+7GU2I3X1Maa88m+pmE1TSnqZU9kwgPC3tlJaGW/tk56L2S9pSInUzq/yTr9bilt+mopY/paIfAwCEJZ0p24j2xa3yFs1uDy0HL149C3rnapTHitGp1MFvtYX+lWH5siDciXsvDHIB9LEQIY5J7jTZOz6sU06pwbXO/LQ7OP3rrxM/116NZM+Cngz0OWmWgi9Z94CMoSSvV9Ftl4CC0pt2yy+qvlJ8yCZVdPtQpboVkE/+dduJFpMTRAiyKnudrldDbkNFYUT3LXTpHdOKIsScPzmXPTjaOlWV/yW2MVN0b0WlVOK2RDHgOKXMu+3hwBktaZC3S6VvuGn267oKBQlZ1tuWkzi17Zdim0VGAVGcof2R+hzdqlcYXsQfreVSxdU8jK4HtNOLkwOD2ADcvuwHtNw4qhrW2O4lCSWts2c/gGaZ4+z17eB6j9XustSv+Qo5DV4BICpCinlvbTde1anD/m2StFZ+JjvzYekz6oFNExwKnhXghYPiGA7oSFjL0SK9nJV2Ila3wlsWTVr/Qsmb1C8G+hA1byehQw08hZ8N+p424fEdoGRPkJ1zLZPZ5vsRgVugRtIIUe5siCC1i5UH5ZUqV4YWlRUIzQyjhr+zEtC2Dqgeuwi4q+wl68HnvxazTO59q7ytNwJcTqq0ni6WcX89PG38Szxp/CgVOWjQMH7a5OHDZ18lAmfGUOG77Yfe0EGjZUiiwM969SoesVOYLf+0FOxYQhmk1RQc+KUjyLvADSrsWHzuALtVol3t2/CQUGDyE2BKZQlYY7i7LRdWwI+4XWmWDofG48X2o8g+KXm7bTJ/i/IFdIIfAx/p8k9fU1ZCq5aRrNfw3W0j+mWeGnnFrI1rwJuYaS1VynkqI/mKE/6Cxk+stwzcMKO7uw7Vz1Sq5d8PvJk16XNoBIPCLPL2QfvBwTh7+/HBOHmpcTxeH5lxPEIbkKpX3TTPvwR6Y/Ijs2zktDJLdxfQb6LsiXYfmdUj/A9HbZUZ+bgb5Wan+QAaP/L20/flW1ryndV52empumrLf7GvSlS2rZJgVyqc7kR2Q/lEdHZGtfYFuuir/z1FsR3bxDR0ynqzALqSVpaGPO8aYr7rBSEpGuzvFeJg12vQP6cSTrTNhMYNoNhn4kCVHlDFBU/aAQ2UdBSeSIlz14Ne7x27egaAF7/RuCpvDAy3EPrN2letOFv3ovK23PTYN+8LaopySnmpuhiK3oDtOKVQ7onLvxZ6TZaq4dONIMYfONMFhcx9XO1Ulq2OWNCI8ewlLpk9FUIodZ8U6LZfR6u/UmqzecdQog2mhvRPW2aLj44ippXb0cN4yVhtHW9NlHXR88mKrWtMuteMaIWotfarMOhPpW4W3X8bUwdF0wHB/Fg1CAFoULWfM+Eg1XR5dJxvZyuRD8v0EvaTGcBfgvEhpVyOZc4KdOCP4ALRtHLACCcFUgXGmF2v5Ad0egxoETQmAQkgvxMu1PXejc4POm6ZKgg/rEUfHw19SG7PdfdBoBYNdQAJhEW9vAk3h0Op7d7mQe41HpCxya18R5TeThw/PSMtX6rFrqBu1mfiU9dDr+vPgynY53/+wCP+Uehn81Dv8fQZfjollzjpwuTcmRL5Mm5sgZ8o2JJT1ymmd/7vNEzZA61hAYtvwGGuoZbPujpm5IPBu+jGccpyaS+bawIXrtHXyttpcCF+jRAjdhgf82DgqM/o/o85kGmBuUVq2cye6IFo3bKH4yJroI+TU1V05JOj0rHSti7T/DQpZE2vJwCniWhP/zl3AFGLTAuCL2Af/eJV1TxP7+Eo354CQa8kXsVbxXzJGALcUY8zg/yWIReyouka1xiVR2S6T8IolUSIPZlubEmuzI4jVxN+s5Jc3ypdGWLeKHv8c1aRpvUvbhWJylvWlFbC3WtJZgU+w4+uXeFweVMxRJbFm4me6Jb3l+W43dTng38jrc/MlF36Xb843boIYQCZDiBpix9zOzZni4famv6VufN520df9ChlzLKqb5lqVbigvZf4Bmg9f81cUPOX1NEXgmdPlOqzQgUYEixyIJK2Qj99DobWjq0rPfNKbFJ2rmqDVLSlB2LEtAdtaP6TbXDWHXfpYo0VOuN8UmdBPoMleX1MenW6Vkn54kH0U53u/n8l1kyPUVJJ9pcZ2QanTCojHG7HcWX0loiyKpXPVeFtDjEr8fW0OnxhBAF9moMYoHLErP1gvZisp/sTWKzOYY9CI1x+jABf3aA0RnYThnV4f6swmfxnXCUt46mdg6d4GcYXE/9KHcLkNrfdz4nUH1TO+lnj/OMurZl+oJyc3E5AZkxQ1UpzlQB7PnP0kU7zdGGTok9BA8CYD0LB+m/wDIOpR/PcTE+eiE4oQE+rFVn5hgNfQWjOGpw2D0/zCaaFlXUGzxLEeTBrtnPamt0DOg4NMLi5jzR+hD0Fsd/ni9UYc8H9VhZtQ5bKxuHOVbpK4bnpbd5uqSr2JfN3XqZQOXksgoU1kSr4JaHxq5nCJNpeEZ+GEtNA7SXHWKQ7JDDR3sRXhTteD+QDhDpxUUQdtkn3B1Qh22NSWaUXZdF9Vg91pRQ816PqLnLLUXK2LEa1OW2susBR72/kccydQqYnjdu2pRWmn7AadVdmbl2bUx/ISQ+c5CtSXrTNsBmyK3SreoiyKqHAE2Y/AY3xfDar5IaZs90V4hDVKPuBrXDFBbKqb1kZN1sTX7xK2uf6w+k1MSlgerYqt2HAMMj5Z/y746Zba49jME03lpVsH/AjZnkd31ruxUSlq1Z7jhEXLLqrEdqOlMhqyCg3+LmeJ2XzbKdjxku7YsCee5CEs1aiOG5WFqnhMAjK0hlFoxtY9sA8I701Wz+mxpex7AqtDN+EIY33nvpDFhe5Nx2OYYnqLOtYI6P62txik50GPVLtnUvAzKFvOEnzrtODZaDEO9YPK21SxZynHxXSi+t4/qoSvaP07UFX1HRnXFdSg7T1fEYDHa/4t7EbSZowxB+7iClEJw1/C7WnS9KhOAEbvj+U49aozbLmAwmPrSTvi/qJDl/hVUwHGYxnJBAEoqQQByQQA8ngImbuSOnEfVsOLdrCzasiF9nT2gr+kDBevbqN2Ja1i1OPnYafLxfTZMEf2qpeazFFvtpvzhSW82diAUc1or3b9BkGpX3VuezApf9ZZarx7RcFdwtb9a6FQ7ss6rhWkoRd6tgn8oWdl/YxUCp3lMqWe84P8Evh75NqfQrngr0HKyWV20RfsQnrxdXzVGXzVKlyvZLyto62Usgq0WzROrRqnnhcB8aCVX+RghkIuk2RJ0b12wHNFi0L19gT5ev3zFrVeUIya7jm7r8hZd3ozJ5VUYtd/QX9jcB27CQ48kIepyb1VLKlwfCI+2Qg8ETgTF7dKk4MJ+23/gOrAma5OzoqOffGnwNt1VsyYjmG+tyOkjpwNWTBP2vim8prQMH1xuq5kZOCE3QgmyarKP2uoufV/DrZCR8UmXQIuAYE4jwdx6q+vI6rPqos19F23BYbJV+4IPk9Os9mR0mPwYigEEw2psVFdoDxyVnVcv2qqhy2PWPKftLUxZ7eCgEkcE1rOSLdvAnTHEzXKmCzK4CghNMG1qyIHDwpqHg+IcdiAMirnxLTN2Q1zLtFzgLcPgfxogrvDaAeo8Gh+pND7UMIyQ9RnUMW2zM2CEWPOwg+WkI9+O9m72lWyh/pZtR368FaoIDSJuvnTRFjWIgsq9cDsn4gLOUwKFM6Uvr8Bx1GcEn1X83uis4mTJF2h04JJiInRpUhc1s8EjjDHyN68xcaKm5CwmTRoOVEYapsqXAV8cxu49kcgX116TQGHcTtc70ocGQ0nLEdPX/h1gETCUdIOhAFD3tkZJShhJStgkKa9jkealbfzECb0u3cB5yihhMwZemzylCMnJZDbzy4hO3AQUUdYpqzcSmu8qCa+eH3hT6lvI/lJBjk2yF22faqeUmn0UGUk46zy+XsjK/kyT9fSHTUIv3e2qV98BjtJgdUeyPnDVr/ao3tbQaBUYy2uWQg/78884QcU9nsUIUg70sA5vwOLjchFSj1uIeqRr33VjCGlak3kFWFkIFwKwo+6+NkLu12nSaOQCw0HVyJdx1ZfJIh8kqr70q03gv/Ja6qzL2DMPm9ovDjXM7OqOGkzUX4fvfPCwgRiqsQSnrjFVbpqpcv3d8t2WGVW507GABOnrpPchO3bNw70wj+4I2dTDVddQsdNY4cO9AeRP3wEUe59+MZBLt0W9d4C87STcHHXRd+l2qslq0pc3YdWboT0BCQTzTs847bBYHryGbToeXUA9wYHS9mFRPIDEtMzKPn65Uy9GjBV5OjxkcLkrvD67zF6k3zhmDoCffh91cmAAWLNfmM7bbHK9401RBlfeEjqrzKBL3uZQgZwM7RMqgu/BVboiN7na1w19GpMI2nfnZEgCqIOZaT55oocNBIRSPC+E4Rm6NDKW1f86aWbVj6f7DF4O2ZGydG/4m6GmtVD226ogrVoqd21ZxnLLUmiFj3H3IrEZw7mDAIsADSI24ngQhGHt+4nIUR0aFYZlUO5ClvkQp3VmPIg0tMcC2+Nfg+ahPVmPh44Xss8nWCzFgWpAhyx1Iv+aDKAgZINEFfFkonI6yR7JpNVPyGrYQyS5GcszseAjMqn7FO9JlF9XFxffYeyNfySK7wdDzAXo74iTusS0q6rbj0v/YM+ujeieQvbrcuSFIMTsCbzA/vqVubrW9Iqug9qpldMU+SQKfuApCmBKw/P4xvrCfQT/ZtRLtXw5i3YLhkoyN6Vzfyyd0LuKuxmel0ZBfw3PkZsf7AuNFX1+CD0/Jf55eEbOhlYpVcazs++ZCxC8Rg6oUTzk/nY11jBTQ1pUqkxJWD2GBrwFZLg2u43te5CqK1B1a3mABcFtTkrTQEKI/6exJ40Lar+duYPL1ct3wN9CtSY46UjIkTNVcviqna661edcdUtW5wR0OTt4q9V1YPUYpCvD1owoc3oWMNuHptPU5Wo/fF9Pxr/PYIJBe0NtdnXtcjzFe/lM7MviochbstvwiMSSxsqSpsqSTypLPlVKqnENwcmFcRj76liiMHZdZXZtI+5e9aYqwngABuo6JL37QmbIOnM=
*/