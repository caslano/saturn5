// Boost.Bimap
//
// Copyright (c) 2006-2007 Matias Capeletto
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

/// \file relation/structured_pair.hpp
/// \brief Defines the structured_pair class.

#ifndef BOOST_BIMAP_RELATION_STRUCTURED_PAIR_HPP
#define BOOST_BIMAP_RELATION_STRUCTURED_PAIR_HPP

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/config.hpp>

#include <utility>

#include <boost/type_traits/remove_const.hpp>

#include <boost/mpl/aux_/na.hpp>

#include <boost/call_traits.hpp>

#include <boost/utility/enable_if.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/mpl/if.hpp>
#include <boost/mpl/vector.hpp>

#include <boost/bimap/detail/debug/static_error.hpp>
#include <boost/bimap/relation/pair_layout.hpp>
#include <boost/bimap/relation/symmetrical_base.hpp>
#include <boost/bimap/relation/support/get.hpp>
#include <boost/bimap/tags/support/value_type_of.hpp>



namespace boost {
namespace bimaps {
namespace relation {

namespace detail {

/// \brief Storage definition of the left view of a mutant relation.
/**

See also storage_finder, mirror_storage.
                                                                            **/

template< class FirstType, class SecondType >
class normal_storage :
    public symmetrical_base<FirstType,SecondType>
{
    typedef symmetrical_base<FirstType,SecondType> base_;

    public:

    typedef normal_storage storage_;

    typedef BOOST_DEDUCED_TYPENAME base_::left_value_type  first_type;
    typedef BOOST_DEDUCED_TYPENAME base_::right_value_type second_type;

    first_type   first;
    second_type  second;

    normal_storage() {}

    normal_storage(BOOST_DEDUCED_TYPENAME ::boost::call_traits<
                        first_type >::param_type f,
                   BOOST_DEDUCED_TYPENAME ::boost::call_traits<
                        second_type>::param_type s)

        : first(f), second(s) {}

          BOOST_DEDUCED_TYPENAME base_:: left_value_type &  get_left()      { return first;  }
    const BOOST_DEDUCED_TYPENAME base_:: left_value_type &  get_left()const { return first;  }
          BOOST_DEDUCED_TYPENAME base_::right_value_type & get_right()      { return second; }
    const BOOST_DEDUCED_TYPENAME base_::right_value_type & get_right()const { return second; }
};

/// \brief Storage definition of the right view of a mutant relation.
/**

See also storage_finder, normal_storage.
                                                                            **/

template< class FirstType, class SecondType >
class mirror_storage :
    public symmetrical_base<SecondType,FirstType>
{
    typedef symmetrical_base<SecondType,FirstType> base_;

    public:

    typedef mirror_storage storage_;

    typedef BOOST_DEDUCED_TYPENAME base_::left_value_type   second_type;
    typedef BOOST_DEDUCED_TYPENAME base_::right_value_type  first_type;

    second_type  second;
    first_type   first;

    mirror_storage() {}

    mirror_storage(BOOST_DEDUCED_TYPENAME ::boost::call_traits<first_type  >::param_type f,
                   BOOST_DEDUCED_TYPENAME ::boost::call_traits<second_type >::param_type s)

        : second(s), first(f)  {}

          BOOST_DEDUCED_TYPENAME base_:: left_value_type &  get_left()      { return second; }
    const BOOST_DEDUCED_TYPENAME base_:: left_value_type &  get_left()const { return second; }
          BOOST_DEDUCED_TYPENAME base_::right_value_type & get_right()      { return first;  }
    const BOOST_DEDUCED_TYPENAME base_::right_value_type & get_right()const { return first;  }
};

/** \struct boost::bimaps::relation::storage_finder
\brief Obtain the a storage with the correct layout.

\code
template< class FirstType, class SecondType, class Layout >
struct storage_finder
{
    typedef {normal/mirror}_storage<FirstType,SecondType> type;
};
\endcode

See also normal_storage, mirror_storage.
                                                                        **/

#ifndef BOOST_BIMAP_DOXYGEN_WILL_NOT_PROCESS_THE_FOLLOWING_LINES

template
<
    class FirstType,
    class SecondType,
    class Layout
>
struct storage_finder
{
    typedef normal_storage<FirstType,SecondType> type;
};

template
<
    class FirstType,
    class SecondType
>
struct storage_finder<FirstType,SecondType,mirror_layout>
{
    typedef mirror_storage<FirstType,SecondType> type;
};

#endif // BOOST_BIMAP_DOXYGEN_WILL_NOT_PROCESS_THE_FOLLOWING_LINES


template< class TA, class TB, class Info, class Layout >
class pair_info_hook :
    public ::boost::bimaps::relation::detail::storage_finder<TA,TB,Layout>::type
{
    typedef BOOST_DEDUCED_TYPENAME ::boost::bimaps::relation::detail::storage_finder<TA,TB,Layout>::type base_;

    typedef BOOST_DEDUCED_TYPENAME ::boost::bimaps::tags::support::
        default_tagged<Info,member_at::info>::type tagged_info_type;

    public:
    typedef BOOST_DEDUCED_TYPENAME tagged_info_type::value_type info_type;
    typedef BOOST_DEDUCED_TYPENAME tagged_info_type::tag        info_tag;

    info_type info;

    protected:

    pair_info_hook() {}

    pair_info_hook( BOOST_DEDUCED_TYPENAME ::boost::call_traits<
                        BOOST_DEDUCED_TYPENAME base_::first_type
                    >::param_type f,
                    BOOST_DEDUCED_TYPENAME ::boost::call_traits<
                        BOOST_DEDUCED_TYPENAME base_::second_type
                    >::param_type s,
                    BOOST_DEDUCED_TYPENAME ::boost::call_traits<
                        info_type
                    >::param_type i = info_type() )
        : base_(f,s), info(i) {}

    template< class Pair >
    pair_info_hook( const Pair & p) :
        base_(p.first,p.second),
        info(p.info) {}

    template< class Pair >
    void change_to( const Pair & p )
    {
        base_::first  = p.first ;
        base_::second = p.second;
        info          = p.info  ;
    }

    void clear_info()
    {
        info = info_type();
    };
};

template< class TA, class TB, class Layout>
class pair_info_hook<TA,TB,::boost::mpl::na,Layout> :
    public ::boost::bimaps::relation::detail::storage_finder<TA,TB,Layout>::type
{
    typedef BOOST_DEDUCED_TYPENAME ::boost::bimaps::relation::detail::storage_finder<TA,TB,Layout>::type base_;

    public:
    typedef ::boost::mpl::na info_type;
    typedef member_at::info info_tag;

    protected:

    pair_info_hook() {}

    pair_info_hook( BOOST_DEDUCED_TYPENAME ::boost::call_traits<
                        BOOST_DEDUCED_TYPENAME base_::first_type
                    >::param_type f,
                    BOOST_DEDUCED_TYPENAME ::boost::call_traits<
                        BOOST_DEDUCED_TYPENAME base_::second_type
                    >::param_type s)

        : base_(f,s) {}

    template< class Pair >
    pair_info_hook( const Pair & p ) :
        base_(p.first,p.second) {}

    template< class Pair >
    void change_to( const Pair & p )
    {
        base_::first  = p.first ;
        base_::second = p.second;
    }

    void clear_info() {};
};



} // namespace detail

template< class TA, class TB, class Info, bool FM >
class mutant_relation;


/// \brief A std::pair signature compatible class that allows you to control
///        the internal structure of the data.
/**
This class allows you to specify the order in wich the two data types will be
in the layout of the class.
                                                                               **/

template< class FirstType, class SecondType, class Info, class Layout = normal_layout >
class structured_pair :

