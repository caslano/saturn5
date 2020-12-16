/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_CATEGORY_OF_07202005_0308)
#define FUSION_CATEGORY_OF_07202005_0308

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/support/tag_of.hpp>
#include <boost/type_traits/is_base_of.hpp>

namespace boost { namespace fusion
{
    // Special tags:
    struct boost_tuple_tag; // boost::tuples::tuple tag
    struct boost_array_tag; // boost::array tag
    struct mpl_sequence_tag; // mpl sequence tag
    struct std_pair_tag; // std::pair tag

    struct incrementable_traversal_tag {};

    struct single_pass_traversal_tag
        : incrementable_traversal_tag {};

    struct forward_traversal_tag
        : single_pass_traversal_tag {};

    struct bidirectional_traversal_tag
        : forward_traversal_tag {};

    struct random_access_traversal_tag
        : bidirectional_traversal_tag {};

    struct associative_tag {};

    struct unbounded_tag {};

    namespace extension
    {
        template<typename Tag>
        struct category_of_impl
        {
            template<typename T>
            struct apply
            {
                typedef typename T::category type;
            };
        };

        template <>
        struct category_of_impl<boost_tuple_tag>;

        template <>
        struct category_of_impl<boost_array_tag>;

        template <>
        struct category_of_impl<mpl_sequence_tag>;

        template <>
        struct category_of_impl<std_pair_tag>;
    }

    namespace traits
    {
        template <typename T>
        struct category_of
            : extension::category_of_impl<typename fusion::detail::tag_of<T>::type>::
                template apply<T>
        {};

        template <typename T>
        struct is_associative
            : is_base_of<
                associative_tag
              , typename category_of<T>::type>
        {};

        template <typename T>
        struct is_incrementable
            : is_base_of<
                incrementable_traversal_tag
              , typename category_of<T>::type>
        {};

        template <typename T>
        struct is_single_pass
            : is_base_of<
                single_pass_traversal_tag
              , typename category_of<T>::type>
        {};

        template <typename T>
        struct is_forward
            : is_base_of<
                forward_traversal_tag
              , typename category_of<T>::type>
        {};

        template <typename T>
        struct is_bidirectional
            : is_base_of<
                bidirectional_traversal_tag
              , typename category_of<T>::type>
        {};

        template <typename T>
        struct is_random_access
            : is_base_of<
                random_access_traversal_tag
              , typename category_of<T>::type>
        {};

        template <typename T>
        struct is_unbounded
            : is_base_of<
                unbounded_tag
              , typename category_of<T>::type>
        {};
    }
}}

#endif

/* category_of.hpp
Obq+evg2zvSJT9Ifaj5bTpLmDzSNuNej9O9rOnWdZ+M1zXT0lWGf9sV9hkb4zJ7xoI0VAi/zwMZmE2nPdmjndQAVh+/dBxxaE8DE0uZmLW081F44LG3BoYE6D84EVm+sjh2BcWNOLUvn9V/wLMVcvvM6ou2jTqw98jiMg5b+htc7OrXjeawStnW2lSnUk70U+sViklKKMKzYCw0M5KDTUTu4Y40NTZKrqBZMA0/pn0D/VPon1j9C/2T6R+ofrn96bxbe5Kb5mLQuchlGYZNiqn9q/VMiN94fne3am5Qp0xcuuVRpk8CT9c/phhdLqPBv9X8toU77Wd25jeSRsKqWdR5AE2H6T8O/LWIyJc2pRirep3Tt/wfS/iItZSmDikX9c8xfXNyJUpSRzEN9Q7C1gTY97rj43uBUUMWN9OI7VdRFTCNdX2hoEKH/YgbpjRQbAO6P5vYD3fq+xTKOpq08PmkHrDzVcEtPu8sQO6iJxzXcQrlbnZ4UY0ttbZ6DpwLZCsrwsyluce3c87rQXuMurTcNHMz65tnl9XJ4YXPrRaebGM9TmNaDpywu0mMeFIunljdWNi9MbX/dYKbc/hYl4zKI0iyuGApLc6/W3E0O9c96063zKLTL+qexz2r65YX029CiI/zY3JmNMNlN/fMcpC4jtVHlrumfczaZ05jsFpuy4/rqW7Qd7JK+zVpnjzx/fs79H2yzO9wI6ou4E4/0cHo90GEhZXOmbNcLHULuqea/9X7g4jFNL3lZn3paG7qu/f5y/T04lXC9svCEn9JrUJdeXSX6T6fHfCVgaQr0HuRqK4/DF4CUuPc1aoC0EZgGWz+50/h9fA5OGBuO/P6ioenJW7u52EI/mW+7fje9RwGJwNBhesvTrGHfgUJf+6W+V2vuD/UzykYfPANz/m/094avfXuLcauA/s0Hwtj9JXkbDGVqzkvIfx35m++Gu+W/vb6TQnpDwhgkDwW6/su/2vQ3lyikNdXZgmXVtPsboSw6986p650d38bfadsKLu1tu89N43f9bnE85cbzRVpzIYaF31xx9lgziBmNhztQwCYZzPf++5CuXdpa/aL7HdK2Dev4otxPMCR/3Fs4GDMV2L3vAU3z2gz9bnyW0mmbOnPl0YMa58kM3oNcO0/0Q5InQltTMduq9I3NX8737EeTuJB1IJg6VSWdIT801nDF3nGPtE+kF2sZ0KmSS26kT70E6c4lN73j/ra949ZAvOS+vZHTq00eKzsXLrwI5/xdOj+fftEYjpiLMKyCsYBVQ/8N9zJH/4rja/WFS7v6jDlEPzHne2+qqjKNIh1K/Wb+YxbWLr25832fU1koE3mz4w7oUrq64JGbHs9YVOaSp5lkT9vcgW6BHmkfEULDwt+axwaosRbBkxo7jG7OvXLenXPnTvTm3CHMN80ce/Gabm8tum2UlruZ7691vsMN9nDX+Dk/r+XA0ppv/7gL5Nd8a8/cOu3nAO6S+bbUvEVuvwd6LW2+wyS71YSYa/Lc1nNj830No242+hIjF+++RuYn4Gm/32S/b18YNTSc096ONDqnafqOPgM29LY3WoTGtvT7al1KQ9cEbY6w3cTmXFtpy6TnuUsvJnMqzpWfvXbz5krdzjswkuEoA2ztt/vfXa9zIpN8MSu543MGhPtbzTyDbsasf6eGtvc88zdKp+VxdVIzGqdBZo4233+zD7/jHA00c6eENM+X4irSYCy20y/W54dIw3GK+o7FWaRtbJJZ3db5FxbjIrAuK4eQrjPGMv0Bv9v5+vbon0rTtvV0YtfrK3o+UZvrLzr2yLl5rVXRCkM738x9jdC1mgB5L37dpeHxH+lHv0ro6Nv+Fua8vAPnLC0=
*/