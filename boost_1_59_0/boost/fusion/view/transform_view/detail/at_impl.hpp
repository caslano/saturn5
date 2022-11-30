/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman
    Copyright (c) 2005-2006 Dan Marsden
    Copyright (c) 2018 Kohei Takahashi

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_AT_IMPL_20061029_1946)
#define BOOST_FUSION_AT_IMPL_20061029_1946

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/sequence/intrinsic/at.hpp>
#include <boost/utility/result_of.hpp>

namespace boost { namespace fusion {
    struct transform_view_tag;
    struct transform_view2_tag;

    namespace extension
    {
        template<typename Tag>
        struct at_impl;

        template<>
        struct at_impl<transform_view_tag>
        {
            template<typename Seq, typename N>
            struct apply
            {
                typedef typename Seq::transform_type F;
                typedef typename result_of::at<typename Seq::sequence_type, N>::type value_type;
                typedef typename boost::result_of<F(value_type)>::type type;

                BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
                static type call(Seq& seq)
                {
                    return seq.f(boost::fusion::at<N>(seq.seq));
                }
            };
        };

        template<>
        struct at_impl<transform_view2_tag>
        {
            template<typename Seq, typename N>
            struct apply
            {
                typedef typename Seq::transform_type F;
                typedef typename result_of::at<typename Seq::sequence1_type, N>::type value1_type;
                typedef typename result_of::at<typename Seq::sequence2_type, N>::type value2_type;
                typedef typename boost::result_of<F(value1_type, value2_type)>::type type;

                BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
                static type call(Seq& seq)
                {
                    return seq.f(boost::fusion::at<N>(seq.seq1), boost::fusion::at<N>(seq.seq2));
                }
            };
        };
    }
}}

#endif

