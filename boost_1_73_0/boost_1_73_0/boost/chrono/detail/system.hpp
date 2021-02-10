//  Copyright 2009-2010 Vicente J. Botet Escriba

//  Distributed under the Boost Software License, Version 1.0.
//  See http://www.boost.org/LICENSE_1_0.txt

#ifndef BOOST_CHRONO_DETAIL_SYSTEM_HPP
#define BOOST_CHRONO_DETAIL_SYSTEM_HPP

#if !defined BOOST_CHRONO_DONT_PROVIDE_HYBRID_ERROR_HANDLING

#include <boost/system/error_code.hpp>

namespace boost {
namespace chrono {
    inline bool is_throws(system::error_code  & ec) { return (&ec==&boost::throws()); }
}
}

#endif
#endif

/* system.hpp
6cK4JJg0mtgjE5KlgGOWSmsr8+tgkDW1RCWDXGdmkB2o6Jd2+01V98hmy/akK0tWU2N4RM4+oq3OReGuoAiHVZNKYcromBYAVT7QNRkuZRcOroKbtgROScdW5CypQvbCuovRyji0Xam3J4agtQtUNLUCHGiBXa5BfESNynnt7T0RB5SOZU/5d1p2zD0nrZAVhcOE4iSklBlhIvoSL29nd0v6MlwshtPlPc3+oOH0vov3Vzy9wWwIoNbEn6qaG2RRk9hWUvD8BPwHKn15S66fa87Mfp03VQk20e6PFF5cUsIrjPXFzyGFUqTO7nhHn5lqmAyDfnJL0+HncfBanHMaSa3QTTq4GdSFoaPWwHsn99PZPImToH9NPwmVySbndOWs21krPwV4FVM4ultM6N0rOGftm7BDDXu/hYEPfTNORot4voxn08B3rGhU5oaedkJK6MNiFpCd4jvPQ5cWhooQHCpkFg+NEWoDRUg3EwHGWbghQ4sehW6M3KMoexCnUFVj21irIm7DrYp5n661LbvwhjKmAtOkhv/bcGURIeVOH07iOa84vvypG20E3dO2MZZSFwGGRc1hucOoBIA40pFJjp5UZx97DjAIhkjYzaTaQBElFHzMryOqxF5IOUfmWno1VFooL9YzvNFVpY1X
*/