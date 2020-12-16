
#ifndef BOOST_CONTRACT_DETAIL_DESTRUCTOR_HPP_
#define BOOST_CONTRACT_DETAIL_DESTRUCTOR_HPP_

// Copyright (C) 2008-2018 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0 (see accompanying
// file LICENSE_1_0.txt or a copy at http://www.boost.org/LICENSE_1_0.txt).
// See: http://www.boost.org/doc/libs/release/libs/contract/doc/html/index.html

#include <boost/contract/core/exception.hpp>
#include <boost/contract/core/config.hpp>
#include <boost/contract/detail/condition/cond_inv.hpp>
#include <boost/contract/detail/none.hpp>
#include <boost/contract/detail/exception.hpp>
#if     !defined(BOOST_CONTRACT_ALL_DISABLE_NO_ASSERTION) && ( \
        !defined(BOOST_CONTRACT_NO_INVARIANTS) || \
        !defined(BOOST_CONTRACT_NO_POSTCONDITIONS) || \
        !defined(BOOST_CONTRACT_NO_EXCEPTS))
    #include <boost/contract/detail/checking.hpp>
#endif
#if     !defined(BOOST_CONTRACT_NO_EXIT_INVARIANTS) || \
        !defined(BOOST_CONTRACT_NO_POSTCONDITIONS) || \
        !defined(BOOST_CONTRACT_NO_EXCEPTS)
    #include <boost/config.hpp>
    #include <exception>
#endif

namespace boost { namespace contract { namespace detail {

// Dtor subcontracting impl via C++ obj destruction mechanism.
template<class C> // Non-copyable base.
class destructor : public cond_inv</* VR = */ none, C> {
public:
    explicit destructor(C* obj) : cond_inv</* VR = */ none, C>(
            boost::contract::from_destructor, obj) {}

private:
    #if     !defined(BOOST_CONTRACT_NO_ENTRY_INVARIANTS) || \
            !defined(BOOST_CONTRACT_NO_OLDS)
        void init() /* override */ {
            #ifndef BOOST_CONTRACT_ALL_DISABLE_NO_ASSERTION
                if(checking::already()) return;
            #endif

            #ifndef BOOST_CONTRACT_NO_ENTRY_INVARIANTS
                {
                    #ifndef BOOST_CONTRACT_ALL_DISABLE_NO_ASSERTION
                        checking k;
                    #endif
                    // Obj exists (before dtor body), check static and non- inv.
                    this->check_entry_all_inv();
                    // Dtor cannot have pre because it has no parameters.
                }
            #endif
            #ifndef BOOST_CONTRACT_NO_OLDS
                this->copy_old();
            #endif
        }
    #endif
    
public:
    #if     !defined(BOOST_CONTRACT_NO_EXIT_INVARIANTS) || \
            !defined(BOOST_CONTRACT_NO_POSTCONDITIONS) || \
            !defined(BOOST_CONTRACT_NO_EXCEPTS)
        ~destructor() BOOST_NOEXCEPT_IF(false) {
            this->assert_initialized();
            #ifndef BOOST_CONTRACT_ALL_DISABLE_NO_ASSERTION
                if(checking::already()) return;
                checking k;
            #endif

            // If dtor body threw, obj still exists so check subcontracted
            // static and non- inv (but no post because of throw). Otherwise,
            // obj destructed so check static inv and post (even if there is no
            // obj after dtor body, this library allows dtor post, for example
            // to check static members for an instance counter class).
            // NOTE: In theory C++ destructors should not throw, but the
            // language allows for that (even if in C++11 dtors declarations are
            // implicitly noexcept(true) unless specified otherwise) so this
            // library must handle such a case.
            if(uncaught_exception()) {
                #ifndef BOOST_CONTRACT_NO_EXIT_INVARIANTS
                    this->check_exit_all_inv();
                #endif
                #ifndef BOOST_CONTRACT_NO_EXCEPTS
                    this->check_except();
                #endif
            } else {
                #ifndef BOOST_CONTRACT_NO_EXIT_INVARIANTS
                    this->check_exit_static_inv();
                #endif
                #ifndef BOOST_CONTRACT_NO_POSTCONDITIONS
                    this->check_post(none());
                #endif
            }
        }
    #endif
};

} } } // namespace

#endif // #include guard


