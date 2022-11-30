// Copyright 2008 Christophe Henry
// henry UNDERSCORE christophe AT hotmail DOT com
// This is an extended version of the state machine available in the boost::mpl library
// Distributed under the same license as the original.
// Copyright for the original version:
// Copyright 2005 David Abrahams and Aleksey Gurtovoy. Distributed
// under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_MSM_BACK_FAVOR_COMPILE_TIME_H
#define BOOST_MSM_BACK_FAVOR_COMPILE_TIME_H

#include <utility>
#include <deque>

#include <boost/mpl/filter_view.hpp>
#include <boost/mpl/for_each.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/any.hpp>

#include <boost/msm/common.hpp>
#include <boost/msm/back/metafunctions.hpp>
#include <boost/msm/back/common_types.hpp>
#include <boost/msm/back/dispatch_table.hpp>

namespace boost { namespace msm { namespace back
{

template <class Fsm>
struct process_any_event_helper
{
    process_any_event_helper(msm::back::HandledEnum& res_,Fsm* self_,::boost::any any_event_):
    res(res_),self(self_),any_event(any_event_),finished(false){}
    template <class Event>
    void operator()(boost::msm::wrap<Event> const&)
    {
        if ( ! finished && ::boost::any_cast<Event>(&any_event)!=0)
        {
            finished = true;
            res = self->process_event_internal(::boost::any_cast<Event>(any_event));
        }
    }
private:
    msm::back::HandledEnum&     res;
    Fsm*                        self;
    ::boost::any                any_event;
    bool                        finished;
};

#define BOOST_MSM_BACK_GENERATE_PROCESS_EVENT(fsmname)                                              \
    namespace boost { namespace msm { namespace back{                                               \
    template<>                                                                                      \
    ::boost::msm::back::HandledEnum fsmname::process_any_event( ::boost::any const& any_event)      \
    {                                                                                               \
        typedef ::boost::msm::back::recursive_get_transition_table<fsmname>::type stt;              \
        typedef ::boost::msm::back::generate_event_set<stt>::type stt_events;                       \
        typedef ::boost::msm::back::recursive_get_internal_transition_table<fsmname, ::boost::mpl::true_ >::type istt;    \
        typedef ::boost::msm::back::generate_event_set<create_real_stt<fsmname,istt>::type >::type istt_events;  \
        typedef ::boost::msm::back::set_insert_range<stt_events,istt_events>::type all_events;      \
        ::boost::msm::back::HandledEnum res= ::boost::msm::back::HANDLED_FALSE;                     \
        ::boost::mpl::for_each<all_events, ::boost::msm::wrap< ::boost::mpl::placeholders::_1> >    \
        (::boost::msm::back::process_any_event_helper<fsmname>(res,this,any_event));                \
        return res;                                                                                 \
    }                                                                                               \
    }}}

struct favor_compile_time
{
    typedef int compile_policy;
    typedef ::boost::mpl::false_ add_forwarding_rows;
};

// Generates a singleton runtime lookup table that maps current state
// to a function that makes the SM take its transition on the given
// Event type.
template <class Fsm,class Stt, class Event>
struct dispatch_table < Fsm, Stt, Event, ::boost::msm::back::favor_compile_time>
{
 private:
    // This is a table of these function pointers.
    typedef HandledEnum (*cell)(Fsm&, int,int,Event const&);
    typedef bool (*guard)(Fsm&, Event const&);

    // Compute the maximum state value in the sm so we know how big
    // to make the table
    typedef typename generate_state_set<Stt>::type state_list;
    BOOST_STATIC_CONSTANT(int, max_state = ( ::boost::mpl::size<state_list>::value));

