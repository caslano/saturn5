/*=============================================================================
    Copyright (c) 2001-2013 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_MAP_DETAIL_AT_IMPL_02042013_0821)
#define BOOST_FUSION_MAP_DETAIL_AT_IMPL_02042013_0821

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/support/detail/access.hpp>
#include <boost/utility/declval.hpp>

namespace boost { namespace fusion
{
    struct map_tag;

    namespace extension
    {
        template <typename Tag>
        struct at_impl;

        template <>
        struct at_impl<map_tag>
        {
            template <typename Sequence, typename N>
            struct apply
            {
                typedef mpl::int_<N::value> index;
                typedef
                    decltype(boost::declval<Sequence>().get(index()))
                type;

                BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
                static type
                call(Sequence& m)
                {
                    return m.get(index());
                }
            };

            template <typename Sequence, typename N>
            struct apply<Sequence const, N>
            {
                typedef mpl::int_<N::value> index;
                typedef
                    decltype(boost::declval<Sequence const>().get(index()))
                type;

                BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
                static type
                call(Sequence const& m)
                {
                    return m.get(index());
                }
            };
        };
    }
}}

#endif

/* at_impl.hpp
m9KsSb64zVq9HWbMwv6E7lQdOTLCGDMDi8yH7uBlaYrNw5Gtae3w9HZ0f1XDtupManS9jqc+RF5/7LND/HyOMcFytPxYr77BTQ0vhbxwAydhASPmBeb1JCUyv0l/mkwOysFYDJV3lYk5T2r1ItirRxqkPsIO0NpIbP6UfuzifWWJ9yfZimKhjRrJTRUc/a7s57nPTkA412HXnUka2XN3+EZmiPetpCDDWOLDZ3Uy0Cti3XjGlbb9hHHBZ3RofkEM/7sq+uIAkJMcSNT2UL+le7eK0oJGAEOHb47Da4fljgXBD35ouz9oFRpEAfoO5a9bYIYHXSiNVu8YHg5eo4/WDPHVaJOkOvtpK10hd/CqnRBllzaw5ywA/SSATnfEtIIzmquvT4yk4YHakyeT7Q+O6FefCh+YRvKQipnA9KFTsKbEvL+KLIPOu58ARcJS7UO2UpIBcki/zmHugzVKzXl8tRKHpN5SpdGjQza6VlDiPLl5Y9WpaJYUUDkefVOhCuedPJQd1gladSnN4SaLC44jOpciIBNJxpqcY1FCTp/9sHz6XJxBmTl7FS5UCg==
*/