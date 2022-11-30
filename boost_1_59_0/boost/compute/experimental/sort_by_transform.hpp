//---------------------------------------------------------------------------//
// Copyright (c) 2013 Kyle Lutz <kyle.r.lutz@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_EXPERIMENTAL_SORT_BY_TRANSFORM_HPP
#define BOOST_COMPUTE_EXPERIMENTAL_SORT_BY_TRANSFORM_HPP

#include <iterator>

#include <boost/compute/algorithm/sort_by_key.hpp>
#include <boost/compute/algorithm/transform.hpp>
#include <boost/compute/container/vector.hpp>
#include <boost/compute/detail/iterator_range_size.hpp>
#include <boost/compute/type_traits/result_of.hpp>

namespace boost {
namespace compute {
namespace experimental {

template<class Iterator, class Transform, class Compare>
inline void sort_by_transform(Iterator first,
                              Iterator last,
                              Transform transform,
                              Compare compare,
                              command_queue &queue = system::default_queue())
{
    typedef typename std::iterator_traits<Iterator>::value_type value_type;
    typedef typename boost::compute::result_of<Transform(value_type)>::type key_type;

    size_t n = detail::iterator_range_size(first, last);
    if(n < 2){
        return;
    }

    const context &context = queue.get_context();

    ::boost::compute::vector<key_type> keys(n, context);

    ::boost::compute::transform(
        first,
        last,
        keys.begin(),
        transform,
        queue
    );

    ::boost::compute::sort_by_key(
        keys.begin(),
        keys.end(),
        first,
        compare,
        queue
    );
}

} // end experimental namespace
} // end compute namespace
} // end boost namespace

#endif // BOOST_COMPUTE_EXPERIMENTAL_SORT_BY_TRANSFORM_HPP

