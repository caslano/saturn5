/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_IS_VIEW_IMPL_09242011_1744)
#define BOOST_FUSION_IS_VIEW_IMPL_09242011_1744

#include <boost/fusion/support/config.hpp>
#include <boost/mpl/bool.hpp>

namespace boost { namespace fusion
{
    struct std_tuple_tag;

    namespace extension
    {
        template<typename Tag>
        struct is_view_impl;

        template<>
        struct is_view_impl<std_tuple_tag>
        {
            template<typename T>
            struct apply : mpl::false_ {};
        };
    }
}}

#endif

/* is_view_impl.hpp
X1cnudTfLyW59B9fTnM5w9XjQSVFGNembVw/cF2auzthrnfc9M08zG6MUxqKI1tojQbvq9V2s2HnajTX6a9qG5gUi0I6WdOeB8p3m6bs8mkTV61q9w58PWHTxd7ubwjDcLQx0ahV3bfZG3zu7ny40dPbWa0x08iwf/WmNMP8He4v1TayDI+e/1bEMpVs7K2Nbdzvnu9YRvkxRdyahgUlgeejxQZONaWId+/Nwjomw2R/i9OK1zffTufmoz0m947d6uly79htnr7c25t7u2MYMaI+fN/qXE84V+KUfAOk/Qdi151BmD90GkaYsP2R1fnGINJ+7DR559xhNWrTcGXO7E7NXHq4HH+imV2pWy1Wg5osY5/WT7VNVNa4TzS2QUli3lpzV/k5j3c5Jud3/MJpsnbgbqvx/ojiTjKK+x6n5/anKp9Cgz7jl5rr8kDa7nVcrrC17Fea2XoI9mvNUOa2fv9GWMJnOc9dKxt0GLxH1+myX/x+T9MNivnvLJd2ypUW/AHFp2emMlUEfH6r5cF35wed3mlVxsrmvzFvXvghyzE8tvl/mPToa6XXl/8hbeP68j+mudtn8ojj+HlMixwxX22Za6Os/9npWVPrj1rdtRHOx1+cPmMiiG7H4bNdPRtqgJT+x2Odns0R5xM+zw0n/Umrk1QMtnG+K+nuvKsRM+JZOqjGh08nuby/n0lyaV/PFnzp4qGBla6oSP+rp8se2L95uqxX+7vTj13Wv9iFRewfEZNx5j8jJt9s/uVYdDoJ8X8nufzW/0+SS5qfE76kf2TEbFiRfcMbbB4yyc+GEZP8PC9iMm5+fsFGl65YyVMVlFk606w8tHSYgme7jdZrJ3fAvWC9dvIbYGNnxynT485NQoZx56aBrs+92syw0WL8jYVjtv/eHHrRYqy2BTReYMTaC61mFhbbfaFbWm2iMZXR3gguw62gFy2JbjSnQ/dbbi3Qi8Bp4Sk9zHG82OozrSk7NtraaXnWrbeQJLbfxrK8ZpzTJO0lTssyu+93W9GQHrNEv9F0/dt2EUd6Ec9LwbFun/KwPTSeSKBMkL5DoQ/0qSO8sFeWdf/4LoS/Ixh6QApnJ9b0kV5k+3LoOuydobUSYe8Chtsc6LykXUk7hPhu/G971Bdpu0PDM6TtUWhDZuZkUM5FfIXWKjJW29PTZay2l9bl5CVie3vMvz92H8O82SgajzHbN2R6HyszzFDhMaR9v5Dh9+L+rFeW9pdGKrQE0T+34IAEt/k7MGbuHXgQWPG+mC2NkNjBlpXLOkpisyIm/dbsiEk/2Qe24vA5s+1dUtlaflfO0WwyM4MT47qipMmCnz9E2xRL+isN1x7mMuMbIGB/qNWmGs168RPNbAC0vj4sYk3S57GOLXEmfoR1uNYlXfTMEcz05b2UpiNZh4J7LqHp8ns1NJ1ty14TMERN7LXMsJOq3dF3lx+lGLoWeqZf6xPVWqfVzm0+5iumz9AbYF1fwYTeiJ8bFG6SRj96SC853bdfwDppuv4vVDo5CPEvUjolTi4/pDwNRVz6/aMDVhmn7QQmnTP07DEhNz+VGvkqYosDhoIktiRg+myi4YDp+6eWBswlBnkd8TiuzSt6YfBjkzxrWj4a8e44PQ5eTnB6HGkfC7jeQ7gsYHoP4XLF9Lel47Sex2W3IuCzVdmt9Fhcdq8LuC674yMmZXdCwHTZnRgwXXav91hcdhWPx2V3UpJL2VU9HpfduMfjsqsFXJddPWQou60My4jJXP2E/O2120nWaQMJAPXdq6DPVOvUlZr/8TuF3jo8xmys16YyPTkxm8I6uaedeaNgvLp6fTYUFNtN9bLjn/nGiu2m12/XZ/3fTNiZN+aavjk=
*/