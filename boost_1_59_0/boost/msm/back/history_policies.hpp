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
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
*/