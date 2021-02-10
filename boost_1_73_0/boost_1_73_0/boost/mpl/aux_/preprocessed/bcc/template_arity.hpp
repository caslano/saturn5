
// Copyright Aleksey Gurtovoy 2001-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// *Preprocessed* version of the main "template_arity.hpp" header
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
7Hab6LDQ3C1YbozEthFbVBeRt3D55dYQ7aEtasPIm9qKQgOx3XPF0TCeiUU/bmLCQPPX810Sx3kykIwDE/OlMq03rF0/Wm1crhkh5WKzKExbmOKKOWgzq4VqZ4uirYfrWXnce87cXQKNDErVBDy3VLOo59fX9m4wGCl22aQkzMnNw+OWG2ljBrEDRiya85zndvv9ztqGQ3lNDP0kAFYdczRDHTHhYbqKu5ah6wN1L3s+ifX6otojD6RTECIbs4YZ9UTZdJEGk0icxMzazhhIx2ClYe7OiUtC6SzmTDHMpZ0g70CxosydrZAdY+GMvN18GluSvB8meqz3+vY82SdY3uwgSTly3eBgq5Qirx3RmGgaTzS8zpJf7oJ6T92r0XBXsrTiyNo6CGUlHNHCbE7Ya1ENN/qqSTeofFptkbmBJDm2Z/S4UdCqnyrYbq82KCB6k4nJiGxqNvYGA7Ljvq5kR6ujFthGmKikvGL1ZN9MO+sSdEVueijzqLGUEX1V9Jve1tsQhDwNbXM0zOpzUxXTtL/ps/5s+kiUjY6yA4ecVmht1+9mpsyEfbpe9KhVnd4b6nI5isbcSqORtD62WJXaZQyhDXUdaFPKbehlQWf1Po0195rBTDbkgQZ9q09M9ju6tEbsdO2xBbkBUT8k
*/