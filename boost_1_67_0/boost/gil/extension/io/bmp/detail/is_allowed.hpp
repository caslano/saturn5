//
// Copyright 2009 Christian Henning
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
#ifndef BOOST_GIL_EXTENSION_IO_BMP_DETAIL_IS_ALLOWED_HPP
#define BOOST_GIL_EXTENSION_IO_BMP_DETAIL_IS_ALLOWED_HPP

#include <boost/gil/extension/io/bmp/tags.hpp>
#include <boost/gil/channel.hpp>

#include <type_traits>

namespace boost { namespace gil { namespace detail {

template< typename View >
bool is_allowed( const image_read_info< bmp_tag >& info
               , std::true_type   // is read_and_no_convert
               )
{
    bmp_bits_per_pixel::type src_bits_per_pixel = 0;

    switch( info._bits_per_pixel )
    {
        case 1:
        case 4:
        case 8:
        {
            if(  info._header_size == bmp_header_size::_win32_info_size
              && info._compression != bmp_compression::_rle8
              && info._compression != bmp_compression::_rle4
              )
            {
                src_bits_per_pixel = 32;
            }
            else
            {
                src_bits_per_pixel = 24;
            }

            break;
        }

        case 15:
        case 16:
        {
            src_bits_per_pixel = 24;

            break;
        }

        case 24:
        case 32:
        {
            src_bits_per_pixel = info._bits_per_pixel;

            break;
        }
        default:
        {
            io_error( "Pixel size not supported." );
        }
    }

    using channel_t = typename channel_traits<typename element_type<typename View::value_type>::type>::value_type;
    bmp_bits_per_pixel::type dst_bits_per_pixel = detail::unsigned_integral_num_bits< channel_t >::value
                                                * num_channels< View >::value;

    return ( dst_bits_per_pixel == src_bits_per_pixel );
}

template< typename View >
bool is_allowed( const image_read_info< bmp_tag >& /* info */
               , std::false_type  // is read_and_convert
               )
{
    return true;
}

} // namespace detail
} // namespace gil
} // namespace boost

#endif

