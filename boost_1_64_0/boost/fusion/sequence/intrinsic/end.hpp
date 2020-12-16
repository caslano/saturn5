/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_END_04052005_1141)
#define FUSION_END_04052005_1141

#include <boost/fusion/support/config.hpp>
#include <boost/utility/enable_if.hpp>
#include <boost/mpl/empty_base.hpp>
#include <boost/mpl/if.hpp>
#include <boost/fusion/sequence/intrinsic_fwd.hpp>
#include <boost/fusion/support/tag_of.hpp>
#include <boost/fusion/support/is_sequence.hpp>
#include <boost/fusion/support/is_segmented.hpp>
#include <boost/fusion/sequence/intrinsic/detail/segmented_end.hpp>

namespace boost { namespace fusion
{
    // Special tags:
    struct sequence_facade_tag;
    struct boost_tuple_tag; // boost::tuples::tuple tag
    struct boost_array_tag; // boost::array tag
    struct mpl_sequence_tag; // mpl sequence tag
    struct std_pair_tag; // std::pair tag

    namespace extension
    {
        template <typename Tag>
        struct end_impl
        {
            template <typename Sequence>
            struct apply
              : mpl::if_<
                    traits::is_segmented<Sequence>
                  , detail::segmented_end<Sequence>
                  , mpl::empty_base
                >::type
            {};
        };

        template <>
        struct end_impl<sequence_facade_tag>
        {
            template <typename Sequence>
            struct apply : Sequence::template end<Sequence> {};
        };

        template <>
        struct end_impl<boost_tuple_tag>;

        template <>
        struct end_impl<boost_array_tag>;

        template <>
        struct end_impl<mpl_sequence_tag>;

        template <>
        struct end_impl<std_pair_tag>;
    }

    namespace result_of
    {
        template <typename Sequence>
        struct end
            : extension::end_impl<typename detail::tag_of<Sequence>::type>::
                template apply<Sequence>
        {};
    }

    template <typename Sequence>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline typename
        lazy_enable_if<
            traits::is_sequence<Sequence>
          , result_of::end<Sequence>
        >::type const
    end(Sequence& seq)
    {
        return result_of::end<Sequence>::call(seq);
    }

    template <typename Sequence>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline typename
        lazy_enable_if<
            traits::is_sequence<Sequence>
          , result_of::end<Sequence const>
        >::type const
    end(Sequence const& seq)
    {
        return result_of::end<Sequence const>::call(seq);
    }
}}

#endif

/* end.hpp
6Vu18yCjn13rLOFgwXPt957LaLioyzxJz8Pfe+2lc8XTS1v11y7pbFFV7wexzM8+H+lcGzwLg50U0kp9yGudcu/1QgUHyj2OucHI76JOSJ95MaGXiQkV+uhLCF10SaR/G+nlIUOsYegr/9IKvQvfvSf53/cyhd5egpjgZ+d6bdk2AxNIF9dwWOcrCq2jtPerD6u/i9lByvwa0nETJfP2HZE00FR8KqSffjnSgTYHH3sNHNPPypxcks6DB8CH6q9Co4Pqat6tSYHDjRnS7hxDGk4X6Bv3Ck6jGzSkL01JOvRDoT/K7h9HOt614rd6ZUGDrzz3BLRbAVK/9WdfJejwd6GLAIx7/GpBxz4q3A4Rc+Y1HAP82KvKPoPf9fRrGabsTUcWpO5jJ8TvKBZpLzaRttqGOUylXUIaH/MKbdFiNHZ9J3qupDk2o/FNXNk7kXbNUWk9OFW3kfZtl9CeUHW51+K0Uh5QJe2mL2ioCtKuBJQGjEjzQ0brYIsudOU3m4gYTYRD1X1gjZjRlQ0lb1qMs5JU6D0oWR1LBZ3d5rKcRktnYe+CvE4KNHbH6ATTM7N5BnF7SIyWqzpd8zc0MsA8xAfyKxpG94E0csDU3y/L3FT1GNQJ6/W6Eoe2BVV9NDpe08p2P1nFUH2/Qej19gmvnq7BVOUQDLdk6/ZJ38pnCIYd4mQ/JzRah0OnVBre6su8g5RO8w4SGrSP0r5veb1Kw7ZD3tuUDtfakrbwBpVG82rdJzTaTu87zWn0poz0j3v1GOwfe0XsoTcyXLlSPi54i99wYyXWedTt8psoHWYOpBlvljSxgKM/5FsY7cH33Df/pN7NxoZnJnaWBRvO4aLaxT6v3EOhozA1iwUs2iTrWGoWq+yZB3UsP0N3+p15Eo/gtw1YsWHHe6fNOk41i8V7oTpcr77s7lAdVi9753AtDstG/6QSh/mf2fJJ9sNbJF0MYYDInDlbFTrUTfBj3usauvhQaJs7omOqdssHt9VisInUMu/WYKu5is5sh3/rPue8ispbaD1Oe/M7s6MWx81L8T0NPkwtrvZdcrEeS+aFWwSj+c6jP/j7fqGMwyOJ5yRWECbGyhPcsMsTMXd+QcdrYDuJ72a+sbbc67bni5P8iUnF/eDEJEwOxb9BipRzlcixjMgLMyf1UpADbynABYN7Er7NiclyT0FkKvrcUuVYmWEHmeWELV0O1UmEs0E5I7+kMUFjy7Gs1A+InIV2Me1QWVO9E5NSjkHk2FAvN3ec3KuXA2oU/MIkVMpZJHIcI8rcyAkzTQ44T8gmKoNYn5h8Qsq59EvaPh4LDB+nLYM0B5qklg9hMk/GwGuFnSCR0zLyyG3FLdcyWBWa+dv4nQh/aoRe7Htmy6R6dKAtllegYd7DvliRhKMUhHqM3FHlBIbvB3YapzaVszgHguBWtLPK4ych/yHC7xlJABGgEtdn9Wgon8bhJfymESbw2tkyc8ZPy6X968ydyjtpqwXdy28Z51ZWz88Js2vQYFnrXaCR8j2JnNRIc99OnZa3UTnfJnJ8I3NbZmo6iS5H9lJpZyzlDPyKynGikAWSsB8kR9ohG9iuE6ocaJ40ta3YTY2VNZCxcu7E5Pn2+ZXV96Bduviexq9of8jBejWIvMBgtx1lx6xOSPS7EP1To2XnJvTLuJlfaVvQBL9LpR1Sy4/TPLT1eaiII1mZ1qQ+36jIye0sDkM67MvdFvx7kY23zmqvL/WxRA4f0i6xAbmYQ8tMHDpOig0bE7rC9Fp+O43XPPZrVYYLbRu3WklmURkkTNmK+C4ThNc33Mi1ssg3OsvlqJq0Tf2rwDIecv5c5bdNI45bWRq1IoNdAoGy7eW3s/+XNxg=
*/