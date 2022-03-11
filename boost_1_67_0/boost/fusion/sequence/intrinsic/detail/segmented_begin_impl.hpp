/*=============================================================================
    Copyright (c) 2011 Eric Niebler

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_SEGMENTED_BEGIN_IMPL_HPP_INCLUDED)
#define BOOST_FUSION_SEGMENTED_BEGIN_IMPL_HPP_INCLUDED

#include <boost/fusion/support/config.hpp>
#include <boost/type_traits/remove_const.hpp>
#include <boost/fusion/container/list/cons_fwd.hpp>
#include <boost/fusion/sequence/intrinsic_fwd.hpp>
#include <boost/fusion/support/is_segmented.hpp>
#include <boost/fusion/sequence/intrinsic/detail/segmented_end_impl.hpp>
#include <boost/fusion/support/detail/segmented_fold_until_impl.hpp>

namespace boost { namespace fusion
{
    template <typename First, typename Last>
    struct iterator_range;
}}

namespace boost { namespace fusion { namespace detail
{
    struct segmented_begin_fun
    {
        template <typename Sequence, typename State, typename Context>
        struct apply
        {
            typedef
                iterator_range<
                    typename fusion::result_of::begin<Sequence>::type
                  , typename fusion::result_of::end<Sequence>::type
                >
            range_type;

            typedef cons<range_type, Context> type;
            typedef mpl::false_ continue_type;

            BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
            static type call(Sequence& seq, State const&, Context const& context, segmented_begin_fun)
            {
                return type(range_type(fusion::begin(seq), fusion::end(seq)), context);
            }
        };
    };

    template <typename Sequence, typename Stack, bool IsSegmented = traits::is_segmented<Sequence>::type::value>
    struct segmented_begin_impl_aux
    {
        typedef
            segmented_end_impl<Sequence, Stack>
        end_impl;

        typedef
            segmented_fold_until_impl<
                Sequence
              , typename end_impl::type
              , Stack
              , segmented_begin_fun
            >
        fold_impl;

        typedef typename fold_impl::type type;

        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        static type call(Sequence& seq, Stack const& stack)
        {
            return fold_impl::call(seq, end_impl::call(seq, stack), stack, segmented_begin_fun());
        }
    };

    template <typename Sequence, typename Stack>
    struct segmented_begin_impl_aux<Sequence, Stack, false>
    {
        typedef typename result_of::begin<Sequence>::type  begin_type;
        typedef typename result_of::end<Sequence>::type    end_type;
        typedef iterator_range<begin_type, end_type>    pair_type;
        typedef cons<pair_type, Stack>                  type;

        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        static type call(Sequence& seq, Stack stack)
        {
            return type(pair_type(fusion::begin(seq), fusion::end(seq)), stack);
        }
    };

    template <typename Sequence, typename Stack>
    struct segmented_begin_impl
      : segmented_begin_impl_aux<Sequence, Stack>
    {};

}}}

#endif

/* segmented_begin_impl.hpp
H7Q654ljfjTAEvNNDvGSMIQfGeGR3s9oNJnPLv3cNUsTPUrWbezM6/Cpl9EjdLr/Y7YGDuH815egZFk6apYeVhbfiBsepwaA2IqyJZohiRg7cstNjoL0cj+fk3rxws77C0YR08A5uRDZuHiK7TElJU8/7ShlTz+BZXMVvapGvyD6JZjnUkj4bA7z6qTixm2kiqxCzrl+t88ayRhXE8B6nlG2pO6CROIHYseikupFz+v8f34CFni2VsVTXYKE3RE1HoGxK6mhNeMPM9Sm8B0U4L9F9J4yfmUz5wttibTp7Jj7BfOHKekgS0Zt3EajumMT5hzXSqYZ5TBXYwtS5vGOJgyLA2z386poh2s66EdP0j2hA5L6AHMem9T1UnuynWLpXHPeuPWt6HpvoLnufPTKJ7/8erW3eNwxiEvNI3eXWtJXM3uZCkIJni12ATwPbDWthaqRppZzasLs4CrOgAieFB8UKvDJ17JQHJQT1O0Y3w7rQnaIiMlO/v+gKUhQf/c98wG4PTER9rlYM0LsLg+QAZg8xAz/lX/io5HsymQdP7GJyTW+81smZiAn/CSzIo79siT8FhrU89jFciQA/aRzl/vdfQtvKlDv/4i0PHjD21fqdrD5iXXULe46ymyAv+qSzDFP7URwazBPBd6ydgWPLMsRN5al+dRf3dr7AfkTYb8ugtwoiI38l8AURVPf9KOXtTDiIMu5BGolbwQ0quKbY/MLO7AEbyny5kD25b8xS1bFDdcIohQB+KqNWWi5CNgBWSVBteg2CESZS6v+w3JJSpc6NxocDb+KuaADZ3c8H3Pid9aIRZLCjrrRCSC+iMPZX13CXlMuHu/+/oaU1J2G+oCog5OYJX3pXJ47vltWYd/UzTb8A9akKDS0mK3t3OP9wPzsqCBOu+KGJOWi+PKUnqN/HBzkNXP2wGwaq7AgZcKS6zVLV3W/y6WRayC7fmLLDwb3FIp7huzg5ioCFtlpnguPWjKHXF6txVr+wSKFc/QqD75XUK1FdbeNXjmJyHNGczGZW64VTstc0swjoqNp9HY6K55Fd5JQAn4fivghKWOAmpnGaERTCC3QOtPJYnpDw6ZAWOdvomuaYXYUACk4lIXC7zuFwassDrBxA4xlWXA2WgR+fPNNyWrEMwWyXImOGz2DdzOTgX1rHckTvRq8PuR1rif51goLi2CiJ0r6Rqqxy7WJMhGRsm/2BNg8QmEwVVNvxsBIPDKOTfUCkFHiOhIY5SWBHeYL3KBvVK0YCZplmDLTU6WgYC2Eyt3hLldqZ/7VsMi2PHS2yNYsYLrEpkyYNV4Rad0KnzTiwVKrjaZD4lYdNhH4SU+3k5wJHv2dPQNUnyy30gNX/VrccXerRMaAPRMgJ4c/+ev3SfbVpXC6MGODYm/SLxJ1LEo3QIL4kUaHLDoRlthjsE+GcvW4/184wExqzTqnqmGYn4L5GopMNzIWZRda6GpWD6BoBLJxVR9Xdb1dUdFK2HFS+BcyRd3+u/VLlYDIBDtLOl7A9xtBfyCJVkD75FlNCadwQ6oBxkIJvifVa+eJ1cZOnXq5r46QV2tmxrFu24MZpQg8DeoF0Lso27Zb5DSfqVRsPNIaIutH7CLEenmB7weVzFXdHCmq2Bm/VGqS93b8TyFfw+0c+whVfUNBlVIYU/qwC2/sv0iP2+ISO7lnX7SX3guTS564orYaUUG7LrTpvQHOxa7hlvlkeG/Qm8O4Spc3IH6CRAH5omT4xr0YUJRIV1Ahk516OyWdepVeluOTVCK5miA9557hij5dwsG69r3DKlcJ9NC+2gWcuS+0oj0BQ138UFax+F+cCGjLQT0y7PUY37LVflnY7AEErL3jnerbYs08oh3iQFNQj1zQf4HLtlpvFmZKCCyXPwas/161S4yt+AjilWJL6Wi8JgjDBVxlHn4Epu2EReN2rqL2BgRvRe+FWCvFHTHiicfi03WL/5MzDfoXRsfWwOYrtv9dc45mvPHX23zgpXsccj0cZe0DXVY6HT/aMxxfHmy279E0fszVCBaWGCw8PzW2dAdBF2lNh0MSlyk2JqXO0kz+GJQosGySVRZq2VuE2PzbtyX20srbFM9glkbS2baLw7gQNMaIdZMYMZMchMxX4CnOvHH4arFvEkLkIWZGL6ZYztY2nIO0YABqp2Qj9vlxUxQ4PShDDNnYrO3/9zg9qdjEWAFJbPhugqOVgPQIby18R86FO7EbHo/4CG/jbIlujkr4kr4Hw9QlnI8nJ2kWcFUnHPpAJfNw44/BGixY/QyimV4AicZyt1UiYf5Wznx2FgwLyIASqJJV1bLPwlPSlJCtqlmOHH2knJqhUbE6Ki2ktqVPJ8mvnKpxvENw2s+6glas+Nnh9XwyoQr2U3l03pbuzQeHQIsXGtWbmqSYmnhk1SAlWrJ4bIUZPJdhqjdF7zuYDdau0JiuyiWTUJe8vKQJ0Dxd4tNMpHU34SCNgat6R8YHG+kZfSUJWVvarWbsxylbcp79G0EXsZft/FQuj8sT2entS2fdbeOD/hHSv0mBCF8PLglibFeG5IDwhH/eZNXLyxs6Fma2zL/7I4h+cbV8Mi0J7/lCGpQLeHWagV15JUyX6Sd0ZmDZPJJjYrU3nXN9xXzagf9I+4ByiLXAeQGA7SPHtb74Gkv1XbVwU1+oEe4eBHvSBrxb/RNTqdarRasnrbDs/PSxLvxT+RGaZKLs1s/fRwSoxxraLDrpALHYJqfmCWJQiO9jdQTWn3TX6d40tuvwEd9+j/gGq8dpHjEC12tyt0O72tjxyxUYdbIydayCxwVxnOU7lhOljNLacFlOCm9HzZ1ZCqgiybpf+jljTiFrGOh8HFawdoJ3jHxuwW5ScseQaijcfdXjh+XPCw84XEDbioy2ldWxXgks7wA+xeGtfaAPOZ4BTJnN4wrpGRYNh+dW3NWzzTBcFDu/ftE2fpJr6yr6FC5QnLT/emf+wH3jZGj6uCVHmdEwBtejglkWxLXEOL8AmEQOLqzD4++y+m27u7K2QItsraGezwx2uXFo9J94zDf4WLUgo1PAHUxl7zMdqLBA/iDcN5aRwB0EcPvxuKrn7i2ceCr/sMoQl+zxwxxWx2Z0kyHaObfPbb3ovU9UiL54oz0OsaEfOr6TLc5IdtK3F27DGf8v4ypQDowi1d/tyVWbsbEg2kVYdfRElqEnwSwS2URqXMZ9VNe7+DvYgz3qHYlv1Oh5O6CNqGYC7dhlhIdAjQ9yCXBFZkAGr8NjFgML3btIa+aJa9OKqM4GwpKQrtG2fMN0w1pgBu0LtQlwGBmazWd1wKoGRZ/nCrWbMwDZaF31CpyRCwyITABeyN6oRytC1mNb4SVhR75ikwuw2FMkUffqAEKL0XVVeJfP8AlHWy9MvMCs7r5gmMJtJYcok5TSjmjFgMFFNNgLSerBoM5FUiGo8cXWwv+ItJ1HSOKg64UAbQUWKKTTLrQsE0k/UwflfaRwE2GTjPsdqMAQngAgPghpKbBjtN8XPrfPtU/anOxZSEnruud2WqwPJz9przRZfU980F1opuCw/1EwCTGVoDsvh3eTRWR78RC8lfmj/r4VA/WIok0tyfy1mG6JdbQKFLDZLilvV8gbD8GS9vJHZXyo3RKHON7e2hrwt4MT8JGetneI8Q11MvMOeUBeoO02c6XM26WGDTxYaE3nDevmUC9v6JwrNTw0/kPclP5DOVD76WeAHnC459Hq3bq7MbJ5/n1A3MY958reNG69onZ00ikJNyGw/83dw6McoDTkrllbFuEkv+2suuJ9jCvdAeBi7kGTg4tYHm/Y2+Y8cHtZ8/BYbfMB9xLYkc+5Ht+mfceqtzC1BnRLGlnxkLcPfOd8oUdY2uAlcrDFU1kWgjX0W3ttm/h/Lsu0HIG1vxPKLEKi32989ZbvJaJmxdhdH8u53cfx7j7i/eR+H0NdORQCeyx0XaX5tVo6UPWGczFSbF45UC6CrI9RtMeR6NTHhQ2S0iyGNEKgyHl3VFz5TERPooAzh9eWnKHiIyndIRQw2fzeMsha7XxQ38y8u1FP74DCZp7WAk90xnDJPK5jvKlPvBZg9lb+LIUvPrypXW3188gkh+OyYWY1gd8UdJPWby7cVGN5mKe6HmlJLZCABfFA6dckXf+3sMnFuOl2GOOB1o3ucFeWvVQgo42TG2F7ZVLXRp3WhYisGh/UCByrKVDz8hTrZc6j8yD/sOj0hdQ6hBAamO9qZNpo86CIqR0J5DAT6Ketsbl1FHCQcS621w0HpwCKXg+bUJ1FdcRGxRD9lGHhDz8J+R96SuOajQOopnSU3NgUOzg6hwmbVzcgA0f1xGZ9KPmPSI9ld9gDCpp+p6s3OT7p2Auf1DJEbkYkt3KRTgyNwg76u/rR4Xh04xoR7Obg+ecPi51kFBh05T/i3mPsVHK+91lEnUcJKQhecxt6lR/pkkBwyOn9JT2rkcoteh0GXyfVBwq6F9BwjF3EOhwJIEE9ouhIIf2F2vp3Vp2Kpx8KMtTB224KxzAMRgWEa9aJzxOv6UYELUbqucZh0kmXerq6B5+JoKUMvgX2LcwsjGtWYJcvpnrxkvF8tKIjT/aqshkl/wFZKLcmNXJSkvyPyrTGgx778VPFYwkGxU7sVi0GdWCncCAaJwSaqgdqw7KXhC1XUFMUcFuAWhYAz6DZqAKnIurlfvkoFxgNmnowlAInSogeOOcijgQQcPYPA6H4jHw+33m3KiLmhsgaVW0LmGz7D3froGtA4STG+QTzOfrYf0jTD63cXAjX2BRpqZP42i1wU8gQl5QzIGLEs0TkSIbU2Ja4cSKImk12Cu7+EPpHpoFQ60li7prJCdfMHHSDcofWUBRVd8oHdAk+47cc8sOd9uDeYskx0MtGtEfYFlqfetyfvgGV+YPgBS7G0DQmwJlJVNzPPDhZ+udzyen/TdFLF5CX83jkUVz2ULe3IdhSE7vuhyzDRmdRrr4k86SKDQAHv/r3sjVUd4EW+HnhjdjShJrCrkuP6G6g5AM/mfLE5QEGf0KU0WCLjgBVNHDy6xtyz0cZzb/Aw2p2DLlcokKBhakINLWDvrVwq0M7kn5Z7LivtFyiaGvKabHbdP84bBM/dfX0g8+JkVr1u7ZEA6rNOdAJb5ATF9xRW5qNmcPv/fd2PSLq6VXRSnhJeVIMbEOQ9QKmsucKYRmk7T/zpkqoOw6/sTk5oTFJIfRKH3Oi8fDz1Rag3TNRgTby3AOnN78LNoYgm6oUDt60PykhC2WkxYNC3uwNUr6FT+Y4jj7Op2YxTfDjEOxH37uMktK5wjTtl7BoUDM2zEcNZlmBBuYwqWWhcWT1up/u3bvanQ5P1Es+sD0wTmwNzDYR5Ea8h243q2LIC6JQXHJ6WnNQXY+5/0W/ILfTMLc7I0LI+VLtmaUiTi3GEcXdQESrtTVCBGVvY6v1yWG+IrflxbTxvkDUrveeOXlMeRdZ84U6Xi/SFq/Iyih7gAM2jpsdPIUj7t3t4mQb7TdQU0PyzQeGvewhaWaREHLigGcw+qwNpIfipq4f11d6U11zzWj7ny0lp4iAmoVD5UWDSCUVHbjUFXl+op+3trFfAK/BTY0bAdNi/1n0qUveHskO5eN8hbcLobehA15J8WjPIAN7iEOeoQK6Pk7ddUGtow2JIy24dyI9Jj1Cap0nv7GBu94CRT6C7WaRkASeGUArJPBU8ZR/Cr70sBzFw1jLVrWw2kvFmjoO7fiEi3MZPGQY8r4d9q7lSqxALFqIhHkpJVmEaePSvDTidv8Cao7iu1U+cHin2ZXki7Es4XOH+9nlco5Dtt7a/Hfxcg4391xrq473FhphmdvjlKq05u4QVRtK8nWMMZNFo4Z8xya2A4P1dVk0iIDrLK1kKAA1IB6r4E/2f/DyGfhXjL8sLI6pfPO/OKa4Hgmy+dPwhh6NNY0pqfGEq7rFRtqxaVH10D9atkp0VnFXmM8QoLlXRkRaTP8VkmM+N4SNuk+Hs3m+xxD82P6QsGS8f9EO8u2o9F0Z/WvVjHCBU8AxhBUraP9NzAvsLpgwo1ts8nZZpsPfJv2c3eT88AWwQ3nMQOCc0t5ha53n0dwYQ8AtB9+6NacRwtm6siA8X8KlM1kkRP2kNn19JW6QCxp/sWmFwpl9893anFsdGF2hM+0PrbmG0M9ZVj5wuVSWoTvc2CcDQ9aJvEqksTyehwCFujaCZpdZVZ0onMDq0pUHDs++5NXtEoE1Lww7ENRUg0vmPQ/kyf+Z3hWEgYU97kV/smtokTkwFo2xYCRNc3iu+rgj85xpVUuqOxBQ/Fy30zuhuzTrhkvepIHjMVzUtfA1WGa0wSPljrkzyFewrGvpqYTOG2yYc2dB7REpIvdxWWZcMP16eG9mr4qutQ8QY7V6ozA0GGMrc1GqhHWFcymKiT6tiLG5ML2s5+b43LMhRWhr6ZEzWA1GmManE+kSQxJNdhE4HCnoemirIqx04Lr7BPDUGX4vJ6SsZ9ZmPUFiVwEE5iZOGezTpaCbXOhiOIAJhaWwDMVCDNkjPGA23Gs/J4dfPBy0jKCcTW1sc0UapJBJUl1ZFx2sCLbmQ+BV8h8i/h4qTx0XHIwu+wE0lWZ3bImfdZNIQrznYL8fufs+DxM9erkpqBaOxSoMmq74CXB486ewljYOYdBdNSlvXda7cStu6cDYypabhOrWHKjTDML3KCqNRiOAOOq8OkFx3QutpnJoTDSDwiYjlgjHpDWcdufhqsBZWkKFwdcb5/WP4kzIwVBJJlGH3+bnAFH/hsKB0nDHqOPaL9ZcvhkXjjatL0/QL2FWs2xVrZkZ8Kto+miNNq6tEN3FtgI78KUyg3YnZvCulmjowpEAPAb+sBQ92guZwYMEWxMPsiKaVb86EZx0NyRiliZtWOu8WGYrPE/+RAp7oZ8EAtTgjwVrlz+2IESbMQ1wRGz0xPEeRY4gTJK2wNBPvnZnkClZKK+VMxpkOK2swQ5QOYJEXuS5nubmGOwNa3+g2oEcJIrnVI51F3KMkspckUi9wcTNM7gSE9nM7HyyqqyhV6vOr2J18ylGDuluy8CGQj51FWGcpJIuYFahsojgsZg0VZ4cRDj+B6DHHb1Lf077WL+KmzKApML1T8pOq0NtMrvhyVnL7R8Md0ByK3NRoH6PqYtjQWgsIdnOZsYAv5HJDhZvm5a8D81MvB+vf/F5iABwg3KxSIqevuVKbz09lXpVQ2VIN6pij6UyvLL8PLmCHDVPsemEC9PBlBwqAjEalCUSxOJEf8M/yUl1m8sH0TZ8H9TBtGWpjZw0/VEe9UjfSY/QOE9yv+Fk6lrFo7iX+27sWRQ89mmDmYDKEArE6kFj2s2QhBrLry9rsR9rKe+Ijqvg6zJfPFnlWQfIJ6aQpQfBTFZCsrfcPSHHFsR43zqKG/LpPT4pXrxi9zeEzx06sJRh6Z9Tx8rnrV6pztxdOp2xrhDaxwCu0hXvZiI/L/BnVFZ9+NlYcnxJ5Aty/tBagyw7ToFkvBImLEkO2BK49E1KIdkfQCN06ZJua7+pjK8cHEaijYWRXH+FFy/ESNJHJ/FnGWOhmsbZoQGpTH/soaXaGcqQk35+p95jP+FofJNfxAaQW/YIw6fwJYwdMwhAZRV9MnrJkvvibjVlU5bJdKt8q/id+5Uyc4cqubb2lKGB7hcBX3oeTAJPRKdw+xznUkmixcLjbyFC3Ap71/ixswa3QbKKd1R7jd1/VvfiyIvLJ2g/E3URV9tsHQnDj3TkQzqY7/4a11xkiALtcu+4oeMcmT3rhZsBVTMCrc9z+GK6+brh5belXOWXMafGIlQyGgcJd+Lx0JGPTDH2jXtCVvht7isoIYaZ7yBJZTm/2LMGMARiR/8JAj898zNMNDaqMSYVrCeMEyg1RH0j2B4oXV0sMMW1tkMgD25ubPqGVkwJbfdmDGpsv9hIeAayo7Jvr7h2HIvgAwak772PYQ7aCJL3acFgl67oz3q4P9joiz98pyIAtGSG5+oJ38FHqPttxnJcvotEaV/7p7773DU3Ze9+sWJKo0/LSR96JWHNjobcOTED4djgC05licyIFJd6O4bjWo+8yhGmPB8XEawQ2IeA7QJFl2d6CDMWBZPtA0bPPKMwVhwUD3IJPaHjXbRjWoGG3nccnsciIvpZhGIxFxdYKrcUJzgerIE/naZX8J3430ozGRqaUxt+/gtk5GgJUa+Z7mEtidqUkzg6xlm5Z2RFtXvd7dOb6WpC9IuVLJL11fH3mCUK63NYmPmkIOQcGqAaElPkAT8Hq+JyAgAgogDgDyfQ0lucDRu2oHO6+e8EsCCZ2WG/7Aqy7LWgxMWZM3C5lWPCGGYeQ1GOl6ZDiUkESJQgyRcJJVJ2pGFRN140/3oXfaFWuwGNCbLgO8bmBy9zd3txI3Mp1FXdLWq6N691ZKjt5HdE7IioOBHj0bHECyEJTUSjw7gLKeNyvMXgyAbSaGEAW/Zz5/xdjOHeH/miLOI3eCcDtJqZdgcJo9GN8RDl1e8YCMAbFMwmJS/g+fVYqLci1S2OVQI60RdQ/C6TRzfnpC+yCk+bsOrtgZ1AnGuDI+nLmhDb4aT4uDMYNaH8kdhcNqUWqS0uwH/CT3yZ1edW17ndQar2qZblK4qHjPTQala2SfEhzK91bVJOVyGtbiSEAb01rLN+nPAZD6qxDn1AYabixKMAAiz900+Ui869d+IxvxxaIXPuNsL488u2YpLNpkF5fAEQ63BIEtywGXCGzdioh7ME0Lix1xO4gRiKvCibPLZbIBbiPLReW5QN5BtC9lOCDLEDqw8AX1z1RkMk9GPYXZPtJgmfNAfe9wMMD9KN86cODCkGhV/jFSYkz1qw4CLwU8UuY1uXjwRK6JT6G0MVvqFTTdmpS8TO1s2vqaPn5dFoeztX9oL6QTJa8mAj7tVgcEFKWQetnoJK+GUWD2Z7sEWKU7QHVzfBPBzOpGBIy4LGrkcEQRWihXCLWfRR08bnuhjUH80JiTdGUQ2xRJdx1OhCX3huF2RmUOP53Zd/4+0A1UPJ8QBRpCUFXAsxPrbXbNeI5NXSTvMdMMW5LX2laXgLb/dbJkjyPegaeUOqy0XWCLPOy/n1fE2krNAJWc8h3nbBTdk6v5HwS9R48AJ7Ik98kpZTJWOcknNkp+ilAX5rXOeSknZg+3fcTBk/eTt2U04kko0V/01HAg3w7Zo=
*/