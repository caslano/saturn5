
#ifndef BOOST_CONTRACT_DETAIL_COND_SUBCONTRACTING_HPP_
#define BOOST_CONTRACT_DETAIL_COND_SUBCONTRACTING_HPP_

// Copyright (C) 2008-2018 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0 (see accompanying
// file LICENSE_1_0.txt or a copy at http://www.boost.org/LICENSE_1_0.txt).
// See: http://www.boost.org/doc/libs/release/libs/contract/doc/html/index.html

#include <boost/contract/core/config.hpp>
#if     !defined(BOOST_CONTRACT_NO_PRECONDITIONS) || \
        !defined(BOOST_CONTRACT_NO_POSTCONDITIONS) || \
        !defined(BOOST_CONTRACT_NO_EXCEPTS)
    #include <boost/contract/core/exception.hpp>
#endif
#include <boost/contract/detail/condition/cond_inv.hpp>
#include <boost/contract/detail/decl.hpp>
#include <boost/contract/detail/tvariadic.hpp>
#ifndef BOOST_CONTRACT_NO_CONDITIONS
    #include <boost/contract/core/virtual.hpp>
    #include <boost/contract/core/access.hpp>
    #include <boost/contract/detail/type_traits/optional.hpp>
    #include <boost/contract/detail/type_traits/member_function_types.hpp>
    #include <boost/contract/detail/debug.hpp>
    #include <boost/contract/detail/none.hpp>
    #include <boost/contract/detail/name.hpp>
    #include <boost/type_traits/add_pointer.hpp>
    #include <boost/mpl/fold.hpp>
    #include <boost/mpl/contains.hpp>
    #include <boost/mpl/empty.hpp>
    #include <boost/mpl/push_back.hpp>
    #include <boost/mpl/eval_if.hpp>
    #include <boost/mpl/identity.hpp>
    #include <boost/mpl/placeholders.hpp>
    #ifndef BOOST_CONTRACT_PERMISSIVE
        #include <boost/type_traits/is_same.hpp>
        #include <boost/mpl/or.hpp>
        #include <boost/mpl/not.hpp>
        #include <boost/static_assert.hpp>
    #endif
    #include <boost/preprocessor/punctuation/comma_if.hpp>
    #include <boost/config.hpp>
#endif
#include <boost/mpl/vector.hpp>
#if     !defined(BOOST_CONTRACT_NO_INVARIANTS) || \
        !defined(BOOST_CONTRACT_NO_POSTCONDITIONS) || \
        !defined(BOOST_CONTRACT_NO_EXCEPTS)
    #include <boost/mpl/for_each.hpp>
#endif
#ifndef BOOST_CONTRACT_NO_PRECONDITIONS
    #include <boost/mpl/pop_front.hpp>
    #include <boost/mpl/front.hpp>
#endif
#if     !defined(BOOST_CONTRACT_NO_POSTCONDITIONS) || \
        !defined(BOSOT_CONTRACT_NO_EXCEPTS)
    #include <boost/any.hpp>
    #include <boost/optional.hpp>
    #include <boost/type_traits/remove_reference.hpp>
    #include <boost/utility/enable_if.hpp>
    #include <typeinfo>
#endif

