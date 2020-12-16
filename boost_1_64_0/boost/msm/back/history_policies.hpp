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
jvHVeaNsWuSomYt4EsvwE77dHk/XrFmTc1x0EhYleMLkwdBLNl3XcIb+gU2v1SeuPa1PXfQOBN6t8+/ABhctQbbT8mhw0+x4UG60aci5W2Z2Qw+MtekmATk6CF9p8bTarDHDj5jryjZMzPPQQsI647L66+1ujfcoy9J27qNLq3LHv/SjBqNszqxhH/PQQibXp3dwaGorU4Z6uXix5lvQ45OL0mZOgUnmOiE+iwgzWhZXGVq2p+a6uia3aL2Z5fp64GpzHffT12PX6OtSMOZsw9hmRlmm2dN8zKJhlcL2wZcMzVikqS/yH1h0mfqlUULXee9Ti45FGj9rsK5jjezXaXscZtGwOGHRwiMtmqzpLJoYbmgElDZuNTofa2iOleo4cq3hsV6NVK5PlzWSiQ3UtwbjVLimzqlafXhrqMBPDa1eDRV20dWq0Oo75qZTQxnd5tw06YMm3lu0/mqfkgvjr32Kx7no2ba0PG3pallj12iTDCaprF+fN1n3oxWnvm7R/n68m845JfZp6LmlXjqTh67P39G7RfdW8mZ/cDsXzl3J23NpdY2HFZlnmMLfcdNQBU9MdBlf8tHlosU6vzOyZiFjFK3t+zpNZ9nGJoQQndqHDe0U5zkK7fuTDE2Jv1PbXsjQtHKsMUumXxUq2QvXutm6jzY/evjRzfNncUAuIwSnIlmxxpFrvl8Mdg5d45Z6carMIdQSUUwOXObC+Z4vLPnpnZbPGJ/24TAdyZb9HMCJ/WBgXfBvkiPfOriMc4Bg9v5NTvXju7AH4xN+OrnVjJeP+uj4nm9Ac4ZUD29kktUy8eE4OZCcWc88VOtg0u3oycpn5VYHI89t2IfBR7T/tNk0qTpDK7poqM2+r92mIQ5omiebxtQQhDpFMzyF4i4MByYm/osLBivaXB4JPrwvwNt7u+Hq1i665Nqmpz10OHetn3MeOqyZ2stDQzHG1jd7aZyBdpkcGn5A0+c0dcvtdJMzYiU3raenKZ1iw1nXWG46z6OY84H8g16avN/Yb/AxH709cYpV/9elyz7MuXDucS8Gp0qbM7v8xnp0dx+xJ30Y/NP0ESnXoXv4qPox3b1dpg/xfD16rQ8dc/7gxRDfu06JR1f24ociu7eD++MWcHRp573SS37syh77vLceXXZi+qj+pR7G5P/qX+vSZScmVr3qwkgbarLpxR0c35m3YH7fQa37efLCjj66dB9z/04+Ou5hrS+CPjpuYGJbZNd6dOIp+bXdqlPFBge3cPbMiJ+Pgpvu5+Nem+7nI/e6Qz/+oCk81sSjASiWfNodx3DNGiL8to0zjzAdn14p9Dn9O3UxpjfLTtI6RrS0ZmTaWZXqYd5RvU6oDHLohAcTDyuvDDbX+24ya6DyjQ6Np7ibWlk6GVrFGY+FQtJDK/xb0yAlXLSSh5bGM/R4Nw02NI46Bf/0eL+waMuZO/+0fdt9dsVrvTJ3PeZe1r3d6YQtt2rR0PqKLc4mbLlVP1R9145iTMz9yHUdKZh4XXHTagZm9Vn4WNO70/ZZ1af6unwiLyu1nFnVAkR0az1+aTC4V1bnlluceSA49GGPl+ty7iH8WvuGOWxZX6eObLP2Ywt/tWnSLkx/wQGaxp4hf/HD0V9WjYNt2tdLDr4miZT2gd3M9ZSMO8lsZ6o7TqFt5hv5ldNnZ1u79ZxjcL2617hFe6aFsr72nPFqZ4zgCnW/x33sZ1EK5P16GOs9DWo1g+E1lSR7qQo0+aAmxnNwlX5xTU1TLVy1f9wB0yycOKk/3JTpdn+BfnEHNE0Gp/eGtnJwphzWMcSm1ertjLDeDYm1GFniKB1tTVNDBzlSCDE9a72V3wL2wGnTzTP0XtyUA5qmOX0=
*/