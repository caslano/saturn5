/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman
    Copyright (c) 2007 Tobias Schwinger

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_SEQUENCE_BASE_04182005_0737)
#define FUSION_SEQUENCE_BASE_04182005_0737

#include <boost/config.hpp>
#include <boost/fusion/support/config.hpp>
#include <boost/mpl/begin_end_fwd.hpp>

namespace boost { namespace fusion
{
    namespace detail
    {
        struct from_sequence_convertible_type
        {};
    }

    template <typename Sequence>
    struct sequence_base
    {
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        Sequence const&
        derived() const BOOST_NOEXCEPT
        {
            return static_cast<Sequence const&>(*this);
        }

        BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        Sequence&
        derived() BOOST_NOEXCEPT
        {
            return static_cast<Sequence&>(*this);
        }

        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        operator detail::from_sequence_convertible_type() const BOOST_NOEXCEPT
        {
            return detail::from_sequence_convertible_type();
        }
    };

    struct fusion_sequence_tag;
}}

namespace boost { namespace mpl
{
    // Deliberately break mpl::begin, so it doesn't lie that a Fusion sequence
    // is not an MPL sequence by returning mpl::void_.
    // In other words: Fusion Sequences are always MPL Sequences, but they can
    // be incompletely defined.
    template<> struct begin_impl< boost::fusion::fusion_sequence_tag >;
}}

#endif

/* sequence_base.hpp
RwawXcbsU683Tyo2yV/IzWyDxy/kyIfFvr6g2B4/JTc7fvAhudkBsQ/pXXagbBW52SeG3qZnWGn8x0uZxvc5ek82KXclN3v+6/M5WhtukU/rSazphbCNjTXCxE4gjXp7xEyHpFToJ86MpO9DtWKbYrZd86C9kekTsDfylfNo8zkT+d7Io/3ZLEkq4CKfl+JwyfaSHi5m4CKfvRPlDS/HYpR91XOp1X/fXHf3yKZrtP+B89J0At9XPVrmIbC/u00j3b9nzX1qsrJpRGzVpChKNSaMrak2zzxaZmq7cl6svBPmyStshiktD7AvJlJeyqjyotq8c/lHlpcSLC/01cUR41nxZbLiWxZLk0wW8mqYahePJlMTz7NMbVik2QnDsnMsS+7OI9GdjzjvW75dnXXlqmIs1JUHLdLbt8y21psZaetPMphr4MaELtfuFalNluOuqY18zF7/8XG1KZBZrlaLXi5fDAkU3mxV5HzQfF8eD4zUCcTHHAKFrjqBvjywvk6gNw/01Am08kChpWtgJmfolE5gAn9zp06gPw98VycwkAfG6wRe5mkO0QkU+JsddAJjSiKwjk7gav6mRScwg6f5ewvXQDuP9phOYCaPdptOYAYPXKwTmMXTnKwTmMYDB+gEZvPANjqBFp6mr06gwN/8J0CnhHjgzzqBu3jgIZ1AGwXGCJsCVKZ+tgi3p8+DIu6++/0DWciPvvRQXjds
*/