    struct chain_row
    {
        HandledEnum operator()(Fsm& fsm, int region,int state,Event const& evt) const
        {
            HandledEnum res = HANDLED_FALSE;
            typename std::deque<cell>::const_iterator it = one_state.begin();
            while (it != one_state.end() && (res != HANDLED_TRUE && res != HANDLED_DEFERRED ))
            {
                HandledEnum handled = (*it)(fsm,region,state,evt);
                // reject is considered as erasing an error (HANDLED_FALSE)
                if ((HANDLED_FALSE==handled) && (HANDLED_GUARD_REJECT==res) )
                    res = HANDLED_GUARD_REJECT;
                else
                    res = handled;
                ++it;
            }
            return res;
        }
        std::deque<cell> one_state;
    };
    template <class TransitionState>
    static HandledEnum call_submachine(Fsm& fsm, int , int , Event const& evt)
    {
        return (fsm.template get_state<TransitionState&>()).process_any_event( ::boost::any(evt));
    }
    // A function object for use with mpl::for_each that stuffs
    // transitions into cells.
    struct init_cell
    {
        init_cell(dispatch_table* self_)
          : self(self_)
        {}
        // version for transition event not base of our event
        template <class Transition>
        typename ::boost::disable_if<
            typename ::boost::is_same<typename Transition::current_state_type,Fsm>::type
        ,void>::type
        init_event_base_case(Transition const&, ::boost::mpl::true_ const &) const
        {
            typedef typename create_stt<Fsm>::type stt;
            BOOST_STATIC_CONSTANT(int, state_id =
                (get_state_id<stt,typename Transition::current_state_type>::value));
            self->entries[state_id+1].one_state.push_front(reinterpret_cast<cell>(&Transition::execute));
        }
        template <class Transition>
        typename ::boost::enable_if<
            typename ::boost::is_same<typename Transition::current_state_type,Fsm>::type
        ,void>::type
        init_event_base_case(Transition const&, ::boost::mpl::true_ const &) const
        {
            self->entries[0].one_state.push_front(reinterpret_cast<cell>(&Transition::execute));
        }

        // version for transition event base of our event
        template <class Transition>
        typename ::boost::disable_if<
            typename ::boost::is_same<typename Transition::current_state_type,Fsm>::type
        ,void>::type
        init_event_base_case(Transition const&, ::boost::mpl::false_ const &) const
        {
            typedef typename create_stt<Fsm>::type stt;
            BOOST_STATIC_CONSTANT(int, state_id =
                (get_state_id<stt,typename Transition::current_state_type>::value));
            self->entries[state_id+1].one_state.push_front(&Transition::execute);
        }
        template <class Transition>
        typename ::boost::enable_if<
            typename ::boost::is_same<typename Transition::current_state_type,Fsm>::type
        ,void>::type
        init_event_base_case(Transition const&, ::boost::mpl::false_ const &) const
        {
            self->entries[0].one_state.push_front(&Transition::execute);
        }
        // Cell initializer function object, used with mpl::for_each
        template <class Transition>
        typename ::boost::enable_if<typename has_not_real_row_tag<Transition>::type,void >::type
            operator()(Transition const&,boost::msm::back::dummy<0> = 0) const
        {
            // version for not real rows. No problem because irrelevant for process_event
        }
        template <class Transition>
        typename ::boost::disable_if<typename has_not_real_row_tag<Transition>::type,void >::type
        operator()(Transition const& tr,boost::msm::back::dummy<1> = 0) const
        {
            //only if the transition event is a base of our event is the reinterpret_case safe
            init_event_base_case(tr,
                ::boost::mpl::bool_<
                    ::boost::is_base_of<typename Transition::transition_event,Event>::type::value>() );
        }

        dispatch_table* self;
    };

