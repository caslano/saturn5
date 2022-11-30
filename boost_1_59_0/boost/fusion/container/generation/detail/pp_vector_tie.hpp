/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#ifndef BOOST_PP_IS_ITERATING
#if !defined(FUSION_VECTOR_TIE_07192005_1242)
#define FUSION_VECTOR_TIE_07192005_1242

#include <boost/preprocessor/iterate.hpp>
#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/preprocessor/repetition/enum_binary_params.hpp>
#include <boost/preprocessor/repetition/enum_params_with_a_default.hpp>
#include <boost/preprocessor/repetition/repeat_from_to.hpp>
#include <boost/fusion/container/vector/vector.hpp>

#if !defined(BOOST_FUSION_DONT_USE_PREPROCESSED_FILES)
#include <boost/fusion/container/generation/detail/preprocessed/vector_tie.hpp>
#else
#if defined(__WAVE__) && defined(BOOST_FUSION_CREATE_PREPROCESSED_FILES)
#pragma wave option(preserve: 2, line: 0, output: "preprocessed/vector_tie" FUSION_MAX_VECTOR_SIZE_STR".hpp")
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
    struct void_;

    namespace result_of
    {
        template <
            BOOST_PP_ENUM_PARAMS_WITH_A_DEFAULT(
                FUSION_MAX_VECTOR_SIZE, typename T, void_)
          , typename Extra = void_
        >
        struct vector_tie;
    }

#define BOOST_FUSION_REF(z, n, data) BOOST_PP_CAT(T, n)&

#define BOOST_PP_FILENAME_1 <boost/fusion/container/generation/detail/pp_vector_tie.hpp>
#define BOOST_PP_ITERATION_LIMITS (1, FUSION_MAX_VECTOR_SIZE)
#include BOOST_PP_ITERATE()

#undef BOOST_FUSION_REF
}}

#if defined(__WAVE__) && defined(BOOST_FUSION_CREATE_PREPROCESSED_FILES)
#pragma wave option(output: null)
#endif

#endif // BOOST_FUSION_DONT_USE_PREPROCESSED_FILES

#endif
#else // defined(BOOST_PP_IS_ITERATING)
///////////////////////////////////////////////////////////////////////////////
//
//  Preprocessor vertical repetition code
//
///////////////////////////////////////////////////////////////////////////////

#define N BOOST_PP_ITERATION()

    namespace result_of
    {
        template <BOOST_PP_ENUM_PARAMS(N, typename T)>
        #define TEXT(z, n, text) , text
        struct vector_tie< BOOST_PP_ENUM_PARAMS(N, T) BOOST_PP_REPEAT_FROM_TO(BOOST_PP_DEC(N), FUSION_MAX_VECTOR_SIZE, TEXT, void_) >
        #undef TEXT
        {
            typedef vector<BOOST_PP_ENUM(N, BOOST_FUSION_REF, _)> type;
        };
    }

    template <BOOST_PP_ENUM_PARAMS(N, typename T)>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline vector<BOOST_PP_ENUM(N, BOOST_FUSION_REF, _)>
    vector_tie(BOOST_PP_ENUM_BINARY_PARAMS(N, T, & arg))
    {
        return vector<BOOST_PP_ENUM(N, BOOST_FUSION_REF, _)>(
            BOOST_PP_ENUM_PARAMS(N, arg));
    }

#undef N
#endif // defined(BOOST_PP_IS_ITERATING)


