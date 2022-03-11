/*=============================================================================
    Copyright (c) 2006-2007 Tobias Schwinger
  
    Use modification and distribution are subject to the Boost Software 
    License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt).
==============================================================================*/

#if !defined(BOOST_FUSION_FUNCTIONAL_ADAPTER_UNFUSED_TYPED_HPP_INCLUDED)
#if !defined(BOOST_PP_IS_ITERATING)

#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/iteration/iterate.hpp>
#include <boost/preprocessor/repetition/enum.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/preprocessor/repetition/enum_trailing_params.hpp>

#include <boost/config.hpp>

#include <boost/utility/result_of.hpp>

#include <boost/fusion/support/detail/access.hpp>
#include <boost/fusion/sequence/intrinsic/value_at.hpp>
#include <boost/fusion/sequence/intrinsic/size.hpp>
#include <boost/fusion/container/vector/vector.hpp>
#include <boost/fusion/container/vector/convert.hpp>

#include <boost/fusion/functional/adapter/limits.hpp>
#include <boost/fusion/functional/adapter/detail/access.hpp>

#if defined (BOOST_MSVC)
#  pragma warning(push)
#  pragma warning (disable: 4512) // assignment operator could not be generated.
#endif


namespace boost { namespace fusion
{

    template <class Function, class Sequence> class unfused_typed;

    //----- ---- --- -- - -  -   -

    namespace detail
    {
        template <class Derived, class Function, 
            class Sequence, long Arity>
        struct unfused_typed_impl;
    }

    template <class Function, class Sequence>
    class unfused_typed
        : public detail::unfused_typed_impl
          < unfused_typed<Function,Sequence>, Function, Sequence, 
            result_of::size<Sequence>::value > 
    {
        Function fnc_transformed;

        template <class D, class F, class S, long A>
        friend struct detail::unfused_typed_impl;

        typedef typename detail::call_param<Function>::type func_const_fwd_t;

    public:

        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        inline explicit unfused_typed(func_const_fwd_t f = Function())
            : fnc_transformed(f)
        { }
    }; 

    #define  BOOST_PP_FILENAME_1 <boost/fusion/functional/adapter/unfused_typed.hpp>
    #define  BOOST_PP_ITERATION_LIMITS (0,BOOST_FUSION_UNFUSED_TYPED_MAX_ARITY)
    #include BOOST_PP_ITERATE() 

}}

#if defined (BOOST_MSVC)
#  pragma warning(pop)
#endif

namespace boost 
{
#if !defined(BOOST_RESULT_OF_USE_DECLTYPE) || defined(BOOST_NO_CXX11_DECLTYPE)
    template<class F, class Seq>
    struct result_of< boost::fusion::unfused_typed<F,Seq> const () >
        : boost::fusion::unfused_typed<F,Seq>::template result< 
            boost::fusion::unfused_typed<F,Seq> const () >
    { };
    template<class F, class Seq>
    struct result_of< boost::fusion::unfused_typed<F,Seq>() >
        : boost::fusion::unfused_typed<F,Seq>::template result< 
            boost::fusion::unfused_typed<F,Seq> () >
    { };
#endif
    template<class F, class Seq>
    struct tr1_result_of< boost::fusion::unfused_typed<F,Seq> const () >
        : boost::fusion::unfused_typed<F,Seq>::template result< 
            boost::fusion::unfused_typed<F,Seq> const () >
    { };
    template<class F, class Seq>
    struct tr1_result_of< boost::fusion::unfused_typed<F,Seq>() >
        : boost::fusion::unfused_typed<F,Seq>::template result< 
            boost::fusion::unfused_typed<F,Seq> () >
    { };
}


