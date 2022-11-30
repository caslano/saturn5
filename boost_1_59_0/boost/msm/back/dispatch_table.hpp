// Copyright 2008 Christophe Henry
// henry UNDERSCORE christophe AT hotmail DOT com
// This is an extended version of the state machine available in the boost::mpl library
// Distributed under the same license as the original.
// Copyright for the original version:
// Copyright 2005 David Abrahams and Aleksey Gurtovoy. Distributed
// under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_MSM_BACK_DISPATCH_TABLE_H
#define BOOST_MSM_BACK_DISPATCH_TABLE_H

#include <utility>

#include <boost/mpl/reverse_fold.hpp>
#include <boost/mpl/greater.hpp>
#include <boost/mpl/filter_view.hpp>
#include <boost/mpl/pop_front.hpp>
#include <boost/mpl/for_each.hpp>
#include <boost/mpl/advance.hpp>

#include <boost/type_traits/is_base_of.hpp>
#include <boost/type_traits/is_same.hpp>

#include <boost/msm/event_traits.hpp>
#include <boost/msm/back/metafunctions.hpp>
#include <boost/msm/back/common_types.hpp>

BOOST_MPL_HAS_XXX_TRAIT_DEF(is_frow)

namespace boost { namespace msm { namespace back 
{

// Generates a singleton runtime lookup table that maps current state
// to a function that makes the SM take its transition on the given
// Event type.
template <class Fsm,class Stt, class Event,class CompilePolicy>
struct dispatch_table
{
 private:
    // This is a table of these function pointers.
    typedef HandledEnum (*cell)(Fsm&, int,int,Event const&);
    typedef bool (*guard)(Fsm&, Event const&);

    // class used to build a chain (or sequence) of transitions for a given event and start state
    // (like an UML diamond). Allows transition conflicts.
    template< typename Seq,typename AnEvent,typename State >
    struct chain_row
    {
        typedef State   current_state_type;
        typedef AnEvent transition_event;

        // helper for building a disable/enable_if-controlled execute function
        struct execute_helper
        {
            template <class Sequence>
            static
            HandledEnum
            execute(Fsm& , int, int, Event const& , ::boost::mpl::true_ const & )
            {
                // if at least one guard rejected, this will be ignored, otherwise will generate an error
                return HANDLED_FALSE;
            }

            template <class Sequence>
            static
            HandledEnum
            execute(Fsm& fsm, int region_index , int state, Event const& evt,
                    ::boost::mpl::false_ const & )
            {
                 // try the first guard
                 typedef typename ::boost::mpl::front<Sequence>::type first_row;
                 HandledEnum res = first_row::execute(fsm,region_index,state,evt);
                 if (HANDLED_TRUE!=res && HANDLED_DEFERRED!=res)
                 {
                    // if the first rejected, move on to the next one
                    HandledEnum sub_res = 
                         execute<typename ::boost::mpl::pop_front<Sequence>::type>(fsm,region_index,state,evt,
                            ::boost::mpl::bool_<
                                ::boost::mpl::empty<typename ::boost::mpl::pop_front<Sequence>::type>::type::value>());
                    // if at least one guards rejects, the event will not generate a call to no_transition
                    if ((HANDLED_FALSE==sub_res) && (HANDLED_GUARD_REJECT==res) )
                        return HANDLED_GUARD_REJECT;
                    else
                        return sub_res;
                 }
                 return res;
            }
        };
        // Take the transition action and return the next state.
        static HandledEnum execute(Fsm& fsm, int region_index, int state, Event const& evt)
        {
            // forward to helper
            return execute_helper::template execute<Seq>(fsm,region_index,state,evt,
                ::boost::mpl::bool_< ::boost::mpl::empty<Seq>::type::value>());
        }
    };
    // nullary metafunction whose only job is to prevent early evaluation of _1
    template< typename Entry > 
    struct make_chain_row_from_map_entry
    { 
        // if we have more than one frow with the same state as source, remove the ones extra
        // note: we know the frow's are located at the beginning so we remove at the beginning (number of frows - 1) elements
        enum {number_frows = ::boost::mpl::count_if< typename Entry::second,has_is_frow< ::boost::mpl::placeholders::_1> >::value};