/* destructor.hpp
8GQBurspMc9X04gr3IQNJbYb+Sn6lljDBt6djy16sxY27BLoR/8z6oDVLgDTIS8vw2MLHsGfWw9/ImNfYOeGRtgq9vwMPlIe+8SaPwjGXcFcYUvqbICf4rD99H/bJmgldeDz6MJ2yGpL4oU3Mhfn0f5u3kc25kSAAQ+DAejrxfhRZczRo8zp0s/hFfBgHny0czy+MTzaGb6w8b/iG4C3+7Fn8BNsODHIXvjvreh7j+HQmLx+l6FXEsCj6MqxzOF3t6OrSb8O3fUyPlUEsdlh0H8ovJywGbyHnrm6BnJch/GDfxcXob/RuXLP3ZpY9E839FomPnYuceRlgvUn+A46HbyafTuMswHxteRyAaaHXsjtslJwFPTYhCxf3pd+gI8/ugPdkkScDR/CZiyXgYfGI9/ffEfZu9GTNYnPY8eGnI4OXIEsVDK34Lmsh8BVd2LfZoB1RsL3MpbhJRYvfSps7Tvgire+IZb8g4zNEOcB133xIj7zUmRoBriB39nEO+sz3sROjJm11Yww4sGV2Pzm2IkdYJpd+NDlYKV82vWAX+DBK33YsnfpF32/sTnY8jl00Bj2gBKDWz2DGPx7zEci+zfAfVkdsSHnoSfPt9X+sI7ov7Q76SdjBXKIUxnPr1tYw5Vx8+dlXIW4QAdkB0xaeBhsEo1Mf0mc4WePWgvaNBf7XQzGH4nOvQm9t4YylN21Dyx/kU1/0L3Q88rO1NcALMd8XdYDf7i+h/0m6O9a2PIjxPui0OE82+uQyaX4dvhtPR9A9tLBGdjyHhn4LpdCjzL01Ub4n/hVfjvWv8rA5/xuSt11iZkMZ56e6gYdk7E9+NKrsoiRvEssFV12273oxZ/xKS3iZYtZu4G2YeCDBj9hk5Gd01ahW5/g/wF0mzxTdDM4uhD7Dc/sAr92ysMH/AsYZxI2uAh+IHZ7eybjQFee2hVe3MJ/4gg/r8MGThHir4PYX3EmtpJ4+dfEaMdHME+98SnQC1dFUuYSyndADhrDz3fKPS/sI6Cv+2rINQp0dhQ8jo+VtRr82hN9lwB/9cYmlPJ/IWNdgixBkz3XMdd1oeXfwfw874YvW2Oz1iYjAyvBcui/7mnI/zPYd/zHXOi/AmzY+Dzu3pwPbmTM9QZgL6FlfDt0BnJwxuPELWtCrz7EwRviKxJjaoWdLF0Lzxfy/g3oHcpV9CPm4GVf6iCwBjoiYTqxKXDfNngjSlD3jWD/q+AhxjMcvPVVbcZAvOiRfPhiK/UTnyj8iH18DYg/3MYegrPA0PBYJDQtu56YJBh04XfQ/maw6i5id03BhQVg2HuRF5s4GTZ/eBxxuBnQ/VzmEkz6aVvqbguPMu5LdxEXYl/FjT2xufDAUOx23+5C7fdJAftNwk5ciU0rsIhxEXecQowhWuBn4adU0HYU/uHH8FslaaeiX5JikdUd8GIKaynwyT3dmDvwxJtnYMPQQXe/jt5MYh2Hec5YQplbwe6sMU84DR7vin2H3+y7kXv2cBY8xfwOJqZcm9j+KuwRY1l9HbYC3NPvHfAcevMmeFJ0gMbLWJv4B1hQ7mfBFjT/G3NLrLtGHjYEfvwMeevcCpvOunfba8BR0DgGHZVOXpNziAOWQN8XwKm0P+kVdAtxwSOv4bc3RRcjb0/iQ4/IZs8YPHTLJDAgOvr9MsZ3O/NVBJ6U6xrF2KVnsQ1t8AvAiE/CRxHQLQNeTME2HsS2x2Af8leDxTYTb2jF+NFltzB2zwLiQ8xHXfTguFj0CbGz2OXYjUPIHbGCTh3AIFPBy9nsuY0Fw1Vgc99H94O3MicSL8TehFN3V3ihDrw77BHmnn1c6cTGt40Ew04Q7MUBd+L71WKspcStz5XrcV0=
*/