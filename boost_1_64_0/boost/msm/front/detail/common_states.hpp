// Copyright 2008 Christophe Henry
// henry UNDERSCORE christophe AT hotmail DOT com
// This is an extended version of the state machine available in the boost::mpl library
// Distributed under the same license as the original.
// Copyright for the original version:
// Copyright 2005 David Abrahams and Aleksey Gurtovoy. Distributed
// under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_MSM_FRONT_DETAILS_COMMON_STATES_H
#define BOOST_MSM_FRONT_DETAILS_COMMON_STATES_H

#include <boost/mpl/int.hpp>

#include <boost/mpl/vector.hpp>
#include <boost/fusion/container/map.hpp>
#include <boost/fusion/include/at_key.hpp>
#include <boost/type_traits/add_const.hpp>

namespace boost { namespace msm { namespace front {namespace detail
{
template <class Attributes= ::boost::fusion::map<> >
struct inherit_attributes
{
    inherit_attributes():m_attributes(){}
    inherit_attributes(Attributes const& the_attributes):m_attributes(the_attributes){}
    // on the fly attribute creation capability
    typedef Attributes      attributes_type;
    template <class Index>
    typename ::boost::fusion::result_of::at_key<attributes_type, 
                                                Index>::type
    get_attribute(Index const&) 
    {
        return ::boost::fusion::at_key<Index>(m_attributes);
    }
    
    template <class Index>
    typename ::boost::add_const<
        typename ::boost::fusion::result_of::at_key<attributes_type,
                                                    Index>::type>::type
    get_attribute(Index const&)const 
    {
        return const_cast< 
            typename ::boost::add_const< 
                typename ::boost::fusion::result_of::at_key< attributes_type,
                                                             Index >::type>::type>
                                (::boost::fusion::at_key<Index>(m_attributes));
    }

private:
    // attributes
    Attributes m_attributes;
};

// the interface for all states. Defines entry and exit functions. Overwrite to implement for any state needing it.
template<class USERBASE,class Attributes= ::boost::fusion::map<> >
struct state_base : public inherit_attributes<Attributes>, USERBASE
{
    typedef USERBASE        user_state_base;
    typedef Attributes      attributes_type;

    // empty implementation for the states not wishing to define an entry condition
    // will not be called polymorphic way
    template <class Event,class FSM>
    void on_entry(Event const& ,FSM&){}
    template <class Event,class FSM>
    void on_exit(Event const&,FSM& ){}
    // default (empty) transition table;
    typedef ::boost::mpl::vector0<>  internal_transition_table;
    typedef ::boost::mpl::vector0<>  transition_table;
};

}}}}

#endif //BOOST_MSM_FRONT_DETAILS_COMMON_STATES_H


/* common_states.hpp
wt+4K1mpO3L3ri6j3DRLfZbZktChlIqzrvcLOfRtzm3F5753T/ssdvz1ef/K5ppi2v0+njqgi2o763Kv4o7mu73ltpkD8HxbMTYfnXYfTNoNGWwFhS6NAgY7PK2mLKFM0hwORy3EGbf757GkNXKu2FMc6bH1ZKAs0F5nGseb1Zn6HDUN29WwbsWY4G7t0QM1YztUc3ZJ+E0elMet9U+JtCf30JzrZLkvORNj0KR5TS4aZ3+cNnBbcW6cNp6/IV56H4Xjg3wX4Ygn+OS4/mDIw+f3eA53D8EE9/uW5O/ND21dDLDPWv7WynqYZ3u/PeW6CfNMAs/VdxRDcQhbaA/y6FN9XO4PAaef6ZN9jOLUW5braHOK1W9YbmoGj8ohjzGmnxxBX6bkpAPNzlpW2/INKcX5756MQrnrDqljEvszfAZLG3KfkKxTt38PtsI5KYM+sr554fdlnaOuUsXE85s8zONUfjeVXOd3YiNkkF9ui7uCcZuZ3YlCeppNvIX/eOYadSOzB+ZbnVVahbLb6KG3URZr6x3UxxOi3Nqy6Hs2o4zLrPQZPlFxnp1WepKSkwKMny3hOwvqcW7Qd2dhoAuaM8oyQD+t5dKeYB/wUzQnbYpbjON7asj9b3bFpvqdshfgVy1sRlksfdIiHcItapbHZQOKNNQVq8ZnfitLsdExehm+SMXrcRppflqMdYuTtnoH8Bs//b+xTWP5sq/wGSGP9VVTGuvQQ8mN56V48YTvdt68h+TMwMTjzrYnC+Yjb/Rkp4L8sZ9Pc4PuaXNumZm6ZtAOMG/00mLbANZQNqQsPgdY9OPo56V3pDmkBf3OOyTj/EyibBHnO2Ocfpdn7z0RzhYTmOSeY8a9WGy2XQd23USUMdXGel96U8jgEKjsY7lN5fJw1nSQ31zWrshBJ2LpDN5bGW3EGFQt0pdG40T1euPApmP5GA2MOfaTaEYadH30y/fUnHzvPtlWchh2mPOrMIKxRIdxKjZXrCsORl4P5aQYZejx2UrFKmOvg35UsXGDD76/NytevR2Ivk6z0vjjeVEu12d/kWKUEYh4U82yISj0fSPOYe4Jn3ScgyEl87wbZTEPXUafoTj4W9lWzWH6LbEu8xbNsAEnfHVKV62/FfbFI5ScG6u8v0jHJ+0VLrMoF6+v+ls1G6uvUZTT9VV6m+Zy6yvK6vpafLvmwvpK3qGZsL624gzqC+n6kuPYym6wxcfcSHPSigZX+LLm8PKR1MuAg4Us94d9RTPODwBmI2Bg+RKDvjrGUB7d/k+kPflqnBvnEXtR8jhMm4TO5bF92lrU5vEkfYDj3AWM08drcpVygHknOOq2BICxy8V3t/nm1NGxOUc7gNpn+WzP4tcFE5wt2/qmlDnnjPs9/GDfkgze/1nGuePvSLlxwokzSz8QMuskS/C7Dx8wsgVafbmpuyMLsk2W0YEaX7Z1/stbGQ5TiPn+xceyhfnqtPUIpg/gOt++REw+3hnAY8fuTy7nOFJ6+/7cGFpHu/ypZIx5NEaYKQZMOqQS7nZNA+H1Rc0gIPSzHmNcQFab0b6kHCalDQTt62eOMVMHkg2XjEZ111Lh701+4RinS27HGXwk2yw3Fxi0UV6/HH9fblPQ3XO8FY7j/xWYYeqXKZgdyfhlCmbx15KJl+nmbxSj4ir+VjB+mSG/e2D8eyTrI/fdnUDIXAaIQZwL97nucCBTwu18y+do0kDL5PLc+O+0XIYDXfK5QbsP6hR8ej4DZSLRKYzbYPRREJnuEThxFESeefi9lJt6wB5B2BATkkEcnJailLusm4c6zUZEWdZplOusjznkX3KudNx+J6R7B4xNj0HNageVFc/3NGMyN+wHdyYkf4g=
*/