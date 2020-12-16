/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman
    Copyright (c) 2005-2006 Dan Marsden

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_STD_ARRAY_VALUE_AT_IMPL_01062013_1700)
#define BOOST_FUSION_STD_ARRAY_VALUE_AT_IMPL_01062013_1700

namespace boost { namespace fusion {
    
    struct std_array_tag;

    namespace extension
    {
        template<typename T>
        struct value_at_impl;

        template <>
        struct value_at_impl<std_array_tag>
        {
            template <typename Sequence, typename N>
            struct apply 
            {
                typedef typename Sequence::value_type type;
            };
        };
    }
}}

#endif

/* value_at_impl.hpp
Xklxun+uzFjD1eepVRATZaN4q6pjfU5KIKbfQbwaHuMwKzIQgzziST8uBnfEU0F8qaURTwfwJZYlfa8fF4M42rt6AB9p10rS3jWYqwEhsQxj7Sp2HUxjTT8mjFT6tZDzPzPvIwyvwaWu38Dkc7EsY57TLtdxbkL1PxDCxf9GHYv9P4g8EpjO2vJYCxHPIR5uP3nGzXGkoDA9jqxDmL425Pa+roG7rW19Y8x6kmsJmNJZn7HgeXQDhasBHfENGVfnV057I4XrdjaEGPYDPN6Yj9vDFGcTdazj2Ijh7Az9vSkei9W2uNJJvzWa7S2avHoLLnHDkvN3Y8ynRBxcN1G+ZT6GCSMeO3wMhUO7R+h4q2Kl7fBpC/FRwrd2W5uxA8m2zRDHkwkMfqR1BbZOr92f7vddf2xu4KPNun6naACn5UiUfkVz6nql6scgX9LWGG86ONDSswjAkol8wbfCRT6LYC6wygXz2FJyZccXp8m4f6ULxfGYC+bTkng9nE+bOb26hWzZSuB6gQuew7YWWDpXyPRmktA0Bgf6MslMOu+7r7VNtAbSIH7baF7tV9lO8P2JpLgQlMvCpH3bM6cucBnfwcDN53c7GjjOcPnOMa4S47g7GRpRCGn/zhLvdWtFHuN3kVhG3E/l5xgSWwdvUiG2G2NijUK7Smucd0csbyehh8C9sgzcqfWtz9ojzKv1WXuGOfUu573CHA2wZCRq9mZNmireKYuPisqGxZp9IjVOzdTsG6XBvQmi5ZBmP6XZyqnUG6SRDwQ5nf1Zk3NKjtto5Wj5Bou6eJ9QpAZdRvuEInmsZRo8eH3jQZE6vWbr4EheuJf2GR2iebfhgoeV8Ws529I7mGEoI+2hv6alorny3biH+bRcc4E6OTxKo+sE/XBElIbyakCliFaAuiMjdVsUm67KFHVHddRRosXKKOqO/nWdyBd9csxv6OpNdxS8gtpjf0PbdLYQwz5qj+uolUnqejm+s9aTjrLYnydEa50tQMw1iLoTO+tk3qg7KVoHKxpU48EyntxJp/2Oto8B7Sm/rsUl0E5Tt7VTo/RkOlhO5Tyts6ZR9Dwxb8C0Tv8VHSSGfeqMKA09Nkf+TObz+LEh2ajrZXk/5SzJgx00gOATLIx7tsk1RVzlRyzfOSHe5z/UnNtBUy2LZkv+OM+nCXcq2V7OD+l0HRRbMGdk3QUhXaCuWHdhSIcDLOvQVvTRRRE6+BN9dHGI45XrnMclHXgwjM4i7KdLSScuirvsJOQMX70pwRBN39PxMK3LTE3O2Qqm2OIqQCRKMj7PXm7o0ArGr/DhTbXu6koTb8qGpM8zV0Xyqq1iGldrTXdggMe8rzF4s0zX+nBdpusMXOeJMemZmeZlhdHeKo3zxbntVeGyv1Sk6/cbNa8JroObTK4FVzfFphZxeW9mTalebdB6Y35WRrjvufitBoZTG8ZvM/CM8fz7donr0zimfQfh8uSBdt7px9TMQNpyVwSvaox9fHekBhKRz9Ik747qOQNz9/o41eaxvPcR5/vu1v2MjQg/cP4PEIad0z+Aecg/aPK6A6k13g+ZvO5OGPdhk3N4xlbYtiHL/4jk9cCgrhMfNTgcSjnNxzQe2cYf1zy1cY/Se8KHNytyHcSTjLseVEGrCHvjqC89RTjWR6DsyD9t8LLslB/Z9ozmdcJcN88Sh9GkH58zMLuJdik/Pm9wTpm6W7HVasp29kIHnjeao+bFzhrxuRTUvPQrmtY21OZf9mtgJYfTclBFZXnFx+tPA3A+tEcrpMEEMP5rIc5nCmpej9ZwFqR5o4OmVG/X5LXMm1LTgl5VpfbwFmPtmhpd6NmcwoPeoXPMOx14XXTSvRut08Vn3Xs=
*/