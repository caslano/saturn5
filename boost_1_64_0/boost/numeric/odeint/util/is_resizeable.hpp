/*
 [auto_generated]
 boost/numeric/odeint/util/is_resizeable.hpp

 [begin_description]
 Metafunction to determine if a state type can resized. For usage in the steppers.
 [end_description]

 Copyright 2011-2012 Karsten Ahnert
 Copyright 2011 Mario Mulansky

 Distributed under the Boost Software License, Version 1.0.
 (See accompanying file LICENSE_1_0.txt or
 copy at http://www.boost.org/LICENSE_1_0.txt)
 */


#ifndef BOOST_NUMERIC_ODEINT_UTIL_IS_RESIZEABLE_HPP_INCLUDED
#define BOOST_NUMERIC_ODEINT_UTIL_IS_RESIZEABLE_HPP_INCLUDED


#include <vector>

#include <boost/type_traits/integral_constant.hpp>
#include <boost/type_traits/remove_reference.hpp>
#include <boost/fusion/include/front.hpp>
#include <boost/fusion/include/is_sequence.hpp>

#include <boost/mpl/find_if.hpp>
#include <boost/mpl/end.hpp>
#include <boost/mpl/placeholders.hpp>
#include <boost/mpl/if.hpp>
#include <boost/type_traits/is_same.hpp>

namespace boost {
namespace numeric {
namespace odeint {
   
/*
 * by default any type is not resizable
 */
template< typename Container , typename Enabler = void >
struct is_resizeable_sfinae : boost::false_type {};

template< typename Container >
struct is_resizeable : is_resizeable_sfinae< Container > {};



/*
 * specialization for std::vector
 */
template< class V, class A >
struct is_resizeable< std::vector< V , A  > > : boost::true_type {};


/*
 * sfinae specialization for fusion sequences
 */
template< typename FusionSequence >
struct is_resizeable_sfinae<
    FusionSequence ,
    typename boost::enable_if< typename boost::fusion::traits::is_sequence< FusionSequence >::type >::type >
{
    typedef typename boost::mpl::find_if< FusionSequence , is_resizeable< boost::mpl::_1 > >::type iter;
    typedef typename boost::mpl::end< FusionSequence >::type last;

    typedef typename boost::mpl::if_< boost::is_same< iter , last > , boost::false_type , boost::true_type >::type type;
    const static bool value = type::value;
};






} // namespace odeint
} // namespace numeric
} // namespace boost



#endif // BOOST_NUMERIC_ODEINT_UTIL_IS_RESIZEABLE_HPP_INCLUDED

/* is_resizeable.hpp
wz6w0m/ONG+qPcLrzxhVzY2uwqXqvzlnzpymkCnoqLtwGKfFc6Bl86cp+paxkFFJ2RKxV0fsoXCK6IfChEMfK9rh8MpZSdAXAnrlbDWIxG+eZlJZwLtlWpDj5L7HGx5nFyfIprRjgtRfrAiPc0S+7QEPbOjLvvA4Z2RBhqndmCJGevFhRIPw0QRI/CB1Lj6Myh1A77D9PCDXW59V0IrtMqQofE7awxPYV6awRwXO00LxFnCKEbIWnOEJ5LtdoeOS6kvpjgkC+o1flX7kNYe2eYpwsWWYxoPpt+TBzdPybXI2q5IKvliWFRu5dTslM5YLriq2ZO237gptklyhwARtVSwjz5FRIh56WuUlxADIzvPKPfoc7V5x5ysUmoaLCgQDWYAIrJ7QJqW1+SLt7jjcZwh3ognXVN88CxmnH2E/IWHnSdhwUQFpIGx6yj4Zqo+lcr8St9R+Ek/lIaby7lNGKgzAVKi0WPlR4JSp/GYXU4GLCqjYuu7wOLe+TDJ8QvgiwFZpxhfmnaoq+nvFfvZm2mWLhmigCLnp/Yr0bja9m6X3XgkJX5j3STO+MAtp5jeybJdkDofkTwyAhmSDeToa2Y8s26185U9Y4r6Z8NWXva+SP03bZlYGpPXM2qYng34ILiz6gN745VGU/rOf2PmPDySrnnOGlB6NSAGPShz4fFX2HTdIsg5chrddzqh2cfhJIi99saBrB2OdbS37uwg9jqn007ijRBuvo+OhuGM9HafR8XDcUYo+j4djdO1OGr//FI3NNC6XuSiM1Km+UNvcAaXbquVvhFmzWWNQ2Lai4xc2oziiF6Jqqaa/T/wJXtBaffS5+1geX2Vewqy+5BcxZC6YWTnGnH5+rKYfy+OxBTRS7GmqM+fycFqTZH3umggdCXX7TG4yWITqEeNQ2eE6Yz4/u/KiJLhrkGrlxUbpUmXpso5FNrarh0RNrkl2blwpMePM3uGLBD36dsWfGJURTAsthIjuyKJQgwfzbdUH/uxoaBEEqTxytu9T7hXfftLEATJLMDOHoulVbyrBl8aZWCHUphabxnDQYmyMjnnjyPw5kC9ihUBoQgZCUysRGjJRiS2kAJ4inme3gfvymImVDp2zCnjp87AT6+H2dtcOzhqZQHmC5wIfvQdeCh/9LeWGY/joe78w8VFFmmKGtb5xDGmKwpAGPmYKah1HiTo/uipBD5akZfhLEIPwiq88ESdQDvLFBCdcL5nY0QnMKNp+nMom2/5YcS/Si5WGR87vSu6bs7sZM3vHKGoghObkSE6ElZ2C+QKreTuSQmjKAMmjmaCXBXqjwXt4Ob66R9JM/GwSk0K1s6O1DuIluQV6H4njDH0pjtcArSlM2YLLu28ZqDcTvSlMjdjrwG8KqE7Y2+yE77PM4bSjlzqucSH6pDCIyomvV6/BUCROvAv9orGb+M3dxke3UhC6j++QdUB83CuWvdIRbU3zidG7OkzFQoszaiBjR5UArtq/AhCr19vyJ5jqU/HB/XyTmlnzuieyFJ0v1O5afEtgXkj0CHhCwuqqfZZxDqa4Vj6lWOXF5kW83H4Gh0l+wOIeoYM2V4QbxwIr7amIcctNBTaabwkdtFctZIVKrYDrLVHuvbYUfAYptUWz6TmdnoBQNZmG1CgOfKAFF4wZNWWwpyqHMkvQnGQPntNWmGENQv0g5/VFabDZgl9htDTq1gz0QppV7rZCZ1qwJ+HI2G1Hb8J/6JHzW0X2B2QuHEBS5eLhR2R3JTbwLhwkg9+gPErFn0ohWbC3QX0sdNIBlL9HY6THcAKb6GU1Jfd/JHEmqEQyE+BSLsl9kEL/uSHOHByq3RaL3MuMvHsNvZHGT2Q4u2R5kQL4Iuw=
*/