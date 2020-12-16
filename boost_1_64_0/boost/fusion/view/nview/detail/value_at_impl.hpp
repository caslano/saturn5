/*=============================================================================
    Copyright (c) 2009 Hartmut Kaiser

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#if !defined(BOOST_FUSION_NVIEW_VALUE_AT_IMPL_SEP_24_2009_0234PM)
#define BOOST_FUSION_NVIEW_VALUE_AT_IMPL_SEP_24_2009_0234PM

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/sequence/intrinsic/value_at.hpp>

namespace boost { namespace fusion 
{
    struct nview_tag;

    namespace extension
    {
        template<typename Tag>
        struct value_at_impl;

        template<>
        struct value_at_impl<nview_tag>
        {
            template<typename Sequence, typename N>
            struct apply
            {
                typedef typename Sequence::sequence_type sequence_type;
                typedef typename Sequence::index_type index_type;

                typedef typename result_of::at<index_type, N>::type index;
                typedef typename result_of::at<sequence_type, index>::type type;
            };
        };
    }

}}

#endif

/* value_at_impl.hpp
XtSlcPJ1s8WrpzTHTuvhMEhrviBoOrXnGT2MYZaj6odx1GZoQ5h1ffBmOrXLWRwv0sR4EfGhdReWvF7cvP/Jh9asc3qoZ5KW7mWGOrS+JFLsaOrY4bIeNuqkdc5cN5zy/FMPhUWeRZLbpXG+BVSXv/QwUCdt2fflN+je+xZey0R5yeXerhcaTfHd1sNeYcmLVcfQJXpaI+/IdbA4iN9aUWJA8yNTt0siWh5mL4+EXKH47nrP03nXe56uu97zjESrwixiwr5/U100zH5PD8HMolY6r9FY0rC4e3L9LJE8H/YH56Sx68H4yNTxudD8yNTxhaHlIVPHF4NWhUwdgwctmExdT/t9WZeSqeoShuZHpq6LGy0PmboucWixzLK2+/ic8nwg5q2wjdkLemgNeUwxoKljiEQLJlPHkPBYxuBIFQM8wRjI1DEEoOUhU8fgfOI9z0iNPGM08kxAa8zsV2vMR4r9Ka4TBmk/PPVyyN9h0MNavbSaUau3UJ6vqM3Q1G0W8Nq7haEFS1OPXQ3zoP0U9SyVvPaM/7SA7B89GJkt71cxkK5Hn6g90dTtmYTmR6ZuT/iM7Ummbk8H2hWdtH9ZSxajPvqqhz4iXenkdIPOxFC7fBN1Eaaaf2h+0tTzDy2PNPX8Q2vDzBpY4W+K4bse5jDrN68xXTsS0NIyuxG3Nw+1J1oMswK1G7WlPvqBfUum7tsktGAydf85furhD2HJ/8+JWRt+J0u+92GWcWOOC7RGovVlFrQ6RyC1i84AmUS/lwGAPV0XOGgemQxQQidtYOvOpSl2HwP0F+O6bPKyX3/eUSrPbKAzq3L49+GTbnkoncUA05gVXha4meaKvwEKMstUZ9tv1GZow5n5PsvUneppNcAvBmkDzvyrNsUXYIANemldw8LfUF0yGOCASZrlxSGKPSm7AYzM5nzfdY3Ky2uAjCzPB/6D91O/BxogaxppJZxV39G4LmuAfSzduhdhg6i8CgbYysoLHnhsFo15J6YDaa8f9pJrZHUD5CVT34M5NCwMrSiZ+h4lDu2FqEt5ADC+LryX6lLPABVA2p7ehi+UJ1plZv5vLpppDUFbbZA2dmaf5dSejQ1QXSft3o6BB6g9m+Beg9mcOVviKb5QAzRneZ6v8F6ukQi7jdLKzJpL97SutlgXkJY7fehCuqa2wzYjU7eZCy2Y2aoDznG0hqAFSVOf76KVEJbcdm9jI3dTe7ZXW627NRpTeWhGo7T4M5s+U3ydDXBSJ+1QgfSvqP+6GuApSDv98OQZGvPdMD4ydXxJGmbvLuOroIqvXf+w7jKGihARQfGhxaGFMJu1IumtYklo35iN8XO0U8zRU8QubMYe30OKOfvhvAVpQ1b5PaN04Xh+oJdmi9uSVTGP2wBNQNrOoWeuKOYagOcAOmm7/9iSRrGEgQbIAtJSzuTE+BwoY6+EfyuMvJ+B2izCAGmY+Tkjt9OYR7ORqZ93uFTp1M8f3KnMOuHFNRqDqSz0xmIHzT+0LsxK3l+1kebRIANkZtZ4Rc7vVBe0TGTqZy/uVOlqvNoQSnVJZfW7uhdSXVJZloq+Y2muoG1mNqHE/VeUDg9KFvhIq+Q/6hON3dEGcBmlBfUtWp7myngDDAVphgqfad2FKDwH0Enb9Dp3KZorE9Tp0g3aeovyjDbARmZFbu7PT307EdceZsuvjr9ObY0v8CxvkFb+8s03lG4azT809fxzowWRqdeX+GlyDCavv2++94umdkFLy2zad8MaWnum43ghU48XRyqr97bteBoT01V5qp7judGGMDMcXXSXypthgGzMhl22J6VY/3YONPodWOjfme7d0JxoeZlRu6C5NdJFouVklqFJeJBi8Ro=
*/