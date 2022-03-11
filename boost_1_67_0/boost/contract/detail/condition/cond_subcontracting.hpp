
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