/*=============================================================================
    Copyright (c) 2011 Eric Niebler

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#if !defined(BOOST_FUSION_SINGLE_VIEW_ADVANCE_IMPL_JUL_07_2011_1348PM)
#define BOOST_FUSION_SINGLE_VIEW_ADVANCE_IMPL_JUL_07_2011_1348PM

#include <boost/fusion/support/config.hpp>
#include <boost/mpl/plus.hpp>

namespace boost { namespace fusion 
{
    struct single_view_iterator_tag;

    template <typename SingleView, typename Pos>
    struct single_view_iterator;

    namespace extension
    {
        template<typename Tag>
        struct advance_impl;

        template<>
        struct advance_impl<single_view_iterator_tag>
        {
            template<typename Iterator, typename Dist>
            struct apply
            {
                typedef single_view_iterator<
                    typename Iterator::single_view_type,
                    typename mpl::plus<typename Iterator::position, Dist>::type>
                type;

                BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
                static type
                call(Iterator const& i)
                {
                    return type(i.view);
                }
            };
        };
    }

}}

#endif

/* advance_impl.hpp
NtdPbfqs0CdG2ul5rRYLc6yywlCQZr6YbZawEFqhWGkDunkTydZa4SJr8/3CEtmEuTfiNs1yKbygFOUZ2GSFNSCt9fr5h2j+NlvBxto0Plt5nPL0W6ELizv15PNuahPtA7NJBhsZbLdCI2bDy99/QHmivWW2eGa5gsJ8v1ihB7MrE3pUpvHcoW4BtPRszObNrZVA9e2xQilmpz8+2UfnYPut9LuBt3C7tZmy1RbmOIBrlxm/z+5Bi2PGP5fxasQFNeJC0XHRn3ccVI+zo+Vixu/ru9DU2vRptOnXaDOEVpEZvyduP6RuHg0LapgtgNsYM35t6NIwn4aFVA3XwGErPXt+G/9nevYczYk2LpW0Gx//eUfXOafkPusOrjN6jxL+8aO1Z9Z424LOwuynrbCU2Y4b1x3C4IwVyjH7af263cKcaPWYvV7e5Tr1l8yKWuvZhenORlubRbluC3Mnsw3mxcWFBdHGx0jbWyPPJmEQjBw3Iza3Yo0PwhxoWRRpaR4evUhzdMEKOSJ2F8/dZvTZe0OY7pKVzoXvKcDOhQcU86D1iVhIwTvB6/+bRpjuMu6z4qQVq7Amcu7dubD3rpXu191X+g8rV3rrf4QF0DYq0sa/Cz4UFgpZwcXirg3tnFqY674VMjGjZ0rRPGhVmU1durUstYnG27yZaX9navMBHqeZDcozoqMwH5qd2eXv+g2iNtF4LlO2D28qDB7iuuZt7kjKJcyO9l2MtBKT7PuE6Z5E5jZie4+5fhXmRLvGLHFDntFUwx94fsZsYZGHfwiz/QfPFZk1H5W9PdlTXC/MFnQrYBDmQCvH7Lw1RzGaWzQbs+21yt+nuUWbyuxS3sF/CXM/s4KJWcV0Gf7H112HOXUtAQCfZBcpGqTobnKzxZZFAsviEqC4BddCsOIQHFokUNwanGINRVo8BQqUhwTa0kexUNyDFQqUTVtc37yPPXMm9/vO/fv3zTkzc67nJqHafWgLmT3fkcny3jw9XQ8K0rPDm6YeJceP6bWI7CFuu8yKDbjeTFgQLTuzsz3zFRUWRsvGjN7TQYO/ouOGZLtTS5imM/odSDQnGh8za/YXFOfWxX02qeoMYV6dlbo41SHMr7OkRW+DVJ/O5O9uYX06o9+yRINH0Sb3I6xPZ3K7xvp0djX1YCrVp7MiLTs/p/rQfmRWtfuD18I8qQXBymx/vW6DqXa0BczehY4fpvki0XEdM595KcynM8/lvXmoZ2gFmQ0YdHGvsIgurmqdKkeoL39H28xNj+4Lc+nsn4t3tlDtOlu4ONMKYQGd+cdMSU/rp7Nfy/ZJEWb5J9oGhtt1pTXS2cUPZtM26NHZw5umtHNAyTJ+tDVpdsvk6fnJpAJlhHn+xWtaZtfH5s7y3gYNdz4uSP/xcNvUp/9/LzWfLCygs8+qDikhTHsSbc1Gdu0izKez+wOOrREGT/Hamxk9C0KzGJiGlpGZvAbrPsSBVsr83u6Yeg4sZ243WFjkeUHoCtJGfTv/oTDPi4JwLkZaqNGk58KcbwvCEBY3J++hXcJCaFnTSfty3O7DwrR0cVCSxdXZ/KCAMDdaErNr5b+cIsyPlpPZpPsd1gkLohVhln7Keao9glaG2dNL+6an9czjSB8Hx2Pf2x+mnj12ffPpELIscVAivbRTzllWYZFccfA7ixt2bdYsYVAgDgqzuDetrk0SFrDHQf0M0pp/ufd7YaHicbjtSisVufazMEiKg7rMSs4/e0KYGy0jM1p3NA/aWGY3cg7zCbOUiIMazLJ/ebUtjYn2iNnFzH0Lv7ehQ30l4+B1mt01lRzxz+KR/YSFSsVBHZO0LCm2UcI8jjjoY5aWt8OGasK8yXHgY/bb+OM=
*/