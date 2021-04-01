// Copyright 2005 Daniel Wallin.
// Copyright 2005 Joel de Guzman.
//
// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
// Modeled after range_ex, Copyright 2004 Eric Niebler
///////////////////////////////////////////////////////////////////////////////
//
// has_sort.hpp
//
/////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_PHOENIX_HAS_SORT_EN_14_12_2004
#define BOOST_PHOENIX_HAS_SORT_EN_14_12_2004

#include "./is_std_list.hpp"

namespace boost
{
    // Specialize this for user-defined types
    template<typename T>
    struct has_sort
        : is_std_list<T>
    {
    };
}

#endif

/* has_sort.hpp
WjNLvi8doSherxyQ1TROByb1LJf616Ut4USlW2jO5v4iTqGI0Z3f8cwGrgCe1I+kyChzGqh6vJCiciIDyuqadTdeb/LJtUlAAtQzkt4t/lHG3twO55j2fG61CXBvZU+V05US1SG9HKKf57YnvPm7cfyd6XwN3u5qCsBREegL4zAZ9T5sA9FfhOPL+3vb8jEqPUFdDk187WZQuGT1WTClOS3VLX41k1WoFZpzkAZ6AUSVSNXGH1GgW5gngxXgAKdCv7pzPSLWydfcezWQyk5QrglpoWrFPVGscRhgrj3vrTw4k96VaO1l1MjsK+f5yvaXfqE8SrNaA/UOtzZmVTYP4x5TsCQVD0PtAbxPP+SW5rh/ID9akOx+3yabLoM3zMdSNn0gkz5XTwj48jE66e59TI/ENzjzdUwEPdyhAEkJeqUJHeW4IXd/mLFOvc55TZSyc4QRvSml3KqhmmczDmhflJweBm1H+Qg1UWQTVGzlKN+Nj8D6BfhtLlom3kAc6V5CvyktLntjziFDSHcZdpQ6YEnkyvkguId9K7du6I+R6GSUwrEjPqyB8IxXvQ==
*/