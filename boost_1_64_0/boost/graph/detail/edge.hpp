//
//=======================================================================
// Copyright 1997, 1998, 1999, 2000 University of Notre Dame.
// Authors: Andrew Lumsdaine, Lie-Quan Lee, Jeremy G. Siek
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//=======================================================================

#ifndef BOOST_GRAPH_DETAIL_EDGE_HPP
#define BOOST_GRAPH_DETAIL_EDGE_HPP

#include <iosfwd>

#include <boost/functional/hash.hpp>

namespace boost
{

namespace detail
{

    template < typename Directed, typename Vertex > struct edge_base
    {
        inline edge_base() {}
        inline edge_base(Vertex s, Vertex d) : m_source(s), m_target(d) {}
        Vertex m_source;
        Vertex m_target;
    };

    template < typename Directed, typename Vertex >
    class edge_desc_impl : public edge_base< Directed, Vertex >
    {
        typedef edge_desc_impl self;
        typedef edge_base< Directed, Vertex > Base;

    public:
        typedef void property_type;

        inline edge_desc_impl() : m_eproperty(0) {}

        inline edge_desc_impl(Vertex s, Vertex d, const property_type* eplug)
        : Base(s, d), m_eproperty(const_cast< property_type* >(eplug))
        {
        }

        property_type* get_property() { return m_eproperty; }
        const property_type* get_property() const { return m_eproperty; }

        //  protected:
        property_type* m_eproperty;
    };

    template < class D, class V >
    inline bool operator==(const detail::edge_desc_impl< D, V >& a,
        const detail::edge_desc_impl< D, V >& b)
    {
        return a.get_property() == b.get_property();
    }
    template < class D, class V >
    inline bool operator!=(const detail::edge_desc_impl< D, V >& a,
        const detail::edge_desc_impl< D, V >& b)
    {
        return !(a.get_property() == b.get_property());
    }

    // Order edges according to the address of their property object
    template < class D, class V >
    inline bool operator<(const detail::edge_desc_impl< D, V >& a,
        const detail::edge_desc_impl< D, V >& b)
    {
        return a.get_property() < b.get_property();
    }
    template < class D, class V >
    inline bool operator<=(const detail::edge_desc_impl< D, V >& a,
        const detail::edge_desc_impl< D, V >& b)
    {
        return a.get_property() <= b.get_property();
    }
    template < class D, class V >
    inline bool operator>(const detail::edge_desc_impl< D, V >& a,
        const detail::edge_desc_impl< D, V >& b)
    {
        return a.get_property() > b.get_property();
    }
    template < class D, class V >
    inline bool operator>=(const detail::edge_desc_impl< D, V >& a,
        const detail::edge_desc_impl< D, V >& b)
    {
        return a.get_property() >= b.get_property();
    }

} // namespace detail

} // namespace boost

namespace std
{
template < class Char, class Traits, class D, class V >
std::basic_ostream< Char, Traits >& operator<<(
    std::basic_ostream< Char, Traits >& os,
    const boost::detail::edge_desc_impl< D, V >& e)
{
    return os << "(" << e.m_source << "," << e.m_target << ")";
}
}

// Boost's functional/hash
namespace boost
{
template < typename D, typename V >
struct hash< boost::detail::edge_desc_impl< D, V > >
{
    std::size_t operator()(const boost::detail::edge_desc_impl< D, V >& x) const
    {
        return hash_value(x.get_property());
    }
};
}

#endif // BOOST_GRAPH_DETAIL_DETAIL_EDGE_HPP

