
#ifndef BOOST_CONTRACT_DETAIL_COND_BASE_HPP_
#define BOOST_CONTRACT_DETAIL_COND_BASE_HPP_

// Copyright (C) 2008-2018 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0 (see accompanying
// file LICENSE_1_0.txt or a copy at http://www.boost.org/LICENSE_1_0.txt).
// See: http://www.boost.org/doc/libs/release/libs/contract/doc/html/index.html

// NOTE: It seemed not possible to implement this library without inheritance
// here because some sort of base type needs to be used to hold contract objects
// in instances of boost::contract::check while polymorphically calling
// init and destructor functions to check contracts at entry and exit. This
// could be possible without inheritance only if boost::contract::check was made
// a template type but that would complicate user code. In any case, early
// experimentation with removing this base class and its virtual methods did not
// seem to reduce compilation and/or run time.

#include <boost/contract/core/exception.hpp>
#include <boost/contract/core/config.hpp>
#if     !defined(BOOST_CONTRACT_NO_PRECONDITIONS) || \
        !defined(BOOST_CONTRACT_NO_OLDS) || \
        !defined(BOOST_CONTRACT_NO_EXEPTS)
    #include <boost/function.hpp>
#endif
#include <boost/noncopyable.hpp>
#ifndef BOOST_CONTRACT_ON_MISSING_CHECK_DECL
    #include <boost/assert.hpp>
#endif
#include <boost/config.hpp>

namespace boost { namespace contract { namespace detail {

class cond_base : // Base to hold all contract objects for RAII.
    private boost::noncopyable // Avoid copying possible user's ftor captures.
{
public:
    explicit cond_base(boost::contract::from from) :
          BOOST_CONTRACT_ERROR_missing_check_object_declaration(false)
        , init_asserted_(false)
        #ifndef BOOST_CONTRACT_NO_CONDITIONS
            , from_(from)
            , failed_(false)
        #endif
    {}
    
    // Can override for checking on exit, but should call assert_initialized().
    virtual ~cond_base() BOOST_NOEXCEPT_IF(false) {
        // Catch error (but later) even if overrides miss assert_initialized().
        if(!init_asserted_) assert_initialized();
    }

    void initialize() { // Must be called by owner ctor (i.e., check class).
        BOOST_CONTRACT_ERROR_missing_check_object_declaration = true;
        this->init(); // So all inits (pre, old, post) done after owner decl.
    }
    
    #ifndef BOOST_CONTRACT_NO_PRECONDITIONS
        template<typename F>
        void set_pre(F const& f) { pre_ = f; }
    #endif

    #ifndef BOOST_CONTRACT_NO_OLDS
        template<typename F>
        void set_old(F const& f) { old_ = f; }
    #endif

    #ifndef BOOST_CONTRACT_NO_EXCEPTS
        template<typename F>
        void set_except(F const& f) { except_ = f; }
    #endif

protected:
    void assert_initialized() { // Derived dtors must assert this at entry.
        init_asserted_ = true;
        #ifdef BOOST_CONTRACT_ON_MISSING_CHECK_DECL
            if(!BOOST_CONTRACT_ERROR_missing_check_object_declaration) {
                BOOST_CONTRACT_ON_MISSING_CHECK_DECL;
            }
        #else
            // Cannot use a macro instead of this ERROR_... directly here
            // because assert will not expand it in the error message.
            BOOST_ASSERT(BOOST_CONTRACT_ERROR_missing_check_object_declaration);
        #endif
    }
    
    virtual void init() {} // Override for checking on entry.
    
    // Return true if actually checked calling user ftor.
    #ifndef BOOST_CONTRACT_NO_PRECONDITIONS
        bool check_pre(bool throw_on_failure = false) {
            if(failed()) return true;
            try { if(pre_) pre_(); else return false; }
            catch(...) {
                // Subcontracted pre must throw on failure (instead of
                // calling failure handler) so to be checked in logic-or.
                if(throw_on_failure) throw;
                fail(&boost::contract::precondition_failure);
            }
            return true;
        }
    #endif

    #ifndef BOOST_CONTRACT_NO_OLDS
        void copy_old() {
            if(failed()) return;
            try { if(old_) old_(); }
            catch(...) { fail(&boost::contract::old_failure); }
        }
    #endif

    #ifndef BOOST_CONTRACT_NO_EXCEPTS
        void check_except() {
            if(failed()) return;
            try { if(except_) except_(); }
            catch(...) { fail(&boost::contract::except_failure); }
        }
    #endif
    
    #ifndef BOOST_CONTRACT_NO_CONDITIONS
        void fail(void (*h)(boost::contract::from)) {
            failed(true);
            if(h) h(from_);
        }
    
        // Virtual so overriding pub func can use virtual_::failed_ instead.
        virtual bool failed() const { return failed_; }
        virtual void failed(bool value) { failed_ = value; }
    #endif

private:
    bool BOOST_CONTRACT_ERROR_missing_check_object_declaration;
    bool init_asserted_; // Avoid throwing twice from dtors (undef behavior).
    #ifndef BOOST_CONTRACT_NO_CONDITIONS
        boost::contract::from from_;
        bool failed_;
    #endif
    // Following use Boost.Function to handle also lambdas, binds, etc.
    #ifndef BOOST_CONTRACT_NO_PRECONDITIONS
        boost::function<void ()> pre_;
    #endif
    #ifndef BOOST_CONTRACT_NO_OLDS
        boost::function<void ()> old_;
    #endif
    #ifndef BOOST_CONTRACT_NO_EXCEPTS
        boost::function<void ()> except_;
    #endif
};

} } } // namespace

#endif // #include guard


/* cond_base.hpp
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
*/