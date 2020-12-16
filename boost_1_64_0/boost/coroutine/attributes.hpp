
//          Copyright Oliver Kowalke 2009.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_COROUTINES_ATTRIBUTES_H
#define BOOST_COROUTINES_ATTRIBUTES_H

#include <cstddef>

#include <boost/config.hpp>

#include <boost/coroutine/flags.hpp>
#include <boost/coroutine/stack_allocator.hpp>

#ifdef BOOST_HAS_ABI_HEADERS
#  include BOOST_ABI_PREFIX
#endif

namespace boost {
namespace coroutines {

struct attributes
{
    std::size_t     size;
    flag_unwind_t   do_unwind;

    attributes() BOOST_NOEXCEPT :
        size( stack_allocator::traits_type::default_size() ),
        do_unwind( stack_unwind)
    {}

    explicit attributes( std::size_t size_) BOOST_NOEXCEPT :
        size( size_),
        do_unwind( stack_unwind)
    {}

    explicit attributes( flag_unwind_t do_unwind_) BOOST_NOEXCEPT :
        size( stack_allocator::traits_type::default_size() ),
        do_unwind( do_unwind_)
    {}

    explicit attributes(
            std::size_t size_,
            flag_unwind_t do_unwind_) BOOST_NOEXCEPT :
        size( size_),
        do_unwind( do_unwind_)
    {}
};

}}

#ifdef BOOST_HAS_ABI_HEADERS
#  include BOOST_ABI_SUFFIX
#endif

#endif // BOOST_COROUTINES_ATTRIBUTES_H

/* attributes.hpp
PqbWJ+JYn48I4qJv9UdZbPvw5lzf9kEaB1ntiV4eHeGh/6gI9/ajHhPF932mH2BxeifRpOvCD5TwyCc7h/s+2Q8Svi+/PQ0fHvTeuD/YhYsuIQ3B8A2CJ0Ec1OGTbfjwSPfIjuGkSn0dHhrhmg4R93V4WBTfllHeDicc7Mmzm6f6mGo3iKPdHB7ExbPYi9iOoZ+QtrKYsajtQrs9CjjYpjBvxzAHbFfKtVQwtC3XvyxTcf89yhU6Z7wKdrWKOda2nG5We+G+n8C1HubLO54xtiPR57P8cO9tou4AGwfb6hEM7cPhm+L+xnuTZUuMk3xXlhMIpzO5aj33A5ZVz0PAyarnnczR6vk5gun1fArgWfX8fOBk1fMoc8J6HuNwrZ7HPcyX90LAsJ4nOVyr5zJjWj3XBMN6dnmZZhzqUXQ4A5hmA6cr+Dj0xebcdcM85Fmncfmo0+uLVkq4fVmlbn1KzHXtzY55aAd5XBvzbMMxj/M7R2lSPsmp2KZkDtyw5/YbJTj7/IokX5YzWansadI4Pl+aFPxMK4PxPHvqhzMUGg7+p19FOL4hK4s9IOPsQAafSxYZ5zjceocp0N2CfAHnPFgO0ivNzEruPNO5hLGdGIc6kQyZs/jpcFHA/10gBzlLMvJaSBZiq8aRSJ30bvwPlIx+ljP//Ehmdpy0PG8K0rAmQnPB6VIB/Xdd+kTgwToiH0c25cJyI89cYS8V9oLfPiWfyFsQlx88d7i76RcGcmgPNbkX1ZERv1ivW48mJTKtiXwJzwC+Feqc5CTHJmexG7sSXirPxrHlKfl+h94c5zkq99t9Oez+yOnvHb4M4Fh/c2pdiIcV/32Md0WydJ4uy/nA6tDrJOaiv0Rd5h58T/y9sTzk6brn/smcrkXdvz/WPR+Pndteqe03NV8CVddntiRL8yNQQ1nuXfWDTN7tXjx9RHs39w7xOQX6ogDvlJXhuB9o+BZ+wmNfUts2D6A08VP3hIQzsOEEX0aKf8jKKM40EHd5+TDhSQK9J4/Q6kvfQL/5dLArKsjzR3Rege58lQrgI+ZjzNu5gpi2XHP242P1XSueaqMp6x0v9vS+AMYhPM5QdfAJh/OJcdPNOru83MO5qVMH1Hq+m43SZF3J98vV7/UnYzug9JPLmzKO/JTOmarvdvm/IubUQzmf1TgsR3xrOj1QsyObgb2Fqxw2RodIG0WC4VwOzkkJsF/81Ha+KGMCMB94I0ZsGeqBP7VGqzIGvMrHKR2ng69EmFn/7+/rAX1frXKo6YCdq3KcmYusr8W8QqVZ9tY8vxFzaDrh9P3NCHd+5L7lMK7vXGnKtiaR/22fQ0ughaLnM8nhddCnpHEN4FlpfB84mEYq44eAY9vBfPwYONj+zHrgtYRNLaQ1CuI9fL+W2lu9mtlPvF3tJybh26L1y9dZHOYQer88sxLm/khCv5qJzdtvwY6RTavdXhvc70nGM+zphV7Q4PJIu7klkIF7cZif3yVyZH6I+XF+MZN5zHRucy95lKOVwv7u7b1YR3/0+21Kg8RwHd250q7Znk28/VuuIzMS0OYwH1T7xLtX2rVE6oDEQ64xXDwzeY82RqBJDPnZ4zmW65f+YXXYu3Mwt73HOtGTMt+HmOzGOfxffjrR+tD9GD9Yw/1PEHd3MWl7zWLd1e8DIQfniXjePeDh+lpbp603O1jONauUyjiM9fYjHOPWbUdTLJsmSENRHAs8NOaycdospWV7eKdml1a5qaz9VY4oWWQ9EtIM01syt3yZWbK3X/XoiM9HsKm4KeexwOH9UDNXr9D2YhvWf6Pu5JT4bXQFR8etksbjOlOcz3+IBcCZAMeBwYezowMZh3yKiSxW0qnWKgU=
*/