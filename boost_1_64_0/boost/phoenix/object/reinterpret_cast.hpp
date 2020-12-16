/*==============================================================================
    Copyright (c) 2001-2010 Joel de Guzman
    Copyright (c) 2010 Thomas Heller

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#ifndef BOOST_PHOENIX_OBJECT_REINTERPRET_CAST_HPP
#define BOOST_PHOENIX_OBJECT_REINTERPRET_CAST_HPP

#include <boost/phoenix/core/limits.hpp>
#include <boost/phoenix/core/call.hpp>
#include <boost/phoenix/core/expression.hpp>
#include <boost/phoenix/core/meta_grammar.hpp>
#include <boost/phoenix/object/detail/target.hpp>
#include <boost/proto/transform/lazy.hpp>

BOOST_PHOENIX_DEFINE_EXPRESSION(
    (boost)(phoenix)(reinterpret_cast_)
  , (proto::terminal<detail::target<proto::_> >)
    (meta_grammar)
)

namespace boost { namespace phoenix
{
    struct reinterpret_cast_eval
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
                reinterpret_cast<
                    typename detail::result_of::target<Target>::type
                >(boost::phoenix::eval(u, ctx));
        }
    };

    template <typename Dummy>
    struct default_actions::when<rule::reinterpret_cast_, Dummy>
        : call<reinterpret_cast_eval, Dummy>
    {};

    template <typename T, typename U>
    inline
    typename expression::reinterpret_cast_<detail::target<T>, U>::type const
    reinterpret_cast_(U const& u)
    {
        return
            expression::
                reinterpret_cast_<detail::target<T>, U>::
                    make(detail::target<T>(), u);
    }
}}

#endif

/* reinterpret_cast.hpp
ndpQPzGqXfhbXRe+/i3RVvujqa2OSdafEyWCr+nZx+YlsVgz70R85RAhd9YGGjT3qfahod2E9Pxj8/qLllBaj1fDy0zmUiO3sY0HfxlrMtHk7q9E0BzARtBO/ISHp5Vyvc9akm7Uc35BlsW6NNWocTbs6VHD4JL91pJYpPImBJELYT6tDtkUdm/fKGJPGnTzh8ohWWFTGB5sdlcTTiNwuvpqkMo8yrpttHlwySFXu8ZkRChkOKl39CEuP6Qy3TFN5fjr+wTHx0SFHtvspX/CzaSTm8HNP7XJ3TPZrc0UrOrFK7vX6K7GQ41nJDVC5URJQLvHP8W7km5pTEE7KBEeRCgaI1m72LrSFbrYWrBAK+sZpOtvjzQeNVZFaqPGI8bmRo09lZous0cq7ZBGeqja5PoJq5jRRlbQQoNFqPSMXaR0gI0k9htz5a/f1MR+Y5788Zua2LcCWv8sWO2FOPngAKN1aZpR1+yhK0nDbf2wCdls+6PfHtEJygCkaC8H99LvXRh1vbtfjiOBd9Hywh4QZrFUbigxYeTHbksgJfQCZrlyQyn05OVSivFg36Rwr+TsiF0MXEeKyz7iyV7vzV+fZzcNEdwJ5u9lrVhucD2kSELmEc/SalWwaWAS7e1ZQX7mM3kiXdepGqJKa641hlBzXfGmkNff8o8BHVEvq6e699GtLJwLYHhZhzT/OzyClONhvTWh4UcbC7Et5ll5kooxRWgD+ZFIGYEctagNb3BRtMdmNx0lax2y65V/5GgbXfSzmynaKNciSr1+mOp+y0j1ykkVO9+Suim/k28wbnuAB3JQeZp28Ki2vfhGk7bH+51OOLu+IWq7HbD+bqdCY6vB2Z6GkaGiSvmyMiEG2meM6mgR77LqRua/fKeb7brnk+4qUI1eZ96v9qeS+xCH91kxp8hjrRmfKz+6gEnWbdjBLw8ckeK06jSw7zt6v9RHOd3fx7v6ihu0akct5J6gvbr/2WyO15F3O7JzlmOL1GG+j9JUrcjMt6vykwHzONnMY6isXHwPaYpzzR+XGTRNkBXRnCYof13TBPeoepo1wQloAu4uiiZQRzyFe3kLFE2wAZogfwOOk/aomiBzA6aSHBL1Bzb/pG95Ekhr6nzaco5faIHbZtEIuG2ddiAvGmAA8rDW64VMasewRzQ3dJ7eI0TlF1JokJ0X0WTqdliABRziEqG7vIG7+A2qeq7j4DXisZu5alO0FcmVS9U5AO13DA50VQsqbpakqaIs/DKRuDOZK0vzeV6p7VT+bv7lncrLn8ufS/ho+9FvOHm/yCzeJ6KhYR4veM1x2ntaS8XGhnkKpsWhsMfssOjWEbY83UwPe9u/FRaYuIQftrmFG5VfhrZyr58lrCUyeVfJRkXmN9A5bYN+VTkyT75LZOIiBDW5RpryhSI8uUbaw3WIH7XrxfD/rBFls/uf80L791/dH2Y2MlgxbcuR3/1KLPOPqBu/6k+p/biT6WIaRzg494XdadDaKwHlK5eVF8eohvdX2cs1FZpMZ80rd3E5SCfsob0MR9MDoJ52vvh+cT+fpHv/EVpeLLqPhq0SH8zC8mtv+NbmYDYwtGEXUf1pYFRk0d36eYVUcJv4lcVlxlIDfLwSq9PdK4h3yzjajdftt2QhRgt6MrJwk4WPf2sD65re+dPKQkx6Vta8ZH0EFdu6FOshtA+jaAi8CWznbZxL+Ah7G8x+atUTkQ2KmQivUTcioG1RbjKHHkTgvrmFzRduO8ltzPDlKohJnJrsZBuKawUEo6/Qo9+nR1+lBBjsgB7sSAjMXRGPN+6d6iKK7t8+P5lDXA0LF57M1G3gff0tjtCz0bOnhja0Zk3RXvjbzpYxTgvDjHE=
*/