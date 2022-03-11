/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_VECTOR40_05052005_0208)
#define FUSION_VECTOR40_05052005_0208

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/container/vector/detail/cpp03/vector40_fwd.hpp>
#include <boost/fusion/support/sequence_base.hpp>
#include <boost/fusion/support/is_sequence.hpp>
#include <boost/fusion/support/detail/access.hpp>
#include <boost/fusion/iterator/next.hpp>
#include <boost/fusion/iterator/deref.hpp>
#include <boost/fusion/sequence/intrinsic/begin.hpp>
#include <boost/fusion/container/vector/detail/at_impl.hpp>
#include <boost/fusion/container/vector/detail/value_at_impl.hpp>
#include <boost/fusion/container/vector/detail/begin_impl.hpp>
#include <boost/fusion/container/vector/detail/end_impl.hpp>

#include <boost/mpl/void.hpp>
#include <boost/mpl/int.hpp>
#include <boost/mpl/at.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/mpl/vector/vector40.hpp>
#include <boost/type_traits/is_convertible.hpp>
#include <boost/utility/enable_if.hpp>

#include <boost/preprocessor/dec.hpp>
#include <boost/preprocessor/iteration/iterate.hpp>
#include <boost/preprocessor/repetition/enum.hpp>
#include <boost/preprocessor/repetition/enum_shifted.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/preprocessor/repetition/enum_binary_params.hpp>
#include <boost/preprocessor/repetition/repeat_from_to.hpp>

#if !defined(BOOST_FUSION_DONT_USE_PREPROCESSED_FILES)
#include <boost/fusion/container/vector/detail/cpp03/preprocessed/vector40.hpp>
#else
#if defined(__WAVE__) && defined(BOOST_FUSION_CREATE_PREPROCESSED_FILES)
#pragma wave option(preserve: 2, line: 0, output: "preprocessed/vector40.hpp")
#endif

/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

    This is an auto-generated file. Do not edit!
==============================================================================*/

#if defined(__WAVE__) && defined(BOOST_FUSION_CREATE_PREPROCESSED_FILES)
#pragma wave option(preserve: 1)
#endif

namespace boost { namespace fusion
{
    struct vector_tag;
    struct fusion_sequence_tag;
    struct random_access_traversal_tag;

#define FUSION_HASH #
// expand vector31 to vector40
#define BOOST_PP_FILENAME_1 <boost/fusion/container/vector/detail/cpp03/vector_n.hpp>
#define BOOST_PP_ITERATION_LIMITS (31, 40)
#include BOOST_PP_ITERATE()
#undef FUSION_HASH
}}

#if defined(__WAVE__) && defined(BOOST_FUSION_CREATE_PREPROCESSED_FILES)
#pragma wave option(output: null)
#endif

#endif // BOOST_FUSION_DONT_USE_PREPROCESSED_FILES

#endif


