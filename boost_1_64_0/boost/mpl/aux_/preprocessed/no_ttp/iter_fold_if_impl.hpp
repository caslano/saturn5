
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
eJrx6/0AONr/Lwjl3lnaH1vkmc3lRGl5tmo4n4/e7Wz/79mq11DgtjQXa9d7IsTZ5rVluT368nj2WNrXSP8EPPst24A/lkYDxjJN449c+ZOGZkZn06YC59F/+yhpi+nb7pK8vq4vm+efpc3YYfewV9vufZL37bJu3yKimSb9Y3fe7dbEAufXqw+BJJOzvwPU2llZRzrzHop6e3cZp+W17R5HXmMkr879YEFQ7v1giZbXPa68sujYCTEmEy3D8m+PqbePluXLZxjnznd8YsxIGzrb6FE2bV/It12mtOXz6mPivOS9geS9LjGEvEftdeVdX9zf2X89t+cc+aBJ9sVo1NuceSzHajYXuO17GY82vwmynRp/4thOQ2UfS3QO+2y385KnhkQQUZ94VCv7p648jTS7j418++7wV/5Wzn2kiLSzkfU8RJtOK79rWdKi3uhoUh/I+vZsR+973GnnMf2sJevkW305PA/vc5ylF3XMcIZsl3RcxjQhn7nypbUDDGC7FCmXts/Zhrhg54kQdOdXjj8/+/p5z33dY5/WuiGI05qtSln773Nvb899PVL6NVgm22AxYWYaw+fOsjpaGAey7stchjbG/s6PZj0vTCv77oPOYZ/tlillKUsESXkeY5rd7rIkm8cF1t+Ms51uY9nAzWVfaIqZzPOk1zz1i2GKKYB1JPune9v6bke5fgXv9398HpH8mKR80cQopknf78qPJcY+ynFiLUB+/J1XLfq5XvLo0bbXNjHvY2q/5DvBJ9/p8ojqLsn3DuIJbaMfcOXbZr7C19y4FEuC2eS9/+dIvh6RfM2Xc73hS1e+Ui1Gqzk+gGtUfudhz/bG0SVy94GzjZPtG1969hGjn/8D7h9G+qbx2n83l8jdH9N2lpPtvRz2Yfr1SUzMd1mqrfJ/93egc4n6fFYMeiruukaVvmtw/rdl1TPOXfnfh05px79B7gHkO2GWnE/tsnc9L20s1mAoZmE4vogtcC22wXXYDV9GI76Ccbgep+IGXIwbcRluwUx8DU8h2Xd818dgacNUSTtOJB/XSRumyhiKVbEKhmEEVsOWWAPbYzh2x5p4B9bCeKyNSXg9jscbcCreiIuxLi7HergZ6+Nb2AD3Y0P8Gm/Gc9gI/8AI1DLfFE/pbUrk+z9ul/VaFmdIed6T9boTK+AurI/vY1Pcg73wExyAn+EI3Iex+AXehfsxFb/CDMyW9fo1rsBD+BYedr/fke/6ntvb+/2OnWQ9d5b13AWrYle8GbthM+yOLbAn9sFItGAvnIW9cRlGYSb2QWnjLt/XWad+2sbHyHqJxboY57F/zJHPmfzsH+3kcx1lfXbCatgF22JX7ILdsSf2wP7YEydjJN6LvXA13oGvYW/chv3wW+yPv+EAvICD5L2lg7E2DsGWOBS74zAcisMxGt1t1+W7OzaU9eDZdv176SPgiFyij2JNPIbX43HZX07I/KKJOTK/ETK/4kh+SSjbdQBWxIGyXe/E2jgIG+Bg7IZD8HYchkNwuHP7FXJ+32Zflu2gfb4OammcbIcJGIp3YxVMw3o4CRvhZNkeU7AHTsUonI6jcAam40ycibNwFmbgA3gfLsT7cQ3OxpdwHm7A+fg+LpDt9jAew0fwNC7Cc7gYy5H3JVgBl2J1XIa34mPYAjOxFz6BZnwSR+IKTMSVaMVVOBlXYzo+4z7u5Ls78/Zz3F0j26cYhmIJDMeS2BpLYXssgz2xLPbDEEzBcjgRy+NCDMXFWNF93Mn3bT7r57hrKftbK9l+rSXf2cRJ+Vxz2d6V+fde+VxZmb48VsLrMByrYDOsiq0wDHtjNRyINTAGw3E01sIpWBvnYR25XtyAy/FG2c51Zfs=
*/