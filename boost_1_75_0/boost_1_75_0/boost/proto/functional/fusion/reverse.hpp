///////////////////////////////////////////////////////////////////////////////
/// \file reverse.hpp
/// Proto callables Fusion reverse
//
//  Copyright 2010 Eric Niebler. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PROTO_FUNCTIONAL_FUSION_REVERSE_HPP_EAN_11_27_2010
#define BOOST_PROTO_FUNCTIONAL_FUSION_REVERSE_HPP_EAN_11_27_2010

#include <boost/fusion/include/reverse.hpp>
#include <boost/proto/proto_fwd.hpp>

namespace boost { namespace proto { namespace functional
{
    /// \brief A PolymorphicFunctionObject type that invokes the
    /// \c fusion::reverse() algorithm on its argument.
    ///
    /// A PolymorphicFunctionObject type that invokes the
    /// \c fusion::reverse() algorithm on its argument. This is
    /// useful for defining a CallableTransform like \c reverse(_)
    /// which reverses the order of the children of a Proto
    /// expression node.
    struct reverse
    {
        BOOST_PROTO_CALLABLE()

        template<typename Sig>
        struct result;

        template<typename This, typename Seq>
        struct result<This(Seq)>
          : result<This(Seq const &)>
        {};

        template<typename This, typename Seq>
        struct result<This(Seq &)>
          : fusion::result_of::reverse<Seq>
        {};

        template<typename Seq>
        typename fusion::result_of::reverse<Seq>::type
        operator ()(Seq &seq) const
        {
            // Work around a const-correctness issue in Fusion
            typedef typename fusion::result_of::reverse<Seq>::type result_type;
            return result_type(seq);
        }

        template<typename Seq>
        typename fusion::result_of::reverse<Seq const>::type
        operator ()(Seq const &seq) const
        {
            return fusion::reverse(seq);
        }
    };
}}}

#endif

/* reverse.hpp
XMfnQD7I7jyGC9g5s1rXIvQ4SvTKNNl1dI7mVfcJm7dB7xo3EujfDxFKHl19Utuih0iBGHygrjdYOKpX5ohYPgFEOOaskBH0rLvcKi6Jl/89nI3EAhadaJOxGahyj/LdC9CCJqs/d/wrdqSRjMn9/c6p9K7Cjlg/MTPgVDloYznwMCBxNnF2W1owyYtf9nYjJ1MLUGsw0XGzNDuvTtqpJ6nL5feuS4SWin+65RC4RLpNKyR/inrDq+KekEflSvoCreKeuCi6KdEM70qKj3VKMid2iQs5i/r3cEYQXajWX0dfR3cF1xzKNKjbZrfGt75HcCF/hn1U/v4EUC74HjuLbkZ0kS10HmeJblJoCLbUnTbWdlIijls3MQznaA0QK6SfIpFbDUtvet92mscl9fxIWj2kooi1hr0oKOPv0zQEvdaxtr8qrgennk4/lfzJtGd/rQqxHdMt9GFejLvSQ+P/cOTezb2dCCAkdVpkjLCz6KJYags8GIEhjTtgEjl9xiiOZf73qLnGOFBmtO5r+Pr7w6z3DGP2LKmdm1r/SMsPRf5dcsKsS/XCTf7JZoKTQgXVfYUL7oZz7yZN7faOYkvbneco+7ccLiltwkm329mhXgesdyaBbvOZE14Izu79h32PeQ+BI41hjBbds+3Z8cPC5OPbOdbbh8pp/YKFiqOArgq30ng1nIpfT8yCWBH3wV3BLJxqf1F/kZ9A1o+3
*/