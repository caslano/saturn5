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
p93FGi/E7hzrpogXDIVDQdzhdAO3R5TtGQYebAtwI1nTIjhmTR+aEQkbtm40BhcvqLIKLHqMOWn/BGsfK7OClEjUnCpi4aZH8OaakmZO3ChqA4HxNWbdxLW9YTP3tFLOBSBE9Qz2r2HRjGh8vIK7Dde9FqubveO06whHNm5SpGOnbNyB6cxB+LajRmdkzsass4nM3JTdHGdbN3P2GtuTS6qddjJkU6zRjsfEZaScnj/zsbJMi44qzMRjrsi60syusEYOnGiL1DPTs46ybqkrw4XxFjjs6iTrpkjnpkgnkSKcSNCObEsXmTlmTfPqZNoGcDcGWXOMwQPMKOJiuDk9ORN3d1s3GnM9tNTU9YTbcBnj5f9Oz5/7WFqlR0cD1v42lkWpUTVFKcKyLLxNdEdZN1UVslpgDfCKfvmdYA1PG7yQkzLtzrGOcka4sVxox0gRIvo0S8de3Z5kzcAtKr9QIzLCn9Pq537kxDZx3F4ScHMX03Q7Z914fA1Yw/3MTU3xxiwgFfe1tkqPiQGs/WwsS1IjawqTAe7akvT68mzgz5uqCmgqhKJ3qZDgJldVBcCKxTrd2di64TUL4G7krC3HRaeTaFE2Wo7dVFOCl+7SV+y2QNwka654/Y5rzNUU7UyTa1MUkAtUBClI/AWG3hjJjOOhpIGHMHGDXD3IhkzOKes2o2prtHE3zswNxHAzZqJ2uycn7PopZO2BLyIG
*/