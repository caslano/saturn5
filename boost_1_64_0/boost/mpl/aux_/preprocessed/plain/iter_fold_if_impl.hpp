
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
lzEKX8F5+Cquw2O4Af+KO/A4PoZleABfx7/iCfwBy/ESvom1pf55a3wLA/FtNLUbkGdUeXbdoms3sEjSn4HNMRND0Cjb+SYplxyciLk4HxdjOi7BmzEPV+Ay3I43W9o7yHMpdpP4tfVuWVeBNy7AzpiC5vqnJbKcn9Qz1dY/DdTMV+7ifJUyX3NJh3a+jZb55LkJG1WzvpA81+KNcnE+o4vzFbk4X8kV5mujLT9dfp3NVynz1a1mPsNS19YXuNS19IW7MN8AQrzM15qwRdeuaIecDx7CevhHDMCdaL6OFcnyHzu4jj0qx8lebIqPY0t8AttjCY7GP+Es3I/Z+CRuxAP4ED6FO/FpLMFn8BgexA/xWQx0sZ7if3K9RFfrJLrSh/e1qotYXT3E0u/qXHVdRG09xNOs5yLB//s6hgGEeEIBoZhQSjhDMPxA3UPCGEIeYRuhlHCGUPtiHUMoIZZQQNhFOEaoIPj8WMcQ8qOnbqJn8AyewTN4Bhn+Ne//043q/67N9/+V9//hmvf/wTXsv0OcoLxXyJRvI0+MiouIjnH5u43m377msI7EnDz1PekUdV08T/a1fW+5zUE/fenMU6CLe0Gy69+CNse/SOLXxucj7/B7EurLs1EG8xXZx6d2euhOX0BqfJn23+ncJnHmSJxGJTBvuW2cLn1/0hzXzL72/fXN0XyTsoXRVN7xuvI2t3tLk7SkELKYx2i0pkXJA9/zzY6bl5aZuKj6/Nttb/nNNdDb1BeTvHsn/4zTyYo5zb4yj7kPMX+ZJ5V57L5/LvnaLflK1uVrgrfjfBlusuYrOc+YkJFkypUr2/Vfma+BN9nky3JsHpYE3iDHRx1CjrK/WvOl7qvUaXDp2DTvP6l9HX8nPbiW/fGYy7zFuvg4Nn5TfFU4oIaz31ad/9a7+AZl+mMzl8VUXHfHw8t3NTlT9shdR539Vu3+b8Pu/obt7LfqPvnK9Dkr2tcv7V+Ws/u+5OykDfe9cO1+GzZ9y1DO0XLuPk3Qfsuwpzx7h2Ad7IU3YB9siqHYCfvhIOyv+e2oQNZbV9ar/e0oUNbbFmtjkHU5OY8St4PlZhrkm1vYDWdrf1OU5XJkOe1vio1lOT9Jb1NZvhn2QX+cis1xPrbAdAxAI7ayxCPnOUxzEM9giedG9Mch2ArDcRgOw9E4HKdjBCbjSEzBUZp4DDc5j2ecxDNR4pkk8Wi/vzIap0g8UyWeaRLPdG15Szw3OCjvrrKdumEdDLYux/HsfPt2kOU6Ym3shCHMfGwiz+aESwTzbyBrCWmT+C2BUEaoINSL5LmeoPz+sROPKuP87Rtl+52YMsZ3YtJkfifAQjxGMH8vJmAKz/g8c29B7e8XA2jkHU8oJBwlbNP/LjGtpiGEkEfYTDisBNbzPl4ihEzndwRCyTDygebfJ0JpND+BkELIZ7wejefDCMUE/fdm8mn8XM46Kwg+P/HbAGECwUgoIuz9yfNbgWfwDJ7BM/w/DP+i5/9r9v2/xX15tvAzfd9vYpT99//GcNNwTvPv+u//DXfh+3/lGXUMNt//Y01X8/2/2v8D3/9z9nyyIF99/gme9fzxbYv8Lq75dVTPDn7e1X/nTy1bKfPTBqmroPsWeFdsjd2wOwZjGPbEYRiCG3HCJb51StB/56+2vKuy3rPpv+nn2vf8dO+B5Dt+9vdUGy957pk8g2fwDJ7BM3gGz+AZPINn8Az/+cO/4Pk/bpnl7f9ve/4P4vl+gfJOT32+V9Yqr9bjMjKVMVavPuOP0HynL7yG9Ztd9aUt5hLWUZRhfS+oLOvKe9XG8v5T+w5b2359p8RVi+AlocKHOt6muNQfQtRUK1/ay8g10tbR5W/4ybc=
*/