// Boost.Bimap
//
// Copyright (c) 2006-2007 Matias Capeletto
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

/// \file relation/mutant_relation.hpp
/// \brief Defines the mutant_relation class

#ifndef BOOST_BIMAP_RELATION_MUTANT_RELATION_HPP
#define BOOST_BIMAP_RELATION_MUTANT_RELATION_HPP

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/config.hpp>

#include <boost/mpl/vector.hpp>
#include <boost/operators.hpp>
#include <boost/call_traits.hpp>

#ifndef BOOST_BIMAP_DISABLE_SERIALIZATION
  #include <boost/serialization/nvp.hpp>
#endif // BOOST_BIMAP_DISABLE_SERIALIZATION

#include <boost/functional/hash/hash.hpp>

#include <boost/mpl/aux_/na.hpp>

// Boost.Bimap
#include <boost/bimap/tags/tagged.hpp>
#include <boost/bimap/tags/support/default_tagged.hpp>
#include <boost/bimap/tags/support/tag_of.hpp>
#include <boost/bimap/tags/support/value_type_of.hpp>

#include <boost/bimap/relation/member_at.hpp>
#include <boost/bimap/relation/detail/mutant.hpp>
#include <boost/bimap/relation/structured_pair.hpp>
#include <boost/bimap/relation/symmetrical_base.hpp>
#include <boost/bimap/relation/support/get.hpp>

