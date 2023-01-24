/*=============================================================================
    Copyright (c) 2009-2010 Christopher Schmidt

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_FUSION_ADAPTED_STRUCT_DETAIL_VALUE_OF_DATA_IMPL_HPP
#define BOOST_FUSION_ADAPTED_STRUCT_DETAIL_VALUE_OF_DATA_IMPL_HPP

namespace boost { namespace fusion { namespace extension
{
    template <typename>
    struct value_of_data_impl;

    template <>
    struct value_of_data_impl<struct_iterator_tag>
      : value_of_impl<struct_iterator_tag>
    {};
}}}

#endif

/* value_of_data_impl.hpp
R+DhMPNwg1UczH9tN4xjWQ/ifZiNaCr0sSwfo5AHxdgMznTDW5it/0MRZd0h6LRQGQaHOoeJlXpDWe9ZTKwDBausvmwozfzrKJteBlyEFfArGnUeg+UVXJTh1Sy8uCon9/Hu5kox6uMwm5VnXu1mvRjCWMyuntOcutoPjb/Z5Nfs6iq1C6vUrjbjqp7l3q5SW84q6vaGJWR4V7q9O9zeDZwW5NrmqD+B7kEmJp0EUtSLNXAKMhsZ/YT++A/h/hpgV8ZHo7hc/qwUl02RJC4nLXGh6FvHps4gLmneaikvJ1V5ORkgL2uxyiUcDIyBVFb5GIU+It1tSC85qJfeEal28NyJYs3tHZGQDI2S5iVIxwzYvqPGQSz6y8QrNduUL9djwwe/AO6bFLUJLpzwW8zvJ3EMqOOvL1tqhCT3/UfC9mZ624AMbNGUWE+v6IlNTv/UXJsE/ZFIY6cLCeDn64hGrM2ZQujmpsnx1sJAOS5oYz17TzxzfmWr+f6ckp0MjXF5RJMlO/8mU6r/bSak2suc9yikMMnaZgE16sWj/NTGlqzW3AG36LX/nqHXFjfTrPhVenQhU8RjZvPL1osXhK1vXGvw/XeeYZXZogqPJeTwaxd1/LDSwI6H32rHT79EAgvu+8Dq+F1N63jbM9Tx/4TXOyotcrfAZYBeulcU+P9oexO4qKr2cXwGGBaBGUxHcUnHJKOsxKyEtJpJ0CFB
*/