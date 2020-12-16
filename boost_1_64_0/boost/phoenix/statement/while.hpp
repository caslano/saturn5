/*==============================================================================
    Copyright (c) 2001-2010 Joel de Guzman
    Copyright (c) 2010 Thomas Heller

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#ifndef BOOST_PHOENIX_STATEMENT_WHILE_HPP
#define BOOST_PHOENIX_STATEMENT_WHILE_HPP

#include <boost/phoenix/core/limits.hpp>
#include <boost/phoenix/core/call.hpp>
#include <boost/phoenix/core/expression.hpp>
#include <boost/phoenix/core/meta_grammar.hpp>

BOOST_PHOENIX_DEFINE_EXPRESSION(
    (boost)(phoenix)(while_)
  , (meta_grammar) // Cond
    (meta_grammar) // Do
)

namespace boost { namespace phoenix
{
    struct while_eval
    {
        typedef void result_type;

        template <typename Cond, typename Do, typename Context>
        result_type
        operator()(Cond const& cond, Do const& do_it, Context const & ctx) const
        {
            while(boost::phoenix::eval(cond, ctx))
            {
                boost::phoenix::eval(do_it, ctx);
            }
        }
    };
    
    template <typename Dummy>
    struct default_actions::when<rule::while_, Dummy>
        : call<while_eval, Dummy>
    {};

    template <typename Cond>
    struct while_gen
    {
        while_gen(Cond const& cond_) : cond(cond_) {}

        template <typename Do>
        typename expression::while_<Cond, Do>::type const
        operator[](Do const& do_it) const
        {
            return expression::while_<Cond, Do>::make(cond, do_it);
        }

        Cond const& cond;
    };

    template <typename Cond>
    inline
    while_gen<Cond> const
    while_(Cond const& cond)
    {
        return while_gen<Cond>(cond);
    }


}}

#endif

/* while.hpp
jflj39LqNJP05XvD2t83DH8bx8GHywDD0pL/4vIt5cxDt85/PGOxTbeZf8f3aPX9zUo9ticvT6il/uHYLnMc5bS39UUST4wlKcU6yaKqz74d9Zblxvk5b0fW2npmjsl2dITwmLoWf9+ljJwLo5Kjx0cnxWllCr6NMtnajRvQl+Zx0uir9RWaNEiLlZ5EkxMTuk9PoddSXGJCcl/9IVCA4RpDq1f2jTosv57l6xmXdyzZJT6RaylJ97Q8C0xOiJP2C/uzQbLico6eYbWA071TZh29YONlDOY4VNtw8GGX+nE/k2j1VCuP9XTNsE7lPG88vhu3b6bJ9YGHY3QK63UpeX+Yv9/U8mrS61LODXJ4le3Ica1U1fBt6vGJqQnmqNQE1RiaZElOtpgd29NjR5z3oXOGv43foQ+rK+2Zsg8twSfUefiovf7kEtgclxw9Lt5ivv13F8g1ruPdBYREq3N7d3tpoBwi+RmIG1V+jtnyo7V3R6dyIjTH5j0vgYZ1aI5lq4gZF5eSrK+TbtTFeUJ1/m+Rlp5cc9n2W+sklVf7vKHk9TnmeVXmNX57fILhWfdwP5WW1ekb3FbZjo1tUIel7P1kX+9FSFftEB/ay264DOBWMc7MUezW5w3XNs+Kkk/Zz/T4YhLjXb+1b66vR7Ja8rOSsFndm3/k6/WdHbJv3fZzCMmj23nBmK9rkq/lJtlmJV/ZLvmSff4vz1cPydf0BnpEFeUeP8ikH4syjzvylWQha55qLBfPClzzZkw7p4FLm6ykneWWttTKXUjbdgzu20Sf8dti+vr4GiNV305H2skx0QkeCq2nCzdtX0j8Utu/kuL0Q3mu1pHx3SjGY6bhVSz6RbRJrudlf7DYT1PyjMp47pFj92Xquh5l3lWEdp1PHNeNp1zjkPnPN2TbaERfNmbs/qnjWJHhOPdp++RZSUutIHV9F6USlbiPy7yxickp6v9kX7XHv5X4RzHtmROOc8kqW/xJ1qheLvOfayR9hT7T56/B/Ett+Y+hhZEHa3LTrd24u6ZXq7H+noHlsryq4y2yPCs4zsoNtX4Tri9uXHYsy85R++3njmUP2/KaarUmJqkX1ciTjmSXdKn38yzU66SjnHsc9c7cct8k0zgvWhMTzJy/pMuz1Od5ucZnGb3noqwrM3kLJo03+fuEIY1smZ9Y1OxyrLffZ2vrb7+HNA33vvZz80XZZvzl3Bwj9VDL33m/2ioPlYbKfhUh+1XY1077lezQ7vtV+1vsV2/8cGf7ldzn29uXQJuW5dJPSK2P07L/6fmTLMuGrP7/lPf90/0aUNZVeBP+po520I9y8DeOdXXepc9ZgGHdJFMQ2/IpTTluEi7zd+cz+vJ1DO1flhhtN9D3Ar31Skok26TE0Y08BLPwp9867mVv8As2Oe4h1aJauva2Msf/ucZnJb57iKjw945jRbajTp22pd3fOG9LiWdlW5K/B3yn//2Gy3XfqGbu7z3bos6h5x3bloX9Ny5lRpS6X8nNs2xv209JUoxJmS7bj+Fe1fDOsKnjZ2jrKUj+jkuOslhc+oOENtcT2yfn/T2EZ9RzoQue86z3W7n9e7xQ9fck0y3zbbzmj3O9T5jKOjfcC9KQTMZooXfpD+XbQs/QTCnbVLX/q2f4P3kpG/ePuWkzuJN1oq7NAwxlkYtl+36v9+MhHy5l8WspbXtSlpNSlrCfvZSFQ72tLH5/cVkueyhLjuHZuvRJsJd5slmbpO2bRVuQVku9f+hTPzvvmxP81bx6PRi32flSF7/IfvazKkxZzoHZhrpIkUsj+z1W3vc1477t20qf8bL0of9V0lzxizFN2xieKLLt3m/INxd1r+oojf+0EoPxHi4=
*/