namespace boost {
namespace bimaps {
namespace relation {

namespace detail {

// This class is included so structured_pair and mutant_relation share
// exactly the same class layout

template< class LeftType, class RightType, bool force_mutable >
class relation_storage :
    public symmetrical_base<LeftType,RightType,force_mutable>
{
    typedef symmetrical_base<LeftType,RightType,force_mutable> base_;

    typedef relation_storage storage_;

    public:

    typedef relation_storage<LeftType,RightType,false> non_mutable_storage;

    typedef ::boost::mpl::vector2
    <
        relation_storage< LeftType, RightType, true  >,
        relation_storage< LeftType, RightType, false >

    > mutant_views;

    //@{
        /// data
        BOOST_DEDUCED_TYPENAME base_::left_value_type  left;
        BOOST_DEDUCED_TYPENAME base_::right_value_type right;
    //@}

    relation_storage() {}

    relation_storage(BOOST_DEDUCED_TYPENAME ::boost::call_traits<
                         BOOST_DEDUCED_TYPENAME base_::left_value_type
                     >::param_type l,
                     BOOST_DEDUCED_TYPENAME ::boost::call_traits<
                        BOOST_DEDUCED_TYPENAME base_::right_value_type
                     >::param_type r)

        : left(l), right(r) {}

          BOOST_DEDUCED_TYPENAME base_:: left_value_type &  get_left()      { return left;  }
    const BOOST_DEDUCED_TYPENAME base_:: left_value_type &  get_left()const { return left;  }
          BOOST_DEDUCED_TYPENAME base_::right_value_type & get_right()      { return right; }
    const BOOST_DEDUCED_TYPENAME base_::right_value_type & get_right()const { return right; }
};



template< class TA, class TB, class Info, bool force_mutable >
class relation_info_hook : public
 ::boost::bimaps::relation::detail::relation_storage<TA,TB,force_mutable>
{
    typedef ::boost::bimaps::relation::detail::
                relation_storage<TA,TB,force_mutable> base_;

    typedef BOOST_DEDUCED_TYPENAME ::boost::bimaps::tags::support::
        default_tagged<Info,member_at::info>::type tagged_info_type;

    public:
    typedef BOOST_DEDUCED_TYPENAME tagged_info_type::value_type info_type;
    typedef BOOST_DEDUCED_TYPENAME tagged_info_type::tag        info_tag;

    info_type info;

    protected:

    relation_info_hook() {}

    relation_info_hook( BOOST_DEDUCED_TYPENAME ::boost::call_traits<
                           BOOST_DEDUCED_TYPENAME base_::left_value_type
                        >::param_type l,
                        BOOST_DEDUCED_TYPENAME ::boost::call_traits<
                            BOOST_DEDUCED_TYPENAME base_::right_value_type
                        >::param_type r,
                        BOOST_DEDUCED_TYPENAME ::boost::call_traits<
                            info_type
                        >::param_type i = info_type() )

        : base_(l,r), info(i) {}

    template< class Relation >
    relation_info_hook( const Relation & rel ) :
        base_(rel.left,rel.right),
        info(rel.info) {}

    template< class Relation >
    void change_to( const Relation & rel )
    {
        base_::left  = rel.left ;
        base_::right = rel.right;
        info         = rel.info ;
    }

    #ifndef BOOST_BIMAP_DISABLE_SERIALIZATION
    template< class Archive >
    void serialize(Archive & ar, const unsigned int)
    {
        ar & ::boost::serialization::make_nvp("left" , base_::left );
        ar & ::boost::serialization::make_nvp("right", base_::right);
        ar & ::boost::serialization::make_nvp("info" , info        );
    }
    #endif // BOOST_BIMAP_DISABLE_SERIALIZATION
};

template< class TA, class TB, bool force_mutable>
class relation_info_hook<TA,TB,::boost::mpl::na,force_mutable> :
    public ::boost::bimaps::relation::detail::relation_storage<TA,TB,force_mutable>
{
    typedef ::boost::bimaps::relation::detail::
                relation_storage<TA,TB,force_mutable> base_;

    public:
    typedef ::boost::mpl::na info_type;
    typedef member_at::info info_tag;

    protected:

    relation_info_hook() {}

    relation_info_hook( BOOST_DEDUCED_TYPENAME ::boost::call_traits<
                           BOOST_DEDUCED_TYPENAME base_::left_value_type
                        >::param_type l,
                        BOOST_DEDUCED_TYPENAME ::boost::call_traits<
                            BOOST_DEDUCED_TYPENAME base_::right_value_type
                        >::param_type r)

        : base_(l,r) {}

    template< class Relation >
    relation_info_hook( const Relation & rel ) :
        base_(rel.left,rel.right) {}

    template< class Relation >
    void change_to( const Relation & rel )
    {
        base_::left  = rel.left ;
        base_::right = rel.right;
    }

    #ifndef BOOST_BIMAP_DISABLE_SERIALIZATION
    template< class Archive >
    void serialize(Archive & ar, const unsigned int)
    {
        ar & ::boost::serialization::make_nvp("left" , base_::left );
        ar & ::boost::serialization::make_nvp("right", base_::right);
    }
    #endif // BOOST_BIMAP_DISABLE_SERIALIZATION
};


} // namespace detail

/// \brief Abstraction of a related pair of values, that extends the std::pair class.
/**
The mutant_relation is a mutant class. A mutant class can mutate
with zero overhead in other classes that are called views.
Each view has to be StorageCompatible with the base class
of the mutant. Note that all the views have the following
storage structure:

\verbatim
                        __________
                       |          |
                       |    TA    |
                       |__________|
                       |          |
                       |    TB    |
                       |__________|

\endverbatim

See also select_relation, standard_relation.
\ingroup relation_group
                                                           **/


template< class TA, class TB, class Info = ::boost::mpl::na, bool force_mutable = false >
class mutant_relation : public
    ::boost::bimaps::relation::detail::
        relation_info_hook<TA,TB,Info,force_mutable>
{
    typedef ::boost::bimaps::relation::detail::
        relation_info_hook<TA,TB,Info,force_mutable> base_;

    public:

    // We have to know the type of the base where the types are
    // defined because Boost.MultiIndex requires it.

    typedef ::boost::bimaps::relation::detail::
                relation_storage<TA,TB,force_mutable> storage_base;

    /// Above view, non mutable view of the relation

    typedef mutant_relation<TA,TB,Info,false> above_view;

    //@{
        /// A signature compatible std::pair that is a view of the relation.

        typedef structured_pair< TA, TB, Info, normal_layout >  left_pair;
        typedef structured_pair< TB, TA, Info, mirror_layout > right_pair;
    //@}

    typedef ::boost::mpl::vector4
    <
         left_pair,
        right_pair,

        mutant_relation< TA, TB, Info, true  >,
        mutant_relation< TA, TB, Info, false >

    > mutant_views;

    mutant_relation() {}

    mutant_relation(BOOST_DEDUCED_TYPENAME ::boost::call_traits<
                        BOOST_DEDUCED_TYPENAME base_:: left_value_type
                    >::param_type l,
                    BOOST_DEDUCED_TYPENAME ::boost::call_traits<
                        BOOST_DEDUCED_TYPENAME base_::right_value_type
                    >::param_type r) :
        base_(l,r) {}

    mutant_relation(BOOST_DEDUCED_TYPENAME ::boost::call_traits<
                        BOOST_DEDUCED_TYPENAME base_:: left_value_type
                    >::param_type l,
                    BOOST_DEDUCED_TYPENAME ::boost::call_traits<
                        BOOST_DEDUCED_TYPENAME base_::right_value_type
                    >::param_type r,
                    BOOST_DEDUCED_TYPENAME ::boost::call_traits<
                        BOOST_DEDUCED_TYPENAME base_::info_type
                    >::param_type i) :
        base_(l,r,i) {}

    mutant_relation(const mutant_relation<TA,TB,Info,false> & rel) :
        base_(rel) {}

    mutant_relation(const mutant_relation<TA,TB,Info,true> & rel) :
        base_(rel) {}

    // Operators

    template< bool FM >
    mutant_relation& operator=(const mutant_relation<TA,TB,Info,FM> & rel)
    {
        base_::change_to(rel);
        return *this;
    }

    // The following functions are redundant if you only consider this class.
    // They are included to make easier the construction of the get and the
    // pair_by metafunction. Remember that not all compiler supports the mutant
    // idiom.

    left_pair & get_left_pair()
    {
        return ::boost::bimaps::relation::detail::mutate<left_pair>(*this);
    }

    const left_pair & get_left_pair() const
    {
        return ::boost::bimaps::relation::detail::mutate<left_pair>(*this);
    }

    right_pair & get_right_pair()
    {
        return ::boost::bimaps::relation::detail::mutate<right_pair>(*this);
    }

    const right_pair & get_right_pair() const
    {
        return ::boost::bimaps::relation::detail::mutate<right_pair>(*this);
    }

    above_view & get_view()
    {
        return ::boost::bimaps::relation::detail::mutate<above_view>(*this);
    }

    const above_view & get_view() const
    {
        return ::boost::bimaps::relation::detail::mutate<above_view>(*this);
    }

    template< class Tag >
    const BOOST_DEDUCED_TYPENAME ::boost::bimaps::relation::support::
        result_of::get<Tag,const mutant_relation>::type
    get() const
    {
        return ::boost::bimaps::relation::support::get<Tag>(*this);
    }

    template< class Tag >
    BOOST_DEDUCED_TYPENAME ::boost::bimaps::relation::support::
        result_of::get<Tag,mutant_relation>::type
    get()
    {
        return ::boost::bimaps::relation::support::get<Tag>(*this);
    }
    
    #ifndef BOOST_BIMAP_DISABLE_SERIALIZATION

    private:
    friend class ::boost::serialization::access;

    template<class Archive>
    void serialize(Archive & ar, const unsigned int version)
    {
        base_::serialize(ar,version);
    }

    #endif // BOOST_BIMAP_DISABLE_SERIALIZATION
};

// hash value

template< class FirstType, class SecondType, bool FM >
std::size_t hash_value(const detail::relation_storage<FirstType,SecondType,FM> & r)
{
    std::size_t seed = 0;
    ::boost::hash_combine(seed, r. left );
    ::boost::hash_combine(seed, r.right );

    return seed;
}

// mutant_relation - mutant_relation

template< class FirstType, class SecondType, bool FM1, bool FM2 >
bool operator==(const detail::relation_storage<FirstType,SecondType,FM1> & a,
                const detail::relation_storage<FirstType,SecondType,FM2> & b)
{
    return ( ( a.left  == b.left  ) &&
             ( a.right == b.right ) );
}

template< class FirstType, class SecondType, bool FM1, bool FM2 >
bool operator!=(const detail::relation_storage<FirstType,SecondType,FM1> & a,
                const detail::relation_storage<FirstType,SecondType,FM2> & b)
{
    return ! ( a == b );
}

template< class FirstType, class SecondType, bool FM1, bool FM2 >
bool operator<(const detail::relation_storage<FirstType,SecondType,FM1> & a,
               const detail::relation_storage<FirstType,SecondType,FM2> & b)
{
    return (  ( a.left  <  b.left  ) ||
             (( a.left == b.left ) && ( a.right < b.right )));
}

template< class FirstType, class SecondType, bool FM1, bool FM2 >
bool operator<=(const detail::relation_storage<FirstType,SecondType,FM1> & a,
                const detail::relation_storage<FirstType,SecondType,FM2> & b)
{
    return (  ( a.left  <  b.left  ) ||
             (( a.left == b.left ) && ( a.right <= b.right )));
}

template< class FirstType, class SecondType, bool FM1, bool FM2 >
bool operator>(const detail::relation_storage<FirstType,SecondType,FM1> & a,
               const detail::relation_storage<FirstType,SecondType,FM2> & b)
{
    return ( ( a.left  >  b.left  ) ||
             (( a.left == b.left ) && ( a.right > b.right )));
}

template< class FirstType, class SecondType, bool FM1, bool FM2 >
bool operator>=(const detail::relation_storage<FirstType,SecondType,FM1> & a,
                const detail::relation_storage<FirstType,SecondType,FM2> & b)
{
    return ( ( a.left  >  b.left  ) ||
             (( a.left == b.left ) && ( a.right >= b.right )));
}

namespace detail {

template< class TA, class TB, class Info, bool force_mutable>
mutant_relation<TA,TB,Info,force_mutable> 
    copy_with_left_replaced(mutant_relation<TA,TB,Info,force_mutable> const& rel,
        BOOST_DEDUCED_TYPENAME ::boost::call_traits< BOOST_DEDUCED_TYPENAME 
            mutant_relation<TA,TB,Info,force_mutable>::left_value_type>
                ::param_type l)
{
    return mutant_relation<TA,TB,Info,force_mutable>(l,rel.right,rel.info);
}
    
template< class TA, class TB, bool force_mutable>
mutant_relation<TA,TB,::boost::mpl::na,force_mutable>
    copy_with_left_replaced(mutant_relation<TA,TB,::boost::mpl::na,force_mutable> const& rel,
        BOOST_DEDUCED_TYPENAME ::boost::call_traits< BOOST_DEDUCED_TYPENAME 
            mutant_relation<TA,TB,::boost::mpl::na,force_mutable>::left_value_type>
                ::param_type l)
{
    return mutant_relation<TA,TB,::boost::mpl::na,force_mutable>(l,rel.right);  
}
    
template< class TA, class TB, class Info, bool force_mutable>
mutant_relation<TA,TB,Info,force_mutable> 
    copy_with_right_replaced(mutant_relation<TA,TB,Info,force_mutable> const& rel,
        BOOST_DEDUCED_TYPENAME ::boost::call_traits< BOOST_DEDUCED_TYPENAME 
            mutant_relation<TA,TB,Info,force_mutable>::right_value_type>
                ::param_type r)
{
    return mutant_relation<TA,TB,Info,force_mutable>(rel.left,r,rel.info);
}
    
template< class TA, class TB, bool force_mutable>
mutant_relation<TA,TB,::boost::mpl::na,force_mutable>
    copy_with_right_replaced(mutant_relation<TA,TB,::boost::mpl::na,force_mutable> const& rel,
        BOOST_DEDUCED_TYPENAME ::boost::call_traits< BOOST_DEDUCED_TYPENAME 
            mutant_relation<TA,TB,::boost::mpl::na,force_mutable>::right_value_type>
                ::param_type r)
{
    return mutant_relation<TA,TB,::boost::mpl::na,force_mutable>(rel.left,r);  
}

} // namespace detail

} // namespace relation
} // namespace bimaps
} // namespace boost


#endif // BOOST_BIMAP_RELATION_MUTANT_RELATION_HPP




/* mutant_relation.hpp
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
*/