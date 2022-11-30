#ifndef BOOST_QVM_DETAIL_TRANSP_IMPL_HPP_INCLUDED
#define BOOST_QVM_DETAIL_TRANSP_IMPL_HPP_INCLUDED

// Copyright 2008-2022 Emil Dotchevski and Reverge Studios, Inc.

// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#include <boost/qvm/deduce_mat.hpp>
#include <boost/qvm/static_assert.hpp>
#include <boost/qvm/assert.hpp>

namespace boost { namespace qvm {

namespace
qvm_detail
    {
    template <class OriginalMatrix>
    class
    transposed_
        {
        transposed_( transposed_ const & );
        transposed_ & operator=( transposed_ const & );
        ~transposed_();

        public:

        template <class T>
        BOOST_QVM_CONSTEXPR BOOST_QVM_INLINE_TRIVIAL
        transposed_ &
        operator=( T const & x )
            {
            assign(*this,x);
            return *this;
            }

        template <class R>
        BOOST_QVM_CONSTEXPR BOOST_QVM_INLINE_TRIVIAL
        operator R() const
            {
            R r;
            assign(r,*this);
            return r;
            }
        };
    }

template <class OriginalMatrix>
struct
mat_traits< qvm_detail::transposed_<OriginalMatrix> >
    {
    typedef typename mat_traits<OriginalMatrix>::scalar_type scalar_type;
    typedef qvm_detail::transposed_<OriginalMatrix> this_matrix;
    static int const rows=mat_traits<OriginalMatrix>::cols;
    static int const cols=mat_traits<OriginalMatrix>::rows;

    template <int Row,int Col>
    static
    BOOST_QVM_CONSTEXPR BOOST_QVM_INLINE_CRITICAL
    scalar_type
    read_element( this_matrix const & x )
        {
        BOOST_QVM_STATIC_ASSERT(Row>=0);
        BOOST_QVM_STATIC_ASSERT(Row<rows);
        BOOST_QVM_STATIC_ASSERT(Col>=0);
        BOOST_QVM_STATIC_ASSERT(Col<cols);
        return mat_traits<OriginalMatrix>::template read_element<Col,Row>(reinterpret_cast<OriginalMatrix const &>(x));
        }

    template <int Row,int Col>
    static
    BOOST_QVM_CONSTEXPR BOOST_QVM_INLINE_CRITICAL
    scalar_type &
    write_element( this_matrix & x )
        {
        BOOST_QVM_STATIC_ASSERT(Row>=0);
        BOOST_QVM_STATIC_ASSERT(Row<rows);
        BOOST_QVM_STATIC_ASSERT(Col>=0);
        BOOST_QVM_STATIC_ASSERT(Col<cols);
        return mat_traits<OriginalMatrix>::template write_element<Col,Row>(reinterpret_cast<OriginalMatrix &>(x));
        }

    static
    BOOST_QVM_CONSTEXPR BOOST_QVM_INLINE_CRITICAL
    scalar_type
    read_element_idx( int row, int col, this_matrix const & x )
        {
        BOOST_QVM_ASSERT(row>=0);
        BOOST_QVM_ASSERT(row<rows);
        BOOST_QVM_ASSERT(col>=0);
        BOOST_QVM_ASSERT(col<cols);
        return mat_traits<OriginalMatrix>::read_element_idx(col,row,reinterpret_cast<OriginalMatrix const &>(x));
        }

    static
    BOOST_QVM_CONSTEXPR BOOST_QVM_INLINE_CRITICAL
    scalar_type &
    write_element_idx( int row, int col, this_matrix & x )
        {
        BOOST_QVM_ASSERT(row>=0);
        BOOST_QVM_ASSERT(row<rows);
        BOOST_QVM_ASSERT(col>=0);
        BOOST_QVM_ASSERT(col<cols);
        return mat_traits<OriginalMatrix>::write_element_idx(col,row,reinterpret_cast<OriginalMatrix &>(x));
        }
    };

template <class OriginalMatrix,int R,int C>
struct
deduce_mat<qvm_detail::transposed_<OriginalMatrix>,R,C>
    {
    typedef mat<typename mat_traits<OriginalMatrix>::scalar_type,R,C> type;
    };

template <class OriginalMatrix,int R,int C>
struct
deduce_mat2<qvm_detail::transposed_<OriginalMatrix>,qvm_detail::transposed_<OriginalMatrix>,R,C>
    {
    typedef mat<typename mat_traits<OriginalMatrix>::scalar_type,R,C> type;
    };

} }

#endif