/* is_allowed.hpp
YzF/8AtR+fUFNX+G7Hs15qtS6pfVGPQ/URv/s16Wr/Ywv/r9SfyL5v37BLDnq4PzFTvJC7Tu581oM2Xq1nPaddffcembmM9O9dNMOM5p+s+gURGdJ9AjmvLVWcTRn/94eZov2ByqZmi/MbXuGJb41EtNcXl67IVEdT3InkS01UmeRPTrc8tSnkXwsb0K1c4i5OiPpJfXKxF0CFZn0NnfK2Fk508z0eEA5lCu7fywqL8KUBXQIGlkz6w1DZ/QnkS0cu/AoQrOLO8jarX/1Uj4CxMpEXdTLrm296F9fCiqUMwaHuzGHUTC/PeDYNMla7TizkHBsv8ljbxdi07kum7l7xZ8h+2qG4VOE7cD+lXQQfvf2RcHhMvZ806KRdxuHsHMJBnpBnM3xXyNF4qFtFLEy0Kplr1UE38k/27tIqlPkWYE2ZQUi9XV570dqRZ0yuswsU7LKwWv/Gdyt8ANLVfFDWrxbKmGy/F6AwvvI+zrRK7YSpR/b02lE8YiqJwW3XO4SzFW+aeMZFj5/IK4VfRLwU3CUWKP4vgVg2rhkRmKtAoAXCwixLOy/9IPqtPBwLN+AYlpovKnutzYy1Tk9Z3WDKRmrmZEKWGUwQwLGh2UlbGFGWFxd49CRnLJdyWDiSJZsbUw2gozn1FOSA4nkdp+lYPCdhFKHEK7AoEuoPiKARJ3sx9Fjva6OtSOJidzQf+ELK1ipK/UvYgbBnxHgWJFfzqfuI1ytWmKU8wsOZxvuO4ZazomvHcdNeIKX0DzLOCRN7x1nouSxqdjf0zaM9rKjzJODUfV96zyWN3L7x5KSd3LIxqm4XV1oeQ1S2gzftMihHuMhW8FD+nMWfqImiMw5prx7joAw7kh0gAVoNhFeO5kveEUgp3EfYJVUdGEiFZKypxCeUtAh/RjjPLm8tEVH3YavKO4UwDakjky3iiQWNmsGU8ufGc8X+2hYxsXqh+v3LNVZzXdJu541ApXA7iY1nIlD79oT3icOvCLBxmqecxXZKKH03XC4nIlbq6OuEm8V/NiUpTB0KrCyhmHtInBk23YRquTuUmtl2ox2voOsmBbfgCcGiBprW6LQyKuwQzckXXcdOPoLPk4ca1us/SWHnJoOADw/tksQA+iu0sYsVcxmmdepYdwpt467XwnTqqDvhXm4qQeenUz+tmJHaH4svounEtUTpbmxGRzkdQWb9yK7AIG6CONrR/XPy3E4JxzTVNcn33CnBgtEf1E82UvxS+o6ZZcVc6LzDwJjP/qFGfiDrzOdInlSDW3oTeJFQfAzQI6uUEG1CnHMe6dO3YWbm6Sko01bZjUDwfAAck/rURohFCB7+vL3u9vtNaUgjZsoGFpFA2hwA/bK6xlR5z3H/3tONVdqsc14BwDdqIO6i7Y1iclrXk09eYo4AVlpHNSLcqzQGqUEYEoWAM/Nfvcu+1sI5XbN3DPiXfmEJMrxaKxs8Nv5XRYrf27TYm6H7q8W2mX3FMPGrFXtPhKD5ype1S2bSp3Ik2mW53NvyGr2xfnMvUdK2pYf7f9TpPXRNw/BwAVsjo1rW+ynVZf58K486FnTznk5tvhiupl2O9IbNEJNLcin02yKFut/ElyE7vn5Jzgo2H9JNIlztXdbSJ8pvM6/jnhOJ/h0KnYbIQS7FLQrtaU1OQL/ZjAwyuAq96wQxWIOsQQ/wzOTpOeXKyoWMHZcKNYwytD9kZfw4R2D4a16BPZtokJ6t6yLD3ruzUQvtONCDpTQF8rzJXuSG8bHftA0jYe5JBRh4lcziZV/75s36yMZlOrWH+hIBgGbPSZcFS07lbDgFwJJNrdL2zh6li5CHwnnLlTT+mEF8w5qN/A5EXCorrRfcM+oiY4oV//XGSkgBMTG6Kw5F0cLy3skKYwDV1RL7F8+CWORyWKySpXDfV77Jm94qR+mMhgMe641H4MHOk7nFRqrBW/86pvRuS1pQB584g+K1KnSPOoc1u0v19JBRLfEGja5+q2D94gf+fWa06F9iXX8jMOeOi7NgwmnUKQM0f0nHoYOcsk4YlFLgjN969ELsg5IhZLTLl8Wei1zJhdgOtFQHQzfdy//0v6MDQAJOcQe4U2Lyy1HyMYS0oi8l3CMeeRLD60kVPENS4EdkR3u3ui9lJrlYQwV9yln35RLLGYPjeYCZZqxH0zjHulVt2ez/ynNGX+KA3euyVJ34kfBZNv+4YAsiPUrsm9/LFwBSkZ6sKk/sCFUdKqYIu6aimwBIgG5AUIEb0mEsXKRrZKf0A/j0mJNiNrlH9isrqyftOW88MlRQ3/n72CuQvOr8faz9np+Hwr+LCT7XwJ3OZm8fqhl6WGPb2udnl6jiH5RCwJfbmohuPqSk6LvLEheDEHxrpK4c3YE1ck8n+1dbz8SFnZwj6Liw7kKzNDQAEPwPw5gSm9kBjpp9cVyaXnJjv04BPJShSHLaVWaQ3r5MGZpY5TBzjMh/aSxaIo3VlqZA4WSmc+UkQfpl4ZMZrcz30rXIhRG4Li5N65zUz3ZoKCot8JKCGskhycXtXMYWAN+nDEJgPuxBu5imjRslOySl22ubhRkVDDkFqsjRYBWI2PWoPARi80eW+H+oKfl05JS5i29XcGWVxFvGz3LAicH6rgF/lcjCSLHhIlnA2PGwPmi1sQeZILQR90RMDN3js5s37woD1AvWXaUwwUxSJirLXFKoCJhma04Saf4SR7z0+czAtSlE2TVeFo0A8i9o59gCUebhHjyvsleAXWowOe9AgX2khYZUfVP59MWjxXCucQz6O9++M4Xbax8mILhehpoTT1hbZK0TGp1c1l1Q6uOtgdO/Tfdr4F41omtJKgKr38IsqFulJNTXxSgX57G1q1J9UlaPKMwnJ+jX0oxMmMF5aiYjpSTAjy4cbjy9B6v6B7qT4PXK68m+/ifMj2O5YccQIlj1GT8eFY3vX6yQR7VzCvNJkdxVK7Vd8fHTPyRKlnWu9uNh8E1lNyhXfz4O8/+W0Qb1ji71+POuxg0jS7inldXjjEdRCnBMwLj+tSSNHDqXZXfGo44wsNk9vHvTVLaLH3yZ2TdESajGa1RAWUV0reGI2b5POvovj/ndVdQGiKbGexSUs65ryhfghfp79xW426NB2OKlS8PWHxQhhZrzCSLuyvI8shUsIZcVZhirRJkBvc4QRYuS1AJRrI8THyTwlFduEuDp97+G8FycqiM5e/T1go/uq0ProHdsUddLNqZdFlQxUFFE/ewQuHWwMH99DDPdEAjWkzKLuYkG/xayBgUaYk2+4/Akff2+zxIm+PBNh5XtvswNp45uVUH2NL390/G2eaDWXEtURH72xJgB/MUTY2WBmZhsX2UPAoeihxBLxK6j5FcWpz8kBWYWNmlO5sjnHwIAK64CXW7jXMnSHDZ58tSLUZ+Od7PR0Hb/8YcH2jwiOiP4NzN5w7YvL2oMrhXcGBZN1ht6X2bz+hbIXktTpNLHvQlIwKODDiQb9fy3pky8QtLzYqPmF84YHzPF9z9rOgzAdOn+v8/cPl+6/fOJMf7YaKkhZL5lHy+/EDHQQDYcHGoOX5t3PFeWiGU45xIEULNW81K4JxjriHkNCLLTcN2kruf9D4dmt3bmp41Pi6Gsz2PXNxTc0rQeVYn+mHnG0ummBmYcTXIO+mZ5+Ykf57Ttdgpa9vQEAY1ZSs9vEHnIO1WORE4xMHau7vRsLDng/FTL3ru3G3Ch77ype+3A8CnDPMxKbh0S076QRcV29P0nJ12IeYFTfFhOA00AeFJ2QlHxS+xuPpf0TUUmXS9gp/KiATlbfYt6d4fpXojgJxso0WHreGpnNR+KQT+9xotDKbfmgKu2wkNw3ZVUPo/bedHuRU0FZQRO2W1h3C9LBRSFyFlr/syPLafTDzzTLoEpOjOywFNPp+k0QXseeyiA9oMWeYkRfZhpcQu0fUhoe9Bw0gMcm83hEFLYMYU6K7PIiVWit2ygssHXcVnjS/Ra8/G6W49Yh++GPMuDv+UbwyCgkPgF+j2VW9/rhBRPdd4fhItPY9ZB3EyVKcML3cjzbTZY40WXcy8ruO23YWqQKnEPyp/rqbxY25u61O8V1/M7InA2q3/lyvU3kOwHIqxZWr717O8+vBPeT9mNH8Fjg3wwIlSC7YG94Z2cyos+EWjl1zBIftsPVSgc7QOLkyTsetg9pK5njdNoPXW6J8SCrJPzcta4oDebaVTx9a8tRby8BBgAKSy1sTaThnGNexaGaJByOvWmWAgszYYCvUYj69nhgPa9d+EKtNgY2A71FAvJkixvafy3sRZxbs+k+kjba5UgvsWIvkbKqRyeBxCYb5jJl4y/vYCmNGwzfgutrl+gvtQiPovEQlpza+SSfU+oee8DqdcMuwV8totI3CcJT7aFYDKTE2j+nwViMFdo1uOiXhpn2MzaPCpvCJDeXYfxaLB2+WybBzflOd8bSLYysBm1GcJzZwJt446zPcKQ284TYGDmMrL+YzbDxjc+Cn6Y05QtirtEa6oomkP9onARK92xLwsu1v/cZSu2kL+mR43kkL+gM2SOfqE0/m4IbGFDuMpbej2Ma/6okau0UtF2DY8DvDlcAvWPi11/ZQATdXgXpy4MikK246egU8U68bmGjqoVBZss8wHkIfwr75/T995Kk91Z09O1gKzsxBaNxLJtejjtDEOeKqdJRqEe58CUuUg6EIq0ev81riAp3bhLE9Zo1nfDUBvoGUp7wAPnl5gOCSFacy3bljxqRD2c5mzr17NJQtX4AANaqPZkQrSLjpF7TOdKP3YzOjZFw8nBdNm9fPal2o+LpyKkxhG2NcZXj32RSXxHqwglFXT0u0DYAC5yIkqOaTp/TmYcilSlcWO8DbGj3bjdROZiqLaF3oCKBPrApjWvEf3C604cy5BWjcvOQ3fNCRDS8PghdhGZ8l61b7Wm03cIPNdRn2wgjVJE50xd40H56R19cbbtpN2z0Wc9j5haUtWzUrI7hPJVNoDbNNy5R6VHFa6idjdE5tqb9i8Kz13FkY1Lgd2IjczAcUKGENe88HAIVegdVwz7nyz4Xs4I3rGSQdviA4986InOUiYpGSIgUJ7ICjr6BsWoPoivUHphtfy05hWtEOM6DLDjqPLtsZ//DAmelQuC2L6n0Hcm2Nhy6hEVmQSz9HO01q3sdYo7e3ecgpVkuTK+fo7WRvF2zEmeXPcu3cRM5alA/PQPbLYeFvTCFiBDbIb0lir5K26f/VDPbHWrh4ZD4DuFGGkTKF+4EPlVI/bV+uE6Aoy+XrXFRQC/dDLI+kpNaFWUBAw+TzFlHsewncuO83ckgtl+D2NbtrDQQLaY0h+YC2+HrMogt6l7pD28ePHrtxY38a9uhuUHGKsjaTWvu/lA/vFyyWgGq3A4TRBBRPvGne8bh47OgukX8YK3kmHuSWxMDhMZYyn9NHS8W6PpeZoFGVj8vRvYTKP4OSa/qrjRtUhEROt76oXSWiCaRnbA+ue2daTPWj7reINClRERKunHKtD3xpsdLLRuzLUpCjAWNxeQDqvLKKScSpHugSJB8in/5Eqcs2bWP9AJeViSoNa7O7C9YQQ4pHzSIB5xHs2zedSf+KMEsQyT+CCqmPIyn0tSKixFP1+GX/DK8LscwnsWlltyWfiPKIdsF/rswzBcuv0PvYjxuj81SjhyAJ/Gpgqojgbwwf+oazbQwLsiNye7w1Cj4g3DfzBGapkpCbY0TC9E+CT8LYZycXKNA6if/KdDUhvRFf0DE+8E2JqR8b182A6B4jmLleCI8lfA0RvxKuROvqcsShLWb0TW9Qz3wGPvveCB2tQb/Ol57JdhFonbSEyAtn6g58yvvW9Hoym9VsAiGLkqPS8EXWQ46sC/yXYx9XauVuVhbeBa3+cLUV7bCLwGqe1mYpmmbmJsrK6igKHte1YRf9MRbAdgQQ42jT0BxgsY/sjebCqOdLXMTUJpzpYetXinY7ukhL4PYt3LGfEck2vWFeFliglht3iTk+iWnbUO49sjkAPBQfO6QT9YpI2UC4H5H9BmCclNqJVJ0uUx0OXzhKEICjsbP3hopDvbPUUmCxCQHRnvZfk0GuJyMBgo7+tdLdhvJvf79IDhmv3hsN2TvD6qQeO3dFDP7g2QGca77QJHRE6C8Zl+AcpX2+fnebwNQeiLcFPXfhZbLi8rXIjy/SVOEuKkLhAFgulPWAfi8Oojz6Qa0WdIpL9zHAt0TIykTzKvkhqPV2M2FY/gdFM3nyyhArfPqW+Kt5TtVqiJeuIe65CTcbyIE0aHioW7Ouq0zWySJe37MjbhGJuzPryupDiW8Hy5tEcGd9Js6eNjyXse86M4bhAd9F8pCvCuOTT8cElQ9beak+eABAgLA0IEDArz+lSzcc/zIYO5NrIDNfdkIoU5Mn3POCAbjbnQDEBB8EBCJFfZzoj66OEvmGn3X2/FKl+AFGya4XD4AOKti8d1Wq2yLJkI1k9uDJiwKwKAH0EtXOdm5RFXdwoP6LjPe/6joFoRD8zXzLdXOAeM4tFAMT8OIyUUor1ciN5EI3SLrP+daK1pjYpwzP6owdNNIG2fHNGg/r5ML/NEy0q2xoBZT4M+uviwozFSZoDLa78aJsYlOuqVUi2ahFVaXm3aS8XIL1jEEZnCbdmJl6L8JpMc7jpjW4admM8WEl+tsmMjsFvArLmMbhhJDljWUXmNmzWCRFNtf+JYyYqtbIbwGWuERtM0GTbFBrdaYn+Ozfkr22kzlFEbD281qrAVRgkY/BwiaAhLd9ghF5LY/Y9Vt3lbL3Q9sPb0V1gtJ75t3w98jzIu1xPyMisDidWmIli8U+QCpsRZcTgT0FGTXKPCRzo/ki9yq8nWIuDCtj26JloED5ZrYTStN0S/3bli5HxV6Isms3WrRI0rlvRMs8jvRZhFrn6RiFTDlEu9XMUBDRYdeL0+46jqEjtruHv3WzPKCHf5W3GMy5gGFwCDuAgwOoWLjGJL+umU91WVyZkGa4ZdBxjoCn9CRKdU+Hy2DaiDA0EhoU1paNYhIQh1r3KoKkJNlgwutf7NrU3F4M4Ka8tVvOKvCAL9txGe6EF1wOyMkp8chSuYUY9tZ4jl1yzCovuZyq3np/Cc8txtt7eCGkfSLI4EXOyiKoLKaJETu4oyd9CRtRxsoXw0Gc18ZwwUFqaBW0X2i2W6Fc8m4lViula/WAd9cXwWQci/spnQyP5F3NDHexhdneC0MSfv1A/Zj7bmJldEm7/VdQ6V82OmdI7LQ4tw7+wudCbDlR10KsUSu+9G3MGLXalLmBcktIsVkGrA63xD1ncSMQVg5M6/MJqYx54Y69maYVBDzdvIAm2imO7yrWycQgyONPEWbxcslBl6npJCTxcdO2Wa7uuHVtxIz6wZ+eP/BW6ULV9E0rGMoIKxK6AQ5L9fbOAu4SXutfEPvMue2KAdXAUghVLL2yON7fd4GdnnMKwY24VhVw4eVHeTnUQTy7+yNQaLvp/NQyfWW3WeFltckZ0YJZtPNuarQUzI//zNwxieMco1fS3TkVQfHoK6Ws3rwSfO2K/Wt71Gv7tcqL5y8eI781RiiFrDhgfgsI8HEfYTfD6K9CD1FguFh8EL2DNMWUYznylLoXQNm/t4P0L71t9TWDnDS8JfrgfJkkjfQ+0OsWcA1pEKWenre0DnOR0AiWq+oHEPwxFLjLx/6s3UdZ1nq7/2pk/Oo/ii7toMdSpkZJZgx5ZOaCwY/MmUtNrQ689syTVQjaxALRBcADe6ihPkWdqJ2ZOozE2QrIYMN4wh3+3qhbjo9x9bd0gzMnwpfrGQMytSaeaSRJ2JrSVaMJaRwLjNhaCO6MvBG/08T7UjDcRnnXKHf8ZI9gKU3kqnDR6VsLBjb6k+erwWXddUN53tta5JQGuP+ySCExw7q3WDI/n2vCrHm9IwSPBv8Vme82+YqkedmD1xGI8rM18dPkFn6Ej81p4rtVVxl+S+kjMaxNhIRgaLT2C/p64dpDUJKYzlYxE2S0eZ+f6aF2oH9UlnufW/l5xd3EiLwewD9d7ZgX6F/stCV1ptnd7OCbjxN4dbtavgJX2X/8ni3guFiydzydkSmnnZS9O3u5WDJ1JLsppYF9GaX5OTulnaR3NnmRdSxNZl81J/1qCubI/PpfHY0n+b1UM2DolnGJ/ENe5F9u8HYfU3JV/RRoTW/r6hX9woPUKjompkHEH7X/jYk27/jh4eKeVsUerjw9pxJkCy7EPXLRQAKjjyJvD85rnsN3YGc80ONiTzSAKdEoO4pFYM8JOzyBqHf1/BU52wnQgpOdKSeE1gcznCZU6z9yub/uZWW7E3S47jjTdZMOmaFxNQKf2TyYz58PQ80BU1MfoxoJmoMVnUbfrdyFV6jHGWwjrPwv01Oqia27zHOWUPayfNnQmjRaEysFELoMgBUAIbxUCTt5njyPdSSoGwQjR/pbcSRRO77ge5IcZR0Y3R9qIxpezMwfImtHzQKjioVab0AYiddGAPoVhZ1fEKZolcog8p+6o10clRzm26Qqyblq/lFEs9j4CN8GLy4W5n8ecW8l0knY5kH3+k7Q4Vch7gmcYfLZblGC3/TcJifTTI2bSq7pmhZyKctyn0fwUDXqjbGCaN7bt8Hotv9Um1AFcZwbOVpkXQwponDuwl+2gPqK4XDz87EqJ9xg9igTtgvv0foGWMY81Gb2crgcM5ZHH1jlbdcDEYBS+NQn+GZCX/961Q8Rq1iWBR54WqkOda2OFe3+jvdU7a8TPQzLGXg3bMserY9epgWcYmxLMPt8XHoOZyN7t8y00OKck/Vu8sSSzOAB8gyrHubqTRXnK/vpkkztXvkLM70D9ZLudf5Cb3s7vl+/LFKWxop3bq2lmMm+xq/6ruXCXxSXiO/aVwvq1MnKYRfP8ja9HywA/s5lBlh9QBx1S6M2rWx2ULtWKaH/orqB7jYDvEhLLL45taivwESfnbJE2xeatFKbOLzBTIhjJ9P/pY6F2hjLTjJbmEtoxrJjdcJTtBitbOtGBBQ/Mg/do2vW/+c8fhfAE6wGGW2Tsp0Vn++hPzJcEmcakHIb0KDePVd8Ll6dxfjDvlMkbWekQ5rzDDdyYxyeWRj7cYSokpz+2wYrHpoucohbk7yWghSmdECzhMxUI/sX2sT023S5wHZ/Q6aRFHK3zBkPlKnkhaBredqjf42wqIejlnALP3JvOhPw6lJtopI=
*/