    public ::boost::bimaps::relation::detail::pair_info_hook
    <
        FirstType, SecondType,
        Info,
        Layout

    >

{
    typedef BOOST_DEDUCED_TYPENAME ::boost::bimaps::relation::detail::pair_info_hook
    <
        FirstType, SecondType,
        Info,
        Layout

    > base_;

    public:

    typedef ::boost::mpl::vector3<
        structured_pair< FirstType, SecondType, Info, normal_layout >,
        structured_pair< FirstType, SecondType, Info, mirror_layout >,
        BOOST_DEDUCED_TYPENAME ::boost::mpl::if_<
            BOOST_DEDUCED_TYPENAME ::boost::is_same<Layout, normal_layout>::type,
            mutant_relation< FirstType, SecondType, Info, true >,
            mutant_relation< SecondType, FirstType, Info, true >
        >::type

    > mutant_views;

    structured_pair() {}

    structured_pair(BOOST_DEDUCED_TYPENAME boost::call_traits<
                        BOOST_DEDUCED_TYPENAME base_::first_type  >::param_type f,
                    BOOST_DEDUCED_TYPENAME boost::call_traits<
                        BOOST_DEDUCED_TYPENAME base_::second_type >::param_type s)
        : base_(f,s) {}

    structured_pair(BOOST_DEDUCED_TYPENAME boost::call_traits<
                        BOOST_DEDUCED_TYPENAME base_::first_type  >::param_type f,
                    BOOST_DEDUCED_TYPENAME boost::call_traits<
                        BOOST_DEDUCED_TYPENAME base_::second_type >::param_type s,
                    BOOST_DEDUCED_TYPENAME boost::call_traits<
                        BOOST_DEDUCED_TYPENAME base_::info_type   >::param_type i)
        : base_(f,s,i) {}

    template< class OtherLayout >
    structured_pair(
        const structured_pair<FirstType,SecondType,Info,OtherLayout> & p)
        : base_(p) {}

    template< class OtherLayout >
    structured_pair& operator=(
        const structured_pair<FirstType,SecondType,OtherLayout> & p)
    {
        base_::change_to(p);
        return *this;
    }

    template< class First, class Second >
    structured_pair(const std::pair<First,Second> & p) :
        base_(p.first,p.second)
    {}

    template< class First, class Second >
    structured_pair& operator=(const std::pair<First,Second> & p)
    {
        base_::first  = p.first;
        base_::second = p.second;
        base_::clear_info();
        return *this;
    }

    template< class Tag >
    const BOOST_DEDUCED_TYPENAME ::boost::bimaps::relation::support::
        result_of::get<Tag,const structured_pair>::type
    get() const
    {
        return ::boost::bimaps::relation::support::get<Tag>(*this);
    }

    template< class Tag >
    BOOST_DEDUCED_TYPENAME ::boost::bimaps::relation::support::
        result_of::get<Tag,structured_pair>::type
    get()
    {
        return ::boost::bimaps::relation::support::get<Tag>(*this);
    }
};

// structured_pair - structured_pair

template< class FirstType, class SecondType, class Info, class Layout1, class Layout2 >
bool operator==(const structured_pair<FirstType,SecondType,Info,Layout1> & a,
                const structured_pair<FirstType,SecondType,Info,Layout2> & b)
{
    return ( ( a.first  == b.first  ) &&
             ( a.second == b.second ) );
}

template< class FirstType, class SecondType, class Info, class Layout1, class Layout2 >
bool operator!=(const structured_pair<FirstType,SecondType,Info,Layout1> & a,
                const structured_pair<FirstType,SecondType,Info,Layout2> & b)
{
    return ! ( a == b );
}

template< class FirstType, class SecondType, class Info, class Layout1, class Layout2 >
bool operator<(const structured_pair<FirstType,SecondType,Info,Layout1> & a,
               const structured_pair<FirstType,SecondType,Info,Layout2> & b)
{
    return (  ( a.first  <  b.first  ) ||
             (( a.first == b.first ) && ( a.second < b.second )));
}

template< class FirstType, class SecondType, class Info, class Layout1, class Layout2 >
bool operator<=(const structured_pair<FirstType,SecondType,Info,Layout1> & a,
                const structured_pair<FirstType,SecondType,Info,Layout2> & b)
{
    return (  ( a.first  <  b.first  ) ||
             (( a.first == b.first ) && ( a.second <= b.second )));
}

template< class FirstType, class SecondType, class Info, class Layout1, class Layout2 >
bool operator>(const structured_pair<FirstType,SecondType,Info,Layout1> & a,
               const structured_pair<FirstType,SecondType,Info,Layout2> & b)
{
    return ( ( a.first  >  b.first  ) ||
             (( a.first == b.first ) && ( a.second > b.second )));
}

template< class FirstType, class SecondType, class Info, class Layout1, class Layout2 >
bool operator>=(const structured_pair<FirstType,SecondType,Info,Layout1> & a,
                const structured_pair<FirstType,SecondType,Info,Layout2> & b)
{
    return ( ( a.first  >  b.first  ) ||
             (( a.first == b.first ) && ( a.second >= b.second )));
}

// structured_pair - std::pair

template< class FirstType, class SecondType, class Info, class Layout, class F, class S >
bool operator==(const structured_pair<FirstType,SecondType,Info,Layout> & a,
                const std::pair<F,S> & b)
{
    return ( ( a.first  == b.first  ) &&
             ( a.second == b.second ) );
}

template< class FirstType, class SecondType, class Info, class Layout, class F, class S >
bool operator!=(const structured_pair<FirstType,SecondType,Info,Layout> & a,
                const std::pair<F,S> & b)
{
    return ! ( a == b );
}

template< class FirstType, class SecondType, class Info, class Layout, class F, class S >
bool operator<(const structured_pair<FirstType,SecondType,Info,Layout> & a,
               const std::pair<F,S> & b)
{
    return (  ( a.first  <  b.first  ) ||
             (( a.first == b.first ) && ( a.second < b.second )));
}

template< class FirstType, class SecondType, class Info, class Layout, class F, class S >
bool operator<=(const structured_pair<FirstType,SecondType,Info,Layout> & a,
                const std::pair<F,S> & b)
{
    return (  ( a.first  <  b.first  ) ||
             (( a.first == b.first ) && ( a.second <= b.second )));
}

template< class FirstType, class SecondType, class Info, class Layout, class F, class S >
bool operator>(const structured_pair<FirstType,SecondType,Info,Layout> & a,
               const std::pair<F,S> & b)
{
    return ( ( a.first  >  b.first  ) ||
             (( a.first == b.first ) && ( a.second > b.second )));
}

template< class FirstType, class SecondType, class Info, class Layout, class F, class S >
bool operator>=(const structured_pair<FirstType,SecondType,Info,Layout> & a,
                const std::pair<F,S> & b)
{
    return ( ( a.first  >  b.first  ) ||
             (( a.first == b.first ) && ( a.second >= b.second )));
}

// std::pair - sturctured_pair

template< class FirstType, class SecondType, class Info, class Layout, class F, class S >
bool operator==(const std::pair<F,S> & a,
                const structured_pair<FirstType,SecondType,Info,Layout> & b)
{
    return ( ( a.first  == b.first  ) &&
             ( a.second == b.second ) );
}

template< class FirstType, class SecondType, class Info, class Layout, class F, class S >
bool operator!=(const std::pair<F,S> & a,
                const structured_pair<FirstType,SecondType,Info,Layout> & b)
{
    return ! ( a == b );
}

template< class FirstType, class SecondType, class Info, class Layout, class F, class S >
bool operator<(const std::pair<F,S> & a,
               const structured_pair<FirstType,SecondType,Info,Layout> & b)
{
    return (  ( a.first  <  b.first  ) ||
             (( a.first == b.first ) && ( a.second < b.second )));
}

template< class FirstType, class SecondType, class Info, class Layout, class F, class S >
bool operator<=(const std::pair<F,S> & a,
                const structured_pair<FirstType,SecondType,Info,Layout> & b)
{
    return (  ( a.first  <  b.first  ) ||
             (( a.first == b.first ) && ( a.second <= b.second )));
}

template< class FirstType, class SecondType, class Info, class Layout, class F, class S >
bool operator>(const std::pair<F,S> & a,
               const structured_pair<FirstType,SecondType,Info,Layout> & b)
{
    return ( ( a.first  >  b.first  ) ||
             (( a.first == b.first ) && ( a.second > b.second )));
}

template< class FirstType, class SecondType, class Info, class Layout, class F, class S >
bool operator>=(const std::pair<F,S> & a,
                const structured_pair<FirstType,SecondType,Info,Layout> & b)
{
    return ( ( a.first  >  b.first  ) ||
             (( a.first == b.first ) && ( a.second >= b.second )));
}


namespace detail {

template< class FirstType, class SecondType, class Info, class Layout>
structured_pair<FirstType,SecondType,Info,Layout> 
    copy_with_first_replaced(structured_pair<FirstType,SecondType,Info,Layout> const& p,
        BOOST_DEDUCED_TYPENAME ::boost::call_traits< BOOST_DEDUCED_TYPENAME 
            structured_pair<FirstType,SecondType,Info,Layout>::first_type>
                ::param_type f)
{
    return structured_pair<FirstType,SecondType,Info,Layout>(f,p.second,p.info);
}
    
template< class FirstType, class SecondType, class Layout>
structured_pair<FirstType,SecondType,::boost::mpl::na,Layout> 
    copy_with_first_replaced(structured_pair<FirstType,SecondType,::boost::mpl::na,Layout> const& p,
        BOOST_DEDUCED_TYPENAME ::boost::call_traits< BOOST_DEDUCED_TYPENAME 
            structured_pair<FirstType,SecondType,::boost::mpl::na,Layout>::first_type>
                ::param_type f)
{
    return structured_pair<FirstType,SecondType,::boost::mpl::na,Layout>(f,p.second);
}
    
template< class FirstType, class SecondType, class Info, class Layout>
structured_pair<FirstType,SecondType,Info,Layout> 
    copy_with_second_replaced(structured_pair<FirstType,SecondType,Info,Layout> const& p,
        BOOST_DEDUCED_TYPENAME ::boost::call_traits< BOOST_DEDUCED_TYPENAME 
            structured_pair<FirstType,SecondType,Info,Layout>::second_type>
                ::param_type s)
{
    return structured_pair<FirstType,SecondType,Info,Layout>(p.first,s,p.info);
}
    
template< class FirstType, class SecondType, class Layout>
structured_pair<FirstType,SecondType,::boost::mpl::na,Layout> 
    copy_with_second_replaced(structured_pair<FirstType,SecondType,::boost::mpl::na,Layout> const& p,
        BOOST_DEDUCED_TYPENAME ::boost::call_traits< BOOST_DEDUCED_TYPENAME 
            structured_pair<FirstType,SecondType,::boost::mpl::na,Layout>::second_type>
                ::param_type s)
{
    return structured_pair<FirstType,SecondType,::boost::mpl::na,Layout>(p.first,s);
}

} // namespace detail


} // namespace relation
} // namespace bimaps
} // namespace boost

#endif // BOOST_BIMAP_RELATION_STRUCTURED_PAIR_HPP


/* structured_pair.hpp
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
*/