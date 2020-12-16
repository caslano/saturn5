//  lambda_fwd.hpp - Boost Lambda Library -------------------------------

// Copyright (C) 1999, 2000 Jaakko Jarvi (jaakko.jarvi@cs.utu.fi)
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
// For more information, see www.boost.org

// -------------------------------------------------------

#ifndef BOOST_LAMBDA_FWD_HPP
#define BOOST_LAMBDA_FWD_HPP

namespace boost { 
namespace lambda { 

namespace detail {

template<class T> struct generate_error;

}   
// -- placeholders --------------------------------------------

template <int I> struct placeholder;

// function_adaptors
template <class Func> 
struct function_adaptor;

template <int I, class Act> class action;

template <class Base> 
class lambda_functor;

template <class Act, class Args> 
class lambda_functor_base;

} // namespace lambda
} // namespace boost


//  #define CALL_TEMPLATE_ARGS class A, class Env
//  #define CALL_FORMAL_ARGS A& a, Env& env
//  #define CALL_ACTUAL_ARGS a, env
//  #define CALL_ACTUAL_ARGS_NO_ENV a
//  #define CALL_REFERENCE_TYPES A&, Env&
//  #define CALL_PLAIN_TYPES A, Env
#define CALL_TEMPLATE_ARGS class A, class B, class C, class Env
#define CALL_FORMAL_ARGS A& a, B& b, C& c, Env& env
#define CALL_ACTUAL_ARGS a, b, c, env
#define CALL_ACTUAL_ARGS_NO_ENV a, b, c
#define CALL_REFERENCE_TYPES A&, B&, C&, Env&
#define CALL_PLAIN_TYPES A, B, C, Env

namespace boost {
namespace lambda {
namespace detail {

template<class A1, class A2, class A3, class A4>
void do_nothing(A1&, A2&, A3&, A4&) {}

} // detail
} // lambda
} // boost

// prevent the warnings from unused arguments
#define CALL_USE_ARGS \
::boost::lambda::detail::do_nothing(a, b, c, env)



#endif

/* lambda_fwd.hpp
A5OBM5HpNXb6x6G0LNizal+I60wbX14N+yz22Nj4CuxsJuSljQV9Bu5MAScX5WfZ2wSt/DOEH+Mm8tucAWgTv/QxEsDmLHPw2/cFzdkXbBL/C40gaGUUtL0KVM84o1/Q79qPCP/FRiP8poEeBIUZ1fuIxqz7UXtN3q0qFmOipSCzni5G/VscgjYm9TRe17+jrKdeno3gudHkcZ+veT734dnNePB/+bpvPI3JcxI8N5k8xoKWnmCXjqtJo+pxxYR6/8sXRPv2RZ3xXJ99UQn/u1YCeS+4Wu7r3le9sffs+ipt483j/5fVxltQaQ8L5f9UhK5z4i7lNkPcWbfoHqn5dR2q1g9u40emF0LQVsBp/2DvWsCjKq7w3BBIgAQSSEIkESPyiBIwBcSoiAHCQ4u6aqRB0SQQEDTAmgSb1ldsAVEBU4sVLSIvAS0qVqigoEGpRIsWLVZasKYVLW1pm7ZYaaWP/578O5m9O7tsIG2/fl8WTv57555zZubM886dB/CnsEH+T81yCL+ieM8P1CWTIGvvS1NvhL70DHl+ve5L34B7a1+auqx9afYDZ8vza52e7FdOkfuJTi/UtV9Fn/Qt+9661GvvJ78rzw6hth9DN0cd+ynX1sLF1lfu5t590LS/Y4y332t8F3xc9JzmLFbJYd+7fyY8Z+j3ha/L/aUt6usG3iNuFtnLnVTUUjtBbnlyc8X47oFyUmjv85LPDz6+J6+0vieTLz4l8J7cJfCenOSWySq4bQLxPbm3Vz7AE5ui+6mp0bRlV30Q3JZVyH170anXJIe8J7e8jxpNmT7ZPumCD+x90j1pSn4Psd/yLdcN8cjdb5bXSrPf4i0fOv3PE5lFagD+zrb3XaDX2nfReXa2PL8a428x1jJKeZYLrnW1z0Ugr73c+eXZlShj7aSNqYPnRyB4r7QfnULajzTypKQx78QNSWiXaBkXIl8e+BZKPhxna6+EZzJ47pN3qsmeNkb3ZZGPQC34Rl8Zsc/kaQdoO3MejL+H3qdNft1defjc2JQfuAND8dQpzAcVst7YbQYqbelNOUfHb3kL1oG6ulOp2w3jWObZpPTQ/SL2JcH9ZxLGpiH04kBQS8vLjUFq2ELqpSrEswF0v6RRUkK7bs1pmZPclAaB+8TUE89JCVrjy/D1JsOZoLUpsG1T+DyD5krPx+gHueQo9suVfi/9SjrNswcJbbGSftkG6MEi5xfUwL8joAdgg86q8yDsz5DQXoWER2wRMc08eaixZ+hcqr8gI+1lmORglTLu4+EZm7fkIchZx9Wt9QN54Sb1A3mLy6zzlchvqY9s/W7w2vr/1j43eK39f1t/G7wtmyvmHRON94yJpgWVccafvEmW+iDF0ldM9/QVzfTdm6nk5xgBnAv/G4z05cRRIx38+Nwlxc8+Juq1F/s7ljQGr7WfZh+jbEH6NrQgfRtakL4NUaYvz0Oi3Wkvb9tPu3ja/lZN30297OnbaKSvHOzSgvRtbEH6NrYgfRtbkL6NLUjfxhakb+P/WfruO4NpCnKo75WB7kdZSV93kKR0dpl8DA73bqbf19uLzBx1Ef5OtPf5qNcJO/5+nTyP0fNBe6az/8x+dE91jaTB69kOEiDoW7XWMVZ0dDphOx2pj222qwVZuu0iwn+EfWWTjSpvKR5TVDx65IQJo0aO/rK8z86eW16uzH5jhPyQdVmyZ2+ZRot/2+DfJrt/c2ex7XyR7yv2ckd5/NP91CjCFWhnXN2p1G3a5vCZoWHdA946a1j9c/xsDNzwbogcXurgHoBJgbEqjm1Z6gryG3236OO3wYhfGsug62eq9jM4jfb1Do33a9Cx1x7vuZUzoouzyOMf+9OR6kbNq98=
*/