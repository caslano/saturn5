
// Copyright Aleksey Gurtovoy 2001-2004
// Copyright David Abrahams 2001-2002
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// Preprocessed version of "boost/mpl/aux_/iter_fold_if_impl.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl { namespace aux {

template< typename Iterator, typename State >
struct iter_fold_if_null_step
{
    typedef State state;
    typedef Iterator iterator;
};

template< bool >
struct iter_fold_if_step_impl
{
    template<
          typename Iterator
        , typename State
        , typename StateOp
        , typename IteratorOp
        >
    struct result_
    {
        typedef typename apply2< StateOp,State,Iterator >::type state;
        typedef typename IteratorOp::type iterator;
    };
};

template<>
struct iter_fold_if_step_impl<false>
{
    template<
          typename Iterator
        , typename State
        , typename StateOp
        , typename IteratorOp
        >
    struct result_
    {
        typedef State state;
        typedef Iterator iterator;
    };
};

template<
      typename Iterator
    , typename State
    , typename ForwardOp
    , typename Predicate
    >
struct iter_fold_if_forward_step
{
    typedef typename apply2< Predicate,State,Iterator >::type not_last;
    typedef typename iter_fold_if_step_impl<
          BOOST_MPL_AUX_MSVC_VALUE_WKND(not_last)::value
        >::template result_< Iterator,State,ForwardOp, mpl::next<Iterator> > impl_;

    typedef typename impl_::state state;
    typedef typename impl_::iterator iterator;
};

template<
      typename Iterator
    , typename State
    , typename BackwardOp
    , typename Predicate
    >
struct iter_fold_if_backward_step
{
    typedef typename apply2< Predicate,State,Iterator >::type not_last;
    typedef typename iter_fold_if_step_impl<
          BOOST_MPL_AUX_MSVC_VALUE_WKND(not_last)::value
        >::template result_< Iterator,State,BackwardOp, identity<Iterator> > impl_;

    typedef typename impl_::state state;
    typedef typename impl_::iterator iterator;
};

template<
      typename Iterator
    , typename State
    , typename ForwardOp
    , typename ForwardPredicate
    , typename BackwardOp
    , typename BackwardPredicate
    >
struct iter_fold_if_impl
{
 private:
    typedef iter_fold_if_null_step< Iterator,State > forward_step0;
    typedef iter_fold_if_forward_step< typename forward_step0::iterator, typename forward_step0::state, ForwardOp, ForwardPredicate > forward_step1;
    typedef iter_fold_if_forward_step< typename forward_step1::iterator, typename forward_step1::state, ForwardOp, ForwardPredicate > forward_step2;
    typedef iter_fold_if_forward_step< typename forward_step2::iterator, typename forward_step2::state, ForwardOp, ForwardPredicate > forward_step3;
    typedef iter_fold_if_forward_step< typename forward_step3::iterator, typename forward_step3::state, ForwardOp, ForwardPredicate > forward_step4;
    

    typedef typename if_<
          typename forward_step4::not_last
        , iter_fold_if_impl<
              typename forward_step4::iterator
            , typename forward_step4::state
            , ForwardOp
            , ForwardPredicate
            , BackwardOp
            , BackwardPredicate
            >
        , iter_fold_if_null_step<
              typename forward_step4::iterator
            , typename forward_step4::state
            >
        >::type backward_step4;

    typedef iter_fold_if_backward_step< typename forward_step3::iterator, typename backward_step4::state, BackwardOp, BackwardPredicate > backward_step3;
    typedef iter_fold_if_backward_step< typename forward_step2::iterator, typename backward_step3::state, BackwardOp, BackwardPredicate > backward_step2;
    typedef iter_fold_if_backward_step< typename forward_step1::iterator, typename backward_step2::state, BackwardOp, BackwardPredicate > backward_step1;
    typedef iter_fold_if_backward_step< typename forward_step0::iterator, typename backward_step1::state, BackwardOp, BackwardPredicate > backward_step0;
    

 public:
    typedef typename backward_step0::state state;
    typedef typename backward_step4::iterator iterator;
};

}}}

