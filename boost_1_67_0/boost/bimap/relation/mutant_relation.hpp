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