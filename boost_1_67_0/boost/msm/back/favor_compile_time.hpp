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
+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
*/