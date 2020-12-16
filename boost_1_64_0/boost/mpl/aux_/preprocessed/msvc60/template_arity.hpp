
// Copyright Aleksey Gurtovoy 2001-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// Preprocessed version of "boost/mpl/aux_/template_arity.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl { namespace aux {

template< bool >
struct template_arity_impl
{
    template< typename F > struct result_
        : mpl::int_< -1 >
    {
    };
};

template<>
struct template_arity_impl<true>
{
    template< typename F > struct result_
        : F::arity
    {
    };
};

template< typename F >
struct template_arity
    : template_arity_impl< ::boost::mpl::aux::has_rebind<F>::value >
        ::template result_<F>
{
};

template<>
struct template_arity<int>
    : mpl::int_< -1 >
{
};

}}}


/* template_arity.hpp
PHbBeOyDCXgGTsSZmCH9m4nLcQZejTPxBszG2/E8vA9z8BGcjZsxF5/CubK++bgXi/A42jQPQ/ECHIAX4jC8CMdisazvxZiLl2AJXoqrsIT/7sCFeBcuwi14Ge7CxfgKLsVaLMNvcRn+gMvxN7wcveircjweV2BrXGnfj+VzTMPnG8f9+Erp11XSn9dib7we4/FGzMSbMR8r8RK8FZfibbgBb8encS2+gnfg+7gOlc9T61Huu+VziDq/hPa+2z1yrWsvdsZPVctVuljuS1nuK1lun2q5GhfL7Zbl3pbl3rEvx05mvNwHstyHslwtJnk15HlIJozyOJDDwaPrcv+EHA16+Rm4jveX5GjgOl+jeRoay9Eg1//cys1wuHkZ3M3JEE4Exv578zD81TkYSrkWuZbYTuwhvJeQw4CIIVKI4iXmtUpzMidzMidzMidzMidzMidzMqf/+uRNzDkG1/8L0qfPbMgAcOQ5APq1tdjGjRku5y6nEK2IRKKncl0xxjbuHbVPij1t9MjY01MzeBKgMCs8NS86e86MRsdasF4fClXGVIi2X1P+nRParI5m/Jrt0o6p0o7JRAjtqHDdDjoo2u12VAQ23o4YuW+gB+FFdCdCaYcl1rgdqRlZ+e6MedlW2nEONc0fHD6Uf2rqrtap+0TqDndRN+R4cq3uKmpikfp6z5B693lJ/mnp+x1EH+pNc1FvQ9enZs2p31Ubv+bcVjXuRl56Vuqc7Ezbdec2frw3vYCnQrTjIirvce3Zdh2f6/OMfZJTaJ3PX+ZT3rPOFyjvZTP4pnW+INkHG/Zart/ItemINg1tycjOm6UeT0X2C9t+IvuNjHWjHePfX7ZVR6Kf0mcj9fpsZlZheOr0wsJ8t7fTH9KGjur7HChA6TjH/aZO2hIsbQkiwmhLiVFb5BfYk/1G2qOpd5ac9upFeEn9A6i3yqhe+YU90nprdeqNCOV943oLps/IKjjceq3bPKmZ8zing6jXb5RhvYUL8twff1evzp1SZ4LUGU9EKsdnozoHKkejxsdadVXn8ObOdQ5WjsXGdXJIOby+tW7TnVLnRDkGjSeGUKclzqDOVEqo/2VofMwfx3rbqu5tSle2EGrW39dhjFlpS55hW2jHYe5b1nsztvk6H0+ilD7X1Eld9YcRz+vSP4443DMnY/N3kzYEEkOV32d7G6JtTfBgfeXvv1EbzPtEzPtEPL5PZG/99pq+ISTg/RN/Wx64ID8h49a1+4/NfSJpFvl8jFPkuutxmCQ7/2y5Xj0HO2AeBuBcDMd8jMRCPA2LcALOw0S8AKUe+fzL9tKpp1jquVjqKZF6FuIgXIRRWIpjcbGUvwQn41LbdWT5fAs9dK4jp8p15DTsjum25QgXy2XJcjNkuVmyXAWRJss9J8udgKWy3BWq6/0heC32w+swAq/HabgGM/AmvARvxkV4K16Jt+N1uBYfxDvwcbwTn8L1uAPvtq2PfH5Df5318Zf16YwdsYssF0OUyHLBspwPRspywbJcT1muF3bBEAzCUFU5VVJOL51y+kg5fdEf+2EghmEwnqQqp9ZFOQOlnAgpZ5CUEynlDLb1h3y2wRY6/REt5QxFXzxZlksggmS5BFmuOcbJcmfKcuOkP9T3yUTgBByCCRiPiapyK1yUO1nKnSLlniXlJku5U6Xcs6XcFNs4GvI5AyYSjuNojJT9cZT002iMwtNwOJ6O43GM+v4RKa+dTr+dIu0cgW3wVNVyFXHG+18bWa6trF871XJVslw3neW6ynLdpP3dsdC8D8S8D8R6H8gSH/NeEDfvBbEs9bGEEclEKbGBqCV8yxgPg0gmSoh1RA1xkOi1jDFwiJxl5n0i5mRO5mQ=
*/