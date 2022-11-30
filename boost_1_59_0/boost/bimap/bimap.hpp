// Boost.Bimap
//
// Copyright (c) 2006-2007 Matias Capeletto
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

/// \file bimap.hpp
/// \brief Includes the basic bimap container

/** \mainpage notitle
\n
\image html http://matias.capeletto.googlepages.com/boost.bimap.reference.logo.png

\section Introduction

This is the complete reference of Boost.Bimap.

After getting a good understanding of the library from a user perspective
the next step will be:

    - Understand the tagged idiom. (boost::bimaps::tags)
    - Understand the internals of the relation class (boost::bimaps::relation)
    - Read the container_adaptor toolbox docs (boost::bimaps::container_adaptor)
    - Understand the internals of the bimap class. (boost::bimaps, boost::bimaps::views
      and boost::bimaps::detail)


                                                                        **/

/** \defgroup mutant_group mutant idiom
\brief A safe wrapper around reinterpret_cast
                                                                        **/

/** \defgroup relation_group relation
\brief The relation
                                                                        **/

/** \defgroup tags_group tagged idiom
\brief The tagged idiom
                                                                        **/


#ifndef BOOST_BIMAP_BIMAP_HPP
#define BOOST_BIMAP_BIMAP_HPP

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/config.hpp>
#include <boost/bimap/detail/user_interface_config.hpp>
#include <boost/mpl/aux_/na.hpp>

#ifndef BOOST_BIMAP_DISABLE_SERIALIZATION
    #include <boost/serialization/nvp.hpp>
#endif // BOOST_BIMAP_DISABLE_SERIALIZATION

// Boost.Bimap
#include <boost/bimap/detail/bimap_core.hpp>
#include <boost/bimap/detail/map_view_base.hpp>
#include <boost/bimap/detail/modifier_adaptor.hpp>
#include <boost/bimap/relation/support/data_extractor.hpp>
#include <boost/bimap/relation/support/member_with_tag.hpp>

#include <boost/bimap/support/map_type_by.hpp>
#include <boost/bimap/support/map_by.hpp>
#include <boost/bimap/support/iterator_type_by.hpp>

/// \brief The namespace where all the boost libraries lives.

namespace boost {

/// \brief Boost.Bimap library namespace
/**
All the entities in the library are defined in this namespace.
                                                                    **/
namespace bimaps {

/// \brief The bimap class is the entry point to the library.
/**
This class manages the instantiation of the desired bimap type.
As there are several types of bidirectional maps that can be
created using it. the main job of it is to find the desired
type. This is done using metaprogramming to obtain the relation
type that will be stored, the map_view type of each side and
the set_view type of the general relationship. The instantiation
is kept simple using an extended standard set theory, where a
bidirectional map type is defined by the set types it relates.
For example, a bidirectional map that has multimap semantics
viewed from both sides is defined by specifying that the two
keys sets are of \c multiset_of<Key> type.
This allows the bimap class to support seamingless N-N, 1-N,
ordered/unordered and even vector-list types of mapping.
The three last parameters are used to specify the set type of
the relation, an inplace hooked data class and the allocator
type. As a help to the bimap user, these parameters support
default types but use a special idiom that allow them to be
specified without interleaving the usual use_default keyword.
The possible bimap instantiation are enumerated here:
\c {Side}KeyType can be directly a type, this is default to
\c set_of<{Side}KeyType>, or can be a \c {SetType}_of<Type>
specification. Additionally this two parameters can be tagged
to specify others tags instead of the usual \c member_at::{Side}
ones.


\code

    typedef bimap
    <
        LeftCollectionType, RightCollectionType

        [ , SetTypeOfRelation  ]  // Default to left_based
        [ , info_hook< Info >  ]  // Default to no info
        [ , Allocator          ]  // Default to std::allocator<>

    > bm;

\endcode

                                                                       **/


template
<
    class KeyTypeA, class KeyTypeB,
    class AP1 = ::boost::mpl::na,
    class AP2 = ::boost::mpl::na,
    class AP3 = ::boost::mpl::na
>
class bimap
:
    // Bimap Core, use mpl magic to find the desired bimap type

