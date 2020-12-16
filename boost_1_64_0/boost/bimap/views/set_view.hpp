// Boost.Bimap
//
// Copyright (c) 2006-2007 Matias Capeletto
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

/// \file views/set_view.hpp
/// \brief View of a bimap that is signature compatible with std::set.

#ifndef BOOST_BIMAP_VIEWS_SET_VIEW_HPP
#define BOOST_BIMAP_VIEWS_SET_VIEW_HPP

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/config.hpp>

#include <boost/bimap/container_adaptor/set_adaptor.hpp>
#include <boost/bimap/detail/set_view_base.hpp>

namespace boost {
namespace bimaps {
namespace views {

/// \brief View of a bimap that is signature compatible with std::set.
/**

This class uses container_adaptor and iterator_adaptor to wrapped a index of the
multi_index bimap core so it can be used as a std::set.

See also const_set_view.
                                                                                    **/

template< class CoreIndex >
class set_view
:
    public BOOST_BIMAP_SET_VIEW_CONTAINER_ADAPTOR(
        set_adaptor,
        CoreIndex,
        reverse_iterator, const_reverse_iterator
    ),

    public ::boost::bimaps::detail::
                set_view_base< set_view< CoreIndex >, CoreIndex >
{
    typedef BOOST_BIMAP_SET_VIEW_CONTAINER_ADAPTOR(
        set_adaptor,
        CoreIndex,
        reverse_iterator, const_reverse_iterator

    ) base_;

    BOOST_BIMAP_SET_VIEW_BASE_FRIEND(set_view,CoreIndex)

    public:

    set_view(BOOST_DEDUCED_TYPENAME base_::base_type & c) : base_(c) {}

    /*
    template< class LowerBounder, class UpperBounder >
    std::pair<BOOST_DEDUCED_TYPENAME base_::const_iterator,
              BOOST_DEDUCED_TYPENAME base_::const_iterator>
        range(LowerBounder lower,UpperBounder upper) const
    {
        return this->base().range(

            ::boost::bimaps::container_adaptor::detail::unary_check_adaptor
            <
                LowerBounder,
                BOOST_DEDUCED_TYPENAME base_::base_type::value_type,
                BOOST_DEDUCED_TYPENAME base_::value_from_base

            >( lower, this->template functor<
                            BOOST_DEDUCED_TYPENAME base_::value_from_base>() ),

            ::boost::bimaps::container_adaptor::detail::unary_check_adaptor
            <
                UpperBounder,
                BOOST_DEDUCED_TYPENAME base_::base_type::value_type,
                BOOST_DEDUCED_TYPENAME base_::value_from_base

            >( upper, this->template functor<
                            BOOST_DEDUCED_TYPENAME base_::value_from_base>() )

        );
    }
    */

    set_view & operator=(const set_view & v) 
    {
        this->base() = v.base();
        return *this;
    }
};


} // namespace views
} // namespace bimaps
} // namespace boost

#endif // BOOST_BIMAP_VIEWS_SET_VIEW_HPP



/* set_view.hpp
bO7fgbl9f/t5uMzt7TD1MXjRnLm2jSTI/P78TMs8K+6h8/uEAORbgyGEUex4P0D97vVZiHP/r6Uart8htIoz1YFwZclDYjiDbJkzv9pW9d3QawR0A/7vP1v5pXToeT2jeUrWOI61/nJM8uTzrn0l7fgBd/V461avNRGvNRSvtQ+vtZL/nM5G92/w9l03Y+BZgrYBbRvZETp6NumzBD+VuRGMhba/PEy1+vOrvxjH/j+NkLPZFBZzYsunDdOH4faMwrx3rc8qdkLn84rknoQJ9T1snl24v4utzzLM+9g7h7m8j63PNRbDiPex9V3s8OcdU+Eq6KU3Q5+BmHezF4zweD9bn4tshgVwG9TnI+Z9bfOudrQejQa9q63PVXhf2/3ZSugd7tBzls0cF8LI97k3j3HXtRF6BuP+fve2seF6N5ZiAs9oGq57Y/r40LveCZ/xjvdnB9fXDv4O/g7+Dv4O/g7+Dv4O/vb1969+/l9VY5uimqqKqrJf4vm/Pb8vzmSyrPPwUp2Av4Bph1mL+Tab96RaBOb3R0wpGjNHIlNWOpqte9lrS2zBdyPPam8hRxQd3wK8IX4Xh96VFHtXs+9LeVpoz/JY2c90dtmZ6n+ikc81e868KvY/yr65HS2VD2xxat4/f0Vk5qKzOlb8FZpwOqqMz0qU656GxPFy7eVy7VI22Kk1+99sFD8rxT7ZhJGt8uYdYec7u8hEv7M7H7K3YmXJqTVGNj9Cthx7k9D7vXLNNI5KJJ6N1B7KL40DP4my2SN4pJzPdUsnrifw/imylPlu/E7HnJLJ1TJ4VwMzg+PSTKvB7xFT3rzHSnk73iOmDHELlGG6vkdMOeFmysm8S7xcZCXPzbvEuIW9h1wO54v/QP6xpmPq6zJ9kfgVTBbmEcz3dn1N86ivZXPC6ivXMu9pa/1Uv93MPs1vin2V1LcXUqR+V1SX03hCdVT9dDFl8JrYjzFlUNJS9h+nDPzR9Vzr9Wbxc12ovoq9k1s9N/XzZZG5JVQ/xZ4TXef0HfMeEo+hVj8rNrzOpkXXWcqWn7MtQ/FfZGVRj+KtQP2pIOB5mEzqzUzMrIyG1x/y37xLnq71hzzGTfNYZQtd6tU0j3pVHF1fzPrlPUSaH3bWVFSv8E/Ul3Utg/XFfAbiVT9UNlfyqsC+pnmfX5Yp51SUmv3OVLa9yI536Qv02wGV6yhyhY7986brtzAD9zMvayUfTLw0L6Pzp5fmz3Rd2L1N9/74A4bqRIAmf2TH9oi+3nxXkSNyc9hLI1HzK+g3x/T3V4q9SVQfqm1J5Um1tosssV/I+8bxrvW6FfY2InOpNYF/zVMNp41rn3ppurNPNXHy7FPPkPOdtN47+89Qv3lky4bX++h+09nveZeT+U5Pl2rmaTnJ3rj290zh5VQ0gzf1ass8+zqVb2d05fwo9nHWUJe81jqtflqbPuV7sR9njebf9BsR9SKulYTLu2WJ5l2/1qa/aPj3XqaOmz0Avdt6hn5k19SuQ3AXJpY8qm5l8khHL95jl+Ui+7TmV9BvN1OXT80I3Ytfl3tD9WznfQF5c184DvtVYv9Q5N8X+Rn2tr8m/5fJ+dutgVo3C00YnVTGZ20Q+5+QWBY9btH6epm5DvcFE0ZOfeMWZBo+bqlutfdxS3GGs42ZvIpuY5r2EXI+1y2dnuOW2Zm/3LiF8sON8nO0v/fFzS6jAx+zDA72sc31HkSauykTqJfrMiLrpb1Lb+8i7m6u9ZP6iJ/QfvlTsX8r9j3WB1wx9B0aITja4tcic691ru4rP9GEc6ip16sype805es1Bik0fvMl/GOwbxd7jO9jK9Yx1rHvPpbp0z8P1AXfW8xVtI5qOD2x67U=
*/