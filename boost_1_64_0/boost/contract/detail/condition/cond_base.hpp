
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
LoA2Rq+dtlR6hCiR6aQ5Zy/C7U4GLaN/TxNNBVfqsc8Pl3kz8nCs5Yk29aqZoGywshn9gnvHu2odNub335fwD9CgB/fpBzoyxP8BAZUX2U/SqiTYsunjOunOqTONs+X+0AuNsUf8SfzgnAmqULUGV07M9aQaoqQwt0hfN2ekMz4OeE7IKs3hHqqSrHIjDxoRRCzPzsPAq81wMaWlWZXyfh0dG+5ujCW8GvMQcv6qIUtyznrqOXPuJHK+nd7AwQLYozYhsFQv3jMxRB+enTUB6nDWGszvnzpnBkKvPZwEv6qzCYYd7huIxZhnuHLZpYz7mFWqv1/hpKmdgaKFPjse30/dP5ShfMFEdX+F+3xsegpemOFDZFRJkWf8dLuJ/VR5fSEKcqljWv2rzqfyXrzy9kdvkcblme5E/7zqesNU/KxkaKL//KIhQ2UlWfqO5CcbUrdeSx3hfJvHaLejaOeVvIYNyy7NL+E0ZDt8COI9sZVwtDeym+rGCcrQK/O7DpD0pPo4kP64+5hi9PH8E/SxVzX62MvVR3GSfRxs9NFZrxtSZf5czas+udKO9a26ar4refoSLZdXHEs3czNdRrLazpuU7yuVV1RUuio+UaGADk83dHiGbnfE8dtFpxWgOf2aW26qpb5I1erxiwTaHGq0OUy3ObOK3SjTd4CbtrdY3wVnns3MztEHwlVamqqrxEVnf/lM8hqJEkUPI1PlDSevlShRQc4R+mzmpca8t/vTxs6ZUz1ek08bniSf/iWELF1u9Pes48tS194nlqWuvV2y1Pgk++gN0ceRRh/PPoG8dz1xHyO70seT6dOZLX/fp1HmPJ+gT12q0acuKlbtwqmmLQkdk/TbjeE9urnWdVyZ0W7zs3+UafeM+0p0mroDabS+b1fiyhzGe6zaHdnKUTQJpAv/3YnhYT45p9WwifK+CXV+D553fncJD/6uYaT3qXEgcFfhaNVuvK9E36Gbp57TfXwLKnDnTr602a4z2GNkmorH+u8dGKNx4VhTd/+b6B8laoT8fjqo0+eAF1nl0MBTNJl+v7THsd8dlZXjzSaqql51HvSbSo8UaQzk/L7RiA+V8Ozs65J5xfyXe77GaXpQTr3j6OAyfp9vvF9+jPcr9PtOTOMstS8tVFlbTNBl3Xnm/rK2cn8ZDZaSLv+OV33irJd85m+lE59Rbam6VL/5rwPUlrgydDvm2qOmkRqjKje1n1kuQJeQec6YG+i+TtN9ne7QKMwsHzxzIP1J0YhzejIdOp8OR07itzOXcv7leuhk0giiFxf5sak3l4vXvP5taN6C/HKf3MVfv3Etawrlpjovq/psMUO2qy75Ly69WMj6PJST9RXIoy7e8bn+OGI2+XzSsrhMGlTVbkPrKsrp3Y2+7HhfQTxlZF6YpJbIlLxJ79rbV+ty1/C3WTV4M+q4PK2Qbn6OftN5dN4dcOx3vSDjIm9peXm+t1gZVlXF71KDsiXnZhZ95r/JKw4/qDxHfma55Od6g/9l3nWa/28w5GeWIT83ueTn5mO8f4t635XnlhfNZzdqPpujZeJWd50mjztjMnh8fj+zXKDvIfNucfH4bbrt2w0ed8qbPL5Q8/hMle7n59nV4OfT5b53Vc49qdQBr8+TvP77TMXzd7h5Hl6+MzQvK346BR6+y+ThP8hPscfn66q63kgx9L3ilQUG3y1w8d29xhzLvHs03yw0+G6BwXeLXHy3+Bjv36/ed+UZutjku/v03D+gdfCD7jpD8N0Cg+8e6meWC/Q9ZN79Lr5bqtt+2OA7p7zJd7e7dSv89FelWw2ya15aovWmkaH46JEQunNJNXXno8fgt1jNb8tMfvsDPHKNEZeRY3TiMoU=
*/