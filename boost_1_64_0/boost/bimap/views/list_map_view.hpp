// Boost.Bimap
//
// Copyright (c) 2006-2007 Matias Capeletto
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

/// \file views/list_map_view.hpp
/// \brief View of a side of a bimap.

#ifndef BOOST_BIMAP_VIEWS_LIST_MAP_VIEW_HPP
#define BOOST_BIMAP_VIEWS_LIST_MAP_VIEW_HPP

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/config.hpp>

#include <boost/bimap/container_adaptor/list_map_adaptor.hpp>
#include <boost/bimap/relation/support/pair_by.hpp>
#include <boost/bimap/support/iterator_type_by.hpp>
#include <boost/bimap/detail/map_view_base.hpp>
#include <boost/bimap/relation/support/data_extractor.hpp>
#include <boost/bimap/relation/detail/to_mutable_relation_functor.hpp>

namespace boost {
namespace bimaps {
namespace views {

#ifndef BOOST_BIMAP_DOXYGEN_WILL_NOT_PROCESS_THE_FOLLOWING_LINES

template< class Tag, class BimapType >
struct list_map_view_base
{
    typedef ::boost::bimaps::container_adaptor::list_map_adaptor
    <
        BOOST_DEDUCED_TYPENAME BimapType::core_type::
            BOOST_NESTED_TEMPLATE index<Tag>::type,
        ::boost::bimaps::detail::              map_view_iterator<Tag,BimapType>,
        ::boost::bimaps::detail::        const_map_view_iterator<Tag,BimapType>,
        ::boost::bimaps::detail::      reverse_map_view_iterator<Tag,BimapType>,
        ::boost::bimaps::detail::const_reverse_map_view_iterator<Tag,BimapType>,
        ::boost::bimaps::container_adaptor::support::iterator_facade_to_base
        <
            ::boost::bimaps::detail::      map_view_iterator<Tag,BimapType>,
            ::boost::bimaps::detail::const_map_view_iterator<Tag,BimapType>
            
        >,
        ::boost::mpl::na,
        ::boost::mpl::na,
        ::boost::bimaps::relation::detail::
            pair_to_relation_functor<Tag, BOOST_DEDUCED_TYPENAME BimapType::relation >,
        ::boost::bimaps::relation::support::
            get_pair_functor<Tag, BOOST_DEDUCED_TYPENAME BimapType::relation >,

        BOOST_DEDUCED_TYPENAME ::boost::bimaps::relation::support::data_extractor
        <
            Tag,
            BOOST_DEDUCED_TYPENAME BimapType::relation
            
        >::type

    > type;
};

#endif // BOOST_BIMAP_DOXYGEN_WILL_NOT_PROCESS_THE_FOLLOWING_LINES

/// \brief View of a side of a bimap.
/**

This class uses container_adaptor and iterator_adaptor to wrapped a index of the
multi_index bimap core.

See also const_list_map_view.
                                                                                    **/
template< class Tag, class BimapType >
class list_map_view
:
    public list_map_view_base<Tag,BimapType>::type,
    public ::boost::bimaps::detail::
            map_view_base< list_map_view<Tag,BimapType>,Tag,BimapType >

{
    typedef BOOST_DEDUCED_TYPENAME list_map_view_base<Tag,BimapType>::type base_;

    BOOST_BIMAP_MAP_VIEW_BASE_FRIEND(list_map_view,Tag,BimapType)

    public:

    typedef BOOST_DEDUCED_TYPENAME base_::value_type::info_type info_type;

    list_map_view(BOOST_DEDUCED_TYPENAME base_::base_type & c) :
        base_(c) {}

    list_map_view & operator=(const list_map_view & v)
    {
        this->base() = v.base(); 
        return *this;
    }

    BOOST_BIMAP_VIEW_ASSIGN_IMPLEMENTATION(base_)

    BOOST_BIMAP_VIEW_FRONT_BACK_IMPLEMENTATION(base_)

    // Rearrange Operations

    void relocate(BOOST_DEDUCED_TYPENAME base_::iterator position,
                  BOOST_DEDUCED_TYPENAME base_::iterator i)
    {
        this->base().relocate(
            this->template functor<
                BOOST_DEDUCED_TYPENAME base_::iterator_to_base>()(position),
            this->template functor<
                BOOST_DEDUCED_TYPENAME base_::iterator_to_base>()(i)
        );
    }

    void relocate(BOOST_DEDUCED_TYPENAME base_::iterator position,
                  BOOST_DEDUCED_TYPENAME base_::iterator first,
                  BOOST_DEDUCED_TYPENAME base_::iterator last)
    {
        this->base().relocate(
            this->template functor<
                BOOST_DEDUCED_TYPENAME base_::iterator_to_base>()(position),
            this->template functor<
                BOOST_DEDUCED_TYPENAME base_::iterator_to_base>()(first),
            this->template functor<
                BOOST_DEDUCED_TYPENAME base_::iterator_to_base>()(last)
        );
    }
};


} // namespace views

/*===========================================================================*/
#define BOOST_BIMAP_MAP_VIEW_EXTRA_TYPEDEF(MAP_VIEW,SIDE,TYPENAME)            \
typedef BOOST_DEDUCED_TYPENAME MAP_VIEW::TYPENAME                             \
    BOOST_PP_CAT(SIDE,BOOST_PP_CAT(_,TYPENAME));
/*===========================================================================*/

/*===========================================================================*/
#define BOOST_BIMAP_MAP_VIEW_EXTRA_TYPEDEFS_BODY(MAP_VIEW,SIDE)               \
    BOOST_BIMAP_MAP_VIEW_EXTRA_TYPEDEF(MAP_VIEW,SIDE,reverse_iterator)        \
    BOOST_BIMAP_MAP_VIEW_EXTRA_TYPEDEF(MAP_VIEW,SIDE,const_reverse_iterator)  \
/*===========================================================================*/

namespace detail {

template< class Tag, class BimapType >
struct left_map_view_extra_typedefs< ::boost::bimaps::views::list_map_view<Tag,BimapType> >
{
    private: typedef ::boost::bimaps::views::list_map_view<Tag,BimapType> map_view_;
    public : BOOST_BIMAP_MAP_VIEW_EXTRA_TYPEDEFS_BODY(map_view_,left)
};

template< class Tag, class BimapType >
struct right_map_view_extra_typedefs< ::boost::bimaps::views::list_map_view<Tag,BimapType> >
{
    private: typedef ::boost::bimaps::views::list_map_view<Tag,BimapType> map_view_;
    public : BOOST_BIMAP_MAP_VIEW_EXTRA_TYPEDEFS_BODY(map_view_,right)
};

} // namespace detail

/*===========================================================================*/
#undef BOOST_BIMAP_MAP_VIEW_EXTRA_TYPEDEF
#undef BOOST_BIMAP_MAP_VIEW_EXTRA_TYPEDEFS_BODY
/*===========================================================================*/

} // namespace bimaps
} // namespace boost

