/*=============================================================================
    Copyright (c) 2016 Kohei Takahashi

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef PHOENIX_BIND_BIND_FUNCTION_HPP
#define PHOENIX_BIND_BIND_FUNCTION_HPP

#include <boost/phoenix/core/limits.hpp>

#if defined(BOOST_PHOENIX_NO_VARIADIC_BIND)
# include <boost/phoenix/bind/detail/cpp03/bind_function.hpp>
#else

#include <boost/phoenix/core/expression.hpp>
#include <boost/phoenix/core/detail/function_eval.hpp>

namespace boost { namespace phoenix
{
    namespace detail
    {
        template <typename RT, typename FP>
        struct function_ptr
        {
            typedef RT result_type;

            function_ptr(FP fp_)
                : fp(fp_) {}

            template <typename... A>
            result_type operator()(A&... a) const
            {
                return fp(a...);
            }

            bool operator==(function_ptr const& rhs) const
            {
                return fp == rhs.fp;
            }

            template <typename RhsRT, typename RhsFP>
            bool operator==(function_ptr<RhsRT, RhsFP> const& /*rhs*/) const
            {
                return false;
            }

            FP fp;
        };
    } // namespace boost::phoenix::detail

    template <typename RT, typename... T, typename... A>
    inline typename detail::expression::function_eval<
        detail::function_ptr<RT, RT (*)(T...)>
      , A...
    >::type const
    bind(RT (*f)(T...), A const&... a)
    {
        typedef detail::function_ptr<RT, RT (*)(T...)> fp_type;
        return detail::expression::function_eval<fp_type, A...>::make(fp_type(f), a...);
    }
}} // namespace boost::phoenix

#endif
#endif

/* bind_function.hpp
jrpQc8M/XLGIO9Z+gfMxE5v6KyHVsYlX12UcwyGZvg+nmON2gzlwI7onUq4WPlP3V6Qu1g8aj6ozJdV9P0OJLvsQD+ADzpzSrItGqx/TUr33j+32eu5jbPG575m9Lk4+1R65P0P5CvnQk7Hnao/3vkumK8271t5F/YtMFGH9zsWwwUCd/QdxWB10fwj7mhqrjre77BRdx4plHIxeWGo4j2atl6bfqPTuBNKtO6NRP6V3ZFqXxMjo5/T4o2RWL5VM3D8VxHNDyWUmSu4//qkgp+yME+LlsSzjyKWdKLn4fyrIkmP/9ThyrhfozpGckXQ8OUdTq20Lkn85fybo9Vaek5XHY3srfewVSvfY/UxLx2Slu34CZKV1x6TtUZ8y/5+itNif/tgyc/FkZCPLlodPlUzcVz9ZFyU3n3I8OXre5SO9y03Zl/Oqo9NX+almnv/8uoclX3aGKf+fXylRO3Euycd7NcT1rtKamah3japqArRLab77lup9F/P5skqoDvA6VNRvQ4gFKUd5Wh6w8ugZ83FzOXX1jbnrki3i5wpZdeXe76nreLnM9UT51rPvHvnqAnW7gge4RLbet0iJet+iILegeGP+hks257289y1WhqvMpZxLVF6uu7yCTbkbLyneWFKYtzG3sgmrmBeoF523u5K3IKsuOvei8y7K3LCen/NGfmZYGyCNsgJWWYc9ZRUVbinesiW/5L8p60zjzZSFreEEw0eAQ1RiDpWVjF+lzSR40vSCmZX34FJXuvnLJTJbeWsTPWnKbKV3nuCkY6w6Xhfl/Uyn7rUnmulBphvq5a3NfZXMlq5xtvokM/3luIiTZyrJzPOyXNjO0/YKM8/Lcysrz0yymefluT3+G2nPya4+XZ+XW1Jy8cYNxQUFuZEK6VD9Ku2izLw8OtDKt8mTb8umjfmbN20szo1UGpPPfkfvFsP0ey7nVvoD4bhC4+hX9nlmE+616bzxZ+d9N2ZB569Z+M0fN/B7ONffQvA5so6cXqE926p//VKrHv34X78n8vymKcXnyFEv73Dz+pV/J3d091KWdN7iyNDcylr9hI8G6B6/5pViW26xFwDrbdlLbNnF/ogG71lqnsu1ZfWHYnbxO0zS1Ufl19BHek/VNLZ+XGand7nTXRJW+ow7fZWTbunaeyzyzhjOFVa00TRn+BUzcxZobgxQ15lWXYzpRGRr+MGB/4omxJ2/T5McPf8TmvHup+s3cMtj0rm91uz0VVps/sA+yqitdd6XCz3tlQk2BCNxg37TQH/NxMg0N1U7759Ozbrfm2Xqjrxzq3R8/E+ed3LrEXC927o7Uv7Fhb6t+sWs0WzlrZ3xlM0bpGbZ1vi42H7nlLa53l8tss+boyMc2wWt/im10vRz9V3nnrdqjfmTfAKxc3POX+X+zUz5cWTXrrwgLGu3489hWW5B+etrqlY11TNtWWkfoByl1davItmV1uPka7LSrP6pcvIxiMK//OYqz/zttvPblcvjyTC/R8Sceu6P2NJ8fLolP/J79RorbVNUGleMpFnlVyjNfuwaiR2v9NdGgmFL1yB6SC6f4XsgGCokvmS4uuaiK2NktgUZPPS5M34P/puya4GyMxnCNw82yNrYjYgVjBUEEZPJJLKE3Pf78ZuZRBBuJjM3mWFe5t5ZCYvxDoIgiOcJFjnkOOGs9yIIFsFiEe9gETYYDk4Oy/H1/1d3Vff//5PBuSb++rq6uru6u7q7uiuEyatRxOSz+w9R8qD9RT5r/hSBcfyVJ5gPhsSNxu5afFF+79m8BSaepi2zaJu29oKm5d7JtMFWu4mEWLQM8f2WV99JdPLNHd3fanf2HvTNT+KPuP8GozyYcNGC7wPOkrw=
*/