/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman
    Copyright (c) 2006 Dan Marsden

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_STRICTEST_TRAVERSAL_20060123_2101)
#define FUSION_STRICTEST_TRAVERSAL_20060123_2101

#include <boost/fusion/support/config.hpp>
#include <boost/config.hpp>
#include <boost/mpl/or.hpp>
#include <boost/mpl/if.hpp>
#include <boost/fusion/support/category_of.hpp>
#include <boost/fusion/mpl.hpp>
#include <boost/fusion/algorithm/iteration/fold.hpp>
#include <boost/type_traits/remove_reference.hpp>
#include <boost/type_traits/is_convertible.hpp>

namespace boost { namespace fusion
{
    struct forward_traversal_tag;
    struct bidirectional_traversal_tag;
    struct random_access_traversal_tag;

    namespace detail
    {
        template<typename Tag1, typename Tag2,
            bool Tag1Stricter = boost::is_convertible<Tag2,Tag1>::value>
        struct stricter_traversal
        {
            typedef Tag1 type;
        };

        template<typename Tag1, typename Tag2>
        struct stricter_traversal<Tag1,Tag2,false>
        {
            typedef Tag2 type;
        };

        struct strictest_traversal_impl
        {
            template<typename Sig>
            struct result;

            template<typename StrictestSoFar, typename Next>
            struct result<strictest_traversal_impl(StrictestSoFar, Next)>
            {
                typedef typename remove_reference<Next>::type next_value;
                typedef typename remove_reference<StrictestSoFar>::type strictest_so_far;

                typedef strictest_so_far tag1;
                typedef typename traits::category_of<next_value>::type tag2;

                typedef typename stricter_traversal<tag1,tag2>::type type;
            };

            // never called, but needed for decltype-based result_of (C++0x)
#ifndef BOOST_NO_CXX11_RVALUE_REFERENCES
            template<typename StrictestSoFar, typename Next>
            BOOST_FUSION_GPU_ENABLED
            typename result<strictest_traversal_impl(StrictestSoFar, Next)>::type
            operator()(StrictestSoFar&&, Next&&) const;
#endif
        };

        template<typename Sequence>
        struct strictest_traversal
            : result_of::fold<
            Sequence, fusion::random_access_traversal_tag,
            strictest_traversal_impl>
        {};

    }
}}

#endif

