/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman
    Copyright (c) 2007

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_COUNT_09162005_0150)
#define BOOST_FUSION_COUNT_09162005_0150

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/algorithm/query/count_if.hpp>
#include <boost/fusion/algorithm/query/detail/count.hpp>
#include <boost/fusion/support/is_sequence.hpp>
#include <boost/utility/enable_if.hpp>

namespace boost { namespace fusion
{
    namespace result_of
    {
        template <typename Sequence, typename F>
        struct count
        {
            typedef int type;
        };
    }

    template <typename Sequence, typename T>
    BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline typename
        enable_if<
            traits::is_sequence<Sequence>
          , int
        >::type
    count(Sequence const& seq, T const& x)
    {
        detail::count_compare<T> f(x);
        return fusion::count_if(seq, f);
    }
}}

#endif


/* count.hpp
kXWWX4PMPfFfmnciYf2/Y+6J+ph3Imt9/c898XfzU+pz/ol/Yu6JY23eiWSueWbKcspaSiVlL+UIJWiRnymBkkYpotxIeZCynXKAcoTS5nzm+KCkUIopq8/35cP4Ft/iW3zL0V78KbOOcvy/IHuBEv7/W7H/DhLHj2tki9VPSByfXjv9M/eaa+cG2MAPpzLt/5d4vj0XIEe9Di/nfqrkEMQ1Vv0/eaklF2Cow7wCK3VyAZ5X7oOvV34jqRvgbT7ADQO08wo0a6wf66x8VFufNzkBzRobzytg1skJ2Mo+lunsozd5AZHW8cM6eQHbotkn9fa9yg3Y2lIbG0/QyQ14gXpMj6nq8To/gLo0eRsb/PSPU5y6Lq/i0s0aqY6Rqr4T/bXH6EXlPFTX53Fs2rrdlf7a2OR2tlvymDo2ybbdbtfaX3vCvY9LWs/Fvk207XmV9lQ5t0fOR2+O48t1iJdG2sb9a+OBN/H+Dd5gjYd530+cV0axQHWfBGjrfo19ybDVXfc+ucEwHqmOV9VIG9LkXtIUihKvqrJclwpy82f9o/GqYNu+KE1Rz9me2lQ7prqKN1L5BtWc7fEpKRNGDpmUkmgbVu3BnO1/Z/xwfcW/9ONrRvEvo3iW93Gx/1s8Sz/O+M/FudrGKH9fv7Xtin0ntexy6ZV3r0tacrp/3eNcyeuNxw/HON4/f9R4/HCU4/1m2V5Hd9tzUW+CfT0uDsbrDbGvx2ewcfvi7Ovx2Sntc7O9EllvoJv1qlTrGe2vfGZgHzfby9Csp91eqkmuwXJtNjvNed1V7td3w94Yin0xDIdgDxyLPXEC9sYpGG5rh1wn5fpZrY4b8Dng+fjFtRdwP4jyFSXwQj/VfXPumXM/ys2Yxvt84xp94xr/Yu9s4KqszgB+FXKmZoiK+FFiWmpqYn6BaUKKYqISoGFZgAKCIlz5UFRMKjUtLTJzWlZUllrOsWZlzRY1a5auqGy1zSaV29pmi8rKNdv2f+997nvfT+69gG377b6/Hv7d67nvec5zPt6P55znNP+98dH/4nWN5Sv8W9uYtMu/9Y2NrW0cQB9MQgqQDcgu5CBSj5xBIleGOGKQNKQU2bAy+L42eASP4BE8gkfwCB7BI3gEj+ARPIJH8PhvPr6P9f/OsrmEgVamADRv/b9nDkDDv87x+OiTZ141NWG224XvmgOQ0015N9nG8O/ixhc//mDNmv5MCz/+k4r/dIf4T70nUdzDfvvPenU2+/BPSF7jJK8YZA95VZny8i+WsvgmJS9MrImFXeNdo6XTIU987ltEh7tFh3pLHaJ9rtsTX5xJh2idDvq14jHyuqhC3hevQPaiQ/VjljpksB111iKHP/5y1tHDBS5dnM6FrlXzspbeu7ZXXYsXCUvbSFrNmsEo2NW9Fj9LsyZUykhrNth0j53P/3FTefJL/SqH7PngsI/X0NbC7/9jpd2a88Rr6dvvqz13rZx7PCfqBsfApxTfv/ncJTl+7PMQztrrvTvVtddFxZr1njWxun0SpM04aUjSjsTuUm/8LrbTV249HD+NNezxIL74Otmv8jDyNGnCdlnpLe3KD5+4Xg/q3xQzOouxje90Pmxn6TJnjuq/Dmlj8l/LulSG0nnUuZSf38p3NEhDv+nSxlvn5yAXItuVuQa79bEnZMDNmJtfWlJa7Lu9Sdx/y7gSJyTP3UgvWaf01UW0s93qvIuJqfFi1gDW+X55UdPW3Q+Ab6ljjYy33nX30n/17Ugfm99cnt44w6KfUMuTMEGKE8i65Qsubnp53m1CeTzzTyrbmstzQzfa/JOe8gReN9d3a3pZPHqyClt09/SbcudCc/l0dZN8rrks/2DxW4O3LClNaWs=
*/