// Copyright Daniel Wallin, David Abrahams 2005.
// Copyright Cromwell D. Enage 2017.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PARAMETER_AUX_DEFAULT_HPP
#define BOOST_PARAMETER_AUX_DEFAULT_HPP

namespace boost { namespace parameter { namespace aux {

    // A wrapper for the default value passed by the user when resolving
    // the value of the parameter with the given Keyword
    template <typename Keyword, typename Value>
    struct default_
    {
        inline BOOST_CONSTEXPR default_(Value& x) : value(x)
        {
        }

        Value& value;
    };
}}} // namespace boost::parameter::aux

#include <boost/parameter/config.hpp>

namespace boost { namespace parameter { namespace aux {

    // lazy_default -- A wrapper for the default value computation function
    // passed by the user when resolving the value of the parameter with the
    // given keyword.
#if BOOST_WORKAROUND(__EDG_VERSION__, <= 300)
    // These compilers need a little extra help with overload resolution;
    // we have empty_arg_list's operator[] accept a base class
    // to make that overload less preferable.
    template <typename KW, typename DefaultComputer>
    struct lazy_default_base
    {
        inline BOOST_CONSTEXPR lazy_default_base(DefaultComputer& x)
          : compute_default(x)
        {
        }

        DefaultComputer& compute_default;
    };

    template <typename KW, typename DefaultComputer>
    struct lazy_default
      : ::boost::parameter::aux::lazy_default_base<KW,DefaultComputer>
    {
        inline BOOST_CONSTEXPR lazy_default(DefaultComputer& x)
          : ::boost::parameter::aux::lazy_default_base<KW,DefaultComputer>(x)
        {
        }
    };
#else   // !BOOST_WORKAROUND(__EDG_VERSION__, <= 300)
    template <typename KW, typename DefaultComputer>
    struct lazy_default
    {
        inline BOOST_CONSTEXPR lazy_default(DefaultComputer& x)
          : compute_default(x)
        {
        }

        DefaultComputer& compute_default;
    };
#endif  // EDG workarounds needed.
}}} // namespace boost::parameter::aux

#if BOOST_WORKAROUND(__EDG_VERSION__, <= 300)
#define BOOST_PARAMETER_lazy_default_fallback \
    ::boost::parameter::aux::lazy_default_base
/**/
#else
#define BOOST_PARAMETER_lazy_default_fallback \
    ::boost::parameter::aux::lazy_default
/**/
#endif

#if defined(BOOST_PARAMETER_HAS_PERFECT_FORWARDING)

#include <utility>

namespace boost { namespace parameter { namespace aux {

    template <typename Keyword, typename Value>
    struct default_r_
    {
        inline BOOST_CONSTEXPR default_r_(Value&& x)
          : value(::std::forward<Value>(x))
        {
        }

        Value&& value;
    };
}}} // namespace boost::parameter::aux

#endif  // BOOST_PARAMETER_HAS_PERFECT_FORWARDING
#endif  // include guard


/* default.hpp
nSOR58AohQ6oZ8iNjXRhO6aYubnCUtuN3vSP0RfyqbvJBkfQY/9ZRvybupWn3TqU9IZ68FQFqaB/UCk6/lLqSS84huX07W1tvtv7oTIVxm0RQMaDKBC5CMDtOmkNZ3CQZHEwE1YCW5AAdPSYn1KFEDalcBgHCuBVWsDRMpmlWmBLQ7AeXBSI2QiX1s0mY44nDBYssJkw2VJyFQvHQLZgRH6J26Uz/4FzPA5qFol17FTa+q34uwGAx033HgCQ4zTa29vzGskKB50J1X9z/O5XTL3IkkAql2b22nYHG5Xh1II2QbzmoLXF/Ju6Z8LYsgYCNlNkmUZx4+KElMaMKaQVSw6EiTbCGR8cVEhwxUstCM5ZbUA3Oee9SIBeDGHFamfCMfASv1SRooKjFAAfVENQKsTUTFTawCNgBsxRFsR1EFro4fJAb47Oyk2/wV6lJZKFM8sfnvtcpP2RN/LGO96Yv0ajASC6i9AdeJ89e7ZBYB3kXP9PCJ+IIHqsFSKx/49YPxl743GNdguqO1Dv7u6uzjZFZcRFRSRmvaw0he/7Sgvmqtq4nNv50tSPujyXBxYQX6Z6GaNKpLrAvlb6h2vRrElsYleeugRfyqzkbzndrn+RFBWZnICDoQpjUBXlMoAP1SHA/jdVqiZULlJ9
*/