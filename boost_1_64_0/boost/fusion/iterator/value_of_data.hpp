/*=============================================================================
    Copyright (c) 2009 Christopher Schmidt

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_FUSION_ITERATOR_VALUE_OF_DATA_HPP
#define BOOST_FUSION_ITERATOR_VALUE_OF_DATA_HPP

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/support/tag_of.hpp>

namespace boost { namespace fusion
{
    struct iterator_facade_tag;

    namespace extension
    {
        template <typename>
        struct value_of_data_impl;

        template <>
        struct value_of_data_impl<iterator_facade_tag>
        {
            template <typename It>
            struct apply
              : It::template value_of_data<It>
            {};
        };
    }

    namespace result_of
    {
        template <typename It>
        struct value_of_data
          : extension::value_of_data_impl<typename traits::tag_of<It>::type>::
                template apply<It>
        {};
    }
}}

#endif

/* value_of_data.hpp
+rzXsjdr/1Nj7k+7Bn+/e2894scYnZ6VvvE2lhNXv9Zuv9L+H3K+X6eP/t6cw32RlLXSM3cr08/Vx8vc+2h1b9G5qqqcxderR+1TPEncmhsUpZ34k7HgUfF9lfr5klh/QNo7E+6jitefLLeDedzfzQ1c61S9nz5LXU4bL8w1Ygfj7nGIu1H3ku81Rh9yrvS/z8OrEsYS+98gD6do25vEmv06HjbWf176EfXweeNuzPxZvIWfOd8tl3uH9vrqCusamo8vGUP/6lrO9X6H9i+fsNo93Ub3uSLu+cv3+cqoz5U7jVHGxM4Vzisz7kW6J1K/33uDrge/7pr100frT+rmteYdzpO508WbY7XviLveV99TzulP2qKdxNN01P89cjxjcTG7XN/aR8zH6j7T/d4G9zPEtnZv32K+975VxiHXAqvl+6BrSNc9HTetV9/uKe6PyqNrh33OC39wnRHVtmc5Dx6v//Xp0+K1UDeWlMW/a9OYMaX9OG3s+jz2hxXaT1zvEOfX6Ds96v85+lIt4nxlXNzmfsrPj3KvzRj8gPpQvnbX/Qnp5a7X3hPy8GP99EnmhJcsx4a5XJfrwi3K3+Baw3VC2py6bq3EzrJ5hTUbi+5DZPPy63v07eaqdfWfsU/ndcr2Jef57yr7B7X/I9q212cl4iLIV+o1+qr77yljbafzQXij8dg9tLLP/svL9fOuHT5n9dp65zt5yonB2Hb5cD8kO6j9C9qiQx3d6JructeZowlrDTpvDmhv8832l7tmvFLduW+UeCDicz6x+nP9obp8DhXPC9IUwznt29kpBr2fHlWvrk+zOf3qYvFUEQsX6hdvFPt3xd27VrdflP4RxtE9zsnXOrZ+nM3rk8+Rnznt17YtJK4URz9V71/W5xakfcBxu40BxzpfLDkH3eL64FtRvyNR1jHX5ce6LvmDuvEd2KK5ZfV2j58yB/2Ke043OQeZc6aPbNI2a13bJIy9y/d2xKU5Rdr1f+6F5hT6f3E5DwvGKXFY7jJfuk5e3QdNPaYfmXvU73Af82plSqtHihXjzh/0Ie91Doq7fcr8eMTY6jhvdq5Oi3VlSzz5v+ydZ3xb1RXAbxInZDiJsp39MtlBcQaBMpThgCFDJA6EMjxlx8S2FFnOYLSiBQotULEJhKBA2AkVlJaVgBgttIyKEWYABTLYFWUUykj/z7rv3vskmX7sF/zDXOud8+499+xz7tML+yTO+vZB97gvwZ7ixFixkHxlLvEijg3QE0ycaZHbkxf8gMzbwL2OPKrzeOpBznLrxnNWU0T9wX38Rsndo3PJO8iVU+SY0cHwnesWvwny9xB6kSBn90+A7gewN/DEPHiDrvks/EACn7MHfX4c//QdPuZxat1BxCn0IEaNkuDfmkluGoYPHox/6ItOEV8e4rpdu2JXvqF9yG+INUdB805iMjae+Bh+fcp7+a+lBjidvd1O/xQZijf60rfBNk6y0CH6BvhtH/ckiQmeP8LvD/sJ8Qo+GrnGbylB75ivYhgxlThtn4UNtMjB6I1Dk+ci+kV2PY59p0ZC62XwiXutPfgKcvLEbdhlN/ovvwP/TOz4PezraXgxAJlExuH74e+Z2PWV+PByfOxK/A05mdhOLT1sNDwfIXx16JZ9zhVH/ztjp3dbwInl2EXmVPS2iH9L6p4Seg7E4CHEwNXoBPPEg9gxtKauGCm832LPtk49i9wfR09XWMh3PO+kxadiK1YMm9iDf6A/kLiJGATMM6CEeTtho+jnbOrBwChoYb/UwNELsN9yeBIhDuCrMqOR+aPoHLVNaDQ5d3gEtoreL8P3r/XQByAevMr6G5mfnoBIEUc34Cv6EUPJNT074e213H8=
*/