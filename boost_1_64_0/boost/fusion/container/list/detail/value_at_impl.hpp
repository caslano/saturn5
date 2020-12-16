/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_VALUE_AT_IMPL_07172005_0952)
#define FUSION_VALUE_AT_IMPL_07172005_0952

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/support/detail/access.hpp>
#include <boost/type_traits/is_const.hpp>
#include <boost/mpl/eval_if.hpp>
#include <boost/mpl/bool.hpp>

namespace boost { namespace fusion
{
    struct cons_tag;

    namespace extension
    {
        template <typename Tag>
        struct value_at_impl;

        template <>
        struct value_at_impl<cons_tag>
        {
            template <typename Sequence, typename N>
            struct apply
            {
                typedef typename
                    mpl::eval_if<
                        mpl::bool_<N::value == 0>
                      , mpl::identity<typename Sequence::car_type>
                      , apply<typename Sequence::cdr_type, mpl::int_<N::value-1> >
                    >::type
                type;
            };
        };
    }
}}

#endif

/* value_at_impl.hpp
yyQfxZKPnNWN8uE9491d4S4rb748ZWzIkKdEf55Um+oC2DSsq7xTyvn4w+BI4m0x21TqWaAzqgXl3G3vqDu1cSRT268olXEfXdnnl5UWe8vvYG88x2TTPuPrxNanpR0+howjbvWdRlvzy9xUXfPfxz0NNrG+xVDHhZL2Xt7vQDepO0m72Jd2baO0+c5VtLjOtLTJ90teXY5MU75XStp7Id2UuMgU7gm/y5j2LHdFrC/foMnvX/cmvu895DwAp+T1OCSL9FIs0nOOTmu2nC2ee4Z91hdLepmS3kRkKunVWaY3ZWRL6ra5NLdJmlMlzQzkGNKMXWOR5phUJ/9ud5qe4Mb5nEaaNVZpZnZMPneXvfnPlGfOqcixpBlyt0WaBcW5ea0Yx9a3HxnHlj3h/fvBx8Ik1bZSnmTGdlYttiVLeSRKO6trbNvgtrYz33P7lX2157ahfHrtYrJB2l7I2sY2tKft+ex4OYAdNWY7pD3mWNjRnvbos+O1AHb029Vkh7TRWgs72tNGfXa8ZLJjrNhRL3aMk3Y7Cjkuij/3WNhRUVSuHE5S6nK7PKWFJRXtsClNm8fo8VQ0/t2fBwx2unbjDyFe7IxBZij11thOzsHJz51bBAtnucsrnCWFruZ/2+U71MjORM0/5EGPsb9ULzbtIb8Xu0t/rcZoE13Dtv9WjJK0ZqBcCZOkvYyXtGpNaRUXlpfT2W5VvyZQP/Hbe6z7iRvElm8k758jx3NP+L1GW0rclS16xkm5S/s09eVIQAmLkL5IFTIAOzPuM6blKaM9enPdqr7xFSFGf2CiqRxCpf1KX6XE5S6p0Pep+nvvxWHnLbPVXrscJ5jPEtmTP4TTJR8nST4c6yzzgW8ut8L9D+bjuHXW+QjfyzofNdb5mDuzqDDvn6yP3wLkY3f5Np6ChCKViJN7Uu43nfGTO89t7o/3aiYf4RbPkX6azcU8Pr3nskRSlpuQCK7nKOlKfGB+/9Hu747dh3CtWnd/V4v79XldLnmdJs+OTN97rDmv7ry5ZYUVC9QXzFbUmfm5MegBeW6Y+tfRyl95dvVERiO53JPxgMmOdvZD0rR+CJcs3ymNv8UbLOzKi0Kv2a4O6Jsotr3cCttc+zS2za30mx402dYB/RXFttdaYZtj38a2zcI2j9m2DujDKLa91ALbfP2FVWLbMUgYMhkpxLZ6s21W/ZpWtH2L/oLMuaBbo8uPnLOknOBkKMPYHvwhxMlzaKDvObS+kZ1OZdSqNc9SC9t041/G52G92HEEEib2zMaOqgB2OMsrytprS6RaTijyl5PYRymZ3mEy9ms8NvZhH+w221d4UpvLSHl29XjI+tm1VdLPQpQLRyN77Us9PWRIXy2b1sxR8teHZZvWxi9eUNu+W/stmaF+Vn6VCgx2zg/lD2GZlNNSKadak51zPZzNld+276PV+M1QGb9J7MkfGbcJRwqQYuWZ8LCaPqPITkUJY7klg9mupKyojXVlbM+lHmBqQ7llswZrzw7GeOVanLeeN3rtcbxH2ejHn7rLj/tR/M9wOAaWYr/jEfV+1Xa+A62uZ7Pt2RZ1n2PxnSgwfCes20OiRXsYJflZIfkZIM/oQ5E55KemTs1P+WxndkJsknNkVlbm+FFTs8Y4PaUeGdhrol7CDfVy6T6qzbPVPXPEnmj1mqIof25Jnrw/iE1p+/OH4JI+pBMpx6YGr01zS8ppnblFs1rzPW5vv9Fb7rMpeP95cpsZm74pQpk/dP1dVz668dk5W0/eZ12PAd1/mRhoX5qOW/dmPc+s4+bJhaj2v5Fx9ZjNtxYNqY6uf/GbP5YeFmjeW8fNq+vsdXIdNY9tR1k/d7E6761Lwod/5Hw7sHI=
*/