#define BOOST_FUSION_FUNCTIONAL_ADAPTER_UNFUSED_TYPED_HPP_INCLUDED
#else // defined(BOOST_PP_IS_ITERATING)
///////////////////////////////////////////////////////////////////////////////
//
//  Preprocessor vertical repetition code
//
///////////////////////////////////////////////////////////////////////////////
#define N BOOST_PP_ITERATION()

    namespace detail
    {

        template <class Derived, class Function, class Sequence>
        struct unfused_typed_impl<Derived,Function,Sequence,N>
        {
            typedef typename detail::qf_c<Function>::type function_c;
            typedef typename detail::qf<Function>::type function;
            typedef typename result_of::as_vector<Sequence>::type arg_vector_t;

        public:

#define M(z,i,s)                                                                \
    typename call_param<typename result_of::value_at_c<s,i>::type>::type a##i

            BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
            inline typename boost::result_of<
                function_c(arg_vector_t &) >::type
            operator()(BOOST_PP_ENUM(N,M,arg_vector_t)) const
            {
#if N > 0
                arg_vector_t arg(BOOST_PP_ENUM_PARAMS(N,a));
#else
                arg_vector_t arg;
#endif
                return static_cast<Derived const *>(this)->fnc_transformed(arg);
            }

            BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
            inline typename boost::result_of<
                function(arg_vector_t &) >::type 
            operator()(BOOST_PP_ENUM(N,M,arg_vector_t)) 
            {
#if N > 0
                arg_vector_t arg(BOOST_PP_ENUM_PARAMS(N,a));
#else
                arg_vector_t arg;
#endif
                return static_cast<Derived *>(this)->fnc_transformed(arg);
            }

#undef M

            template <typename Sig> struct result { typedef void type; };

            template <class Self BOOST_PP_ENUM_TRAILING_PARAMS(N,typename T)>
            struct result< Self const (BOOST_PP_ENUM_PARAMS(N,T)) >
                : boost::result_of< function_c(arg_vector_t &) > 
            { };

            template <class Self BOOST_PP_ENUM_TRAILING_PARAMS(N,typename T)>
            struct result< Self (BOOST_PP_ENUM_PARAMS(N,T)) >
                : boost::result_of< function(arg_vector_t &) >
            { };
        };

    } // namespace detail

#undef N
#endif // defined(BOOST_PP_IS_ITERATING)
#endif


