/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman
    Copyright (c) 2005-2006 Dan Marsden
    Copyright (c) 2009-2010 Christopher Schmidt

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_FUSION_ADAPTED_STRUCT_DETAIL_VALUE_AT_IMPL_HPP
#define BOOST_FUSION_ADAPTED_STRUCT_DETAIL_VALUE_AT_IMPL_HPP

namespace boost { namespace fusion { namespace extension
{
    template<typename>
    struct value_at_impl;

    template <>
    struct value_at_impl<struct_tag>
    {
        template <typename Seq, typename N>
        struct apply
          : access::struct_member<typename remove_const<Seq>::type, N::value>
        {};
    };

    template <>
    struct value_at_impl<assoc_struct_tag>
      : value_at_impl<struct_tag>
    {};
}}}

#endif

/* value_at_impl.hpp
8fkcTO0d3RffQBdd/ynmnIN7vqin16/7HGx/YJbW2wuT7L3E0fBk0vd0M+lHPpD8osL8CSpbbj11ORo+bO391gR8VqW0MX+zg6g4ewb28yoC/vVmtbLilCpOiH89s4+bY/yRIPfjRkwjZ5A++UvWsxtXxo6/FbcZ8Ubb6+2ek4LipsEuW1v5FHqcffxA+hc3ttdBd+/u3NMN3redlX5AxyT4XEhyE9kYU13upLpc2D16XbI3Oiigw1FPfdaG1ecsl/rcN6w+i8LqRGV36jhIV2WNdGqI5lrvs01boYxPgG3SQ/fan2ulunTqSvoARaaqrPun0on9SjCZjksP0bmQnkYR9wa3CVvBQPUc0m5rmkS+/1Op67QernUd99kU6jWiD1jbxLUPYCHcNc+4zqfUrqcPyGka2QdMM/oh7mWN+YxKJ8cXoKt+1pwef61+Vi/lv1D6A82ln9UEnmbOn2TY50/KvUZFqyyvtNDL54k084rLqiptWbLr0dfKiWLbIhc+cpD5vYqWUSk/eAFdH58/XlGwvpZ+8wXKZ2RSm3Hiqf1b3xGlH6ovcboa0Jlag59GWIqMCw8K6KOFP9MGl7WlyipbLHGV03kPrGFBiM6SZ3M781ulg3ID4QxzPqenVYayfG9BWSzvW7T+qFvgtzF5lYWekLwXKO9FyvtRwllGR66Xk3dlDPZr9M1QP2Xdo/5Mvynv1upXfU39v+HDUnWeav2u+62fbV2vz2xZPJcdECr7qua2AGfoGzE1SbIf4pe9sDSvuKTe560+W3IWlpY47TpSdrXXcNnTQn7Pq/I4ZeJ3pasy6Zk4vxPdlPMkW27PNtvY5Z4Z9rcn06kH83dNZqhO3B2Z7vW0egu7sE1VT0mqp7Te/noq9nnifsbcE+0Zq9ypLs842fkelVdW0X/pvfI474ztSzhwf2le5QTn/jb277rf+b2Zfb/yi9Rbvb2FXZB7VAd3wLMzjMM3fx2U5lXlF8XcVpyxi9pKjOMx+287r61DxsiV1WMix2g6Nyfd3y1tQV7Uu/osYQ9zbq5fSBm8lcweSgpjf57hZcnWb279xbCWdgJzVI9Xqi3Ny/LLUF1R7Kn/exL6znFP9HdO74pbf+Helpx31Bf2bqrNqF/5Iiv0/co5NPTv0rC/k/uHvm/dnL9DnlOLreyCNpbNFeMT8Fwzdu0vvWM+uV7rrcsrKIjBzpT0JyO+M9ND38Uw3c9ifa/874s9Xh2m/9fYIdRf71bu+pc5h218/Ut/ns1Soug7HrZp9B39ckxJiSx7y648s4Acmh7awwlKH7scO0TRPW3WKrLsKeS51i1PlT6eOt8hhvL3kSy+VpF+w2eYb8Thjixh02M5Dq9fnhD7ea0i67nWnIGPmg9VHUeZz89wr+uqrSP1fGea/j9qvsZJd+z5Mv4Nr2v6dXcf3Z5tIp/7xaZ/iCKLHn3MspyfUf9z97f7XCmXDJOP7sHy0V3XOWAbL3z8HJOP7s2t8bfORfD3R13tv0sLS81PG8Vvd3bomDrw/ZhrxasKxMsJ/8a6zzGccxtB38ZLbL15M/Gw+vzqLqHfgDrnb+lPm44/uv60+1ns6HrG7vrW0fSkN54edool52s5V2Wtvq2kS+0BdS9++dt5+8Svb+2uJx1NX3nj2bb7u/Sw/2TvTOCsmuI4/lJZWgdt1sYuWaaaUpmYlmEiNWqqifRmmqWJaeaZmQhhELIPsodBlD2EEAbZt7HvjD2EQQhZvve933v3vXfvnbeUEvd+On17r/PO+Z9zzz333nP+y/qub31Puv883td3yVXXHbj80aeWzrut96jFyelbp3q0hqy5bnG4L72oONg+5dtY+Zxs2xuUr7tzeXw=
*/