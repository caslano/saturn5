/*-----------------------------------------------------------------------------+
Copyright (c) 2010-2010: Joachim Faulhaber
+------------------------------------------------------------------------------+
   Distributed under the Boost Software License, Version 1.0.
      (See accompanying file LICENCE.txt or copy at
           http://www.boost.org/LICENSE_1_0.txt)
+-----------------------------------------------------------------------------*/
#ifndef BOOST_ICL_PREDICATES_STD_EQUAL_HPP_JOFA_101102
#define BOOST_ICL_PREDICATES_STD_EQUAL_HPP_JOFA_101102

#include <boost/icl/type_traits/predicate.hpp>
#include <boost/icl/type_traits/type_to_string.hpp>

namespace boost{namespace icl
{
    template <class Type> struct std_equal : public relation<Type,Type>
    {
        bool operator()(const Type& lhs, const Type& rhs)const
        {
            return lhs == rhs;
        }
    };

    //-----------------------------------------------------------------------------

    template<>         
    inline std::string unary_template_to_string<icl::std_equal>::apply()
    { return "=="; }

}} // namespace icl boost

#endif


/* std_equal.hpp
n2AXnXm+fI3MLaLwsWJxIM/pMztdDpvZLuSwtcjVcrYmNzPz830eWzkrh83rtTnzytk4RdEqOMXxglf0FbgFeUlwXo7T5UM8pCuIEgzOk1YMFx1wTlQig2h4zD6pnTrldu12uzxc5jZ7vVIJBXa7ULZmOMvfPbaM443N87hQfq7ZZi/wiEzusjnhgfRNDSjZLCqpWg6HnLk2p81XHMC3eWV34JV6HXSP2Wl1OeCPIwcBzxOdzHU5b/jMk9cO21x4TUQFTquIAkQr13d5iAL40srsnDfW6RrvFOTq+GmuAbosPgFta7zH5cxjDdEfFZVMVUbvgSafy5Qr4iCQlKyxNlNaSqbaivP6q7kqfsBq7lYXWKb+aSNMbg8iR1ISLdZ8k8XhNVlFuXUH8NBWTN58s0e0mhB6l2od/n4mi8uBRi6a0MDKbLxyi9GI+Lr9VhfkeU6TWBTAw8loy1XpcaVAWm61RKpvAJjQmDntzwR+oFSTHNlYX7Fb1PCkarqs4Kr4iFEZW8sXneX5BTlcXc2DaiBPKj1WLpSQ1MeNh1+fb8p1U5msv76VvgyWzE+3yWnz+iag+zXl4Riac6XmW04mf0EIpiI7YERUXkc+ybySqo7MoxxsdizKycfbcBKOR+uBdZm8yCRFx+Uuo9WR5jxNRInYhwRM8vkWy890LV8+02xWKrPp2yfWYXK4nL48l0P0FCu1kettc9uLA/VY81WyUj5BYLLavBZ0ibiql4VeX18+V7hb+nouiy9WLl9frvgW67JUKlcdT4QefQVc86Enr9TGG5QNtOWj6hGlLl1robZxy6E1yVFXnRP6ctFZmZy3EX0ZXJK6QpezEnvvOI+OTPfgcB2lqbpxZ1NtPf/poCuv3kHS2iV0qV75Aaejrvy6yscAS7XKh56qfF359ZSvf/y5TP/YQlblsa3u6Ryor81VV8dhHiuyCurK1ac6l+mc5voyrzr7QB+D6gqYTVBdAbMJqisg3FT0HTxoSKYS5ECefuC1Oi53sZrO48GX+yWiimRuKi+zinkeUSzPFy3q2y1d+Vi1hp6O6kbdxG65dfX4jTnX0urgcqmlTTnFrFpOuMCPBWuMkjzX48Ldi9ln1uTFZToV1NXTVlSr59WJvZ7MrWMXeNtMys0mawG46Pt5/IhzmluKUFPzeaTUtAmO57uspOYrJxxuIxhPfZPLafU9kppXyM9FzkNNpNsPu80ieVN1PwYldr6oq6qVqV3UyvxucD8yB6UPzNZ2BGqZyWy1BtAWhzuQRoTVtDXHHiDX7zzKDnr1dN2kq3u32+MaI1p8tkJ9A60NHmhFj0/D85rMPlPZE59W5nKqume1TB0yrQytR02ru2k1v6yL1vK9QcTMG0TM9LtZdd5B2uiVcR3Hhd128YOgavPqO3/OGz8wuQ+/inNa9XQhiZSA2mKt2udYzuuv5jK+9jkWPJfEk09RxiJ+A6bxTCXTf17hNy56MlesrVw5LrsVPWj5h0YXhokgsOZrnn7VMq+ZPcza8jR89gBbJiFywxyyIhSCokQ1z2Txeexa2uT1edQ8bqbmYYN+NpAnXwnAVfFkJwlJerASRI+H9+c5ZqsAGdqMMjiTg/0ChzTcJbhyBYy45CkFqppWoJAlZfTD6oJYNZAkSNGjynXk4jG8RWUJ4xxC4BUtcPTIf+OhDBVNED0ufztWhm/kcbGcYkG68gZY8+/0CT6XS7CbPawKebmxDp0hMFKeQXV94W25Ul9tTqntYJhKGhR25UhnKjsL/GN+/lNeYD2XvhxDXdLoZoCMd5icttryMAodaC8/pSHCap4cAzXt8jhUchZENm7l57Oxx+qMpUJTNZJqRvU8qsG6bogaNKI=
*/