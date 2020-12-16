/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_HAS_KEY_09232005_1454)
#define FUSION_HAS_KEY_09232005_1454

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/sequence/intrinsic_fwd.hpp>
#include <boost/fusion/support/tag_of.hpp>
#include <boost/fusion/iterator/equal_to.hpp>
#include <boost/fusion/algorithm/query/find.hpp>
#include <boost/fusion/sequence/intrinsic/end.hpp>
#include <boost/mpl/not.hpp>

namespace boost { namespace fusion
{
    struct void_;

    // Special tags:
    struct sequence_facade_tag;
    struct boost_array_tag; // boost::array tag
    struct mpl_sequence_tag; // mpl sequence tag
    struct std_pair_tag; // std::pair tag

    namespace extension
    {
        template <typename Tag>
        struct has_key_impl
        {
            template <typename Seq, typename Key>
            struct apply
              : mpl::not_<
                    typename result_of::equal_to<
                        typename result_of::find<Seq, Key>::type
                      , typename result_of::end<Seq>::type
                    >::type
                >::type
            {};
        };

        template <>
        struct has_key_impl<sequence_facade_tag>
        {
            template <typename Sequence, typename Key>
            struct apply : Sequence::template has_key<Sequence, Key> {};
        };

        template <>
        struct has_key_impl<boost_array_tag>;

        template <>
        struct has_key_impl<mpl_sequence_tag>;

        template <>
        struct has_key_impl<std_pair_tag>;
    }
    
    namespace result_of
    {
        template <typename Sequence, typename Key>
        struct has_key 
            : extension::has_key_impl<typename detail::tag_of<Sequence>::type>::
                template apply<Sequence, Key>
        {};
    }

    template <typename Key, typename Sequence>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline typename result_of::has_key<Sequence, Key>::type
    has_key(Sequence const&)
    {
        typedef typename result_of::has_key<Sequence, Key>::type result;
        return result();
    }
}}

#endif


/* has_key.hpp
u7dKGvqkincaeAc5WPaBmZOnpmfgnp/6pQ9SOtpTKjK6FYxw7MSYcHX0io/5zGYdw+7wOwvK3b2GQWdMxORDGgZtoDBmi44RTYl1mhqmGMzZIOyGNDqxIUM5/hbEqcYNaFNwcCujw8MLJ6A9wgj8Xu+LhZjvIUbzn0LMW7ZxjFSVR8WVb4C3dQzPFcNlbNfo5J3h2zqd5r/HdxANh35PGMdXw2CVpE3RTobpr/I0/fL9tfid9/HK22y8i9HK1N6HVzoLKt+PKrS55fcgrbtb0sq5Tr5ffvjndGz7ARwe4aZ+o2NbjUv0nKKv6PEPno15hSkG9krmOTCiIHF0dIzVhu1YW41XO0gxEIWA2eXAsqzYpFUwa52FnlrOyGaVTpPkoe83xYidAI9MJcv6LeJo7AuMPTmk0s/X1vsbFEPrjeMaMczLslbONQ2jyzG2SAyNmyHr9DXEkBhTKMPZivTGmBG3EaPFoMJylkYIRovNcRfpGHsDeRe3MVpzDJq80scD13QgXPSG8zywNWr5FTBmijUKejYLgDK71CnmQqD1oa0uqTSlz99hbVbqDzG2yrAFLP8wiSm0qR6jxRQabMbBDAo47NsNOBoH66aGo4aQL5S5vppxrL4K1h8mWG5wV8bOY8Z/xC+HYPkTNW+d52EsA4LBcqsxaMa3EpySK1SxiSYYLSYP4o6OEJw2P6BdrI5jyks526p08lnld9Bw5LMi7n3ba3FaTId7Go62W0+p61t2NGN7aizfnVUcNi+W+zkNo8UMwnIP7qLYphh1nyY4Mr9iuft2E0xPq69q9yGx/ZVZwSPreWEP/JvEuQEyj3OTijN0de10nCD28g3HtnpcWTufhfoLveS+4vImoNfllF47j367N7dKv104/izPd98j8zrfpvpmvpO7LW+j6uJZZ4Sej5LQ9mOvlRgpuMeCimpi0xNqHccHkTq7stxe6iy3ZY6IQaDXxEFzNsPvjxC37BrBaXHLsC0ukLaIjcTN0lbLDTbaGPsHtj5pC/hYiMyUp2bTLHXl75vwd/b/8vdB/B0uByv7p2ey9sGMnDD64dJgrjdAYuxoGNgQv729irnIcM4e1LF8peeLNY5FaGMdy0cjOQ+MDFVx8/C5JP2mRqe5q08PV+jcKQn5NTrN69PdUqX3Ftf6C3BrIGXcQww/VND8QeB/SOn8QMd+wPb4XjOGfTWUFY/U4MrNIX6Haxqms7Cuty+edwiW1x999DT6ahtuOsAanQjEsj+4vRGPtt7YB3ZUsHy7JRYXPDsijvqhTcDQhV0m4HC9qMUd5h52aEu4qxEHPmNKfJPdTTi065Y+OHvqsUorYZv+dlTHCltGBY/f/PKTKJ7thooqqTk39tZhVokt34ufrGO4T6HMHV7BVH2WL+6j9OI7cEPInnpeeoqGQx863FvoGPS1JTmrNBz1s8VYXPs1nOZji3FuNKzmX4vfa+GpGlb3rVV9yzQ89avFfdCYhqv1Vbuj4ahPKvo5P60eJ7or+q5qON0XFX1AH9Owmh8q+oBqWPRBQx3jp2sY4qeGZ8EKDsoEjwRJnzhA6FoOmisVenlao/3v1c/QMLX974aGq+9/b3lcwzX2v3satrn/feSZOra+/8l47jpej1FwXcPpvpr+szQM6aN45tRxeI+IZ85n6xi9H7NLHQ1X248vabjmfjxxUMfSfizL/4aGpf6eeMfyXA2H96J4l6th9DHRfZ6O0ccE/Hl+Bbe2zEYF0rsVOl9Ope8CoxNfFb5P4fSFQ1U6WlIj5msaRveJyV+gYeDWUrmHJXSybcO9tf9CHSPVUc4ptTh67zv+Ih1Tja31uRpM9W544sUSw7cseDmMvlC1GBrr68U=
*/