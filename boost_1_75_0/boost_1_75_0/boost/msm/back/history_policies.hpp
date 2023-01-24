// Copyright 2008 Christophe Henry
// henry UNDERSCORE christophe AT hotmail DOT com
// This is an extended version of the state machine available in the boost::mpl library
// Distributed under the same license as the original.
// Copyright for the original version:
// Copyright 2005 David Abrahams and Aleksey Gurtovoy. Distributed
// under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_MSM_BACK_HISTORY_POLICIES_H
#define BOOST_MSM_BACK_HISTORY_POLICIES_H

#include <boost/mpl/contains.hpp>

namespace boost { namespace msm { namespace back
{

// policy classes

// Default: no history used
template <int NumberOfRegions>
class NoHistoryImpl
{
public:
    NoHistoryImpl(){}
    ~NoHistoryImpl(){}
    void set_initial_states(int* const initial_states)
    {
        for (int i=0;i<NumberOfRegions;++i)
            m_initialStates[i] = initial_states[i];
    }
    void history_exit(int* const )
    {
        // ignore
    }
    // returns the state where the state machine should be at start
    template <class Event>
    const int* history_entry(Event const& )
    {
        // always come back to the original state
        return m_initialStates;
    }
    NoHistoryImpl<NumberOfRegions>& operator=(NoHistoryImpl<NumberOfRegions> const& rhs)
    {
         for (int i=0; i<NumberOfRegions;++i)
         {
             m_initialStates[i] = rhs.m_initialStates[i];
         }
         return *this;
    }
    // this policy deletes all waiting deferred events
    template <class Event>
    bool process_deferred_events(Event const&)const
    {
        return false;
    }
    template<class Archive>
    void serialize(Archive & ar, const unsigned int)
    {
        ar & m_initialStates;
    }
private:
    int m_initialStates[NumberOfRegions];
};

// not UML standard. Always activates history, no matter which event generated the transition
template <int NumberOfRegions>
class AlwaysHistoryImpl
{
public:
    AlwaysHistoryImpl(){}
    ~AlwaysHistoryImpl(){}
    void set_initial_states(int* const initial_states)
    {
        for (int i=0;i<NumberOfRegions;++i)
            m_initialStates[i] = initial_states[i];
    }
    void history_exit(int* const current_states)
    {
        for (int i=0;i<NumberOfRegions;++i)
            m_initialStates[i] = current_states[i];
    }
    // returns the state where the state machine should be at start
    template <class Event>
    const int* history_entry(Event const& )
    {
        // always load back the last active state
        return m_initialStates;
    }
    AlwaysHistoryImpl<NumberOfRegions>& operator=(AlwaysHistoryImpl<NumberOfRegions> const& rhs)
    {
         for (int i=0; i<NumberOfRegions;++i)
         {
             m_initialStates[i] = rhs.m_initialStates[i];
         }
         return *this;
    }
    // the history policy keeps all deferred events until next reentry
    template <class Event>
    bool process_deferred_events(Event const&)const
    {
        return true;
    }

    template<class Archive>
    void serialize(Archive & ar, const unsigned int)
    {
        ar & m_initialStates;
    }
private:
    int m_initialStates[NumberOfRegions];
};

// UML Shallow history. For deep history, just use this policy for all the contained state machines
template <class Events,int NumberOfRegions>
class ShallowHistoryImpl
{
public:
    ShallowHistoryImpl(){}
    ~ShallowHistoryImpl(){}
    void set_initial_states(int* const initial_states)
    {
        for (int i=0;i<NumberOfRegions;++i)
        {
            m_currentStates[i] = initial_states[i];
            m_initialStates[i] = initial_states[i];
        }
    }
    void history_exit(int* const current_states)
    {
        for (int i=0;i<NumberOfRegions;++i)
            m_currentStates[i] = current_states[i];
    }
    // returns the state where the state machine should be at start
    template <class Event>
    const int* history_entry(Event const&)
    {
        if ( ::boost::mpl::contains<Events,Event>::value)
        {
            return m_currentStates;
        }
        // not one of our events, no history
        return m_initialStates;
    }
    ShallowHistoryImpl<Events,NumberOfRegions>& operator=(ShallowHistoryImpl<Events,NumberOfRegions> const& rhs)
    {
         for (int i=0; i<NumberOfRegions;++i)
         {
             m_initialStates[i] = rhs.m_initialStates[i];
             m_currentStates[i] = rhs.m_currentStates[i];
         }
         return *this;
    }
    // the history policy keeps deferred events until next reentry if coming from our history event
    template <class Event>
    bool process_deferred_events(Event const&)const
    {
        return ::boost::mpl::contains<Events,Event>::value;
    }
    template<class Archive>
    void serialize(Archive & ar, const unsigned int)
    {
        ar & m_initialStates;
        ar & m_currentStates;
    }
private:
    int m_initialStates[NumberOfRegions];
    int m_currentStates[NumberOfRegions];
};

struct NoHistory
{
    typedef int history_policy;
    template <int NumberOfRegions>
    struct apply
    {
        typedef NoHistoryImpl<NumberOfRegions> type;
    };
};
struct AlwaysHistory
{
    typedef int history_policy;
    template <int NumberOfRegions>
    struct apply
    {
        typedef AlwaysHistoryImpl<NumberOfRegions> type;
    };
};
template <class Events>
struct ShallowHistory
{
    typedef int history_policy;
    template <int NumberOfRegions>
    struct apply
    {
        typedef ShallowHistoryImpl<Events,NumberOfRegions> type;
    };
};
} } }//boost::msm::back
#endif //BOOST_MSM_BACK_HISTORY_POLICIES_H

/* history_policies.hpp
OX4YYjFxwkI6lCJDdBTWAUN8QtDyDayQKiP/bsYQ3D3LPjeU8QQTZI+yHqWeNTgWcc7I45yxWMLDuwE5wx6UM/I4Z5R4cQYlHIh9trWKM0o8OIPi5wbQTrt4DBAagAFCm9NUMfTJjE9K1XxCG4WQ9GkDk8wn1cQnWewUwvqYnKXrkL6QIWURIr20gZGuliELzSW+c0i/VSEpQjkRcERAxsr3x1hRC/QarPUss9UA6G7OyJRkW4eR6UVHbDeq98mq2ay+ymPdLdBDHrzIGh5adQNUWuDc2PGOb5EbBwA3LvTkxvkKN97ezoMbZSoInRvnB+dGTpcqz30wbgS2AW7c/CdyI/CVLzdeeFrmxuqn+X52h6kA1svP7GWklt2ckVqLjcINFZLbwjMHkcK3fOP71JEy31KGBMyrtVdRVn1K3bH1Zuk1QRVTWZmvYgJFuzjJQzGdYWyuTU89bXB0VZTTVg9R2CogC4ZfiXLa3bJO5WSQAljB81rtGisz2xK1UgqifLR1K5/JKh45wuagKyIuQ/mcqVrOlQ8b+Z6r9SA8taR8lsrKp2bqOC/lY2xL5H6Pl/JZGIDcDTMoYU1ICuigKfXA5NnBFdBuH5Kv4Apo7x869a5xjyrrQP6c+GvHy8R/arxvTdvpRynERvfRcJmmM7W012qAhXDFJC0zxQD+Mq6K8uBHBf6gQZFIX+AdYqOrk1WTu9iPalqi8AI7
*/