// Copyright David Abrahams, Daniel Wallin 2003.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PARAMETER_AUX_PACK_DEDUCE_TAG_HPP
#define BOOST_PARAMETER_AUX_PACK_DEDUCE_TAG_HPP

namespace boost { namespace parameter { namespace aux {

    template <
        typename Argument
      , typename ArgumentPack
      , typename DeducedArgs
      , typename UsedArgs
      , typename TagFn
      , typename EmitsErrors
    >
    struct deduce_tag;
}}} // namespace boost::parameter::aux

#include <boost/parameter/aux_/lambda_tag.hpp>
#include <boost/parameter/config.hpp>
#include <boost/mpl/apply_wrap.hpp>
#include <boost/mpl/lambda.hpp>

#if defined(BOOST_PARAMETER_CAN_USE_MP11)

namespace boost { namespace parameter { namespace aux {

    template <typename Predicate, typename Argument, typename ArgumentPack>
    struct deduce_tag_condition_mpl
      : ::boost::mpl::apply_wrap2<
            typename ::boost::mpl::lambda<
                Predicate
              , ::boost::parameter::aux::lambda_tag
            >::type
          , Argument
          , ArgumentPack
        >
    {
    };
}}} // namespace boost::parameter::aux

#include <boost/parameter/aux_/has_nested_template_fn.hpp>
#include <boost/mp11/list.hpp>
#include <boost/mp11/utility.hpp>

namespace boost { namespace parameter { namespace aux {

    template <typename Predicate, typename Argument, typename ArgumentPack>
    struct deduce_tag_condition_mp11
    {
        using type = ::boost::mp11::mp_apply_q<
            Predicate
          , ::boost::mp11::mp_list<Argument,ArgumentPack>
        >;
    };

    template <typename Predicate, typename Argument, typename ArgumentPack>
    using deduce_tag_condition = ::boost::mp11::mp_if<
        ::boost::parameter::aux::has_nested_template_fn<Predicate>
      , ::boost::parameter::aux
        ::deduce_tag_condition_mp11<Predicate,Argument,ArgumentPack>
      , ::boost::parameter::aux
        ::deduce_tag_condition_mpl<Predicate,Argument,ArgumentPack>
    >;
}}} // namespace boost::parameter::aux

#else
#include <boost/mpl/bool.hpp>
#include <boost/mpl/if.hpp>
#include <boost/mpl/eval_if.hpp>
#include <boost/mpl/assert.hpp>
#endif  // BOOST_PARAMETER_CAN_USE_MP11

#include <boost/parameter/aux_/set.hpp>
#include <boost/parameter/aux_/pack/tag_type.hpp>
#include <boost/parameter/aux_/pack/tag_deduced.hpp>

namespace boost { namespace parameter { namespace aux {

    // Helper for deduce_tag<...>, below.
    template <
        typename Argument
      , typename ArgumentPack
      , typename DeducedArgs
      , typename UsedArgs
      , typename TagFn
      , typename EmitsErrors
    >
    class deduce_tag0
    {
        typedef typename DeducedArgs::spec _spec;

#if defined(BOOST_PARAMETER_CAN_USE_MP11)
        typedef typename ::boost::parameter::aux::deduce_tag_condition<
            typename _spec::predicate
#else
        typedef typename ::boost::mpl::apply_wrap2<
            typename ::boost::mpl::lambda<
                typename _spec::predicate
              , ::boost::parameter::aux::lambda_tag
            >::type
#endif
          , Argument
          , ArgumentPack
        >::type _condition;

#if !defined(BOOST_PARAMETER_CAN_USE_MP11)
        // Deduced parameter matches several arguments.
        BOOST_MPL_ASSERT((
            typename ::boost::mpl::eval_if<
                typename ::boost::parameter::aux::has_key_<
                    UsedArgs
                  , typename ::boost::parameter::aux::tag_type<_spec>::type
                >::type
              , ::boost::mpl::eval_if<
                    _condition
                  , ::boost::mpl::if_<
                        EmitsErrors
                      , ::boost::mpl::false_
                      , ::boost::mpl::true_
                    >
                  , ::boost::mpl::true_
                >
              , ::boost::mpl::true_
            >::type
        ));
#endif  // BOOST_PARAMETER_CAN_USE_MP11

     public:
#if defined(BOOST_PARAMETER_CAN_USE_MP11)
        using type = typename ::boost::mp11::mp_if<
#else
        typedef typename ::boost::mpl::eval_if<
#endif
            _condition
          , ::boost::parameter::aux
            ::tag_deduced<UsedArgs,_spec,Argument,TagFn>
          , ::boost::parameter::aux::deduce_tag<
                Argument
              , ArgumentPack
              , typename DeducedArgs::tail
              , UsedArgs
              , TagFn
              , EmitsErrors
            >
#if defined(BOOST_PARAMETER_CAN_USE_MP11)
        >::type;
#else
        >::type type;
#endif
    };
}}} // namespace boost::parameter::aux

#include <boost/parameter/aux_/void.hpp>

#if defined(BOOST_PARAMETER_CAN_USE_MP11)
#include <type_traits>
#else
#include <boost/mpl/pair.hpp>
#include <boost/type_traits/is_same.hpp>
#endif

namespace boost { namespace parameter { namespace aux {

