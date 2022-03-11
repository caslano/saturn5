/*=============================================================================
    Copyright (c) 2011 Eric Niebler

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_FOLD_S_HPP_INCLUDED)
#define BOOST_FUSION_FOLD_S_HPP_INCLUDED

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/algorithm/iteration/fold_fwd.hpp>
#include <boost/fusion/support/segmented_fold_until.hpp>
#include <boost/mpl/bool.hpp>

namespace boost { namespace fusion { namespace detail
{
    template <typename Fun>
    struct segmented_fold_fun
    {
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        explicit segmented_fold_fun(Fun const& f)
          : fun(f)
        {}

        Fun const& fun;

        template <typename Sequence, typename State, typename Context>
        struct apply
        {
            typedef typename result_of::fold<Sequence, State, Fun>::type type;
            typedef mpl::true_ continue_type;

            BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
            static type call(Sequence& seq, State const& state, Context const&, segmented_fold_fun const& fun)
            {
                return fusion::fold(seq, state, fun.fun);
            }
        };
    };

    // The default implementation of this lives in detail/fold.hpp
    template <typename Sequence, typename State, typename Fun, bool IsSequence, bool IsSegmented>
    struct result_of_fold;

    template <typename Sequence, typename State, typename Fun>
    struct result_of_fold<Sequence, State, Fun, true, true>
    {
        typedef
            typename result_of::segmented_fold_until<
                Sequence,
                State,
                segmented_fold_fun<Fun>
            >::type
        type;

        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        static type call(Sequence& seq, State& state, Fun& fun)
        {
            return fusion::segmented_fold_until(seq, state, segmented_fold_fun<Fun>(fun));
        }
    };
}}}

#endif

/* segmented_fold.hpp
TZ8AZSMu6R4x8dbB5qVWr/wscd0KcvVikvglIZGRv8SQ4OstfiXaUVhnH8C2el7M0/xYAS6XnRgtJiKc4az83vff95g7O8nJAgPP166uhYPXNkGimw32rpllnDjPLoqKTuxJIqIUoghJ6BtD4A+oP0fepj0rqjNcFM1wTYHw6aDq6vQcSS/v+L9BI5TlQigvuQ9BFQKD6++Mja/Na2uRGGU5MDQS04DfiYienjc7T/aabEYPZ4g5FEvJ+SO//GlWoa+pSU2tqdE+msjFQBHKqqjIITNhnDvOYHVbI1NzYK4tvLoaHDyUQUdH1qvez6pTV9s7ZuVI+jmDJvpm9R1fxlnGN/lgJvZEcZrR0bKyLAOpD9avCKCI17ckMeXnmj6YPma7kZqDVK/aNDTEnMqly8sYcsa55Yzu0Haf9vYdv/0a4/V1LQGHF39gMj6jtrZ+3RC+V2VlxUQM4/L+uBR7zvg4Ke+0eMVK6GvaV1k11Tm958fkH/SO0n0nZzRQMdb4O8qnFx1BZwZVasb03DF/YbANl/MhXX8bPKX6XPRFOd0e6pRrjonTWm12FRUNDBweOq0iIW/ZaZqeXZgb5eR1WEWpwiOVv79DZeHmQaG97UQ+a3rQDXYLcaOt9/1XZpIxUtLHx6UjFTVKCaqkOiWl1tbpAVnTuxAP6g8f5sbHF1tTlNKXOFBQPmcezS5z8NqhvTKXlfVHS/ghiQ+NHi1xJ6KyLuzvLxn+982WiVxrK3B5o7+X5/s1nG8cepX7EyqqeQIalSbt/HxeT56l7hcbCQmx+Bl/yQV+/x5Kjp7lbsE+DbSHXkdgSSorG5G9537Lt4r6vbsQ+bEGw8vrDQjdnUZM7OaAnPzkyLQViWOo73urkMDiP22G5wfrFtwvX2qN+Lw/f6yQrv+opa/v32Zkqvs1W8iDgWXfxk5fl57xYNfG7gAXLOjTfCXjfkxDfmgPvqVIdW9Bhalh3JUzkulpVta9HD3WthYr3WO88OiYNxBPvAsQFhn7i4WFChR3txlN0ypJSDg+iY/Xaq7r6Pg13SvFYf6rqIiamprn969fRdTi4sL+0IfwcGad9zmNjeHhv39HRra0VOr4nCqq67NgYkzmq6hhY7IySUK3tpYeVdSTYkIzlaSlfQW9e97nhB13e1DfHMBCKNBaYzI5W1XgY1AIDF5STWnkGbYTUcxvdH5ayMrpult4umPVNzRcWvn2FXqV/OcPz/LuqFGNLB6VuHe1fhV0j5FGqiqfS6pGn6Vp5b8PH+1ep6W1tUVGhoampeEzpqVBoUTs0qUe2Z8n87q6BgZCEeb84+IxsQYmXVXHJe8gHtS7yP4BlfCwgbO/wueON5ycTrzU3lyb9Nxm3Nz1cj9dHPKk48QOjbSbMmueXCCaOtXV31Yqz8r6q9wqysPzvvE3Dy++ehQokMuHI5BzoXq5UanyFmLefH76IUqa4fmQzh1Ypb/V1TsFFCnRtFFFrX25wrhLCR6TQaNAe6EJfs0OlDQg3ul0j8qD18m79Pdn1l2Bz/caErZdFw1Trp2mf6orR8fHe4p+uR6ok5OLtH/96rRqYqrV3lA7OcUpKspU0SUuJkZPz3WZrtFoNPfy8fNA08BmCMTZdSg4uDAIdSG3Aym4rpahO/QvUgWuCFfQneNg3OKOWeeTF06k2yuUt6lKBRxymOkKFdxxdrLtepjVGFUIvH17szuWyWv+xwLxGPXo6GULCAAaGfcDrGHBDwHhaVhol3fYWNDt+HprLeSHaZqHr39tzs6wsc/PeZbrrQVc4gZ3qX5BZv6FN1F9/FztBTaKvfuSrOF0Jtko4VzMoayGneF2f6/dDSt4gT55PcnmCQ+e9oYh38YuN32aohKHTAW6yaHc/MAk4uIUdVopVUFFjUBNJPc5SsvICJPyvH28qSAnwHW9/6yJWxDV7snMCJhCM+tss4mNQM5rfoXap+jm5/ucWwBfNsROKQP8wgJ+NdxchydHRyCbmLT6xAgLtH2SgNFeSiQ01CUftLbniis2O3OfexyMDELv6nbf5OSOKs0tznKW/ow7gHVCSGDj2beYJBKvG2K7rNo68GGHT1mDU7Sjamx5eWBgqq6KVXDp79/hg9F0tx3Nze3Hm1KVXjHow06tKZjK359KlEQIT8M3JeThXOS039e/QFwteGuMsx64c+QH7pEk+PB7sUGGYhEGZXx+XG9PeK6qW9qEl4FEFU0ZebIyyI8xieSj8NzLJfFznodT0IvlRraycjyicp7TrMgZNw9dS0DxUqxn3d37T+pbfezS0l1K71NqgOsjjxCCLoarGyIA6XVrgf0a8yOQjq6eZGdoydBAjrLRfBHx5MS6IxmUHt/qFhFycQj2k/BNyZPUwW/NqjEGguwkLKC2tuPxxMQ3fo/QwAWgkiL45kp6Hbm6LPW/hPdLWkWp+KL3dHmXcqGm5KKX2DwF+fDc7gX5VEdEUDQoLsguFc0rQhOIdBfsufjKBnrmO+6VctlkgHlf0R60d78kBiqqYD6mfEG9fgvvB2EG+jwaHb7cNxEXXWOBrs4cfmhhyIjZXw7W6h1lN7o3IQg+vAkefwmuceBtgl0sSYFCee0PA6YXASCEBPzdUZCY9GvvCplJ/DnLJae06VdGDcEp0271s0OLbvhW3Zjp4D/GPPkPmZtOPIyNjQ6yG/Yc7GFijCBDvyFLQbMYfz0ndcDqgoAEGNc4O0PcMIkQ8RfSnz+/YPVOHm103iK2uEVQIBRkCXAjTiFFheC81ub2OUUuoky6QC4aus3bBryF3CNDXJzeAReXRh4EnKygoOCRjsuAixlOq0mKhbfZ72NFe1z+m10rt5bFGHwWwAUvRaK/ErgjREVVj/36TBqEwO9i99pdc5YoMJ1+sW4tTlEYkwCWvJ1nHbrrBybcLLBP+thPagIpaYnn18YXz5akOH6WfTFJ6IliN1Pl+Flx6MVx3EyB9iRGINL99FT3TPXwmOqjWUV68XCV4HNu8kQFniQUI+EVmqROVq2wCH+U8SE8LnnZAeUd1JrtlYMk1Ne7C7uE2n14X9mN33AkLIZdu7trGbG3FsEGwywYyeIoNS4XRy5zsrnVfXyeRCK/pPkoKll2GC5b2Zob/d0hitEo/kdob2di4LlYQBX89+V514LDbNfPxcUe+nzP/foF1Z22qek2/ulSpiDKdkwQCDXDeeMmA8D2f/w3jetGezOxgwRDSIx9W4DmH/SOCfe1L6NArLl7O5XjqR8o2p2f37FRKCTTnRUBqJyYqC5sCBKpi+Dj25VmYfWTQDh+gbhSZ10UkyxqDkgECs5PJg3vnajoVb5K4MgeEocjf+VYKRxuas5U5CLTyicXRXU0wia9vi6trCwEzY2zMaEJO+oqoj1gedyMKP40wm76pahIItxYN9VHy66mAcxJl5kYKyEiAMP29xvspBQSjVpwHe3+fF5OoQkKKiuD9/e+ruaF9W5q2ARNKlufHD+2uICMlMxhD26HvyxbeKx1t+KgsxokUpcv1mPHP3epDpH7RCUK1Adh8olpiiMlDw9cG6EIQyJ2WL6EKmMxaBUZGcpR3g1/kuJLysq0Gxoq/fz6v9zdfTAmJpCsqbabCDcycmz6XPibp6L18Xj+IZC3IVnC7lmAH4cKy/GwB/Ga82BKBhuLSsKuPdT66HxI9WaIfDNIoVbOQK52ZDl7LaKKVXx2Up1t6HDw/K2dPbzQ/wqNKgRt//mDgyMf6FrJMIVPKOeMBpGa3rVxl4FXPj4bxer5f2FTOYMQhybNTyd7Y6PINR/676M0CFY6K9EP/HdH7r1PA3KywF2IkJ7OzgjUu1swjtV0EQDoWkop+vDk5c7exuIegIPTYiQiEi9LAsLBuUSW5ZifJ2xozsiIBggxg0C3+Mar8J3wLlPm7IyOblSscn43Cg8fxsvIZ4vRVBFDoamELlQJ2bR/1tWrDzo+eewMecScklEABLlRicsGgCcxRIF2OTQyzhsD4yKeh4Pxt/Ezeqm8jfU0EAv74astsKSZKr3VmhW3EHNsZN7XQtDjV7BFY2aJtSGJH2NGHAU8jBBqqKanf1cvUGVn2YapKI8gZ2Smp/+sLQNNMhZOAw96EINhi+azxOXlChp1zZkUUy/P1K7R2M/HrO7cjBpp8NW5zf/5RQ2xsJUzGx9C3enf2JhMCiTwdR042x9q6ezgSo6RDa9LM1FXVy6mBhGSq0wyvtvzUnfclj0ez9at+ZY3F0cYGKKGLVFXnyqqHSDSfXHvRMFI2VIgXlo3sQlLIszuClYA6H/vjwaJY/G9n9OrJ5Z5lWLj59154BIYXgsrj/al8PZOWF3OHj7aklKPy8O9/zoyFhmVGhCXxACIisObrmZz/P/M4Z/6Y4t1JqMQl7WRqU+OtNGzM2EXlp3VxJwkF+vtt01CIQUm41v9mtY7C/oVsbG1ce0f9u+2cGTPoygiFWW7vVNH/qXlfe0US54ajMojaFWx4X7s4rYeEZGTTyP+93Hk+Ue5zii8dFbLlTdtSamLcMGb7C9T21U3Mhox7XFJC7Cjk/f02cEZWMpqslJVS6Z6RxwhyrSfJBZQRETU5th9EdUtcfOszdwKMFh8SzdiXz8ZFh9f+k6IJiBg6OxYWV0ZHKnpALiKikwh1q6MbPOYc9s5TNfV7NmMenK/VOt7WPsd1YEeFC4qBhIjE8J7dB9YXVbi2N9VqsiYf33RJCffDzs7/eO0k47VxqLffuuHhk4DeEvy8SPa3b1d1+asxwBaAmZ9VmCC4WdLKfWRjYI8XLTvweoV3a9Gsm/8aBK/rKnaMXj9oz/u8HuQCEq/FFttno3eG0B/gnT4WtrePXBfv/DzH0ymbj5eq1SU0Akh+CYXU5qYODoW1da2sZxvZ3ejUsaf6CjGdIm/57qsaVYUSce8urOF9TxISbj6CAiUFyblUwqRGhgsbF7fM1y8938fFPVV2V1Ler21Q9TRrV7TIMnrJxn52am/P33abHmvsnKpBT2KeZ5MdE9IzOCupKjo8fE0Dh66EC4Xn2CdDbOn1u7QiMDAAFddnealn1dr3qPx2jswrOjjDBXYelpCMyP1BuMRUHxOdPzfjd5CntSxUZnBoTTiv/9FViGhsAjjpr+j6G6Li/GDAs6K9E5OVFT2U8qlzS4q9LfIqcqk3XUuTuzbEAgjAI/EUP/LFSWFiZEw1+DxN3HUq6vb3pgkBuBbqkk9RRv6E1Fw7dszfMLBV3xSpSSMQKx9zAfO+tdvGYS+jJUEu+/mhqMDdX1bNH0mJ86OdB4c/fxpz+XiOzo1Cm5vTZrVGURce/pLKpmZKlo/0La60gj6HqgnJM+UCHzuEcJE/9CKN0xJlUQBSEIUfTNJ2ZHl+hne4ZTX3eAov2vqpozU47qBurn5+39MfvDdf9zZPsxFgkiNl1ha7o6CyyPWDTg5H5Yh92n4T/fGle9ZlBlEvJRpR8excF6hHsDko1kZGXKytbVv7DpMjp/W146PdX/+ZAHC48fhYRyGxlRtbVZWqcrbOnlee5za3Kur2bJiyu1tBg15mGbVzQ13sC6LadMmbKfbjbq+XrcpJydLUU3DXmJ0/IeGoh3Ds5K/cCvNw0hW9sttugkOLOvTYnhEaqJwoCAXl6Ag08epgtDQlpbp6TbhEFiH6H8vS83+vNV3ePjfK4l+/nyfk4Znvrm/Hxm53BAUVGeipF7Aj71D+872H/3pLQODehZCHV0iAyNAJNjRS59I/4Elo/bpgiKmJwQqgEMvls9yS7f1Im2ar5QuGLzhNzywOyHgsq6sFLb5rzdiZmZEnY9fXuH5oedZtlSbZe86DqOUR0SE1upqu6JiuSHj77ZV1PffPAxlvzSLP36WnSCJQjKj3RliJqj4nJ8aZq2uqKg2iNMin56HlZikrhrJktF23COUAjslvj6cab/AAYnbjFTq6JQlUKCDEk4/z2X/rJ0cwY1/edkMkaCT4QDx2m313d6GvPU539ItCwBtztU60FviVkbGyFU3MY09Cn6PSJNpV5U7pE6LnJRhXImr/Cqvnd1YOrQkrOlJmz5ZUuztIJzo2KbNkvHdDtLZtegx2nFhErCQc7J+8XTw6UPy3uP6VJBE9DOktVsiJIQ48/CwR3JAPMhfsuen3sZGOgPKm8CbxDrOmMyVlRmQGSLi2Zn10MND6CqJmP+u4rhvWGWYD/IKwfFRZQXLZBhagw0UOkHu6MHb/LwVPRgfcK+rzcJp3oK7NvfHiZu7QuZbGh6pgwVCHA3PvyF5hlxuOtq+xcVlIXp6WqsnT4FmdHxa2m/sN9fXd4kxIxN39/e3CTGCXn+Hh5eFeK7nWQU1e7v7h4dHmd8TvPSMoiddFRQkJVU4bJ/XVvydCrt8WW2e27dzxxdwcSe625ZbIBTy/+p329fX+P7yS3b26GiFdVZWy8eZUMTLfVVFyZd4MDjyzenE4Qw6ejpje4uvLz09PUNbu4ggPf3nDaxXGu6rQy0Xl0rPrT5izo6OH/8efG+tY+kZUK9UShvs062zuJEPvOWaeNUt+X0fr2v/i+yQiyPY9THhXS/yJJ5Zp7L67jjpkKnZ5Ie5PulrPONm5+Xw5+T5KgGnp9OGriBrKx6e2zsAEAfNsAF12cnlYr5q68vWbqPdRCR6xXNqDhn5ybbVp9yCgoy9Q7TCOHxGGx7yXGzylVURP5RYm0GM47R3cz/oL3HjHMu7J2CTYR0Bw5CamoSbg8KtHCwYMNhMp18v0tZ2VwYDM1tisy1DHOnTIhEBU5Avu5mJZqi/8du37d5HR3cnBweZufGkUiLtp5/zBKKBm38mNkFmxiLeA8P9EFqJkJMFy/4f/8LDc8h0W9jYBsTaDTs+EbcCLrnBxGAm4CCG8mCG8zRo6gsmFNOvMJOzUk0toblYChwyokIh1NcCOaMTSMlVcbZYF94fJebc/3y91mpoO9cZoIj2kwtydrKjox2enbTVDx/atD08jFf//QtFEG2nEv6aYvGZLfVrZn+mDltthWAAkReLeh41xPWBq4C3uhoDc1SihxHFg9Y1S4BHW1dk59yIuDQdZtkBezLQJ3oEDplqSW0mbFs9fTldG/3cN5Q4nl7+g+t1yfDpXWSUpd6fNG3JHshmv8Hf/pIyVI37ij+x/tN4Sk5OFkVdXU13UZixsRUBbo/X92cvTx+MzFrdt5B8oz8tchkw49FMJUPAkj0SociIw78CBBbsmX7mQ+PB0VKvpaVRVxsdo1OcZrtX4n5pHbIOzI8p4UjuyMvLu9ILtbbBgTO0+4P2k7v+j6EI+1LgaKRNCkA0uQAq9vHs8N+f9W9ZLdnYL9bQ0STz48sYdKt5BWB7mWsml9gTE8QcFZUzF4hQZEHcSyDY6lJIENcV61JAy0QkSJNEI0Dk2UsHf3XnL+GfqaPZtdrqhOHOipiX4Gfva0nzoMFqRWWMnUKJwmB0S8txQDLlmGhR/FiD/eVEqrKx8TPkYnl2/HRPpZ5krT9XwFVwwPF9tccgxrc8CleEi81CEQUJhPExUhJqiURIRckbGKorBZiEy9kfoq8rckKTCvvo9A7gsYO6urMmVPsq5p1wpqvdFwybENhl+N0wCqg2HXvIZLM0ey+c49eXglsLglxZUhFUqRT5tkltwKw3I7RKDA9oWOI6+tu8dimVVY4Al2DEE5BFAVlG86hE6E7PPQlnBbA4C0Oci5JStDaZinuS1YDEx4tv9ejS8v75O+01zWpzevzyr7AreBkX6GdF+0JrN2nTxSWYJfqGZVr6qhFtMBvdL2R8AK0LQEW1Swl2jSEtKFUZFdndT/Op+EkLuHziu965nECEXF7S7F9JPGMdAAcJ9fh+mTs5USz6nF8KFkpMvbqdkrQWpeEVQLwvGAQavFin4NcE9+ve2BHoLfHwTc/t0S4igyo1kMaV2teI4Dpv5DnkNMDCZUpwK1RpWPpJFPpycYu41J4pjpDJmR4gORXeIHKtxcKiphYiv9l9cBV4n2AyfndCccDHJ3pua5sQsik+1G0N2NlsjF3entPdHyTmLDOXVsW62dIpT+MgEUgSHYBHZwrzB4DlvplBZkeEoeoGosaDbxoQ+x0AYZtY46HFagtdveLjAJVCEvJbKKmTCyPwZowz4eIv4X1yOqPQuYrKsnjA/eWN0ypJiB3DI0IYpooqPTFfAH8QrbS0IE5wMnLvVVTwaQCXJ5MfgJHxGqcP/yxPyJRy07cUj8UYnQJtKHb76Zhw6gS+g4w5TagBelpSHBUtWVcHB/8F5jZ3y3Bzw0DRl99249TAy0JB3NuLzf0XbGzSzHzTxWzcB4vAwANYAMVIPHHcyWz56eJiXYPZv2zeBMilpbuWnNznwg7Ra55c/tR4RTXbOpPfkQdhS4bBn3wFh3tBe5LiztESY2GuyQSz0UBSgyCxKQ89vY4LZva9R5cpqq6p0S0vLt70g169qkPi3640L+FWVoI4rxWgERgKgFa3S1t2VIyr7pNlWElkwIcEfWxsFZVLEhYWfX1l5YuNyp8rS5LPt6mjPfYVlUIiMs/3d7c/np60hxN19M8PD1cFBLOEbTH4aJF+lhFRYp/NMtIg/vzZFtiapq0QHadsRNZoUFfN9jGZShDo6el58oVVpBb7sLLoUvKwmHDmmiTqgbQRh+A2hzYukLIVgIzMy5tgJCbmCgRzydJekgQ9GRpyice++VkrbvVGV6Z/FP3sRyU8vsjl07myBwfPFVEfE5tf3sSgOaqqNjtTUpKRxcbumqWlL9dW3MbfT07KB1RVgJXu1ts1xHszME6Z/E+fIX//VnyO9O59lQiK4z0xf/23FMOK+cQXkNMRRxFbzx0kqao60p+VkxZNKkzwggR5Kmp9/766uqf8o+PKinRTIwXFNDyqODuD/RubOjuLhYWth7WRkUdhkZGXQbJvmmXenfpcNDb2xH7P19ZeEj9ZlJmfb3aybicg3ILdnwdBBeUnygvNOuOqFKcKKnYf9rGnuNTUluzflYJCZM+1lGKbdHYNdgewsLIW+d4PPEhmOFxzyXwpMv/omJPD46yi4q4Nr92ZRUSupScnd6M6Og5dIrKDXNnxGUIhM7N0jKXlxFTqOEzCOTlfB7yN6sPzdO0YVvk4k89MtZH0DGCvAe5SkAud+k129pYdbX3nzwOUWb+vH292rRwdXRlZummby+s0zi3BkklAZOSE5Ff4yTmz2NjU2/49JCubZjM=
*/