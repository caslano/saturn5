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
This class allows you to specify the order in which the two data types will be
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
/BzDhBaYuFDpip81aUxTHlTeLhggwepDKP7fLGcIqh7pd/jYMxvkuLnsSYGHclq1nm0lnoX37S6WweQuFsOrYUsX9VEPVJbUtvQlAFoMqFSevYjHoScJSO1WXsZHKrRlHLRSgxBnAglZQZuzUKS9Bnu/OMx+WgVxNDcDGw668k7kc6FR/X/t94xQIO8sYwtJh20o9Zop4qQ54wiJC+rlj6iDPBAnQdMd0egw6RBrEANxDKzqm0TtrPtrzwR1KDd+8PBjg9TOOmdG4Xdu+g6jLf6IAiO162amuu7oll1MgmQmpYrPczWbaGmc8JqNT3YUOBvozsnrkT6+rEdg7uH3cpJ2oOQ8iCi2i5ffWnEkB/6Kk7SIyZDODBuDQT/aPcZpZkmZ8tQDpFhvRQAhQ+JCWpgd9TYd5h5U/hu7I3wcFJdt+HIu5JGaFZYKUUvcADAOTITgr3M6b54GWDrwIcrpXZ9FYWpbLvDAwK8G9Nq575etPDl9GG+5dD6cUa8OQEidgrChwWLPCF6E26m7NgW5onSGIjqJwkGiqPetEKI/qEtDvj4jGQwA+I+3AgHhIZ7B7NU2guCufe4FX0z6CjwYFdT77622hlbri0l4UaBW6kfiDAD357JnzBX/cfUqXd2SjdE4khFZRyORN5saWeFouB5ekGkgZTZwDLhyPwxwXKE0dnoCEt8F4Idfi3r4C7UmX2dSyPgYB6Yz4GiNClT1Fy10aEf65gl1WG5BggShFX1WIl+rQvOswOBQRDDwU7NG+Y4TPr9VUThSDEQKMRbMF564CxLW/+ayU0T4oMILGkbh0EoRzVri4PPCV+ld6NHUVBn3k6PCDVHw/keFNY13HRx89b24egibKYWGZCdJyh2kafiU1JgCESh2rvdAzVt7JnATbttskhVVTcvhHZyYc4MbLqFX/Bky5iPFBl+jTqvWhEjbH1e8dDZcEIFC57na6N7LYzOMfEXicxzzT5ueTha3CpmkcNpqa015VGL+gq3zcccVU6BEm6dECFXVcrIckZdWQQ+BfVNjJt3vAl1/voE+MwsYMgnh0/FOKcfKCnDtk90FHor1n/DmtLEHI1AEbowjgv1p51iVpZSnrmAJLiAGNT3HnqEUoAtlTDSuFJ28SCpKkrqWhp67ryaeXZYpx3ZmbIXeEINbOdLqC1fZtTNDuz8oEVujJRlBCHl6nPDqdCVO615Gogo/OlFiKe3w4TPgsTPu4vBTXaLJlg4BWbVEVROS3pXHuqzCnNEVI7Gov3gwA9z2gaxIkjmFoMJFvEKUv64+oh9P+IoQO6EIRvcw605n/wo+WrTXd0+3Jz2gw/l7ycMtogv68DpeYbL9IKYVXHiBX87nPz32KlprmDhJFf/dyglgkBy66/npv+GQMcHokrdsTm0jRoNQb0rrTFqSioQipjm+SfG5vGEwGoiH0SjNppokEWb6Q3izO9Az9NBiuKOw6JIKnQ62FbW7GOcIxtl1oTHAAkOc0yHRSterO8GbhhjmI9Krx7nNZrfBwFKIAGZ1L8Qn8r+pAn4BmEQX2M2JlJpauSh7DLGmGTlGGYiKGrJQqkHEgCLcIX2dv0HNpS1oRtOV6LeT35NBaVKY4hwyKbM1r5TcCY1UPwrkgmrl96fPSm+h5cal5G/WwL9djikNR032pFpU52R4tbeQsl4kVvXwUjUx2Xt+EYVXCcGP92o1fMNbiJTVtOLJ/DTZsGpvwefq6G0yYrf+Cdu67ukgPRkyxvAPX2Hifzro0iKm46sM+5Gw6Y4BDeUB+HWD548gnvmViilTbi653sRB9Op3mmc0bwiVlfGleHKqjq6qapodYpg9Hp9jyCtYKCh54IWV/mPO70OXxsFHb8W0cCoMS7O5Y9ImUwHKTP0wQhTU/oUrTVa+llqcrHtRSEZwMbHv9IoD6hj8vTEVdx54rvhwdLQo0NjQMH9WB3G/RlsyMWnwei3RoInaoRkCthF0LmuY3YxWE8MBV8OmBPjXAm+MELIPIABbYExd2D9QWRr2e5T2NS3cwQfTc30LN8kkz9fad31ng2Ta8rykE11CKyyR5AvbZEuv3O86xkbD7X4LNg3m2T+LMgsTfvdBaQaVm7dA7/DVWWZPQVvgL6ihq1t8co2tZDvNcQonaTr+uHn4DBcbzuzKP4ekfDC/mBgqwrcOChrSf81e0Hh2CxbvPX4Qx/LhqXyn3sW967P2sNugb5RqlelhbsjP7zGyBBgRamm5lXRLwvOe/gRu+HQtsjRUxr1u5hM+n0Y4b2kexghp7sTxmd+6BxriQuSJ9u8eNfS4ZEZ2Hv4BoTbvy1evXgX/BSoFHiWKN3gpHgT56ljLIwF97qKRX09wOmkWzAVYkY4Yxel9RZF93o1tssd7KW9ti4haMAavJSfFmU78eE+a3+mz4qTzGMQ+YZRI5Ax9+TbuEfYfMJ2DPn+0WlLPIZIic0XC8xiT1h0e6jwSqLuQzBrhNCSACIVYfWezQotZZrbiocuWnl+sXoNIA6iKGZrSJr9BGR4zAqNW408kaz6SyCmBuOExD3IVh40NzTaHYOMhFLT1dfVJ7GXYW4v1dUCzil3DiC2NyLvZxBZONlIfDpFGRvA64yDBwLkiRS6L4K7coSOsXTTJWvW/yUbX6ng8b+GBbbJxtEIbs3gxKub9vOkO3dtKhFrYXfP+8eQCrCXJbdr2fjkJ3NLGg9fjEkeLNP48bT7q9ucZkpiFRrEMHNW7UcwSQT8sBOUB+Q6sYIsF/FLNGVGi16BXeAQjgILiQzxJVfZ4XwT3ZmZ3s/Y6wZ5dzUOXyii6btMucEJfgpk1rCg+gIH5H8UaWi7vM3MrPpswG7SjdqpQvY9yzsCwovRwSwjXrtlqip4smZ32xesLbh7nDllsZ42fjt5rvhD3jopha2Sg6B8Srnm663o+cD/njhwybsOXE/syPv+w/cXxaKWk1c7c7P38Fbw34/A0QteamjabBD419Ib+8y8rWi0WbuJFHrE5yxyjY6bUYtS5/4aIBfZA5d4vsbrHxgL8ZLM/r01PfWfH4rDvUKAJwgNzgGrNhjTiNLKcbc8++CdAOub1NDUzr0KCBSl6EMQmVxyY7jp67KsmmJH7d49bySzLVhrjZY51R6JWK3aUVKCJlF5P3+rshlMfg5LPELhLyZa7MYPsCtfiMVh9HBIxFWwwlIR47Ni2jLebDgzYVAQicw7Nh9iZCsMcv+nHxRfU0piohq8haj0dZpT59gJXuBj1HG4uJRFQzJhKgsy49Rh4QZCPO6DLiDLHJ2NqtO8zGDmk1w7WhxaH/zm/hwdII9pBHuLwoZL2fHqNSP20fgFOm+bwIZW2ltD1jHCmTrbFTcmPfV446+xJbkyEtaSiAmsPfqvZa7TufHAmqB2v+gGKiThmi336eIFJJrg95NM4EdWJgK1WumKKRUO0LZIfTnEk8X7//v4GsgEABP0J/hPyJ/RP2J/wPxF/Iv9E/Yn+E/Mn9k/cn/g/CX8S/yT9Sf6T8if1T9qf9D8ZfzL/ZP3J/pPzJ/dP3p/8PwV/Cv8U/Sn+U/Kn9E/Zn/I/FX8q/1T9qf5T86f2T92f+j8Nfxr/NP1p/tPyp/VP25/2Px1/Ov90/en+0/On90/fn/4/A38G/wz9Gf4z8mf0z9if8T8Tfyb/TP2Z/jPzZ/bP3J/5Pwt/Fv8s/Vn+s/Jn9c/an/U/G382/2z92f6z82f3z96f/T8Hfw7/HP3578/xn5M/p3/O/pz/ufhz+efqz/Wfmz+3f+7+3P95+PP45+nP85+XP69/3v68//n48/nn68/3n58/AOx//d/uqXhu0gMZWljxMnjQ1u86cu65Wo30buLrRtWBzcbPV4OUv19q5mrUJKAItYFvzVV+NJCTEnfS7RrtM/ni+XTvnvjMGaJQ7Q8FmPcFoPsjxkGi7MLeKe4XSKr9F+VAYFcIssHVIxx7m1nVRofRiY7fwzGpr65dXlu1eNG8dJuGDkiQPG0f41SpYQRgZEQNKX3LVkfTNmfXupQ7+WHPCp2mJcG4QX/ofm3EC6J5c4mcXKWX7tDfnIKKvGhZaLw7uHCuJ65BP908e7M+11YM3/wozn1XveRtKPKq8WlOU7xRs/265X0tL5TbZGQQ5p72FKaC4w6u+FUKSDtRGF1GwitmvXkP0pdd2LDgz4TnqIaSNHdac+BxNqw9qQ2NNNmC0nRHkjk/d5cZPx1x+gDPvaZopWSeOSUVZekJeWZptpXwDAkSK+E7nj2K+qDZ+kkFJh0CqnK5Vlxc2r4tgEY9ZchlLeopjqwk92OGVyhzrBXAD3f5rp8TPyJ/qfnpbIt3BSP6Fxw1Bdmex5alDBLLfyns8/FiaxtjH0tIs7DFe/owiYo8FW1OgEPnpSdgpIffW5g8ogOg+MsfkmehwTW8uKJSmGEf0dfUZ0HLpkfKqPfS1Mlpk6vveUgbYsAnX6Zkj0HcGeatfrBz7w0HmjwIRzTjuEio3tttwwSNgaWP98OBIEIVPjvEAkDZBi3GH8GJsHnqWzOSCrGdD1CrCztUt371aPhDW1z8AiTiJzLRLvvi1XBqju6Ehwkuf6+AUyNGW+ksb9eTVT8WLLY2Fnwlpua2zGr+eTMivGiaOwTmhhKQ8IRK8/8Anf7HbFMw536m8alztFO5MyJKhTD/Tc/ytuzFZ5x0Uzf8tEYFqDUikBkX3F3hyIaxoMEXHbeBN41EYau7LS0kZBQtpYj2T6S7KGFsm0mwCj7L3iEP6Zxt9LiqzQVcb8kmrZ/GpFnFG28OHCAhwRz+5YdT+HuMjqxwyxPKjjgq944j3a8IgZatBNO8r7JnMQewacUTV1jgnIPNhYe5wvIjoxBd09Eu2ueHvIB8vuicFsxFFOlTF034P46ogtrDBq5QFoQ34GR4qOV6nskAxaIECYJr9TzuPUGT/BwCYI0vdoB5UwptlCkw6WkMOnkl3Z+CHS5VIbrRYQYKAS4ljBUnLDAP94zCpYsvEi+uzdZMTNYrBQmh8+SH08TS0EjgKgtpFNrIOzsuu3PQEtz2YmxfbJ8JcA1FtYt1i7e0l4Obo3mlm/+88zxxCcLYl4ek+uQ7CdYVo0WP0w82sSk1FowrzFiGmGxPqdHc0v03a9ZuzEit8Mr6uNIBAaYzqsDACpQohhyvrXaY5bOmBF+CjbuQ35oADIHr9EYkxCzxtVYGfGS3rNAcnq9L0nipl50d3i/l6UhOCTyqSB6oYxjZ2FSOq3WpQzaKaIJa+NFsknRr6Afw0h4qY37kJHmMcT15A+PjJCKqLdqjyXrvkTG3+cZgo8JLRHeNS1rYCtCAtJseg73Z7MIV8IrEHmNyCprB4l3YzIuhWT3TsFWK9Vpm+/D54Q54luQNIN7If5QTEx//lbvF+TErkzPk85CN11uBSjtrM2RHnB3uvweeVnOJMnjJUdvxvTg4949AUTPLPZmyk9aZWKdkt6Wbz6TMVBLyfDv9gGA0R4uxnWW7yLyCLTTNo9wAACz/0/XFyF707sEr4HVmEcaycgRh3wfC3GmeIlFytz5noT4L+RknAdL8F3mmY89++e8KYY2G6QrokwlwKOlJvPcF3H/T3fA9adpfLON4DzkQHtZ4Lb+j8yv8jlzORQ1GmuJBNXw032w13kHaSDH8DV1zvyM+KUk9o5e6ykPVGZfB80yNPGm/bDRsND+kxY4vu4muc4LHG7QR3bfpqRfhvrsRalc67NZOnT8ZD6zRlkGn1SNoo2dHy2nVhwnyzMMIhxXh9VXm0RnJvyZ1QUVsiUnlzXVV98tj9uP9x7sEBdlHxgMEEfu2NDrWQ1NHw2HZai3irL/3UWfKZHKrJ99cUsf+OGSElq4rnfbxCVoSDorYpFrUyKjMicSv5HKIYSlpKIUsWte3JEfxtnZV5/YulV3m5FohvFJdPLk0p7nKXoqPOwKnGuKJHFnbXBZq6Ub9aPmaQdB7PxZU1luFm1GgJlruXpE7geZh1/uj3FCj5YK4ILi3S5tfW1JuZkXPHKPQJGT8BwZ53Pa1zYBQjwkTucPgecvFYcF79r9YEvLRvj7jM3ZJ7aAB9jAQTBBBQDHT0yyotNxeRtxCIQ8gwal9INnooGTvBWDX53VaHsBF85rQD6dZ2+IV1WSh9RDtT1nMzknZMIFGzv5grtLdKGY+XNaiVa3mZzqieGEHol4qgaFwM7AvZ87s7ppQWa4UFlLQFQ5csMoplZAZ4ofks8i6XSsbR5Iachd9W+fmA16tf5qMHqzM1hEVxwPpnQFtG4QdIPaBPMGxiK564qeFHPjLqxFGvHU7zOfG1HFkZ7ikmfnijl0bqmSrItmquCQfV8Muv/AprgaKDL140OI9Zmp09CfuS3AMAIq5cqRtJxidkz/Q50OZavhhd8XWKKTYI67A+baWXyI5a1bPtJ5Ow/VvBwKPXf3+vA+C+7QgSKR4bOkFMRlECCSo32F6tCIj5DRAOq+SZzapZmvmnvF5CS3S6WRCayfFK5wfyKd9AnSjN2m7AFcgtya90LFN/vVpdJmkphgwjkDfcDcXJfS8dWn3feRs3mGyAHjg+Ib7ncwy6ayPSxvYnmAlW9sKxqWxAr5lkBJTP2z/FliJnEaZb4mhJ2LWXrrNudolzdFBNa+1rpnBFx4G9beeFkqTgWJg0pDX/ptSQoJvHy/gxQBWkXsTwqNkB6x5xwCdPoER9akTvVCYjDUCeYJIT54HlVNCxq3dMoA12rZwsbuGEW36xFUGK4KLDL6ym7UUxHEA7EyehQD9Bz7DY9MzpXAUD6q4nsFfyzJlvjGQYsIT0/grH/QpyRHzAOxcDDlKDMwNoNuIu75/aZm+38ND7ez3seFUiOBBw8wLdZIf8CxZ/Tgni6xbUrKAwCjJBJNxUk/+Ud6j4pKfrnlyprFJ4jJfOBjx5oCYc4siwA/AvEaRu7uVlR3qkaJa5NMydvmBtwAgy2kh3S2xPoUs5UwI2su77E1Y2nYWDa3MWrEyGyrq+HGErLcDseRMdWk95D3YMD+nUsmnwBTcg1fvGRZw1446RaRsIQxq+RNp88pHmU67F6MEI2Ex0tmBz/95R25J7OYjnxUGITN7TQIXBGOg6cqdOmCjpWRbofMSAtDDvemg9GyHlm8vWulje4rpTKR5QHKS3r2Bsz7/DK7OEDDowHjeEqk/lfO5GZZEW1Lm+9/wPKbJEaeAtdHEsQtEFS8xK911ZOzl1JaHBLiWyk/4gLPMpNIpt5vaZBk+pLBx4yY845Z3595y+tdNsRnUj4wei0iwpeJQv+vAEEU4S3BoVVdUTcnCAVnsRbUtFOlK/SPjFnEklv0zJ/X90PK7/CtvYChic03a5Uw1MvQsSWXA7piVkX4xuEfS0MVF2rr5x2tYTeYiy08n2znYkze6kvpRgekrmk/peW3Dj/m20UlVjLiLL/LSZQ4r7rOLlYnpXzTq7AdSYXsk/y2sLIywzQKNGqMc5BX+t1kW5IGYmYpW+EiGeM25tfXrSCheeiAQk+7ljVYnUfcfPxUtXgFs6sFKePr3Sn13vyhFNDcum70hJaA+gtcQDq7UbThMLumuKMH6FGZ84uTkJETcN54JXJ/ZOBrRyVtwtDMP5nJAlm+2F5JVr5OCW+hW5I/TffQ/yZXp0ELyTyp2wJPzcYObMSwblFpJ
*/