    // Tries to deduced a keyword tag for a given Argument.
    // Returns an mpl::pair<> consisting of the tagged_argument<>,
    // and an mpl::set<> where the new tag has been inserted.
    //
    //  Argument:     The argument type to be tagged.
    //
    //  ArgumentPack: The ArgumentPack built so far.
    //
    //  DeducedArgs:  A specialization of deduced_item<> (see below).
    //                A list containing only the deduced ParameterSpecs.
    //
    //  UsedArgs:     An mpl::set<> containing the keyword tags used so far.
    //
    //  TagFn:        A metafunction class used to tag positional or deduced
    //                arguments with a keyword tag.
    template <
        typename Argument
      , typename ArgumentPack
      , typename DeducedArgs
      , typename UsedArgs
      , typename TagFn
      , typename EmitsErrors
    >
    struct deduce_tag
#if defined(BOOST_PARAMETER_CAN_USE_MP11)
      : ::boost::mp11::mp_if<
            ::std::is_same<DeducedArgs,::boost::parameter::void_>
          , ::boost::mp11::mp_identity<
                ::boost::mp11::mp_list< ::boost::parameter::void_,UsedArgs>
            >
#else
      : ::boost::mpl::eval_if<
            ::boost::is_same<DeducedArgs,::boost::parameter::void_>
          , ::boost::mpl::pair< ::boost::parameter::void_,UsedArgs>
#endif
          , ::boost::parameter::aux::deduce_tag0<
                Argument
              , ArgumentPack
              , DeducedArgs
              , UsedArgs
              , TagFn
              , EmitsErrors
            >
        >
    {
    };
}}} // namespace boost::parameter::aux

#endif  // include guard


/* deduce_tag.hpp
g7SDug/shpnRpi009BztHfdUe3aDumdr66Tv3KLtWe1cD8wPaPOQNk7ZK9T3pS0Tv5q1ub0dC9xr1PdsbY6Eo0bfkzoucfVgTluDOW2NhG2H1nW0MxKGJn0/uD3hnmov0j02fyQxjHtHXOMc/FxwQvq8lADQZZ0G4Ttyhu7zXJ8LHgv/XIBdZ/9W3VDv3r9pXV0fW9HXP6b7elsZEr/scVzTIWB5EmLOBdqXZiS+tT+OJOyK0hXFNSSRCnt6oL7U4Z5rPLGvn6kblG4NyjxXuMdV9CVdEtCnTBV7rH1LY9T9szwJ/JuGuDwb2fyUfWsoe6uUl+773Ih+i3u1mHUzcBZFSdDZow3KTMdNP0cRB8wlDkF7tkiYHPlwTM7E74mooCHPkQ+FoflQrXaMkHx4Nk3lQymBct8/ISRdq+vs7xEl6n531zyx20232kfXtLfrNuhnWNd0R7fFfaNm2dPdiGNniaOUZ0lf4qLTXPJHwpgkad6gn2eD03sh/6p52VLuc5AX8KcpNL3rWpPeTS2k9wPqfoJreotdZ3+kn51vVvezPIPdy7+2b/TXzR1pvxICfZE/ukv8yvj+8b3ptX1tIjtzt7VpX6PTPjidK+WhbL6k87nIM0Yb6pLO9bVVbLUdSOdNKWabYcX/TWVnDnOBvO5tq3sbovfT+Zu6P4Br9322xL7ei/ES3NgVwT7IZloRZmkLnGlFOKT8DZJ08XfS4zKaSbx45vVU6cIAUKmKRwJm7KO4kGu3OIu+N+Iz2XCP8Cj31Dsx9oPeiU8YVqLC73fhvg9D6/fTcN9XIdy+Fq3fP8F9n4pw+1qE3//huzWG+ZG9A8956bqDDY9tuO+TnzW/uTTc/gyt37fEff+N8PuKrFDh6XDAf21Znz9MeP/R7J90XjGzPPz+J+77b4TfF8V9v5Hw+3K47zcSfl8O931Rwu1P0vp9Ntz3FQm3P0n4fVc+lGch/tSYWCbs4guMpRnP8QVcl9t+l8nv5fxeJr9r+S1zImW8VdVz7gXPibzII3MvfTK2KOOmht5Ufg+RaSToNPrhBzAJfgy7yHU3+BFME/N0Mc+Q6+HwEzhKrsfKdQ78FE6Dn8FzZO3DuSAWLoJtYCnsAC+Fy+FVsBJ+Fa6ATbAK3gKr4WbYHu4Ue0/AjvCXMAk+BZPhC7AzfA2mwCOwK3wd9oS9veQpzIX94XQ4EM6Dg+BCOASWwmFwBRwOV8EsuA6OhF+H2fAWOAY+AnPgE3AC/B2cDD+CU6HRAcyA3eBM2AuqtQ5wNhwF58CJ8Bw4Cc6Fs+G5cD6cDxfDBbAMLoTL4SJ4GVwMV8N8uB5eBO+ERXALLIY7YSn8GSyDj8Nl8ClYDvfDar12XMYHYTeXclYg5azQK2NnMp6HHvNyVfjU32pZ43UjzII3w4lwM8yD34IL4e1wCbwTFsBvwyJ4FyyHW2Ed/A68Sa5vht+Dd8F74LPwPvgBvB8mE4YdcCR8EE6AO+E58CdwMXwYkgZKv1bpy9xpuFbuPwUfhS/C3fAT+DiMIb32wET4C7gY7oV3wqfgW/AZ+C7cDz+W67/LtS8qcN0OGtfJ8HmYBm+CPeVa8kPe4Sjbp8mPVea7CJgkevY1f2/IGqI3YVv4J9gRvgs7w7/AFPhn2AO+DXuJeW/4jtT/Y3Cc2MtV92WPDf1MTp0T/2Ngtvi/DD2D5VIuKmAiXC7+VYo7M8xnUDhe3LGvhbxU4lEr8aiDmXCllLMGmCPXskZFnsmoS8o9BM5xrIV8SeJ/CPaHr8Ch8DU4DL4KJ8PfwnPFXOaUy/NTIJyZjjnlKTJHvAs8GHX6eeFbuLcbOTnSx5zMkLngeh74VsQ+9zs926fnf+fyW+Y=
*/