#endif // BOOST_BIMAP_VIEWS_LIST_MAP_VIEW_HPP


/* list_map_view.hpp
2zPRdqsotuMbEHXPJAOuEPceIXVxrGOw32/8a2peaoFnGjp29kgc/T3T+KYrje3cK+Vx7gK9R9rbIcBvUG/3YK7vgugJgR7i9wHMXXoeP/QrMayBA2Zth0g/1bo+3qZ6h36WJXZjbtQ03H75bXRxNFrRDiY46bujO6yX+2F7RZvQQfoo4oGBuxPKyznuHeQcrx3J/dq+KPd1+826SYLJuYOh93VGVzD3D5yT+wejY7xO/OlUF7bPlpZp9u7kSNR1xUFnXdFQy1KnwXtNoX6TZH5lXRB1bXHwJK8tRgfXaZr/Wbounoy5kjrYN1fyL5oO15WvWsvOay1fdi0rX3Oe5O/BzqITQ8eo+if0AKu91xpZ/XSSMPOxHxL7SCvXpadlRzqmBXpa2uk9PPmgTOVR9Ty6y/lYF6PzU46pmCsoZ26JlJPdpLLyVXXV5fYSsGrNigrLe42sYdLVztclxJ4cue9m/E5rrt1mtGaPLLgmXK+6Bk/VSAq0PI1OeS5sZq9U/aVH5tm4nXrS8jw+uK+n+gYzMW3VbLL7WiDPq6oDb98tmjhr4VTtbpOmz3XrbV7FEDVl0HCZ4n6V6HZZLuNby2Hcnf5I71X3Esfd2Z8x+0zN72UXGr2pkh+zN0MeOEce9FyR6Y+Sbuj+X3b0/ng4UBf1FeU1ZZUXrK1tqPJsQ/U7OrINjdu0iD3datxeF7dJJ619g2Ua2828ryfH6VqmonlOmbRIXmVSv8lmbBXP8+yn6rc46r71FHGbctLKGBx3Darbaruf+2vlNZzbqWVssJ9U1F3kVT71N9TK1nvzX4r9PH937r3uiN9hbfBtVT3k6PhbaLsNkutCo7nv9vguhMRTaGXrPdlB7IT15/DkLy++f9z5vj3muyBlEm8fiXeTtsXuTlK3DbWuNdHf8Wf0lps0Rku4Jtufyc/yNbWrnX2gH4u/tf4C/u/zqR5OEz7P1V5rJEwtbvMX2G7b4p5hx79tXD8pRy15HTffPv83X+f4Z6y/xedZ4321Jl3C18l8onsnCyWOrXFPE0eKxrHQFUfX+KcljlG+BlccNcThzAmjJI7O1DV2ws4Re1JcX+tx9/rc+N9/huj59fAfOfZelLzMsHK0n64Q+2/jl1DqurgU6/I4n5Ua/7h7D2yN5Xrm1ijx51I27PzaKfYZcWOti5Bjn2PlcwcbXM//TOp7tT9kPa/97kIJVx+3w6qP6G+O/yqzR/eBlPODuP5x3ZFz7xfRl0L2S3TtuYBwr0keSv2pXON/F3fEKvXlWbf4Eqy3fLlm/+YV8XOOa21eYbeJuU94X9KuiNtgUS9yTvOqa2jxrGvoeH6Viv8xVipXmD6YbK37sXK+3uqOyzDMLN2jjOfsdGmHFN0fCtq/z3bUTT5Xf5MOl6lle1Li6xl/BI02W+JWutqMYaT+MuEzUr4qv/0lnnt98eov8nlqz/na93DvI8+F0R9Wv+LiKpeex0el3X7PU9cDsg/QUSez78p5P/XOd1uYh2flBtcU8+3lREJqm9R+nusKnZv+pHOT1/PeY+LeK7D+1HQeMulseC+QUApISbZ/d2hmnXTDAu03Hmv2L4t7QdwU6xeS3iCu0Sm6jmE9IfpO69PNugJinHXHcb8XYq8d6Lsha4fG0OuA3P9virz/F79NkDmT88yZem6b8SvzoZEDKI330pl18nSuRf+OfOvlDKK/7//J60prrdzAByLfMPHYsU7nVyU+88tXXnq7z96qv3rpUPOSw/jkdah5yG146Mhr/Xf/P1S9JxwyDtPx97wVeObL9Um+ffGE/h6C25P6ezS/f6C/p/P7Yf19Dr8f1d+IR4h8RqGl77pAmk/cfPAUjKXyFzbnwSQ=
*/