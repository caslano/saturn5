// Boost Lambda Library -- control_constructs_common.hpp -------------------

// Copyright (C) 1999, 2000 Jaakko Jarvi (jaakko.jarvi@cs.utu.fi)
// Copyright (C) 2000 Gary Powell (powellg@amazon.com)
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
// For more information, see www.boost.org

// --------------------------------------------------------------------------

#if !defined(BOOST_CONTROL_CONSTRUCTS_COMMON_HPP)
#define BOOST_CONTROL_CONSTRUCTS_COMMON_HPP

namespace boost { 
namespace lambda {

  // special types of lambda functors, used with control structures
  // to guarantee that they are composed correctly.

template<class Tag, class LambdaFunctor>
class tagged_lambda_functor;

template<class Tag, class Args>
class tagged_lambda_functor<Tag, lambda_functor<Args> > 
  : public lambda_functor<Args> 
{
public:
  tagged_lambda_functor(const Args& a) : lambda_functor<Args>(a) {}

  tagged_lambda_functor(const lambda_functor<Args>& a) 
    : lambda_functor<Args>(a) {}

  // for the no body cases in control structures.
  tagged_lambda_functor() : lambda_functor<Args>() {}
};

} // lambda
} // boost

#endif // BOOST_CONTROL_CONSTRUCTS_COMMON_HPP








/* control_constructs_common.hpp
z6fwfMVXUg/clv5S2lgH6vMpyc9Bdyu8UQ7D+8OFxl6c07JXfevYpw46j6mDrmO6LnwmektSjVh+cRL24cD1+DJCQ/437RK3IsPSx0r7vYHplYn/0wH1UOei1Gb1Jt7DHNgJF4j/pCaYT99idFaH8HwEz98by9Tdjs7qTw6Hes3hUgccy1Sxs7Na73RAty71vPNBlefqjDcvnFnucqmnXRtVnhvPbjy78ezGcwCeA/Ac4FKNWa73iwyReCd3QNsObRO5ztQdQtZXvzP+YuwyHnKeMKJYPhNEjxPp96nxojPH8L6TPCbxOXS9Tpd4+mudJEnYUmsZXGg90+ek6DVHXUQ5rpf4HofUc9Wf4RpurFJPGrer2x0XoW6vUtc471GZrkT1uOspNcW9VmUGJKqulPNySXul26luVx8gbHuEfRlh1yLsMcc6tdK5Vi1D2L8hbAf+Lw2TMK6ANmhLaSrXOIK21NYx03gebcjhust4Hm2nJd9FEiQvsS6Td5KaRN7bjAPg9eY3QeRfrevkMYm/3O2tk8GV+jEs+pD/ghGsIxdK+GsDQ1BHYvGf+j7wC7VDbTdCYKfaoR5whKinHDvUImeIusv5KupAiJrv+gBlD3QDA4ABf1GTEYP3ve5D0fGngQFqa+BLgUFqItt9U5ElJ6CyLrih7wh1BPef4/4JI0K9hrq423BD9xHqMdTDJx1uNccZgXQd6l5nkJrjwr0L9y7cu3Hvxr07SJftEfavjVk+QyRvz+i615DvQo9KvxvAd6Wq57Z8n2gjcq5wu2Gz/QT0inFAbXB8rFY4T6oVrpN6LDOGddGiW2l/Q6jbYyLPDYGRkKm9utd4HTotN3aqzdDpi46d6k7o9CHnTlUEnd7kKlczoNMS98dqRgAw4LCaaeqUumsgaT0heQmGrBOZ55fE/ZaAcOiwo3JBl2EqwAAP9LgbQ+/DuD9muKHLMPUqdPo6dLrMGaY2QqebodOlrjC11uVA/ca9G/du3LuD9N7lyaKbK5hukB6TRlZU6qwl2+Vu0dkGl1Vnjzu+URugM/1O9q3Pf5LEcZv1HTHBqr9J4r8wIBj6a47+ax/wqHoJvUIIrMIvqdXQ4ybHS+p66PEO5xtSNxdCj3luoBsIPXrrxrWS9nC2Q/zTSdyvuQNVPeRukvG0gXP6HVnGXCe+FeK81chF79OB9ai/5O00eANh1R1jvAbeNo4ZxipnfXXaebexyuRl3SqReKcEuNUrsJaWoy8px16CcvQjX2CUdBp9yGn2gZoX9WyD8aTxogEe9oHefmIFSuNF40/GG8YK52nDfD/11PZ+yvenli7u77Wepcb3BasNcYTYEPt/svpA/KFn7/j8m8/3LD9QPK3ShlhscKzJuQ/zigflGUybNsTG/L5XE35HKwp4HZ9v5POdwGjgSq5nv582xi+5jv0kz8k6D3G3AQ4GtgOOAMYBnwJ2Ar4O7Az8KzDBDA/sAgxxVNoW2wK7AQcBxwKHAnsAU4C9gS8ALwK+AuwD3A3sB4x0Vp4n1gqYCGwHTAL2B/YHDgEOAF4NTAaWAs34yoADgSuAl5n5Ag4GPgy8HPgNcCjw78BhwDHQ45XA8cAU4ETgCGARcCTwHuBYrutfr9/P5H1Trkag1Szw8dT/RH7PLAf4Cb+ftheBpgCfRf5ygauQ/lTgfMR/NbDQjT38JgagPE1E/PnAucAZZj6As4AbgEXALcBrgO8Ci4GHgXPMfAHn+uwnGApba57f3uq//Jf/8l/+y3/5L//lv/zX/931L7b/507PzJIfMf+fA/v/lGjM1XKu/5RTyfUc58q3gSaY5//9TeZ4B12RNEDst1lNxH57TUH69Gz7M/8ZhvPsTUI=
*/