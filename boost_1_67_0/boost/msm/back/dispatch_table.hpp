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
KcM1IFrgpCe00Gnbw8WUdbuCKkYT8ozPH+bhQ1PmYyDnmV0q/hcoCgoq6kbABQDEvzdqOHCu9m9G6/O9J5K9Lw30myL45NyFVfW+YC+se3PSh3Vwg5daJHwuCfsPZCBBsl6ikJ6M7C3OVcAZufrGqJEsJotnvEKuGDTZGKigkajEhJP1fnbUIflg9ROmrL1/qUwdMOGASdeECYek/690OAq0ROXq1+114wg9Y1SdjQhKLuxn9KwNBlriRIx8fhIfX74nCYq12pX/2Z5dVGv4hDlWIESr0xoDbUCU+kMwaXriXB9+CmmIOuieDNzdLXKiEUMaUReut67Wzv+Vt7ioyAODNBf2LpHwewM1nk/ApmnmtxApStV00aBrjpyPjIR69C/qfa6HO1Ut5cjND3lgczlPAdVg+bF0ienZh8ho1fCeqR6iPJ6w3Pga8KuETJET1RECpBdbi1jCdN6jPT98NbR0okAIexJvvjT4pZ4OCWKD+zcPbPKVtds129DmvfcSdqL9pbnr7R2rAt71tNs/F9WEZ0e0QkG1Gged0b98b9XogzdFqyeGWHrNgntSnTfnKWRot6vuWMSRbikeL3i0j7HehldR/4064jW6UWEheNOUog4qZDNgim+gPwsx4uM7rh9A5w7cMaXgNDDybDZrEHkvQHZAhcWbbhJgZXBNJ55fGKYOV5+etviSJQjnRiaiwNNNN+3pCQHWPlcW8y3K58v0CPXugkKxkdH8wzYXKJx+HknD4xHlYGLrwaU4+ro9dTiloUS8G/JmLB2HtCBqKdh3h3GJ06mTxGYtCBNJJdY5TAoDjYfjz2dNpB02AbSF1TDtKKQ+l/2xI9LBlIQWb2px1UDIQVF1RMx2VYczUrDbFss/TFlbNx0uNCz1cKJvP3NNX1ujoUNUcwX4Es67QvRMZw1+b+JXESKxfDhr7CpTYa+dV76SD36UGyz19fNTRR743r3hyHxdokZaC2vqRQ/pyUtw8gHCpgvv8DdIgjQzPpWzaSchmQd9+5O24FDbJXY1X27S4LK863c3GRyYOAuhImH6fKxdwQ9kFmM3YZc9ihg6yTUNuEsD+wKNpIJaedvzLsBEnw8aYVHfUv2zazjneJTVSYJtpJGYXt1uZPE6ZyadSYGlqnKJ8DS/KT3UtbToMZC+fYvfaVIbbvJ8wmHhhNwLWYff77eKYnRI1MIKpN8S/nrziSY4KWqL8o90MffmofoD0KM3PPJieIqvvSiXilJ+l0/miUiFx+TtzMPxndhrDPTnH43bSNGycn26T+YvLQPMs9N86UYzPNe4BObIVmiutLsBMvSTpREZEHc3T7xpU8GAf1UbqumD2F24kBH0nirUAqIlOYtOQq8iOmrqP5/0iHE5NL7a6lMeqgecVK98ULvwu9OqhaygoiGx40/xn01ZwT79HlCowe+HwKXeEI7SiELKC08AQ0aUZCPHMT8PW683u3t7dcspT2pfanWkPECZZn8hqVxiUMgCzovsGYRJGnDEeAYxj3mDnMeADblQyQygsCZnRZzX2wP2VAGVliYB8FsPHg7CCnNYnfy3/pNvsBX8XRXEo6emdp4H5yudxv3dy+rgkCIJ7g1g3oCbPKZfk7jyQF2Z5Vqb9SHuSAJC/QKLEAq6696AQPwt9d0STZnABprckvF3fQeQmc6LIrTDtJbf2FP4eFCnTXOmV4OZbxlraxKHkYI7QJkE8ZrfYG04P+DvS+/wT2pjvhsZxewlKBcPNjxYj1UIpBzivTiy5MKE9yAK5monHiqxvsbacxb9OqoKfjIh2hgQKcPssIvQLvnlX01TR4G42MYUP8rblyswnkJTfpMG9NmsWUXG8wa5hXzo6j4KjNl7MEV+wmFfxF6K5rEWxKegA76EhrrvvS29qRah2Q0wFCSf8ZAHDx0E27UetvICi2a+65benF0F6dP7gwhu1UFfUiUZEmgODlsTN1CO2nBKb7iSXKoTf45+/T2rEIHZ60zkN6KEPQc/pakvkj727NobGv3+neBxN56IbgoeqwhqkH/rJrZB8tSw5/ng0ewsmBE5Ws0Bqc8UVsbJmmjRi/6joqura5DqsUkHlaTsGOA7tKklHRwQy3aRMdHV1MS4ZhZtuxBI/sIHjap4un34IG/F4CO2IXtB9ZS8Wh1dOHRzdJHBQF8vvHIUWMnNeG1VrNM23NVcDPR9kSw8YR0PYrWsnX1qriooxgPtgive+azvwTTbJyvV15R+nZx4dlV3H3+y0tHZ+7mrufd09/x8wSJanStP52+a1hhBEBdNXSkFbJqFqN862B9f799NrQm3FxLWXohK8MCknZ3jDaq1m4m8FPAPBxeSLgwVYX/ADpAS4Iiv7/rg8CfBavzIvZRktpKHf0mx6qBEi6hcdhcvbTVVQc1BSJzfjYqK54fUgzPwsG0TMYR9tp+nl3Bubi400MnScm1QOP1Qv9ryAjwvEj6VxQdoS9LvY42ye9Is6NuAy/x5HRYq+amFJCjlhPqEOrkl8VAj1Y7ML+3WfBQFJdPuWM0CyvoRlLPSx0CndxdiZoY9tSc+/DGK0m+n7Jr7pEFqMUqoaj5wmriAEL5uS/0pj63rHHemhVjfq2sT999g2PDXpod1gZGpr5Bcbo1c5c04glqg2LSPASCj6Hqk79H944bbS0vyTmg0j8jjl27BoEAg0DETSe0P8Z64OP6C8QzrwcFDddjYk4eAsTVJb0hlA6Pk2uJWMkyVku0CfClaK9W/WusdXHzxUVVQH5/7qAXQDIT14vJAeUXapaxOF1NQPsAPOZhfQCviN2VlNRIJoLOxxOLZaMvt9L/nV1nTt19Pd5hUtvEOfS2I2cS5PoazyViyx6h+cBtEl5uJfruIpoAWi/Xz86ly/YXysIG002cyMsN6pTc4oQYfYli1yPkfOt+NWpSjTGQcgaFuOQ/0nbkXnRfrzzUtwLudLr4XPJm/6reGnvXy6/sRbpIN4KayDQaBNwUGwsFLRxsVDfV+T5Fx+AEYL80u+O2RbpSZH2F28A3/Ybus8wIxyU5Qc1Et3+GkwXoRyA669bjYd0XhmANSusitPpk0gZV3fV9fO1biET2ymckNk/iVcS5wluvFs7L4N/7oXu1GoeQjiPuaJWgH5uf4TaUg0/8E4pEoPCt8mjs4Oe1hW4vuVwBWB1A8lUIGXjwq94tvCEuPMyGmbYj3/FJgsy8kXM0LsjeDti9tQ4DpXMdXy+o/MQ1A99cfXqjOhpeXGFRuBwUa4P4gXUhJsV8eF5s+Iq8vR5mvYCHNZr//jCsAhSDqBrXTtxxhPzxSoj4LnyBTzjaiP5ws71Oa5jvmVKNjzrL2SsUoPRlCc7otG2b8G+qGbZ7+O+B9f5ZuBCc54VlfYH4N0MqU3tg7a+IJ/4ZD686lvhrhGPt/mQoCJ+MFGXfWSWP+DWzWnV+QmtY5fQ1cmn9K5BAJSFaK7DXx/pldJCuVAEFE9mJA/jT1uV1hrZMbcsfNgt8WW8gpEpzQQYOKQ7DjhKG1PTyTbqFUup3X3Ie4TLDNyNtZ52+AJqqMUhElqXGZgSOuIcKVyDFXn90PzjLD6HIq7l9608rGFuM5WIMSXWdwP+avD2Fdyfq3Es5MnMnrPnJ/Db/4oDtHTxZ+Ib3E7OJ+9uHzoiZT5IXi/hMq2zep4GsOINsuDD3UlxBrxicvtAUTBcZtpCryfWYOdSjhmUDPD7lsTCqyYvOlDLKV+OafyDBpE5UJkZV/IYsfq73WQ75UEE/F7wfp5CbSXloey6orgm+4gRkiO/u/AYVtgawVpIRJ7kAimwtFywHi3udCbkEknTbMN+MAJLdohoqbeJlkuODXPeREilPF0fkw23Ks4N/LRB6rBjtRE+1yh+R05ttxHeGDU+uUSOQ3NVt9rdz4ZhbxjIxqjO/e4RidW30dzEG85khB1cwiC03e1dAuypExkWXC+cyo0QNI+F5FaTTeiUefEPX3rzzLuYigIP7RUeDlU0bZUJyirm78G1grE6aCQrHKaX0qzfdfjVplW7kyxtMPieRZ8kEfX1Mrh715B0eu3r3YtWJ9E4fL+kCO7bYnOrfbL2sUiD1zrc+GNm07vp/f/hr5rnjYtkJFNkiUoeA7nudP68J2CQavH8WJOhH5TUJE79xei4XnH/6MlNUklbnWZGLAtuKiMMbns3XaLTB8FUPvh3cUs9OajxXRvqd4y2HhVrlDEilWm1fOQnPW6+s5x5qvID/IwJoXEQ9wVpIrZaMLwhG7F0HF11Eg0jmQ09ch0DSmqhE0UWioI3IqMLrVTsuTM4iWsuKGGG67NTCiv4zgrZ6OdGv4vIKsXE9taCpdi7auf44MqXm/ExDjgH/B9Qo349EySQktWh4nQyVy3wFfY+R4irlapkElXKiNiGt8YWr6naVF0rAzTnX1uEZjY0FxE/mnYpJsJxxPn3fT6+shExNqnpXtU7Nr6D8qaCrO6W9vb83qSjGOrfmcmzimNip7bV0oIiH9Y8+xmJAAPv9Kj96OWEVnI+F+1g1qamuL1IuNjvG/rADfS6SdgQdKgP8t1ldc7OsrtAQGAPBVqcQwlGBsBMq59f5Hu90wuPrpcXYSYOT1WaRIt3zOXkc6+NevxyMTK5nNYIMSSBp6zOnp2Ze/676sVToK8J+tfzd4grEyVArr/1Zqd4DkLnXCrcWXuQKtojVlhGR63tdOgH5scv4kXcket1ha4fK3Gjb5IGNVYxZh+jtxUw3Nx0ZcVLROd4nH4FI9gAwjAgkAmscLHOLwzmG5cbcUr9f3jnkF9VZPqRgve90wwtNguPdRkq923NlZTa1Kx3vUBB6V3d9ZRPzuR7hu3VitSf910ZBcGf2MLRuPSeCYrjCE2zYCDqwwSwI8tqGupHzmbdoo/KPrKEI8ukfp777Uiy6lYB8W+vftxYT3TdFfvNqSP/oOG4F9PwfdNoa8BdigATLCmhqGuy/Nv0VztK/UDXp9tEwIOP8t4/vRCgsrKipithPjmt5rJrGX/x5y2cGSKO/ND5DP/3FJQJD56Mfn7EzgcHZ2aGcOTrws8o8JtHDPYyWfX5MjIxOYHB6NVfb2sWw4/XhCwanfqiKzUDtP29RdSttyUxSvoJDNw8nNIlH6e7uXFYVgfOVlx+HGFPJcZvLDoKR+rNS5TpgGjtt0Z/QPx0TgCGkmSBlks1NZ4tb7bFgB8I5YglYy7IrVnYJU3Hw8oK53v4tjQJO32YJSfDfG75+Hi3bw4vEI1vdFRUVrJLldfXw8jV7uk1uGHie7A7BgQxaz+3VX90NYk9G7tIDyWO+Nx6NfLaCA8O73+5ns1QpST+GdqCFZtNuK57szIitXa62UvbWG1zbXu2UC/57O+Nzu49F8SKC3Wswhws6rh48yLGkNw3udPmSRigvUIM/R5lXBXYysd+X1OLIdHS7Q0w4J5AeUwT3TyTUdh68GhV8qQDEB1xivVsp/Fhx/XDs/z5rsqmylJiUlbQRSlGfG/vGCHVq3kDVc7bgaqc/puhVaWnSBwJnOnd4sUsuSA44wVyNUh0otCwtu92xlAevqlqFnVnnFzGqGmpA7r+Giu3qZfB/WzVd+CeMrY/8SwCRZo3smYnfVEPpy0CtoSZzh+L8EHFQgpJIlzqByZiLU9OGqpPQkykfnfdpgh/sTD/HXoXFD9S+7jLC6VccXosRq9otrwoBzO5bmnBkD36ZqsC6dVTPw0jcj42irI7UIgl3d0utA/6uawdNI8V9OKGaKK4dE8Xx6HMja2vvfUlCRd5O3N3Th6/eMcXBWVlWjpCThfvdJ41evuRkO+adyrS/FxczP35uK7uaYZjH0t49ChN81hodnrdGUFDvkkrp8nmoOzy6MUlUdTxJms814s6ChZQDAXS/Kyyjx/j6jv4nquR8xFJTCMD63bDM4i7Nr8+ufQ/XV7dDFZQn8tqSEv91h/p/v9xnNdvgb5s7SRBUirCXtT1XX1McRZt+rACm+1ct1GalKUJ+yqkux44UboGBVh3D0QgUz7OtJhyXmEuzzewcoaOx58iAnd6QSqlPywlN1xZXUzn/TlREIN1hCpmZGrWjy5XVA9YBLzr1cURyszakOGvZj187ynRB6OaxvaK7vG3qjutAJX99C5KqhOhmi6iykWzbdcRJOYsddEyu0pQLJqO1Urqguv8uheCJ96jZjl9N3k65MzmFWRoXXD7PjngU1uyHFGLaCJIBPgjsHwh/DmHETy2wGcoPU+bLtYulHTz7w7DfcwvmCZiaVY4+iBm7FLSExb7JtVHL5SyZpZvXijkh2WoNExAFXAbxZdubXpGDbHvU/MCcj7y8hqdWVSSNPPJedUrJG3dZkz04fkgCYfIMSRD6B4jOookrYa7GxDYZJAb9QgSKYfkmmr4VH6CKmTQsE9pWN9pzk/OswH22CEt2thR8P/iSRN+FGJK2Xbfq/ORiUZOtqxS0nfu4B+6KVJ23kQUeA2iy+ecktuHpPAW82g8Iis5zGlkh0sE3Kxi8j2VZo5ocDNAcf+gVh3AIlF5G8NlE9g4bH+OZdPH8VxD+uL/j+DOepSImXzmpiuDvaIFlnaPIDEu3RhnP6AOT7Md+wi+LZfUFKVYj0YG5HAzK9/Lq6aqYM+lOxLGdb+fyKrsDF1diXUrgoim/OE0/uuo/S7om6p6cHS9yDpFQ96u37tyj19fVDO/SK5lBsbZZcaTsDyhH+txpZIxGvxV+FZo0qKSnJf/5MsrOiqqws/OR95MHs7n6dmKb3rbf3bQqopbERz8oKBQsN5dtEbjCbGNr8UX4ZF5R+4XtCYf4t01FMQ6IJfsTvR7TdYplE5g/5ouzU1436cwcK0gZU8ceho7bv4iOrtnHYSdVq9Ode9cvoJyPZ+dHaj868qcibzGL7Gth51pty6IQlm8ZGNK7zJra2pU0Ih67XtYyJ2LYyWiHzWwz3sMLtCOOQFzGqaghlaoqyG4bcCO/qGU6felCpqyl5b5Y4n+cZytx3rDJDbvPWk/fnD24yd/BvVzTT8uLodHfYGt+3P2Y38qQndJU43gqx5nWIkiYfo8zp/SisVwu+H5B4zyKaiDs6ZahH4GfJDCHb02gZID3zxKucmdrIieqpCYz1pLCo6yBjlCT3FUmMvNpydN/bmh7Hid3g7rOMC77CXpibAm5hYEXIXoPU8L++fTMc8/rHp2lOJ3nDFCzja/vGd18PP39zjRPNlO15DFsx3LXVehcrZc68Q6rLvnd4Zm81UcH7GC7OCgkPCJjmIbeoK6VGrVYtGneKNX38d/cBr9yqKG6+Nf+8/7AOBxzLMb0SQIeKKuwaoBG3IidMlXt5ecl7Hrs+MHRIt9rmgflwsRbxwYMQLEE/sNZBvQoGMRAySHT3RRFKN//yla+5uroCd+YuhlnOB7KQHwz1u8B6nMe/k0ddP9uSQu6PgEB76ond6yDln7+lDC5OT8cgbzU4KWL6pei7rrtY729Sr5FjhCnHra4yDal6H9j5mqAX+jW7DIofFBWN/4Gl4OM8NCxEWqO1+hcVZt6ihdy5S8tdUnD8Bwy/FH3u28skdcP1LVK9+p/cgG33abvis+vi8LK0UeytHcYcA+AzZNLo5MIea/rgM9mr3rd/AZOg+TgeVpZ7YtifIHe/A0o92BDRm13uk59nuMaDkOC5+k1hZyq0w5vsz+s7gT8cNAIw35BxT4BNs5vjX3qem5ubR00D/EjZeaBLlu5PBVgLtaGhj9BIDAqbwaJbIqGTteIYU9MuqKDwTF5X+d6LfgkMrEF5TtFjvcIddPbDdIXzcyJGnBoX+NfeKa2wkO7WaWD+n8swq6STxeZRCnDTZX/ehNTVocDewnKNUdv1Tk+meSkkhs4xLfeZ9PnFKmbD307ZNPcRhIxM4LbUS/U/n/oxxtbWtvnZ5czHl6I7m72YocbKQmU5cP6X1LIoxTPeYtDR2gJjKF2enWj6G4etRSy1T2GBtIbm1x8K99ko34PY2b4Xv8pbVKhD+1TU2O12IjOR/Qx+qOCsE6BqUNkuD5iQrDVZezbphJzAuwLAcElNF/aNlD0wZH0J8Rxuq11WA3henmXA71d3UubPjr1jnrpmHZ2cTLOpVzzus/UQf12JXE+sCuf6VWQBOiMCr2IJX3E+agj7jsPDnpo9bHzD/zz8O1E/d17wOGo54BlftaFmALe5OA9hrT78HGc9O7OXbNEXbvX0Bdp+swNCJtc5sUVdp4JwjNvbLwieQjJKnvygiUy7mzIXC5/9734E+QyZAiU2BAANHmxrJ6Mu/ne98xowVyg3gNo5K9eb4u/6+vrKv1mRiufzdDBgTARw9h21Myjon+7x87vn8yy4QaIbcJn8EQIJpHPx9lZ+ulqJu5mtYXvnvvBK6Nhn9IKGNx5s7K39lzUOItUwazjE0ColskiTrVk2uzcg7/KRH+8jWBKkIP7sGXR3Xz09/DHA++T51t/DTqDVwhf2GrDovzdBJ06Re3GiRRioDuuWZgDJOwXOXnqOPg0wLsrIMRBc0FDmgO1du9V4A0ZcGO7zTrorVm7O5lEzxTBu/QO2weZHECnlJ1Q6xg+EBDktDMnlC6RYc/bKT8tJloo19I7CoxdaiAfr4/V7r44IaIwpvjOt23nFly6gjripKcbcq+tRTO51WsH9kcTAn8oUghLZo6VPooliFnF9U4ExR6kAW/Wbm5UuTGGx9IpVJOKGPc+fk4RSGezZe4ZqNk8tS93B/vN5e564T6fX86OYXKVyX3Ijbk70dAjKLqYIU6t/m12b3MFj1IRWfmM6NM++qloRd07aiCdqLgw/0zcXN1mU4nK0wd1pp3NhcCnRYsWdFMjwPD7sAEySfTIQ3AZbyy7/Inzj2cGx62QFIk26PapRSKS6pNpFA6G0sQLCei/7E73mqD4ncEWtBu8lugWif0PVlfbvph4i+IJM1UPzWtIX107XZkisDftTQXZeql8VI9mFIWbxhlPI5w0nDZITFKurCY2MR1EyhfYQTnN07RJOZq4msoqZtJC3llQPwvg6T7lh7wfx7T0+AvY7ZFVhn8p49JGbRB3ym10FyRRcwrfTq4tk1mTYvTH9RtJek7uEXo+Ne8ZzFfU0T4s2yzrtp02lt9DPoW9Iy129K+Mx/mjggD9H3iZnefTBlmMDSbWfJr/4FndGxlS205O/cbhF2rBfeErznODg3YJc2jHHlK4TSrUFrmdls4w=
*/