    // Cell default-initializer function object, used with mpl::for_each
    // initializes with call_no_transition, defer_transition or default_eventless_transition
    // variant for non-anonymous transitions
    template <class EventType,class Enable=void>
    struct default_init_cell
    {
        default_init_cell(dispatch_table* self_,chain_row* tofill_entries_)
            : self(self_),tofill_entries(tofill_entries_)
        {}
        template <bool deferred,bool composite, int some_dummy=0>
        struct helper
        {};
        template <int some_dummy> struct helper<true,false,some_dummy>
        {
            template <class State>
            static void execute(boost::msm::wrap<State> const&,chain_row* tofill)
            {
                typedef typename create_stt<Fsm>::type stt;
                BOOST_STATIC_CONSTANT(int, state_id = (get_state_id<stt,State>::value));
                cell call_no_transition = &Fsm::defer_transition;
                tofill[state_id+1].one_state.push_back(call_no_transition);
            }
        };
        template <int some_dummy> struct helper<true,true,some_dummy>
        {
            template <class State>
            static void execute(boost::msm::wrap<State> const&,chain_row* tofill)
            {
                typedef typename create_stt<Fsm>::type stt;
                BOOST_STATIC_CONSTANT(int, state_id = (get_state_id<stt,State>::value));
                cell call_no_transition = &Fsm::defer_transition;
                tofill[state_id+1].one_state.push_back(call_no_transition);
            }
        };
        template <int some_dummy> struct helper<false,true,some_dummy>
        {
            template <class State>
            static
            typename ::boost::enable_if<
                typename ::boost::is_same<State,Fsm>::type
            ,void>::type
            execute(boost::msm::wrap<State> const&,chain_row* tofill,boost::msm::back::dummy<0> = 0)
            {
                // for internal tables
                cell call_no_transition_internal = &Fsm::call_no_transition;
                tofill[0].one_state.push_front(call_no_transition_internal);
            }
            template <class State>
            static
            typename ::boost::disable_if<
                typename ::boost::is_same<State,Fsm>::type
            ,void>::type
            execute(boost::msm::wrap<State> const&,chain_row* tofill,boost::msm::back::dummy<1> = 0)
            {
                typedef typename create_stt<Fsm>::type stt;
                BOOST_STATIC_CONSTANT(int, state_id = (get_state_id<stt,State>::value));
                cell call_no_transition = &call_submachine< State >;
                tofill[state_id+1].one_state.push_front(call_no_transition);
            }
        };
        template <int some_dummy> struct helper<false,false,some_dummy>
        {
            template <class State>
            static void execute(boost::msm::wrap<State> const&,chain_row* tofill)
            {
                typedef typename create_stt<Fsm>::type stt;
                BOOST_STATIC_CONSTANT(int, state_id = (get_state_id<stt,State>::value));
                cell call_no_transition = &Fsm::call_no_transition;
                tofill[state_id+1].one_state.push_back(call_no_transition);
            }
        };
        template <class State>
        void operator()(boost::msm::wrap<State> const& s)
        {
            helper<has_state_delayed_event<State,Event>::type::value,
                   is_composite_state<State>::type::value>::execute(s,tofill_entries);
        }
        dispatch_table* self;
        chain_row* tofill_entries;
    };

    // variant for anonymous transitions
    template <class EventType>
    struct default_init_cell<EventType,
                             typename ::boost::enable_if<
                                typename is_completion_event<EventType>::type>::type>
    {
        default_init_cell(dispatch_table* self_,chain_row* tofill_entries_)
            : self(self_),tofill_entries(tofill_entries_)
        {}

        // this event is a compound one (not a real one, just one for use in event-less transitions)
        // Note this event cannot be used as deferred!
        template <class State>
        void operator()(boost::msm::wrap<State> const&)
        {
            typedef typename create_stt<Fsm>::type stt;
            BOOST_STATIC_CONSTANT(int, state_id = (get_state_id<stt,State>::value));
            cell call_no_transition = &Fsm::default_eventless_transition;
            tofill_entries[state_id+1].one_state.push_back(call_no_transition);
        }

        dispatch_table* self;
        chain_row* tofill_entries;
    };

 public:
    // initialize the dispatch table for a given Event and Fsm
    dispatch_table()
    {
        // Initialize cells for no transition
        ::boost::mpl::for_each<
            ::boost::mpl::filter_view<
                    Stt, ::boost::is_base_of<transition_event< ::boost::mpl::placeholders::_>, Event> > >
        (init_cell(this));

        ::boost::mpl::for_each<
            typename generate_state_set<Stt>::type,
            boost::msm::wrap< ::boost::mpl::placeholders::_1> >
         (default_init_cell<Event>(this,entries));

    }

    // The singleton instance.
    static const dispatch_table instance;

 public: // data members
     chain_row entries[max_state+1];
};

template <class Fsm,class Stt, class Event>
const boost::msm::back::dispatch_table<Fsm,Stt, Event,favor_compile_time>
dispatch_table<Fsm,Stt, Event,favor_compile_time>::instance;

}}} // boost::msm::back

#endif //BOOST_MSM_BACK_FAVOR_COMPILE_TIME_H

/* favor_compile_time.hpp
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
*/