namespace boost { namespace contract { namespace detail {

namespace cond_subcontracting_ {
    // Exception signals (must not inherit).
    class signal_no_error {};
    class signal_not_checked {};
}

// O, VR, F, and Args-i can be none types (but C cannot).
BOOST_CONTRACT_DETAIL_DECL_DETAIL_COND_SUBCONTRACTING_Z(1,
        /* is_friend = */ 0, O, VR, F, C, Args) : public cond_inv<VR, C>
{ // Non-copyable base.
    #ifndef BOOST_CONTRACT_NO_CONDITIONS
        template<class Class, typename Result = boost::mpl::vector<> >
        class overridden_bases_of {
            struct search_bases {
                typedef typename boost::mpl::fold<
                    typename boost::contract::access::base_types_of<Class>::
                            type,
                    Result,
                    // Fold: _1 = result, _2 = current base from base_types.
                    boost::mpl::eval_if<boost::mpl::contains<boost::mpl::_1,
                            boost::add_pointer<boost::mpl::_2> >,
                        boost::mpl::_1 // Base in result, do not add it again.
                    ,
                        boost::mpl::eval_if<
                            typename O::template BOOST_CONTRACT_DETAIL_NAME1(
                                    has_member_function)<
                                boost::mpl::_2,
                                typename member_function_types<C, F>::
                                        result_type,
                                typename member_function_types<C, F>::
                                        virtual_argument_types,
                                typename member_function_types<C, F>::
                                        property_tag
                            >
                        ,
                            boost::mpl::push_back<
                                overridden_bases_of<boost::mpl::_2,
                                        boost::mpl::_1>,
                                // Bases as * since for_each constructs them.
                                boost::add_pointer<boost::mpl::_2>
                            >
                        ,
                            overridden_bases_of<boost::mpl::_2, boost::mpl::_1>
                        >
                    >
                >::type type;
            };
        public:
            typedef typename boost::mpl::eval_if<
                    boost::contract::access::has_base_types<Class>,
                search_bases
            ,
                boost::mpl::identity<Result> // Return result (stop recursion).
            >::type type;
        };
        
        typedef typename boost::mpl::eval_if<boost::is_same<O, none>,
            boost::mpl::vector<>
        ,
            overridden_bases_of<C>
        >::type overridden_bases;

        #ifndef BOOST_CONTRACT_PERMISSIVE
            BOOST_STATIC_ASSERT_MSG(
                (boost::mpl::or_<
                    boost::is_same<O, none>,
                    boost::mpl::not_<boost::mpl::empty<overridden_bases> >
                >::value),
                "subcontracting function specified as 'override' but does not "
                "override any contracted member function"
            );
        #endif
    #else
        typedef boost::mpl::vector<> overridden_bases;
    #endif

public:
    explicit cond_subcontracting(
        boost::contract::from from,
        boost::contract::virtual_* v,
        C* obj,
        VR&
        #ifndef BOOST_CONTRACT_NO_POSTCONDITIONS // Avoid unused param warning.
            r
        #endif
        BOOST_CONTRACT_DETAIL_TVARIADIC_COMMA(BOOST_CONTRACT_MAX_ARGS)
        BOOST_CONTRACT_DETAIL_TVARIADIC_FPARAMS_Z(1,
                BOOST_CONTRACT_MAX_ARGS, Args, &, args)
    ) :
        cond_inv<VR, C>(from, obj)
        #ifndef BOOST_CONTRACT_NO_POSTCONDITIONS
            , r_(r)
        #endif
        #ifndef BOOST_CONTRACT_NO_CONDITIONS
            BOOST_CONTRACT_DETAIL_TVARIADIC_COMMA(BOOST_CONTRACT_MAX_ARGS)
            BOOST_CONTRACT_DETAIL_TVARIADIC_TUPLE_INIT_Z(1,
                    BOOST_CONTRACT_MAX_ARGS, args_, args)
        #endif
    {
        #ifndef BOOST_CONTRACT_NO_CONDITIONS
            if(v) {
                base_call_ = true;
                v_ = v; // Invariant: v_ never null if base_call_.
                BOOST_CONTRACT_DETAIL_DEBUG(v_);
            } else {
                base_call_ = false;
                if(!boost::mpl::empty<overridden_bases>::value) {
                    v_ = new boost::contract::virtual_(
                            boost::contract::virtual_::no_action);
                    #ifndef BOOST_CONTRACT_NO_POSTCONDITIONS
                        v_->result_ptr_ = &r_;
                        v_->result_type_name_ = typeid(VR).name();
                        v_->result_optional_ = is_optional<VR>::value;
                    #endif
                } else v_ = 0;
            }
        #endif
    }

    #ifndef BOOST_CONTRACT_NO_CONDITIONS
        virtual ~cond_subcontracting() BOOST_NOEXCEPT_IF(false) {
            if(!base_call_) delete v_;
        }
    #endif

protected:
    #ifndef BOOST_CONTRACT_NO_OLDS
        void init_subcontracted_old() {
            // Old values of overloaded func on stack (so no `f` param here).
            exec_and(boost::contract::virtual_::push_old_init_copy);
        }
    #endif
    
    #ifndef BOOST_CONTRACT_NO_ENTRY_INVARIANTS
        void check_subcontracted_entry_inv() {
            exec_and(boost::contract::virtual_::check_entry_inv,
                    &cond_subcontracting::check_entry_inv);
        }
    #endif
    
    #ifndef BOOST_CONTRACT_NO_PRECONDITIONS
        void check_subcontracted_pre() {
            exec_or(
                boost::contract::virtual_::check_pre,
                &cond_subcontracting::check_pre,
                &boost::contract::precondition_failure
            );
        }
    #endif

    #ifndef BOOST_CONTRACT_NO_OLDS
        void copy_subcontracted_old() {
            exec_and(boost::contract::virtual_::call_old_ftor,
                    &cond_subcontracting::copy_virtual_old);
        }
    #endif

    #ifndef BOOST_CONTRACT_NO_EXIT_INVARIANTS
        void check_subcontracted_exit_inv() {
            exec_and(boost::contract::virtual_::check_exit_inv,
                    &cond_subcontracting::check_exit_inv);
        }
    #endif

    #ifndef BOOST_CONTRACT_NO_POSTCONDITIONS
        void check_subcontracted_post() {
            exec_and(boost::contract::virtual_::check_post,
                    &cond_subcontracting::check_virtual_post);
        }
    #endif

    #ifndef BOOST_CONTRACT_NO_EXCEPTS
        void check_subcontracted_except() {
            exec_and(boost::contract::virtual_::check_except,
                    &cond_subcontracting::check_virtual_except);
        }
    #endif

    #ifndef BOOST_CONTRACT_NO_CONDITIONS
        bool base_call() const { return base_call_; }

        bool failed() const /* override */ {
            if(v_) return v_->failed_;
            else return cond_base::failed();
        }

        void failed(bool value) /* override */ {
            if(v_) v_->failed_ = value;
            else cond_base::failed(value);
        }
    #endif

private:
    #ifndef BOOST_CONTRACT_NO_OLDS
        void copy_virtual_old() {
            boost::contract::virtual_::action_enum a;
            if(base_call_) {
                a = v_->action_;
                v_->action_ = boost::contract::virtual_::push_old_ftor_copy;
            }
            this->copy_old();
            if(base_call_) v_->action_ = a;
        }
            
        void pop_base_old() {
            if(base_call_) {
                boost::contract::virtual_::action_enum a = v_->action_;
                v_->action_ = boost::contract::virtual_::pop_old_ftor_copy;
                this->copy_old();
                v_->action_ = a;
            } // Else, do nothing (for base calls only).
        }
    #endif

    #ifndef BOOST_CONTRACT_NO_POSTCONDITIONS
        void check_virtual_post() {
            pop_base_old();
            typedef typename boost::remove_reference<typename
                    optional_value_type<VR>::type>::type r_type;
            boost::optional<r_type const&> r; // No result copy in this code.
            if(!base_call_) r = optional_get(r_);
            else if(v_->result_optional_) {
                try {
                    r = **boost::any_cast<boost::optional<r_type>*>(
                            v_->result_ptr_);
                } catch(boost::bad_any_cast const&) {
                    try { // Handle optional<...&>.
                        r = **boost::any_cast<boost::optional<r_type&>*>(
                                v_->result_ptr_);
                    } catch(boost::bad_any_cast const&) {
                        try {
                            throw boost::contract::bad_virtual_result_cast(v_->
                                    result_type_name_, typeid(r_type).name());
                        } catch(...) {
                            this->fail(&boost::contract::postcondition_failure);
                        }
                    }
                }
            } else {
                try {
                    r = *boost::any_cast<r_type*>(v_->result_ptr_);
                } catch(boost::bad_any_cast const&) {
                    try {
                        throw boost::contract::bad_virtual_result_cast(
                                v_->result_type_name_, typeid(r_type).name());
                    } catch(...) {
                        this->fail(&boost::contract::postcondition_failure);
                    }
                }
            }
            check_virtual_post_with_result<VR>(r);
        }

        template<typename R_, typename Result>
        typename boost::enable_if<is_optional<R_> >::type
        check_virtual_post_with_result(Result const& r) {
            this->check_post(r);
        }
        
        template<typename R_, typename Result>
        typename boost::disable_if<is_optional<R_> >::type
        check_virtual_post_with_result(Result const& r) {
            BOOST_CONTRACT_DETAIL_DEBUG(r);
            this->check_post(*r);
        }
    #endif
    
    #ifndef BOOST_CONTRACT_NO_EXCEPTS
        void check_virtual_except() {
            pop_base_old();
            this->check_except();
        }
    #endif

    #if     !defined(BOOST_CONTRACT_NO_INVARIANTS) || \
            !defined(BOOST_CONTRACT_NO_POSTCONDITIONS) || \
            !defined(BOOST_CONTRACT_NO_EXCEPTS)
        void exec_and( // Execute action in short-circuit logic-and with bases.
            boost::contract::virtual_::action_enum a,
            void (cond_subcontracting::* f)() = 0
        ) {
            if(failed()) return;
            if(!base_call_ || v_->action_ == a) {
                if(!base_call_ && v_) {
                    v_->action_ = a;
                    boost::mpl::for_each<overridden_bases>(call_base(*this));
                }
                if(f) (this->*f)();
                if(base_call_) {
                    throw cond_subcontracting_::signal_no_error();
                }
            }
        }
    #endif

    #ifndef BOOST_CONTRACT_NO_PRECONDITIONS
        void exec_or( // Execute action in short-circuit logic-or with bases.
            boost::contract::virtual_::action_enum a,
            bool (cond_subcontracting::* f)(bool) = 0,
            void (*h)(boost::contract::from) = 0
        ) {
            if(failed()) return;
            if(!base_call_ || v_->action_ == a) {
                if(!base_call_ && v_) {
                    v_->action_ = a;
                    try { 
                        exec_or_bases<overridden_bases>();
                        return; // A base checked with no error (done).
                    } catch(...) {
                        bool checked =  f ? (this->*f)(
                                /* throw_on_failure = */ false) : false;
                        if(!checked) {
                            try { throw; } // Report latest exception found.
                            catch(...) { this->fail(h); }
                        }
                        return; // Checked and no exception (done).
                    }
                }
                bool checked = f ?
                        (this->*f)(/* throw_on_failure = */ base_call_) : false;
                if(base_call_) {
                    if(!checked) {
                        throw cond_subcontracting_::signal_not_checked();
                    }
                    throw cond_subcontracting_::signal_no_error();
                }
            }
        }
        
        template<typename Bases>
        typename boost::enable_if<boost::mpl::empty<Bases>, bool>::type
        exec_or_bases() { return false; }

        template<typename Bases>
        typename boost::disable_if<boost::mpl::empty<Bases>, bool>::type
        exec_or_bases() {
            if(boost::mpl::empty<Bases>::value) return false;
            try {
                call_base(*this)(typename boost::mpl::front<Bases>::type());
            } catch(cond_subcontracting_::signal_not_checked const&) {
                return exec_or_bases<
                        typename boost::mpl::pop_front<Bases>::type>();
            } catch(...) {
                bool checked = false;
                try {
                    checked = exec_or_bases<
                            typename boost::mpl::pop_front<Bases>::type>();
                } catch(...) { checked = false; }
                if(!checked) throw;
            }
            return true;
        }
    #endif
    
    #ifndef BOOST_CONTRACT_NO_CONDITIONS
        class call_base { // Copyable (as &).
        public:
            explicit call_base(cond_subcontracting& me) : me_(me) {}

            template<class B>
            void operator()(B*) {
                BOOST_CONTRACT_DETAIL_DEBUG(me_.object());
                BOOST_CONTRACT_DETAIL_DEBUG(me_.v_);
                BOOST_CONTRACT_DETAIL_DEBUG(me_.v_->action_ !=
                        boost::contract::virtual_::no_action);
                try {
                    call<B>(BOOST_CONTRACT_DETAIL_TVARIADIC_TUPLE_INDEXES_OF(
                            Args));
                } catch(cond_subcontracting_::signal_no_error const&) {
                    // No error (do not throw).
                }
            }

        private:
            template<
                class B
                // Can't use TVARIADIC_COMMA here.
                BOOST_PP_COMMA_IF(BOOST_CONTRACT_DETAIL_TVARIADIC)
                BOOST_CONTRACT_DETAIL_TVARIADIC_TUPLE_INDEXES_TPARAM(I)
            >
            void call(
                    BOOST_CONTRACT_DETAIL_TVARIADIC_TUPLE_INDEXES_FPARAM(I)) {
                O::template BOOST_CONTRACT_DETAIL_NAME1(call_base)<B>(
                    me_.v_,
                    me_.object()
                    BOOST_CONTRACT_DETAIL_TVARIADIC_COMMA(
                            BOOST_CONTRACT_MAX_ARGS)
                    BOOST_CONTRACT_DETAIL_TVARIADIC_TUPLE_ELEMS_Z(1,
                            BOOST_CONTRACT_MAX_ARGS, I, me_.args_)
                );
            }
            
            cond_subcontracting& me_;
        };
    #endif

    #ifndef BOOST_CONTRACT_NO_POSTCONDITIONS
        VR& r_;
    #endif
    #ifndef BOOST_CONTRACT_NO_CONDITIONS
        boost::contract::virtual_* v_;
        bool base_call_;
        BOOST_CONTRACT_DETAIL_TVARIADIC_TUPLE_Z(1,
                BOOST_CONTRACT_MAX_ARGS, Args, &, args_)
    #endif
};

} } } // namespace

#endif // #include guard


/* cond_subcontracting.hpp
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
*/