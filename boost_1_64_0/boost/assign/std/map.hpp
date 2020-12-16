// Boost.Assign library
//
//  Copyright Thorsten Ottosen 2003-2004. Use, modification and
//  distribution is subject to the Boost Software License, Version
//  1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//
// For more information, see http://www.boost.org/libs/assign/
//


#ifndef BOOST_ASSIGN_STD_MAP_HPP
#define BOOST_ASSIGN_STD_MAP_HPP

#if defined(_MSC_VER)
# pragma once
#endif

#include <boost/assign/list_inserter.hpp>
#include <boost/config.hpp>
#include <map>

namespace boost
{
namespace assign
{

    template< class K, class V, class C, class A, class P >
    inline list_inserter< assign_detail::call_insert< std::map<K,V,C,A> >, P >
    operator+=( std::map<K,V,C,A>& m, const P& p )
    {
        return insert( m )( p );
    }
    
    template< class K, class V, class C, class A, class P >
    inline list_inserter< assign_detail::call_insert< std::multimap<K,V,C,A> >, P >
    operator+=( std::multimap<K,V,C,A>& m, const P& p )
    {
        return insert( m )( p );
    }

}
}

#endif

/* map.hpp
A/8mZwn6f5apHKFjdu123b9mniYxVv+kafW344AKsaf5hztPORn6nGsp6bzqXMMY9WDn0Kp9mMYduyc0BsuzaedKPV1WTZ82S8It0D7NjVdzn5a8q0qfpvEc7ZNj92mPS7hPfEt8g237GCzXfoSJ1oc1g+9KnDd8YufXQxL+MOPp06w8+hIJO90/wDzt+8HXKbK/sm38Ygk3zdNfzbL91SC5v0H0eCmmCeZQs0/GKbKzhZy7l4kz7b19lu2P7pV04/3e+2fOqMq9Ru3T9F34KynzzNAeJHI9J5g07c+aSRq96a1TTbR6stlc6fZ10obOkuuZX23/6Nsd6h/7uyEkzlmR/aPtl4vFf0mN/WN2ZP+oY+UJuyW+SRN7WFuRPnJbY+bX0m0f+VhkHzkPe8tq+sgxxOuJycuqfX+Zg/2vmgZ9Z0RfWfOeN25fefue8L5yUZS+cmmUvnJZlL5yeZS+ckWMvjK7hr7yud3hfeXHu6P2lVZ3fnvdszBD+8otX0b0lfM5w3Q7bIs5bhv0lRuvs/adwXTaqR76mOM2DddX3wljjts0XDeTofUyea9r3+U7hNZ5Giaiz7O6zutLuH2+w90Ri92TUNKrtu/LhJ/IPR3u7fs0nqN9bZW+z9b73XLeTU6sfq6JpP2oE+znXt7n2rMj+jndp038ehhmV0wmpr32f43lHF/4DsZnPuZoerGTMGWYiL7Q9lmPSpxDfZ6+0J6ng5xniulDWsM947bb9lUZt9nn2MeS3hOOz7lb+zANT95G9Cl2vVE9ibPXN4BcPAOj4yBpj5O1DbtcL6bm8ZHbtg9Nl3Yt7XmcjoXGVxkH1e696xGuP/K9K7JtV0Rp24uitO2lUdr2ssi2rW33NepEtHesS1rp3mq00Rauv7bVvB3R2qod1sQa12i81vIMdOfjS8R+h+9oE2+WYl5x1ptG4ueYjJ2u39hY7VfT6mJaaH04Xez3+QbRJs/B9PGdbOvFQZLWoJjjmtc+94xrbNp97dqHWG28VMJ968uVkbi2cRu/bbXjm7X/qDK+IV7Nbdztgwok7itV2niGtvEFks5O3+GkfzbG07btmPIsCbPN188kmNMwscYwPeVc3cPabRttt9+IX4ITHMN0xow3t5vgOMa/M/BOEh9jHJMj+b5e7d4yHyL1d6Kk38RXpT3rOO8cuYfPfP2ptQuM70e358P1WX4s5rgsb/uO9ayueb2T254P2vnvac9PfG7bs5XNnOiLJesXSwYzlsxjLFm/WLKTP5/M488lS7h7RED2s3Jm//sv7PnZhmfOuunqgy+NJdsYS1Y0lkxiLNnV/ZfZjC5DGksGdv9lb/dXZjaWDOnekIy/jKcTA3o2jZXxiQvJBiV6ZXVUJtBlNkyAvUxI3+8ijVeu8bz6fh9VmcfHVHbwSXg4fB4OgevhePhneBJ8AU6BL2n6/Y3O78FOmn4c7KbpbyRcOvw7bAXfgm1du8ZfhsnT+I9qfJWlkuNKlW28GvZWWcmB8FqVcbweHqsyfCfAFXAGvAUWq+zTHJXhK4d3wbNVlm+Zyjhdo7J7t8CHgjKYRueXYH+9rnqQc3PIM1z0JKfAljAVdoRpsDtMh71hExjMpxRNr0GUfKpPOJcNYBxMgvVhssbP9em8iM4BufGHGdHLLcdIX+C8o2E/OAYeCcfCkXCc6jsfDwvgcbAcTobnw3y4HE6Dd8ICWAlnwn/AU+FeOA/+E86HcQ4zK7AjXAi7wbNgP3gOzIWL4Qx4AZwDl8LT4SXwQvhbWAkvh2vhFfBReCV8El4N18Pr4Dvw9/ATeBP8B7wF7oUr4Q/wNpjq6iGGfeFqeAS8Gw6F98IT4Fo4Az4Mz4KPwWvgk/A=
*/