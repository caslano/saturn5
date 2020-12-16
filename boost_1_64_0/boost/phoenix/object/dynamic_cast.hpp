/*==============================================================================
    Copyright (c) 2001-2010 Joel de Guzman
    Copyright (c) 2010 Thomas Heller

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#ifndef BOOST_PHOENIX_OBJECT_DYNAMIC_CAST_HPP
#define BOOST_PHOENIX_OBJECT_DYNAMIC_CAST_HPP

#include <boost/phoenix/core/limits.hpp>
#include <boost/phoenix/core/call.hpp>
#include <boost/phoenix/core/expression.hpp>
#include <boost/phoenix/core/meta_grammar.hpp>
#include <boost/phoenix/object/detail/target.hpp>
#include <boost/proto/transform/lazy.hpp>

BOOST_PHOENIX_DEFINE_EXPRESSION(
    (boost)(phoenix)(dynamic_cast_)
  , (proto::terminal<detail::target<proto::_> >)
    (meta_grammar)
)
    
namespace boost { namespace phoenix
{
    struct dynamic_cast_eval
    {
        template <typename Sig>
        struct result;

        template <typename This, typename Target, typename Source, typename Context>
        struct result<This(Target, Source, Context)>
            : detail::result_of::target<Target>
        {};

        template <typename Target, typename Source, typename Context>
        typename detail::result_of::target<Target>::type
        operator()(Target, Source const& u, Context const& ctx) const
        {
            return
                dynamic_cast<
                    typename detail::result_of::target<Target>::type
                >(boost::phoenix::eval(u, ctx));
        }
    };

    template <typename Dummy>
    struct default_actions::when<rule::dynamic_cast_, Dummy>
        : call<dynamic_cast_eval, Dummy>
    {};

    template <typename T, typename U>
    inline
    typename expression::dynamic_cast_<detail::target<T>, U>::type const
    dynamic_cast_(U const& u)
    {
        return
            expression::
                dynamic_cast_<detail::target<T>, U>::
                    make(detail::target<T>(), u);
    }
}}

#endif

/* dynamic_cast.hpp
G2rewJ+bylwT+SkT+CLNcbwjy+sRk5ha2TEGhWb5i0YAm+iYyfOu4mNmiPzhz7WD5lbutwwcCMSQCBgMfJpNmHhVg/OFiS1ZvAKdsWQ99aEnW+CK5xWRiiuOcF28DZBWnzce19enQa0P7buvlsLq04FEHg1btPuYiU5TejzFI7mYkw0DO099JDafk+dG0RMZgYRyQWjd4Wqg7WJwkmi0I9RUICHJkWV0x0t5IkObf0UK+q3bpDUvDZDlNbREIytUEMqrfDAUicY1L6XJbyMxLrM2Lr9OgCAbLR6pkwLEsOalVHlDIxBkZiExq0UkyyUayFkKSpTvO19BNvnm8xVklpPOU9BZSrBwCQPkT1YTK+qpE4a2IZAoESsqVhPu+rj8BgYRzW4Qy2rgJlY82QhEW2qrRSTLCzSQsxSEB1XOV5BN7ne+gsxyq/MUdJYSartR765rnwktLvO7SnWwJZnb6QEz0tLz6wva0rR5cauFUfQs37yY8iUkyuMC1/CqqW5uRwBm16dn1xYkEOBC62IGLIguX4KVUaAfR8YvjikqlClngYIgKdAOKUEF7xLgZfBIGtPkixHy/6GP1t/KHtX2B3kXuNasGFrWezOSc+Sjq8LM6YaJN6ToqcZh9ioenev4Rai6z3igcQznWPUpl09FLE8NuvmEud2zjDo1R154VtQjwlCvUVDfFobarUN9YLkedRoeJD0r6tww1DcpqPPCUKfqULvCUCfTMhvMyU315NfQ4JKVRqe2Yx0Sr4U8ZtbvlADL+axkHv9rPBmplAcSm5v2H5MWbT/6F5rRwkpqWm5U0/LwSG6Or73hkczIj0Skow8zSEvLk02fmpQz3MolFHMRpmaN5r9oKkcbRu8YKz/zqW7+K2zNyMRNMWFh4ZSHPSJsbTKS5QHwUsLQVLmHGiseN0zGSSo/0pmKLS6eyaZJrlyeGiTnyhGiWojnqtct4yBLSVqe/IUIOlKYKp4YJnzCdLHVrlrdf/rNlsbzXTMPo8AuRuVqM43KvaJYppqxl7K+kmnRWsT6ygij229I3+0a7qABpWgPZc/TurR79+hc+U+Rir0E78pydMVIfWF7BEDgLusr+RbOK3APNUKDpx9wDUVWDToMifywilsjyb1nNE8MCDhHnirStdQpUPVTPBnGS2Sdwi+LnnqTKOKs872xvP5ZGfa+S+ZGcTKygb7K44UBA2rmK46900gzqHJvdjk99ersZz+AI1cWCfvYo5E2+cePWSaaHCBHc++y+ReZFKsYu3u7LPE5m94Ca0jwEKuoTe7CTdJi1GWTf6SJ9/b5edFEIf0DFSTZ8emlIyFsBV3t1SoZYkvzW4k3UGKYmnhkiUIW0TYSVWC9u3C95OzMJggVTEYbTt0rUbPkIJtiCQdeGHg2vZHfE9zJW0DXcoMRLF46ErDoDfAw7TvdhTtxLq+8zFlOx2kbPNn7MJzTnXOK21cKrbEPA7iI9uQf0D954OpForpjgGIiRy9I4kfOzuhy7HvTGEQkTyD2BXryOmT3aXM4Yj5g5cMHRJUakItnE/sA5cncy2CxAsy9Q7DAycJN/lz5ro+Uao0Qnq7RkhV82+Iu3GJ0pTCvKphXN3ykVLvCXVhhWAyGMbJAV0BGuWIQNFOwDYLRoSCDaR5BY0R2hSe7Wn0r0gbjH26ecqZtoC+/Kk+8g1ysbtF2saea1Fb36Vr9ig/F8YAVsoqpePaRXLE7W50jf2dQOly1J/sktZOzP538H4nIr4jI34e96So+PVRuHmRNgqFs8BDf+kWDvsYWXUciMnd6Mo+AYKa22pMPRBWQDk6qQJLDgKdcsqty9YI9yWsMHqALv/UGYHIpZlcrk+NIk2TgTns=
*/