/* iter_fold_if_impl.hpp
3uQaFjWObAffeod/vWBx8qajPdy+k3npL8VeuUOsCqJzC/Cv81996XWJ6f0zkh22Uis9g9e4y5ZbzghJC9qKgf/FI4EXEoKhyiJTPEkZNHTVV0tVY5fdjT07AW7GfS1P6/xL4qIoo8+qskOyuqlFW10QVXnU553AszF7bMpE3g2DBzcBew/uPwQeXTrUhjR9idBCK4pjlovEreWOQT9mrhED2iu7uBYAAiz90/XVdnxE7c4Y+Lx1+h/kekM5J5dgTCkIf3DQVOsZClpkxgvc57wDSdNOjx9cRssPYyiGBYsCsO3YBX24qqZy/PbOLqtAa5xklMn7GK6glRhEyAuxugYAzZ4u7UOYAzSvRO8lT//RoXYRx6U6x8/y/jCg3s2BNFY7f/PHsEbRidA7kWk838kvujTdyHVM1Y9TnDPsBNX1APcw3Lzohhk5uALJxwxHQDRG66P2drVYZeeb6SC4VNTsWhN9NykI3h+KD+HRE2G4ubdtUkN7CdfLDY6nH6t2DPNG9p271owj+IqhFWnFvE/QcrcqFnUX3vmAz/0nRz89wp/1XX6HvHZdoOqW6kpFdDD2oJCj8gbmF4wmJmNnsvwQwdc1l8StVDLilTrrQeYYYaghULZJb+33g5NBLf8MFvz6mtlwmCx6E/x7pEMVs4Rpkuuol7Fv01gCjQmepEjeLAcr6rNI5bXvObx3v149UuV06NTZjZsPzZ4ihbY4mlUZ6xTBW4fv8iesVJwg4C/o2nOB60LH6bJqInGk+ojdrbPq7ZbDztk+KE07vfIt4/LNj/ygt7zz5fCT4AvgjzqYAmmDJ8rXwHgWYWBURwaNjYmOGWm9OBmmZu3z9Me63XVhTPAW9Y9XYrcJvKasXby9CRG+MGbVP/ntiql+A1SWVSm3TF8Tw/eWzBrFtZrwlDTnGyXivY+zS7e4DnwgwZaKfVKrLDAlMiAsh7EF9lI9wdeqgHwBNEVbacVlVPF3faCX4KuSazLvXkOMxDiZaVnCpPQH/rs1ohqluPLk5JHcii1DVegiwqfL7KupKYUnDLm0JKtW8laxIUAga3qp8c4qU+8/vQg4PQxsb+jtf1d37jO4ho8CbgQe7QePIZU9RniM1WnTtFfND+kaFa+hY95XLH6RRMbxlBYlXsFTEIw5sDXjY12uoimlyVctEWr4GMRlPR9KvhvO5a0i4g/zr7blLRKDyw8zwpgx5mLFmkPnRoisUdocgOMl9ecs4TGSMn3lRagGSjPHNfhow3qC509KOmr/vvEqlhfaKRbzTq8eY4/DfHqySb4nP8+UIZV69UHBg1YUy3Ex1aJL2sr07t+cLWktGAndpCQfhr+NeYxL6rc5bXmZunHRkU05+q8ytY4FF7IkjNgz6IMp6cH/Ee4PXSA8Kpp0H01BLA5VZeES6m31nyHFSjCCIur32kfPz+oqLYQWFq6dKgllR9sLpaaVqkOWhB9QOCv5hitNgnOroyRYdfUROwRqthV1Mws7OIrZnLAaknzkojTIqytBKvQUgFr6xztm6F2Yv2Wlym6hH//UV6YL8DsbYmwomflDj++PpFU4ck/cnLIqP1ed5rakjlPnB2METbQOLx4uiQmbA92S+T9R9QhAy8pb9X32eLzJiyVPkTQYUUgxbcKy7xLl5otvpE5yyxyBv4pwM1BaxwwJD3U1xWasVBupSU6sBmfGZywzqiV+r0lY85Gcmvv42g66r7Jc83mUMFf9K20sOmdgVdayu37YOe58x/afnF9bFAJNC8YlyLE57KuYZzQieB7jlPOxrRAvVO+wB+Ckqo5DqAD3nRnDJIh0FFWbAmOGBYszw7YdxgVItuG7aCun9CmsOJrhDdYzXmX5+rFskjnyBtRxtBqrz9Ro5hBu+AoiS552RhJJwm/p34m6qVty1hhMalsGkO29iM0YHFu4/XfwFzcwLmGfUFlFeGuh34swu/cFVvTcUGD+OyU/iljwYxjMRvzEcggHoCY8JaMHzwZmo9BT6oRWESRKsgrDhfZb1LrOQ1qhNmuuKWkcY5x0D6yZHlhVcsyHn20v8lZyQLKtZ/JNIin0YgM6l+g0+jgSo4++U7PXQ8c+X8ywy1AQn+rV+HhdqFIXRFrKD6h4GL1rTjccnolUV7lgVdMRNh4l1TQ3d7G+PALuMFzITRK2N+YnXL+srqyUJxltoLAeTl19Nj7+unzBFDZJMM2oSXAwfV/BTmkXtgxOzZTAAd06wRrRReCj3Fu1KIhNsKtz50kS3kpFRVX7doMnrbJPG+kV31S3QSkxsljAScfG403EK7Q0xMlmmLvecNR0RINlBmTSHTD+RFV9sbWjoImdNWJ5de8mxu2c02bHzpHH048fdfI6Rn/sexMpqOiDuv/xInXXdR+TrzmDXekWY1TjUNJ58D6LqOXGJ1Nbof+HrK1ke57wdPreJCz2ygayhG9JI5azeZzTJvs3A657dJmY1vU4+My4tTNQNZt1iEOfDEnCce0nml9KqrFlfLuY4J2AQtIvE1GdP6rNqutJjEeH0vYZjAOqW8no9kNNa1o81XEtP+uV1IZHltn40BR3obspe2ZnTmzuhZv0LQAQAv9q5vkmhyLu7SfbRqsCVXFYOdEzr0MWQ+6JwAr6i+ZJmvjxZcvma3cWoQFb9KnRZYrzmo93CzuvG262dSDJt5gcCPbNxYwfUj0nPu6/OsH9Fsd14YyAe34u816rBqs5XVtbIvYF7ltRDLyzanToUIPCN2CzhakCUz27PU+mxVWY0WkfVsIDqgJ3B1py1dXsYtpFF7NT1g2PVnF+SgJQqi+yjEYurBRY6tHrw9LvhRRHendhHdIgs4f6WFLQWA1qya5v0ovTZ/J0cP8zmNG/8GYXgwJrdMMhZ+d2080wO0L36M7ezRM9l6v2qwVg7rmPrvxpx8OW4fUpLmONBOUtDCFXS/cJ3adqjid75F2E54sPLAXu+fTjch//HtQpWJgHvbeoPBwGBO2ip57HKO1qj2ZVbXX/lMJiTDUL881v36Ju+Z5CJ00XUoY9g2JFsCWS40HA77AMlvw1+cy8ifvUOhxtYB+iOV1UG+i8h+W0Bi2Xt4JaRno2bKVa9L6rAwHR8NTwQVdToCXE1pheqKX2hTEXDnwBF81x08+wzP22Uq6ErZcHx0XF+/3WJRdRdB2+u2Ph7Shl5GrjvZVE8TEccMJxHz6A9Pg6okJvNEHk3htsJTRtYPCbK50QL+TKD4IwvOoTdbbZRctuxZStup1ddL02Z4bBqrWpyUv8oELo1eIjQK+33GCCnb0S89RxItlMsrF0de7cEJGjjLTUj9VX5CNzCeX5XvqsVTVygaS6V4Z0FP79yII1pzL8pBB0GFf+b+AlHYH5ZdKFoMKqpfVaGGRT3glEWX3MyumdLQA76G51au2Qr5u2LNiF8mo5oR/+S02Smgdlsgxu5dPtT2Al7rYdFSkDhmzeU9m54eAqP6+IW9sR4btsdCqwwAv6JIp/myGvmMSj4MAVupENcsdXeAhAv8HN1boCyFzfVB/AJ3ugaOW0FLCcQAyumtC1Vgps9yNWMOQ7QU6RebN3txM0DMJSYjeNODzRJJ+LPzCQpGFepgRyVP/Q77mZ6ycwJYxEKhTo9oryh6arLPUJqhhQnZosUZ3BqRqt048qWp59OrtCSXPC2Y8hH6ZwJXiFBE+HAX9G6vZs95zosqUgxpYgKESJY6WolqS8ZcSWYU/CP/jlA4LxlP7sPUqcaWLFnfx6OiBCsyoEpxemnaFpYrWeYq/fP6dzcqKqnfK+SRnFsL/Yu66ztnOkupTWI3M613JU6kLfrVQiU1f46dhs+5tco3wrpeev1pWjYg8xJLO2syoms5TsPVfZ4az22cd9mZeVcTkTdrcTeg9pVQbhwm9NV88266MfFwutB01JL0s4ZwGuc6+Gh4P2vxQEW1URXL01pm0zc00HXgmN8zR/5WotxsXsW3vwmpxVurFSkt/LGpuEw0zhDbac2O0suWq3g23A2MEzJj2tRkGMZ8AyrtLKDSiTMY7ie4CpEkBxCy6OTcGpN17sW0lPRh2psySpDuMESLz9i5y6bQiSCd7amzAuAGAB8rnPRq1u59y8Oxs38bvXpgnu3YP+KWmI4HCkaYB/dMACmiVtUDsH+R0lRj9/U3/4B9X0ZezILXy8dVz3OMMjVcFyF3CwdxB/xjGZEVVms9th10a/HNklaX4AMJf4b5PRgggvyvIsrFKjUgybsUekWI83n2X1+i8t45rjuE03Py+Vnuq0V6oCIziW9GEhOEjSwQkQ1Z8CK5p1IuahdvbVC+isiLk768qvSg1lm3h/SUUm/CqGr/gBVAteIEaQdAZ8GXDDrl6S+f4pIt1eFG+SY3CCY/gzFVqV+ddqhu7LynxB+hYqf7h1zfyC0oMjN3d9J6x4yfQc1nv4tmLZiqPP1fLLTJJGCk5zGatmigZExCM/m2pAD3vSoP7oqXGjriQ22UYAQ36NrTMTNX6Xu2sE5Nb/qJg6bXiDxFJQM7gKVEtIueX6j4UKfwFJC+r286zcS5JsuzkkXAOE0HVeKbXj6CpoOGBQvd8kufaVZUR8XHW8lKH38/05jh+iqVtdIHTlSzLOvpjJCbtUca0cKirXGsDkRlK4wb6FezMJb/azkdWjOi5zvH6SFwrJ1/pTyGZXzbWqmg0i0yncFSfzuBE9zoQkQWNX9qDEqz0FWk8L3rGBVrf6cuaLaAscwGs9NlzRPfCkwa6XvXxE7ynP/wtkwmJUeu6KiemjMkVga99AuOqbfTPlchyurKDqryp+jn05KfTOdQK8NoqMLAzPHHBVK/5ZkvroTSouo7Y5y2A4dACjSQHQbM9nV9GzPzHimnfPy57HUJJZjJcOVVepum+1H2Q6ybCPqJS9J34l8wWCJumeOrq9XOvhrJlHdeDGgbZurWFaUQXyxomiB0TtSKBUXWSx3lj1+Zx7LCwa7q5KOuuJT8MoldZwkpnygRfe8gXS/BsngxvtR0ptN9WaQxkhs5WrbMdL7pvd/cWNIzuolVc+i34fPcvaouVp3Av66yXPTqC5HoXiD3BUaqvdtPEnSneIG+nnh4/ciP8DRYC6f2Or/U9+IvXuZHKwDjQrzwaLqZwRU8um6gfLal20Fdou7bR2VSugR+KXjoVie6f/1hMYWY3ChotsMhO0uAN0e834aPxjjjFlF/Ir5huzC/Y5GTypAVlIUoJvl9NwVacWF5RTDvFikr3qf5OO9tmH7GN2fsd2WjtDnPXOeeeJ89FJ5Ua6laE4poDE5InGUFHdvwCd+dFvLrkrazFVsxFbS6kVwI4Mg8Lcqb3Quulz9dVQak/1RKoSYSnyRh/kuDnmGvMQMsYp2OQlaMxb5j0zD/KdjLr7odW+WLVIC5BKLVocFBIHebmKek0rq45e8G+8v10J31TCre6udPe7F9xaIC7JW9FFQpFahIpnYpu/y9+HmHpM9VF46kMbaFHreUS7BkuJrZfSq+ut9G76bP2Q/laXU2DqGR2MzcZ59RaiqtkAXrPe3GnOh3eUIQugeZ+oKRmEujQ5om8kG8rusPiwD9kZeCnUzTl8W3Y71C5rd1B1A7eRB7jjOaHgpRJOGWjJ5s485xgI4qvbyOsBTbMdvvDAKybkJIS70AoL/PXqXCgktJi6H5XnFV/1goYPrjtp3DRqmlkszXKQA2KTpOQmeYUvqkYH/v/mWq2n9ZisXt5pn7HvgV7aOp2gUQY418FrSVwBG90CC/3lFvLaeEe8a/jrlUQ7kc0Xfnm/Gbxwojo7yBVsCi5Gzc+oUEydA1XSnmst9XH4opv6Zz2u4RhljFbGMOOHkRP8tR929tjsbU231ll7rEQkFclMcpOS+KZF9BTNz8JUhVwXNoMVAGNt4sc4sefb+/92/JGdeQvjK2VF6UpHdtFoA/03F0rgOJRAdC+JV81r4g1TVfQFhBB1oLN7g17Gi8Av7jdQXY+fI6+kA0FXDTqBJYup845J2kQ9jhGuqgheGb8RE3OalcyO8Iz9oP4klqyIbGGNt1Zbh0CLb5Dp8xJCKpOa5AhW9wMxVEeYHYgKch7QG1qbDWEz2QYWjQuo2n/5HijaxzwB4t1du4MjJ6nLLkVyGsx0943q6lLSG6Re22aAcv1HjBJT1CS21yKxb/l9/O2KF7/65YJLUfXa7aP8SM5YZfD4CdDidzRdb6jOrmbqh/XL+mN9Fghsm/EcK5/XjDSbmAPMeeYe+NAr86eZWXWSlXNKF6nuVEVVf9+xIN1r9AOtxEaxCewwS81z8EU8vf3cLu/Udk66793MWN9jXnZEZTmRrbeaxRnXz+f39xf5a6CxcgfDlD2ArvoVCzml8nYW5KtaWlOtJ5T2WG2B0o8/tcR6Bugt+cWj9VmgxivQs7Ggu9Oajtna3AGfv4yvnG9twZrftOZDcUu/yggl4tKyUI6boERiszSsNKuLGDWdbWWX2X9QkEV4Wd6At4GvDeRjeQXnlbPDPaF6QIVBeXTC10uqigAfDlT6SjLVCf+nn15pjc7IIDNUb9MbYPKXyL3q7fK4YiH3FGPJaR9ttX7a5L8vkkKNPkp1h5hZzLrmVeiKH2YKKx8U72f1SqcgomkV1TFkJtkLBf4QXCBruoaCzhcik2yll5E3Y7PUjLFSrDJ+S3PVm/QJSL02b82X8G38DL/P33BqR9rj7fX2EfuS/dL+bTdzujnLnVPOCyfu326X79w/blWvoTfEm6wmsMmOILYoKcaK7aKm39bvBOWxEFEjA7yWgjFaBKNBGXvUGW5UrpTd2mdp6zWqh8OKrun39FTguvdGlOpoZnY1p5qzzZJWezDBMqiOL8iOyUga/ELZj2oMWQb9kV4xe23amMrXOj9pNJaSZWQl8dtusveM8qK8Jm/I2/JOvDsfxSdAPa+Fn+/gV/kfHstOZOcHF9e3+yAu3rVjOKWchk5/8IH8pW1UXzZZRZbCywv9XBe/dKq31yshhohpYOS3oKpqiE2ye1eMoBf08Tjw47RAVuQ9/Dv3K2of02iaFgGb7KANhO9EnRemBcdyPUIfoI9HNlqjP0H0ymww1VdvNfb4tHHPeP339WoTs58pp1dnsjyrKFRAK6zIZKzHKeiwkqQfGUXGkUlkGpkFLbAIq7JKrUt/upKeRkwYhzw6zZ5lz7MX2cuQUWW/oPv2O7BCfoc5S5wtzmnntZPILebWcWe7m9W93Gu3BGy3O37vAs8XVcRk8UMs8TcjLiQJSsJuh0exwL5i6lxDvprbpT3RPmmaXlmXp7T5DN0QiHAlVHe43sYAUOBoxIeNRmwzhSknXX40A+jh8lY1q5HV2ipIa9A6tAFtQltASbannWl30E8/OogOU+/sTtOnlLII1hBxYj17yb4iXk/iN1TnirHIavPtzfYe+7D9xP5oy5r/zqD7Ce5194VbzBvsjfCmgXPiiRwiEPVFd/DdevFQxESM3ibr4VTV7GNVd1BM1ZgU0Ypr9bXp2kLtnpZTb6F30htCk8nzuaf/s81O5nszGaJaUauS1RFKeCjWfws5RK6SeyQGTUBzgU5jsUheCZZXxq5gV7Fr2HXwnZOcy47r1nLbuavcde4md5vsKy4eqBnHo/0lwTaw5MXgruyEAd6PirvxtXTq5GgkrOewdlK7pL3UEuiFwN1V9BrQwA1AXVPVC8VURkV40EhjOojhkVHLbGMuNRta3a0+lny/m4ZlZ4WwgusQvVpj/abxWeDHRaCXq3Zm6MJeiF7dkd12u59cDlXeUJwTL0Rbpf7kdBI/KIbdl28nZa+Od8Enebfxrpi6E4qpxYe66axt0kL0mvoSkO4bRS8jjIXGKuO4cd14Z/wyCpq2WdQsD4sebm4xDyN6VbeagPl7WqOs9dYV2HN+0hNrOY7MJhuwlnHoeGQ32TdVvrkZy7fzHzyR7bsd4ZtLVKfjrOKpHxISod7cjTEmGe2szlYCRInaZCVZj//hHQmjPWkOthbZJTdidQc+gG/g8Z2kTj/k9SLuPPj4MuzFVvcBMqPjzcP/uB3697A4I25LzZU0Qs2aGqy6fS/G70up6+Dc/UY6eOYnM7WVW9X2hjAKvbudleMdObeL2mXs6nYz0OtO+6B9GryT2MmJTLzMqeD19VZ6/3ndRT8xTEwQ88RaUQk0eMl/AWr96ccOsgYkqAJ2jfpNT1V0lHNdEhiVzPpmc3BCf/hODau/dcuaQ36ScqoDqOysc4ktsIVTwRnqFHCLq/OgrJ7uRXp1vFR+F7B86iC3ik4hWoR6RyjvXboh/u6EVT3QQv9O/2qj99DnQcsdAh9HMxIbmQ35gs43IowqIKt1xhFw/FpzE6gkH2lGepGa9LEd7rRze7oD3NHuLLe61xYetx95T84ceyBrt0Ij1JnBSPydvvo0aMRoxg0jCWyhmNkS1HMNka2qVVd1cRloTbO2Wm+tMeQxPcDesNn2OfuzPcKZ4Sxw1jl7HeKWcye7P9w4XmJw6mfsVgFRFHwwWCwTW4XsvSLJRfJhxF8+HALFekJLoZRqPf2M/lpPaoQZnYx98OdjxinjnHEJv+gW4u0j45kRw8xtWiDHTuYI1VflEHKsnBiZwapsdbUGQZsetM6DEFIQHbp0+d/uy3FZQpaUyfmDYfYLu5sz2zng3HTkXchAN5OnecKrgPzR3vvX++5Fiuog20nijYjv54bGHAp9KauRZf1hhKoRSAbKKgN7W6Ct1Z5CrYyDGtisH9BPQls/BTkON+YZBw0fXzkAiuW8GcfaaP1UVWbDaBqnLMh6OnSfBqaWd/xrxR6x1Fcnfu0j1JvXLtoPTSqM83oJZJupxm7DNkuZQ82VVnSeXqma1vwS/8JX2Rfsr3YD/G9f3OnePnDuR9HAHweuXelvQOQsDHrZrc7mIhTX/tZqIpc1N0aBA28bw6BnZT1YTJKSGMQmZRTByjrzPmQkmUzmk43gkzQ0i+rEVZN2hFqYj1h/Syn7GFjP4qw9uHYxfHcHtH0alcnX8pf8q7q9y2MLewoy2nVks2rOcKXqFzqbnVtKGX53MrkmLOUiLGUP+KSnP0D1IFrs7/DP+TQooTgrQp0r5dHCtAHQrWnUdAvHqGQ0hi2kNDOZRcx2sINZ0OfprN5WEeKAC0via/fQbnwrv8bj27HcelDXsiP+MsRyOTflGnTUL3X7NRnZM2aQIWqN5kWourlq2mSs0Qm9sFE=
*/