        //erases the first NumberToDelete rows
        template<class Sequence, int NumberToDelete>
        struct erase_first_rows
        {
            typedef typename ::boost::mpl::erase<
                typename Entry::second,
                typename ::boost::mpl::begin<Sequence>::type,
                typename ::boost::mpl::advance<
                        typename ::boost::mpl::begin<Sequence>::type, 
                        ::boost::mpl::int_<NumberToDelete> >::type
            >::type type;
        };
        // if we have more than 1 frow with this event (not allowed), delete the spare
        typedef typename ::boost::mpl::eval_if<
            typename ::boost::mpl::bool_< number_frows >= 2 >::type,
            erase_first_rows<typename Entry::second,number_frows-1>,
            ::boost::mpl::identity<typename Entry::second>
        >::type filtered_stt;

        typedef chain_row<filtered_stt,Event,
            typename Entry::first > type;
    }; 
    // helper for lazy evaluation in eval_if of change_frow_event
    template <class Transition,class NewEvent>
    struct replace_event
    {
        typedef typename Transition::template replace_event<NewEvent>::type type;
    };
    // changes the event type for a frow to the event we are dispatching
    // this helps ensure that an event does not get processed more than once because of frows and base events.
    template <class FrowTransition>
    struct change_frow_event
    {
        typedef typename ::boost::mpl::eval_if<
            typename has_is_frow<FrowTransition>::type,
            replace_event<FrowTransition,Event>,
            boost::mpl::identity<FrowTransition>
        >::type type;
    };
    // Compute the maximum state value in the sm so we know how big
    // to make the table
    typedef typename generate_state_set<Stt>::type state_list;
    BOOST_STATIC_CONSTANT(int, max_state = ( ::boost::mpl::size<state_list>::value));

    template <class Transition>
    struct convert_event_and_forward
    {
        static HandledEnum execute(Fsm& fsm, int region_index, int state, Event const& evt)
        {
            typename Transition::transition_event forwarded(evt);
            return Transition::execute(fsm,region_index,state,forwarded);
        }
    };

    // A function object for use with mpl::for_each that stuffs
    // transitions into cells.
    struct init_cell
    {
        init_cell(dispatch_table* self_)
          : self(self_)
        {}
        // version for transition event not base of our event
        // first for all transitions, then for internal ones of a fsm
        template <class Transition>
        typename ::boost::disable_if<
            typename ::boost::is_same<typename Transition::current_state_type,Fsm>::type
        ,void>::type
        init_event_base_case(Transition const&, ::boost::mpl::true_ const &, ::boost::mpl::false_ const &) const
        {
            typedef typename create_stt<Fsm>::type stt; 
            BOOST_STATIC_CONSTANT(int, state_id = 
                (get_state_id<stt,typename Transition::current_state_type>::value));
            self->entries[state_id+1] = reinterpret_cast<cell>(&Transition::execute);
        }
        template <class Transition>
        typename ::boost::enable_if<
            typename ::boost::is_same<typename Transition::current_state_type,Fsm>::type
        ,void>::type
        init_event_base_case(Transition const&, ::boost::mpl::true_ const &, ::boost::mpl::false_ const &) const
        {
            self->entries[0] = reinterpret_cast<cell>(&Transition::execute);
        }

        // version for transition event is boost::any
        // first for all transitions, then for internal ones of a fsm
        template <class Transition>
        typename ::boost::disable_if<
            typename ::boost::is_same<typename Transition::current_state_type,Fsm>::type
        ,void>::type
        init_event_base_case(Transition const&, ::boost::mpl::false_ const &, ::boost::mpl::true_ const &) const
        {
            typedef typename create_stt<Fsm>::type stt; 
            BOOST_STATIC_CONSTANT(int, state_id = 
                (get_state_id<stt,typename Transition::current_state_type>::value));
            self->entries[state_id+1] = &convert_event_and_forward<Transition>::execute;
        }
        template <class Transition>
        typename ::boost::enable_if<
            typename ::boost::is_same<typename Transition::current_state_type,Fsm>::type
        ,void>::type
        init_event_base_case(Transition const&, ::boost::mpl::false_ const &, ::boost::mpl::true_ const &) const
        {
            self->entries[0] = &convert_event_and_forward<Transition>::execute;
        }
        template <class Transition>
        typename ::boost::disable_if<
            typename ::boost::is_same<typename Transition::current_state_type,Fsm>::type
        ,void>::type
        init_event_base_case(Transition const&, ::boost::mpl::true_ const &, ::boost::mpl::true_ const &) const
        {
            typedef typename create_stt<Fsm>::type stt;
            BOOST_STATIC_CONSTANT(int, state_id =
                (get_state_id<stt,typename Transition::current_state_type>::value));
            self->entries[state_id+1] = &convert_event_and_forward<Transition>::execute;
        }
        template <class Transition>
        typename ::boost::enable_if<
            typename ::boost::is_same<typename Transition::current_state_type,Fsm>::type
        ,void>::type
        init_event_base_case(Transition const&, ::boost::mpl::true_ const &, ::boost::mpl::true_ const &) const
        {
            self->entries[0] = &convert_event_and_forward<Transition>::execute;
        }
        // end version for kleene

