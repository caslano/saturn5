// Boost.Bimap
//
// Copyright (c) 2006-2007 Matias Capeletto
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

/// \file views/multiset_view.hpp
/// \brief View of a bimap that is signature compatible with std::multiset.

#ifndef BOOST_BIMAP_VIEWS_MULTISET_VIEW_HPP
#define BOOST_BIMAP_VIEWS_MULTISET_VIEW_HPP

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/config.hpp>

#include <boost/bimap/container_adaptor/multiset_adaptor.hpp>
#include <boost/bimap/container_adaptor/detail/comparison_adaptor.hpp>
#include <boost/bimap/detail/non_unique_views_helper.hpp>
#include <boost/bimap/detail/set_view_base.hpp>

namespace boost {
namespace bimaps {
namespace views {

/// \brief View of a bimap that is signature compatible with std::multiset.
/**

This class uses container_adaptor and iterator_adaptor to wrapped a index of the
multi_index bimap core so it can be used as a std::multiset.

See also const_multiset_view.
                                                                                    **/

template< class CoreIndex >
class multiset_view
:
    public BOOST_BIMAP_SET_VIEW_CONTAINER_ADAPTOR(
        multiset_adaptor,
        CoreIndex,
        reverse_iterator,
        const_reverse_iterator
    ),

    public ::boost::bimaps::detail::
                set_view_base< multiset_view< CoreIndex >, CoreIndex >
{
    BOOST_BIMAP_SET_VIEW_BASE_FRIEND(multiset_view, CoreIndex)

    typedef BOOST_BIMAP_SET_VIEW_CONTAINER_ADAPTOR(
        multiset_adaptor,
        CoreIndex,
        reverse_iterator,
        const_reverse_iterator

    ) base_;

    public:

    multiset_view(BOOST_DEDUCED_TYPENAME base_::base_type & c) : base_(c) {}

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

    multiset_view & operator=(const multiset_view & v) 
    {
        this->base() = v.base(); return *this;
    }

    BOOST_BIMAP_NON_UNIQUE_VIEW_INSERT_FUNCTIONS
};


} // namespace views
} // namespace bimaps
} // namespace boost

#endif // BOOST_BIMAP_VIEWS_MULTISET_VIEW_HPP


/* multiset_view.hpp
sLrV9KhGGg2NVaoXPK0ai3jZ1WjytjvCeg+689Gsyph7OexPGafuosMOIPF2SGxVjLD4JbE3hybXM4YLVmzzUbJer9v1K6kd6Sw42dTnEZQP0+GsP5iPezM3zmiuP9ESs8p+70+Hg5vrfn/qw+moLtGT7d5Nwllt9xRDNHo7Cfv7FlUF9gzxSwjHTVbl8Qg2SgVXZb7Zrcu8X7uNRrOz1wCnVPX/AVBLAwQKAAAACAAtZ0pS797yatgFAAD/DAAAIwAJAGN1cmwtbWFzdGVyL2RvY3MvZXhhbXBsZXMvc2Z0cGdldC5jVVQFAAG2SCRgrVZtb9pIEP7Or5gS3RWQA20/XY80OppAioogCuSiSJGsxR7jvdpea3cdwl3y329m10CSXpSeVPJivN6ZeebZmWfc6/y8TwM68OondH8hfejqLM61+gsj+9+7w/Ae/A9Z3dD1tSA92Jvch2143eQeWs4krKMc8fcwfC3QDWPjfz22vAn5K62QGVueqHKj5Sq10Dppw/uPH3+DQ/jw7sO7AE5FITGDucViiXoVwFHsVv5Ixd1d1+BxAGhBZN3a1SKVBoxK7FpoBPqeyQgLgzEIAzGaSMsl3cgCbIqQyAzhZHZ+PZ6eBbBOZZSyk42qwKSqymJIxS2CxgjlrfdR
*/