/* at_impl.hpp
zE0OmQ7tbF1+rbn6ssY8IE2c0WzzUx84uye3jO99ByVLc/R4Za6l8ffQ36Nkbrhi4N/hTXw4ZW/fD6YQnhjoPR36tdK2vvUdbHzmReI+O0CPWvK2egO07bzBmGEduglKdU9eLEXa5e+orc3+pr6L2EBc6THUeWOsIRP667ul6Mohi0P0eL6LpPazB/bMFtyu7/cILVbqneygvVAovPmghGBp3r6/KOGAhSlwQf80T27xwUfWQszAQhfF6DlBALVvwPhPDfK/6BMcpahC/CJ3qZwGa9F7YSFyhvfeUAzOg3TX10x2i/VTcGVubks7pV5qR7a2dl5adXXwCviyQbE/OOkFWjn8Qh3QiTu17559lwojdPmvEaJoYVKdYIer00ZgCg6DiRK9QES4ZwgNgQlETZF1+hsBSf6QKid4mBkl5ArSbFuVkfAIjq8qLKBQlePlF8GSouYnaCYp76g/2CRZWUHFL8XKI8nMXMMkS2PkHwkkTcElS+PkH6kmdVEqOxBJVtjQcOKT8lnCxLNEyTPBke7CJGexCY6zhZV9lsuPnxMnffFIzkAld2GTnmNL8cYkfMMSJowTJ3Whkv7SKjvMQJDaewRtIlK990GQ/kYlQAuRnuYbLUWTYiYtBUuWxMg70En+fIoRJjyKUUjkH0nlJ6QTJ1n5hXVAC5Km5hk9RZO65h3h5idoECdphyT4cqERtXsFJYRTvNuUGd1AkM4KCG9nCpHii42nYUvdiI6HCpLmYuQbQUqKBkuixcgzYZLGroaKo0XLN8Djnf7IlBlRSlbY0rhDkKqFSKbEyj9gJmWhUI3/WxcyKR8fFlG7eVBCofzDtfw4LQWmp+G4EoKCq0aZ0fK/0MMSXoMlV6LkHyCTvnZQid63IEhtxSTQxXvqgUkusAtdSkkvYpNjF3tjyXMGcvUbX3uHc4kOxMS+bJz47qCbwIlrnxFnI5OUxL5Q5rBVAfFERJQYCVf9DQm4u40snt5eyK5s5/B/sMPeRErkEO9dt3+zfz3jPgFXlR+U+CL0SH6Iv6lU9H2JaEzx+Fqwe4/07l52sfmKI2IiYhRGR8yb7gudCp1+Fx9P8Vn5YBBjo2DI83L9doA+IMKN1De+4s+jw353sW/jU2wJvRkv9nb50ngoiX3iX4oVqcrkQ0GxfubT6KSx/nCLwdxSqiQFxChWFBieUThbOU35enwL5AiIgVadiL5UzgX/UhLXqCCu/tZe6/B5TK0F2R+Sk+w4PdIik8vkIIkE/z4h8vVSfb3iP+O3+RK7V1AdpOL8RCYxh/Xyu0NQkFcBhPyNfxFTqLXIXSIn72LntUDiM36qrrWYHYXX6+agfdqJXCTbRvR5HsneVytmHqyt2cH2aTZ3eVueyxq7UhX5slHWtRlC9wX+fFvx3cbnSNn6XOMpZ8brJbcjMaaTfwk4jdirr6ivzv9R1xLaK0PwhsVPNqAJNmx7+f65m0PpZ5u9Q7xV6D+0zeSztLA8M4fC8V3dWnQq2G/cQ1RbE8qEwykMQ9EMslsS/Sog9rFH5BMaoic7eA3k+0I37+X1fbvdDNMzCo+iyd1Xq0dUs0dUywijth5S8RpCvdmu+pFgv8i+2z1e3+81xYP93aboEveMpob8LaaX1esqMbO8eWDFl97N+MxDry3NuEBG82p4TVbT+7pS/zgY/CzN0PW+Dzz31CuXe7ta2/8+j7xEnvsNkGs56fk4EGvHP5b9PmUVCUzOOGIVmfUKXxWb0kLu5RG4fasiuw6MdZCxxWX0VS2UKHG1kpH+7HtaEWvXQp7/bSVfQfFWfdR8sVwPTJ5cLaqWymz3mkZl1+3NZDMZiI8h7i12VYfrTdGpe91m8RDbmCLuxWXud2j7e2u5bkiW90uMO7k6x1WmTPVcuPU0XGvca2/5cbBF7dZt95Iz774N6vlv3jdq7VXaLGuPy2gt6JcbTNhVZ+WLnPkzvlou7/pzWqrnZiuq52it8qUuG6rmv/SctYGGuAfu2xhsIZH6edwh0fsGGBS/Cjd/j8XaM45iHXp57hXouoFnZWznuaRtCX+uIZdgL0Cd/c7FtvN05cEFPxZX/DPfNV/i4ex6hx8DusV8tOrQ74lxy7CXoC8AFmM7BLrz4Bj+bV9qrYTeV//T0zA0r4Re1ysqN1+X7y116Ctxzx7ylNaU2pTQFN//2UrSPAKiw5NhXciWD253OrVFfm2i7Iuz3iHTLfQQXzM3cAtv/Ea/BTf178Fnamq+dcb/KlvABdvAOZPbl7fJ8tC5UuDNT49cDw0XynDv0uIRX9aOIZmH2UmitmgGvUC3uNXzFMbgFgvBxI9d+vlKIl7g30LSnvS+vvsngTcxOLTfhczGYgn+yvx66cUWHniMKoTv3QCxo28B2U32oQZUAr2K2d36WwK4wmnjtxHa2e9GFdqApsLYILYt760E/oOp7WoDPnf3MvqygV0xtwg4rpftl4TtXAMzwemQtxzs2OxQ91z8NoFrALdK92r8PuG20iwRxOwc+4oDtMBsWNsU7eQCKwFbobfw7Eb7mv0vAVfBY178udva91L8PFG0KdtK+68BXun34PwvAf7D//HrgsOKu4VjB91XDWAK3Aq55WLnC/Jqahfax+rPBXuD1MZrd9FjL4BbioeDfdVD8/aN4W2yiPHNTD56hv8YNe/7eI3hPdmXtvf9+Rq7bNmLVfhbzr35ODsiBqQCK5uV5YN4sM4Uo6lWR9lb5wVrXEmhbjpdS+OzIalQvAK7svB1IPiUq/FlNJ/F6Rh0eLV+xEGt0XffU5znxoMXST0pCY1hqf+TaHycrH4Syd4vYu/jrmHMqKQt+rUGRZX+FTHw1eBQ4qZzvwgq0LWmCWUmkt8coDlbM2kaQVUFGpy8tOGA9q1oCS25evIbQEtBa8JW+Ptw0PwOivqef1qE1VxDr65kMU0eS6k7q079AF1tGUm9T5kc/0oFJXgjMMCuSciD8c36fjkBJQCer/7OoDpeQwm+DbFqSf0wadUiSQ08q9tp8uYl42Nsfq9p6fNuIk9Vxmino9+sQV11uRpAQUoAiioHNhvMwF5VTTNV21RTS6OrhCNObzapOY5SRY3vA9JcX5BWfwJ+qwxnmLyid6S1in5SS7oPqQ4IPU4LWhyoyF8rgmp8CfVgbYx6CSXuFYnZpjODcgztWsZQlSQiXBfrbEk17KbKFCcWp5I5Wb0UciBoqeHDqaWpqd5i791T3bQngUjcWi54mbHQ0CyHWuvL5BudTAlRQgRCT0FLTzUmjidLoGU+Dd9uS00XXAbcoz8d8sVaBYuSPltDbyLeIcSALWzQ3dzAlAs4LbknnPqe/FcBgb6JFQlCHaTM4VoJAy2c3WO2lkL9tygZawToooCqfy8izB7iFDsSOp2IcUYENBj0EqpvrH9oRa0AZoNUSUG1B9MRZFEQhWLNtLg5z8BawcdYAfACcpLoohsISpEAnmgWGBJJ0gKCzggadNiIJ1EvRxY21zQ46xCp/IizuPEBeoVpGLvK//Jo/3KMiGqEqQx+SWsu5THcOM4LwUo4zD5/OaW3XxNQk5YCVhitvqAh4qB0coUZMOksv4nA7LdMqL4rjoG6qkiXv9sfFD3uQV5bnTDpFha0uAiujAL4sy4Bi7o7DwnGmyfcdIY4Ev/9fUIMhuQXxizSFRtqYlIqsjo4ZGqdLzMxNyfFWrfhDrEx382bFFhlRrlsFYB9jUbDEYazOC4YO2JSsjoKAahcLPSWXjvNekxXTXUEBbNBQt+PA84T5yW12a4/AIIblkifFcUUFQVrJaWaGpxWaNvIzcjdRXTuUO5tUlILCXGnoWp9vPGWnWbIYzpOQVNewzwtOYsbZzdYY1IN4IHfob7q9zNB6HuHj6ud+8kDLgJq9VGtCJvpFBgtH3moERFeSnSou64M+rUhUqpfVrKeBdQGcevNTnXNWVN/HatSH1C4ZczvyFDdBHRCf54flrraEgbzr7L8XIgzzoGvxPpI7h3dSL2b0E3sgWqLTyMhNdfkXSPneCY/eEM7K9AvoQT8K/QP23SP75G+1FssDJdlSxet8Bb2jCsQ0vSMZErd8N0nX0u/RvIKudAhClau8YqgizehMv9fTubT2jTbtu04Xt8SkQVVo2/JNdk8r6ToOpzk7TwcVP0LptNaAHYtKhv9V9IDZAffFdgjU4mUYH682CU0nwGwIVNEVMlgRA89xZfRgP3XowV6cuJ9X1wWPFjzs99Rdzav29F34ZtvYd7g7VTPG7kjpTVvTnfMb5Db8XHjxuOVCFTMx+MFnC76RJt2U0lu22jxkBDUMFPxkVcxHx+qrNwE+NTB3lT66OXbLha2Kj2mDzjAWiB2laEbVfkldUR6UPSPFlKBIfxYCNOsMPrwvtHIN+C9HPmwXb+9XkgiXtgsQr9RReWCMPKAzvABXCMKKHSqLokhSkZe/1sJ9ki3W3QE2T1sZKcfW8T7HPqQw0AHZJEuWpBcIJuEsFWRvUQRL749ZJGtsFdhL/i9RCG7wLBemhFyPznUe1zC/cPQIy2RLMCujrfxvc4wEkT6iL7ScDcbEJ/MsNlY8dtropwvEbeeLcQ5x6Dfc6KabwOO3fvElWzAb7E9V9AnX/sqXcoepf5+BWbhr6vhu7tbtHuyPh4qwEpsLwlGpSF4wJwpuMNXkCcvRu7u14i3GQhujaHWIG70Q1apIWh6uE34dSD1IWbA0VrtXf9BATkpYA/gLfwAeug1a/E3AAXyUug2XhAxniwke80lOYJdpRsUu93T/XcmtSF6oBo0Ru6ScDctkBy6A+dc6H1w7ZCw229u7d91oh5qID26A1ZEt5iw1NC9TZ/eSE3Cg1hgXq2he9BhScTZCAhytaHT0L22qi8qRLmYu9+yMGyiu1FhboEh+1bGLMDHtrBK4jtuRPw2BBv4SmCPHgQbvndAHrE9ubC3H+j9e0qIM2YgPeIDLsEBAa/qMDWRvWBAHj2IWvwqIl2UgELcDaAP+P77o3G/H+KDxwEdAx4c/9sswg1HkB/PeV9BkB+ivQ1ooNigB6AHiANF7gCOhzDJp0pEd5D7Ufrg1FF7oh4SELUI7oA2lFgCumHiMKl7iIMx4gkIPAHtCDGE1APEoWI3EHvK/3cm93vk3VcHcd4phFfHfzjme0FiEb6l7v7HnP8Ht/AsErfglUbAfx1I6JG4h2jQivS/AvgkuhhvJ/qnDdmQugWtVYP8r7j+J1WcB///pDDI/cf3RNP/P0FAvHfqGjzCf6u8gOCW+0cfdPZvqrCcfyRLwP9xpOwnLur6F1G5Len/xMR5CPqJhX//g9H/w/BS/kUy+39QNo0RUzHGUMWLmWHi5Ru7BaXsI2qG/P/HOEPAUwi6g6AdJG6CiZ1j4hac/P+OEXgKipcfTOXHcfTfzPF/1/wfm/sfvcAXEo/wI3Xvv/r8j4SsNf5fsir4RNb/P9L9fyEScieRPfpXG4huHf8l+//nsHJwkv9ZQC//8vqfyvq/VLDi/8zi/6i4C8D/RJG0h6i4859aaP0/MlyEF7f3vyJUhJe6C5M7CqaYNykU1r0bvwuQC0H3YuraS9wHzYWhfzNy6ycfhObF/P8tJHIXIHn0v3WP3Av+hdbIxfosRf3Pb5audWSscMad8RQL8bU6odelILFH86EyjVl48kJ4lpm/oFULhnQ0NaW0JQuONa40j+xKJFxYstKz8cOREIRDCdrP6vgDCMZJoYBAxP9ygGUB3MvwywJa8YODj/eDr4MT82ONA5kENDvaVVT4llR06KpNxwnAzQBo20xX+jzrLr92q23XDsU8DADGocP5ddkBHAUDE9DjALjvA4xBg/PrcgD8byBKdwFn3/4TDXvffWD3IfCHMPgjRPwxYt44MS+C2Dd+vHt/7oP/HwGpD+JsU/999/8WkCfnZBPxErnyuAV671n05oNzxkf3fHp5znbXXfHLMae3kgv6ZAr4rcHvizaXy2bLMqM2sPaBpnZ50jtJ1aPkrZvgXFi/D56kdvSKva/RYv3xPl5Mqqt7eNRf2ndkyrKaO6/tq2nvfQcft4N+9PW8W/pr9j1CKiD7SlTw0wry7pm1pZ/LDvq+yDj+cy1B5gvaZCsUR36thXok8SkZwG2Oj/ZPCXj3RG24DaceS3z0lYt7fGH87G2lGduVWvNVieOTGQt8Tp9bY8+vtxU03A0a6YGM9jZlfckOvko8Cn/2biAbS3yphnoo8l4F5fTmk834tsVJPIaW9pE93OWM9j0l+NWtgXwA8eltpBrLnbh8feogOP2GruklGXP//XmSOxN7ut3U4PxZC+B21e7pIRhTi6k8VOL2JT+6pBXo8RHs4Y2TszjxVWT+Tdz7soV6eD16/z7hEfhR1s3le+OPIz/9F+Lj42ztLgnHr1RAVq6vjzd5/zv68fi7HsLR+Dv80Snro68u8++pgE/kwyvLQymWu8FPp7NATtqvWsU//1/+X53/GDcdBHIzvRSnp3wYvykEeqnHu9rIR9GJDj8dhGPnuc7oq68RBHyPGVj44o09/1UgInYTuBF7Sd0dvEX+HZcB3O09Bf8OFYEeusfbWjZQzt6eq48RsYAsvV2Cny2ko/FnHdSjzFqJQ187pTi+3wJuPuqDN+SF594HusRTlrdx87vExT3y0n452cDcLDA+TlgfB6yvI5Q3hXE1Fgc8PsBeywAvnZTf1RSC0/vBldENlCNun7e3JKW90P3LZ62ArNHZodaeh8JR306yMfcvkPvTDo6fIO4fVoEf6RR6b5Gl3xBuvsmAr5Ha8QdSgZ+HrqhdqQJvcVx8Wtie/8/lEcvrlPVtxvIue3WPq7bfVTfwtgts1/3/CVDfVSfUWh5x96g8gPSQugPt9vaQjrEff/c/VvxbDi4337s8jt7IbSI8yDuzu+/ddkTZL2w6379NDb/9z9Jc7zSQr4Uevhc/C75knn8gLO9iWd9Gsb4MYX/qwX7VA32r+vlW9vD/7919fIOrhf8K7973WiyWvMdZMYn84NP1NvxQbmx2lhfpaNao/Te/TC/mlloP/Qjy6/cYV2DmkG9Mr1XkE+leJ6GXUud3kVXBpvJRjea34uNd6Gq3A4fPRymOfju5Vs/IQWyQ778p4B2/SUeZWO4PP0pYvkQ6P9LEcje1FgFZp/iDptZKceQP8B3kG6FLs7u4oL/qXhpv4kmbF9+VhXv4vb9OKF/QB6MRBKfv6Fd8IpzexKkWvhiTfBIPaq+uYIUf6DyJD0GqSWfrSUl/MK9fr+t2ySmfmZC9TWGes2XnyVfnCbwdeKJftLCgP7wz/C8t5jVw23O19Q4/85P+aHXgYwvyrcWq5ONfiUmcgX/6J3/LS/LQLcPX0KX29LwG+VDxHf3BPQrVrg38irt0IfORxvhg1D8bDcrHRw7xyWJ9OqyagS/HD6OuuUm9Ga1owJcsB3741rX4iv6gjR50Fkh05zTloD91ehxYhlZ6H1mGzXePvwyd6xpzFjbTPfIgyky9L+JtrxH/5FF7SryMbNqNtDfbhpL0lvikKe45+oC7iCG75DJv60nceN5G+bAW5D69SJj7mHgef3rWUXk5PBWpUSupvU2Yk2vucfhm8vamp3wWeMtcqrnNqzFv6DmFXX3tYqsJ/2YLvQodmfogPUmvDCypoVeDD15Rq4n8j4Yvo7fr
*/