        // version for transition event base of our event
        // first for all transitions, then for internal ones of a fsm
        template <class Transition>
        typename ::boost::disable_if<
            typename ::boost::is_same<typename Transition::current_state_type,Fsm>::type
        ,void>::type
        init_event_base_case(Transition const&, ::boost::mpl::false_ const &, ::boost::mpl::false_ const &) const
        {
            typedef typename create_stt<Fsm>::type stt; 
            BOOST_STATIC_CONSTANT(int, state_id = 
                (get_state_id<stt,typename Transition::current_state_type>::value));
            self->entries[state_id+1] = &Transition::execute;
        }
        template <class Transition>
        typename ::boost::enable_if<
            typename ::boost::is_same<typename Transition::current_state_type,Fsm>::type
        ,void>::type
        init_event_base_case(Transition const&, ::boost::mpl::false_ const &, ::boost::mpl::false_ const &) const
        {
            self->entries[0] = &Transition::execute;
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
                    ::boost::is_base_of<typename Transition::transition_event,Event>::type::value>(),
                ::boost::mpl::bool_< 
                    ::boost::msm::is_kleene_event<typename Transition::transition_event>::type::value>());
        }
    
        dispatch_table* self;
    };

    // Cell default-initializer function object, used with mpl::for_each
    // initializes with call_no_transition, defer_transition or default_eventless_transition
    // variant for non-anonymous transitions
    template <class EventType,class Enable=void>
    struct default_init_cell
    {
        default_init_cell(dispatch_table* self_,cell* tofill_entries_)
            : self(self_),tofill_entries(tofill_entries_)
        {}
        template <class State>
        typename ::boost::enable_if<typename has_state_delayed_event<State,Event>::type,void>::type
        operator()(boost::msm::wrap<State> const&,boost::msm::back::dummy<0> = 0)
        {
            typedef typename create_stt<Fsm>::type stt; 
            BOOST_STATIC_CONSTANT(int, state_id = (get_state_id<stt,State>::value));
            cell call_no_transition = &Fsm::defer_transition;
            tofill_entries[state_id+1] = call_no_transition;
        }
        template <class State>
        typename ::boost::disable_if<
            typename ::boost::mpl::or_<
                typename has_state_delayed_event<State,Event>::type,
                typename ::boost::is_same<State,Fsm>::type
            >::type
        ,void >::type
        operator()(boost::msm::wrap<State> const&,boost::msm::back::dummy<1> = 0)
        {
            typedef typename create_stt<Fsm>::type stt; 
            BOOST_STATIC_CONSTANT(int, state_id = (get_state_id<stt,State>::value));
            cell call_no_transition = &Fsm::call_no_transition;
            tofill_entries[state_id+1] = call_no_transition;
        }
        // case for internal transitions of this fsm
        template <class State>
        typename ::boost::enable_if<
            typename ::boost::mpl::and_<
                typename ::boost::mpl::not_<typename has_state_delayed_event<State,Event>::type>::type,
                typename ::boost::is_same<State,Fsm>::type
            >::type
        ,void>::type
        operator()(boost::msm::wrap<State> const&,boost::msm::back::dummy<2> = 0)
        {
            cell call_no_transition = &Fsm::call_no_transition_internal;
            tofill_entries[0] = call_no_transition;
        }
        dispatch_table* self;
        cell* tofill_entries;
    };

