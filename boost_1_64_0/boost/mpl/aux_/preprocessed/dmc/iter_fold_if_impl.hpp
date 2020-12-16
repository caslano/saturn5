
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
8x27G1tay3ZZNH2NrR1OgQDqt0+0tWw9W1mPbzzpSuxs1iPuLXVqavuLTO/2NdfBToU/z2n9j50/Ab7fF19MbWyBvN/X6ENCa5mjEx/aIi/gQ6WtD9yQB3AcxAd1HHUbn/a2ttbL5RynarVPcvr53z/1iVb6ZLrHOSE3LJHyPBABd1EvIY/pa8lMNzma7a4+nslqHzc+k1nv907IPQk1rMdF1+ovK48Hj6wCZ5rjhvWHUXI/pNUhtz9aMtaZqZ8rTspzhEPukWpET5T0e6lNHvdN1e77JFP9VHNwtM9ieWZdALX6KXvCo35Yr89KO2f9xNrXD/apn+3O+snNyqWKbO6Jazzq6Kyijk57lP2ER9lrPcsu9fiSR9lP2pQ9p62MBUjbaAFjtXNmvWfZi9N4MPGrbazZYG0btdihZft8LpF9OLIO070Pp1CTjGmm/RMZU3IyCgrq0sTJ3PksR92zqeZje8oxpbDYVNf5UtfVnnUt9VaBTl6ueX3sdI/77BnuYyHryqWdynfXsTnueWzkOOx2HxvTPWRItLxrWZ5FNJ22pI14wHIspCf3Z80n9a9Y6xpurGMpu7RNU/uoEp/Wik9rkI74lL7R6hMPS36PbUh7sDybeazDlfZgPv7RiuN/zmPt9Vmb8jja1TlTIeXZhbTRnok2WcvD3YDPPQraub52k/pclzJ6rW/8NbWB+PZ1mfeT60VfpCv+lVvbgHMIzZ/xbOOYGXVsXf9sHjOjbWZm5RnWQGv/mCoPsq7674xPDu3kCvFv7a96ja/d2tnvf+1voGt833SuPf35tE2HI7ZO+HzemUln77okdV/ga3nVa2Ht1vjarZEN3tpf9drZwNcEq9d2262xDnwN8Zm6GBnFf7nn487PXZ/x1q6xY+86Fma3xjr4a3+Zp9PXpKZ6rBW6xvgO682yRliRboCeDvGS7sfGNa7r7e32N8aMkPxa+8gvfbN9fkMN6Rwm/+xj2Jda0lljiacj5ZLuBkl3EUyRdF1ZuhAKu8M2sAdsB3vCjrAX7At7wx/DS2EC7AMTYV8o/jBnYl++FGP9S7rW9n6z1lTmLWQ+Q0t3iba2TNJ9KWvx/gKj4SlZS/s17A//CgfC0/A6eAamwm/gZHgWzoTfQudeOsrxHWwKw7B3MewAw2FH2Az2hM3h5bAFvBFGwCTYCk6AkTANtoEZMArOgG1hAYyGxbA9XA1j4HrYAT4NL4G/gB3hPhgH69YIypyGzHWkeqwR/Ejq42PYDn4CO8Bq2AN+KmvAP4OD4e/hjfAEHAf/CHPhSYg91hjLnIXMZaQiverWMjs/t4u9O2EXuABeCUvgELgQjoBLJP+74Ay4FObDZfB2uAIugitljfMqWArXw5fh/bASboDvwI3wAHwAHoEPwmb49BCMgg/DjrAMdoKPwN5wG+wPH4PXwCfgKLgdToNPQgfcAYvgTrgCPgM3whfhVvgS3AEr4EG4Gx6Cr8Aa+Co8A/fAf8LXYSh1VwlbwrdgFNyrr7mXeRDY0fZ8kFg3hnT2/YzMHcAYH/klWNJZ8ytGHJJupaQzrhXdL+3ggKyJ/RVsDw/Ba+B7MBlWSfv6NSyA78NieAQuhEfhYvgBXAp/I/UTHyJj5rCl2De+c2KhvFNgEWwByUPXSxC9KIXeUtFbBiPhcmM/bbCXjhjrpTTUEPNI0rXxka5M0jVFjnmkW2283rjs+khX5bLrI12tn+kitvmXLp504h97TMzpRhrSJUu6pj7SpfuZX4nLPx/pyvxMVynp2vlIV+1HfvQzMpbD/6Sf7K+N0Us/2VfOj34wEsbDGNgfdjbsVRgAR8KfwPHwSpgFB8JZcJD0l1fL+TIYLoPXwFVwCHw=
*/