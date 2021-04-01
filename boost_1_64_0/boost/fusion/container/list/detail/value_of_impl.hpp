/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman
    Copyright (c) 2005 Eric Niebler

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_VALUE_OF_IMPL_07172005_0838)
#define FUSION_VALUE_OF_IMPL_07172005_0838

namespace boost { namespace fusion
{
    struct cons_iterator_tag;

    namespace extension
    {
        template <typename Tag>
        struct value_of_impl;

        template <>
        struct value_of_impl<cons_iterator_tag>
        {
            template <typename Iterator>
            struct apply
            {
                typedef typename Iterator::cons_type cons_type;
                typedef typename cons_type::car_type type;
            };
        };
    }

}}

#endif



/* value_of_impl.hpp
a62NN60sO8GumXdE+s6aKPkjLdsyMss9m94sCYV6cKoWolRVX/8zZKe8h4Dg1DfYEgEWT2Lxjj1Z/tAvxe/l2b2CYyWfFj+3KhXJjiH7W8uRjM8kjeto/msUzn1v4IoyCZJs5+X7d/XIZsOV6JmHvTx+UwJOomkNEoCsNMmjhTpNHYHD+HzLmN/XZJu4jA4EC2SWv0sNQBMOyRc6cXJQ2cOpFECr/JxkXnMZQvePPow+6FK6KCs9KxCVrqiXeY/Qwx8q1uXtghbbOIgRA59Lfl3b9YrZqaMagjUchll0BjBHJwFFpzBZ8zjY/UaSnVS0aDX9ec7Pwme64atjbG9OD91Hlg2mIGfCpXYoTUXBVU+VI2psTbQp7v9Ku39oo3fZRg3dKDIPf7b79D+tiBgMCiFesAQFq68CTR7gvvAf5qVKklUnTXUT+xXw8wCLgFDO9vSjDrWI50+IO9FsF+NUWTFMl6T75NtZ8uoIfYmR6vOO3p3Tb/xbm3Xrnad6Ke2CYv887rfYmivL+WBFxQYoQgtnVXgxAD0Pmn+rLQXPWIPjHJG6fLTWEfQSiQ==
*/