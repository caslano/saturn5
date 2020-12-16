/*=============================================================================
    Copyright (c) 1999-2003 Jaakko Jarvi
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_AS_FUSION_ELEMENT_05052005_0338)
#define FUSION_AS_FUSION_ELEMENT_05052005_0338

#include <boost/fusion/support/config.hpp>
#include <boost/ref.hpp>

#ifndef BOOST_NO_CXX11_HDR_FUNCTIONAL
#include <functional>
#endif

namespace boost { namespace fusion { namespace detail
{
    template <typename T>
    struct as_fusion_element
    {
        typedef T type;
    };

    template <typename T>
    struct as_fusion_element<reference_wrapper<T> >
    {
        typedef T& type;
    };

#ifndef BOOST_NO_CXX11_HDR_FUNCTIONAL
    template <typename T>
    struct as_fusion_element<std::reference_wrapper<T> >
    {
        typedef T& type;
    };
#endif

    template <typename T, int N>
    struct as_fusion_element<T[N]>
    {
        typedef const T(&type)[N];
    };

    template <typename T, int N>
    struct as_fusion_element<volatile T[N]>
    {
        typedef const volatile T(&type)[N];
    };

    template <typename T, int N>
    struct as_fusion_element<const volatile T[N]>
    {
        typedef const volatile T(&type)[N];
    };

}}}

#endif

/* as_fusion_element.hpp
MV6QWpSqSHnzxngnE7wu0S4bwf5bPDiLfhO/lYQ68xPtg3uVmOT7W0Nu4WM4i076k0dqpGaxHb0aomWjXCvN7CoQLyWsE1TqTi16dKWPQ7PCABXiviE+TVTIQXsdJmvzDBnscL+F9ntHqaBhibo2ZOWF/edbuG9T5LLjfpQPdyjMyh4cxRki35rEMg1cJKv9Ut6CjGXGcZtb3roldFpmafR/bsdBjWeM7FY/0ta1kjhPOdlY/E0Kx3N725E4rE0treDERG55ZGfuSVcez824OHB7ZeW4bI5j3/8GYWdqfY3ss/B1GbAvw7fKpO9zWRYkM/x/kHkbxvzbyPa6U1l5RQsu3A+NMt+npeWauAIqpQv/vcy54I/nf9LW54mw3Juc9CD0Cg+1DpGH9Qa+W1A7VNEXmRiX7H+QfyMOYz6RyWRROr7L/6tMEOekrW9Fd8koa8Xi5n/wMb7MhvvtQoviSsoa5jjS2QfQfK04hhjvGE8zSZ21y+uDnnaLDevDBC9qlajSfL6jzPHg3e47k/MMpV1ZJcKs7xcZDWYVWYg18B38vUiLKjkTl5dO14uhYzlM7W9N9g+E7Ym1LKjSxadj96N9Ze3lvQyAvdPWE4hkXjAvU4u9OXwXwF7S8nBGeEwdl5zN8zdc5aUhKwcQLb2G3SZjPm+MrZXh3ArZYm/0+UP4sN/9+Dt4v1M2K6aIiXFyxsF9KpxixmVU9V6/73O4w255Lieps8jOk9S9COJD7IGtMW6714xallG3bU3f3P7U8qzweouTXdHPaPz6oJ9gB4HbnyljndGmBTg66D88ITd44UE2yPU5kEcIsFdPO1eL58mwhkBu8O/iM5JijuaOYx3YxTa2jy48OMdFPQe4RIYj1coCaWX/dRBmD86UsNehOhjJVhqVUp4qfll/Z3lOrrW8mYhU/cwy62PqYUkhht8ELzjrTZZ2hgcfHaP9xUcQryadlpTlQOfyDmdojP3DCbZnTIbI4gx7v/zQ21GDDU7L60kN0xI9jf29LfJ32xra+1uEJ0mWMlIW57JeP3r9lWLMNVQA+ocxfZAqZqd7TOST9no76B/CzEQb0ZW20nn/Hh+VP+tDtvSyVgw2BRtw//c9bBfvTM1kk0eZjw9n3ygXvofxc+pCzb3yn/HXnjvgg508qosSFg1zPDHy+sPiELCzf1Bi4De9sG4HHZu0wcmFovybPuhfCpo+gDe8SRs6L5kqOxpuA/QEtOHHkzZwzpPW1PznNsz74Q+TNmiZtaFdwm0AD7j1Qf/+hvgk6Xh1qMG6sFm2p2q5unsAa8Nb4d74+xiXUyFcJz3GBc2HefpoxKdI4Sm7oprC1huOmmdqhksmuCJxJnLsJriDvFfA/h3xGSKY8dwrOwVeeIUf7ZQXWJD5ueBrOcEOvKb041jn4F5lfGe7VfhwrOnYKSHMFLtkeq3XK7M3lB8ifk6ydIZZrwnf2Sj/vVQOfEVB3nrx2RdWZry/mGArlzPTc2gxQo/3TxNcJ6Jj0Rd7gZ2NzSXuwQT3HOjXpL9Z5/5F2HXDVtZU4SVJFBQUFAiBRIEQBULL7nqxJaSdnBN4SRISPOzH2uDwsL2wIApKSugQFQ05/VBRUlBQUCByzjn+5BzmvnDunLlvwZItF+ebb+ZMvDMnlBR9z3uwslYYucF38r0oJkNwoYTsoMUQe0BtxtV7u3vn2lAudeoJxUv5/vo+FsZXa3duEG+O2kQTocGdjxziTKRk74J3bjvn5aIeL+cNKYW7pvfitTQ4q4yh5Ork8rXz5QqI9/Z3IN5h8dcpFiXwwQzm7tY79kfaMiJRSRaerFu5o6mW9docvgEQryciueRsyD1vNXq5P9wWhtlr5ps=
*/