
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
4414DufgjzgPf8KN+DNuw2bye7M5PoUe+Bx64mH0wrfxInwPW2ANtsTTeCnWY1v0I4/tsDN2wC7og8HYCcdiZ0zGQMzA7ngT9sBV2BPXYjCux964G/vgExiCb+Fl+DX2xW9wILahrAZhWxyMgzAMB2M4TsUheC0OwyQcgVk4EotwFM7DSDSf36QuBa8hOJ7fRsr5IRLH4WicgGMwFqPwNGYZpG4EV8hyWmGSLKefHM8D0QdDMRQHYziG4WS8HGdhOM7GobgQh+FSjLCmJ3UauEAjvUBJr4uk1w37YpCk213S7YEzMBjTsDcWYx+chyHW8yihkfPok1JOT2EgPq2KV9HI/aJSibcQ2+MiibdKiSfp7ZV4bbBU4vWR790Q7IH9cQgOwDgciEk4CLMwFPNwMBZgGK7Hy/EODMetOAQfxaG4B4dhpZe5/XzA5V5NvmMxaEnD9vIHl9i3mT+mjBO02s4X1RGf6WUESzv6iDOehp1LnbWnJyxtpE09n7VdxjIIlvb1WfxdQiidzLJQq6191TJbe/vaZfZt7luUsZ6EKEIGYQdhP8HSFj+L/FaOYtm4nfG6MvK63sNwiKBunx+wnLbgzKNup19ZR3q4mM/CmbYTDxPU7fZrGTesaNh+34dpOzAcHdvxJ6ywb8t/uM7cnr9sha1Nfy158abS5ST5tLTvP7yCuFiL5wklo0lnJcuhI/PAKaS10tbuv2ylre3/Dv4+SLD0AXCSvz1X2fcFEMJ4IOlZ+gTIWtWwX4AoPnfsF8DINFPfAMy/j1BfR3pjSIO/g8mXpb8Az1sb9hkwis9HKdP5OxEtfQcY+buGaRtQqw+Bfbe63o+AcrEaRUgkqPsUWMx4HeN70Xss6/8NeWP6YWX8WsoXQ7GowuMX9TXQf03T/Q3EkGbcmsb7Hdi+xtb3wF7+3vUMaSv7BX+3LTf3RRCCWv0RxDK9nOkHz3q63C9BEXHOMv9Zxjco8ZVtxPTAbz0N+8pt/RXUq/osCFzLPo5RqNV3QRnTjbgdzzNtP9YSlL4MPNfZ92cQyPhejMbw61kvPMZ4OSYxXoXqPg5q1tn3cxCwnu3BuTGBYCSUE6oIRwlnCd7h7GOEWEIWYRVhJ+EgoZbgOYR3jRKiCRmEMkIlYT+hhmAY6mUIIkQTMgiLCZWE/YTjhPND9f4R9EEf9EEf9EEf9EEf9OGXD//Z9v/ZxszcjKQCWvfk52UqHQD82+3/vyKnYdI/bkYz2/Ov/oRcQo+eXK7OMD0/OWVi3PhJ0YOHhlqencxAjWEZ92LIwwjT84l+hubW5yiV53KJY312uJiQJ+NtMcjT9kz1duKuC1beE2ZuTzLFl/vj3ODxIFfynCP3cd1/ztHd58W0nztzv79XZ88bzgtVpt/97HSvu/765aFJht2RGVMTD7r/PJ35vp5sK9mG+wnq+3qU8WJ/9MEu6IvB6Ifh6I8RGICx2BGTsBPehJ0xFwMxC5V7UgHSZ2ML6VtR/V6xHYSjhITR9u8O2y79BQYMo586rFL12VdKUF+Thg7Tr8/0QR/0QR/0QR/0QR/0QR/04fc5eBLyfoXr/4xZhUXmHgD//T4A/05u5f1A1meJjnhInxl4u9LGsJP9PYDkK7PzUnNcb0OpvrZX5q+Qa3tLe0frvQB1e1iDuZ3kXiwhX12Ua/dAJR+2dtjK8xs5Oaq+t2Q9Tsh6XE3wIEwkbCDNqG4O6zExz6X3t8l6SL7t3weW07xh/22bmK/SMa2EgtS8wpn5Bbnup2dueyr3UFKLUvnTbn2jpB+9O1nv1rgZtxB3v2MerjUSPdPl/okc0/dva04/WXXfpphg6XPpvMO2rJNxNpG1XbNqHWT7y/aWdbo=
*/