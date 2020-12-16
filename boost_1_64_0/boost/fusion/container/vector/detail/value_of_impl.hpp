/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_VALUE_OF_IMPL_05052005_1128)
#define FUSION_VALUE_OF_IMPL_05052005_1128

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/container/vector/detail/value_at_impl.hpp>

namespace boost { namespace fusion
{
    struct vector_iterator_tag;

    namespace extension
    {
        template <typename Tag>
        struct value_of_impl;

        template <>
        struct value_of_impl<vector_iterator_tag>
        {
            template <typename Iterator>
            struct apply
            {
                typedef typename Iterator::vector vector;
                typedef typename Iterator::index index;
                typedef typename value_at_impl<vector_tag>::template apply<vector, index>::type type;
            };
        };
    }
}}

#endif

/* value_of_impl.hpp
wwTcg6PwOUzEV/BqjKI+MwYTMQnH4rU4E6/DPLwei3Ac/hXH46eYgl/gRGxLuUzCDjgFg/AGLFPqS/f6mkKJJMJKlBDUB35x3elg2P9P/el/re6083dUf/JUd9p9r+//Vf1pP/t74l6jnmRMxmRMxvR7n36D/n+pz9ZNG8CflP5/aQMIlN/Ou6Xv7DHiVequlW86tQFk5KWnV9s3XFXHfcmhjkzdVd3WatlWKuFHTCReY97DbzltKyd9XvVtDfrb0q4rSJY+7xDlmm3sjK8zb9IRp23RxxyRmpaeV6PnGirtGzHvSPtGXp7U/x3zoN2Lb29zJc2+ZrkXn6Tl0lmcNSOH90L6pqn/S7qFRIdxFKTLOvgHSQ9Dq0nmlyaC9k590fau/FS6Z6vWZXbcNk0Stn1VnwMvebf1zGblp1oK1P7UIJe+3vbSPkGa5EsyIOuLdc2DtkpbP/o6L8rffr9g04i3tX70JOzdQlmOBaS9w/G9rJT3MkrGe4QTb3QxUal3ey/ZXH5Bel714xh0Pj9q280+W1nJmiQ/QyQvVuljHyx56U+8yTriPeYlNbdg+sz0+TUYW3GxPAXa2qLUVTmVTyvpd79F8rRC8lTsnifJTPV97jJ2wy0vCe55UT8rZfbPGKnSVif5K5X8tSMaEwHEEaXM/uaav1QOWOnVXt9ju5++S97ak+avtp0pq0nNykmdlW9yGXOyTy40mi5tJ1PwHaXN054XvgfsV3ZWWip7kZo5LT+zRvc8adB8bYXzcWGqVk6sSWs/vNFWRsqKtXuKdG1YlZbKt0nupe/S9imfA7lnxyyLfU65p4hzu6K8d5LGvA7HAdYp88kKHMsmlEJVpuHsSFuMx791YT3HbPsmw9Bsh8vUjKzCgtwalI2UhdvxMNPD8TDE6fhiP+4Eq8cdmT912swsi8PRRfYvyHEeZVFZNsxpne4LK8emcsoqxMc+ZuVrZX+1MuPYJOtkIZMcB2Oxf3MtnWbmaY7HbpaR7anHNKf26+NS1ovlfiULiGPKtXnvOpX1DL4TrKDm31etnOWzoT07IssieU9Sn4NjLwE+7jSSW+R77NbmLm3PntuS9duAPbW51t21d/pt4Z7aaGs/9ka/rdpT23bt75tT27bnumoj7zBXSZ/+TPrTL9y0vzi6z7vbX0w8M81zGzZZ4nshvwlxN3GQF41xssMYlBbYFdtjCHbGbhiG3XEk9sDpGIo3YU8swcvxMeyFZzDBJL8LMVW21xDjZHsBzOeH7bAndsAIDMTrsRNOdBgTtMRLfvvJb0Jlfb15bUVlypGxKLMxHHOxH86RfOfhGLTiDJyHOViI+bgQF+BNuAIX4S24hP8241LcistwB67E53E1HsQ1+DquxfewGCvxdvwUN+JXuBnP4b3YgLzfh354P7bAbdgNH8A+uB2H4w4cjQ/jFNyJFnwEM7AMc3EXrsXH8S7cjQ/ik/gCPoWHcQ++j3vxY9yHF/AZbEn5Posd8TnsjOXqGCj53QZRxEGXMVCfSx/GFxiOpxyWi5flBuss95Usdxr7479kuVyiWJa7RZZrghZZ7qws9w12x29lu+cxEr/HFPwBp+MFzMCfMR9Z8ZIlCrgC66E9v/L7Btvp5LcB8zXGhhiAjWS5CmKqLDfdy76c8u+HZLn98jk9gCH4EvbF1zARD+EEfB0n4V9xHr6Bi/EwLse38Y/4Dm7Bo3g/VuBRPIYV+B5+isfRi7z8HZvh+9geP8Su+A/shSdwCH6ME/ATnIKfyvtRaZLfEzhc9q+dPT/qGLu2OAI740jsiaPwSrxK9m8MzsAkzMHrsAjH4s14Pf4Bx2EJjscHMAUfwYl4ECfhIZyMR/AG/ART8Ts=
*/