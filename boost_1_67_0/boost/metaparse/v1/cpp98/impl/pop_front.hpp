#ifndef BOOST_METAPARSE_V1_CPP98_IMPL_POP_FRONT_HPP
#define BOOST_METAPARSE_V1_CPP98_IMPL_POP_FRONT_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2013.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/cpp98/fwd/string.hpp>

#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/preprocessor/repetition/repeat_from_to.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      namespace impl
      {
        template <class S>
        struct pop_front;

        #ifdef BOOST_METAPARSE_POP_FRONT
        #  error BOOST_METAPARSE_POP_FRONT already defined
        #endif
        #define BOOST_METAPARSE_POP_FRONT(z, n, unused) \
          BOOST_PP_COMMA_IF(BOOST_PP_DEC(n)) BOOST_PP_CAT(C, n)

        template < \
          BOOST_PP_ENUM_PARAMS(BOOST_METAPARSE_LIMIT_STRING_SIZE, int C) \
        >
        struct
          pop_front<
            string<BOOST_PP_ENUM_PARAMS(BOOST_METAPARSE_LIMIT_STRING_SIZE, C)>
          > :
          string<
            BOOST_PP_REPEAT_FROM_TO(
              1,
              BOOST_METAPARSE_LIMIT_STRING_SIZE,
              BOOST_METAPARSE_POP_FRONT,
              ~
            ),
            BOOST_NO_CHAR
          >
        {};

        #undef BOOST_METAPARSE_POP_FRONT
      }
    }
  }
}

#endif


