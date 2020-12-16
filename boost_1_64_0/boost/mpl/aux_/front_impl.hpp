
#ifndef BOOST_MPL_AUX_FRONT_IMPL_HPP_INCLUDED
#define BOOST_MPL_AUX_FRONT_IMPL_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#include <boost/mpl/front_fwd.hpp>
#include <boost/mpl/begin_end.hpp>
#include <boost/mpl/deref.hpp>
#include <boost/mpl/aux_/traits_lambda_spec.hpp>

namespace boost { namespace mpl {

// default implementation; conrete sequences might override it by 
// specializing either the 'front_impl' or the primary 'front' template

template< typename Tag >
struct front_impl
{
    template< typename Sequence > struct apply
    {
        typedef typename begin<Sequence>::type iter_;
        typedef typename deref<iter_>::type type;
    };
};

BOOST_MPL_ALGORITM_TRAITS_LAMBDA_SPEC(1,front_impl)

}}

#endif // BOOST_MPL_AUX_FRONT_IMPL_HPP_INCLUDED

/* front_impl.hpp
S/ah5rzab1lb+ETkOCFkIuFqqvWquxKbUcs8EM240aP5Rl6x8DDAWivveBKwFcgjQh6/T8QaE3nKLd8BtJd+OBPT/s2+JUY77gyNhfB+HopzEqqLQjpj9Ab7/E3lqBXcpmJoyrBDx1raIg3EgP+SJqQJup+HH2kmTHNfyzp/tA7TPCUpyq5NWMdtkxY+FeJ1dugLe+OJ4VWtvg+3xwEPD94/1bHyMLyxYfQqwyp/vS3Kdj0FnJ3LYOioGW4pgYBivf6auG0nv2fpzjxSXdMGxZhG/n9aH98TO5oY32v7Y8Y3V41vLo3vvkprfB0Od3w+2H8SHCrgfLMea1VBa2qsv1fKBj9fL9pOLW0ABQlfZNhZJ5FHsogw6BlMoyN/Q2Sdg5+9BE1QlErxwvCT+Mp10FaoEz9LxKQnWfYtnhsKDi72O1WISCQ0IAEhJPG7Hr9xYhMElsqpW+xOOnL0YLN/JTjTyVYuk30+3Pw71DqNg9cdUnPsTJudPfyU5fnDKfJXnj97qg+guVfeRZNS6bAIKfTk1NBCbsVdkguXPT4vIHA17gkv4mkDHV4sjmg5pOIJQjF/xiH7aTkdrfrIJSFa9YVPUI+wcvDOEoQ7nE4u4CxZxc8DpVDp8PTj+w7g1aw+zuX7ot/3dVIkTYhJ4Smh2GLMvyxNUJGjsa0WbsH2peEK0P2NI35GCsV2YWjuEZhnhviJEq+jRENCSQf6sV7kTRQ/UcFRIkr8USQeT4muwh7UFui4+uyCOrR2k8jsimTBuc3OqQOYrsVmPb8cO7+KEaXnGgDyWXE2sghVwq4yQagg11+NHKLKKOprsB9iddeLlwnxEKrE04MKVkxM8mUJBtIGLhzuGvCRExy+Mh7jNCwGP/KDH31vj3zL/wvJCDTi8bkBLEGLY8/XaU4qLBJps3slHeAFyvcSb23DfqHCIW7wPPOyT4BqmPZn50NjSFZU3zG3QZgw/1EU/8SjblgC6GK/cEC6YJ84/tL8GsneI92T+j38KWmyA4s+UIiLicVg+jbXUYGiaOd+OIJ2YVmwA8u8hhymYzR9P5//IfC9RvS9ocitxEGzCHfvf1Opp93kpArBZ7VuJxUus2SAKPyULnwRFbZoF0IfgnYZXNhVrxWtsqKMsdwWovVy+P2hhaMVrtVpc4P+RmnnUaM5XkTK9caqzsABaYo4xBXi7gl9oOiKcDewsxGwco9KxK7qBOZ9HSv8DMDlds5e7CPjfj3bmZjtll1KlfZqLFYPXHAzHkVpqq2mxiS0Oe4BZQyBVh3cKrRY0o1HddsXo+3LdNtpaLsLmy1Lk836svE/qOdjpb/1+Uc1repvLdrfpH6Y+SaRurH6aCviaK+0umV9s5e2tZz/BV0Bzeq/xtF/Qiv937av5fx+jzff//n7W++/9KNW5r+15fxTm61frrmR6VdKkUsj/ff3WV9Bh+uG4ql/wT7i3giu8jTCqdkFvquHIeC20HE7DhwKH50rpBDOomJ+SxeOEJ0JTbZNhHqzc32Cne+BEkM5EHpZl8PY5Zb9C1HGFYpewvUon01vblLyGon+WiJIIY/aqLmqcDL7stTsacX/WyXgxf0zDdWbAUHiw5mE6xlTdNTwCL+rtAMLQWwBpRT+SnKRD1ac7YywimJ2zkFqKpeuui750U1piL5HFbJzG4LJ1l3WsNntc6ihtMEhaXPynJ6VWh4mEXqz1lQYjDe59B42/FUMioHJi+5iO/rSfXQvmLRCxNIYVXAwmKqYGpOctGuCHYDTJXJ3Kr3IakQL7iwmXeUpbCewKYioycCTPmHJ3Q1MMcqqZqbz8ZQFoVInnZSux4R4Gw3w19kQClMvuHtpEKT1eVFRZxuf5do=
*/