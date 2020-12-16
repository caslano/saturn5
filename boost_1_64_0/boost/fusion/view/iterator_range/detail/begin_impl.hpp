/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_BEGIN_IMPL_05062005_1226)
#define FUSION_BEGIN_IMPL_05062005_1226

#include <boost/fusion/support/config.hpp>

namespace boost { namespace fusion
{
    struct iterator_range_tag;

    namespace extension
    {
        template <typename Tag>
        struct begin_impl;

        template <>
        struct begin_impl<iterator_range_tag>
        {
            template <typename Sequence>
            struct apply
            {
                typedef typename Sequence::begin_type type;

                BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
                static type
                call(Sequence& s)
                {
                    return s.first;
                }
            };
        };
    }
}}

#endif



/* begin_impl.hpp
/pmd4HRD6Wh7p7q9MSyr1250C8GJ7xDFWv91jPM8jW5kjVDG1jzFWD913Gc/AnRzLjOl7A7urwYHU7DpOJyXvfaoxpmc1tfcmLOvJP6hIvXzKPAytg5x1VTjYgTeY3d5zhVZmURREjITiGMF49+gPynkSmOkB0mR+HkozM0LMLHwTlpPB/tq5Pcvm98tkh+P9DuqnmJQFwnmebxV57dj6/RRWqeCeyKMlWArwfKL1Gp1ZWylYsIYM51/6HUiQRgNwZigf2/R7drmRYX1nXTzDQpW8jRIvUOEmtk5hW+L/FDf/34FyKN5tu7p/1j3pdGjpe5wrb9YzdyNSNQReJMHMdcWK6oJJDe4dqW/45yrzwOO5tdav/25jSF+HRtHWnSyD/FtTQeNWB8t2YJAiSd27psD185loYoyxQvd1xhICvXwtouVLPH9KE+ygtWB4UCjKP6XA/o+rh8Emb6O7YeLpqTNffk/E7zK0lSmKddl2Ua9c2OV/nNA9vH9KFZe7LHh3ib9xndeQd9zUnmaZHECBcl4RIuC385jr6DrjjQRXuYXh/124j2iy1taHlbd0avKZt+u6VgiRNB7RKccGU0fno0ZQif+aT+iNOKfdnJW0zBvlIy+Qy4dJdP4Q5ROfUO2DZ2OGRoLok3vDq4h/XtHXPorNzYNwlnrHwW6sd1YP+SFfS2kYfmcNju+AHRjz9u870Ua5cU3+bfcc5cgk2lUKF/r93SdeuIWnY8VcRhw79BhCVCnbl6pdYooDH3z5iTS6Z0ZNkNoZN35BUKje54Ls5qGfWU6AmNwt2knq0grTkyLOcDYvqoaFGnjeaBV7Y00fGPuCr0jEceln0oZMpyGByEE9Gqeef3ryfXc6dam5p8OrqdPHcCadv3mHbC2lZ/szJ+eMR2Lm3F43nAn7ABlQuYH45oxFLc01rTndLyLXZgDrG7fg7E4f3mvwe6MoLp6AoM296mbbpz6MAnALuYR2x017s+edHHPlDJJpRfoLwVOiid9e9bF+kLHXozKLJWTvg0L84ELuQki0rzbM3T59RU1qUoVSAaLhGt6be9k2cW7Ry5PyaQfB0UhJ1k6GXVtLL7bP9NzkgMKVXVMaLE3D8JilBQH+3PA0j6keEfuiV8AFvtwOtbOsZSRS2pE5lidNt2qLLcybrfLZnKx9MtYHkq34+6bGziW2mWtB97TbSylO2LRvE3iKvUJnqB03ILXAeYAaeY89g1AJ9zVWMF34J5+x/4DrD0buSN2YNe0GN/gYCz1eXwvwWLOZH44P9fCkPnhdULHXLA8P9b0O+qeI2sesbSv7TzgCNC1LvwXsj6IWCoLzws2Gm/l+HHkSe/Q8y93H+JpJr9q8wu2vjAv1chL5DLgXP5PZ0hPrfKqLBBk5sal+em6a0NTpRI/lZxBTs9szRkeRMqWs1AWMZd58b+U7SmdHvplNv22rs8CHcreo3S0/2de4pZdyZSrSJTs5MnGW0e/XKdvMKRJKqEPD1vsiV+Dab/eNL9dLPt4BjHOWQKJzwd0rNtUGZ9ADJGB9b/u1uu0SALpKxEw2Gii7yO8luBkznOv5AWDh60ad2BdXMFCX4jYi5nZnNan5Mjg6MStdaoTZay83MsPHcQLY9itaXlulmhGJ3YCfp7k3A+ALRYL7o9rrwC8BzDTxBIcyvzqLMWN7iDz/XNNLMGR9zWfROsyGDtt99W1xlj3VSGK9NCbBq5deaKxiW27crORl58HmYyCQ/vgufvOTzB5efvjXWpb0I9oxmIadPxeAN2cO2BTgu5Ozk/Gbfpwt3oiBuuVrDV8N7mI8zg8tJ+F/gafBf2rTsJHVWTTOv0CpJv7TysXlCqXV5sxBB6v3yQ=
*/