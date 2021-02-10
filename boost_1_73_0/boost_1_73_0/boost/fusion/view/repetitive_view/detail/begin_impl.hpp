/*=============================================================================
    Copyright (c) 2007 Tobias Schwinger

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#if !defined(BOOST_FUSION_REPETITIVE_VIEW_BEGIN_IMPL_HPP_INCLUDED)
#define BOOST_FUSION_REPETITIVE_VIEW_BEGIN_IMPL_HPP_INCLUDED

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/sequence/intrinsic/begin.hpp>
#include <boost/fusion/view/repetitive_view/repetitive_view_fwd.hpp>

namespace boost { namespace fusion
{
    struct repetitive_view_tag;

    template <typename Sequence, typename Pos>
    struct repetitive_view_iterator;

    namespace extension
    {
        template<typename Tag>
        struct begin_impl;

        template<>
        struct begin_impl<repetitive_view_tag>
        {
            template<typename View>
            struct apply
            {
                typedef typename View::sequence_type sequence_type;

                typedef repetitive_view_iterator<sequence_type,
                    typename result_of::begin<sequence_type>::type > type;

                BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
                static type call(View const& v)
                {
                    return type(v.seq);
                }
            };
        };

    }

}}

#endif


/* begin_impl.hpp
DVJbdju2eslEvIjMC7ykZZphHmQi65BGtjaPvbfn7/qTiTeeNgm5ZQRgShkLbUZVvkOZgb1hNhs/qb//pHA7J3gbLDppylLF7pLZK3BdxIsKwwqq1+P51B+d+B+9j6Pxxb6z5wh7J/ZNe8kWsgvHbM4yJgkYBoqp19AzM5jeHrw5pLS4ZtJMexoNazDKRV3Qq80N6XDwBl61zEEFwAazaaPYajT2DRQprBlEiigtC44lY5ucCHrjvOD4WUYZW+bGCmPHiKYsS04TqEiK3CltB2gST1dEE4Qaz1RN3mXdNuBusQC9ylkLut2uNQWAmKJW9eR24J/RpEogEZGImNsMKTI7WCg51VsPDVYYVatrPMSwDS/b8Fe0HL/RB20Ye795R1Oftq8tzrjTn+50GedzVyz4ZH2IX1dU2ajLZ7/4ooX60kS5Nntw227u75cRQ/veYmJcAZZUOS9LBbqV2+cyXagS8PqtVzBjYVBghEY5y2hbstM9px+c8plkBI6xdcKSYwYzKTMBLy1He7knzpRz62hUqUX5AQewV1o8I+1cMOqeNucA52XbzdpgfHyFbrb9oHLjC+dH+INM/kTDVTPQzIS2Y1XipjFROQ1w0xelYreFhilnma7JPjodeMPpp/Fg6vnvvf4xbe1Gj5oO
*/