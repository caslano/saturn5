// Boost.Bimap
//
// Copyright (c) 2006-2007 Matias Capeletto
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

/// \file detail/set_view_iterator.hpp
/// \brief Iterator adaptors from multi-index to bimap.

#ifndef BOOST_BIMAP_DETAIL_SET_VIEW_ITERATOR_HPP
#define BOOST_BIMAP_DETAIL_SET_VIEW_ITERATOR_HPP

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/config.hpp>

// Boost

#ifndef BOOST_BIMAP_DISABLE_SERIALIZATION 
  #include <boost/serialization/nvp.hpp>
  #include <boost/serialization/split_member.hpp>
#endif // BOOST_BIMAP_DISABLE_SERIALIZATION

#include <boost/iterator/detail/enable_if.hpp>
#include <boost/iterator/iterator_adaptor.hpp>
#include <boost/bimap/relation/support/get_pair_functor.hpp>

namespace boost {
namespace bimaps {
namespace detail {


/** \brief Set View Iterator adaptor from multi index to bimap.

This is class is based on transform iterator from Boost.Iterator that is
modified to allow serialization. It has been specialized for this
library, and EBO optimization was applied to the functor.

                                                                      **/

#ifndef BOOST_BIMAP_DOXYGEN_WILL_NOT_PROCESS_THE_FOLLOWING_LINES

template< class CoreIterator > struct set_view_iterator;

template< class CoreIterator >
struct set_view_iterator_base
{
    typedef iterator_adaptor
    <
        set_view_iterator< CoreIterator >,
        CoreIterator,
        BOOST_DEDUCED_TYPENAME CoreIterator::value_type::above_view

    > type;
};

#endif // BOOST_BIMAP_DOXYGEN_WILL_NOT_PROCESS_THE_FOLLOWING_LINES

template< class CoreIterator >
struct set_view_iterator : public set_view_iterator_base<CoreIterator>::type
{
    typedef BOOST_DEDUCED_TYPENAME set_view_iterator_base<CoreIterator>::type base_;

    public:

    set_view_iterator() {}

    set_view_iterator(CoreIterator const& iter)
      : base_(iter) {}

    set_view_iterator(set_view_iterator const & iter)
      : base_(iter.base()) {}

    typename base_::reference dereference() const
    {
        return const_cast<
            BOOST_DEDUCED_TYPENAME base_::base_type::value_type*>(
                &(*this->base())
            )->get_view();
    }

    private:

    friend class iterator_core_access;

    #ifndef BOOST_BIMAP_DISABLE_SERIALIZATION

    // Serialization support

    BOOST_SERIALIZATION_SPLIT_MEMBER()

    friend class ::boost::serialization::access;

    template< class Archive >
    void save(Archive & ar, const unsigned int) const
    {
        ar << ::boost::serialization::make_nvp("mi_iterator",this->base());
    }

    template< class Archive >
    void load(Archive & ar, const unsigned int)
    {
        CoreIterator iter;
        ar >> ::boost::serialization::make_nvp("mi_iterator",iter);
        this->base_reference() = iter;
    }

    #endif // BOOST_BIMAP_DISABLE_SERIALIZATION
};

#ifndef BOOST_BIMAP_DOXYGEN_WILL_NOT_PROCESS_THE_FOLLOWING_LINES

template< class CoreIterator > struct const_set_view_iterator;

template< class CoreIterator >
struct const_set_view_iterator_base
{
    typedef iterator_adaptor
    <
        const_set_view_iterator< CoreIterator >,
        CoreIterator,
        const BOOST_DEDUCED_TYPENAME CoreIterator::value_type::above_view

    > type;
};

#endif // BOOST_BIMAP_DOXYGEN_WILL_NOT_PROCESS_THE_FOLLOWING_LINES


/** \brief Const Set View Iterator adaptor from multi index to bimap.

See also set_view_iterator.
                                                                      **/

template< class CoreIterator >
struct const_set_view_iterator : public const_set_view_iterator_base<CoreIterator>::type
{
    typedef BOOST_DEDUCED_TYPENAME const_set_view_iterator_base<CoreIterator>::type base_;

    public:

    const_set_view_iterator() {}

    const_set_view_iterator(CoreIterator const& iter)
      : base_(iter) {}

    const_set_view_iterator(const_set_view_iterator const & iter)
      : base_(iter.base()) {}

    const_set_view_iterator(set_view_iterator<CoreIterator> i)
      : base_(i.base()) {}

    BOOST_DEDUCED_TYPENAME base_::reference dereference() const
    {
        return this->base()->get_view();
    }

    private:

    friend class iterator_core_access;

    #ifndef BOOST_BIMAP_DISABLE_SERIALIZATION

    // Serialization support

    BOOST_SERIALIZATION_SPLIT_MEMBER()

    friend class ::boost::serialization::access;

    template< class Archive >
    void save(Archive & ar, const unsigned int) const
    {
        ar << ::boost::serialization::make_nvp("mi_iterator",this->base());
    }

