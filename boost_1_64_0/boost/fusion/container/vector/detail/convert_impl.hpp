/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman
    Copyright (c) 2005-2006 Dan Marsden

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_CONVERT_IMPL_09222005_1104)
#define FUSION_CONVERT_IMPL_09222005_1104

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/container/vector/detail/as_vector.hpp>
#include <boost/fusion/container/vector/vector.hpp>
#include <boost/fusion/sequence/intrinsic/begin.hpp>
#include <boost/fusion/sequence/intrinsic/size.hpp>

namespace boost { namespace fusion
{
    struct vector_tag;

    namespace extension
    {
        template <typename T>
        struct convert_impl;

        template <>
        struct convert_impl<vector_tag>
        {
            template <typename Sequence>
            struct apply
            {
                typedef typename detail::as_vector<result_of::size<Sequence>::value> gen;
                typedef typename gen::
                    template apply<typename result_of::begin<Sequence>::type>::type
                type;

                BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
                static type call(Sequence& seq)
                {
                    return gen::call(fusion::begin(seq));
                }
            };
        };
    }
}}

#endif

/* convert_impl.hpp
9uuDDZD9GjAAwzEUIzAWIzEJozAdozEDB6Klv1K+y+Q7zrG/crDsfzgacASOwlR8EUfhBDYeh5diOj6E4/EAZmB3/t82AdMxEy/EibgdJ+MunIKf4VT8BadhJ058NgbgdOyLMzAWc/AMzMWpmIezcTYm851dhL9hKXbjdZXhYCzHdKzAMlyIlVgp5yNGJ99VOEnOtys5VM7HIHk/xWIoxuF4jFfvxSbfM+gm29vfi62rrGuiX8O9vsiZa9z/8j7HIo5ZRa4l7yIfJLerZl4eObNa64vUkpa0pKWTnU56/F9aYh6AfyLifyVm/6G77f5/lRKzu2B/PEQO8OP6X4blNzaHz7G/Z9m+Y1znrrO7zr2fxyXm2CKvfJb8/j9of71ayuqxj59SxtFKJOZ2uPYtY7vtxpjbj6c++b+tWzr+enqpUt61bmvvjxJu2TnEp7x74c40jmn5LSjnV857lcNvwdPlN24XHIYeeCZ2w0r0xJuxBx7AXngIe2MMrub//Rur3Vs0nnaL9ntBS1rSkpa0pCUtaUlLWtKSlo6ZTn78nzvfqFyXOkHz/w93t83/10v8nybX+UbK9XJdhnqdTzl68Tzl+C2+Xi33+7feY4m80hwXf7azp35LdMDmp6MPh+xe9koP9dqSHFdiYYdrLx2kz74jBmIn7IedMcYhXh6JXbEjSsxrjnP3anGulrSkJS1pSUta0pKWtKQlLWnpD6aTHv8vKDfm5M8tm3eC4v96u/jfQ8arz0dfLERPZZz4WDX+X1Ceaz58+bwW3PvZOsa5pNwk9xS3WzOOQutadOlNrFGXhSad1OfO0+XzTQ5jrcsKCoyW47VTxw8vNoC5zMNWFm4d6+zmMD7a1WHdOb06FrpIvUd9R3U/pnBrmZf6+vLVemCtRxv+2Wu9PVGqlL/W/u36tbu/2vdd3tud3ooevNDSB6Nzkb+9vCeqsBf5iPyRe8tabwEYhIFowL44EYOxFkPwNHYShjE4AIehAUdjOE7ECMzGSDRhFF6D0ViDA3EdDsKtGINPYiy+jHG4D+NxPyagC+1ORF8choGYjGGYiiNxFM7EMViAaViIZ8jr2us4bsLJmIkjWl+SlrSkJS1pSUta0pKWtPS/Syc9/i85sev/f2EX/2+ROdrppxH/i0d4UJeoxv8ljuv/zzmO9f/rxzRc/3/PGNv6/9Fj1LX+I3VS1tVWpq65/+3oxvcJeHV04/sEbBnd+D4B1aMb3yegcnTj+wRkjW58n4DaFLVMbd8KW5navjm2MrV9abYytX0hKY3vCdDWVqa278PkxvcEeMZWNtDa11DipH+lUtapd+xfWdZE/8ryJuanVzm5B0C1k7X9052s7a9vOLfdYc55GWvgS/+Qk/X9g+zbL9umOVnLP9XJuv0xTtboT3GyRn+UfVsM/+w+mm9LlfLgJP9zV2YfuvGaupxNbgavrZY+mmUu8vmUz2sVmudEu9jmj/hiVwzBbhiNnjgeu2OO3fyRnljItt54KfbCauyNvegT8cF1qMcN6ItK55kf9sM+mIz+OA0DsAgD8Wzsi5djEN6AwdhD1u9fgyG4FkPxZuyPgfw9w/BOHIC70IDjGRAUjq9hBH6CkXgUo1CZqx+N/jgQ43AQjsIYfBoHY7Ks35+KcXgV6/PH4zocgvdhAj6EifgGJqH7aTK33bpe/XH0E3lcq/UTaUlLWtKSlrSkJS39l9JJj/+LZ+WdyPn/n9rF/59L/L/Njd/1Ylc/9h2txv9ydKU5luv/y48j/i9KaBj/pyXY4v9H4xrH8KvjGsfwc+Max/DD4hrH8N5xjWP4w7GN7/W3M7bxvf5ujm0c638yuHGsv5Uyx1j/csocY/05lDk=
*/