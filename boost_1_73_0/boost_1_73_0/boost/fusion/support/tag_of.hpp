/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_TAG_OF_09232005_0845)
#define FUSION_TAG_OF_09232005_0845

#include <boost/fusion/support/config.hpp>
#include <boost/utility/enable_if.hpp>
#include <boost/type_traits/remove_const.hpp>
#include <boost/fusion/support/tag_of_fwd.hpp>
#include <boost/fusion/support/detail/is_mpl_sequence.hpp>
#include <boost/mpl/has_xxx.hpp>
#include <boost/mpl/identity.hpp>
#include <boost/mpl/assert.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/mpl/if.hpp>
#include <boost/config/no_tr1/utility.hpp>

namespace boost
{
    template <typename T, std::size_t N>
    class array; // forward

    namespace tuples
    {
        struct null_type;

        template <
            class T0, class T1, class T2, class T3, class T4,
            class T5, class T6, class T7, class T8, class T9
        >
        class tuple;

        template <class Head, class Tail>
        struct cons;
    }
}

namespace boost { namespace fusion
{
    struct non_fusion_tag;
    struct mpl_sequence_tag;

    namespace detail
    {
        BOOST_MPL_HAS_XXX_TRAIT_DEF(fusion_tag)

        template <typename Sequence, typename Active>
        struct tag_of_impl
          : mpl::if_<fusion::detail::is_mpl_sequence<Sequence>,
              mpl::identity<mpl_sequence_tag>,
              mpl::identity<non_fusion_tag> >::type
        {};

        template <typename Sequence>
        struct tag_of_impl<
            Sequence
          , typename boost::enable_if<detail::has_fusion_tag<Sequence> >::type>
        {
            typedef typename Sequence::fusion_tag type;
        };
    }

    namespace traits
    {
        template <typename Sequence, typename Active>
        struct tag_of
            : boost::fusion::detail::tag_of_impl<Sequence, Active>
        {};
    }

    namespace detail
    {
        template<typename T>
        struct tag_of
            : traits::tag_of<typename remove_const<T>::type>
        {};
    }
}}
#endif

/* tag_of.hpp
avhZV93KwCqgNjXDZRNQVoQmcd7ceK5pPjeXjFoZWGVE5YH+inEtkZ8vDzEt/vw6MMLNKuIbvvXkRFVYoTdwo7nPfSnZVQRdfBiccvbA3rHNe3sY99iQuGRtL+fZreMjN4m4AEFpXGGuMBedzq/yhE5fhkM9o8OX9T8BuHKYmCwI+CZLc538rNi4yqTDb7J19VMdv+Hm1R/8dQ8cqbfrao5NIW9UFEqDfGA9MSmWD6MmTOASLalJ6KxrZofEzTjfiELBFCvN03CYY75DCo0Gc4ygbaAHI52GeIhgzopMJB4vVwV4BpzEG8DCnJSFPYWZUKRaqukmkIxCo5YGrKfkC9ANrb9XY0Uuw3K32ct1exgBqt3+Uqrdw3nPjVBpfESUOdM0robsUOdCy1TA9Sbkr3rQ7DpTvuUDONC1A/u6IXyF/yy4+/9e9F/wopeIdaNWrSPjVY+6JgN2nUE1+dVLveN1pONbe8VEVZ2JfNM9Pu1eVY2kXa92hgFdjBoCPDzxwXzLMEUjH4U3MXmDeLwMRhGD3DDEHVzOJPkLCnxnIV6nAC/w8hdYcu4W/lFgzU0e+rcxstWq6dFufUzCEfxcL+hRB2FZBMS7GCKFZnMtKM3wEjwAD0kTdK2cWLtsHDZ6sn9HJKmRjfKezF/n
*/