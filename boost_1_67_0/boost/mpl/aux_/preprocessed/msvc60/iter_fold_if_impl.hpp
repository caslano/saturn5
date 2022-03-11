
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
WduDsGSVqIBMFICIgdjo5BM4jZ9X78FdeUgiH+X9hXuw1o0UKyMRKsJUUYntpIN/MoQqAals38psG0EbBFg3rsjJzPTrva6OUTFpd/pNXjvukBZDhXwpdDg/0KtffoCalz4FlZfIBOrLehk9MRYlCbph/i3sZR/Z1bO/eDKBHQmUb4Vh2kj1Ol0O/vXsPbiEhEXLqOwvFiWCPOwYYq3N/sK0rja7wbS2FiNnzKLjhQ+TOz56ue0jYihvFVvV/NOfodgGrt8aEdvKURm6rM7AfzQRmeU55m8FbepodsPiW8vH4oXcgtc09/EadjTjMMz0RhJq1dFcVxxpwwv3UqmyVo/1kDfHSVfwee//EkPL7MMwK1nljabqfeRATwd7Z2oUuiRCYDLmEVw4/QuB/jMSHbmQf65V4rET4YNGy/d/Tjkqa/0FwB1TSeiCqG4dqGMMx5uGotUMErX5Jz4K0ilGYHNmYHMt483TjjcELiUu/xWjCDEBaioxFxae9J5tazStpvuDr5dtrd5kBw9fgJF7mc4THoDlqgGGJLiRrp+Gjnuc/EP47jXI7lZvokuaNp0fw3cj68TiQx28Fl/NkNV7jRNm/9sXsJ5Mh6dYnmXm1pOfh70WLDvSxdfTJ6NDnpXGHzoDH8ZhFWMdvByruA2rSHNK04z8J/D+o9oVTq0mUfPhDZkvBg7AArlAKpotGJfWSlQO5JBV3oqqQ6uiOrhbXfxLPSFUmUxbcR5sdPAPRWoNsU7/Vql8y0HbRmJm0j5kLFl0wME3VsxipToxo/lvRVnlIPo+Ykz7EINZJU04V3e5+Aoli79JKm88aNulERPkyTGMFB4Hny8ydCQqcK1FkQFMeYZIf5b6FU9wfP/maL+PWP1lZu7V6C94qWwRO19UJBeaAcCGpNWVr2v4uydALMDqVUtr3LxUQsyDKehpZm+uetBA11fybadh0h8lH+PdGGm4IVYHcmiV8/fPGnLvPQLyZz+sR0AVmjKV+JDuPdHZs77RwIyAxZJ+ggsTjO8lWC4yqam6gcH0Iwj4XnocBKD+B+KwdqGkFXbe+jj3BfgNpp1JnoWs3GzaeUy2aANf3fXUjWiScspzMxNc/My3iBwXau9Tb8Kun2+tJV1RLvi1aUftiovXLdEFeFq9Yh9aiIpgrbXL2rIwu2HRNFZiUOMLmXYeflZ/Hd0HDuXkguaFgYtDlySadtZ1jJAL3oO3xCXXJx4KY87auo/1U4d3Lsz+4MlGWoxCs6XAEueVxMQT7+dR2FMEq37sk7V2dya12Fw1O/lcXi7UnbX4/O68fmn5i8975GlGb4KD34+TPUF2rzDtbHQVSyDj/4Z+FNNAlDhE/MyYj3gGRrZVOvgPp+wJm3aOcMoV8L0SBOpKSMAvMOGc/Jb7kKfneu/yajzcdTOh0toyX8XH5+zgcf6sPoW/jackdzSadky/uzXQZjLVTE88l13nvzGwP2EhLvVPlhLyYbR7YLR9Nwk9Cd5Kre9ba+fx790UxyFv1+Se/v4w6K/jKEv+Fhry+V1m0pcakh6GfFL1WrG11rcMbtDih/Z5iYr9EI2FE7ThcFnmt8gDRm+mK0FvSMSI1KX1kXhm0ftfmivGM3smN2q/Ia53VrkhcL/GVFlPIaoMapDCvh0fEbrN4Ci7g+CiOZlrpl0RpwprJsIqujiSTbXQzRDT+xJSMMFnFQlcB0ogfE8ve+Xm1zVRd+X4R6klHGxqqlcbbu4Yh42IVNltcBXzJRc+D4OcGgJLkZApamem75qcgY5Uany44We6BvqvbM6N8V8bgCDZ1mbtcuAJIuO5iK+G7awTrUJ+A/nIfXH083BD0vIvf6cZ7CqOqP1AmDwtDUnI8FheujccqJsg5etdzoZ8wf2KU+RCg+TuqSo28Et5eCNhpBolvnjuFe8TKat7fbOGl3ylBDEli2RS59dvaPiyjsiVEKXru8KXBVehN8GqG/LTEORARQ6uM/InOPio3l7SKmqRFhvycwj6/MlV+RMa8s1o/kT6/NfXvVeiz7F5VxMv3W+A5aj1DIzDAamkkeYzW6oXeFRRV4qCo6rUUKTQ6HKQLh4hOGAOQkbuPRHPPFqgAhmP85fdGOH8Cj8vS+l9Q1PG734Tb0BJNt/6qsZ7h/dhfF49/lVNmR6+eumTET6VxvJT6O9Xr790+fjFJUaKZh5usHXSu84hYps34e6F38COspDiRDXW4+kbYGH9Upx+vHiNulrIG0Zo0OPnas4Lrcm70v1+VtKBSwzsiHI6rbynwXaO7M9Dw73Are1G3Mm9Fj26tyLQndndpsp70SunHYgGvmGghi3oVt1gqrxJ+EVuxowhNN2OxIy1fRlfgy/vhns1moVZ17JOUNRlu7Gy1jdNNH78s2KP2CEV3a+8E5mV0YHAUQyRiCdE/cC+h5MP3PEqWoFwPwV3DDF6A9UXTq6941XhToeunecfOA9Kvq3TQccBR8Nb4ABom1yEHxRsxyg2wWffTKxsDJ5LwjsN+XbKbUBlscMiajzr4v8moxCmDomC9WzUdm3nHQr0+BAPejFee/OuwN+BIciFeoVkKJypE97VS3+SRDyMfpQRx1qL8upkb7TAg/Zx7hOPwC844XsuDj7hd23uHSgv6YpKNZa5cieQzehylC3QAA/D4DoRrwrR3/a+/g7srC0F9IKUiOOC0kkQPTfh5Q6A+RSxw99A/qpin59P+jUOkJEK9pMgMS4zuw4MgH/F7olaYZr1pzy9VE8eZabAUsNYf9/1dg7e8FVvvPsOlcK+xPaTCRgh/X8wniK6SWQ0xS2myoj2G8/6pva7YVIN9KcZB6mR+69CV+TXKVMvDx9SbApFwvQvtqJDkMbb579gWbxbg2s2o6MYWCe+uI27DbQDOQx1J4XnSUsx0uVicR+pgf3iHJ1dD7coN5V2+ncTczNgjoFkCzzjLOQgbhL8OcYiHaEZsoJP+WRzeMB5inLDEIw/711Rk4pj4f+uuDc6h276weu/55Ql3kIazuIkcri7X31fmIQxqdOclOsWtj5NS3HWXcqd0Ww9aTJT9TIpLwdXYv2g0cxH39BLveE4CGZ5q2kmoD/XUqiifiD+xf3WzJCdr/cnSoWwlMNjC8PgV3a+AVKKDZBiwKteYJllCBeiN4Z/AsvXC6+OJAYs1/8VK7RIFUapwox3wFfo+RcAj1Rh6Xc9mvAHwZINSUthMg5e/h21fH2c+9KurorHLwkihGqQDrd/SXQ4P4YQBf09MvVK8f8DFWaNP5PlpwAm5UKLk8+H+ccKU9hxXctMeXrzhaWjyV7Jis2SGRAU4OaZyz5nFWZrLVDMulq6IDALZgIbIqJXo0vLHL10bTjfKC8x4EaOX700DShy/IDZSOd/oqdinEDtwt8D+vPbqVe8T/di4KkJoKDjTSLyHAOfPgbSAAYOjRtYEivQF4ePR+AxVSaTDxeCgv65D5BH8HMYk7eY1KK7e+gWXTzwp/C7MeyZEM6wcDMJHuxK4L3N1PSvX1HMrSDhMaHCzxYZoIBLz8aKG3vDLeiuJE7ipZLsOisOfImq5VWPKoFuBAzfaHCCcm/Ay+PYKtov8p8ryO70jSg7uWO3JuJGli/5z2XvxO/Lq5mf4yqgWFTA/Xg+iOCydmVRlorrxXjOMuBaw8jGhpvzlcIdfZ5Pfq5s9xDaRjCnoTjccgV9SIxI9B2Epso9dJWhETdDPusGIlmsl/whxHsDjk++Af2QJMzjSeluqaEQF7aerv1a3x3s70+jN/K4JxP34B9m6wH6knNexuY9Dv7Nrt6wtrwn4wv/XzruxP70y27vUfPihUe8AeYITKVviiIteE9ngmQLYfNTtOKIZWc7YewnkBP4io5XwwOAPQXAlmwXMCe633cMVeyB1E3asril5EJ3c2W9Lwddk6Fd+i6VhJ6+RAANabCFCKTyEHNjJ3RhHRq7F3wpelAS8rd0zJJtnf8XnLmkHlU/AIBDS719bWBU1bXofJwkJ2HgDDpg1GjTSl+xob2pQV/CYA3KTIIwwyQhM7SYxHuLaW4e7UOcAewlIzgJ5rAZpLeUYq9FvbW9qH1P2iKJlmJCKBM+Kl9WUbCipXVDcjVAhARCzltr7XMmM8lEaF/v/TNzPvbeZ++1115fe+21oAoMvksW8xOvn3pAF3pxQEpTGUXU7sOGOmhAod/hkmZhOfRl5s+uB7nK7fBx9QKt6qhjFizq9X3Lxw2tZxuuZ7cdB6gN0kkxIIegLojkeW4bq+xBj06v3LQ3KKnmLiuoYJGGXtBfZKXp08F4HqkR9i4/5iUukUFY4d9FNOwhBhVpk1SvDLTGpp+3KMHcVWPVfHWZbJAwdZmUcKfnl8PWlkkFx2MZ65E6ng8q1Aah613O86GzbK5DrbGpNXa1RlZrJD4LxqzWAKVd0GHQw6P3XjXfbb/aQHkP3IDDiMEY5oLNpYyMUxAjSiTcLAZg4XGzSJss0tsBqC8eESFaXD2Iv1PY+6tw/Shi/hRMDgv4O/U9kwgtU3seZj/Uk3cZ8Perw8t6eoyCNNdZUNa5JzRJlD+C6eQteifyzKTvnX4EUfdX53TUPQoX0N/HewdFviKlEUN3do0D5BXWP6ahbvbsq82musXf/ZFJR+OeinoZT6/y98bjSdbsiwahbNwfnBqtPMkuq/Dp4ePqThrXunM4rm4aVyGm4PJ0s8uEyVDjdapRKWpcoRrlfMo5HJ3SdC/aiaHm+6E3GEwBIQ6svwLKi3ASBKHKU4A45cMQR1LzASOXSTQYEKBoAIA8xqnRP4zHPagek9KUpWkpkwcn+ZP9lSj2l/M6J64BThzgeR8LiTBGPl3SyHxTpvsSz/+MtEhgsqNuX31mvaVuP9yW8ZZXiOijOV1nYUCLgYUdGWKpM5DeG/pvOrPXOSxbTEitXT0iV0lQQT8+tL7MsAEjocco5qO0WCb7qK04qQcOCaT+8GeZOhLGs/q+a8gvhE66dRIIgtwzMKihg8pAbDXKeagHRddtIln8Aei0eFpo2WLY0SgGiIiYoTbY+LZPBrXoXMw6Y41lDEBl7ocuxjJ+AZMVXZdtjkeA2TyJYphMht/WLDqonQ+XKFSpm6fTq2L6LaTfqfQ7k07plpqx9Bz4XU+l59O7B+h3Hv366PdBKr2Q4mWAikiDQPW0eXOO2ZBkIp2aupp6shp7ssZlr2hejVpM8+o6VNv/fDa1KYUOka06jbA4/UqaKVGfM828pnxOycBkO310eB2mOc2UODzn5eAN8Xj7cw1Ev8d5GRB9HY1wlPHzj3uAshAQ2Oqp8VxCBpCdHSS5doDkuo7AOgrQ+X9AM2LiBPyNDEdPG6GFtlKBTfFzPuyNIcwxVngpYMVo+n7xzIT1Nr0ihQlwFWkePnlV+wbynmquOq8dcXYojV/Cwclo0IB1k6sdKqriSuN1FA9FRu9Rz7FyjFlQmKZp9daKqKcTt+7z0/A8v8xCnXhMfjwagsXphHwWOqAulljokLoYXr+pLrax0LH4uxP07iS9O1XG7p9CKL/YBgvRJQM4H8JEQJjE0M6uq5sEc4oBRYGyjm8VXqquVhZqjbe2g1pro9Z245funVNGMuchZ8cKELjPm4Fq4xeg5TgRgA/RGcnER3eeCOFJrU6f9hbGRNHeWuM6n+wLSaRhTUeKhynpRXPifExNzX9BkfDJCRPhSTURhcT3bDQRh/zo/vWyVZ+INpyI/7DiRNhYVZs+ETZ9IrJZ1W51vsSqOtX5Mqs6oM6HQofi796kd8fo3Yn4RMynibAZRw1xMnQRP2lCquw0J/HGHNRYNjWWgx+Kz0NT2/IvA+Hwl2G2u3/8T9wUf7JVIL3E2y+gzqFbtxJmi0i2HRUCpOI2nbiPmK02mq1DI2ZLJy3ZydMVf5pyvjpnJudHHDld5uTJQi6Ek9Udn6xupfG4afiqsVgSV80l89Cq6f47rpqv4nlDtYonTZKLw5vx6OZtFsBECCNA/0b0l1Ohv2zS7UWuSwn5z//y2fYiWBFDm4d+TBFUAjVW7kRmQVbyYGadySTDZVcGJb6WTfyWj4cIJJ2ZRYsJPGPEclTXsUifpjSWUkAEZEUREMAaiyim1C1PY0bODO1ovWztg1+Qaw9oR62uY8xzIJojizR4M9G2w/fzQfRjcx3DKAmo5PSqHgzDMEUcjdePy9+KAZLuxVr6Wfmx4gEuF1+XQ5uw6VFsLAyN0VnQ7qF8rN1WVy/GY+pkMQpPdLg/rxMEFaurD5a3eIFZdqOVhw73H+4rz+v0q543eeFvz2JcGeY5hF425ooAxtTgAyD1QuejlScKtHJf3B8FxHoRhcWwSR0B2W2BMxb8atHy3ODtxtMd5wdJ3KzkrOFUvTnvcDmrPJF3KVBWzjr5c9B0ZOcOyol9k1/wKarIHzsffxOcGs9N3m3dYqqbHmoV92Yhz9TXBfjJl2Aqdk+JlgRRxD35qZ4ntX5hfUaZON8P+p66Gs1kNQW/F3vdPCstYV+V5FV2lm0kswDlZyw4XrA34Dwavh39n9lyGdh7hrNBDo4pOM5MM5z7VnR1jfOJTvP3ujWQxBj1uKCtaPNu3AJehxGvDA3BIxfNBQVvuyEbZIvD0qQjP9OHISOwbiiL3aBu3EGR/Slxqyo7d2JEqNAYFpDUjXjZJQNJnyuppdKQkLERD1CrN2jrdlN8N7wLzRTdgW6PZ9oIeeQAhZ+j4pup8uY2+sUqvJqjPELxNvUhdVnYPcXO1TSutf+Arh+bEVKhTEzP5EBLTLKMLuid3ZVA72aOJmFxRlIQbu2cLNqJIpKy7n60Z8xGc4qIQO7hQqIArRdJJFDHmNI4Vmdlpwzq2HBKaURrUgIf+whk5HprgHKWDfD34U5t6AFujg6743FXJU7+dhP56yTyd4BI46H4uzfp3TF6d2IYaewBpK8igaJhdIFiKwttjbe2jVprpdZ2JAkUhiARSxQkSO9IejSMNemim/YWc+FKK1ZdJ52PExzX4hF0dq6IZjFoC+jouvMcHQH/6ZlBbRQjVKskbRm+X+KxNe0N+tkM6W7cawhm3I1hRUIuNkOO9GUG7470PRIsjPTdHCyI9H0x+NVIH5CBSN/Y4KRInz34uUjf/wjeFOmbHJwQ6ftS0B7puy44JtI3Pphe0IYnEVrNxaaVCUcSxH6nrW4lLEg//+OnL+GGFWYKrvPRkwPxJ1mtFqhaTceAXDKG2zOjD0vS6SrDfq0VS/g5sZ+K96VJ97ZYsYS+ZrFiOpKHr2RTQj5aG1lcyqkLPgZcDk2LF49hqdblyfBq3ZB8z9pjpm3wCL6ATevy9DTXZ+2n16/g33gfZqiHHKt6hlTUr2A0mg8GtVg6am0xd5Badi8XB6iH6ZodSSfpq/UZvsbvv/PH0b6/DL+f9OVYOiqO1/59PP8RQA29L1FDn/BzlET7QENPVM8L2vCQ5YXg9aiRRz0DZXUDkq6VD7C+RLEtSeuO1SR8j/wfVrVjVomy+Na1ftx2Twp/ieT9cuptCvG63mTYCkJyXc5Kk8lvnJP/Rjtt7Y3cJdcjadxbd+i2n9NmPZ5WXhXDoJwBvKWjzDv+siX+jvYPcfOwW0+jyqtCou09o3mcGOOts6VhO8mHePdUp/Ing/EWPHv1eLbiREw6Gmx92QFMxn4EeUAO5VZ9Y+gsjHYEeHF8a1xY57ubMXc7sSFkG6KKdqSigh1kPXGJS7+o4NvH0W4B063ozvPwzYMi1UuqbY3h/iMBEenvYDyJoVxzB1IGhwno4PMmI9MHHudBmwPyM75tKspAdtzZ2kimylJZXUexlX2w+h2CN7NSSSVOC5wID+gT92XFNnU1scwyqTy6DuNY8p9nn9Nqtpqrk2MfDMH73UT+KI++42qL77FOgenkmCEouu7ZIQcpfTTCyLOFRAwJuJF4Ui9MPhI/VnBWT1cfXbdVaEdp/NcvntNiFLwUfYiM123idTrfQK/b9NfRnTisWAZ5vpSQ50usJJvs8w3de0pk41syX7H1nKbfZMYyyAHmn+FRdF1vvKcjkXeEP8jX3Ff1NxIgEe0ClKxx20ZsNfaVHId2om5pX6Kw1SiR+fjRd0hziK3G5zSI1VwPY9CK3kN7qJxJoIRKo1cJRDxtylnNgLawrTw7dO21UQLn74+niVr5c1MKupc8vqfdif6rKdfbO2iArSs9vcVUf0OBFqhr/OKLAGxYEc+HXyXvlhVTQb4GKfdZ434CSgEgh5CLXBCKo8TQgw91Eum82DABmoC/casGkXkG0/08r+0NLcooPHDDQHzF3E1x8fbz9y5THh99Q85suIycGNrIEy+H4uxhnGUQXQAvQHK5Xuiwddz7kmCcQqixFDWAOvseUIgAeryXGd8/oVOAAJ/2HLZyApqwkTgFCqajTDuEewrUgtUZC2XVWWEMvP51GEAlx1dkm83Br3D0rm9v3Ks0lVGAt1OoeJLASCtidc9Z4ZavrL2Zgt8eg8t1drM493cCb6zCMoJHAMVBfRAcUaOuKKPl87xoARM8tAi1vN5Ujj6+/Hvn6E2do1/P4JZuuBpGPW8qGzqG3Hcajwf/BfQDUnFmul9CV5FD5Xwf1XcEqG7GUN1DygaXkuD74xIV58Aq8EU9B8r490VFP1WUhyoegI/GP5i1skExKU1ryOnrhNDWpUSLyH04/qpjyloMMVKAp7AEuBMFUz5SVqWt3WHiqy6eJj69oy2VkTaKkTM8dv7y/9mjpeiS3ockI43oQ/Kj7uEG+aE+JD7dak7Vh2T/FNzvNewNP/nDVf1Tbi9JOM/U/BnxUKuAMUVXP080q5nKRz1r1Z8sRs9613rB5GkbnXz9RNROwUjR5w/utQnBKf9OQsHP4hlvBXePdE9iA+pDjYJKs9VvoiQH+p+slmAUhI1I2mIz6DRrbAa6p5soSOoes4lnZL+gCWJNqoo4Sc6ETlkq6UomsDyhPP4MHfzVUluMWENiDeKceC6dOKdaigGZ8eKhlapPL86ItmIIjd2r9lBUq5+twOZkf7RUEthNglnlelxn6TjOYEIaFM8GcidYGjmr1T2I9N+zXqyS+eQvvAHBCctofXkFcaOPw7rT3HoAt3mIYuvNPNN0ViOYpvTVI1fM99AK8ufh/iAbSq4l/hwamoXkMtmIXKW6ukGKwqPWLu7TRY9Z67eQWzOtW0vcQvB8kjFqN56k8vA1xwQZFquZVfUojXiMtOk=
*/