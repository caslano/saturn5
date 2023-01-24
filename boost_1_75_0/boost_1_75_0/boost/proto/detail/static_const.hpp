///////////////////////////////////////////////////////////////////////////////
/// \file static_const.hpp
/// Contains definition of static_const for declaring static constants that 
//
//  Copyright 2008 Eric Niebler. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PROTO_DETAIL_STATIC_CONST_HPP_EAN_20_07_2012
#define BOOST_PROTO_DETAIL_STATIC_CONST_HPP_EAN_20_07_2012

namespace boost { namespace proto
{
    namespace detail
    {
        template<typename T>
        struct static_const
        {
            static T const value;
        };

        template<typename T>
        T const static_const<T>::value = {};
    }
}}

#endif

/* static_const.hpp
nWwWg1llX/YiieoEK0XOb9lJc+qP1MXjV6GhyqZIIjmyINHiJ6aS/D1HFMNhHQ4iw/GFmoql+VORyvAqK10VcUghaKyIiO0Puhtq4aj7oZ+42W1oqA20M0ve8jM4rPlXjQhN8TWNW8ec9Hq+Q7DTA2XWRt2RUxbQWrNgQ7lnZm1hbWV1mXZBOIivbjz/WzA8OX3Ha8ArpuPUutZyGHA8aGHCKgq6sJbPpgwLYoKOREE/iK3Omt5ODeP99jo7AI9fGA+m/536YOU/qW/yJ/VhiX9Sn/NP6uvKbwxrc/kSLfbtrhsmDD82d/yN+kN/Uv/jn9Q/t9Z4sfuT+hPsf1L/L39Sf5LKWdrIE/L0kw2EsPueZ1I+4PbH+6Nv2P1GAk/OSe3NOzC3R8naFgovT/2rDbW5Pb63vdPmwLCdJEr9X79ygZaf027hgLyR/TSUiNv0LTwiUi8W/XgIiVeo35gts1+fG7xw30zLRKLM7VceyewVQfmg3HKpbn/ro+LIh52q1scIPyBCbfKC8hj+LAl4ee79ahcxICST7R1wSzLwuAXBZ7J78lbJ3YfN4wjDdx1U2wP2ZePB8FvKbEAGCBawH/O0sgvMq+w9W912hl4KDdZk4iguP8dmpummPJtauY1ZYgPBDHbrQ8R3OdKbs59YCYwyXeP4ZTPxtvqE5NS31SxQIw/8xSWp/GXDZdrR8K/Ma2yoY3RiXO1ZXrEp
*/