/* pop_front.hpp
bdu2bdu2bdu2bdu2bdu27fP9ORdP04smkzZtOnPTKsAq9jyH67jNeCtFUWgW2LPVVqUDI6Mt02+LiSiojw79DbmRF/yldvYgu3xDYac8V94/M0pDkx2LEhfBC19NbmzokQJWbeYpFeoQZcmwhf7lvwDsPY4f4wM2nCXyr03sd7zESeOe4nnTomjqawozqhfKFXGG85/7pLc7I7oDLsKwd/uTdEJLWWAPy9XJcYabDQ7y9klYfGWt3/WY90DWzln3zX09ar56adsNZbovx61J48ZFluHQSkuw75foXDYrhxHopBS9L6T+ojDZOFAs8o2Kv7BhGzWvaO1+6Ux3p9ZFMmwNEUMT6feMbtNs6c1a3AC2Tn800mtll4zCQmu3M6wpBjWwln85mFHVQgytKYQcnHUkcPvlSJfa5gaR7iGkrRwpTr26U9CdpRDBY9r3PKQSjoaUaWX+mG3QRWV3Z/DkZ9cOfjs0o/nyR629mi4nT31C7omODDXOFKpNP4WtVp56rNhcIc7VDPM/WjVYuxCVe+GkRPloyX10yO8XmNCbesMcyyIFocYSbGq2nacV39XhT/miXjr5SlDTyjE9gP2evfpwk8/jJgOKOEQXCPsf+b+gpL6EpRnYOchL2k3g1Qd4Sk0pVudvLtxmj1UoAGvFfR+uBlSl1ytVlagXwhme7rcpwDUssz8D0z5vQi2TKqYi3aWwUAwT8TVJDcqka1mJH3GDfYdVmJdKVq3m75dCD+ZyQ4y11MLO8S3YHbSBlxnw33MjPWWWkywAJd8klZa0mh3f/ACA8YGFz18O3qiqqYuxp4E2SAeW/rmj+cRQpBe4NdYNxIWN+iVuPssRduKJbK0O5wEZi0g9/wKf8MsQUJRy9bupMLo6Mu7eyGKosuKtzpSUlEjCcCel9zIHi9ZpdSqtxSpzPlL+7UtWOFLWPXrMtvDLlJfafKh9A6zv3YQDQUTQ0m8xF1Og7azlw5qtbzpfSq8ojs1yjVUsJSxAAN4AYT+BPXQa1m162lwjEGUmCWnwigxXCR85kSMkV1JWc7rPYTYSn9KGiOlS/Ck4T9hDiyGp2Eau6ZhEf4xJCnpuu9GN7gFwdH9ryW9+xJVOnkyzmHIc91lyOFd+yJVimB20nshj/13rw2GIbAG2ORUfklOuLHNZbFl6fTp6RaoUKbvUvL9WriQNtw15cvoFgObZrkVHPFxQMmjgQVxb7rTVjCaTQflyAiguzluKpKhXHhN2M+I8Aeaq4WmPVZeETw40xbk831s/msuttoja+J0A6BPkwK8HuwsNqF9LrHMXowCyUBV4n30CFEqdDzWpW0P3gJqGK2MqfOsY1Sh4l5X6kGWmnPzrUt1w6ama8CBHnQpQK+EJrbAEh+5zeoGKZIGZ48dvvXKPodRG63k4TrHGKfrK4O9S/bHpHKXKK1suzEeNHp2qCT/iAeIhxx3qPndsrHBEohwpYhq6KoQYKBF+tAr/vgo7gUuPPk7jI8yFJ7yUiX98WbzO98FA67qj60wWbxondwfdLjIrqD4mzAWsaKNwB/X65cWZ2/cHncMXG2CqD3Ze5MHzEbDIwnInBMFY0hfdCk4HzVrnTgg/PJkHhSwVGPHzYeAoHaDDywRf8s/LF9kCYcLdOaDQJAckVoiHXX5QezOg9YyZPGOIaijTPwoodCKsQ3cJ1Ni8bjBq+TKQnbqvDUTJ4ZG/36pP2Or1WDzB219YxLYO4aNJzBOt5VViOSH/TGIhAJh5Gz5nUmPgG34b9vvDbWXRVgm+Aqoffsu2kk7xg6JMP4mv4TStrd3D3QG2U4f9eL4/c7o/g1szWbGLCd2vQ2JZODvg00l4Eh55WMdSJ5EvxVpFERW6l6QRccVpW3TSjd/d6uci5gGVe/egwpO3dWHKdSg3Mo2rNHIdlsCsFaWF2JfID7HByJFkPEKWr/Syi+uJEykaEnQtngQf9P5vdASw96KW2oQRnComZEB8peR8Xk5HjHtvwL6dBalg728wGrM2VB+xoslKyFMGF9jwg3rDDNmMVsgHi9O6htBZ5/plbMHjlXkPjDqC2bxNjPiqSx10PeW79ULwSQx7jgTvZz7OEwbn4aGyQ4yCthEqHhNDW0oNC8m2qTSOljUK1RcyHXIfBahngw7MUT5PsYthdcKxO21fyWiUMfZ0+FZ0KYrUMxIkWXbfpQ6yLfh79WI0bFh6G+tpaILnNIX8W+Mnui5ZVd4BocYL9N7Uv5P71rrje3LRdur3BNy0NC2asO0/aw7l78gT+fztK6qIjuks2NyNiL2MIJl1QY1lUE8K1IEdUshAtgEeh5l/GtM+1oCFjrjfNaTNu9Nxk6NjFY8rdEF6ypHfuGu+d2a1LRvWR/kfxeuD2Dmoyb0vLNXvtaKnrE2tl3yEFAoXqDxfwmuuA8Goguu/M4wxycQPhVeEWiakgLL/EpTSUSTzk0ogHTRZ+Tx16ymfpQMrAIeIiGlrZdnOfFPClW+XQv4UPGyQpkx3y4ydPpASJrVz9uOUT88H4wTOdkmULy0SfQ7GIuJ73WCX/fC2s2qg6uKh3emgHKSdlInrbAUfE8Enquj85XXr2hYoQAxpkvTITv27ILyk8rN90kUdThP+gCF2XQALOPAaG1xUQYCbhtLehVsUsWUY40g+e1eNG9JmX94KSIBaboUA99HY7qUcPF7EONuFHsEnyEgY5nArPEt0YP6e7wSmcIMi2i0AqSmuoa8SCdlpeNDU4Z3Lf6ZXWmbbVqU8OOci7NeWDkaADYxm+lVrf9BnFDshk3azE7Tv+7o9ul6djxTYr7fnd+fqsqWfqScVveKQn9yYhsl4AZQRf8BE1JLOOQwrBgBexFU4pnGnE4e/cdK/kbJskiyO44hcK67az/lGKFSYF1/gFyZR3kh5DXKVPHKPQOWwKwBLqBWaIfSC8LuK07Ingiec2tDu1lLk/0mef96qHLNUxHW4HojnhfJg236FS8sdhsL+3GPTDTRRE6tkpdUwfM7LCx8/XIexlQSGcXig8k4/hAWwl/mzcwtaxSF/XRYTPra7VihvkYQc+N4BdfPdXQ/KeiCgoFB+dmzJcjAa/bJ7h/dcnZxZk/ZGWkwevssU3a9yiTO3rlreNwPWnJBIMQnsIuQL18lQducU1RQohxmD+5vXHPJP2bV17mrWg0AN4LlZC4Q2DfT8KC9Yx0/hze49QzvA/zO6M0M99YNarQQqNKN7ez2qXxqhjH3RBRnDbAcnxQXLnT2DeQxhKH9uQucjmw69f3YzD9fVsxOANIintGtHrnQ2LpUEUzz5Kp9qx1wIIxMuUPeaFz3ehLWSsWN9skaLmskoHjQZIJ51WRphunhnOJodM+7uWAAeV8iflFq8uz2ddzovIajOQ3eV/Ryp2YO2rY3pQmdwnkMrTTmU/zXq0SnL3e7GnF9PE9fllhXX5rDgIPRtiCYe/uAPxo6VHS96MGwRG58ojvDXtZlfwwGj0PvJJy2gsWbiLrshLUGN4YPvksZ6jbsLie02Fh7G5dhrx5Kjze9b6+GFFlR+n2L+aFWJy5XhsWMnHcVK95g7fqXCQ7sGNQxWZzkdCtnzw22yDr2jc8Ya4qDWh7xweDfjBTIAO8mjWNxvuwZ+63AO5veFP2f357jNuAkLP8emjxzFs40ejsFiPPWD232QOeR6g4Z9/GYGp774Z0mH2oZTbLRT7IRQ1idOzraoM6TnCO20MUGu5sroyT0zEe6R+lhHeEt6lr/DTYtYo0XSCIT4AfDgrtnMQZ82s5F4203Ol/1vOt+HvdgnfQbHSXCpxM8zl4uEQY33CRlgRMRxL4mI1s2KOzr8ToQRK8qYGXXCeHo1XTAdNaLbIVS33nFi1qPRkiQzT77OmVXLMDmT1zx6Jm4xg5+GTfyG2E2AUXzDFt4m3ELrmP3OupZ9Vvupp/FpXkpvShzbkMaDbSXRTYkGN8VpTSiduwnnJqQrtNRxCncAgS1BLOXUWnlbplfWeBXZam02kxlQvlf2UyOAJ4fv9zvm3UjqL/9SQMfi8Lv/EracobE6QLsr3Gx9ljTFydh2Ac6iY2SBtlOasa9a5gjtdmvWZ1xdp20Sbxsfc2sjbZaXkjKSQTWsu7Ax2tsLkm3pA9k0wY4sY+Qle5rat0kcf76aVgxm2qZmJoXBCz0DIUn7wWMcstGcYKdGM46De9a8OpGmUoXRlOiW3pvYUxoy6hsvRQQaz4C8P5vQgZVOw6G8E+UL5XjHqkbkt/ipGqzWeB/9uYMIr0Nzdu8YTU1qW1tqe1qo5LxYp5pGUeM8iyFagqzH2y3RwNPXm0PotxbkTTfIj3cExU5mVnyMt+ce22s42uuQBKw6qS5TgKGD/+ywHy6kSjpVk/vHsERU9R7zUzv0OSBf+UsVDbydYf4xcDH1S3/iFDatPhFNgOKMcokvZxbcwVV085b/CR+38gegSqY+AzlMjjINjoSisUeCzKcyPqQW8qc3nzms7YItBZjkyccVt352pjs82k1RM+As2cZxlSLDX7krrlLEOe9C3sYhXSYxLOpObHdIiG7w9bNEJU5ss5CCR5fCrEA0b2KGWwglawp75JRRxoFC/BTtrbXzsyEv9imy48idV3NNljnfxWYMEhfLNpIUmKvq6LUFL8546K6KarwXNPCkjhM5ucNMbZyVTSoGTMRoY8P9XzvHRsCUYlCF8EX228+1FIS5BYhA/awm7L+C6EBOINxZOuGnFH0gET3KunOgnL3zlNnvLwDKP3atyvvmB3UBCXleBmIt1Axn8xL+sjhrUdoS983oDI/7qkUGJ3gYCZbjgnJ3YduUIfXirEY6igPzVPLA9/HhZmExibKJM7QeZ4V+Ot4zgpBUxcqDD4w0RB6qgl5/ZL+UzxiY44WYt3eYVVIb0Ma36anF14Hi54MZijTEfkN5E4Iu2uK3xjV6J6qSRo/h4PDzRWXroijzWTkvGeKit7dcY5GTd78obtA6ezg3TbGoFdxb61oOUGsd2TF/bAstXvDrjcAYitJarhKqptJS/MK+Xm9uTre5IglJg6hIqu9aB5pPphZ2qbpEVCmq2YexsZRWM8qdgYImbDSkiPnn9LPs5+fI4kFhXsD03iWx9/nhWpUqdRM0+l3JxjP5b5KaEWyh7zOh8TvrjksZOEbWU9JMuXDZ5FTyTPC2AjMCN/Z7ibcYg2AyXXyn3NTV2d86YBemdgtXxi17fs77yGm4QBb8n2eUELTfNUeYw2uOiz1/FtLhs8RfrwoeHt4YRVkwoOtG51OQ4Y3ZjbK25W+ozvFOtKbDEoa6BzVnX+dXEyfdpgIQmLa4I0xIORlDINvtT5iosB0Oz3ak1tFIm0dGNcoUgp4KUJsDrKQQOFlFdjajg7k7FSg2GcV3vjQTym/ZxvphKCcNAJOTxbxsmfEsPu2O+8i7D3sXOm0Dpgoba11TuUTxrem2pJn5UT4BPLzp9bG6vhLUVhlFdiqjA/dG+1niEL8uZqWDcO11TEl/QngrfogS4ecs4TfDi9y+JsPRO0alFCwrZFZLMF6mOgxIfRQRyS97mJHCs6k19gv8jkcBVTF98lOdqmyT0ki4h2qrrsPuAodjAFkSNq6WNoIiZrhOqpp2pEpSW6wLAArzPF5urSfFVOZ4sDmgqAgVmDx2ICm93Ej1pLd72IBRo3+W+TyuZBFptyNEZgbWQzMXL91QL/x3Oba6A6Ve5ZrrRiPU1fjxQ+EP9YGy52P3Dc+QrCWq9eRCcMUSXvXkLYF/avnP/ni3X+5i/ll7/3B3Nuie7q7cVdiIn+yQa8vrxv2RnJ/Z3BTnoGkkpVDWFR8M13FHNibVJVJz7KtR3EqdVzTofas5mkixqphaAuuwjyp8vBUt/VqISwKHYpdx29GMcj0R6/qkHh4XnlI/gfLZHFqbh18NzWnelOj/7MzlLEYVm7ByzS13yys4DnWtg/vUHiQpfWmZaCba2HSxlyfbZN5ycOzkNDQleZfq1f+GKgOAq5iZap+SMwIN1SlDfJYmn62lwDbo51KIOT1ttvmwWlvwMp69xf4JFCN/sgAgB8+MY3F0rgj2LkaStdFrWZrjSMoL01eo9Syh+DkYoKph019XqKGLB/OL5S+WEwXPFsQbK4+8ObyCrWJbDHryc44bvIB5tGmTvhZFIZMuSiQ6/QQc/3x4vvDGxT0hlmvR/JJJP0m+/RzSNafk7M4/wQUFRTQ/HbG7cHjzIMXdO8wYrxzXNYDM3NLEukMSo1id6gS+nUpG8MEaneZNPXfFux6j7jJJsDMAs/GVieVNxS0/VKhoh6Xi90EElyNSWDmzBzz38wvwcr4LO3BC0wa4SdJXwuSSQsldcADdPLl51fc8vMydvgjdCBFhWI5hx2R2rrwvAr3XDG6Y8Ix4RvMsY0Zk/p5ag36ftUD1CfCCHFzPFm8HeYDcUwN1HrCEPkfMGpMvdNlBE5MKgxitqDP+YAa7GcpKFVcEvuUQJz/Hgf0Vn1mBxpu90HALGGBBOOhe4JscULcTfZQoztZV9CFni4vNpJBKuqG3Onrlp1kbt/ky8JfNUGAYEYVR0Y/Sd6tfnAMyEs8aaZ0TyePFnh8Lw4Ce0925n37H9QEPlvMM7NCw057Q2I0u6Kr3Ia7ltWVpOFH+LTrtckorOxVfgECjTS07M+4+g2AHyk9uxWKXTlBUmzpJ4F1CzyWbHoTKpfVoXKMvd4n/DuYYYO1xbBWXQLm/m5djiTpE+xDvkO+9w27Pt46pJeUTHVijNI4AxWh/1KJQs5e1adk763JI2ml1kLCwx4tdP+QTiW0v0CbSgLXE2QAHjw7pxCKqbi4oPUuh5hc5yMzj1WLhPaK/QFb2hfq2Ldrx/LAu3vl+jmwwFtkUtROlWUtoUTuv2xUM+b7vzDPi1hl0qerJeuq9lZ0KIg+haTa1+TUqAbKfBBOcIWrqGvyqQ1ZZSbvXwi9KANEReo1HOTkaUkQxvvXNqT8CUXrYe0+0aydue2aFNooL/GLoWIu0IRiQmq+ALjJOyNlB9Q5eKjDZ7Qjatrm/NpxgfNBN12+kw6EV9mWtoJ1PhGWzJJ4xtJB8fqn/6GJps942FWDSeso2fP6wHqpj8d7xJ42NIE6Lnis+OikqyJsbK2txL1IftLcifGpzHtC6/mmNV0EcwLaSrlGx0JDc8IDRITpliQ+hlAKR8P6ms5LlvjvyfcbwIq5NRdBB5HmQaJOmVe704UkPXZYBxaXAlXdcGX+HQfS+tR+nSVpKBTvksueYEDxg4+yTJnbIUTQWUqWRZRBnsmsNKWXda0O8vhVu69M3C7qiPEi+1JN5NPR7tRUOoZohptu/GcmOfPI4f+/RsN6S8MghXr0t5PA2OPAxLAh4gFksPgBEC4vNdT0DbMx5jCo+GUkmNaSRcRTdKrr/m2uhUKWa/3xxzOaj9nUyRjAGo9U+7ONmEamA3cIocqVNvW9NHIxMCU5Rqv8iyh03/7cGzVUlNuu6KHVgAfz68jb3L+ypKIDUGitIpjioA3PkNfl5SYvRjNDboYQUieDtbuQJo5aaPXQBUuHdF1CZchvVKcazRC4OhmRdk2gKziQil0F/2OXLBU83RPSREzoIv55dTrkgLXOKWrERugFWjXREgv9VTKv4RSyLXe+yDBGO9PPnG+TcVBfzftQwmZJRUoKUze8+LVidFbWqmuIbwtQI2qxJT6lWcVIAwpnGE3uOa6SxXd1Vm9oKaUqWhFOTQoh4o8cv0ALXgfbei3UIFpf6OuKr/Y07lOQxaBny+TdKIVC84py0i1aU5D6f8oq1i1skh0bCldjtGYU3BIduD5auwiw9XUo8mlfCg/EB8DNJT9jPUfqNIlXCMCNxbWUpxhfQl8I4HwXQ558gKPcn2o9OoZSsmmY71obKvRSMEn2EetilnX3sN0zn+N7+v06seQocMtylCeVNR2z3ZuJwbbKpwmaDortdzufpHRmnB8AL28pvQ1Mz0BJZ62C1LXJpgb1CYbO5/M7mJh2tjppbidHxjdSytW8SjkRXTLKr7/fPhq0S93GMEklCdQk5GAxQCVFEVfGsikkIHvpxwCOSS9LMFM81qRHJgHjbQ0KkRYDcFE8Pndiny21bbBJL18ng6TRP6G/4t0LP8C2ZsHZFzcE6Xo6DtByEqvpE78mR6N1/W7YJPSDN3lVJG09ceTnSnCyH1gmluJ9Som6iB70OFMPL3w7zHLhTFcQJXK4m8ru+OGdEZoizSYFV96Uluz+c6ko/qjHtNqEo0KkVIrOaVI0nNIQ/c6a2mX1AweVo92s5WpKx8F8OXkdWlxIGtgdZpO/o+LYbfNiEdkOCPY2oQ0cZi1J/DNJtdktLm1YF54lF5EHgVwyIAtRYISv4DGr5wfVFHsTF3RfsqW7UjJw9i7PaRh4tX8xt1FoM4hktg8bL40whKaf304OSVuvEiN2qd0chz37rUU/LK3c2JcAQ2Prle5J/Ccf+gEspRot+f7+Qtg3eiqF2x0NJoZmhiLOoA9FhywfWDmsIOabmbIQTBi18Ihtu2qZ0c8hjC6XIj9skSh6AiCf38QqlLKa9TroQc6LLX+TclDQqDHd54qU/2fN4BPDRHZ049fEw9zzqpbi14jvkJuDcnbFcxMqvBXA6J/HqHJWnOaa1t4nLxplVAtg5C6dPhbP3fgvc9Tf+lN6cc+Ctiq48vQsKg7pjDe4GttyA2AI9cKAn0KnTTKNS1s7e1+F28Zt3GHhWlZt6QdrN/AUowPhutuMALdwQR+E2Qh6bZeNNEhsarorkQ0HRiNP3lDu8jOngpHJAhZdvAT9zpH55rcdvFzMDlMs/WCSCGS8rksEr53VkSMhMiZkJJxH5wGlHVAOuG+j/7hNEIS8buTI6+6t8RW/Ejp+alF0N5F2azvXAFHS98vF20IGZ1rpgHYF6t9E/2mIMfKGKJepTCi045IEVgut+b7UXTBahP9oZj//gSowgPaME//8XbyhvpZMN98Vim/59CE2o26ENCs76l0aVPoQgzXILKHRxra1GiwWZsc7KPGvSWksl2osB3L3cTQKTej60HfshO+t6DyqsEVRORVoqFAQl85Klzh4WFKhlReTxP4/ct2ziHoDf14E6G8dZL7+8N4+8LybDSaVCJVEfZCjR0x+okMbef7l0sOw05oRTtcZUuCSKo4emX+OpsDt+APX6uSWl2jBI8/H/phyaxAHuaNX81wnU/D0=
*/