/* vector40.hpp
KPIaNfJ8Ks+vwQs/vBK2Bnsq7sRmYd4hLMg9ala7KfUGNfXl4CFHM8L2Yg0UFRsNet0HbD1F3qxGvoMqWUgzRPgJAiS7bgiVGLXS2Lxs5rhgnoIxEFudmQhcnVoQHTnqVdhX03FS03maXzA518jvMx2OP29jn3lrFXI5Icd09kVI9/53mK4hOV3POToTYCrDdO8jkLexayWla3obM9KsrxYnNL2NaTXUCI0Eq1Et0JbvVCQjTbKNFNKs5rIOQu+MhiKtsorvVJwhybLbow6kXLYk6kACZnlRB9Ixmx11IDmzqd8hnpGmQclfCpQGatUhNn0GqvlIj+PsPeN9Kf9DeWkSsFabA2SmrbqozOTW0WwejMPn/oom/4zLy8bJS3cOIs2AB5rtZq7B6ODPs3WxTxNzxj4nM3vs8zK2OPY5hV0/GJepcgbjIkgmSxtEEWoquFr8vOco9E83x749G408jcJB6kKlSPothLY5+MINwtzCnwk5AAYs+dOFDwvZhXuErMJBwVI4TzAXlgumQpdgLNwmcIVQrzOqKNa+6wEUitl+AOrdhUwONaZJWN9/Aq9WCkbXM2qu3l3IAtljMReyQrY5WqJdyBHZj8ElP4agWnchc5RGdPzPzfhxAGPr+Z+nkWOD6jinJVqpsh7HiE8ErYov61kUH2znt5ZgzpdhOVpuQt4F8RbIfwJP0EW3TgqcMrhNvpYFyLfCEwKn0txFvqULbnSWsfXDlAQ5nPSOcVn4NYTz6beIrCwpkrUNzS5nRWXR4LeI4+zCFP7nD1JReE+6Vg16iVLk4Oez30YrjGMIa/w2WmEcS1hzLAzHFLY15sKxha1B6LtKqOwqWm8jn+VRtC6KQbodY19NYXeoNc3H8DkxaDg6sWkxF45SbELMhaMVO/8NtuDaKNzPvkFId6uQ0n1rOleDLFdyTpVHE8Klepyv3aHXsjv+oiivai8lZhZqeTKSh3A930SJby5775u43PyH2GceE7AYjoUomi/kfYFosl+Cb7OCUle93rv0QP6ycO++X/8I5Fy1J5E9hff6/ys59xLybdfQBfKt8SL5NiMm3076Ifn24/OXlm9R/Cgx0TILh/a29V40ZYbTQ0bQgjpSW0Ec8a40x01/dGhbSf40acbbW1H14Y5iWsdKygHno/TeYjTCSKKitNOocQmT8OxhjvyQWTmiAxmSXNYh1XHBefZougvk/xxAD+RqO1ifTk4ygNwtO3AX5yR5pTk3oDsI1UCZ09qV5AB4XG4yyHIyYGKUq/UVcgOXG9H12BpMDQUINLs8eiY9bdVt4NkYxpBZySECHgTMdejX64IIXw6uC6KRnY/We1cacVdWMKpvJ++XeuTMhfMJdF5fPRvwId1/2pH62gPq8jSn6dDid8gzFp0VIXxzoEqAxGz1N49cOE9A+SXL3+nj86PwDBQ0ex+4tP6P/qF3M2LtS/Zhmgsgn1d/aD5iXH7/HBqXHwxOO6655OZWWsPIj9/mhURPNF+CNO9RkFyFtSDPr5DO6+tWuelILKsC6KBoqae8S2hk+l0YRpJsCv2Xfhqk8FOAbi7V5cwDpRS1tSJiBCADCFlseYg64ArIPNm+w0LANnGIa0LEIS4Vrta31Yj4G/wB/A1SexmT+4faXgPR9soGPAZ/EH/r2Dj8dRTn4IDfUTx3gAwHob2Va/5n5+Xrcu6J47eC3a9avwb+33JWNQ+wQfper960QUi2sMhpRVlTEd11cA8hec2ZKJItbDHgOzq7gs70GM4tgGn2fRhHmQnYBIWX8Z4tOJSnsNPYRDo1zs3sGLr0qusW9j6lyCjkxSwVDHsrnIA4ib1C4bya2S/JYQLKmAHCA/rsDqsbJCwodTRS8GVq3C1hanE05Rg/Ic9KT2Pbhx6dCOUysVUQhX/Tb+2qsXXWeEEAgejC0XJ2Uzyp8G45u4ZirZya+36rw2I9ojt6OCSe4998z7syC61gwhiLVjuhTKky3VyqZn/2TBxGszuD9Z2JlhMGWvaneBjfci8UC8LfSYTPZW8mhRfjDhD24hms2bw2x82FKYK+EEQXFYNsNwUUQcDiIAXUqtkL5F8MpapQPe4jj1vBw6F6rD5Dk6eTcFlOI4Sj+x3VsBvVsLRomOr5o/GeibJsVsO1lMNtkMN61WMghB5LwWNl/Hy9GvJJ6BLwA6pnRqxA/5yI/6tLxf+7ULzpb2ItlJc99Pe4gsm2kWtia3U6ZH5FFFX3hhJUmM7KKYoxPAnP/QLs1DbnhFZXejTuotCFVDk7lEyVmaEkquRCUaqMbt1RKfNblkSZXyYcl7EehvGnYHw8Q+HmKf5BRsRYrtqGcDjYYaDVaNivxoeVsNcTYW3jw25nT5+O1ZP9DMLc6Wq+K9g942OuZA8moCwdH+Zk5adJQMewuVReM7T0lPzqdCFGepPJe7WKAz1LkOxjOL1oYt+cHgdyKus9TecF0bxdoke+/QX1yIFUPJDrmJobtHbp3j/MsIcFQIylIy5qD1Mz+ufTmKsF2tUE3U3dG/Dz0zTh2QZlTOFbpqWSFBot2P2nEwX77jz1tbWnk/riHUnhf1TD808n9cVcKjTfsiy6E8vCpp+Ot+U8ZqTizEcIgBtRVx5OAYY39BX6XgddkoMSeV6F0kNf2ezOIAA9X41DzJ3s9JeYr2rPZHyYi72fCHtufNha9u+JsJbxYXexf8CwVAqr/SrWlK2Ou9ldX8WLX8VKwdHUcF1Kq6NayFCrt5jKvh5bekoTXm8S9b+S/K9XHZnkyINWyIpSg+6rBFe/gX33JYYvgPQ68Wo1yakv4/la2R8TjoWskyIvUqO9TY4bsXOcT/R/8rwHO7M12gpYvySWoDsvKVxdnxq2naLfmxx9wyWjY/mAEgtxkyNKCTptCp4+WKpN0aG7BI0Iitv5NxyrrX9pqtMXara5o/VXwcXBG/6L0oT6KOxHoPEtj/G/vktF599YuZp/405joS5sO1P3C2yBKO5/1YcVukl1PE2OfNTgXtbG2Y1EvhuhztziIO95XBvDnZsCapALqx6VfXHc/4StSDhq2S0Jx0/ZgoTDzeYkHPczC0HcFB3/yfEAzn2pHue+iEf9GftLwvEg6004NrOjX2C6h9Q0X52Kda7fk/eWBLhXEom2sl8mHAL7u4RDZC2Ublu0/cmxPVHlmkTUHawy4djJViQcD7NbEo5H2IKEo47NIYj1KrR8KG1+9UbxOtU5gcIaILeZqkfkVDxlIwufQg21KU7KxxOBBexDDHQsxjk/NXQ/edjaHYUabP4C1ffX5FuYJPY8mYDyY9ZKwfepcR8hxwbV8TNyLMHOtDNOEJWn4j11VzMKdyVxYLtw5Yrq5zaoHhJ6XJ3kgWaQ2NQkD9SsmSHJAze7sMGTcZg/R3ffSUQD7q7LrzbzLWE0gn+gmSw6ev4cR86BRCovpvrNyQRYNCnCnk3ykNFjd5IHTu2zR5I8fOjhppzxwrfwDsRpjZpV+ckoaoQ1UQ5WnJSS8JB3YWazLsxs0oWZfd8by0zN5S/odhTg8NBarY8Peu0naFns0gaYFqSpBphoDwXu9+B+lrzfI9l16BA7DvA6tBbwbC/Wa+TARfoIBoXeja2qY6TkKG3F+gv1a/ZUsj7y/vGL9MeXksNfGR+O5Z07rrxzx5X3ovXk+5PTh87jrLqCRuEVkYOoM1NQ1fr9z0jVIhPwClkYN+LNTXbOZ+ecvtJBVot7yp77i97ksw86O+yDnZCA/XgC6GDJwLpRkUrt/FvA8Ibo2hMJYB8jsMwLgUkE7OMLgNFqDq5D26F2aS7m+1RRKpMjVIXceNWHUgaKNsK1XQGNH4yn/QJRE01bdmFaKKYUmFAm+Sc4mQDphnsqZ/griyi8mKzk7xtAZKvVquc0FfKIMB/LyxbN0mh8m7UuZpkJ+VV6yfbqZAhxOdl/XEHTh+3LOC3eOYaZQVGaGjiNMEHZpmevZEESqUYP2jGnqQ7GioI3iYNnRypD2oMgJY89qtDF5knowKt/Rmxjwkz2KwVFDQ6vmtqmlz9iLnCHU/FI4zJ97D6ADi0CCz2CYKIoUeGz2iTE5B+7ADFqk4wvDXvkgrKUlePFUn6j1z66QZ5JmrEuqiHbObnKKD8wKt83qvSu6wJFf23lz/U5Sq+aEG0wbJAX0TS6ONphj3gX6UxujSIaFTGC2H36AwRilIv0Uu/3eHdlsX6DvIRAV416bRu8M9VrGQg0kRweShmFklj9TqdTEUcV0ayIJoLIMQPZpsz22iM4NWiPoJl+tZ6jsohmL6wfsgycr9e4lG1mZZsRy2JStpkwcec1lLg6mkTqzy9vrudm40bmy/a136gz0d2aVn9RCKVSaWOPpsN+4lvwp5kDX2mPNeC198p2i9feR4fzmWzP8tqhxaFAA9LGQUgTgf+oxrtx0PtARJ2J8Np7fPYeFZ0d9k6tilWv/RBeVGXvZp254NHURDE/xpO8EKrkKWs+rqyUNnZqpPpRjTAt3ixyVY9XF8VaeIIcAyzbO9d1BaONOYoIL+GspUamTdFEL1CTemuEyXjbZxFtj4dahjeF3W4teCmbLfQ001NFGX0S1v5+LmENKWRHjkZMBz9oDDYavxGKboWyjzprEZPsedqEkSXbR5Fw7suS789WeiG3RPHoEk48sLgdCU7+czhXGlNEA1tyHZobMK2U2+/3m3X20YISfb3BVsI1GDB8glJqlKs4r8jhHTf1gD2zw5uHjWGxrTdu19vObjOwc/NxcVJNjjQV65F0CaI3ld2NhkebnlIPO7KV4PK++pS6oBklClYQjxKeKHO2Uk6YqF4F8m1RVdDqj5Ebm4zxRM5G6cXJTHuteu9G61N0mWOQDVwTBzRBLtHbvhF4OYCreeI31VUh53w1eok+fCRKjRYiM2kj0/hKmTWAV3jaB4jOBqGyRR32fgady1sawW4aJS3mszOVAhTRUgbtxhwIuFOOecuBrqAtAwGLKWeDIWG+Ztz9jXgBGt5DAQ0SkA/r2m1j2zhbhH/0OdyUMYJEuSVLWrJhrcGkEaZUuKTTvPQVbxurXi8aQtdBew13kB5gDoRSpFM6aYTbcs3ZF5WcJ/csht7U8TsMlEL6LUapV6frVHI8LxTg8TDfcxC8B945+H4N/HrhrwfH7MNtqa1pbQ5t6zJtmyMFwLYuS5HadVIHAT8UBw76QjwuxdJK7SlSRwrG+lU81h41jtSOcaQOLYa2JsP4ObwE+G+C/wb43w3/O+G/Av5LsQ5LH+vzLn28D94M3gze/fDuh/cAvAfgPQjvQXhH4B2B9yi8R316lHk0ugFdJIYNBSv9Evxfg38n+ti56vVdwT1YwuRvtfZRHyjjOIwAOmJxfcINo766gtFoG+Qk2iDj+7MvjkK+8wox3+FjgOkTNqpvrE1G1DbJxTbJs1GbYOQ9RfC9Af674d/m0M0+3LpMJ31N2PsrYe+3SaCxbNE4ibb6GmJSK7QmxdyTFA8iJdrsa530Vywy/yiOeeNh90IZGPwH4B+Bvwa8Ofib4D+7kNomC3CdBW8LvC3wNsPbDG8TvDHcCG8jvDl4c/DWw1s/vm1UHBXCcyn874R/bWFS2zh0UOqktiD3+HZI9hvXdtF+nY0SQYWbqzygfxAkp/resy/C+AUdez105GoQNoxDGk5IA3FKU/S0FiUrRRxQxD5F7FUy992gN3WRCT2SkNYeBjQt6rnNYFIyX1MtA6Yo3e7p7Lp5uEjt1rA/kzlnY2hv7oUWkKPmlEzpnXj2QZyA8+/DJ/FOzuGTcg+GDm/IMevUr5O6o+suMLhU4Sq30s77dH+9eRkupA33DH8q9WjoBC448VBALMySCMuCMEu6X7SQRWM6dDT8DWVogvfRcDF8ryAb0GiN13Q4fPjY4TOHe9KPi4MQPgCFygKGthRAfqU7vGWSDeJt57ak2SDuNu1K6xG5fZWYNvzpcI/0qWZd9Xoo9T6/qDPt3XA13opZC883NungaxN8uelrM3ztpS8BvozwtXcHRa6DZ76IAU3wNZeitMBX2/341QpfU+ErOlL8ApcL8G4wA/vHmzSa46cuuDEoxjfnq2KN1Bf5LCvnW36ePqcrGAubLPXrjxXmrK2RehtrpEijcFQlGalv4Jj/GODt87oc0+ebcvDIIeIOG7zwzyHPkZ1XHMvKkY05zd+gutgcwPu6pW7cY2eWjmjC86Khqn+P6v+pJmzGj+GD6CvuO3Z3jgX/CUotr7Aed6dZ/ZW++j5vVe/ZVwqqjGIma3DgtbRTUYv7EXxKnUr4p0DUtqDQB/KlGYYhGHlANAK5wGfvBcWg/1YSdvowH/YMnUw3KaV98sCOibK9t9Wi2HvDFLWctdyIUjcE7kijoJj/JvKHgXl9bBhXxJhkybE7aKnGNA7jdO50RY7ec0T4qdXfBlTc4henNp+jUWxSDOOG0IgdN9KPSOf0W24YPiad1AnG3MMwSMDwENKKQ3JnoJfTBfBlgtd7wFOBWQmpZ18BwBPVeGcwHmSwPoidKC73y91J9zXUgDQpsRTbQcFQU8CJg/AQUuICRFmZzx5xKpn/StfKR+TSUbfGoGkKXFvb9IunNM2Hf7Tyx2NlTsYhus+l1U1qTFuiPFj0D9sMeE6kG63wdAkGr9Zbpo9ip1y9K9sodzad1FmPN42kiEUvc3jmr0B2gKZxc27EozTMq3C62FerAbVOlr5avRigQ+QhXYt/Jw8iutdhDKdJK43Z0vvKekiImoM3FddvY5KPej8nqKco9VeGr3exOmiMSjS1jYQxa9hhxHPhgtnF6lfjHX/PYnakkOFV8CAauc21lq9BcbljGRp0IiM8J9xa1nknxPPWj1qHvGKvbdE90Fy8DydZnr+zBMRv/asF+UK1rBkqMkqCC6qxyYEUYj1yq3fNKEWR9a/KJcahgCRcX7CGEyc72e1YMimiCFco9r7w9IJ6TjQPBVIE3smujwaJugn2E5Arww0njnALsDixl8ApC191MZEywc24Yzg7cRkZ7uGAw/cJMCycYIcgPAiFX1COyip8zEK4CVRVSB8pgC4zW3xbvA99Br0jvSO8dMgBNcl3sUIA7ZIj7K41Go2LlZQh0trupE7j8e80AITwZTLO9wvpTpaPJjJqslDtNGpIOQy6jbVFiM/zQNhSaZ9i9VMb8U/6QWzNZP5b4znfd6vaezMg6yIhg0DY+1gaVsLFPl2K2iyoL1AkrAWoObF6G1CM/RivHGZX2+NqOUiOqjA/DNRoldcYc//Ev6lfXOOFToJXkAi65eLXEGRZLmRa/fyb3fLBwClT+sHDobOvTOmqOfvK+oTg/cPcR5Mo/95itfy1Me5DZvZ6fXaTs/zSzGfWwv+K+aQtuDTz+esNScwnxl+aRoq2ZjaNZG9N5V88eLQ3KHdb/U0nZx09FUSbf8nKfzt0AUD9fax/JmoanFyyyTtJLqn1rtTLk2wZpoUGNKyT0XmDweQp2SymsUVVdNmSQ28zdOdB4FS88yoezrEn1qjmWRzcUNHmFNEslWxOwdtdUEUByEV6DBw3cYMKs690gNWgqg/K6b5/xT3FDVN89gGnW48sdHEVdf+wSW7C00TAUqDtSqRefRNqnGlyaUS6d/P3sbFhyZ12vJL6MuRyGRqoAEQuhshAfRqEhrsSKivjbRnL/vTYuOynYva1FXhXMKTZd7dagsvGlWAOBv9XZTCPKwNFj5WiIVoK9XwX3iSW2znDP9w9u1N+Z45mQFFsnVsmyoHKJ2SNV58TnI/XM3k04VD8fmeadKAfUDPKeykT/cIE6aCWf0WfE/4GL7fvwrUKKaBtS6Wgdi2/V5+z9WvQ7d7Jru4Kjr8P/P+LfvVh9g/rVwPLLq1f6ZeRLK8pUfWrFnDuMcOjCP4blv039SsE/rf1K4z1w/pVFMZpeH0M/0Pwfwf+v4f/a/D/V/i/sOx/S78ibChYaQ7+ZvjPLfn/Q7/avTyuXxUu/0H9ak8JtQlG3vMcfL8D//6Sv6Ff7V7+39WvCO7/SL+Kwi6CVwn8nfBfC/974F8L/83wl5b/b+lXKo6egecL8H8N/p3L/5f0K5Aj7sFxT3eLhmbdlFLTjsXARXJLjd5STlljDv9FtvfTZF0fdHicuuttzr9v6wO9QnqH/YQ6b3YiyHbgRRMbWWysG7lZowElAkbVJoT+Ippa3dinwZ7czv+73aS1c7Hc0q8BmUvNagBGHK16zyhB4WiRRgWFOy7FyeMmMnHXVdBtqn0Os7j1Ztqcb+8FhVAtrs1uqp+CAt2HAFsnGr0ihxLMlx323osyWY6ZmCGTXsrEQqojZXJ8DDPhav2YyWdLaCYWTzk+zBw/RvMKIgy2ITx9wc5ZVDe7AwLCIfbpvXii/CUQTvfWAnNiVnDvXbsYvu5ZhzF3prFfZULMj1j1Pejekc0+r6KPaaCDXlkJwyeaP1YMd0Ka0BEs5iYID3dZFZA31xUsQf+GZiUD3yB9FSxpBd4uGtjHd6FZTZPIs0KIz4ohE/bmvYka4/GD0KNkCRSjgVjvBK1MAR1sKkQNht14qrOS/dGs0dTijmOQyFZW0GA+YBvmW4wAw6UsojSLdiyOqdFkSmJahYtNyiSBILNVvYNvpV4JW1zsHT34hrpxZjOiE9MqWNU08LD6i9gHhYB7I9JKL+J4ZyGe/pe/pWu6i9Bi6JBoLMjESvIt72pUMrUNgKQ8liJe9/zcB0mD50CzVrohNtIJ3/ILPJPkKme3QX5kdJRvkaJe0/O/Ry9pTCvm4JWAFSCrGMCvwq0pZ1MgfgxkKvpArYYwK514FSY+Sxd9i7ofqRkJky/KP4pkoL/wTLTfyMkTnGXsF/eSCJzoIVY/+6MNkB1dTDFqod206piOY90aI+uHaJVVaJH6h0U7k2hhc/Ljol3nTSTahf6ReiVN2IKEN912FiTAsZvi0Z5Xo4W3ROU8sgTbi7aAbtk2ISr0hQ066EzQCSw+1Emx1znZVFo5MNGtV4tQ4rtIGDx39aWFwVPkL3cka6JmdV1B7WbTSBk1J4Sf6ESuuhZQXvGHlV8Vvf02npO3dQgZnqAwYbh7rwWihDe6krRAcdQqRpTM59Di34BKgvh+gd4oOME3aYuDVvuAFchZTDuwCiCHTZ6zyJsyJoM+BUpr+oB3ERZg+BPvIswlUe4fbohnboxj+JYb1Yb4xSUaQkxEs6jRwg/97Ybw2c0onps=
*/