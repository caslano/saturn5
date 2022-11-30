
// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// *Preprocessed* version of the main "equal_to.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl {

template<
      typename Tag1
    , typename Tag2
    >
struct equal_to_impl
    : if_c<
          ( BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag1)
              > BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag2)
            )

        , aux::cast2nd_impl< equal_to_impl< Tag1,Tag1 >,Tag1, Tag2 >
        , aux::cast1st_impl< equal_to_impl< Tag2,Tag2 >,Tag1, Tag2 >
        >::type
{
};

/// for Digital Mars C++/compilers with no CTPS/TTP support
template<> struct equal_to_impl< na,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename Tag > struct equal_to_impl< na,Tag >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename Tag > struct equal_to_impl< Tag,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename T > struct equal_to_tag
{
    typedef typename T::tag type;
};

template<
      typename BOOST_MPL_AUX_NA_PARAM(N1)
    , typename BOOST_MPL_AUX_NA_PARAM(N2)
    >
struct equal_to

    : equal_to_impl<
          typename equal_to_tag<N1>::type
        , typename equal_to_tag<N2>::type
        >::template apply< N1,N2 >::type
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(2, equal_to, (N1, N2))

};

BOOST_MPL_AUX_NA_SPEC2(2, 2, equal_to)

}}

namespace boost { namespace mpl {

template<>
struct equal_to_impl< integral_c_tag,integral_c_tag >
{
    template< typename N1, typename N2 > struct apply

        : bool_< ( BOOST_MPL_AUX_VALUE_WKND(N1)::value  == BOOST_MPL_AUX_VALUE_WKND(N2)::value ) >
    {
    };
};

}}

