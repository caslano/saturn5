
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