    public ::boost::bimaps::detail::bimap_core<KeyTypeA,KeyTypeB,AP1,AP2,AP3>,

    // You can use bimap as a collection of relations

    public ::boost::bimaps::detail::bimap_core<KeyTypeA,KeyTypeB,AP1,AP2,AP3>
                ::relation_set,

    // Include extra typedefs (i.e. left_local_iterator for unordered_map)

    public ::boost::bimaps::detail:: left_map_view_extra_typedefs<
        BOOST_DEDUCED_TYPENAME ::boost::bimaps::detail::left_map_view_type<
            ::boost::bimaps::detail::bimap_core<KeyTypeA,KeyTypeB,AP1,AP2,AP3>
        >::type
    >,
    public ::boost::bimaps::detail::right_map_view_extra_typedefs< 
        BOOST_DEDUCED_TYPENAME ::boost::bimaps::detail::right_map_view_type<
            ::boost::bimaps::detail::bimap_core<KeyTypeA,KeyTypeB,AP1,AP2,AP3>
        >::type
    >
{
    typedef BOOST_DEDUCED_TYPENAME ::boost::bimaps::detail::
        bimap_core<KeyTypeA,KeyTypeB,AP1,AP2,AP3> base_;

    BOOST_DEDUCED_TYPENAME base_::core_type core;

    public:

    // metadata --------------------------------------------------------

    /*
    // The rest is computed in the core, because it is quite difficult to
    // expose a nice interface with so many metaprogramming stuff.
    
    // Map by {side} metadata

    typedef -unspecified- {side}_tag;
    typedef -unspecified- {side}_data_type;
    typedef -unspecified- {side}_value_type;
    typedef -unspecified- {side}_key_type;
    
    // There are other typedefs for definitions of different map views
    
    ------------------------------------------------------------------*/

    typedef BOOST_DEDUCED_TYPENAME ::boost::bimaps::detail::
          left_map_view_type<base_>::type  left_map;
    typedef BOOST_DEDUCED_TYPENAME ::boost::bimaps::detail::
         right_map_view_type<base_>::type right_map;
	
    typedef BOOST_DEDUCED_TYPENAME
         left_map::iterator        left_iterator;
    typedef BOOST_DEDUCED_TYPENAME
         left_map::const_iterator  left_const_iterator;

    typedef BOOST_DEDUCED_TYPENAME
         right_map::iterator       right_iterator;
    typedef BOOST_DEDUCED_TYPENAME
         right_map::const_iterator right_const_iterator;

    typedef BOOST_DEDUCED_TYPENAME
         left_map::reference       left_reference;
    typedef BOOST_DEDUCED_TYPENAME
         left_map::const_reference left_const_reference;

    typedef BOOST_DEDUCED_TYPENAME
        right_map::reference       right_reference;
    typedef BOOST_DEDUCED_TYPENAME
        right_map::const_reference right_const_reference;

    typedef BOOST_DEDUCED_TYPENAME base_::relation::info_type info_type;

    typedef BOOST_DEDUCED_TYPENAME base_::core_type::allocator_type allocator_type; 
    
    /// Left map view
    left_map  left;

    /// Right map view
    right_map right;

    typedef BOOST_DEDUCED_TYPENAME base_::logic_relation_set_tag 
                                          logic_relation_set_tag;
    typedef BOOST_DEDUCED_TYPENAME base_::logic_left_tag logic_left_tag;
    typedef BOOST_DEDUCED_TYPENAME base_::logic_right_tag logic_right_tag;
    typedef BOOST_DEDUCED_TYPENAME base_::core_type::ctor_args_list 
                                                     ctor_args_list;

   bimap(const allocator_type& al = allocator_type()) :

       base_::relation_set(
           ::boost::multi_index::get<
               logic_relation_set_tag
           >(core)
       ),

       core(al),

       left (
           ::boost::multi_index::get<
               logic_left_tag
           >(core)
       ),
       right (
           ::boost::multi_index::get<
               logic_right_tag
           >(core)
       )

   {}

   template< class InputIterator >
   bimap(InputIterator first,InputIterator last,
         const allocator_type& al = allocator_type()) :

       base_::relation_set(
           ::boost::multi_index::get<
               BOOST_DEDUCED_TYPENAME base_::logic_relation_set_tag>(core)
       ),

       core(first,last,ctor_args_list(),al),

       left (
           ::boost::multi_index::get<
               BOOST_DEDUCED_TYPENAME base_::logic_left_tag>(core)
       ),
       right (
           ::boost::multi_index::get<
               BOOST_DEDUCED_TYPENAME base_::logic_right_tag>(core)
       )

   {}

   bimap(const bimap& x) :

       base_::relation_set(
           ::boost::multi_index::get<
               BOOST_DEDUCED_TYPENAME base_::logic_relation_set_tag>(core)
       ),

       core(x.core),

       left (
           ::boost::multi_index::get<
               BOOST_DEDUCED_TYPENAME base_::logic_left_tag>(core)
       ),
       right (
           ::boost::multi_index::get<
               BOOST_DEDUCED_TYPENAME base_::logic_right_tag>(core)
       )

   {}

    bimap& operator=(const bimap& x)
    {
        core = x.core;
        return *this;
    }

    // Projection of iterators

    template< class IteratorType >
    left_iterator project_left(IteratorType iter)
    {
        return core.template project<
            BOOST_DEDUCED_TYPENAME base_::logic_left_tag>(iter.base());
    }

    template< class IteratorType >
    left_const_iterator project_left(IteratorType iter) const
    {
        return core.template project<
            BOOST_DEDUCED_TYPENAME base_::logic_left_tag>(iter.base());
    }

    template< class IteratorType >
    right_iterator project_right(IteratorType iter)
    {
        return core.template project<
            BOOST_DEDUCED_TYPENAME base_::logic_right_tag>(iter.base());
    }

    template< class IteratorType >
    right_const_iterator project_right(IteratorType iter) const
    {
        return core.template project<
            BOOST_DEDUCED_TYPENAME base_::logic_right_tag>(iter.base());
    }

    template< class IteratorType >
    BOOST_DEDUCED_TYPENAME base_::relation_set::iterator
        project_up(IteratorType iter)
    {
        return core.template project<
            BOOST_DEDUCED_TYPENAME base_::logic_relation_set_tag>(iter.base());
    }

    template< class IteratorType >
    BOOST_DEDUCED_TYPENAME base_::relation_set::const_iterator
        project_up(IteratorType iter) const
    {
        return core.template project<
            BOOST_DEDUCED_TYPENAME base_::logic_relation_set_tag>(iter.base());
    }

    // Support for tags

    template< class Tag, class IteratorType >
    BOOST_DEDUCED_TYPENAME ::boost::bimaps::support::
    iterator_type_by<Tag,bimap>::type
        project(IteratorType iter)
    {
        return core.template project<Tag>(iter.base());
    }

    template< class Tag, class IteratorType >
    BOOST_DEDUCED_TYPENAME ::boost::bimaps::support::
    const_iterator_type_by<Tag,bimap>::type
        project(IteratorType iter) const
    {
        return core.template project<Tag>(iter.base());
    }

    template< class Tag >
    struct map_by :
        public ::boost::bimaps::support::map_type_by<Tag,bimap>::type
    {
        typedef BOOST_DEDUCED_TYPENAME ::boost::bimaps::support::
            map_type_by<Tag,bimap>::type type;

        private: map_by() {}
    };

    template< class Tag >
    BOOST_DEDUCED_TYPENAME ::boost::bimaps::support::
    map_type_by<Tag,bimap>::type &by()
    {
        return ::boost::bimaps::support::map_by<Tag>(*this);
    }

    template< class Tag >
    const BOOST_DEDUCED_TYPENAME ::boost::bimaps::support::
    map_type_by<Tag,bimap>::type &by() const
    {
        return ::boost::bimaps::support::map_by<Tag>(*this);
    }


    #ifndef BOOST_BIMAP_DISABLE_SERIALIZATION

    // Serialization support

    private:

    friend class boost::serialization::access;

    template<class Archive>
    void serialize(Archive & ar, const unsigned int)
    {
        ar & serialization::make_nvp("mi_core",core);
    }

    #endif // BOOST_BIMAP_DISABLE_SERIALIZATION
};

} // namespace bimaps
} // namespace boost