/* strictest_traversal.hpp
GKu4iIRBazaaHzXfVC5iGR6BKEiVR8BBZTo2wvcKvmN8d6jRK/Fm+wZll1ge9oU2F9nv408av/+kunpSeyOTscw0zU2EX6sapo167WaRn2pEb3vI0mSWpLeGHaSVt179SxUNZEvUZfnR+WOj88GAPFEhEQddjgSBetakeOuGw5X3zxk05J+1snuKq9vZ0zdXqvIBU0ZJmhyPmTvEoUDjvbM+8E8gGox1B8B4rXKFuhMxgGGMhsCP8v7J+RaEhqC/KlMKgaA5owApA9gfxV62bg8GLK8Xon6W7qNBvxvdh3wd0KkHHIxHB+pUU8NsX/ax6itn7TN0Zzs5OL5xR3z8OJbZj+G+i7Ik/d1k6d1ASAI/6bhpLZ4X/bllf8t/eFBSU3BfUPYGa7c7tdfdcN719rkhd9G7tW75mNTWJtVVs1ZSYx4SqnuqOlIXw9bQum2U6Jiz07F0gw2LpLUOnhtPQ6EnHe6BiiD+L3u6DTAkn7HI8pOQAjN2+jTuK1Hm10+vnNKDy14pJQdrcuKtxUf4EnL206p4vdrhU5jpf6Ui/4UwWOs1G8/igTPT7PmjKSRpRAxNjiVzh8OfKXOj2QX+X01NJdPvssSPv4CSBzu/ApvrNNLwRfRWS+rQI9oMcTsVV9/pjSXxULxyyXorTTUMzTtX/x37R5FZAzfHnKlxf+cUh6DmGuBhs2CrJJGnkrx7hH3Ob9R22KW4PvahYr1nzwhz0z6xL1Eae+VhINRIn+WXMX5/dD8FIY295PZrt5/SfpT7M/g3MzTg4C4NugjKEhpjNCFqi6QUZ+5gVtQdLpydumMM0uaVL77Y/a3SFjnMdqyENu1fQDJX6d9dCIOV8etwejvx68h7WUI/F1DIfztaqC7rbrFKQHIkmvKHLpnUwR/9GnP+KYtQ8Bqf0zmTunQpCgrbCeCfYt0YmIugn6KFenyBXk15GrcQBO0Px7Zwy+ldkBty5982R/D+Ev9KpeO4gje/pKwlhFWSlypYYfx9pTrgQbpSm2KWFSg4OTm+NGnaeKSWeVgw6k/hylP8Q2qUqqH7QzTYxjvLmwqk3ZL+SoQKGRqu6WR16u57K3iphXb5+FN+34P8fevVcAOpW86mjhDetuWwdd8pu9fK9j5lV9S7tM3MsD9f8TQEJxOHsNcqadlaonb128uSaSHuxWG0zuwpNxXqt33W/VRJM21iIz7iOZNI7pods1EUClfeA22KE6vRWIoTy9ElClKTbynh5eDScWUBqoIjDncC+fLzWSL+IVZXhd+vwPt/pHmkeo6+vZPid2dIpYW4MsTSllDIW49SCyaNJdDhqMczEFp6R2hTSLEsFKn6Ds0VJQ0qUwiwELRF0csOjStTsLIIvsaTi/qtz8vq6hZZ6v+u2YKM9AZFLhv7SUROj6RBWWrRXMwSJ32ogoJie45iFG4+5HXPRLIp0bI/Y2OY3nnfMeOXvsQep0fayuxg2e0dZzsW49RPonXpW2qeTqqy5S10XqOa0mi0YjyCEw298hqQVqIPODp0+oj7mEN5Y/dbWzeA/5w++Tx5yywptV5eApah9T7uMrhNCH8gQYoiyvybmNwwlwWW3DCvhZjcHukNoxw+yff+ROlw0aFEhvAD1+LEwwBOue8ZqmRy30ndxOTmSXjC6U+wud0YQmm3sD4zpNM6UlRYVwu4MMQ/BfQlvgl30KFhv/vs+d9VhZOYEKXZ2ScLhFeN2oie7ige+e1YIp/7D+UAfjL7c47Q2R+qGSnef5qv/tKSiadh1Vh/awsXfPetaJxAL7LIC0OxYr7asY0r3d5Kmdv2h+91In/i5He+zJL1z50PWeY3DFVqugH3KvQV4h7SKcZTCv5OPWn6OKxIzLgfvAe0cYsN5SKC30cSbMkaJgxEEjnI0HuYZ6hEzggj8MY9oap+Q1Eh83gFF1iCMmp/2qKSUSyZBFz18h12GVUwUnDbozRel8RkCWKqabkQOCPHb/9EBdUbhAb1lQmzW1FQ1XsQaBLlZZpAvWOPF7BTp2Z1ykyWQl9bQsEOPiwCdZfk2vmeRCpvgjME96xGTwKCeE2/+fd8Bt8syt42yVITxF7ybNSabsVy/j4sX97y4dU2A4JFJKmXDGtOWCp2150ye9vocmXwpah2v/FI8Qgl9SfoCyX1JUjHTZqNHlKMmUX+pF/DFuJTlXIjme9PNAgPmEgUDV90KQ6mpXYpTqCtFDIzH52g+GT2jVvuNylPPH00adIQnohUUAVtnDDb0rL32nfNJE6hgUhKGi8b6ZLoqXco8VURAxZTfXOv3PkEyE059q0IJkH2jLqbFrPKJ+87+cnnayhtBeLqllpLDa1gjfI4TvZl75v8KnS9BDIlTyUKlB5seMtRHXV9F1QyQg//rL1fmJpSaQ5y6jC53GU0Ekt5cxPXS4VnIt6r3GXE3OpOwPnf+NSfqCdnxS/rjxS3OPL+mpWr7teyBQaAL2dKAus5ExsX4b7eQpCahl+JW8k8ttIPO7FfThDnTVp0kyvE3r4l1vCnVi8fR8+DLG+HO5IL26mfIwGH2L6oBPH34yGmSxT3ft1oNwu9NX/Ebr80GraQBz4KUwdJw/qsoCmh9E+MeY+p6FJn8Y6lsF2pqXvxm8pdlTFnR/3GQIKnISHXr+OmS6AJn+SfiOAJeexpyxmM6bUQl7b7pPTCtjgtf56nKQYg2klZwqqdSnToCCcEgwqYO5S+HjqyEhEJsbjez8Oicj7Bpspbld/n/frP1lveZFopiFc+wBQDjl/qPIpbUy8pZ46+UCdKZjBQXWQqpMCnV4oOKUsp6ttv1AlYTtq5HqLd065/nPbt26+UGhSwuYagQkIviwqgNEckSxmaeAb0dzo2sQ799q7rS73LOVmrmBJw9Adcc+CE/KTqpLMyVxLEK01qrT6xw1QJAued+st5LktNbQz6ItQWadhdu8YZkbFPh447QYvw2aF4c+LEeD+IDvfE+riVvf/D2/XDFqu/jKPmiJyxPlO9N1gI7uYiLySo+x6lqBynA50A7slr8FVgSMaz0ZC4JvppR/P980mafMdE5mU41uLQs2SPbStVnf1FEwFU3sq+fvYybd3W+mLwE3GuxFHSbRpK0BOY5auARkFHC9YsTrIgCOG9zXYq2YmUc6CvpM8eWpR3tNGhn0C1bwsJ0LanlIm1gT5nweyVJGjtlMT77nsInjv61vtI2DMZ7Rxo71cWYBuGgMKl2sspJulYRVLg/hu3RHDBpy/6mIaFw20ceuYK2iZbqIFmF+sdskCvxAHYNgR2luqmM+W2SkEToTajfc8HqvB3y0kxjxHxiDNMcv4TByGEe4A6S/PEAconZfUkeV9zVrOD5lTC/P/Blz8f37UobUFWnNmd5pxxnNadnbx36iuT3L6JkgpHMGrZY1XeCbYXxi4oobhz6cuZ7+nObdtRgoSSnLfG5u5wcy3rtA+Aj92GRjMTGeyQsNzkQuAm0xoc8mMH8XzFdhEaPzMvvuqnFeM9XTErhOg1i29cpS5Z/Z6zyopuc96MMmXm4Gl2SfUBbv3I3QRxT3JuiHMuOciq3IfGHnT+GGnVvql+v0tu1w0xVF7xhwkVHM7ZPly6NzkDAuPiJgbAx13TTNoxUwRKWDPB8lsFzUbp64ZV+1BU+5d3zF1KuEXcCth2r5tzpj4+J7rtqMiaPtu+7L0Vvuz6jBDrcz/Gvspdl+jsc+oGSl48kIJtlb1zifnYLzENNeoX78NzoyuB+0PO8DNI4inE9O7hbQ0w/BCO/L49ViYFnqc/NMzfFzFNOFUlK3Zn802Yrj8JNYMYlBTVB9vCvNQOVssJNIbNluu9BHB+i414MHqcP4QW9mBTGidHtLhXvCBVrkmjmMC/TI4MQAkC64pw+ktTfz4ZDBg0E081Y+suMH9fn0H/XckPMjQ1FQWG59Uq+A1tsl1agim6i/ydoGtCAMOyYv0ZD8OixWrB/dqseSYPgufV9m8g5luc/E6D+WberQaajtr38hBgYMHInsbYStH+BssT453xJolz1gnSyXiVsxt53/gAQszd6Xq82tKTb/19wv92boqi9Paxz7SDA4yzEAgGhZ90X+i6DW03OmTcS769D2ssgO40mp4gavc3hte1daDdA2bGOn8J/KvTh1XufvPplBHcfoh+ik1vsb79fe/naQYyq7cvuf+O9nUk4IIwUL18f2Pgn1hSUIXK5H9S0eNlSax1xomse1bJrHZ+KQbN1smUwnqsGct2pXfWRFg5be4F5sCPPW2X1itS536/bE3eW57Y6AzYQM1fgGlaCH+xJKjOuQFRkTgyt7ONtw7u/JgHHswhth93yc3Rz8PtKmXR5QAkuo2JAVzbq7DqItIV26vM2n+gjpVEHOaLQ44PuPq+3eZaFMMlhphjkTtDF/72TI/gPAHmmxmy4idinDgnUKfYsrF3Y3Fn7sklRiEUrVITMZbQU6aHuzpQ7P3FYMRHzxfgkxFUyFQXxL4A6nt2q02smZCSrae6ES2ALpJwDNf0u7vCJaApSHjBEH030n8VCrT2gAP2ioFOpwmzyhRm4EOpn57EYQuIp3iXelkjkneG+yJsR2KfSv2O95aX7IG3M0DtcWDyoTMZlSHQQ/wMsJ3Ex+axEFHhZPTBsDLq4iej+v7p7iyfVV2GEkGOvbuyRw3hn0GDypU5nwGGI70YgSaI0fK25KeRzzkkRbrHxCePKnwacP3Jplxs3mpwEG932WEiq52edE1b7doY4czH2gR7hufoZsIwa5kX64sXMe+5IR/hDuc3qo0K0F6RaEcTBgQfmWpFZC25pi2ZxuR7DsrOCtfE5XsyyMwKO8Xme07SaWO1i3+pKbekatcbu5N3i5Xdwmua1ukyfj7Y1Qej431OV6UbzGj3NNN7IR9/hd3zyXyHZ3wryCsh4BX7fpx+/Hik2KMp3INkfxL2DJCw8nWOLTb/p1ncBs6MKTBXbVjt+ebKOWfG62GGMiWSfWZ8HYlsHGEpyvDmJDnpYhVoQd2UsNJZNTIpuBO1wbv7fHLwDz36uLXtarYnr96rRXfQpywivseqqhnTHjZzr9gvMzW023Q0f9XLFyEX1XXGyRPB9/AEwlViTJTinDCN+fToB+T8LRYqO9eTRy2z4q/+nyFkRnburoftd81Da+GxX21M4Rl8n7ljG0kmswK9fGGuze+eOondEHmTgHLoqyBzHQ4+NutzzDXGP+7dFY4/Hupwax4g0YKNx1ihmaeMGShnKnXz1kh5rZOnFQo/g8v639wGJfvQNwsAvfnauainfoWRI1ZWyiyg/slqgDXhw7fWuOEP9isUyrX1c2aOJdK/4ro//mmRoNc7MCgmMI9Oy0V6BCh+BKFRgsjGvL+MtOYcXiTdqMRgUxIQ0/9z9wxYYACVCPdEm9lwzAzOcrNFFZi38YTX1LaaD3Y6NcctgzKWBZTsjWNIFFUPjh8ShLtu1+EPl0rROgK2RB1ObuzEPVQ5A0bOW8HITpWwYv1xj8rQ421CRftuiZaPJobu5ic9B1AJvqJ2u6flpHun7q+w6g408LukWCRqJo/W6tKgCinTOYsZ0K0ECYI0Fq0vihEA8bBZaUjulWF6JFpKXOc56g4zP8CYfQEPY/PM9aodbD866RQABgfeg81gOETfVoubQ15LmCNzubcDYLZ/LcmWE5pldhKwja8IvvXi5zAemYcO5eoIy6k7R/H9o7iIJzz7OyT8/BQD/WILF6d6UA2ryKE1IfvfZ9XZOVg6mpYdI0KWliHBbTIxlW9Cfte1M2sTvvWMLidvZ9VeYx79+P1HaXk9JrnCqcvvT3/KM8yOXN5NudaVlw8IXah4hIObWLuKbVIO1NTXBoUGsjOsDHo4gzhrnKu1z3z9tP7BkEAIvOeuprnnznA5tyovq7sc5OFfbpwPvwM3zo9gQrRnZDQJnGjdcG1cIB7/eZ61rNRuJEuLOAD2L/InrWNB1bkiN64froVFvnTJovt25SWQKFD+M884YWiaivEinbvnWRctpLRsQo9adiztua8jEMWKF4kCS+HvC4Hf+iLbCQ7gH5lGodTZNBBnb6KHa71wwhPsKs3pXgUvNK1w3rrfmBPjdQhUXVXaSkpdTpFo8ZBGeg0Bi4C4GMXpvfakaZ8t6ygvZ7euawPNow6U+Io8SXgcnbY/Ba02OmVzre5h3p5uaPNKDaXGc7aAwKu8uGhUoRygnlwowdV+9gFMqjiOT+XZMyDMZoPkwrfwwrqptaNXyM3jp3BHR6T750sP+IVKHmorPD+IiEEo2iveJdxL3jutVbEH6wQpfDZyRTPnxbvuVEhp1WSMX31bRT4hYRlYn0TNNAWpGAFaRXlFZqFeJIgobr+nbRyDx0fR2vNnj4Ss7W0vTPhQyc6YD/IO+2x/mdkYJDi+WcitWJZbPDNhNZCGHnR8gS62b66KbNxe2tWkunQmiOT34fAkXAPXBLQELJWbGmr7dgKtxju+48KytjmVGuUBPvyDP4T1qRbE8TXICRYa0XxBXg2BVv/lacWCcWeIHqqDYiyV6NOQZo/URBVP8mh9uDw7d84Jt0DTR7EwuyCRXQE6oGIoRFguzzntqmwKD6Z+QH40+sRKGqT8848zLSxFqLd2bgdi8niP35N6JZIowQV+rmU9NDz86XB3uzigeVAXyuoSanC46cR4GWrluelZQ+eEdUPO9yiFDaLZxcXvIXwqIoOd1DzDABtVRyNThAHA9l7VTFYwuefj+O2gRr/zR5jfgbfdVWPmI6BRfSqPBmZ6INI29oROEpTwK++M8VHeqbd2dseb68JdVGYKQgvzOniwv3LEBkn1P2QwPS4cmSJmkm9HMu+fGHWTkL+cJYOK0EDWNeIA4C+Jb49aB/F2V8rYIJX++M7QAyRlBtJ79GkJG9nrJ48gCBK7EeF7ZMdGamECQq4iEiE7HOAHHliEUhLMm+kJEvdU20dt+siBH4S720oPNA6FnJfOOOsyjQFwk5BUGUgqt6D/BpAbei899aA+xZLBvoZD2P9vymjhoHrZJGQuA1KMGyl2CCvClvjxf5NV5YUJJDM8qT4OjHpfzR8LTJqvG/fP3NE9QcJeBsW1eLyPSoIx/f+mOoWNvF5Kgj0wPkFinyDs4BUeWNzb/xuTP5ya8f/GFO8HNtT8+3NTcx+6V0AhbJVz4I44bUvMw71HBn7OTVYSczL6eIKEJiAkbjo/P4p7c61IVhUjJfL+IROdM2qvsy0eB7iTEBK7ZZMjCCAa8M8uJPmq+hcoCvYaJ2iC8gDu/RPReQTgqQ8IfExhIbp9g6e4+CayxOWnaBonKWIQyw6h3v+y/rVooCHDPKBOv/c9Icz1APo4/sSNjSwBL8Hs+mfuh64BOAivcMhD+R9nepjTAa7tFbXV4+sxu5451astWDA1hAlMLYU4u+SSVVrBU0pb8NP1dkV8WhLVic5rK1s0E6IkO4zpiM6muum8vmY5hK9AY/wu5wbyupDP+3AQcni48lmlsp3vl72kUzeaAEgKSvFpf6e+bPFMAB02JHQqiahDA45JSaBvC1ccybH9FxAf1quqV87N0XuFxQCz6q+VCupEA0Tubsg/mv+SiITZvibbf5M76X+HySch9uVq/02w89wOOSmCBRMYfaWf6Ly0Y+2vElhD7NffrHNUEdTD6r4Kef/FV2A/+yG1GfATXDvNrmzii/fz5kYv87kK/s0w7/mLet7vLzsC9lfV2EhV6r9PA79A8TBuHER5GUKwz566/Ek+evQRTHeOZEu6xTF6vvaXf7z4BYqEceAEUQwgoeR2iKahYmRowICZEKj/ivxjANZuGdswIh4NmLgLAXybasUPYrpB//xoiI08Q+MDOUftiLD1wYzpwLg8sHNjhZu8K9YEUFVf3lH1DHI/9H92FnQQb3sVStKj3q/6ju6J+tcTNQO4zP/M2Ng7kCd/GtDvLB2Ujgac9j+F12zrB+ZpjNdLPP08FRs2rTh2jzETolI8PPSwW5TKlNBaDqryfUDRFGNJ++1XzDn0VFvyfLuAsu0CpPqXK6wq1m418Py2yrDgjoTm7rjfLZxvvH1I7l+OaMgdVEUx0KW7Iz6D+jMqssn3YIte6+4ZZNKAECBZQaLZx8glt6FnkAhHLnNIG9sPCOcyemKbifIeqU4JpT/deIPXWzT+Zot8oJvWNMWoQeLM+YDaSrOXbg/bHQO1DKcxPpXhTpCuMFuv8B2eL5fPTMyUT3CTywjJ0vcgSe/cYSsvihcduyl2OMPq9L5IqSDOAQD5PiQ9pegcFI+8Lz4lc8MivCMZcXsjdXgYY7hgRJB0//35VE5W9e+MxKcyrv9mgLJCCKx/kKkNh1P/W7Vym1rxA+P5HWeLR0CQ8VQ8LgGsl2sna+AA1o2NfI0JjL0iTwB8VkIGSDR+CcxN9X2OAuaqHSYbtu3E04CEDMydAn62xWf030Ewc3vagGPam3J2JKqlkEXR8YdUYxA30+JMTY9Lohzlrlr8Atmdz2x6FSBqNv4EY26Yez1ZWn/cBsCwbiXbORpfhTRv0o/ySpmj+hd6H7ismk3favmcq3H8FOPznWRGCdCAlJMTeaqKuYngwYfvrgHHqJfBh48DehLRElXp3QvUyxPbZ/+7FTcVGifbLVJSqk3MwJ64a84zEzV+jBYe4aV6CLOAkxcp06/zy/rjzt3zrnMUUlo3GRNUGxf3eEm+ahrZeyUoYfrazDAn81oLLeHOOTEAJP8Ebg+ueOA9FMkeD8x3Oxz5C81kT4pByuw9GhfDxK84lvfhr5KQ6s/ccIkoibC58LenIAhY4fJBWZ0Osc4cCWRXoAIQ3WC92RX9gdbv6aZKY8CE+/Y3X31Zpo7xOwawhJ6xiFKTlexZ3Tebs0LAul6HZ1KgwtZcYe0mXiw0r/Dw4sdXs7roufhdvEIcs6aRKP6suVz9X2dhxFEGldaivMShI47ca8hBHx7iZKhEkSOjXqtO4EUEyQQpviL+frtt1M4Kz/qQ9Ma0TeuH6tg5fryLt0WBETYo+/+aAbTrHrKd/JGiSBLHwA9N7uYJNmCV4VvqY994n3CSGW8GxoF3gRddJV/JZ2wEPjiiFm1JNbHH3LcqFsRFpP8W1iOdwfyXTZ/rOuyuyNWO0ObZfy2dNWXDG0Kb1mXiBufNDf0FmrLBpUcK7uLy5rofk/btP/jAaHXOQ130S2a4wiNJ3Ekd+ef4udaZIlui5xA=
*/