/* edge.hpp
5HnJZ7wPllPbW9emxtPCMhiFDbAh3pbvB3WfOs5TzzcHDlfLz2c9uXEB5sdXsQguUs9zMVbCJRiBS7E2LsP6uByb4AqUdm7YE1fjUFyDk3Gdej4BFt5z6vmUUZ9/hfj7F0fDbvV8GmF9bIwx2ATjsClOxhhchbG4HpvjIXwWj+Aw/ABb4U1srfZHG7RvQ1vMjh2wKnbEGtgJ62JnrI+J2Br7YBp2wUnYFadhN1yO3XElJuNxTMGvMRW/wUGY35q+fQVxmNqeDVbHPaBy/6/sj5b2/avqemeRLxIXqvf5YvW+XoJ9cRmOxOU4A1fiClyN23AtHsf1+CluwG9wIxazcHxjSdyEpdV0OG5R+2EHNlTTTdR0LG7DODVd0sbxiq3wALbFgxiPh7EHHsFeeBSfwWPYB49jMp7EUXgGl+IHeADP4WE8j6fwY5Txt9DGG+EiBuBnWBQ/x9p4GevjFWyK1zABr+MY/BIn4Fc4C2/icbyFH+C3eAVv4w/4hA/l+9L2CqvhD8Qj8SfshPcwBX/BMWiQbzpa8WW04Vr0w63ojzsxAI9hIN7AYAz04/wegzAU82IeDMNHsQnmw1gshIlYGMdhEZyMRXEGlsC1WBKPYCk8iY/hx1gGg/3Tn18ezI7lMQdWwipYEytgLFZ0fD9nc7Tnl3sL5Lh9lnSBuCH9a3Bc4HwMw4VYFZdjF1yBecm/GgviOqyG67EpvoZ9cBtOxjdwJT7O/t2EZXEPlsPD+ASexvL4ET6Jn2OYeh9WwO+wEt7HKhjCeywcC2BVLIkRWB6rYVV8CutidWyJNbAT1sR+WAtTsTZOwV0Gn+u4B+fjPnwd9+Ob+Da+je/gSTyEV/Awfokn8DaexB/wNP6GZ9BHjUcXiOcwCD/EwvgxlsCL+AR+ghXxElbHz7AOXsaGeAWj8Sq2xmvYAb/EHvgVJuENTMWbOAS/wZF4CyfgtzgF7+AM/A7n413cjD/gDvwJ9+E9PIo/4xW8j1/ib3gHDQu/V9GKv6ENfXj/+WIg+mEQBmBezIIFMRuWwEB8HHNgBXwEwzEIa2EwRmIoNsRcGI15MBbzYg/Mh0lYAIdhIRyJRXACFsUpWBxnYQmci6VwLT6G6/Fx3IJP4FEsj+9hGJ7FingRK+GnWAWvYzh+hRF4G6vhd1gd72MN/A1rYYAvxx9mxbpYHCOxLNrfT7WxDNMtsCy2wbeId8fN2BO3YG98mvkp2BDTsAm+jM1wNbbA3RiH57AVfoWt8Rtsh3exPWbz4/sVQ7AjPoXxWBu7YCx2xVbYDdtjd+yIPTEZe+EA7IvDMBmnYiq+ioNwGQ7G3TgED2AaHsVn8RMcjldxJN7BURjK59loLIhjsBi+hKXxZWyMMzEGZ2EczsH2+AoOx3k4CufjOFyIS3ERrsPFuBFX4UFcjZ/hGryKa/EWTsBsAfyux/w4CavhZIzEKdgQl2JbXIbxuBx74Dp8GTfgQtyIe/ENPIKb8CS+hWdwP36EB9AvC9/X+AgexnJ4BCvgUQzHY1gHT2ErPI2peAaH4Ls4HN/Dcfg+TsOzOBvP4V78GI/gBfwZP0F7Ze5lLIVXsBp+ge3wGnbGrTgCt+HLuB034Q7cjrtxD36FB/FrvIw38QZ+i3fxDtqy8TmF2fEuhqjp3Gq6MNrzVcD7WA1/xWb4G8bi99gTf8BU/BGHoGHl+EQfXIC+uA79cRcG4GnMgmcxEC/iI3gNg/AGBmOWQH4HYA4MxRDMi6UxH9bC/BiLBbAdFsbBWASHYVEcicVwARbHJVgCV2Ip/ArLY9HsfE9iTayInbESJmMEDsancCLWxHlYC9/C2rgbI/EMRuFlbIDX8Wn8GRuikYPfDJgDozE=
*/