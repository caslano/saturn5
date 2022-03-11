/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman
    Copyright (c) 2011 Brandon Kohn

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_MAP_DETAIL_AT_IMPL_HPP)
#define BOOST_FUSION_MAP_DETAIL_AT_IMPL_HPP

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/support/detail/access.hpp>
#include <boost/type_traits/is_const.hpp>
#include <boost/mpl/at.hpp>
#include <boost/mpl/int.hpp>

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
                typedef typename
                    mpl::at<typename Sequence::storage_type::types, N>::type
                element;
                typedef typename detail::ref_result<element>::type type;

                BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
                static type
                call(Sequence& m)
                {
                    return m.get_data().at_impl(N());
                }
            };

            template <typename Sequence, typename N>
            struct apply<Sequence const, N>
            {
                typedef typename
                    mpl::at<typename Sequence::storage_type::types, N>::type
                element;
                typedef typename detail::cref_result<element>::type type;

                BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
                static type
                call(Sequence const& m)
                {
                    return m.get_data().at_impl(N());
                }
            };
        };
    }
}}

#endif //BOOST_FUSION_MAP_DETAIL_AT_IMPL_HPP

/* at_impl.hpp
fKPFvaLaMT9IH1mx1Zj/TNM9hFu3g4XTc8t5jZ2hnUYqw+xs9S/bY3iHXY66CbWF5NW9ySeyqzNcFb8lvjyhup2tZvc02QA7hixs/vDf9hl+5zqhWIkS7hH25t7F4+GVlHv3UuwYquComQ70xFUdzYiC+8nJMXqBw6KYUdiwGhLf7aokHL7IK0J/dhI3pENRJxANtbvmRop9ZWt6EgDBAOR0Mg5/K7gBfrBJPgTpdu+Jy8lr2DP4NCF3oD3OXgFEA8TLH28MAwwDqv4qCDYiapFTMfWoWbK3Gn7fIC1EW1H1iNnYWow8+D0O9PXAW5h+h6BYwknCzcBbgyDd3P7w2YjbzQiNxltcXFA+M6MdPi9qD+Sf3lA9o1sZGDG6JTAGU8uPyxRpSxAQgMtOYgP1hgUdbn2ykBb0IgYcqw9zU0aFyBXSu3Vi3YzDleGdOmFamzmh5GSgZNqJw/hXrrc4KQvCZv4WS4UK6vVZV+jrq8O3ifS5ENoFPAJYd+bvjphXfE5R2vny/OkLjLS8Ha9OehbFrahx4rBEkLj4P4pIwpIB4hIIFJCEJAKF/8/BMWHLtuf6ZKsWrVvdVu5jXZhzEoEu4tIUkKf4XF2kRakATwl5Osj/92DxNhAlKg4Rp86wM6ODNkxnO+I6oixyDJkk2kPqe2oU4FCreGQIgJP31G7jKoprwV0wfC1b4gN3d9ATeOb1xrzFHJKCootkiJbyPhG12GXvxZv4/gBxRKRjg/umMCYa8ffWWI81Mzp6XIVRrnjxkzBXg4Ie+uzmylFCDpPUHRMtX6+w3srAfYOK7+s6sAW6U2LjRREq/iwtskqDjeHl7Q3m8LwtFnMpw+Slx0tt1WgR7DPKm0ltMUnpBqMHiZdWU99g/V8MdfKmmb7NHDwUX77O3Hcn0acbK+k+8o6Wk3ShgeSVZ0CbeSS+JI0FiXJnY4pmwTMXLnOFJiGQYYYz0yRvDk0u4TJi5k1RtMzyG40/DNe6HuebeTz3xGNRFPQW5WGQ1bA0c3hvLDUb28XgU7rF7UJPELieQXA8gqF4s3kiLdfmbaLdf1ybtDsEoRheyIL4IQnkBSESAfxJx90BZ8MzKOx5GS42NxsavzY2215ggJRu8EFokd9uUMfYvPJgg6kTAzaiTZWiaYmLmlKaTtk0NKvL7mgt2kRBknMcCh6nQ2ezR74HGk8MGk9W/VKfM3frCLpCpx6TuKRFC5uZxbWwjtfrl60nNBOuGvNE1uWBu77ombbdwXv8xkNIletOAjf6Ng5F2rWqdRYdaVS4XqRXEeZ9IroUHbA6qVu3guMOYnuQZ12/1zaYmJCbOsf2R6hNCmetn96b+rCr1nenmEV8gpc7lBCjG8PFEYumpRXfo/El7BwGd+6suKqPHP0o7irYuzX2U9Dvxh4Kl5tGdHdvkXFwqrDsicLlHux6VsotwTZRXYBtIxTUFYIxgjm/hkq4X9rnWYBN8vSrviOBL69wW7rHKeN9HDXGJPAqz8G6zRfZhXTwdiuUP62M+DzktUN9NwWVKTsSNAxelLl9b+IjyG6eFM8OWqH/zZP9JComD9q+vJuWKjxeHO2MTZDfFLU9u5mZVpO6hH13hmg+MrJ2Rn/eYWpsuI1OAoBSQv73xiHnn47l0VS7uxVAgTXW6OcB5+mXd/TT4ql26JoepR0HW4yH5GAllFqwjBR/TTiN/RkD+DlFJvHyKrgG3Gkc7i2K3Y9Ez4/jtbIEkskMaDZ0cLUcf7Carad6Z9xRZew+b0rtQ6WCrhxKWwqnI4/bnsvpLOByGnA+C7qUB10u9P8O/DEqgyn6GcbqH0wHOridrdqud14xqr/JS00tTmv07vYow37wiRIzNEq2e0Z7maDuUZeK0nCX3vVpStzMR7P6CFs4XABpEnPO5ZEPOAVP6MeDIbIEiJ59xi/BCPnxP1R9M4C0VeCKNObc1HhEaq0cvkj72vVX8lIdVzJH0dlNNhPTpaZ2r97VcBC70YZhzdAzXS+NOxl/Sbmzx7Rf+2ScVCcpYR9OF9fYYTx9zkp4k/fU1jx5qHy41gYz5cLTrab4zg699/h3Y89LJmadfyGLlU5Lar+tgvodwmp8o4v6YxbZXKAWs/hbVJ2307AN0ikqlnQO4TpU8PaZ5OzWy9mvgWtH0ITfbBSCKHiAFPkEzHcXTpbu07pGXJN64jQHzHEtPNumI74WuaFaCbFptIq4+cDU6Eb5N9mlvJFKlvaRRyHyBWIyBGMqkAbWNz742pwiLfK7bEVUTy6rMHH9xXaROCqlCl6jdrrUK9Lxmq1Gftgw6dmprHBurpbzsddJmamwqod4gMQ3YGQr0Rdr1bOdzfU4OjtLw0yOgbjReinTARacAOBqlJKN6gjJ8rgbkVzb9ssLzNmrL5xuMX+spuOoqW/psL9i7PrqRflSSoPDW2Q0mixhD6vbP9mrkc9ICfupUbVzRvVu07ArV+6yn91WLlAc1baJtasZj30tREnJrQxZuJ3IkP+7Ewz0GbOhzBrhJsfAZaLofsWu+4Gi20GgHakZYEqjZ7ks5JuUxqgXOSng9WnrcaV0bHUCZR0PdGyFr9umjxyQbagGZBKb47B43mUN80O0EvllUvY8Sqz116+mhdUqtrPMfi7leTTL5N3UrQ/0HPykvUHZxEF8P8uEMtJr6LpSWYNXWcZP6Ro9w69C/cRKM4ANrETpG3/X14rXnmYp4rXA23afzjTI/JI+V9p735BSzOA14UzZVTeuoUGklD24UOfPzhtcs8pRKNXTdpvWuC41R3Zsx9z+XPqnX5HVOO9nMiOvbQJ8/ALTJqKDohXk9lyhmdwoKcPIUGQ96uVglDed4tK/FDbnKCSuGatwPyAdO43+jM4ttuhO8yU/36uDrJrgAc8CJt9bGF6N1Uq2taex1YkoMg7yRGVkt6Gb/otHmiTDG56/NCs8oZIxI7qi2J6ilNkQvyeL2JUsdNr892Xpb4+Tstrhq7Q8Nfgs9wydB/NtGLYTHSC+YvCsO+D7ab622mG4hbsi8n6P1q+GUKpXtEMdEg+6k2sWZnG3NulP9BXIi3uFEnzlfHrdAxdP01g1Fx/57IBXuvs1Bqb7zoLckJ5uR5RbGkUK3lHVo+EHY68Jrxb1B9+wP3a4Me8PVpC4T971VHYrXO/sCmaHKlZjbyqtzsMqvmYuhfRdBPRtwjdDJmK9p8FKVHI67Cxs5bedU6XutfNXYbV0/QyaYwWWSQkiXLuHdXVwd3/2W4i6Ie/o96vCVv7oRrsz7UeH2Yl4M+2//MET+WTen/njC3bnMFiCmCO4GSMw3Ixi1kXog3JGR8Ab8soxOENoK/LNDVXkp+AH7nBVw0BvocMzvAJxJr0tiTa5kWIAXKRjh6UiM+CZIKSTxwaqosS/MxXD2pRhdzafMV1ezNA1VpPO7alUYbleeDO9T3GdpeMnW8VXUdNSjvruWaJ5M7viteQZ2+2rWZUzv7Kx5JnRvV213PH4NGTZRcc6L7Aud4mAnlV2t04EuX0a9DAz/qhclkEyf3Ocrdzm7xNTcv4PT/j9SnznMMTy71cTJTSlsUAKNXkS6FV9ryva60wAocYsOXSlqf8JNX2OiaY8FfUenTyP7WIgQtVocj4qhksOhkdeWEYGXq2xR4mvwrovt86bjU/beCIj6PIcv8ZYHFjGOHcISodklj0t8aiBNs7pnwgmkxXEiQbHfLbWsBhxh4XeIBR4BT/MEneV8ek4sJxx9n+KlYqyhbPagMCj7YrlZqCc8fhv7dvyotojTqPtkkmGTaJ2EAg1hEWSRf3iZcUUMBTMM5fCkvImjOJlSmV4hczlMM7DLlOJoUSwGcrD0Ja34up3jctpdCnJXI8jQ0J5itTIlE2QBggGAAYoe6ZB0RAViIyxFYso+wcQGozvPSI/ypTw8DOEHjB7p9SiBP0uuh3LHvCpBsjiaMIY/KMwKnjP7dcbfyZvAB74Gidbc3SaQBdPlDdqLS/kbTKUM8SaosuawWO3d/Wn9ktB92DNjsyi/I6d7lKIhNgpMjXtCWJdPmtrRDZcAwMD6DzI1efzm8xeodHer3YHAs7YhrDVyW5m6fJ4DVgJizlCw6Ll/0IwTDETwp3zEL1IDRKrCmsHUQuHSVyGuaNYLvYIS+8LD5Yo2m/uaFYy2mY+sVnKU8a96EpmAQhSITLC41/pd5sM0gnbF4bMqd1t+vglg/UUKe0OYC6ZmnzKVDRTLD0j/XPTbOIhCtMKKy/BkKGc6HzYG72HiOf8BKsHahjtR7eOorbr9qfW6/av3PcG1vBF1igirR+XNlZJH4VKHS1njFOxIYxk65hJWSTD1Fmavm/OXR7b+L263HnBNStM20fcCAJp0jyDF6Moj4NRftmEnOMOpdFfUVFjsRH7UPyNah6U7eYeyWSL9iKf5r3siPel6AUgyiMuJsTctELbeULVVputAkXqwEccjvtFLaamx1Qlx0Jz7HEmQfVRNxxkYj4InSm7yIV7+imHow+M9VeTbKKsJxKa0qeY1A1M2yapVqr61XstoZN7VIfKmDB6BE6vUG0qYANqozjpgkWJIzjptnNM6ppmeED9nn9rYeCpCZxGoVTKYUIq/3EYB5crgwmpjuLECE5RNiC73t/D4Mfh59VJHxul5ZlMJ2toH+ukhZvYJq9pHqulOZjAHaflNvv+o1CO2aPZjw+BglJOxi6vjwpwhFApVMQivUo0laIDgQxAFojTlzZBLgVOtXBOXkGyu4vSjGE6Hlg569ql0Sh9DGgxhp2H3j4HtXsKaPFM8yItC1aH98dWQcNJAhXb+/t6+3SHmFAg2vkHhz2iDjYGKg3HRalgTB65Y5vYtt9orKp+t4j6ZMN+Y1Dn0f3Tym5yUv4TLiLH/ead2HcYDdsguLJZd6ae+063xIiEDJsWpy88vuVcweztRZ0A5oMWZ4+BdP9Nb0fySXfXy8RLT+SVKkq0cuHWnNljKQ7O15Jj/q7889Yp0rh2lo8HqkJ333KbYT4yi36JtqtKAyvRdWf45YtbT/m2uG/fu7xELrb98VkG1C4hJEy6ZP55y1MpCWj7qVgUVFhO88nLfNLakWo2pIkAwWh7nflux93i/hXmCMBE//kieK1GbRDMtQbmUhdztYux1stE/2W89zrJf4sKuEPtfw9gAkH+DpDGwFDjYJKJEoMLcgli95fcPmL04wVRBLlABEJYIajSISMucaYhq9BdJnTVyj33865R9UNBa4GhNcNQW2OqrzLW1proG0z09if7B9MA/2+BKAOA3+YkPaa6ASMPeZJAK7IBlAFuv2WQbBBrkFzeInk/MkQsAYoJYnlmnrxgEnJnqPgIOKagrE4pkuOZYOE/LfTNYO72XMbDJdAGghzaMDjUBZzeVYi3Jxjr+jxFGy3wBJGN5PUofAS5jeWJx7n1msX1ldXGZy0cTa+uyHpTkotWYx4qDXzRZVi88YuCTt9xLdOojidAxds3kSeVRTDh8mjWxZXZdkCPgEX9wsUzzNWwC+zo4yU2aAua1aCNPvWTlo7DK1oPrp9GvaKmmqKQ6oIQVnuhtNzNEqpCOTXxnNcSHyIWZxoWZ1yWxrxJjEns0jz9FDBL8tYSfywoU8vckGcCQdhggvbfXoczMAuK6XmIqc4rhTBqQJdgUru9Vpgl2ENwqemt8G8jMqjU1F76twEcfB6VEjKZLjQ1DETYOKbeoWNaOSaoqsFtc6gVwumuuZqrumYi901p9ilNj1d1jBxh1FqIMSG+SVJR3qmy2qs6lNMwa7St78rYjSu1IERkFPwEyzb4IaefFSC3Yc19z68n472HRDnnIzguABinFB1NJQRnkYXHyjJCH3/XcoEuO6xXW3hBvRyHXrnePUjC3VJkWJH1mvoSjw24hDWLxa/Hltv093v9ryWAz9pfWzDnDMAtoFM4YE3w0wywR5RcMtjTlL+6zLklgF0W/D1AyrXKuQt/ZTFnfIHN5/9mAz82A36hzRoWbCrwk6F3fgWD2vkZ9W3QdF5Hp41nGL447ENiw1q8uGM/NFZnPe7uFn1uzddYLGm53BaYNr7vlkyZT/UVmTZe7pJNmp/1zWQo/PS5mZqaIsDiUDMrUcHLZpQNgV+Zlt/kbkR5wqMRpctqO2a7nPjb4pE7m4Z3wY8xbgrBVh/ctGEXK/uEbtNXnYda6LRJ29XWny7s134LdPVVnY+4a6jfzGF3lvsmNNONunWBK8qii7wNZFAKv5GXWEocxt5bEmsOrjRIOSOKTBBbHnT5I30hR7xTlLNxhxD5uW4N0DLazgFoMsvQlNcURtVI+fq22F1vba+5eZGjcQEd/ZCHBg/H98heaI+pIDmoSzbK/hASEMROlqmHa+XOAGva8OsBKEvtffGkaM/wv6xQZLKrDWLDiAg2TvcYWGAG/7s1XSlXkOurba4ZAWM4Q2M4qxOQbu+x5b+vdO1r6GH9EybxkgILYTjvMxJg1kLj/iwDDFTgymfBr794zYbO7eXQx4SYgIc9WPiReAdjOP/V7PTdMAY6g4Z9pAsyaOjoF3tFAmD3x1ijjc/A6w04SEjqEOpkOFkjcwlxWlZQ+7WXpuqCjZpxQpr0GefzEMdKj4MMMScNOe2hGKMVHm3q7rvDqf8ujiNNk5OMpyEAJRWZc6WvRT5K+BgXMS1dI85DQrg4RFOjiC1TtaO2qM0gSiSEHy2HITnToskKmU8DrizNFDK/NLT1CcgvP9kRTd5ZcrWpV/xpuuideDxTJ6pUaHBAmjpLhliCUh9xSyU85F8iXGq9UD2nj58RIksn6VHzJnxfxeHlv3UgoW/tTEENKFEGmMt3rKQii6J0nY317ycjGtASzcV3BpsfqEFV+bj2ObvjhYKF+1NmRcr9UNw7IUCkRst+OZ3DOo95sn3x2PLG6YIbQbAswkAvKF5tMKuth5wqNMzPz0yYZrRbDTjNE9P3I2TV1/rHOIaLD1C7KSCFCq0/IU/QIHZ5ADxd/Ma6mn9ka6gRcoOBvCaAEG10/3Rjo0FcCvZ52fqXZmn8CenR++Pek5nEGOLLQuVRiAKCNoprkLZM4m3VwoCqgzJjuAtAikzadgFQTBTjCYeSrrDjL5eq8OO/Mtk5DZySXnYNbJdWtg0sNbW4D7xgankG2JGm6dprI0oFn8nAxP5H4Yta4UzMRsQa+yLSYE5gM+wmQ/VkEW5U7arW8nRWTa6saeD9yLKt+x2zCXhfhasYC29RrWNxnaFruQBLvHf5E29nRKOm4FRje4RYobt7KZocOkgMaeYhzh4py9AuV5hDqE74LQyWT+RpCdgSvLD8mWGJPrcmW9WqpMnnyW+X54GiJCe/5mEbI/ze1QqJmS+jAypb9kY/bh8wcFTJLAJtpoXYbn0W1qizIbLlbpHHoU4EdKQxrxOUAs6G3F7T1W/pjjYTW3YhoXxO5q0AD6n1tRaYUQxegyTqk9wVw2kHEWJbQejWsnEaP2G3blaEMvV7kg2h0haxHQ+7uP16CUwZFAJZr78ZDGlUUIzq+VVE6pXSh06aTUx0GK0IeZb6AP2B6Nn57K3xiXq6pk4JTdf7R5dqbcKoq+69O5OnXnlg/7U2JxJlMLSLhEyFzXnfdlWu3YDvLOSrEJvTke2SbKs2x3nAdx72Q+J/OjnJWJulgARoulvq7m9LuupjWlWWdJWHVaxN6Kr3qh3rEyGjAtmZnHOmA9J4LqW+q2n5skvwXEqLRe8GZhHtKnyX0gqx56Fp3OcqX/QJYj7l+Mdj5nX/HVD7qm0VlirLRkWQZE0Qm1Dms5adk1yCz1Bizn03cIpQLfNdzcxfKsc3vTeP/s8ELOX/rHChzDd5OCe6BN+h3Jh2b09cKzG0usgABCz70zG4HOlI/q4Z0PNn0Uj+HRKb/oeRVf/bxLr3c2L171vLUt5z/+fGubKXwbeNS1kX/U9z+5Juqp8WjyXdZE+VbhP68Y5qzjr0g12u+pD+91An3+hERCw+pF8xcpIYr0Uj0e7KHAJWB3QIdMhBjXbLa1iEwzjIDtoodFzXJwmvZHjWATdKqDeFmLe7sfFmPt9I4E9k81DoQc0rek7StMytWuV7x50ajcXFz7HK7H6BO1Qmhsaru/actLtO0sSHnK1YIf1JCf5WkSuwSLRqEza5ZWPZFr9Cgc4VWAQWriWb/OKpcod/viglKApL+5JtbulcwX8ydf+T+Vi2Ba2gfASLlVFkeHvC4oWtAvMdifGJzvBKZ3irN7jbE9bnhxj4Qwj2I/I/gWe9Ut9W2ve99tPQi/wcHfT+vb0f7buLj+70behQ4agUwPeN9ygosEQh0FCVWiFQKhV7TVBw5RAxHtTNwgA8rAzl277AWgI7+1KqpZAGywH1vU37BlpGgEdH9PEOMYHGlD7QArCNvn/T1uBCnA24MGeTrvSFTBtvMs1ULGvVk8YdkglXQKQbKmnWajb7jabJV9+hpxlNnTyoSxOEL6jUjrHm4XSavUaQvIMN+yuaKyXUAV/MgyxdLy+v3X5TjXUfDlONrMrGg5HkW5bFWpC1aX+jAVogWyFvU/+GAtRAukPepv2V08Pzyuvq8ineLdS0rdbZbZ3lfLPqiE9A1nmbHyb2wyS4inT4UHdi+Ypb/14+Sw54oCl30dy4EZuUs1CVaFBcJFXAFtlCclFaJFKAF+lCelJcJFPI8e363kROIJkZ0i1Ea07hLqmmzLT6I0PjPxoDiZYEj1joJ5Y/g0zcmmxoTzMk2ffJnua2TXmID42R95KUIAlvbDjpqwVaRQ00+KZE+YqE8d0IxevUGJbmC1jy4+hrIqOs4cH2fEfcDf3tNaz/CtdwA9lwQ9FwwzXVbTbZ/ZLqc8PysW32/CXQcAOf5uO3evmR7e3EwxKEPfNuArcxRsM+MZxRclCjPr9HuC1dQPbcn4bwYO+G7LWnF8ZzGlD8Fcem1ttYJ5j70x6fd1N5SNlWpVlyiRHhY51252EdKZgZ/73NkjJ4N4fvSFPA9wm3SYw8mV1Z/tAlJ7+0UBX8k1MF6SexEdvSggKTcbUa6yYFpDkXq/roVDaGWp5hNS1bZuubtUjylOJWYBYOQf+WKNCeK9HOmeAcTXqWLjNvwyjh1iHRPkV61pxeaMUigc4qgc4iEWpUJZy0fs3WRPEjNiRUG9ZUVt6whF8pTnMMv2Qq7C+otKthQVOwrkFhXgTX24CUOxaESx5SBC/jN8M+uljGjvI=
*/