/* transp_impl.hpp
gqAigC+6iHR1WQ22KWOJX0BiSzkjM9NSDa4tYwlEly+FO2m0nX4IGLGDoilqjQZ0Q8rRwN4Do60+vzQlLcDTblgm/1UH0FlcfGxvXqCaNQIM7wtBbzH3F31/OCBeWZIGBxavgO9XLYdBt6ICO9v2dcJjISeuIrGMx34WgX2zqSsuaHJk/iEVcZrCwULpD6EI64rHyiY7tFOHFV0hoC6gUMBgpOCfHxnpxgTFSIwlOcaKtnZ7PuouHy+hLeympynQQGRFsWHn7PGCVLs/C/wD8J3wK2TtVodX6hxpFDaWw87Nwc2m8Oh+8IFuHcz58K5pzWlQf11Tk9nHs4h/b3OnEBpYjl47zCFGaKs0AoM1vM2DfDUb38rdFXtmgQHwqT+fxmg8zhaO1pHUf9MX5rYCCZEThAExqu+jG6z31PWm0ziaOH+shvf68WrmtYV4M81N9cZCvk6tvBoG0qDHsaw0zWB2aQeimakbLq5rkY/9ugBgV2RIM2JwgyVqzOmXG1f3rq+7DxA45BLHm2uVTDRvoZHBM124gM6xZcsSMkx0qYkwagaIqKfZgc4fvYJCc+A8UmBqQjT9lF++AoZT888QiojCGQ0H9oGqDQyI5NJ0asmSJi/yVGUMbaKBT+kLJJEk5vUh9JCBRR+G2KQQUMdJxoJ1zLPAiy3T1FU12yftVqW4ioxbVdrvIzf7AVapIrJTzYPVV6PS8drKOboMK38eYDptiIW3vvZ4Bv7CC9o4HvPZ7KKhOqEfAuk6t0cxfB+UML5jN239eJEvw6T4RUaJP1KVXBzk9ooybVPyC87acpw5nwNkl+m3McFGD9wVBmf6ZqbzMF39Q3Fj1QaMtFjJFLoJLCz92wW6z+53Y5/wss/OzDbjW4aTEwpJqssmg+EDfD1G/YYGatJ+nKMRSCofiJ8LSsWeyRK6ckdH3uOnk/Blu5mJ8mpL2LH5dS7rQdMh8dT27DqYXf5NFeCj5bQmG0sWYZ+61+OzYiuGaTpdaT5rK67MkfqIydyYS7S9KNMS6nj2eOXSrv1Yb8fVsQAWiUPzZ1RNSDcKiq4LdbxVXjBUFDc+5IwRUGRXncXwkWzVI/Rb5zOqr4DyzHbumWBHQv/r/Gwq732nGFDM8MNKnHnB+QE23cbjDCy5W/hnA01N2Bc6MsLx/aNjzzShGje/5yabh3P45qzkZ+A0+/v1R+mOnlLYVxa+ayD9wMMXLJLOA7JmWwFYDakB4Q+yhD8CqGIyxWBosnAEYI7JF8wROzFCt9K26FRspX2Zfjlge4UJMQpJObIF3GbRct4xziJRf+4itAXEpeqOqsJu6ztWPj8hlYhU0FsYqJs0I6HPv6s5qNso/ao+AE0oEyrWabEjFhBFcl8oHfT/o+SdgoXhlWjBb9u2bdu2bdu2bdu2bdu2bdt7z3/mearm3qfV6U51KpVOsvKwkg1OFpQn5GEzvhiP7575QH7kMZooP4iFAHMfJT/ZlMRAHH2vjb5ipvIOygKdqo5akI0n4OKe+qCm8FS4OID9w1OIxQBieEQ3GjJQESyibiiOeJKdrRxWMyXAAUJKqlC5IfFEb+rFOHGa7KEQIR9j7h9EYWpdxBPzHGJRvJEu6uKe8QA0qqtqeQE4mu3s1Akgy+g79V5p0zPzL8wG+ROliCGJPqoB7oh91HQUJVrONHMpaH8uY1nqzkRxL9ewJ1tEPTklc0UPM1mkiJvMyjkVQJXRdqrw0ztFxAV2qpTTzGQJPcVECRapkUKWK26hZ4OZVs6ULx0HtM5ETUGrUeKPpohorJo6ZfLC5nRdzcjR/toRXO2Yenoi0Idjrug7cCc7FxzsRnnSzPWyIX777hpUfK5EwfVYsWPJkcLZ5TZwW/idKZR0EDdV7mw2CjLomrtyaL57uVrYfHYrn3Qwx0N5DqYcIgjHI3lO6z9M8oiC9xsvaoCdK+OlGCej8iT3A4o1cgUowdTk7/GhMkSnplUPLrGjzU/fgoKU/zUDONF3oRbcwt0v56/S3c/P7Y5zyAnS/DEn2FgZFbSc+ooOygmOo/e9K164OwVU4/RWeOaZRLCt/BNmW3GFPKLDYMPH3CdhO/koxdJmX8UdxOMujqBmpbqob06nZqp9NtSGbMcAIwIdmJPsawoL6KIuo4YGZZQ1zA4LL1IVLarPfcAY7TGBQojDJx0McKw0U4EbRB3Vo6814Q5FB+Z7ze/tbCBbMYY84om+o8+9ljByqDgDvc571DV1Je9kI/jrEG7kB0UOGpUW5GNPxtjxW8RrkwvIgI/UpQo2ohXiKzuQYx/bhp4rsA4WN8UjiAJD6oOZB8wbpICO8uf+bXJPEq5Di+AXk2bokoClAEiMV1iXuaaIyscLi0kplcgYBxWAT22TLOzrwBm242vu17yAQ9wM1vcTQgUesvcSsXv5FeWk68iHzGRPI864ZEQ8BaiZ8GBMsWdqduz6mlzuzTIgCVNxXId2D1raIVSaMe3nNXV59KigO3UI3/p1ytB0RvOebfkNkabphJJ1mtYzmHZY5yrrMJUzosXchvsDhDCyHelUPwBIJpk+0flI3obKIKUYV01d1Hz5B8zkFbcRBD95rY7RoApuhqooe80GP1CN1pQCT5LSz7ES6cJeFyMYzRg9qIur345RiSrHth3LjqYA2PagMzwimqiGwSf6jTU1QSrJkuyQdcE1TCeddh6BZQi8bfcnzoCuy7pVwhDVlvWEEMeYa9IMjLCJ/sUoq689vj75Dm24cljzH/HEibYjkLRnNyctxJReJ3LvRQZQGXAdbhiAIgG5FARfC7MW8OY4VhneibZj8sV8xDzEgL2B3ohBR5Vcj1mYZad/lhlWKLjT/00S5Bv1tQ+tcFw5xI0OQhdj2J1cH29PfxAYHUPPM9geeOc1hMgGL9rtRVcNH0XClOXJQN7VcRVoNiHdzEtZmFAPNfc/QOUyZPlv70agXgZoSrlN2ySFOFa1MBd5cw9CktAzJDKDEa4Z/O4VVQ8KKdDlW8f8Ih3On9uEIxXavcWcTptXDm2nD5X7cYaK2tMdmUU7Uhvob+aNJXzQxigh4MUyEfCitMFfNbHFjh7aZ/Od9TV8y2yPqYNZeYOPPg+L4ZO6FaX7YPwclfeH2DpX5MdhvnQDKkggKSTlMmMsJDHjNJBZfZItsKuS3aAWFQ0eF2dEQkIlmlKR3NsjvgyxjrqOJhsPQkTHEXjaPGpPoppMH95h7Jl+hz+IiSpdok4vJUp6oJYqbnKOzkSXIdTchzW/oVBdSwpxhcmUJEmfezHxjr48GF/c7K+cuwe/dG6b+gyW9SUbpInOszHkm0Uv3ZMDtUGklpwUoOWQrLPXgG91pGpYfRcp1Onb3jFpoe5VpxB9KZqVdrXsjs9CvlrV8DVCBdaM0ROJq+b8IAxFww9eO1XoVAnfaRGuWxgTyM9Yp1Rs2lN9lpBW9XFDSdd/XhkGcL2k29cFrB95onebrMdeN4+fQA1hnV8tLXYAO/kdERgfAWNFUUPiGrqyMaPHCTJ3Z97S0YHqvjUUjScyPrNym3LHUoUq1c+MuoYHKQ7oMvpGVAvW44wynS9RgXhhDc0PQbkCDyHumwW66F9AzOOnLywDRNCr1Wsr+Rn3IVdvL2N1DtSBYMUZ7OxDDJjqqyNyVzGphxtI3Lfow6XHCjKm23BqmVGGIYcvZ1zAqetCsoN4bTkDbDCaSu2jjzVDsK7aDu649crcXaF+WbKoeLepW2kWcShKPjV4zTywn8NtPDNYMvcBZNx36vexlB1FWkw9v7mwHn+tM1Ng+VYxLYkJNBVjv/fo+8FZCrziBYaAzSVe26vWT++jGvtckNTec1KD6xKeDFZT93R3Bd2lPO43UffAfAWqicOGT69qiN1LTkBIBIocFqocWwl5jnNOzG0T9KVJelvbjyspuuFhIT0GLgPdTq3SdBA0Y3v2q5pKHfzOB6G/cjYlLW7Ow5Xo2tOO2U34PF9p2n6ZJab1UOTA8ZCovKsbrmtY+MeZhOgkUx5sYRsQHNy0j+XfPRGoYvpiawTu7HWx9cN37fYKHFCVYO3rDFQm7JT3IYNtJN/jPtqDo13LGqvEU6wvHfwcK9ATquG9uQ1F6TNPT658fQq/I1pQb5MZ5g4ujn18ngi+y3t0x2HQEJ1kGWjl9t0kDWTUnTGuKcZaO/fmSlWdoHowLp9c0WzaWoRpquOve6UejaseX7lw2FaklB3CapvtaVyeXNxXj48gO2Dbjvl09JGZ9id4+10w5dfzP2sMc3uAOqNZGw8LGvuAVMW1a9WGEQTywDdga6jw5zIZeAf0wTAd9AL2PNcgwE0yFegE9+AqwMLY6wbjDNeDlruee+TGqZOwDSoPCBLhCa8ezmsl42pQzQXqwPLozI3jPlqvk63LJJzMA5oJd3IkmMW7QLrqHaeNE0K9aK8a0jrha9ajEV2deNDny8+Z0Jwy4oWifH6Z8Hpvh6S0O9ctoLqAbpin3bso3Ixj6njmdhVannzYl0nNPQ2VO6r/k83ldnOio/FfJLTLu0lE68fhZKKJuI3xWvQC1pq6XgvsQd6JvVYY2D2olxHxhLhZuJt0C5ig+TZzBrvMnk5NDzQMh4E30GDoSZBBqQ4cwtz2nWsDRoVSHTHAA2dN2YCPUz8yjJ1EV6pXGfcF+ALZwnQCOPNQbLi/nvYlUQdrigOBiiJBVSpsI+BoxdH4Q+xx45m2RbFWtwZrTOPxnE4lTOpEbjbMqRF0ZYtGurYwfuvHCrwRba2OEutg6y/yJqSDuyfPm+yDvic3OwbTz9TttDDcbnuENEeu5r0FM3YDV0XAK6r2PwPGirgWeI9D7OvhBuZLdRfrzHqEf6Ze6Tlcfnfc/uNTvnzbpTJwqdjzqgtuVexb0wPJkvrR9UPpxlcX8ubiBuQC6QrbUBhYHcUTK02+uP54lzZhcUayxhrVhiEJxInli7xmHZAdaRO30g/V/4u+8xczyNAXgBBL6MFXdxQEqw6hA3Giv9KqjVO3M0XpcXZVEuRoxAhcYdSiWxc03fG8iq7Wp4G+vWkLbKmXrkeBcDWhuUa+bgh2VQfDA3+FTg2rjpv9jfaoDbrzviZnlNPbIYUl+KK5RpGWdSaPGwiH5ClleWCvDltB8VR3M7bZvy4LgxFrBQh9QbMRpw6LoW/rU8dDtEtgG/QJrBHnhuwL0wB6TpcjTSWX62cdcNWnzdLv5z/AqH+esdetb4rIG5cT2hP4xJ1evCH/BuC9Kwr7afGquMBQX5MzGzA5+S6l6tPhQ9JfG0rmA11/ET/5oHX9YVQH/fp5Qb2Hft3aQD3nWLcz09qfHfD9+kba5lm3y/MLJAr6ufpSlQ97X3ur0cc41NvTC/ER+j6xCYJzNvXkvoBurAP2or2QMkYD2Yoz2CLoVjTD0193FUe7Dit2dYfhDgwhxhNjVa8/PHZdBzgCwQo04MrXrUeF3oKIAtaKNeAqUKmvQW+FYoV8xQ29CaxJ+dR0ofTIbcR6jwJK0OFvBZuFQs1rVPfAIbTTN20s3a7qBmDNkSChgMPvUqonoDi5J63uFcDbykxWmczax7h9Q7ITXAL38Xt1nQSF7pKqD6KQo7QbkAr0CTbwMmjTzyPcWjNZe2HFxi6o49cr5q7qhhmq+ub5o5VezrDQt+Rq1AiMkeGJta7Ql6K/5lGnWJeE9oJjhWjFGoLtrwrEGakHuq/Vl9Tkwg4+ChwpxRFzrZ3ckwp7B+ofLtfbDfsJVOjDDrUTu2yhldsqwA4dE7tQ5eW2yXtEW+ca3ZPyC0kx6qH5VP6g+p4dk6USM5hT3yHck/lS+ICPvZj+xrNI/ETwJl3vi8cJqhOZNq+S+Gmf4v4k1sfFCTsCeCJX5lkwwfUBRRu9tLFXP1pxpY9b2pC3yvzkGIZkHcisyg3EHrisGbnEaJep96r2WW6S55vlE/37JyeCf0XxvQhVUlLq11/oG2AwFaz3GTpUCQYcukPdPcNmgozKTU9PLWkWryp7Xacz+Es6WMkebYuuptlDPoSZ6jfmiDVlRSuEwapZEZZbUicXXMNXsTfx2VY7bsZ3FKY282f5DnP0Fg3jimPSCVXStx926ExZwp0jeSekVwOeUo038clALSfdxy3X48KCbYZZZiP+ttYx49nBHWa0O8GQZk/xVub1sjuPCZszWuBpC9fUG3MyQ21n4ME1VVem1wObZqXsTpZji9TmdJ7g36pd1bpGVAcd78KdCvsZkHpbwmgMXeI2liDNMMRYzkvxzJManyrwIlGm9iBoCsrzH/Fs5/6jslJPP2hjUBs9IVJMPRjLs92RO8Mu/4s/+dV+MtB+Qsj+E471+0JxeTdZWGGw79Zk7CZ/aidXw0hjASiZO1u8O1jEO/W1mmrXnfILMOqdbP+KxN3NOhgjUgu+pPnJvPI4xnSgbQjVFVtpiUHFmkhorW0cvFGp29i10vh6aWbOnJI0aQYbL4nmATLmm5wPs2Lpf1XiADtlTVaKMe2IdaiFM1EffmxSO863Avw6C4erMwXyYWfbAaNt8/gS6Ig0lfFv82bfqVv7sk+hkS/yxzDTAgYWYBQWYBjevxMmH8pzc4BzFSD8o52Y2ZRnESzF6gYWpSrKWRhRH1UfUJ9QH2HHfWBfxo9VzFJnynOAOKSxpDoke8TMkNSApTOVUUgbyq3eWlFdz1spdu0P0xBzIPsxWgV88chQ3VCDT6uU0jd//anEIF/hlfUSz83qwWSJavJTli0sleEh6UuisYDALhP6ZeYS7+rncB4vxY56hSQ+cebPys4wUiM2EZdtRC3YzjRayg274OjQDGRkK1OPiredoVirniziCJL3hTwhjbDshZoN40TucmQ3y1wl1ZvOKNhAWeGFWQhIB1aOjFkosZ8j19vAm6dMad/WUEwxnCsxA1auepDM007SLIGe85GuUiQ9tl22TC7dntHMeVS+xWshPdG/ncqEmj27XZ1OTG7DMumMq1IUfGREQRM+axEqMRbhBvbw+Go+ieS68zcNjeyGNVcRPfUpT5E4eow1okh6ylxmiWS5C27VOPAVjWbuLsSelWIWFn9ZxR6iXUbGgKVQPnuQ9PTlGwqjduuf/5YUKim/cV9WG1z+VnEsYabyy/FOPFKWzHqsgqF1Z/BLPCgergm9+Ui8DHRDj2PINb2eHuN8klHjTYfcJMAzhDTFGqVyjuLSLfDa9aa2yj1ILoxzFBn4WeczJsAJh0MX1AcdTVPuSd5D5o4++a3Nx9a+Zy/MeEl2pRkt5hSDKlZGuAwIJKv/HYMs/816zGNJP7gD0YKBsGw26hqo9MS2w7im3KFTkWTjzBWZAV5uFgwqkrAJAsMBg+5af7XULxqCVJ4sCyW5DzxKLgB9zS8FjWXwnUPXFU+fWI9ygD6SHjUJMctX/NE54JDu6rjPC4V8KRmMCqXMtVJZrArRI7ylSY5huZco2FAn8dFCj208JeZYkGjMOcGljnMcLeReyQh2bHqCLu2Z+yBJbZzIMNAG3Mp2PaL9yG+CsPJFFMqqT4Nk6N1RkX1oGGbt6KpCp/HInwpln2ZZF2eHbthMqWieSNIminEtmRVB7U10ADvSGMakqCkHGpWaJcyUQXMqNZj+FSnm02yGe8ATgYphSTwV/VKuqOakmNqxtFbx7MQT6J6QqQDt9LWyVrlz5rO1
*/