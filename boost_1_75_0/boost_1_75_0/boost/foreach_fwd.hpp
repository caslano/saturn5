///////////////////////////////////////////////////////////////////////////////
// foreach.hpp header file
//
// Copyright 2010 Eric Niebler.
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
// See http://www.boost.org/libs/foreach for documentation
//
// Credits:
// Kazutoshi Satoda: for suggesting the need for a _fwd header for foreach's
//                      customization points.

#ifndef BOOST_FOREACH_FWD_HPP
#define BOOST_FOREACH_FWD_HPP

// This must be at global scope, hence the uglified name
enum boost_foreach_argument_dependent_lookup_hack
{
    boost_foreach_argument_dependent_lookup_hack_value
};

namespace boost
{

namespace foreach
{
    ///////////////////////////////////////////////////////////////////////////////
    // boost::foreach::tag
    //
    typedef boost_foreach_argument_dependent_lookup_hack tag;

    ///////////////////////////////////////////////////////////////////////////////
    // boost::foreach::is_lightweight_proxy
    //   Specialize this for user-defined collection types if they are inexpensive to copy.
    //   This tells BOOST_FOREACH it can avoid the rvalue/lvalue detection stuff.
    template<typename T>
    struct is_lightweight_proxy;

    ///////////////////////////////////////////////////////////////////////////////
    // boost::foreach::is_noncopyable
    //   Specialize this for user-defined collection types if they cannot be copied.
    //   This also tells BOOST_FOREACH to avoid the rvalue/lvalue detection stuff.
    template<typename T>
    struct is_noncopyable;

} // namespace foreach

} // namespace boost

#endif

/* foreach_fwd.hpp
sG3mnUCBUVopUZRySkYTYKYiDB1W6k3qIHRMdJCgbmpuah5q7mqenW6dHp3unZ5KGLVGW3Ih2Z68QFZ7dx5fvZFTvRnts8Guoj1KODgMCQkLUwuLoP5DfUHlpL6hPqAaUyWoftRbVB2qAO5jeGN4Yjhq3ti3TI6YMpFCMvqZu8a/YXCUdugS4k91pj7CRYUj5k3VDHzLm4kza95H0LP1kFDqPdyn8IrwzPCm8OR5k92yQOLB0VVcwrzBLiKQFLqmcmQXUjxvvVt6TDhfpx5dOXsR9kXVkqOEjhCz3nX08EwnLF0VxFFaiCysLKwJPaprMxIfp4bUsf/UOzTF6dNtLB3uheiIk7pCNFI2GA6z2UkMIVF2cIt1hqPXZ85h8eEfw4vDv4bXhcepAgorjEiua1kbUkeDh1ZnXlQI9U5YsqpFp2mnbmGlPXqUVDPGtEbaIK2TNuXW7h6xHmmeGZw5hsWFN4QnhCPDc8OxHead6p1mnXqd1p3anRadRvYVCzVqRWpVamVqKLUSNYQ4iWOCg1T402LNaMNo3WhT+AhwJnXW8NfCCtRgKg1Vk8pLBYcldQAjNCMAEQYRthHqEWYRevaVnejO0j/a9jW+PxcICxMLJLWfchu5h8NnMWfaZ31n/GeVZ4+pUlR/6l2qHlU4DNlh8Af0R2uhOgIZURlRs/sz4mfEZMR4BDFiLIIQMRFBCtyIWMMeqh11HnYe
*/