    // variant for anonymous transitions
    template <class EventType>
    struct default_init_cell<EventType,
                             typename ::boost::enable_if<
                                typename is_completion_event<EventType>::type>::type>
    {
        default_init_cell(dispatch_table* self_,cell* tofill_entries_)
            : self(self_),tofill_entries(tofill_entries_)
        {}

        // this event is a compound one (not a real one, just one for use in event-less transitions)
        // Note this event cannot be used as deferred!
        // case for internal transitions of this fsm 
        template <class State>
        typename ::boost::disable_if<
            typename ::boost::is_same<State,Fsm>::type
        ,void>::type
        operator()(boost::msm::wrap<State> const&,boost::msm::back::dummy<0> = 0)
        {
            typedef typename create_stt<Fsm>::type stt; 
            BOOST_STATIC_CONSTANT(int, state_id = (get_state_id<stt,State>::value));
            cell call_no_transition = &Fsm::default_eventless_transition;
            tofill_entries[state_id+1] = call_no_transition;
        }

        template <class State>
        typename ::boost::enable_if<
            typename ::boost::is_same<State,Fsm>::type
        ,void>::type
        operator()(boost::msm::wrap<State> const&,boost::msm::back::dummy<1> = 0)
        {
            cell call_no_transition = &Fsm::default_eventless_transition;
            tofill_entries[0] = call_no_transition;
        }
        dispatch_table* self;
        cell* tofill_entries;
    };

 public:
    // initialize the dispatch table for a given Event and Fsm
    dispatch_table()
    {
        // Initialize cells for no transition
        ::boost::mpl::for_each<typename generate_state_set<Stt>::type, 
                               boost::msm::wrap< ::boost::mpl::placeholders::_1> >
                        (default_init_cell<Event>(this,entries));

        // build chaining rows for rows coming from the same state and the current event
        // first we build a map of sequence for every source
        // in reverse order so that the frow's are handled first (UML priority)
        typedef typename ::boost::mpl::reverse_fold<
                        // filter on event
                        ::boost::mpl::filter_view
                            <Stt, boost::mpl::or_<
                                    ::boost::is_base_of<transition_event< ::boost::mpl::placeholders::_>, Event>,
                                    ::boost::msm::is_kleene_event<transition_event< ::boost::mpl::placeholders::_> >
                                    >
                            >,
                        // build a map
                        ::boost::mpl::map<>,
                        ::boost::mpl::if_<
                            // if we already have a row on this source state
                            ::boost::mpl::has_key< ::boost::mpl::placeholders::_1,
                                                   transition_source_type< ::boost::mpl::placeholders::_2> >,
                            // insert a new element in the value type
                            ::boost::mpl::insert< 
                                ::boost::mpl::placeholders::_1,
                                ::boost::mpl::pair<transition_source_type< ::boost::mpl::placeholders::_2>,
                                                   ::boost::mpl::push_back< 
                                                        ::boost::mpl::at< ::boost::mpl::placeholders::_1,
                                                        transition_source_type< ::boost::mpl::placeholders::_2> >,
                                                        change_frow_event< ::boost::mpl::placeholders::_2 > > 
                                                   > >,
                            // first row on this source state, make a vector with 1 element
                            ::boost::mpl::insert< 
                                        ::boost::mpl::placeholders::_1,
                                        ::boost::mpl::pair<transition_source_type< ::boost::mpl::placeholders::_2>,
                                        make_vector< change_frow_event< ::boost::mpl::placeholders::_2> > > >
                               >
                       >::type map_of_row_seq;
        // and then build chaining rows for all source states having more than 1 row
        typedef typename ::boost::mpl::fold<
            map_of_row_seq,::boost::mpl::vector0<>,
            ::boost::mpl::if_<
                     ::boost::mpl::greater< ::boost::mpl::size< 
                                                    ::boost::mpl::second< ::boost::mpl::placeholders::_2> >,
                                            ::boost::mpl::int_<1> >,
                     // we need row chaining
                     ::boost::mpl::push_back< ::boost::mpl::placeholders::_1, 
                                    make_chain_row_from_map_entry< ::boost::mpl::placeholders::_2> >,
                     // just one row, no chaining, we rebuild the row like it was before
                     ::boost::mpl::push_back< ::boost::mpl::placeholders::_1, 
                                              get_first_element_pair_second< ::boost::mpl::placeholders::_2> > 
             > >::type chained_rows; 
        // Go back and fill in cells for matching transitions.
        ::boost::mpl::for_each<chained_rows>(init_cell(this));
    }

    // The singleton instance.
    static const dispatch_table instance;

 public: // data members
     // +1 => 0 is reserved for this fsm (internal transitions)
    cell entries[max_state+1];
};

}}} // boost::msm::back


#endif //BOOST_MSM_BACK_DISPATCH_TABLE_H


/* dispatch_table.hpp
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
*/