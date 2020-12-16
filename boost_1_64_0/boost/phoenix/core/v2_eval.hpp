/*=============================================================================
    Copyright (c) 2011 Thomas Heller

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#ifndef BOOST_PHOENIX_CORE_V2_EVAL_HPP
#define BOOST_PHOENIX_CORE_V2_EVAL_HPP

#include <boost/phoenix/core/limits.hpp>
#include <boost/phoenix/core/environment.hpp>
#include <boost/phoenix/core/is_actor.hpp>
#include <boost/phoenix/core/meta_grammar.hpp>
#include <boost/phoenix/core/terminal_fwd.hpp>
#include <boost/phoenix/support/vector.hpp>
#include <boost/proto/transform/fold.hpp>
#include <boost/proto/transform/lazy.hpp>

namespace boost { namespace phoenix
{
    struct v2_eval
        : proto::callable
    {
        template <typename Sig>
        struct result;

        template <typename This, typename Eval, typename Env>
        struct result<This(Eval, Env)>
            : Eval::template result<typename proto::detail::uncvref<Env>::type>
        {};

        template <typename This, typename Eval, typename Env>
        struct result<This(Eval &, Env)>
            : Eval::template result<typename proto::detail::uncvref<Env>::type>
        {};

        template <typename This, typename Eval, typename Env>
        struct result<This(Eval const &, Env)>
            : Eval::template result<typename proto::detail::uncvref<Env>::type>
        {};

        template <typename Eval, typename Env>
        typename result<v2_eval(Eval const&, Env)>::type
        operator()(Eval const & e, Env const & env) const
        {
            return e.eval(env);
        }
    };
}}

#endif

/* v2_eval.hpp
JJ8/IeG25+jLvofE+QYJd5ik9yUJl9VLbyNgunoZT2w6TFeGBcSqYboy1MHSdP2ahLuT5HM7sSdJPl8l4d4m9iGJ80tSvtTe+v2oN0wXpxOmq5dCEmcRsVKYLp8+WI7G1pG83ErCPUjKtwem67v7SJwtsFSNfUHK16mPPr1cmF1jebDeun2lD9lXSJxLYLr6XE3CbSTp1ZPyPU7CvUjsXZiuHT6H5WosM1dfvsG5+jgnkXCzc/XtUJmrL8NqEudNsDSN/SRX38+2knANxHYT20vsdViGxg6Q+vyClD2tr976wewacxKbDNO1wxySnpuEW0nCXQ/rrWsjYk8T20fycpiE69RPbw5Yhq4++5FxntgcmC6fFbBs3f5A7GaS3lZij5O8vEjSayb2ObG0/obh0FgeTBduKqyfxkphubo6I3YbsUeJNRE7TPKZ6tCHG+rQ98FC2GDd/gcbqLH1Dn1d/xxg1/UJWJrG9sByNPYWLENjhxz6fnacpJcygKyxDCDnhjBdepOJzYHp2qgapuuf60hebiW2jdiTxF6GZejagdTZh8S+GEDmYAP14bJhuj7hJDYdpuvzpcSuJHm5Hpaqsc0wXZ1tgWXp9geYrk+8RuJsJuGOk3rJGqRv96GD9OEmDyL9moRbMkjfr+tIXm6G2XX1SWzHIH2dNRJ7ldjbxD4kdpTUWdpgfV/KHqwPN2IwWZcaTNalBuvregExH7E1xDYR20LsUWLPE9sHy9XYZ8TsQ/THVCexWUP0fd5NbDWxzUP0bbt1CJlnEdtL7K0h+n52BNZbYylD9fU5eCg5j4Nla2wOsUpia4htJnYfzK47Ng4lx0YS5wES56ewVI0dJ+HSztRbLkxX1wUwXRmmkzjnwXTl85H01hG7A6brZw3EnoU5NHaQpHccpuu72cP0fXc0zKHrn7B+GvMTu4nYdmIvwgZq7DCxjOH6OPNgGRqbCNO1exEsTWPFMF37+WG6driehLuT5OVRYi+Ssh+C6eosdYR+X8kdQfYxmK58s4lVwnT9bANMl8/7YHkaewOmK/tnMLvGkkbqy549kuwrMF37TR9JxheSXiWJc/VIctyEOXT9ZSTpLyS9d0nZvyBlSMsj62d5+nxOztPncy6xJXn6MqwhdjPJ59Y8skYGS9PVJyxDY/tIuIMkn0dJnJ1GkWu7o8g9EjBdX5pG4pwH0/WJAAm3DmbX9V2Sl+2jyDVFEudrJM4PYf00luLUt/tAmK4+z4bp0psNy9X1XWLrYUN19eIk1/hIPl+F6erzIMyusc+c5P6Cs/T9OvMscr0DpivDaBLnZBJuFrEFxCpJeiFidbBUjV1PbDNM10bbSJ09Scqwl9gbxA4S+5TkJcml7y9ZLrLGQsKd7dLXy0xiC136fXo1bKDG7iTWCMvR2D6Sl8Muci0kn9wDArNrbARMl5ep+WTtHpaqG3vyybVWWJrGNsCydfWZT+5LIOH2kHp5g9iHpF4SRuvDZcPsuv5J7Gxi04nNg+nqxU0sAMvWtQNMV/Z6mK7d7yPp7RxN7oki1kLi/JKUIWuMfl9xwnThpsF0bTufmA+WprGVJC83w3J09QnL1NhuYq+S8h0k9gXJZ1aBPp95BeR+jQJ9PucTWwKza+zKAn0fXEfsJpLPbQX6Pvhsgb7O3iLWUkD6LgmXNVYfbiAxF7HJY8k5kNYMY8lYsx0Mh7i/XLRD1BDuPHWOQuwnsByN7SDh9sByNfYusS9g/TSWc7bYp4WJfk2sENZbYwtg2RrzE1tP4qyH6cq3m8T5GinD+7BMjR3VhsM4Nw79zOwT6t+N6A2L7n/nq/NyYk5i44lNJTYL5tCYD9ZbMrl862GZZvlmtCnfENs=
*/