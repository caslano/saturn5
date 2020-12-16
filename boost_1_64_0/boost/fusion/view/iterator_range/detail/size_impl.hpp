/*=============================================================================
    Copyright (c) 2011 Eric Niebler

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#if !defined(BOOST_FUSION_ITERATOR_RANGE_SIZE_IMPL_HPP_INCLUDED)
#define BOOST_FUSION_ITERATOR_RANGE_SIZE_IMPL_HPP_INCLUDED

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/iterator/distance.hpp>

namespace boost { namespace fusion
{
    struct iterator_range_tag;

    namespace extension
    {
        template <typename Tag>
        struct size_impl;

        template <>
        struct size_impl<iterator_range_tag>
        {
            template <typename Seq>
            struct apply
              : result_of::distance<
                    typename Seq::begin_type,
                    typename Seq::end_type
                >
            {};
        };
    }
}}

#endif


/* size_impl.hpp
Z0zb3dOLqJKovz+m+KL087hMPFbbacSjDWzoRqr8SBUqZ8aPOFiWeup4Etrh2u4r+xtUNxZCqhtJknEvKg0rxpKuWF6Jvo8hbQeeeGkmgoxdB6YqZrhxe6rNGo6zkw2+NCpA84MQ+XDeSPmSBl+YFEXsZxnlw3KiLbxM6xbJtOS+J03dMDpbY04zpDx+yv2gTGMGLagH8xLufLhr00b5BJe554ukikizZMwBeILt7eFImdz3eX/YvK+c+Typ1yzmuup0AWjrQuKTA3bbV0XOINgfYRjh2jRs+DBDOcuozNhabwNrt7QFQwZDY+Odql8S3oyFRa70UGNrV4f1fMq4eL16b1f/lQQSxrOqyD1XKnMpQMkCmJkBfrBG79QuRI19XuHzMFQBq9/gmp4bbd+thozcE1mU+cZ70ozwpZ1d+KVH7QBeMBzZ8YG2JaL6EPA8VZlkeu7j5I93eS3fp10+xZRfKB4HMLfoD7UnXP/6er+/0d9AvsieP7p8QcBkIqK8iFm9rQqXmTfMaw/2PUNTeh3XYHdv3HfWaX+P6LwoD/0C+tpjlVIswcJjbDpsjHfI8B2/kzH144vKuMijRFnekeVdHwy3+pBgbtGMWm1/Kaa6LeMs5VHJGazT+uuVCN2L9XNolh/Xxtfjxj5Y6flpGvqUH7WW6M4twpuyOMijNI88zQsTjcEYNQZur4+u9sbrqDsM76ESGYUx3FHsFY4M+MjXfWC8fvb218eTTsW1VUx0KJCBF/nSqwKdmPxHrbXjbxt1l2BkvVQJYNrTegBnQZD7rn4IpLd3Ba8RbvjWRie0/krEnh/GnA1g7n6lt22eX7SDdnN3D1qgtW92Nmne9+UiytJ0IsMORMO5h/swScMvFgx2kHKHb30LNAaaas8qzXlcDyVk3OQ8TxJfZcjaLCvG9kvo+YcIvdgrc+QDk2Y3BhmuzxOqnwmMbi8X3oRpcNXp6Naa5QuN9in9iJdeJJCfajb6W3+X8CUsy8sk46GT7w78Yc54lsyZXsXPUDca/Pp0rhQx4R9pPVwic1CG33xB78mEQRZzTzrscJpZ8fTQ91XQPg1EoiQvE8pEyot6dFLQM4g89r2ER8hKBrATTyMRtH/SNChV5uUOo4mEr//W27nRGr9bohFzICjKhOdBk38Ef9FmaNyHMWW3k5jzHq9onIf4cVyqyCnHEKYH2M4D3NtrtFmWizwvfGyzqn90P2Hp0fZ9s8Ebge0O/SxGXm24UT+ofv240W7cT70wj4sJ72v6e2A5qvve2O5XffvtEI2zqjItVKRSZtW5snjwiMtg0BiQ48jqS0pjWaS+iosiUSjDMV5GBvwdv6PuG0YptcG5p6KSq4jZF4fBjkFZrCXTRk1b9k1bIIzPkdI68TjzyjLzHDk4icG5RNPGpHTfW/m8CHwxEQEf6UFjbngrbexrJFEQCJVOmMwlbvM1b9rCT6eNPSVfZoWSvsMLdws2B9bAYP8TPsFC5cfS82Lkw3ke3k4w/Nj/aWPfMgmFL4Sa8FdLsfrD33fsuIf2IqP1ToMginmUODL6mns8mdKObP4nM6o7JYdeF1GGvNjdOgIYGQSoN4rIUKyQMpZx6rTB/g4Y2L1Rb3tqr+McJGvYPR0OKAm4I2e8edbdTexs435HRvQl9NI0D8McWbHc7jl+RuNypFFQlkIwmJqOD1pDfCFr2El9suwXPqtUa2cy1ImejW0db2eNdbcss5yn0vBPX354+C1q5F3EWRrmvmd4D16/jPFbJGnskszzgzxmdk60BM7N6EOF940kXe+WaeRFaZEgF+gWVHjDzJLW+pgnflca/Nq5RYlYsatWFYx9QwVptteWbIzpNEt9Py+Qv1o=
*/