/* pp_vector_tie.hpp
QfxvRQz/Y7yT8r9PYvnfCpn/OSX+t17hf4sIIqiAIYE0yTxvUSj8IIZMjcWi70Asb3ujOIa3jWkkln0O8bXi+MzNXzzEqoj00RrPnuoiPW6+eaUiT5kNQMwuB6mah6bWDtwzS1I19j4cpkuwoe0FQM92UV73T1CxkGbSr8KGD/fpBOVUlIAI1hL8aEUhvdL4kVSBisrB6rI3kSw3BYu1kCk8mIiidA2S0LJYEuJkUXpP1F///y5Pl0XpZ9kgeZrH5ClCjjgBeQqoW6AI1K+nIiU9FBWoPxoqT79TElee/vyjGHpqKpHo6T77EHn6XUZcBQwjhH3iLBKcCKCtZT40QGg8a1YwaKR9RC/n+wkTpUhtLnONldlSzrsHMGysLDyXFkbpS82T0gqVLcdaZgEgR4AnmZTnjN42xd1vYAIxNx+A/bdkAUCGLLbTnZtvsxn2HHwgeA0TfEhilZkBWKRxtHFt9+L+IwxstssI+hiqtoY7JeGmyANnJ4WpGYW1Igu+4rY9j7lfEshSi7xpKNJx+wz2Cj6Bacl5cguMdSPbd4jhzLhsH8RsUBGzO1DMgrpdH6tuX/5UVrcLfS07UMze4vtCZv90B1KF8WwBnjxJGBVQCZs6aP9fEE/CNhYMlQdZ+nj2X1Bp+MA7kIOuj7TzLWcgu0zTqX70SZYS6cXG0tDXjFPxoukF8iz7tsxI83I2yLO8YRqwC6guhB+S1GxVBMimh5CzvE/fZwkPg06HPreqeFEjSRgACS6NkCVpgWOe6aECbehU3V9b667UeYcF9QVdX7D6kEK3bjPcoDinU4yderWxUzF4ncHY8TaZya9KlWORvAQ1N2vx0m3M+hxS1y1OSWVG0vvBnI0w+p6akdauT/Xe5WtBfHnnhJZGcjjvRIIAMgRY//z4sJylAx4uZ6nOM8I3oPcafb26an27fnbmpY4AFAQOlt0MiK9dRNiEmHb/+/wKmiqyYjvV+0ngFKbiBTit+Smc8Hv0RoUyVKeTMfHJXCiDPYZP9TMPHMNzMEpwbo2wNgLQBskzydlhq75nE/+4RHYgTmF9kHwTBDtvWaK4Nc7TRvGUpvFAUDFYABAu8HIGC3qcNCRYC9eA90CwSd+TtNpECVQh8JEUMfk3UuUxQ2V0tB7p9licbMWBn8XTSocx2bjTqQJGu/whsPUWGGvmJTotgUhtSVR+/P/Ox+XqA9IsPJlSs0GeganyDKzJlGdA9sDx3FbMIzAFQN2M1rnAOZwJeBxd/3fHs8o23q0+XuxgRtnNykPkB6/Et/+RT6VjIJS+wlK0X+gLIBCFdLryYWxAV4g+gIboLAFI3eOg+l5SyKVFaxqzXS3X0qUknRTY2NYtON4p29XEz/8sZecBx0haNyxVCo4vApdb727fVYNnONiEAz8DTr13BVUCJlANGDrYgPniVujod1xq3N6VkyOuIOMre5dNHpA73H5T1QDGyMJeg/VMZWUwiVUMBE8R7cW7kNvLhdw6GIBLri33o2W9KM1gP3IraawVL1zmUWzhhvnx9S9P/P0l20sCUsGpDXdWsiMA26FEpZ/of1/Z3lAxKTThPmfRAHkP3YlA3lhPU+0RMogQfQVZqiNhaIFuG1GqVfAFOsn6VsGPjDHA/WYWCjVfC/YFyW13XYsTr5XJJVKazOSUZPrczmzb2J6dbRUdovFDxb61VCsBJMhQMOFIgfAd0dFNmfUMtw1vLOJj0tSIRwIyDVxGaQ0JJ5PoVhnAp78M9GsWfl1Z1l/BC3fi92VlAxW8bcCpjLJ+LdjPY4Z6Ml01AjrmbxpEwRllEE/jKcQw74YKklBBlhsADCzz0yqIS0fxCv1Eu0Mw1L1JUIr3/BudnvhAVhTGqQT//1jjCf4XrIO21lF62zNkvfMCO3w0uZjWTtrc4LAR9Z9rj7GVtaWfVuxBKnsZW/x88xpkAbhM/M/H2sfqWphrRkt0W8P58WxAKtGe3vFS5mGJ+Wfj6SqARnnBBJKXEhwv8RGOb1qPKv+qWJW/X941uqV42bi3+z/p+6ui+v4q1X6x1MJsgDhPsiGfaftiUjIq+ZWKKGqM1e9X5MfGQ9/A4qF3nIrR71vyJf3eVyjp9zZFvy9X9ou4D26KHgsQRDvo945QQjAxmIQXmxmGAz8dwCtWGjY3XMAbu418MDuOiez+7Pi7yPnZKi52PfsYY1fgvizMHa6cIbiYXq8o4SdOgvXLIrQgu6q/A9nXB2gh265iWexQgfn/d6S3n+6NUsgzyNESK0gSY2gVPOeQDDZUZY93oPDZLWpVXeXOET2RA2idqhM5GIroeF861fbkV5AJso0b4YSTBZ6dGHDb7oHNRIcONqsLIzFYHpYVb51+eZd6nSI+X7+OvWalbK9BqYyn7kPN2el/kg07PJ48RVeotPZAoLBdNR7zcn7Qd5gmTtenVUOuelaRr9Ob4WWjb2BEzZLQskkDoQnBlZMGgpxvQFd9O1zRDMsnXBLx2wb7J9z8niTLwU2uuAhCAPyabb9DoxmxSkfR3ey8GfIXwN+s0ZQ+IzJxCztQOrOxQXQ9uD8qbKTDR/+RBIJ/2YCsPY85yNX0AV9kRM3i0HJtaHzQpQ0m+SK66jnfCuSH32Wy376c9Vds/WrjG5JFSL5fGgt6BEFeKvX/IffMhohKJRt7p7IlUqkB1+4Y5C9QrYunf5mZkKfLRph7t4udYssrh+2DebTJisF3MHgiLKEdbAl5LeQwrCLccvJNflhLRzgfZAMWUBCx9dWV2MgImJxmhmbrcc4HGQtIXzruQyl62fuO072+3hGcsAuX25gKsozrJ02M9ldO7pf3yiNgK/MA2yjH3Sc/lBa7T24cYh+tV+yjalu0+P4p5bi1Dk/pcfXhyHyHdXS9SQN4j9u2GBOTIcfBzbdguNsm22rFNccxjRJUQ+1KB+wfVKQdDEfbumCuCwYY8NLjNu7pmwF1qwZ4NM12TVNr2HPmygsY8/cg38NirE9Ks9t+Cr4IRxgb7JIMCRJGQ4jRpboKMraCd+pA8aE4LHfHY13fmXrd80Tkq9HjUJeKewFGxe0nFfzlAYNCEHS+Lp0CpO/+CMMVQdpSePStbysY+x/0ufCJOsVkIiHoMPeMPsI8NyUz9A2Z8bQPFi/gwgSqsDp3x+aQt8g55CVDhLC9B7On9oDrAx/ww9/Wt9DW2ALOEV+/Jv2wiEDiu7G0pwdeqO3F/PZh6yH44/Zh71+kEH+23tdq2HqlmypvW875Ns/V7L8P83e9CNUDwR48ocdgka/34DEl/fRspszgGjNdNKrT1afRxQQvPCPt4u9uYxcQ5lGOco15u8bk24NM8g8iTcDr690/IDgO1gRFLYIDn3HO36B70su31AGEU6iM6mFrrZ/tcHfdjPNNZ6j51R40hV3mW+AbJQHvDeRyRwE2x952BABx6MxckNwRaOxhm4qOQD39Bv+xFDJBKYUM31Ldg/l/10jQMblzit1/U/RBp+wcjLzRMwHlN7fXKKRQgXKDLmhk/sFulxC+eFl19Hj+ENtw1CSDeU+CpdYj63NAEaQFnhPDW5Tue9D0M5LYjYF3ucDbzIUH3hoXWE/XTCCPGATD874sDVWC0NGn1WA9Xf1ldGzR8dJ9NjRrrUmufpEgYjI7hc3amPv+RIAZApMC538I7j50WAdqJkXtVb+B8EYV/PZCmAjoq736gouuxX5cUf4+ZS3fN1meXND5E4QwvHPYzt8DYZDYACzP82Ec3rucH2KtkbfJdzFz9wAOEgAhC5LBtvI57IMOLab7oP2Q2Crz0mJe2EVfb5o5KN895/8txXFMsvqPCRYlPeCws2mOYJgvVTAV/Ialtz/NgvTSWo9ArU1a60DtGalWAKHIS6Y9L8GeA8fidFp0vU7lQdDqF+XqU4dUTxxavRkQQ5pwieCUVA2DZNTOKj3fDC2LG6dopMlyOUmv6Jmm0eh7Cc51KM/8qoHz/xyv83L+nfTvqzr2yjOcEihZqB3TlQie7At1YwC9NRAc3jgC7ul+9B35ivuDUh6SsOUqS0NyE8bvvV4qEhlKIQDlbRRQCNT5h5tBIsMTOyvgJN3iUUpK+m7r5VodGSA4GtKEK066G0r1Ga7h50gDADO3d4mWBIBc09skxVjPPQuKMVuYsSZXCeWO2MU5Uc4vBOtzLl2ftynr01lFF/jCr1ULdNEBRrRaQYDnEuTSKq7Si71gTz2j7+SbgInCxf3XkVSAyVoPBIAfM8WdrV6+PoA8nL0hHW/pEPRK+BEhj/Vbu2tGCvkDjEmTdnI7exBRHjxmoE+MvCD/NLIC2mgBE3uik5/42oYJjw74Dlt8A+urd1A1ASDbIYCIEOrxD9fwA7w8jpCHYQ54LSvHbxdA/khQnoFgsioYg4NhDMbCGBwCY3AIjME4MJ7XX1WEAbIKVbwXM5tY4ERcu38YvL2VsZ4eEoYalL0g67E7pBUhlk6m7E5/xhcxcPUzacv7XaWlpZe7IAXIZGGZDvLeoeClIvcoStnfXUCRy37sOo9iVs/k656eqGA9+2sqWLuqTFXrfwt6pHh8geRwCxiE29LZKGo4/2tGmYV1LAC1VHP+JaNGxe+VfFf4hOxBEgETPeTgCxXRBeyp9Ld61r+qgyWbRBbehkt2vLDwdrpkPcuk5Tp7lrxccwYv10kI/zdnJoKyVOK1go2JiViqHdXhnyKDnfbrYLRhY3zQThYlAxcCAez8ZAAzAGP2YWR2jECZZhG1J4eRInPY1BLhVZwut01aVOLrN0GZKJtzOyiD+HkqMohmmCOu4RhYP/Y07cEf4CZM/E27WI7sGTZx50x8APPHwmpYbCKZyS44sccMzQjGIiNfj8941h5/AFsi7RK17++RqX2Y8N0Bic7pV4XCDVSDk6ibPtbKdE2/61QUvXUA6Ki6uSvDLUZmKEhYYOzi3OIXMxRw8owM5OE28cwMlq4cX5giAiCRCxzEA2SgEDgXQ3fl9Vz9UVT9AeV28RVoDbUqWrsSyTcMI6PMDMYJ+vV5mLjj4pg0OBABPqvx3FC1XggDG3BAgH5Y7nBM1z0VUsCyjhT6PBBAXEdYmi7Qyjx50nVjyJudkgzOrjNIr+Tc6LaJ/z2T/lE2R8DzpM2RbQL6CXctZk/Btt6oWt+gT8HzLAE+VfoU8mutzK+FFdpQYjFGi+5TC0jWqMMpPjkdjFDZqA16Tdmo6HD+Z/GGANK2gB3IAklcnIo53pEfWLsZ/XPbD0P0iGminlLiKSZ9hLmP6fcIe5QOJUOe3G96t/jlTXJLbEr07byfVWiT5m8ezBBXD/FXuiaxmd3qD0CRU4nyRArswTdOZuEUZTI5P3iPw7whL98zDKYTOMk1jTRfRaobuBvGg3aJIrI75ubd17eob94ps2YTXx7HZq1EmjVJ2saftDEwX7l0vrKV+YpNk4qIO0z7btqhmjNyUjySBrjDIWwfhYLKtECS+u2I5/SjrCcbL9ShInFS3JJCZwfnS6rJtkl+rE/a4EYVIoXdZak/C9aReIR/GSigaTtuwfimXQoX47H/rtFq/0csxvgY2TMK1wbFdQkachGttgw98ky65RTGgmftqhROGIGnka/j4htL2rYeQKkC1MU1fIGaAjS49cAo+fF+lncZ9OTaBAZNJib/q0Gmit3vGAdUEej0jiK4fySG/TZX10gisB9vQb726fK55XScB8UewbQ1DdtR21ziXIir2eodwfYNuFuwtsBQq3f6WvCRJ1saexibR9SQA8OQm859uYDHl3TTVOgSR+JcQjG++qX+rgyX2DeVhSzq9Ex3dt3oEs9PVUbhHxfl3ZQRnmQlWfs4g/BlXiqgqr4WLMCM7EkAN9AoeDn/dK2KdcXsZw7gLBMJOs7/D40sr3xtOuuHnPBHZbNhvYfOVDsa2DsQ4zAHgc7alTJ6d9vc4m/TZIxOi41dHYNQt/g3jYzQ13vkHNhfVzfLRHAvVlb7K67SOkXu1qj9fJTT7RKFt2Is575bJcv54jlSJlFGjYjquVvzfNVb+yFbN2j6hUMFx5eIPg8CMIpB3JGfxi75Qh3Frmedor5UIb3L/MOi1eLNU2LtHiy+A9hvLeRDN7+2v6Owl/nLe6ZGkryTSU0ypYlk8a/ZGk164jzIxs09O5nuATsSwLxBNifDpCQZIEyMWetdWeE7lAbhH70T6Lfp+G2U71AdS8j8T4hEhtF9q7QM1VXr0a0NrlcfLkeFxH+YFiov26/HeNxsDGuNwC3y/zIQYW4Q88CloQyoMY87BP4vL8Cu0kZlx7WxaPaBq1NPAcXRtzZu3zOw9aOr6dPo2zV6ib7KcMd6TcsKc/ueXQZl7U7xDbmw9w5sphI2m07xR8rjSVLfF6W+tyqt+38J7ORxU+CSdydMwKPJ5CCE+gNUQdQ4FT/i9jV8RetXBI55JlJ+DsHsuEPuWQ67TbxN6WkDKZ9BB5vFHSqeRStclCA0KwWW0rcToR6372mA30EH+9UY+e1s+hTqsFDYNgnz0v94Nf35mxH3gUSAe0sW3Oq4Dzb0a02k0MjtXZZMOUWDPIKpUMg9lxyhS2tiaATVS2+iM5RDC0F6hTnehEULAq1b/lGXo6EKEB6AXneIyxUYK+MPcbZSoDjOEDnl7cz/dYhvpsIQvXlkS27XHEqESHdAVp8VyWRlhwO7wl4MopPDH2wFc1IG2ZIHYY8oRoxwxjOTPa8gK0wVfMN+CFKzZYbGO5wihH9+j5k56ngXI+b6Qd1+yzAaab8Lz+aMDCKnQ9S/ybr13gQUshhindBV4bSJExfJ8OAVu1oDXX/fh2jcC5K5Q2WU4OqA2J2URZlHK+QMJ39OpFC32GeWsfIUNJ2fzO1rhAXgdLjFj5V3ZQAf2EWCgDen3S22Ke8WSN3tq0vDiWv1TOEOLdfZaZ875EIejhT2lpf5WnWr5UtdUgx96RfEUB1qYGXxb93kyWTIV0GpaRbenjaCN/e6j9nIPfPY4r5z0IpMVQCcOGjpJShQ6TIvMaqlaKbYpK2OKGS0/R6GVu6nPZN9SMqX2M0o2kGUPIsk8nQhef6Ki5JnmUSeRZQAn5XJs4EbRJ4u+vYZmTwf4VTk+cw3kecJ0TIJyXMWeTyLAhb4j0Grb8+zDGTvDQpijRp+H5Di+V4WmYu4hi5JfZwl+cNvHvNvk/6XMb+c9E1jrk769mNOvQnHfCN5PLdLTx7Pg4Fn4vHUoCFWkOV0tT2Lq60WV5trLv+CvNo4v4gXVjAi5sdwYkhplVKwnSyhJPzcIoRM/NsohTu/hYfLUWodlO9z/6uQ38n54tCcL77aZDCpQ16m5vXwKayin+0BeKLxjlXCuB6YKCd49dXO1TjJGT6wjhbx5MuW6Ki56/8B7VRV+KlNAIBDS8V9f3xTVZZ4frVN25QXaApFCtSxKFrUakBbwo9gm1KEYkohoYNtcUeZTIYZEd8DHSm0voZp8oiyu7Cru8Oqg87qzg+dGUHUARKqLYiDgI7iwGrVijcGtQiWAKXve865L2mKzux+//h+vv0078d95/46955zzz333HPl9SV47ptmXTXhCjr3TdNjHR4LUvQ2bStycBsmoSws9NazW/8KhJIIBnwfcJkoxzhknzAXJK47P+B727myGaGEvd83KGEsM/EDTQs7XzmYVIYqWzES
*/