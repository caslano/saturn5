/*
 [auto_generated]
 boost/numeric/odeint/version.hpp

 [begin_description]
 Defines the current version of odeint.
 [end_description]

 Copyright 2011-2012 Karsten Ahnert
 Copyright 2011-2012 Mario Mulansky

 Distributed under the Boost Software License, Version 1.0.
 (See accompanying file LICENSE_1_0.txt or
 copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_NUMERIC_ODEINT_VERSION_HPP_INCLUDED
#define BOOST_NUMERIC_ODEINT_VERSION_HPP_INCLUDED

#include <string>
#include <sstream>


#define ODEINT_MAJOR_VERSION 2
#define ODEINT_MINOR_VERSION 2
#define ODEINT_PATCH_LEVEL 0
#define ODEINT_VERSION ( ODEINT_MAJOR_VERSION * 100000 + ODEINT_MINOR_VERSION * 100 + ODEINT_PATCH_LEVEL )


namespace boost {
namespace numeric {
namespace odeint {

namespace version {

const int major = ODEINT_MAJOR_VERSION ;
const int minor = ODEINT_MINOR_VERSION ;
const int patch_level = ODEINT_PATCH_LEVEL ;

}

inline std::string get_version_string( void )
{
    std::ostringstream str;
    str << "v" << version::major << "." << version::minor;
    if( version::patch_level != 0 ) str << "_" << version::patch_level;
    return str.str();
}


}
}
}

#endif // BOOST_NUMERIC_ODEINT_VERSION_HPP_INCLUDED

/* version.hpp
1UvQr8TzpWrAh6n9jZdtdSS1f/Ayoz+Az0PJ51dofOAVZv34CqN/XmHWL68w9iuTf+cVuv7qVbp8iVeZ9fOrTP2Z+7uvMvVn8ParjP3+GmO/v0bXL/Ua4z95ja5f7TVm/cSUr8PkPwp8Ymp+vW6r9Sn/WYBPEDV/gE9C+WeBL0edD38D9aPGB/D5CX79DWb/Bvj9FrF/+hbiO4j6NbA5fpoNPCr+4l3EHxPlG3gvjI/qf3/gZxJ45n2MD0o/AafOH44C35Lq3w9stSCl34C3w7HZR/5/iPUTZf9/ZKsBKn/gWxP1bwPfkno+wceIDyH6r/Mx41/9hFm/fMLsnwAnz5cCX52yD4C/SD1f5FPEr2ssQv99ZqsKEf8T/xznP4j951HgOxHrS/cLW01LjT/ghxD3H/jSVncT5U+OIv5xXH//e+Z+9fse+dvE+YIfGfseeHti3D/KvsTDvRYaP/r8jZoipham8BljaldcLBsRf1qfLaZ+1PFdEf0zRwzjhxhfDJ4CXqXmP8OPzxlTGxP82pw0v8HgLQbvAJ+FKt9cMTo+Bfj0lP0BfDnK/wF867/M3yYWvOPiL32/uWNqU0I+ucDHp/Y/gR9H+E8G5ompq6j41HljalFKfs5L168JfAKqfxi8DXwRqn/mi6n1cFGNWt8vHFPHEue/GskYXKiYP+P0jx+NLxlT0+r444j7LxVTa1L6A/jklH0EfCFq/i0do8+HAZ+N8A/VGX4L+BxUfDvwjXHxmRXx/KYVaX4d+DfU86FXitHP3wZOrn9WjqllCf2VAb4iMf6bwCfz5OMEPXhv/w/EVE4R56uA7wwFkIuKj9oQ84M6Hwm8TcSPDqRi6k1M8MtU//j8xLYxtS8aY/Me/L4jxp7PXtsxps4J1s+JfuXPxLT9NkGU/AZO+Y9T2Zi6AfdfqAc/98ix/F0npjYg7N94PqbG1fWP6L+hmPqYev7ATphflP8M+GJU+wPfhFjfZ3aOqQ+I83G1QkydQNnfu6D+1PlW4FtoLKJ9dsX8peIPgH+HzyXD+//l/MZwTM1Mtc+wHh+R86M1gvFnR8ffZsoxtR+1P1CBfLSJ5+Pvjv4l9jdSe0G+UP4/4Pvo8R1Rvn1i6idt30X4hxFc/RX1fJdDYupIAm8BX4eQL4lDY7R9CHwe/JGI4h8RU0PU+AFO+s+Bz0/JzyNj6hX8MXNU+xyL8UGdfz4upsrU+uh4un0awEn/JfBviecLjOJwxN3E/OycEFNzU/t7J9LtkwJ+KrG/ED8ppral7Ffg61D2p8YJ++xkun1SwIeJ8dE5mR4/mVPo9qmfQrdP+xS6feqnxtR8lH0HfGoqvuZUun1Sp9HtkwG+LS5mtv6yPgqfzxYj18fJc2LqSSL/5LmwD6n1N/DFqfgb4C9Qz08+L0bvPzJ4B3hS69cI/XY+1o+UfgQ+OfF82tSFkO/U8z2Ak/HJDN5m8A7w6Sn/6kU0Pw58R8q+YPgNBm8C/4L6fo6LY/T5+Uv0+iv6+QXAJ6XyBz4J1f7AF7cI+X0ZvX7OAJ+RWn8yeAP4gZT+uDymVqLOlwGnzifGr9D2ZfT64Eq0n0WsD67C+oDSrww+yuDxq2GfUfs3wKem4neupu9fY/AGg7cYvMPg6pqY2ouwrxvAyeffAJ+a+v6OZkytQO3fNOnxVwd+AOG/TV5H+3dSwMnzQwzuMniNwesM3mDwJoO3GLwNfBVi/iWuj6mpqPgRBs8weI3BGwzeYvAOg6sbaDwBfBnKfwecjP8Gvg9lf9wYUwdR+gX48tT5wpuwfhsn2v5v3x7qp/76/w74Pwi8A/xBSn/fGVNrUevnu2JqK2r9AZyMbwBOnn+6O6YuGjf6+y8=
*/