/* sort_by_transform.hpp
iGzQQPEI5kYbDafmeKzj5t2jAyBOlzhdktSOYos0XTL1xquKA+tLl2oW4cLQrUPACoS3BZhS0zD0Dtvkl5B2iJ11UtcRXodqGkpAUmlINaKEHKTKXooayQwkeFECKBXpIMrQwdQhSagEGhkJMaRx5doEKzONqrjiHWpQScKHbqUmxUJpypBfKv6L5YlYhaqpgJXlYlSWymkJJoUi5qBqwjMYWFLbZjwyOSDCeopgZOJ5QyygaUmiM+ZgY4G1xjM4aVLXZny0OUEEgQYa/kaaYFGVAKQ334wDNPyTCozN3MU3nDXiG79Yziw1wFnHzpc6m69qRM9Dz8Me6HtwYBCUiAUAG9xy8OLRfHEqS+eaQb4lifEIyyorPjz0CM4qNT1c9IjKCm9Pq0Y/CMoJNOgQpp8buXHoAKqQL1Q7ZvWo5BOqnjm+BetQsJ1Oj33V7J6xznmF845dK3X1I/a40dFmAhJNQbQRxhAgXvrOaBCbuxUJEoAxywBrQoIlsRGOQjwnzjwdKU08MsjmEKEVI9qpALBEwRQWayQZyZSP06tgruzHaRGhYRisYDqLDbsRRZa/aMaoEQkqjnGaEy0iSg5RsHzA6AE7BJOib9KM6XeDb93/TXxr1I25m4QMNJmBeUqaKV7grVQv3om5Z5SlbtRqp1WLGf6wDiBD0QgtQEVyjKlupYKBeoyqDuuxcD4D0KGUHfsLvYy4Gq1JectPK6GoM4ChikpiNy5+u3pe7KcMeGu6YLpkofjy3AHnyS2yg4ursOb2K3HYwfnJmNuZgHnAEoh0NfilBJdCYIl8pUPF1kS8QrXY2W9YRcHliBYILcSikSJ339WQlfMU55RT00rISocswtLKikoPLYLTSj0sCMwBaaWhF4jqCRwEI9DK+8wv5SHyFMZmU5IgKsVFBeXmpmNwmOqlC0KsaMVGgnx2LEE1CBWFGRMKlKmFwqonqRqoKjU+qnEDpnyyRyVgS56EpWij2WqgpBKojHmQD0gOKkrrDxuqH5RtnQMnrKTUekHqm6qBqPV5lRjU82FCqhI/IK7CzBmpEVNJFyVrFCtZqFeHfzBV0lAva/C6V0kn+FbipEfjzORSt0zGbxmX2I4F1nPhacT6qJqkR0TKsdMSF66w1sp06dBW84y48F9yrx1vetxYFiN9EVN00k3SyEkqZRWnOLUAn37rv7yl0oh80ZUyfeAs8mObJluS1jSjrpXGti7GdUI8LdCuT7dZylr3wu2iXMyLpmLKIRKZjJrMCZGtGzl5g264dCKDTVMEeU3xS1gCfIUQhC/LAYI9eGVz8orG/RJSTc+t/HQ9xFr4hf7eXWJCynWV5hsL2rMpmNTeIU/4/qWgzjB1TLdFzK+0mC6umDaSgkoMiu+Qq+LLge4WY+ZH1SimHTdF3gUJDbe1HnX2ccr4HW47ilWqJYkWiRqwc6UqpiXOFh1LAK/miulzaA0q2jmNjxr14qfKbbM2DeBlJFMAsPmbLP5gh3oKJT7WGjrxqpUQ5RNYmJaxbBY5yJHBCy23B1OyzN/oCi7uadzcU1UMWTWs7S7s3NgC+Pd/ZlJv9I7Zrepwfx+/5qIDXlUBgqoGlmiqhZvvI8EbN3Tj8SANLc4VG3bjfCqIU3vsUBwxzdE9cu+hIkfPBLZxqfHBbczKWmNVPMLovNxHBeaOrnAXnErmeWISJaYwRowT1ms4zOVn3SkLsqDEILtx7puJR6EQA1TOAxueLDL2Z4L6ibZLEIa58R1tUqhYDlZfPlg+g7kiFWaeP8QqDdLNbLwNfFo43a71lzI3rNWuTGOdG9vEZktOhZcOwDTVVl87iXBH73Wk0zrhy2uwovwwoJh7WhZk391sq//oNy54HJPLWWOhGam0asERKnnMhGI5RywhmvgKWfd5VRmwe4ulYWpTGI3a9igUQe55MdawyUudpoX8uvgv2seiWorC8hbLknFIApKvCbP82bRKZW++BosV9bTMuTDAEiS0zN6jinVzQA3Ct4PelH7VUbXgqkE2lLYwux5ryuU9WdGqOXfpCvsdNBDvUv4Lu90LT0dt8eAbMih8CaATlAFdLL+kWkU4HPiETvdz5qnlF8Y+jjVUTckpwEqvHJgO0Zcg20uJjgVqToJzHlZ8XqUStNK+g4xImU0Juz4eDj3UlSrUcbRv4VOoEC2a2BjMrc5jO+nBo3U5PK9YzAUMASr6bHSVxe9BXNbt2vjlaXniJBS3/rGUypW+ZVP8Ywe6ptZk1oSsPV+TVeYOEuf12MbbbTcKfeRCeGCP2HpymUZk30Jm9fXKe56MHlUsIJ+8McsAK8ALv02wSpBYA7sYwEZIFC+8Uh7cADk5w5qVy0gIqXnGDyFdyB/IkrCfvoX7Vahiy8rgUSZ+Cz3KtctUBcASzVVTnyxiOpAnZilehgspY6AQh5vNAxqehEE9cPY/uCa5ccJ7aoLqOOqYw/8iWAUVK/F7qdYvAStBMQdwDUsMrbUTBnftu80ZWc3BrLzD1bucdmd4U25yz1QTDG9agE/Fl3PW/LZfgm5iM2W18WJkmDkxfrJ4ljMjeJY3lb7BTKxuRjFgUBQafSAGF4cD01abmTIICWWxpO1z0ziTQusVHQGBz2/4ZZD6KjM40SCKG0+gdg9Yze7YGdw4ab9y8Dknw6AOBJlZctSuuXxUetuZ6KuzkpIrnwpZz1Vepj3uyzq65p+pvB+5dJepzqsvRHxYwb3uYEnPtN1hqetVf7CJFr0fZyKuueMLUPJsGPsgr3RZFd/FEbSyQOKmhpyVCxY35JUDHRBEV3bQXXLlA2lPVjhRdEjK097tRwo5dSSAamw+A7rxBGWbdreNbMxEvgnPpBt5IEvvTSAJukf9qNlPHTn/Iv1N0uQLMi/rjfLkTJdIZxt84dtcqS5i9bdOVqERD3cEi0QQ4+EAKBUBe41cOkAKyCALIwHC4RywSJt01zQ/ElSwQhwzAY5QYhiLDRmA9p1zUh/6Q3ZYRXDd7FuMoqJSTotYDcBCyztXC/AFi6BeKRAdpAukb2JveJfFfmfhr3S6SiHwlXo2LTTyZ8wv01W4S+Z1dxlxHVtUZSSJYIVQvmspG9W5e7FIiiJHEtSHJIAH0EFZRgLcwx8lajLQhhNHe2Jyk5PP2a3j+PakSBOe9mLIgEBR5KBLoIZRVZ4n+HA/ce5wY2+Kz5x2rQbLzYPtYXFQaTlDZXIS6z5ADawwxZpt//kYu9UiDvhX2YXcr1MAetBuUU0XOcmuWrg9K/aCX9hx/M+uAy/a4i6PKkVj+TNI9e4bpQ4lMRdld4AepukghTubcfUV2MpCYwtyA8jet2/cO7u0bb72i4ldeEePv2KIYVjEMJqRh1ifg/dRLdeUNijd06uTeGlgnjDQ/cuaCa/9rozJAWAFSp2Ar96nVUJASiTAEvJBqBTgRQ6UgTVTqGdysIXSED3Sao7Ya55D6YEguRf5u42MucqBQhqC5Zl06pYSXrt+WZl7qyuozzvD1k/rnmtdt9AJUDZPMfkiczAou0p4vixUV2umrSB9sTku342cPPfQ1VyQUQuZZUb5fnxes1dvcKfrI3YU/NAXJjs1kBdK3YHdtFtqP3Pqc3gd2MUxUM9Lkeq7CXnYebf/mNZ1xrzGsA4NVgZtFdHypQkJ7l38ntdAqTO52QV51yCmQ+w2wFGWhwOXasA1l/b4y+vajKG7DhOGltF29Y37uejskywzh0lX+V15oWfxE+7Ac5J6V/XNc4hrlrJ8GN7Zab7Gwlw36wR/bW7vK5UW6Cpsh/pJWFpm64omJq78jo/36cKQSrk+nFM1ENUCjMjxXMBkBcm7dD+hBV7enl9jXfe2dXSDoaAGeLIuPLXfVeW2K2ABRakLckZdE+Ez1ZNLM3pA8bO6B0HcTWvp0zC3kpCtb19SRjj9OYXmOGtjguns49vk0fOvjfvA7pqF02qcvutYLDdR7BdCHJ2fOc+ckw9QdtZ1BwgdRB5ztiDCwhItfAP9z+VO1NnQCFCmgBUlq1lM9J5MX5q2KEuLc/DgPXFOLqsHOvB6wH5WgiQcyaAmFc8WrkuE+p1VhO/NPqa2o1IhY1F6fXdj72oNYjuvqmwNEhrgWR0GuvXAmttzPPm5WPOj1HTitX5lUWywRkGR78Yl58dlkcL+5O7RbWZSxRlIGI78RVI2jm3W3BgOhzKo18B1hg6xF2jyY5u7NCZKa7fajl9+X4D1+9mR7NVJthwNczKBgmIPQLoUzI02UW5+Zzk/YIlhUDXunTcwCfjw15PsC/6vqlNvOkutxg/edmPl7LPMv7Nt11Sq7iJ2wXTTkb39x78x7T+3t2etp8tExLUKHXl3EL6uMVlGCtni0GWDB99xwblvBLvrAfiIeZtqepgU7csAPiAE7Rt16w5vkEZeRNrM38N2ab1T+wCTk1u1P06aPBukkhSKSrACT17Pj58feZFbBvnCuqtReCwkuVbdphpVNsuVwNBtcYpHb3IOxJjCBDpHj6VmBO+ZW94NBfObmtVcNOKst4V5T2iQNw1HxIWB56hVyvEtT1rdqY03urfTzLlWd6WbGj/LsjJ4m1Mo0d4O6DD/9Xit3Kp/64xXFuzRBtvSoqtvN31lXrLoXE3CJiW1OvYGToBxy8ZMA7ax0L2Staq+9N6r5iGDkCN8w6zKTXYN9jJedVRDipuXH37yfNZ7f57Iqpbo9IWNONwqWvJuHH400E9IQGRKtV5k3yXyGlh200FvhWsqjFu4Wue9fKmy9b2Jybf2EAuvU9zUPd7SCn8bVROSZbnIMHMkr5V1k+s67+22ZGuceDmkLQR2PLWgKLaueHXh7ByBSepA0WGT8jfd7c4uE/wd+iSrRRdQzvL2eLo+qW2ZBph8+C0fZBNPKIoRw9QNmxjSOhBHGZMUFHx27WLON956sQmrJ3d/6G1RKksDfq295qQp8Y1OqVG0xKcJEU5FV6X26/orGK8qRgLn+MJ2goDMzciZ+PXaFxht2FPELC4wb5WViLrcpZJIN9UjhK5kums6j4fs9aSR12vhYzjdAPCqNxuMSE+cNbAGuBCme2/waoiyI0qLA/nb1gnXpCvXFcn6jt0hD7OyutwI2WT3/I7Ve7/JooOuu4i365f8gh3r9usX5Nx7TdGa5wYug/zxd/Z9mML33iL5uYe31C6xtRGfW44bE9JyxdsM/gkiXJo2L7X318exU0iZzlrXhzC+yVkvs63ax/msWEqNvIKySlJKIHOi7vVi1q9IQiy1Agec0xupKJVLfe33b+Wvh1PTOHGF+4eFHoU653KugutN8yYNLT4N612Hjb820WEWCcFl5a0997fEJMx7SIfK694shm+ozS7GMcGPsNuP3/GUc3V9UX1Wg6bhQvxEFdK5je+9ZcZHxknfXIvBDIB00E2WFNexMClGr/elG6glqb6epx7pbeTjvbfNSRDk8UzKoT4UeZOWHaZHVrm12gNpEW7bFqznNt/rSXn07tl/pz2GBzYHS2dIaBIisb3PHumqQ2kamr/mGTj81gSy4LD/a5r1B84OCD2x09OiHgX6y6pXHze5E4U6zNpt27dsJTALOnV028Nv0cLP5CuwcMlfg8SET2gKQQWNJwbe7V07v9iTmWO8V/ljIDL6p2H5fSFAQDyhaxjRMWkppT2yAAFCZCQCQkRE/LhBhPAdEQIE6A/kOwSIgTDIVu+H6IPoher9/h0R8f5lrcmz1RMsqlwlWamUw6Pz/HB//dnZVi6j757H9DVlZBE1PDM8e6Po3VSV6lxvEdV1BYP95bwtsmscO7sP8X4rwP30bvXcKwS/iyxI8rmA+rxliK9fVoWWrayqMUGT8a0j61iNd4aTd8Kdd4SUd0CFtweWt4vdw+X8ZsXldtQma/V4MR9LRfv9xdvb+/X+1rdK7VT0Nued/1iny5P8Z4td5JHke8St52yvp4z9Wu2DjYzWAuKEc5/9eZ+t51ZjltupcIaLflP7fZ8RMG9x7sqU+HjJtK3CwvmPknU9kWNby1NNjfvG+fb82zPLSjGN/dR5t9Lb24ZGv3mRWrZpD6rKwipnmqUWN8unY+6nkban8vVjehO2NnI2LkRk7e9BZaeizndNZU/HZR3KJ7tVX8++56CoBOPlr3+/95h2yKnV0j2FsNcbU3CxHsTCjPsi/2s8eNPY1h9+/IsTS45jHLcPZaUQ1rFHMXVkQOuQ81iheeqLjQnLCLWnh2aRjMtpS2YKmP2t393PgSfP5dn4Ldrb++vMjnjyO7irs8KdOihdt8flBhPb2ZAcJHlwCXQ7ZASunCVz5Uz00Pf9vkfa9FtKR/Hm1/YNBw4e0/Pk/t+nNEJe7z1vJIwklBGYm5m7/pejJLUCD5g645iPs1/dYmrOHgaeAg3V+srHSy5K2dPU5gV2T2ceilvdh3fI2HcJXuc3bt4yjzOl2CGiVS3vfLqbLLe+mi7gMlJpHdF4WI9yMhUVaAaiIxPbYEPjyX09H35Bryo3oaN+pOZAYL9NiX4yaluadKlxilqt/Q2/5ti/jDrSbTtu5V2DybMH049C5LUrPYfK3S01NaQFkiE8wPTWYPNGwhkvkwua5J8dFYT2e9DdjOLMzznDVgeS8sfIdrsDEZ2fiEMIg4d2ek7R3FIMv53pxZS8o/kR/1afio/SV4GZZIusKMDTNy2i3tOvzqcu7+7V6zNV+9zPhad798g8tL/5Tr8uMTZE9p9hBwfHnx9hz+1B7+2kTY9at6mUW0JhWkdQ+cjCv1Oi5PoIIIYls2Th8JFehCS13gsN8yWA+Zzs1DSar65SWnvS8YbHdSBHTVbOhCVe93xRSkPVk3x0/Jlw3yo0YrlHjjm2dJREyoQoN7DUs9jhvY5n0SXaJ/ramoeL1XDElWjLLV9YJWZbIKCQ3XKmBZPi4D0Ecmnv4vHeQIqVH6M366ueNUzdqlRClHjBs6VbBEellAw9TWQ2VELEL86Zh5mvUcArhr1XFuNYMfmt8Gk5dgtYPQtOS5OIAQoSYBx/Inuv1kX6kXTsXoIL3mi3xXYmQWvaLqMXujZPNZ9Ymj1yJ8U/ZMX+fNC4R+isorrwx6TquCArJcSLg9Owdim4l71TL/ovZPGw0qMHdn56YouiqB8BgpJL3z335QUlgCPnLYvc9PJLHIiIRQY86Nh+ZYvaPt3izynkW3Rs+HB5mTnlYBsQv5DJMjsgQmyZ7Npiuugs4o5cRDepPffzj/OxKK1JqPCzwTJPkdqkMvNAmFHibvx8INc3UR8f58XdP33U6h2SS2YDvbx56ZHqkXkeoolfptYC1obmZ1CY5R56F+GT5IteprVzHpqA3d38EvvcqHZlYYf0Npq5mHupuM4RSnOxjBL8RW748S4Q7zfFrvsGuHYmzlKeFqYPDWdNXLKdFruD+gM1Q2CxBlIw26l0gOteWp7uL9rYstjiQrAi8/1eTp9GYPrNLI/grOONmC/wWRSthFjO7XJOvG394ujdiz/FC1TqqM4iH75HDM+U1s0nHrK7ksFXco5kJJneYLtP20/ajn/pyVlfsW+Heqo0wnZFyOgL1U1xgZLag2tVsskht87c55a2KD7Hwp4byNkftB8GMZ2ZXfGJnfZCQi6UBmNVK2IoeKbgOg+4Lzgw8zX11D1jIo++JDFRbyZyvewN2kv26rPvW6Qm
*/