
// Copyright Aleksey Gurtovoy 2001-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// Preprocessed version of "boost/mpl/aux_/template_arity.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl { namespace aux {

template< bool >
struct template_arity_impl
{
    template< typename F > struct result_
        : mpl::int_< -1 >
    {
    };
};

template<>
struct template_arity_impl<true>
{
    template< typename F > struct result_
        : F::arity
    {
    };
};

template< typename F >
struct template_arity
    : template_arity_impl< ::boost::mpl::aux::has_rebind<F>::value >
        ::template result_<F>
{
};

}}}


/* template_arity.hpp
q5kTq3+PxvsmI7GZab22km6RPy9QrFSnFfhnBUrG6l/tly+GaigHPgT9M5X0a65mqXeRaX2yklb15/bK+Q+t1yv9Z6oWmYGULtVLz4txf4FeaaVsgYJAiW5gjvVXt+94Mo6+2LSedh7N6qXn+erH0HvYohfInSq/r+p5q/6ll+qur1O8td4lpvWKf0a/ILeoSP4cqKzFAkXTCvLlY7tq5cHT+X54aFzJQ16+Rt7q9iuPXlpz
*/