    template< class Archive >
    void load(Archive & ar, const unsigned int)
    {
        CoreIterator iter;
        ar >> ::boost::serialization::make_nvp("mi_iterator",iter);
        this->base_reference() = iter;
    }

    #endif // BOOST_BIMAP_DISABLE_SERIALIZATION
};


} // namespace detail
} // namespace bimaps
} // namespace boost

#endif // BOOST_BIMAP_DETAIL_MAP_VIEW_ITERATOR_HPP



/* set_view_iterator.hpp
kKbvgHpx83dfDbmo9UL9dbPGPPSdjH2FsX8XmXpn4AYznukfiVlL630TOCQ4eK/5+KvDjUyNBNZYqHxO6Q8F6oLO+awRd++5ibw3+3EPWYdi7vGEb6CT4FP/Ie+bLJ2vWSvuPvCx+85JIYwKff92k7Z8XiAt+o5uvsrvdiI9nyQ18+7TBcnH46gXLXR8NDctsD7sDlRBi4hK3GSr4re4vVPcq/4Y1gT53z3EIbQtjbA+cI61PjAdfVWU56i+Qdtqr5/b1MORa4A+Rz1Rmwmz8AojiyDiWkKtp+quQ8Rx0xKx66z1Meg2JaKsiBJjPyC0v/dPricMXT85Q78nLHkODd4n2/0J13maFnpe8hb8rtN8EHkMpTMXlM6qIvRAfvyqrYzj19Sa51bdW2vw7hb9EN4DtOdGbm5N9SyvHVM/BUgKaqF55To7xKwx+ar13FoX+JjYdcWuscmrqem0+0G5O8eQV8SdfCDu3ntZ5dEStwb9pkm9wt+1N+B2b4WdN7Ory8uj9SXUrfWePfU43rOEF3Gd5eE+Acc9tJ+TDjd05MdqL146di6zbdjot43OsdlyiMXPVxrfYBgdVO5J2Pya2rcz3zjtRJ/sWu/amtL6Qf3z9R6tYba4Sdf3bDCMbLWnpyj6Q/I9P7UX6e5Nofm/i2YndfZ/GDVOmpuUy4/4Jk7Dcg+vW5qO2auD60Wbado46UzM4hvULZVRJXbfxc5nxnFGi9krzDg9K99Zwfit6KPxOz0Yv8rjjt8ACTuHObnmJn4XRIhfusbvHLEroAVpwruqadQ4pnP/eEfih5JvQeaPj97PtteQ23Od+i7Ruc6G3y1a1g2em3V5kb9RNi6y62dNxbKoc1vq1npuzjuO58Z6HxrZLRl+OSYJImOj5M6R++6r7L+u586XP/77dV3//2S6FI/ym5874vGRpad9uabVd3oue692cB2yOCR/nn110kf3Vmbv++qmjSN+1/GRg9FlwHwu7re8M7nDN6ff1/TKpBfd9E/v+WE02TAnTgbMGJFH/csb9hRNfuRAzgXL417/5rMH2iGjWcIf8tduXSd8uuLq+8+5KGN/o68jqOJekUlTm3XNXy4//7aLruw+8a6U/k3ejSar5t8vM6ZE8m3PFWXX3936k0f3tZr51o7VT3ePLkumVuK5+p7bf/3e83l5lz8/vr7iurv3n1gZM/pcyTjKDtLfxiG9+ruT/32iv5eiDoqcFd3rovtl/HZN4AQNZyMPejr8DmwHvws7wu/BgfBuOBTeAwvhfbAY3gvHqJ778MbTvSWwrd4nHvbU+7yOu2ZwD5Txepih+oNwEqpK/eep/8ZwtPonWeK/DcyCbWEblaOSo/rOsB3squY9VK/x070UmEWI3wyN30zYCs6CmaoPxi9F8/H6CPGbp+4rNX8WQkkTXARr4GJYCy+HC+AVqj8IN6C2aPr3afgpcK2G/zNfoJx2wHbwBdgRvgjz4CtwPHwVXgJ3wRr4a3gj/A28Gb4J74K/gw/A1+Ev4B74ktrvhr+Hb6j+IDwQXHev6/eJH/PP7CWB/utt3GXCP8AcuB92hQdhH/gJ7A/L4pxVZ8FP0Y+Bf4WL4edwHfwC3gn/Dh+CX8Jt0Ie/52AcfAXGw90wEe6DjeB+mAQz/XkHC2EqLIItYC1Mh8tgBrwbZsGHYVv4I9geboc5cD/MhV/ALrClj3YXtoE9YB/YE86AvWElzIe1sB9cCQfANXAgvBGeBm+Dg+ADcDB8Ag6Bz8Iz4POwEB6Aw+FncAT8Eo6Encn/s2E/OApOguPhPDgB1sEL4Uo4EX4NToY3wilwK5wGfwJnwNfgTPgunAXfh2XwoNRFXX+r64N36BrhPVo=
*/