/* unfused_typed.hpp
lGDmJ1whKsw/YCcwxNoYA6U7FMSwMSxBziiJxbVkYlkDnOMS2MTtTmsjDVwY68By4MS6MTgA5bGJwjE4YpJcYnFMQZuGrjEimGeg5ffcKvPvyBVFsLewS/sKQOxEuJifjDNzY+NGRkERNmRlEeOmRlkRRmQ0ZiRSGQmRDsyJYiKcyJgiFDL/kBT/ijAiLsukICsOibAiamdUEBfFRYoRAcmwIM/3D8MRYcG25keQkcEhFDI5ZtzQEAC93BaohHWojNZXOgD2jkTAyaERn2B2AMhhEadjCi5jqondOmATWHiYvVMK4cRwTHMoEpLkIqJzDMWYMCbBytETe8agBDmnJCKJbe3hmIgYliDl8MYsMTSC5uDGgGBYApRHIqYmkjlgYVialsDmWIm5MS0AykESf2AMBI+syysu846PEzoscEwhisUZWTpkGMcUECGeUVZbe8iAkOM+goJlYJAcYCAbi4hkzkWemh4AIX7J7A1DvtOR2fxGeFBymAGZjmg0Y5xscGCxWIgoR6b9N65FSRGQcU2hEW0ZFgQHPMiyvylQFAuRGwlHVJZxSnTAhBweUdBEx9C114gJYH4OMEuHgTnqNTAOQmxv2GNgEpX4sOfCzDQ9buoAxxyUvc5BFdwUj5iJCM5hG1PCmAQnh0yMGWMSuDguQUdc8V0almgkJtXvyPybJkByhMTLMUsBydMSuMSADkwYliYioOSxiWZiWgOJmOsD43IONDGXhib4HIvy9xVT44IOZRicU+OIDqN5JXY3FKheXP5bFIh0ZGAR4wZGGRE0ZDtERNmRDyJLjI6ZETxkCrFiJcUJkOCIIzIlyIqDImiIdr8JT2FeFAIRChkaIUVmFVFhRiQgEgCZGiFGphXZ34TPAYI8PznMRyShyzQl064SF8jcf7Q0KcHPoSgGhskJPIMoNoqRCVAejZibSFkt/pv3IPACbIxEdw5x5RRYmA2MQU1hXGI5MXs5BVmIxkgBxomDEmzEHJcozErjEHG8HTHtmAOGZMGJv4+KiKSxCTQxh8cahqUByFjk5AekpVEJZg6l2AbGwNFRG8aZAYh6cjjmmRGIKxPsdXmnG0Ni1AdCqi+4fwSxyKXhAQbiR8Yp+QEAsnlE/yJfZLiSJaM3VaKbpI0UqFulwOO9cfydcfFvXBZmxwE4wjE5h8YZOMAxMg3+0TpwcTRxmbtF2Rco5pHBcU2z0zUF51C5Ue2dyjK0iOQ6Ni+bHDVdUP7IVA0gvJbQ6J741z30rb7tXnzeuH6/cP145/70zPzo/e/VH/wBP7i9+1ifN9//R8v/t/rH/K5vMc36tu/HwfZb3YJjlif9XTmZpYp/iqHvsVYCSaqzD4i05lq/viNN5UWLtAG6+JXaBfRVQSJ3Rnd2kf+ZfNQ+5LVCnNNi93tQhGmCYCcpiwBzYy7GZN6GEG/gxIdK7wt7NrMk53SK+YSfPu/el0E+n1BONzN5ek7lrbrXkN0qSSQwQSpJarD462Zz0+E5hgrfwQyDaydfCsouHr6kCBUzxy7MyO1jKB98djYBFn6kerpRAkq2TohYcblSNMcEUlZbjgVFuvEm/jinksA0UHU2MXFaKn3RVzt+Ja4GmmgznycQEH29q8iBWrbKsdTaI6N3IBWwjwb2KbL10COqEM2oAkyd7vN+Tx2iz2ivv0FeaKiOYjQiTICQJRMmo2pUIAXH2arLwm837qqt4CTwX28jj+RBCrrxxJXiIadbkUM9/IjNrV7DCLyWk0LDomSNrwEZvbxIiy5L4pa2TKwAk+XVtkvbXtKXpIe9zw+5vMUVaSQOKaKCLfo0wyY1LM06hGXLTXgCy5gN+agxuhvkvoY0w4lKL7zs4IRRquiWza7zwfJZ0D448rCDSfCfTXVV1adw54N/kF+Hx8n8Iy+zl/5PSD2+Aw7STuGcWnOLPvO6KMH2y0lrsXEreaKi9p79pH53zJ9Mdd9cjWSjaOWvx/8G+Zw6XKD4Qg7WmhWtx64Bof4FlhYejrtJUoFgsz0yFARiLNnuI8Yb9Dyc9WEHWoUL6RzRsbP0wwUGwR4pQLM35fED22cNKE5TSbnqRo4YvetP9z8cof6O3ek/L6p5VlQXcGfaXcAxb2paIp5W3rciZjXpPVuYMs/VOqjV+yCR6majUlKL63eEyFbYl6XxvobElUoAmG4SnymoV+d+HhCVxPWRz6dXtHD2M6yC2ZYx+8OsjrLy8OLAFNF2oGA/t04UZqKz8vgcaXagnoZPzLt38XPuRs26E/Ef/RG1Ir6HEyShZMeW8KOpJHlCDouK4mGGjYJMpIfhjsTa3WCEWlC3T/bfz0fUFRVolL5do0/He0CRqHSaeMMeZsCR/ePiKFKFtkuoidsJlrYF9W2VK/5wEZ6i1zw8LqE8CuaeI1/Q4pE2/hj8IVE9baiZ++1Gj0FJcP81Gfoj0I7k9HWiSg+zeXbdanbnAKQsOmcIZY5AHNUtwCszmFcINLb1xHTO4wtww/HuRTcbI1IkHo7DfzzhGdx8Odqgu8XjfVVBYqwDgprYX2Qgm96gVZF4PkGG8kFtf3O3X9VVRoRbwP8zVty5yJI1GEr1aDgebj5sX+LYiJpMrcMnRNX6kPzag1Mx+Tev7404uNKe82SpxR15c0l6l+uGtLseDZ3WoK6JwiZt7VYq3mtFdarMT/m8IO4dgkKg2smkAK9xKut8Oowqn9om9HiRrazpBdFZ65IEYbMLXhoCteMfkaW/JVfzV/MW2vuVQOHJ8hUCmrdoIBXubJfEzdBBpmNC+OzrM6xq8YJp4WOh+5Eq8H5In4bV2OhPdQs+gxCqEQVVw6cwx17bUrRusL4I8ChyxFczQhRnBiVK9hfmSFRWTTdq5ysTaudK75DEP/j0/YExdyDWTMothCVbUdaJY+U8qB42PI9yxFdRqBhFyZV5Tv0SyW+JB3FvkqbD9MshRvhdRfV0IdHi6vBORzfo1PMPDi7XwxiOgd4HSAKqz7so37E0EEqnnMoSv4c0jymJ0sl9UupDnpwSWhP23PcUXI7cZ3UB8KTSvluKYU36YsIu5XMnx3RSZk4jT7wh0x3TC+rJ/sGTZyI7IVQFU8tEpnKyaBTQ99u1vePYLfqJtZ8WY3FxNBGclpJE46rA4StDzLrTVe69B7GNBkoKr1pMp/qqDSmj+TwNKzapi0QITQ+WCONlIkQuYHohrMhhR97M6gnUxzaN4ci/pasQwZXVG8wKxMN0OlJ0HHcEVvTr0fK3Vi7EaVmg8ISIl5qUTJeBhOFXryYfd3GS5GQBhc5Fb6R04bu95FZ8oWa1zB+SQbU9INc1MKyo0udEijnoUWQhZLUydH8xp+tmmm5uIqvjQsmQhsEzxx4IdI4hUfJR7U168f4yhXohDdrv2jP6Zzy0nv61GevUYNhOSuG0/a7JQPPWVoy4QdTxQ706raOHFIVu+PlWwXi/0YUwlJ7nCaXgCo+KlPsTrVhKo7UEJ1siT7ZQb0LSPDH9p1v/Ukza9Mxq8OyVWY3SR7qglLo0ycVbUOwMcmPCinhp1ZojRa0n1P6pxqbM6p/0Ifaaz5SwFjjdqiNE/He0NxJFso3gcJGvoXNNWoPlIS85rvOlqEbHsL/AOrXrLpfys6/C8/MPkCy/7vsu93++hJz2hfZQVm11SELeAJhHHiMQJBKLdC/6o2UpDk1rTFlaIxNI4lvIc6NTPsQAE7zjApYLRWsptThNaZoSpHd1+pWL+TiDWgePx7dRpjohXDh3B5XCVaEOi4Yypk9Rd6xvfeV7fwpc9bJz8/HFd/aX76Mlz/uq5Vmzy5I5KcBfpItRY6G6dAk+buMdAWUV5YRzFnCLvVETiy0J1MH/ZFe5rI5LhW3DXU6bbaJtopBy8Se8VZzdUn760lsDN2qkNiez/vgy7HkBbGMOlbzhhOJODxgJq/9V552pnudNdlBE3sCTalOoJX+o2m3hI/DIcgHMx2b27z/JLiYNM75SOGNOtT9YI3PT6BDx1I/2gAToMvEFUFOtDOp82X9WZ8SSWk7mcqtQufnCr1sa8XFHelXVYnXcsXlUqyeAo0OMV9PTzSs1XONHufN+aqcmi7NDRmKAYcf1fGDUjLtV4zUD0RqjUiMGbQMj650Beo6QmnMy0bSZ7/1aUy9acJ3lelk/LiP3PHsYhgTub8D+lo8O7IRM9WMROcWlLmaWJzu/BaG5W1hhU4qswCH9xVTQln2zNYbemb9dgX1FkBQLV6/OBMkScMStGk2QcxeOcFl2hKYzf63znxWGHBPDqWXP1vjy14R4FdpRo/3Zw8mvVIplRNawYQw6ePapP6lYtbuw45F9nvTlIlSnseezFmiFWDLsjqhZFxKboLatd7kcAeFrZmmEMwc+AuRjyvPflposQ3YmYzUqsOMZb2l956DNtxDUUw1voFT4Q6l79tG92lAloO+kG3kmXxtwBMAuH0DZjAyuqMzib0ynrhLYSVKdoKqBUiHHahAV8GGhjaphAUvTDP00dR5Rcv0peqXplSQjdDQI2kWlkDDoYh9n2A/0j9uSmsKIPMOftKCgPaSVImDyGfPtM9q/gyoAUWUCaoqtJFB0FO+HXufHPYyB1vEojmUjTUOTVMu6F617lzXgzw2Xn7GBP7zH1XMeiBtWstTAccGsApvRPYx6PIsn2PFRKQ321f0Km48jMfUC9ahMGzmLE6G+inl7P1wPbxCVNnZ2ablJMp37aTJo0YxOBTNXK9w0S72B417iBzB0WvOshphWPROk+WoVNTZiRkM1uAzVH5kgcgyN5x/AUruTNOwGvUzp2o8U8xbmBtbTtREdjYgwuPNj1Iqj6i3AH768hXObUu4+BKAMdH1XAIXRJnPNf5Wxa2CVODCG9LxJTvB2UDT3bLTe55oT2TG8oQ9Xz2Pr1yk9Mz0urktsuYsvUVxBN645Ga02Rd20gjtSF+IThU36pTgHmbjiBkaVTfpncKsypx1qO27T9Fr1AjteCkAt1C1CqntvWSEMMuRj6nZtQ2kvhiZpTOgZ/mbLbAG6mlntP5l04pPMk9qM6ZAEgpWi8B6BXRw8Zo67Gt3ScM44WKV1iIOPz/fAUz8066QRBrLrHlLVzNNESOBKbElzE6opAMFf3IyJ+NZA+ZoKSH4zG4VUhtwut0qm1nh9TvNwzEMWiWV8pJf8LedwU2PBT3D43QKai9ZyZYixl/crwAsV45dOlmZn6RPx7wZ5XgLVxdVnw8pz83K4kOrrOt1lziL/A1iAp38ep6sdg/0pXQB9ZACYBGVx2UADZOMAnZKpyCMGmI4DfJP+t/gBMHSFycj9KTrBOcvs5igskVFuRvr3m/4+aVSR+zK97zqBdxqwsrkxtEpX9OPRekemwntpWRbmM3IAG9KV7mwDhigUfZZL9Ct57anYN/TcweXDt5OT62aWT/xqZZmWe8j9Udr5kbx9L5Evb+UoFs4rDeTn6B7qHYR4sn8l3yebOBGRgEEMi+CVByoBiX7TY+gndfWMFrym3G/nF8GtIXzkIz7a2VUFMVOPUPT9KEr+cmKfJkJR2b9YiGtla2F/hKfHkFU6xeWvP/6Zrkgx5g0gQcx4r/QsRH1x78BBoD8aJwUJLp0ieL57/2+gecTq+d7qWdoQ03qUtyJlz+SZtvbMfMor8lgwkOfld5yjoovX38WKH/eMJS70L4USZ/P1gRT5SlWR/ymqyElZxynyDaTIkZlIyQ9LkZf3JEymzO2ky+WqR2mhj+hz0tagqyfPFbq6HHT1pBhdrZgz2Qw97LpcoTGiDnU3uEp/imLzb1JQ/ik8c9JOSeXj1buBZ5rvGY0US+A/SMk/Eavky+W6D1Uln5Wtavj930PDPxqn4f8/0u/l/fT7j4bS7zMzh1buh4ah3P9l5ZDKfWmccve15sVqdjGf/2H9XoL63deSp2r3+v8B9T5VVe+pMepdQBNRNbdG8fud9Hsr1++vVvGteXQ5vryKdy8ZXL93/u/qd19wWaxyR/33v67f/0lIqq91WRzGfxyv3BN4/q3voX//48Q8usNGKivuN87/rn6vofstuIpfqar4mqcpfXBEy8fHNzA6Mrc4EhhBN25o5p8j/tdfb408el/Xckdlvj2J0ie5Q1oP7HnQmSnuK/rKzV2X5XbYJI/l4RzhxH7ZG3Fizza4MZddiYe3JwfjCMxCh12nuYEV8MwI8u78RP53sXA33U/pzMaDZocO5nooyR+0yXaHSlarPSn12ZhoU3SI9+xBQy8mHwy9BJscqL4Ch8/A1vNdoQnYEPAAG69s1UEFjaK5ySUx3/s9oY/y0VVr8L2V6aIsfqGDWJCPjm+Dmix23z/398oX4BU7RnbEf8r7j8yHp5qKS1zcHaW8jC7UnYVIx0t4vwq+dXMvEnsUSSo2j0qZJaR/FbQwo8INWOhRymyhL1+hyzo5eVv1mgUUG4i9PpPngIuZT+XJwrj7zdCXTzlr8TAi+8of9t6GUbk8ANHgZvvDh9g2GrQaY5quYn4vVOjO7UhqU0qL6hXix/jo1tL2BzGSiKPgPPj9lb6TXu6ow75SWkom062DcpUB3W6PGNgidA3Phf/nR7JptwVDI3zHtfCcATtPnEKeXt5q4K5WvtUHkcrkpXTfFHfFVqLjiwUy4d+znWh2fKz1BTGjYCp0lYaJQwt8vYYyK1uLh3PYLCNzZ7rY2myeN+xNUBM917L19K7IyLKWuNl6F88WdtXrOrRovIxfXbXib8vsK5B52L7O80daAB3HqvHkp8t30gTV5nc34q/uakqKHexuxL9dAGE3T6EdvYvv5jeIj/K7Gw28Sp7vLbMbLy8stJcfzbcXQgu0Vbqpe7XV1zAb7mjobpxLt1CZfa8hVrVy3ROof8rtaYay2zFR6Ww9a0AXsovD7AagPQB1wVJtBPDwmPtB2/TciklKi/WM/M9ujgYP4MEFiIDqEVyExyzB9R2vFWysICjp7sh9x6rxV+dHoGq6G7AIzIoMvP4LofrgXHdjB/kf/4pu6JWYWf4UMk8U29kFMMR8ju5JO3Qa4grAJaB6LqaTNQBWjrQcq0au7W50Re+mRIwiVrpf08ELB8dHN9WjRqLaOlFt22tR5K2MQ96qhUNjLJtjbH4Mxrob8EgpIuJY9W5CgQB+9yDAnybgO8gHn0q3K1Vt0xGlkg0FZXez9RkqHvIADXkcDc7txHXL2KYMvstcwmYYWV5+gYdtwqN2bk/IAFV6prK1GSpDL4NZFnKGng9Y5B1TJ0VGxPBc3tMKlrUC7WmoAgheKXj7fnxzpAXvOzhWncZhOo8wNeIPF9QsVDmc8yUShNLIN+K/R4LHiOU/uBzL37mTWD67u9HE86evozsgOdfHU3T0TvL5QlUL7w0YweyBesfy7eURyUiLkYwjO0ipQ4vFxJqZnMCugWywFWvWcTZYIthgp5AhPPBMlCn7KSb2zdGzOuQID6eDC4jgZnl5BUuxJI/oIDiisUbLc0PHMFFGlInyoQmU5MeK3eJ+YpcRFbtlUB1KCmPETowgJrVuwKRW8EnNFZNawi1xb3djPaHjRSGp2EnncVjOuhvoZtdq1OQSqNtj1fU8X31ed8MOoZGOnT+yt7sRDzl/8FV3I11HiCoXb/QD3ge7AQzMPChySfmkx7OvBv6A58Ul8LAkgKnZ9wHLLAHuub+zV1AC9T2xB5DCvh0F16YKLnJOiaiGNCdiQ7VL29RgVHfjCkGxHVxwZ3bTvDlg3SNq/mg2HdvTTQqpe0QF/TqyD7lyM0F7nOoSRFAL9dIHe/Etnlr27TiMpzq8y1gFPnRXo4JleZmK+Z7uJztwn6I8Rn+6q5HFpnXfZ+iuRgbqvs8UyMvkE2Q1fx1D63karuekbNhL2J1vlUHjvYpNTYXy+qUjwu9jQdkZzFT8yYL+DtWl4SVLYuP5ceF8c0yyRhPPzpjShXc2horO9YVZE+VbvOC9lh0IZWNBrh7vbqRE/fpAIxmQOS4oMrmAX12hzHv4pnkh/JyLxXgXsjt0s1o8l+WUU3GxweUJ/UAtLucXusCbq3k/vXn8DaV1ZHXCrMlANFDWRqg50hXKXU6ZHHkiTNyERGOb86JpW2Pjey+eARu0CZ9TugRYC76Boniw8D1rokAxr3Okd0AdigtTWBdEMBMnhmZeAwY/PYFGLA99nUXmnkupo/hL6GP4rTRgmNwT+myC+o7H3d//RIvy6FGq0WniCm2aBHXrME7vDv3bVKxr873liKLu/VyBOpsakiUWVprwx6pcbslMfpzCyVbGI8dt3tt54yegcaARy8BQ4YHiCOZX0Tssw6AJN+pDO1/WCuc9VJRdoZ1d3JtD0dB+4UrYH5gwfua127hiZJV4sZG8tRIPvz5+dicee8UU7CZ1f1qNEVBh0fKAK2u0GqKGbI/zBYw5+JrsBjoRk77MbpLXNKBHUYRqn/scj3lhGvuwXDUD17CGqPGrNNIBhZD3eQxJ0F70LX0BXS5RaLeFpr6q1ZzJNZi81xYodYh8tzgv0oDY94QeQdjnGDhh3K6QcgdQ43AJ/13gAllJC908RYdXazXgBIvkx1r5YQhPQYkrtHwcospB5yE+xt169VuAMyeF5BgxhrprqH6Hh+OiW4ccqwjHsRKDstwS/HzE2UO+j7RaMl3Z2idHYuiKogB11Cl1x6hEMb9LnTa8I4JXXZghPDs+iOVvAe4ma6KrAj//OvoibieOeu3mD/b06LsPH/mCx6bY2no8I1/dS6bWY/hch4EstqkKnxsoSrX2HV4Hn9d38Dqoz9YeHomqFmODBd3V+LFKyTEqY/vBXNXhfuz/AmFiCOYK7dnCQ136bwl1WXhoa3y+3SpCXRT64qEu3yoTmEcTYA61uQa7qSYnr3aOpWb2PbUl42qKZ7LEQI6DrcfD/1yCpBqKvM5OYpvK8VYxfrK2AA8s8NM4ma1HPAdmp7JNx7FyLZ6PldY/jXVqvNQkLf7VszGvMsSrNXiAnBXbPIGcTLb+rZEq75a4ArOzQ+NOajEyF8ix46XKetixF+Fdtlq56klCP3VRgSdyAzmFQLXr2P7Qe/8VDmMi/joe1cPs9QYlJx+vOxD18SRzoLqCE3ocNPnp59ikbFG0+koX3XUNu2Chdw7cRXrlxM8vAgX2OeuQoyfX2eBfrwNvr5gD5aovwAS7M3Q5eCp3YePi0O9549j3pA8KCyIHGFK6StLb5CqkJt3tg9c=
*/