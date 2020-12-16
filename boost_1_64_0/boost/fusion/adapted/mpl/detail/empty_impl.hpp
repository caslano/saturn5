/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman
    Copyright (c) 2005-2006 Dan Marsden

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_EMPTY_IMPL_31122005_1554)
#define BOOST_FUSION_EMPTY_IMPL_31122005_1554

#include <boost/fusion/support/config.hpp>
#include <boost/mpl/empty.hpp>

namespace boost { namespace fusion
{
    struct mpl_sequence_tag;

    namespace extension
    {
        template <typename Sequence>
        struct empty_impl;

        template <>
        struct empty_impl<mpl_sequence_tag>
        {
            template <typename Sequence>
            struct apply : mpl::empty<Sequence> {};
        };
    }
}}

#endif

/* empty_impl.hpp
/LjkeRXvkRzPXOr5kmt5Fbvfbs55+R2uWdIm47o493L988w7o/AGmcPL+IgUeHSFe5I8r+Bu7zIGnsfPSZbX8Pnv1i/P4uUS8QpOeY9150U8aoW14Hm8TIbzMt4ie/E6DllprnkKx0uK53Gh7IzvF1fLNl7BO6TBG3jVB6Kw8Qj9fDAKPyi7Lo9Wm38ZzotXRuF6yfLGh6KQXmPMPPNhz/LHjDn2tVG4QlK8gsd/0r3zBh76KevIK/grmcDzFftciryK98lePPvpKFwoGV7CG2QOr+HvJcdTn4nCWCnwHF4kU3kNH5RVPFxj/q+1Z2L/gj1/fRTW8ypul3XcX5CHo2UNz+GzbvAeiR3Hfsl7n1fxa1/3jjpS/9+MQt+3ojDpKPOP22STeqgZ+6365Tm88bYoTOP5zVHY//YojOThjih85c4ojHNucYv3m6xXj34Q+f9dNB5ewIPr3oHalPDMu6IwcCTHZ//E/cbn4pu2esfxGn7hp8bGw888yzJO++zdUVggTXE/+OFtrqHewNI95pdXsfnn5l+bLA7cF4XR6rlfeM83PP+8+EDkvz2Lwi5exy8/GIU2Hnb43iFLeOZX7us35oQXdnqmf2s+eeZ3nvtd5pOnHo7CKx4xhng8OO33rhU79ofm0MYreG9Tc5jGw9Oaw9myiBfwBXs1h4PiecBRezeHEbyAw57RHJbzIs7cpzks43V8SUp751bxy/s1h1XqqWc1hzfKUvUyNu3fHLrVI3zFs5vDSPUanj68OWxUb+CmA5rDZp56XnO4R3bw7IHNoV222hsFXCnbeQVvlc28jnsf1By28AjHSDFjbnGxLOUl/LQ0eBXvlaB9OLg5vFh2qmexXeq8gCtlG6/gnVLhDdzv+c3hdh7hGLmK53C2lHkBL5cSL+MGqfIa/k5u5qkXNIfj5Vqew0ukxkt4nazgNXxAdsTjjIxTdvEszpBF8bVw72b3Hu8B7JKtvIiTWqwZr+IrD7EGvIx3y9CX6/OFzWGW5Edqj4e9qDms5Xl8ryziDTzy0OaQ4Tn8mKzn0YudJ+t4A6ccZq/wzOHN4SOykdew82XWgpfwDjmUN/C0THPI8gJ+VpbyGu55RHMo8AgvlhIv4zOPNCc8gytlAq/it49qDnN46uX6kxwvYVWm8hqGo+0tnsJ2KcXPNU48xtyO5Nh3rHnjDXzRcebN/GTxbLld+zxeLDfzEl4v23gNfyd1njq+ORwrNZ7DN0mVl3GDXMVreLeUeQP3G+2+eISnyLU8j2+TCi/jLbKXsdXxGa9oDhGPcIwEnsN50ojvCz8uw9WreK+keHil/SM7tclij2xWL+InZQuv4gOyi4dXNYdXSZN5yOEHsp479ewJ1lS61Qu4XDp4GX8o43gDDx9r//EsvkFG8xL+Wkby1LjmcIW08SqeOd67iNdw5onNYQkv4Va5kIeTmsNxMsBzOE8O4kVcLSN4Be+QVt7ApRPs86PV8e0Ttec1fOPJ7otHp3gXTXIuL2HrqcJz+KHT3W88/py1k128gf1n2DO8jC2T7ZO4PV40xVjVaxjaPBc8hR2yhRfxVtnEG/ihM80/r+FLz/JM8Ry+6GzPDs/jp2UZr+FDsoanpjaH8bKW5/FiWc5LeJ2s4jV83jnWwtgy+DoZzUv4HRnJG7jvueaf53HhNPPPq/iIdPDUeZ4h6eYF3CCTeB1fM91a8CoekTc/PIcfk3W8ikPbrR2PcIMMO8Z1sWWGOVTP4PdkKw8zm8O7ZDuv4tAOa6F9hN1yEC/iTtkc99nZHC6VLbyCw2aZE57BzTJU+zC7ORwlm9Sz+HlpUq/jZXPMeXwtPLfLnPMSjniteeZ5XClLRukf75FVcZ8=
*/