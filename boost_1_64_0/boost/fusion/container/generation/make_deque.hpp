/*=============================================================================
    Copyright (c) 2001-2013 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_MAKE_DEQUE_01272013_1401)
#define FUSION_MAKE_DEQUE_01272013_1401

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/container/deque/deque.hpp>

#if !defined(BOOST_FUSION_HAS_VARIADIC_DEQUE)
# include <boost/fusion/container/generation/detail/pp_make_deque.hpp>
#else

///////////////////////////////////////////////////////////////////////////////
// C++11 variadic interface
///////////////////////////////////////////////////////////////////////////////

#include <boost/fusion/support/detail/as_fusion_element.hpp>

namespace boost { namespace fusion
{
    namespace result_of
    {
        template <typename ...T>
        struct make_deque
        {
            typedef deque<typename detail::as_fusion_element<T>::type...> type;
        };
    }

    template <typename ...T>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline deque<typename detail::as_fusion_element<T>::type...>
    make_deque(T const&... arg)
    {
        return deque<typename detail::as_fusion_element<T>::type...>(arg...);
    }
 }}

#endif
#endif


/* make_deque.hpp
Saj+/L+83//K+P+2JvVhUTVMyghWc5IySvhqmV+omZ+RnWYuYJ5SZzBR6TPg/Jtt3tmmjFGyzctKYzHbtiex3AKZl5Sak59tVecP4O9LbPMd4+Udz3krss1XRpVmpGRmzGDwM+tIPUXxQZd4Aayjzi9xzmfQsPo3e4yBVQeNYwwof8/HLba/q+WrLqEsq/69DX/fbvu78geKLsmarjzcLiNNzdM/OnB8M1xiHDhiF7x80LPYBc9qnr9YKDEA/FRMtUgZlKGlzDnOeCRXypgxsbY+Eya3fSZcxxCfkO3eIv0yEqRfxuyy3z6GWDteOLaG8Xhh02eXP164m+zjsIyVz6FKqhuOxUVK+R9wjBd2xHVYYrr0sx9no/1Z+x8ddn3WfpHBGPpigzH0JY6YD+xV5sUh1zzzlOtdxrM71s2zJmWkFdifyx/umJ+he07/rbb10vk37yleU2wpmUnKu+pq5ndxLEexZudYbaVaYax/7lTQPe9/Mq/VWAvDG9nyaIuxEMe5O+ij9m8JPUhZyLYSHM9kTM3PlXOhfQZkPRm//TfsitVwMsce8pnzfGjjVWyp5JwUa87Je19qzgmvq51wvOZNlmXLX6lBPIYdBrE59jjmqVEfTDJ/Nra1L5uUas7IVLdhMTiHkcqyHpzDNN05XGBwDuU6keVyJpvk3pfJPkvlnpqRywcATzPNkTwVKueiubK81XFeYzXn9WpeJ2qvC2UTsr79Wmok55IiVJ7NaZtfoD0utcgMr5Eyro/zNdXr/dBRicPhGltCuTZs4+2nq+fflBPq+szQNLleVss9okjuEbP3Vxjv79F9wb7dPbLduiRfUh3SDPLu/7Vzu+nTbGE0Kr1nKmXt5zj2VGuB7hm0cX7OfdWRtJrzEui6r4KcXJPH+9Jfw/7a61J3Hz8o++8i8UI6SmyT5E+d+8/O0UY3qfweK8/p1eVDrm03+UiurW6gu+QjWPJRpMmHJhce9fGrSj7s575M8tFD8tGVNJd8xGk+E5QTX5X91/T3fP8z66gbiGRn9fEaeSZxmaYcJC5IpXFwZP/OmBwyL0h3H76aeYFGnwGSt2DJW7mSN1m3oXw2DydvIeq1arsHuC+TQJc8DWus7CspnnVs7/Eh9j6HzGeflcaPNu6DWfWYFFV9xqtxX9Gq9/E0jlXhrg9p1Z/5a9wn9PeL+2wcu8RdzIuqx9qoaqyTVcOV+ZM65fZan9H+8zV3P1o3M+zUeZNJfdasfN9FP/2zZiV2gWIa1kKzJibAbFnvFllP2xd2nPSFTcQmeAu2wfHYDZMwAZMdY/bl+6u8d4J0Y/ZvluXSq8t3UPluqiw3VNkPKtNU2f5M7I23YyTOwqG4AONxISbiIkzBxfgQ/gOX4BJ8ApfiOlyGL+By3IkrcB8+igfwMTyCRfgFPiH5fRIv4FoMINPrMALX4xh8FnOwBGfiRnwEn8NVuAk34mZ8HZ/H9/BVvIZjLsWB+DqOwG1oxe14H76JxfgWvo478F+4E4/g23gc38FzuAsv4m7swYXwLvbB93Ai7sHJ+D4uwQ/wUdyHW3E/luIR/BzL8Gv8DJUf60fRF49ha/wcI/BLvBnL8UH8Ny7F0/gEfo8r8QwW4w/4LJ7DrXgR9+OvWI3rggtkdg1fwKuwOnbDGtgLfXAA1sTr0Q/HYG0ci3WQfRMPTb5jy3dv5XpT7v1p8husIct1xRbYF1viAOyII7E/3oTXYSoOwCwciPkYhTNwMC7DcbgLE/F9HI+fYCoexYn4LU7CHzEdfclcBl6Bk7EZZmILzMKOaMFQnIJ9MQ/NaMVMnI1z8Q5cinfiKrwHn8b5uAkfxJdwCb6LS/EjXIaHcDkexRV4Eh8=
*/