/* equal_to.hpp
vecFgQeVCSpvdyJaIgXtMn+HzO/B3DyqCuwPX20oQFjdxHpm68BSeN/zXku35J0afwonC5W857zjwRcIFs4Tb/1HabCgT+Zvt/Xb+qv9ck6JbH9IUMR3wa4MFlRyCANm4N3d79h7l5Xt98GLtl5oCXSQ7V2s1kk6yyCQISjR3xm15/ELBMGplmPjN2HQ9F4MdyiIA+1xVn8lftG1A/EHBG0n/coKrHnt5UBiSgoGY7286OU8PS0fjP9ZJd7hSB50/1jsg0zb4Z5pW2za3ppJeXUn+DUW+BtNP4R/ZJfV80Vrulg/CVRunZTe85zSmCCZ3tCRnHO7VGm3nbCd8FcHBBgTxfPWF1SjMF7QA2jSE9l+O1hcOWdXs8Wv/MOfgDrxAh9RZwVSpzv6fQBLqp0CwvBAwj0suCZDp0rTcwZV8E2iynDLMay/wXgJazOBejpiF4N20ceL0ZS8pNX7CUjv4BQWeMBuVCAJhuTtXEFPrHta/hmWu9P8Y4A9jgpy5bRq/aouVMuVF1Trd6W4PHaUj8X5dZG31ZmZWs964KEFydcIEFrt37Eb63m7G+zhJqC8u4GLwiKOA/a31XPMdJO+vh/Fn/R12nlV/ueaTaC+5pi+9oG+LhpJkj2xwU7lgFJLXdDuORm5m0lcmhSXXa9SLPowjT4Mc7LA/fOILnCTIHB/SwL3J3pjgMYTwbfr4zn9jD6eMJSTIGLHUcQ+NETsmCZiDrkFL1HMXP9NHzxlG5F5ggYggds5e5Crlo2YuIpHMEBCHrbSV1A6etV34AUNHkPqmp6ZxV+TwF9HxmtI6iqZ1NWT1N1GUsci898j2QP2H6hWij9nshcE2Xs71utC2TsMsrfEymSvd2GyZ+vxTIPoeVXRi3t6DNEzD4FJABlZXp8hhi+dMIkhe3PIdkK2U2toVtBjiOTwqdkiWarxvy6ZZvoly2f+v6aUzyNfRz5hfRuCxbUe7+q5h2tZBHPpgPIr6EBaB1rzUwLkqFy8K6THvYZgUlppZESIHeU8n8Ekt4oLKlkgJ1KIwzpMlfbGhvHPv8ByiNoE5VDN4ynydZ58dv+l8796eSGobMmysPPYeEYbps/zrTyIOTl9q0TfatFXLPoKRV9J3Lc2i6VRt4q+ctG3XvSBzNSIvro5k8XOrjf162f3L6DeAAJB+WIlX6EKjLl4XIkYXSVGV4vRYjFaqJW0LTFqDPRcM09t61QFFoLSmVBRIoioVa4XQWdFa8RonfKpHbcKg0HlzgzikiVBxc/claP5jY5fdDf0KvuXqBOsMUwkWIlMoV07tYsc7SKXXdD7YtTFPmHQ58N7TfsfOXOs14pGis65G1eFXVJZYVG/pxdrSg/oBai2sP1cz1lH26ANFfHKlnR3Y3nE5W4oxKv1ke+4G4odne+ic3JjjaPtTZLsYvhOJ+700j2RLuocbTtZyHW1NAyELb+SgvxRYGI7BHgpXyzLj3AJX3FsIDGRAf+zNhTHduRbWheJ7KLlFql2stnqD4aUazDlPQKsVlFztK3D4drCYVF6bYegaGS8FO4m35J8Kz29LXWARDhAm1MIy+pcgiVzFiwrY30IS1/CCpcAgkOmfSDtxx+sbPqpbVLh5wvZ59fD52vH/PT5+uX0eW7W5wuNzxeyL75Kn1d/HNI+P2Z8nki7GSbSRNqNdFHn2P13Fyl6naHz52XUH/8VSHuFVKuA1gPSdqNjL5JM0an4JUyhxMioXqgj5wlKi4m2Qnl/MYmxnbhxWFs7V+boP9KIc4f1evd88kapNk9XpQsGFT1WzwGWbdtx5saJVYWegXC6+CMsat5YLFWtFrlE1SqxbHXkRmjt6Q1ndoEw94IwV5WIjavExtXQTGzUhLmxBNjb0ebGj2FzRxvOCMevx9+1Uxj3HlnctOXxgyxKF3dnpIuozI4qW/FUr3UqqKy5CuSWEMTHQbVKl/L3LsvsYNqLQK+PULTUj3wvg8Vvw7As54hUi7CarSDXTvqVtQPnEy9mddRfaBI++blFwB1DZfTB84nYkVzKELwqqPTkUt85M/r+6BrMB3gFVXcwn+EtMucD4HSwdDDHDDAnfO7G/JbMeFm+DYX2M2U5fI7WKqRdqnixUdM9VZruqdJ0T5Wqe8RGF6ifxnxQPXMZL10fjd350KXr3Vdw0r2FuLwKR6VriRu2cdKtoMU9Z8JNKblvI/9Ncd9J6B05D3qPdEi3FXoOk404HPlcrF4lVq8Wq4vF6kLp9hLGVjCriZeUMKhno/0t2qfrl1lm742z/i2VB+bZr9PyPVAOIzafVrey/6rZElB+k8ZMNCgosXSlWFoolhbj5HoiHeZEcM97Aaul9MLEUPkhOcE4BT3EX6tiVDGFMUqOtjY1K4A0oCxOt7BxAvULcuD0K6v7zlO6Ak0MeEE51amJQbpUGFD+cxnmFFunikEgXsrE4MNcrB6s3JmlskEFb2KDCqeJDfTMHq0c6sQ/4vvh9D8uovj0/7jV4rBIJ5WXOKou/X2QVvj1FPuVL9bzQJFldIw+oDy/1GIxti/UCiXjuPyNteZY5G0rQS1Vcs2WamXrm5xFrMOVJ3DVsXCmCHMdbuImWBvg3xuwMGKzRRG0VljIIV28DdWcD1PwF51wh4RIthhYKQYKxUDxhOBHyvj90lmxllcwMC52P6judJh3TdhgPLQkKnx5NTQpXRn38kSkhlkty9lYzlJeWEd4JjfjGZFWeXcmc6aovCtGc6g+tale7wLemqdeb+K7K94xJ/U71J1qfrra2O+co3wAkA9EnqkQxqZqJQEe9KrVYkoKbiW90a0rkRzTxnBlrv7DDtMuMbpCjObNXV6AxefiEVVkyQLzVQeC0pTyT5nJU0FV9c87HZTL7ISlz8Wa06K8ipNDvFjJ+UkF0uqgDMvWOrUVfE41fYmtG3L99DV6s8wl+lwA5R2z6N08j37DRM1x7xTxYBagHjtqx9NNygKm1bzzTlE4dfzSE+qF9QcDfD6kdShih3GeFkMpOlxI/biv1N9V1J/zW+vvt07sL+db689N/eV+vf6CGJiOrEzTq+MqayqfAs2UX8KiqCFlfqUbnzXtx+Z8tfxUlCXnQt7BpJwzadIaiuh+O7bdbgnnJd7GtHH/39qxxUZRRWenSxhloYtpQ5WmtrjqCiUKNUitxDaw24ZQ2O7aHaNtMUE3deRzJimxXT+W/dhMxkhi/DR8+gE/ROMHJq4toWJIET8QRcHENU6ya7JCbZdQOp5z7p3d2VfbNPSrc/fee+6cc++55zXn9L4ZKiawYi0DJ4doHlrssMlFRBWupmJH1NsnqPlTarZ7D+b1vnnQ7HoUBvgIsK1YojCi7VRcxvAfYWrsZVViG9hlyZ2+YjG3jR7I6704Sd9AqHySl9j80GxPdYhN5a4zFcl7HB3A/PO4ZorlyGjbMcPB0Pg7sPzx34Cbhq3mLym1TFP2qZDjt3nnby16IFOLkJ2wOcyfRV4XzRYyWXxZ3hkvtb50W1eRHU6I62OHfI1jM1X7a+/1j1e6L/61HTTGoPSFS+3CMIyGB8DibY8lZkOZV1whGYQoLBG6Tw/ON6QpKItqn2f3F/cmWSkH0cNj5rdhbIoUroHGv0CXMj9xObQKaaUsdJXvs8lpX5Xq2Ffvmi+6ihrJ6Qdko6KfbpsLTwjkx75NFl7aLOrLsBUT6eUQbt8c23NeXuS4bM+VJSNKTEmC+h4eAclx9kbzWH7XF1IEmckp8KN5hz4Ch7bIkNU8mabUlI4yvJhqTEE8pIL4Pf0dGxbHS/Z5I+oLy5hjO9gesppbak4AY/W4P2mdkqgebSru77rSfRRUlu/wfqoQgS7XtPwGfbJ+wJPG3eQXmImvJYQpkmrBCrbPBn28107Wq63UC3qAxhT0zwbbsQ8oTsdnaFxVayV9PZtXjWfRPBRqmhrNfEuuMdAqeMkk1C3J9jIoRTDwJjWVAbkdZP7UaN6cpE89tK1GgCpIMingQzHboE/lukdNtQuICop2Z8JyqVsTlqh6YJrZPv9mfGsPDWFcMV8ypUM3bafeZsBWNz1uzE7hpkgXe37GHSTbyEB6rLc+ESrjEaiChxEohLosWQFZfwnfLDVVgFc2zxMqCj2L6qv61FLSUg8pFgb9N0t4TCPuqBw2v7oUEGRuh0XNz4tJA5gVjtM8sARCq/MjmkGpso+zvta0bEyI3D4c06VEWowlr2j/wahds9cLxiFBhEMUpvhkF9n8gjSTw/847Vk9XqnrFlqtUmN+nnFtdIldFz0z2rNoV4Dpny6QC8RxPgm3nCmP99KFBb+oFMGmPUYPGZbOmnZE95hP80WYTnTDPAs8AlPIRoxjLng8Q4+Np9Ncn4tgMBLWwMzbp9mHX5lPpKk+aI2jnC8e5e4x/+QkyOTYryeQUzfC4cIdhe3vdo9K6jhGqzOjPuK/gHtYxk3shBf1YTjIGuFNeeTSZ9HomoAxYmo/aK7wzwZ9MJcCJaGJ/h82U7gnxsi0kV8Ln/AK5ed1+p+V6+cBeKCRxFlKUW22TSEoSGjPUZDcnHl4oUhUycl082VUlZxU5cabRNwnaDsUl03PH+8TPb3A0QdEeE7Ts7oH3hurBA4DBwjARXUU6y4gJVvr8VTQT6OAnGn9btV1VWW899a6r+7tObNKPZ4pCW+KSLEM6NlLWFgvuaDKzpR6yOmiR6PU5IYTHoqwnnTJFfWNnEsQypFWrXXMUBIkHOOgBR9ao3cZP0I0d9imhBvm+wVCc2PIGMBj8xY9qocJy1592MOUdRvXihDmmbsB416G8Ser7wziF16hdF3wBobPg057v7c2+wB1N4NnIu4vQ193HI68bK/9/CI78rJxTILHzxfZkceoWhn+8MSPd7J8joCcTkpFxs++fqApjRQYqnM5UsMBNJBqMS4j32RVXoibKFi0luk3y5aViDOjhekwb1DG2N4hZG6pQK7EAyLhOhBxEug86VasrKgIDB42Uj3BSY9BlxbukewmIr9N/Ez1hqmn5Txi/O9eKMN/2wLDf2ZN+FfXg3+Gewop5Ph/4eEjxn+HYjFYXLTUWkpXEQoPWamCOJNbyD/D9c3sZnY259ZBHk6fq+fWUN+QW5epsPIGxnQbnNZl0Wlddjmty0Jd63IFN7Trw39wriyesnpFQXSuJzHPanewVduhXzbv3bWsiyTZjbWWRylQnAUGksIqhpCc5t8X7lvFkK0m7nH4CRov8qrQ8FrYmg+b31xAY6uPRSLbHmOSGtakvc2Zu7BETPV6yuq1aVIi3io0Ju9hCei4JGjb4IV2wAuxKC60ebaSLSxijOG3CatqdnrcHUu8PqIpscRH4oh2wuh3U+HhN35g5VcluCh2ofAFQsOAC/Ms8vvBaj7HokcVFheCcy1n2wkmybGzRkh0yHBYcNl4rR/eQDZdGwWW9X3ihCGLykiYw7uJ8G6pux3waOmVANmOQYgPsh0yPa0AEt+vMfkZkpADCzmA7TUOigivtwiwqRbAJn7GQaA/VnIlEcRqeRUBxxKT/csj6iZlhHqf/HWl9Qnq4w7fmDmE6muwFUlq+6q2ACs5/vZYlT/o947V4u1QmcnpfW4QcI1TgHN1gPZuBBaG8qyAC7O18Qi5P6/BAGYWAdH4Iub4xhn2Re1PNvAzIWCtbvYFEw1cmBHVxsSfD2E8DabQvDkrpS0tzLjwl2UAVvyFpY5E164Z2yAwFwB5OkJ2JQoYWPKzvQJ7sI3cGlGr+QjQpPFrT9BwB4GAi79sv/LM93AJXePbuX5AO8NXsmMN8dd6vwdV9lkP3hh3KNQesZVj2Pofnfpjugc4AIBDS7R9f3yT1dV4kqYllEAipBJmlDiidtp9rRaV2uhaSSFIC0laGvYdv1RkjxFnlQSrttCQVvv4kA33gkOpyhzby1zdUFE7h9pCpQWZMmWKipPtrXpZu1mVQZ2MfO85997neZL+wO37ef+APnnOPeeee55zzz3n3F+qtCJGtjNDTSEZdUKCSfU9aaaVyUO1AE3vgwioObnJPLIIeNmICcYrURM/eF2qphJJq24IeermE7NK3jwS+eEk7BASfu+cN6cd1EkYxGNPdNth/JEbBtiKBCYgohNQNhdQv15AOcMISDt9XQiI6AVEjfB1WaIFY4a0gPwHOkJbEHYkuh2QlLQ1/c+w7FsY+zS60LE/dhj2LarHPhz7lXBfuEmwnzuEfY46tP5xrH4a+EP5uvfZQd7D1D9OJZI5pFAGciOLAB2Nz78jocl4lP3ZkCo1op8xTtr6BXh164fbNKK/z+G1/We4D4Ht6Ck6AbmVRvLOJ7Aq4pRiCJB+vOLHzBaupo+N5f10qBijeF+t+NuTBjRRr5Fvf4JpN4wq7PglN+kOkCU6Q3Mz7TtFJ2ilcoyQEx8jmglziSQYrkHtAweM2vtaCID36v0vZSDCd8tAbP9m8wnb5t3Je1LTGkjmVhr5Xnfzibuz5FU0qKDFHu44Uz4W14vWhBOvCQfjFT9tnTK5+c2oX9mdrE0bKfb+YVAZgONp4YS05TgsUeMUo3GQxfaC+Y7E4KJo9gr6IktZfCpVfgoWqn2Vij5DK96Tfh54RD8fYBltibryBp+2SOUNgHjAa+z/UHf+OnWbF8GD/3gQUpvUQNXwmYxU3nGWBh8SxGbcr9mfr24nOqUssNQon8X/uZJ28oZcKbuUqsfgk1+llHKrPzE4bjV/9RF9VaUstifnpsKJL88Tr1+Hkg2ORGqyeLML3lQ6E1+WiDdPIjVXYlB9s5m+ie/eSONKufwwrUhe0C9XHlEq3ckFh/0hueGovLhXLidy5WAqb+F+tro1Z9rupXKN+XuJwVQsVwpTJSFBrOqUsrfo90vIt37NNv+4hq7Ht71geRGaRyW/omT/qkndORgbs7XqVFZUPrYXAtZIKkT/5MJ/Fvgvx/ZCqQnO96kcJHvh6gkQ1iBMgZ/NkNLuK/Vo95W6QWOSFR4rbKNq7cKkxmRkmW166p6NNZMHf/lVCu+lwvuMUnn5r2Lw/Ec4aDwZ9ZhJKTupz6xUeyyyDY7RWVJ0QA6blW5y9VPlhmGy6QfEecoBOKd0O5MdrT5XmgASm0prlHPSZm0VI2wDowW/y9qTLDMXG6PZx3pp3Zr+rrHqDifeaNDvR6tK25DWYEni/QvKu4Eq+SUJDzN3UDuYeAneGpUBW/MuXDcoN8PJuyUdd2UnTqeoYpxtovyt3U4V4zSMbKsn1CSTeDbvJbDr3JpMwuEqMr4SXWET/KgJgeu76E9oQnLZDrRlsBEF6dcE2P0f1MiI1L8YCNBJ4EC9HceKirEiW9NbeIEE8vEWVYFje4D3fbZtncasjm6sAZPl+2LZVC9FK37731+lrmGNCHDkFaexEZuwEZt4I3CRCRJJeq8MB9R2dKe1AwnUBJPJ5ciqk8/AKch6QDdzxgvo24L1FWN90XGclXGgynsyRhPcP/fxk8PolLrfZ4zyGbU5EWOwhs8ZjVECx7PeDKGFgjmjpSPdX03tSw3xfM0Lr5m+feJW7eXwkwWW7pweFu6C5SM1uFmahn3KGk/3LPdRCir5KjoxOceQnC8ye98p+Sr2mTJvurykQF5SKC/Jl5d4+MKPJdP1ca/7gxFHW8FfwbOj7zf+UhrE1IZ2I03RCTrgUhUdq/SQhX6r
*/