/** \namespace boost::bimaps::support
\brief Metafunctions to help working with bimaps.
                                                            **/

/** \namespace boost::bimaps::views
\brief Bimap views.
                                                            **/

/** \namespace boost::bimaps::views::detail
\brief Bimap views details.
                                                            **/



// Include basic tools for user commodity

#include <boost/bimap/tags/tagged.hpp>
#include <boost/bimap/relation/member_at.hpp>
#include <boost/multi_index/detail/unbounded.hpp>

// Bring the most used namespaces directly to the user main namespace
namespace boost {
namespace bimaps {

using ::boost::bimaps::tags::tagged;

namespace member_at = ::boost::bimaps::relation::member_at;

using ::boost::multi_index::unbounded;

} // namespace bimaps
} // namespace boost


#endif // BOOST_BIMAP_BIMAP_HPP

/* bimap.hpp
qcC9FdSgDMXIhelJRLtm5k8Aa1XIsq9E6brAxgBmxc8JZXS9DUsuIFQa9gflStzAHdXUt//BvgV0CViCa042/nO6XBnJ3Mm9JhcQb8c/dDWRyxZ9jdIBJ8oA1sKi3jeM940T+lV+4Ow4vfnBn4BAaBUodOTJhsqVAPUs14K4BwNs8PgeIp6YydLTHqj9pEQ5a9w+gevT4CfhT0Io0dOM+9J+IFB9V5fawbCWu+dWMxsoDTtB5EzGsH079WavA+izTe+3C/V37MJa4/6DXRQsxFhSNNuwqhQQHzd4RP5LY1/qKZ4r0cWmBDwOaeirz0djn1ow87L3tQvf4lX+rD86mnnJcVLgfYFSyJzG59SI5GQX1KsOyyAFnyIQ+8uJYAs/A1eg9uZLIJzRhCgyD+WaG5yAnyphp0yhvyR+xRytQMSuAGwKwcZHu+on5apTShg3IZK0FkFcLnx9JPCMxKJDjmaoVu6ZglrAYSFEK/I92Rgl4F2pgbw3dWX+jPWrnueI4kr97IR3Dwz16uWk7Hd4swAhaRo2bAsmTn1nLden2yMcjhHF34MCYcGlEeNJfKJycnNIOJkehgrix2A4rd6vJ/okc7TtdBJG6+CTatSYRKXzcUDp3V7YIX9r0odsFCvJtatYmGbrbu6kX0sdUCDunLsQ62zXdfdKWaYWyuAWSXvBWYLoVhaSrTQ0P/6t8Oek5eBqyH1dx9Vgx/3xxx+/neJ/nyrJL1XHPGYzhYj7KlYfN06hBMcNhliCCNXieNN+5bvtQDsZrxUaEqp5RAVAQ652Pp9nxhjWs5kE5kuSTQhE9rHimi0ZSIxxx+Wb2PpYjV8ibPBcaDnLSXoseRoqDt5R5JqLuAL9fhho7sNOcR33wyMeG64fG3igHdHiBAOGh9dXG5iiQzRYEMrysvd8mwSD0odD6RFk0FhWkVAFDyqWTtkEoHr6VyfXzACS7cGRm5XCAL7mYKP98fRsidoE/0q3CYITxAujEXG8dP1eByH+etYh1ITYmSVF1v4nbqsiFpNZYsBPBlOnEGk+V4d5cDMw3m9Cmn0NoXMhmRaTh1zs38YfIm/4onMdV5thzRGtsYMaKKJMOI8FJgSfTxvWrSXyuLQG/WfaTPNOvolH84RGD4bscNnaUFb1aQxywrG87Bh26HAddx+MSxLai+H7TGfGIWtqiEi25pwG104jNNwx6X6eOECp1Vt78chXjKuqgidyR4FcDP7tiIoL9bWb0+G9EjQv9opyX4I/Rg1JVpVJqskDuvB7n2AXaHUBGBd19zbY50G9hFP5IgeyiVE5xKIlF2kTSX4n7kgxEof8QZRodO6/kSbNqv98NUgdxbuikdYkdolIHbKcO0nz2oMJPNGTl1n++5HkGXfGpjVwWMK4cz0XHpMlXhi19YGMyNXBIt0z9+Z98vqRA6AJEJ+Iwz9tdQt1Nj6Bw4qQBRm3NDQgN9Zrl6KcgOsLIUWaoLeHyOgblGY3kDNmcE9C4q0dva8bldB0xy7Hxtmyt/bkgv+xvu+G7ca01DJAl2S0gWS8iCjq2gF+VVLoadrJko/vBhflaOzBSsVHLjJeiTgE8puCWHUP+wtYUrmi5awyZupHA9NXCGn2LiBm99PrKJ/Ij0pLCzj32JfqL7qmiT3AMbbFYxE5sYd0Q/4zz0Psi6NrxYY4OjBfvMvY2mq3AXreXmqi+z2HMFvKbq/fLLSJO/Nt562WQyyrnksaWaa0L9DLVGz8B6C1Q+2q+FzcBUZfzXZ3cCMoWqoIhMFaqJc/TV0dxR1BCm3p92wZfVgxVwa0Lll8RpbdbAa04+8L6v7uzgLJrrVvB2+TFhsDDrDfcVpyPNRFnK2Gl7G3u1DnzgV4B8FniUOaIXj2LbzYAUjUBleo+jk+3LlrBEvcm4EdSAvzrDC9PS5J1jV2mQZBNsH1M/luaoJDbYDFn4fpDtIoTAXiaUccW/ENMKkXxHMOwtJdt8XMxTvAWu/s6lzcnV0mxpgcHd/XuxFu2kln46HsX6I3ekEUk/30F1BOTfIH0c4P1dak5H++YtV04RsJy9pZKudhVRN8u1/gSmgOcMqkgL6UKWQvgiBxnlM2F1gLAW8UQmil8537NRqxreUO39Q+DptokAQ2dDDQXHdQAF8/FmGi0Sj/4OJtLkoQYtLD3mcwIcrqGoWwWBTlU1Rclfs4bqqS6TIrNPRFHW84w5qnQ05SA0ZfUb/bTB3SH5f0RYtFH+FYnnukl60xL5IFQ3DWH2bxrkaHCx1M6NKMwm1lZT1FYX1/FDVYKod6CtttiFtH/VAJGcEGEux5mV8VFPXb3UrYwEyYII8fwM6VQu1s10YGeyhB4c9pPVyZXNuROUUy0ZDCRQOeFpt2z2aV03PIxLtacnVs4zWfUdQUfgbHWskrz07BlHbAlnc/TONBcXfE4NVTiBUnGuKDIUFFioRc9l1WmWhNgzYeHH9qKL3xqG6x+54AQIL7pd5QjBdsIPYH34N7OgvmHaz6KZ4ytUHhMFKgXappFpvTo73WWO8IXSwW3dvPE45q9195XYbszAp8CWl1W+HsDsN5cGUYR2WJewXiYea/9d3FttpoJ83FHwnVxoST3GxbzoAgLc2AjASudmjLAjTfxzH9cyDtFhBIj/UK4/aZlhMZWbjz3LlaNgIjOdUp/r0VSaF1VWRoTxlm0uCNPh7SLcvZqJxvMpRBh0l208/dEBBDMlSu0wE26/79QOj98SgRbBENusc+kqwha2P0/ECsfRDlaATxfT91zRrzuqYP+SRoABAs79ORdD6VMgXnuuV2Rnb2XswEOt136ISqPkKChf7oOZ0o2XUfUf+hdzlmzL7YP63mEvxh3tPprZpwyxlD8GSxQg/UsgsLhBl3PxxztDJY738ZoUSN7nM2+84vwpTdlIAECdAVVCu4N4YOywHH28SdDQSfrRWCbvQdxxBleOvKEoA/BMNdDcbRS5uInKav45Wa/Nyy2xemA7PUELUinkRe6vjMS+b0qHBwWBhr4/3BSE+nnFd416QMR/e/WNO5m9RWYYQPBzKdBDtXv8DSmXFuiSu1jCOS8biMHUhxYzQMCOmKUWvVrpKKB8HvdEFoRhTG5w3Eh8Rzj8awsEAlJdfymrpxO5ntCB/pwM5IbCXPD2xZpzthxtkdKmPfLkvtPOEz0pSw8b+IwKRAAsF2buNeL51J+5hDDFuyflW7H0B37+NlZo+fKRnzjdr5lE5GfPJ20l3jE8EQYrFcqGi4TFgsT9LIJV+NeZnn2jhOAne2J/CjihT/zd2uak19kWA61k1MP/rc391C62KOi2OPJNXySFBhTKgGZFcPeoxKQXEyGN9kvlhVeu29hIylZTpwsduftnXL0e18PAkpR0QGh5zqBhMALUTjH9luNtfBGTQbiUeHGPLSKf/pQ43kyRT8Iy0AawI2sXMdvRUszY/Q24kswHkXQsPi7KQ1OxzB4N3gxcBnHEHCe0s6Fw0shK/C4NpKm2QjvFM7Y62tnKU9fDNxpuVARbDpi+zJoFUQx8W06VHduvC5byMCfY6UJvYkeYW5CSPLy4tKJQrxG69/rPFrA3V5KznNfB6SCGPL8TxvqbT1uck0x+1nQTCFrLWPqwakZdasx9q7EaukpFwOV7sb0Q7+lDbNcf+WIAAT4OgxEz/JPUN7k7h4HWk9+RmRAmoMg18L7GI1oFf1Z3wuWxeS1M1W8VCwdmXRjvhLKj5cuOqlh8NkojDsLdrY1y4Rq3AfF/9B4Oj7y+Q74FPsDiIF+KXBm8ba5oq9UKYQYhWTkBoxJqJfTDLKgOBZw+yM6wYuVMhWfhhW7XfC61ntS2Y5ud7MAHf2EjmPREWvbQzzZlPBcnZzndCSvbhcjzbY/fRUFNmuB0lEHduHz/bcLML/3hfgYHWQpxFZw7Rn5mieEiUed0k00ZlgLO/7V/wwldb7zT9Bt+97TLj5STyDG4RIfu5+EqDyuo2PyCe5d1TJbWRCTLEh/2BHFJUvabTpZlQbPhhvFQWpXtqU57WPewpjhPsQinAZKrqw+bfJwjjROd2Wrj9qx2unWwMo9IqnMbF/4hpcLOZZPSpDKUwZlk3faCUlpr7kQrDW+0O3XT4lHHDpQpM4aPFDfMwR3ARXNgapR0swYtY2DEnqomd3HoSd4h724nyjfTRiabLzazKBpi+fWpRuH/ElGbIDxpO8D74qNDpoFpHwinWygcxch6TUsfMTIDcF1F9BbP8poGYays10JDV5lq2DctXDqitEszO49HLXKN+/gT5Coisu4GdQ83fEn3ZujUKGavbfTmCi4U69bwk2e5K/UUnCTsPAf7rWSMWhBxyN2IqLjkxy70QBKSMGRZ4+GWwFwBibfM8FI1Hz8UDflxiGeesR5tIbe4h0CMEeHJzO1tvVVpOYtVuEHkcw3KV62lp82RkytzmVbyGKGGXkQMVK8UCxkU7ynTpWbfiMYywXeKnv9A0f2jBakO03itBeH06M7KHhBWg9AmqKMcpjM88/QORde+NJ7enEPAnyoDVlPpIMMxfvJoTiXQqMf1lqgvekYuJX8By4Xce4J1GOjpAx2qtRPo69NwtqkytaY4xfuPqz/AzMg/G8L8Uv0RTWBBVI5ZCktC1VhuEAur5TT41Dg70L/kXzIL2ZNJxP0bnafJt4XbWzc8W2/m1M2AyyLTrD+3va9CA03dF9Qd2owOi+abCbyToGDBcCnq3LdUSNqhQuZvhcFbNPB3qjzGOi2Ut8BdHjkliNevWrKyU87KUdUUEMSlRyJG9PZuGMExGG22js7de5VhkTUnIT5UmPm5+5bCjtcXHJehS/SPYVik2VrN9GrfLrDXGnZRrgMqgpvZkJVzDzXel5NBliKL5a7bJ6p2/c2WVX+D2fNek/bY5sKXCp4PqAX2Kp60xPw56I9y+AjNTqfz8mTkjmpLLGuVD+UFuRFaE+XJ37FN8MrRLUgpGiigEZ0Q/L/AFkrLHsphOEt39ICc1m7NSQD26WXj+IoLKWfd1Ws7IK+BlJ0EQ6vVrZ9eQXo9b46zYmA5sE0Btk7PCAfccluklMrss3s8iu8ApPujaG2JVAUOfjMOsd9fgTREqEorIeg5XnWambQkIEHXucKQb9WAY6/FaT3Y1dDo8rVJryH9JTRTTvh1owWpLAVVBocZ/UzcFDiXim7aGSqVpWVevxd+ABLTuqBxL1ltVSNEeeYNbe04RrZ2JSIC8ZQe/Z8bVV+n7aSQKgPxpGCcfm25Yh7IlwDKJTmrcgwWBj/AUbpHSoFrBFb1DYIb/fFBMOBpwFhg3dAJyl3dBBD0otgDeNDFZCWMvsiyQycUBkVKAdE6+RIsWfPHGvKAmNCvZQwnSUlrUM5FpyxmND3oe//9ErE33rCXwUxfmljdY4gWu5MR6RKHjih61kRvqJkkqlicfMzcSE7tOU66d0kbB6j3lbFubLQXFbv76ozEvURxohJ+WnJc+4QWHCEH//OB8GSK/ZSDvRfCzIHCPv42vbZYnxYsTWH3lM4Z0lRii012q7TYBuUIvrVPgQOSTo3Ug9aHAp6nwY+TP02hd0ToD4pvxEbST5YAg7w3W/spUZxj4buaLzqxru7Le6aLLLRg7h3FQIe+cJBZ4NM9Cx8VAL1XGIo2505qUpHkFi6sXXFwCxtB1Rd0PkSZrRST3r1Yx6ikf80EL8AY2WlzmlveKeJJ4aeobBdu2MuA9uACs7j0qi402vTYdgcdAdVK39uDrRKVnokZ+ml11zdNAOFdea05cDFgM5oYXXplUHWVNnJJ6B1vl4ZTlR3cKKTJ2BWRSedC4PJ2zKChIT3NdBJcrA8GPwR0ELxg5hXlhYWDypzC3TgPk9uUZ7MR011MRZOArW9gL+B3+hKtRrdlAHWG80mG6Ky6PwiIwY7o+vVk93WgoMRkWvaqQpOxS7zrH2Jj4nEFcpA7dHs7MRKblj13/4sp4usUrdx2udf2/xyx6o29z8bHmkZ4vDLN/Bp5ckf5BnGNIgPYhkML6UuifVOUHZbW8pcK49MdDChfTzV1Jc7zylY4jdbPVfPoWKwxFO2/kiHEgyRkgEQuvzZZrz66+hKWa6vdyvBGgP9cw8AsfR2WU3Gq+T8MP2Scph/e2S7VEnv6UtvjCa7ZH8kcFBcxooPfkF3S/BySzPEmKAbxAE+IaT0RG9B+qMh1K+3mm110BfFietKo98PBsSXmVCJpA+5XU4CX+k7Z3mtiK1Trcy8YkEGLOjmwesHYlYkQ66gwAiDBpwRoTfZqDvICUFm3eXJjtSTHJ0cVgsj3GFQnrJBrDAy3AikXH52SANszMXpoFZkzgKN1lDPL+kDDx8T8RiCplWqnnCQjUy07tWhTV6PHh7Z8j6kkmPxwfdRfiH6G/Ixs1/Fzi9wgUyj+48oxxC1mZhTl3S7JtKBed5D1eTlbNmr/ZJ/vYsQzXZf9xUMv+TsOEMXh/XK2O0y/g0nX3YMH0qK8fLFbkLk/DtYnxf3MyPlQsqiqL2sOuscQVm3oQyRL22QEeyzxET+U1Ph9DQnp9op7SKHkFDYg4W0t675w9XfObeNj+/o9G7BpibISvVsUWy/hHNqERNuLnWiMxG6AFMwpuWGszMkQApbnLtcCx5T5TI49kZPSdzFi6MG2ejEPTcQzjS6S4DP7B4p90Ir61KxwBnxZqWv40xrwdcNcq6wRjnZO6sS6xigzPrzx+Y+aW03FVhlcXPKAmmFcfiLKjdUbUi3AndxGGgsmjDvXx/TVmuZhsfPTQWyatIj+j8hejkinjeAd3BHys/juVSosmPOVs3StJ5EYWaCQUJ9QuOJA/O6TEnBlWKvOQMHl9uw7e06bOHWHt8QG61kTCGPbiLjLm3Lrsi9i++a87mu0cZ13EHF3stZdGjh5fyAnfA5jf5R5ensKN5SU8eQh8399QRqI6St37tITwBaWKAuIppPMEwMIjK5AJXqqGqIOB6Cwv6GmtLCiLRSRQtNuYkxAhSNDRbIzR57wxbP6Vaf0v1ZbcOdJQRGCm6Nseha3TMif5s4Gw8LEa0xwxhHOwzuxMPQ9O1gStrTfbtK/QiGQbMZ5NIHbnY3HUKiEE0aKydkFlFvKqvwLj8FJHXs2Yd/E2e7dsawrdm4irEyVtyUY44cmUz9VZat/6+ZplyGZJKSQMdz4QYISLxSc844Ioq89SRSEWQAdxuNxu+wdZQvlpOo/4kkGVPEsf9+xeb8cjcHNStwUtep5RUYFXqiVkn0fkB75J71MgsSuGPPtmckGhdpya4cds5+zvSxnBjRB+7t9tFGJkkD1SCYPt4/12+sUIQKVN9mJB6BbyEHdjaRQRyQ+XQVh9VFy27mVYOq1fRy9tKY931JoopRe05vXe+f1FP+6e55Q/um0QnK9ivAm7SHqXxYMfREDsZhbtTqITqLOYf+iW+0qlQKdskYvcW0pnht0feOveJmzbMerUUidKeQJjp4tGCq/ocVAqdLvjjFeK6BAXSelpRnR/9ehDKQXjzafFUkI2q1o12MnVsoXwIhpn2Q95aWfXJRhHgALxvw+xQGKvr0Gx6QXSFFH1ywbljs7L7iC1YBTJf2JSNyTAgOQ6ukCzrE2RM+/zdEEx1Jk0JhW9XHpP17wrk5irn2cV8nqyG46RFRqRchqTK75pNY060XHEN
*/