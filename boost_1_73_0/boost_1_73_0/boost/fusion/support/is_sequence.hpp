/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_IS_SEQUENCE_05052005_1002)
#define FUSION_IS_SEQUENCE_05052005_1002

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/support/sequence_base.hpp>
#include <boost/fusion/support/tag_of.hpp>
#include <boost/fusion/support/detail/is_native_fusion_sequence.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/mpl/is_sequence.hpp>
#include <boost/type_traits/is_convertible.hpp>

namespace boost { namespace fusion
{
    // Special tags:
    struct non_fusion_tag;
    struct boost_tuple_tag; // boost::tuples::tuple tag
    struct boost_array_tag; // boost::array tag
    struct mpl_sequence_tag; // mpl sequence tag
    struct std_pair_tag; // std::pair tag

    namespace extension
    {
        template <typename T>
        struct is_sequence_impl
        {
            template <typename Sequence>
            struct apply
              : is_convertible<Sequence, fusion::detail::from_sequence_convertible_type>
            {};
        };

        template <>
        struct is_sequence_impl<non_fusion_tag>
        {
            template <typename T>
            struct apply : mpl::false_ {};
        };

        template <>
        struct is_sequence_impl<boost_tuple_tag>;

        template <>
        struct is_sequence_impl<boost_array_tag>;

        template <>
        struct is_sequence_impl<mpl_sequence_tag>;

        template <>
        struct is_sequence_impl<std_pair_tag>;
    }

    namespace traits
    {
        template <typename T>
        struct is_sequence
          : mpl::bool_<
                (bool)extension::is_sequence_impl<
                    typename fusion::detail::tag_of<T>::type
                >::template apply<T>::type::value
            >
        {};

        using detail::is_native_fusion_sequence;
    }
}}

#endif

/* is_sequence.hpp
fj2+ujq+6H1Ql6/U8cUHBPbL2cUpTH0IyFKlP81SnQHyVIXTWRTqkcH5cJ+Dra3vwngYzUda7eDs9TOdz2f7kx3x4md8wXM7eS47jJN0OgryAJt/F47V9kiPw1iPWifvr877p2fXxy/Pu/03vd67tnr0qOH127O33fYW9bfv3xz/q9s/P3v5unvRf0NdvTcvj6+7F8fYy5EYhYMbHSN93+kY5EiSCYQbKtUBTDcKUJ7Owdqc4IB1kN0pYIRrPw2nmodkn8RJ/DjIhmHoP/6YR9kB/uM/BujDICuByICscaXdiHntnqUgu/4TEKs4AjHApwd7pI1RkOXqH6pog+KYWdUeaDYDIQoOSrE3NprjWRrGeYkYejHV0yS981/As5EezG9IJra+45lQOKnvLq97/Xe9K5wLRXNaflpt/ursvFvT3j6uhX9yedHrXvSuqzjsm2q3q+7xKQIt9bGPa/G8fP/qVfeqioWfV7ucHJ+fvzw++aXUwz6udqhFYKDD3D7cx5im49HoDVjmd0mWt9ruWaYCZZ8bVZiD6QLrhzYOjG7eUaCNsCToOO/PsBUI0w0sFTFI1zCZal4KVDYf0Nuk1DjOch2M8HEA1jDFhR2hKh3pKbSylvMKTE0KtjnWi+gOVpUoGQZoNAvawHpm
*/