/*=============================================================================
    Copyright (c) 2012-2014 Kohei Takahashi

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_CONVERT_IMPL_10172012_0120)
#define BOOST_FUSION_CONVERT_IMPL_10172012_0120

#include <boost/tuple/tuple.hpp>
#include <boost/fusion/adapted/boost_tuple/detail/build_cons.hpp>
#include <boost/fusion/sequence/intrinsic/begin.hpp>
#include <boost/fusion/sequence/intrinsic/end.hpp>

namespace boost { namespace fusion
{
    struct boost_tuple_tag;

    namespace extension
    {
        template <typename T>
        struct convert_impl;

        template <>
        struct convert_impl<boost_tuple_tag>
        {
            template <typename Sequence>
            struct apply
            {
                typedef typename
                    detail::build_tuple_cons<
                        typename result_of::begin<Sequence>::type
                      , typename result_of::end<Sequence>::type
                    >
                build_tuple_cons;

                typedef typename build_tuple_cons::type type;

                BOOST_FUSION_GPU_ENABLED
                static type
                call(Sequence& seq)
                {
                    return build_tuple_cons::call(fusion::begin(seq), fusion::end(seq));
                }
            };
        };
    }
}}

#endif

/* convert_impl.hpp
arU2eJzU6Xg2a5J6XVO9u0ca8CQc1NMjTToOe/o80oyH4DukVcdh514eacd98IzeHjmmNcAnyCndCybO9UjGXsb7eMR6gUdq9Fn4+IUeacHT0HORR+zM8cECYuIheGt/j4zBg5d4ZDMpxFNwoJ/+6Dg8ZwB9U4eTSR4egctJPp6A+0kfPA07X+qRbNyAA0iu1gYnkhx9Fm4hBToflg+kz3gcVl1G/7XOQR7pPZie42FYejk913WuoIekROfDnDz6r7XBBKnRfa9k/GrOQudfw3xSp/Nh3xvooc4f7pE/ib1F/39VeMebqBkPw6tupbf67G3cmSC9Yjw4gjO6nXfEQ/BN0q5rwn0kg/E0PL+QvfEIXEKadQ78jDThSXiU1ONyp0cuJq26F5xIWvAIXE4a8AQ07qKHWicsJ/l4DNrv5ix0HI4fydnhCXjPKHqrNcB/RnO+On8Mdf2HM9V3gT3u5Uz1XWDxffQXj8PLQvRWx+ELpELfC/YeSz/xFEzcz3nh0Qd4J1KDB4o88gap1Pnwtgc5FzwM15FTeBIeIcdwecgjt5MWnQM/Jq26PvQ+TM+/473gk6RO94IfjqPn+r4TPPIyyWBOHHaYSC9wH7yTNOuacBap12fhh6RJa4B/kwbcKOYOkDzda5JHfn2UvuGxMOtM5j7gUXjdY5w7HoF9p9BHPAQzSzgXPAAPknzceNwjEVKoc570yKin6DOegj2e5ix0L/jKM/QdT8MrS+k5HoThafQZT8B/SZmu+SzrkDo8DBtJqa4JRz9Hz7U2uJJU6LPwvAj919rgl6RG94IfTaeHuMygBpK9j/mw/HnOQp+FP5JWnVPGXqRJfaZHLiTNuiaMkgY8Dh97gT6rwwMkgzXTsOsszlrfF04ip7RO+Eg558WcONxDTDz4ImvOps94Cp5fQZ/xCNw4hz7jvlf47SVl+iw8M8q76zic+yo9xP3z2H8+fdBnYYqU4rLAI/eTFh2Hn5JW3QveupB3wcPwd9Kka1Z55GZSj4fgfNKs+8KDpB2XRR7pRWp0Xzia1Oo6cDGp1vlwL6nD07Dra9wNnQ9HkzE6Hy4mxTof7iAFWhv8k+TjspjfClKEB+B4kodH4Elifq//et8j15McPAhzX+d88SisfIPe4inY6036jwfgBnJK94KjYjzDeBzuJhl4Gl69hHPUPsBfSYHutZTfSVKoe8Eb3uJddC+4muThCfgjycelxiNPkVI8BreSMl0fDnibs9N14DZSpOv/1yOLSIWuA9tIMS7v8B2RSp0PS0gdHoF7SLWuCQcs4yx0HO4h9ToOuyznvHA/vJU04CG4h7TisoK7R9p1fTiXtOBxeOFK7oaOw23kmNZZ65HhpFnXgc+SUzpfx0h2it7CoavoJx6Ec4mp43Dou5yLjsOpxI5H4bskR+fAjPfoOW7A8SQXj8DNJF/H44yTQh2Hy0genoD7yBg8rXNW039dH64lZbo+7LWGPuIBuIEU6Tgc9T79x+NwNynWdeBzdfRfx+FXpBqXD3gPUo/74YukBo/B/aROx9cyThp0HDaSWt0LniZNOmcd70Ha8RDcQJrxJHSt54x0HG4gx3QcniAtuLHBI/3JKX0X2Gmjh/8dMhy+QBr3sy/sUO+RJB6Cz2/iHfEk7PIR74X74b8J3gtPbOb3/BOPrMfj8BDJx2ULJAW6DoyTQl1HxxqoCQ/DwKceSeMR2Gsr8/AgTJE23PiM3xmyW9eB88gYrRPuJ0W4NHrkFlKsc+ACUqL1wGOkVNfZ5pEQKdO94L1f8PcT756Cs77kzjCeht9+xd/feGA7dzPJPdE1YSMR5qfhxh3Up/Ph1V9z/3QOfHinR4LMicM/yUjcaPY=
*/