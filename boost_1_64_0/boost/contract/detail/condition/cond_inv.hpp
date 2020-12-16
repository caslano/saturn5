
#ifndef BOOST_CONTRACT_DETAIL_COND_INV_HPP_
#define BOOST_CONTRACT_DETAIL_COND_INV_HPP_

// Copyright (C) 2008-2018 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0 (see accompanying
// file LICENSE_1_0.txt or a copy at http://www.boost.org/LICENSE_1_0.txt).
// See: http://www.boost.org/doc/libs/release/libs/contract/doc/html/index.html

#include <boost/contract/core/exception.hpp>
#include <boost/contract/core/config.hpp>
#include <boost/contract/detail/condition/cond_post.hpp>
#ifndef BOOST_CONTRACT_NO_INVARIANTS
    #include <boost/contract/core/access.hpp>
    #include <boost/type_traits/add_pointer.hpp>
    #include <boost/type_traits/is_volatile.hpp>
    #include <boost/mpl/vector.hpp>
    #include <boost/mpl/transform.hpp>
    #include <boost/mpl/for_each.hpp>
    #include <boost/mpl/copy_if.hpp>
    #include <boost/mpl/eval_if.hpp>
    #include <boost/mpl/not.hpp>
    #include <boost/mpl/and.hpp>
    #include <boost/mpl/placeholders.hpp>
    #include <boost/utility/enable_if.hpp>
    #ifndef BOOST_CONTRACT_PERMISSIVE
        #include <boost/function_types/property_tags.hpp>
        #include <boost/static_assert.hpp>
    #endif
#endif

namespace boost { namespace contract { namespace detail {

template<typename VR, class C>
class cond_inv : public cond_post<VR> { // Non-copyable base.
    #if     !defined(BOOST_CONTRACT_NO_INVARIANTS) && \
            !defined(BOOST_CONTRACT_PERMISSIVE)
        BOOST_STATIC_ASSERT_MSG(
            (!boost::contract::access::has_static_invariant_f<
                C, void, boost::mpl:: vector<>
            >::value),
            "static invariant member function cannot be mutable "
            "(it must be static instead)"
        );
        BOOST_STATIC_ASSERT_MSG(
            (!boost::contract::access::has_static_invariant_f<
                C, void, boost::mpl::vector<>,
                        boost::function_types::const_non_volatile
            >::value),
            "static invariant member function cannot be const qualified "
            "(it must be static instead)"
        );
        BOOST_STATIC_ASSERT_MSG(
            (!boost::contract::access::has_static_invariant_f<
                C, void, boost::mpl::vector<>,
                        boost::function_types::volatile_non_const
            >::value),
            "static invariant member function cannot be volatile qualified "
            "(it must be static instead)"
        );
        BOOST_STATIC_ASSERT_MSG(
            (!boost::contract::access::has_static_invariant_f<
                C, void, boost::mpl::vector<>,
                        boost::function_types::cv_qualified
            >::value),
            "static invariant member function cannot be const volatile "
            "qualified (it must be static instead)"
        );

        BOOST_STATIC_ASSERT_MSG(
            (!boost::contract::access::has_invariant_s<
                C, void, boost::mpl::vector<>
            >::value),
            "non-static invariant member function cannot be static "
            "(it must be either const or const volatile qualified instead)"
        );
        BOOST_STATIC_ASSERT_MSG(
            (!boost::contract::access::has_invariant_f<
                C, void, boost::mpl::vector<>,
                        boost::function_types::non_cv
            >::value),
            "non-static invariant member function cannot be mutable "
            "(it must be either const or const volatile qualified instead)"
        );
        BOOST_STATIC_ASSERT_MSG(
            (!boost::contract::access::has_invariant_f<
                C, void, boost::mpl::vector<>,
                        boost::function_types::volatile_non_const
            >::value),
            "non-static invariant member function cannot be volatile qualified "
            "(it must be const or const volatile qualified instead)"
        );
    #endif

public:
    // obj can be 0 for static member functions.
    explicit cond_inv(boost::contract::from from, C* obj) :
        cond_post<VR>(from)
        #ifndef BOOST_CONTRACT_NO_CONDITIONS
            , obj_(obj)
        #endif
    {}
    
protected:
    #ifndef BOOST_CONTRACT_NO_ENTRY_INVARIANTS
        void check_entry_inv() { check_inv(true, false, false); }
        void check_entry_static_inv() { check_inv(true, true, false); }
        void check_entry_all_inv() { check_inv(true, false, true); }
    #endif
    
    #ifndef BOOST_CONTRACT_NO_EXIT_INVARIANTS
        void check_exit_inv() { check_inv(false, false, false); }
        void check_exit_static_inv() { check_inv(false, true, false); }
        void check_exit_all_inv() { check_inv(false, false, true); }
    #endif

    #ifndef BOOST_CONTRACT_NO_CONDITIONS
        C* object() { return obj_; }
    #endif

private:
    #ifndef BOOST_CONTRACT_NO_INVARIANTS
        // Static, cv, and const inv in that order as strongest qualifier first.
        void check_inv(bool on_entry, bool static_only, bool const_and_cv) {
            if(this->failed()) return;
            try {
                // Static members only check static inv.
                check_static_inv<C>();
                if(!static_only) {
                    if(const_and_cv) {
                        check_cv_inv<C>();
                        check_const_inv<C>();
                    } else if(boost::is_volatile<C>::value) {
                        check_cv_inv<C>();
                    } else {
                        check_const_inv<C>();
                    }
                }
            } catch(...) {
                if(on_entry) {
                    this->fail(&boost::contract::entry_invariant_failure);
                } else this->fail(&boost::contract::exit_invariant_failure);
            }
        }
        
        template<class C_>
        typename boost::disable_if<
                boost::contract::access::has_const_invariant<C_> >::type
        check_const_inv() {}
        
        template<class C_>
        typename boost::enable_if<
                boost::contract::access::has_const_invariant<C_> >::type
        check_const_inv() { boost::contract::access::const_invariant(obj_); }
        
        template<class C_>
        typename boost::disable_if<
                boost::contract::access::has_cv_invariant<C_> >::type
        check_cv_inv() {}

        template<class C_>
        typename boost::enable_if<
                boost::contract::access::has_cv_invariant<C_> >::type
        check_cv_inv() { boost::contract::access::cv_invariant(obj_); }
        
        template<class C_>
        typename boost::disable_if<
                boost::contract::access::has_static_invariant<C_> >::type
        check_static_inv() {}
        
        template<class C_>
        typename boost::enable_if<
                boost::contract::access::has_static_invariant<C_> >::type
        check_static_inv() {
            // SFINAE HAS_STATIC_... returns true even when member is inherited
            // so extra run-time check here (not the same for non static).
            if(!inherited<boost::contract::access::has_static_invariant,
                    boost::contract::access::static_invariant_addr>::apply()) {
                boost::contract::access::static_invariant<C_>();
            }
        }

        // Check if class's func is inherited from its base types or not.
        template<template<class> class HasFunc, template<class> class FuncAddr>
        struct inherited {
            static bool apply() {
                try {
                    boost::mpl::for_each<
                        // For now, no reason to deeply search inheritance tree
                        // (SFINAE HAS_STATIC_... already fails in that case).
                        typename boost::mpl::transform<
                            typename boost::mpl::copy_if<
                                typename boost::mpl::eval_if<boost::contract::
                                        access::has_base_types<C>,
                                    typename boost::contract::access::
                                            base_types_of<C>
                                ,
                                    boost::mpl::vector<>
                                >::type,
                                HasFunc<boost::mpl::_1>
                            >::type,
                            boost::add_pointer<boost::mpl::_1>
                        >::type
                    >(compare_func_addr());
                } catch(signal_equal const&) { return true; }
                return false;
            }

        private:
            class signal_equal {}; // Except. to stop for_each as soon as found.

            struct compare_func_addr {
                template<typename B>
                void operator()(B*) {
                    // Inherited func has same addr as in its base.
                    if(FuncAddr<C>::apply() == FuncAddr<B>::apply()) {
                        throw signal_equal();
                    }
                }
            };
        };
    #endif

    #ifndef BOOST_CONTRACT_NO_CONDITIONS
        C* obj_;
    #endif
};

} } } // namespace

#endif // #include guard


/* cond_inv.hpp
xtw/4Zr7J415kuUe13P/lOqLO8+tc9x5hl115bntt8x7WvPKM/rvs/rvCh0XKjT4Y2U/oy5x7P6ZPOaM1znn1zHcX+4FV7nEY+1nKjdI7c1hT4UCeaEylJ/m8J7TF5P3noL3TmnEHnjSpU1/jr9Vec4jnv+9jhKrdF+nBgur9BcVdhViQp4TJ7TESyrNqzZ/SL5cVU2+fPkYfBmlbfkrJl9WE6OewJ6r76+odwNPVXl5taHvVrv03WsGz8q8NZr3/mbou9UGz6918fwbx3j/TfV+6LwrQ+aFxqWva330lrbBb2u+/ru73RD8utrg+Xf6meUC4wuZ96ZLJ76r+7DB0IlOeZMvbw6BN9fxOzAtWh+u1/pQJypduDGELlxfTZ577zg8Vweee9/kuWryzeAT8JwMmXv5Mo63wP+9Facad4bpL31g8OEHLj78yJhPmfeh5pXNBh9+YPDhJy4+/PQY73+m3nfnhba7H+t53qJ57HN3nSF47AODx7b3M8sF+h4y7zMXj32h295h8JhT3uSxJZrHVht2dyu/Q07KQT+/bXP4zV1A+zBfhuC9bdXkva+OwXuDtR3eafLev8g/Mw3+menin93GXMm8XXr+9xj8M9Pgn3+4+GfvMd7/Vr3vzjNttzsvtB77Rs/vPq3HvtM8tl+3y7vqfbef5K7bzX8zDf77oZ9ZLjD2kHnfuvjvR92/nwz+U+Wr4VMf4LfhWCof5GA1fBDJm99r3nRelvx4KAQ/fl9Nfvz5BPb3F5Mfq+kTH+ubLYP0jkF+KMzifB8/TbXhjoGbMXP2dcrDCFn5+tLjMv8dqwpzTsjzGTH3Zq51TyeO3ipEHH2o/j7+kZBxc9mO+Yorah66wLG/w/In1Ctl8jdDJkV0MC5vRQfXj5x1RTtaPioNMSQ3RK1l1OOcmfFEV9nj7+6KWvI1eunOUv0z+9HM6EfNavRjjO5HmNGPVqJd6NZCLQVWr6jqZ6TuV7lqpTAnn9v8jPVx8xneG6+e2+vYe22jf3VD8HSY1JAiVc1PHT0/nUJig8ACqpKiwJNeT6sbHfCh1G9nzk+LrqqHT48O6jxZrl60Xw+H6346dTk6r0G0UU4Y5XTdjr9ylq6vEf8NHaryuhh5Zh2OnxP6PbOP1feBAnQxfCB3htsHctow9fBO7QOdSrr0d+pHGzOgfaCGpLn0qGhMWl5WWZ5XbhTWaU3McheL36W1MdJG+biU3Od/bsozIXqle53n0qwJ3mBaQ9FM02ZqsHPKv2oebfhX6O0W0aH1tuS1uujtljpf8mCz4/DagOrpqmrJv+TVMwxeba35P/eE66Smznbp/UA7wbwzVb0lVXtAm1fo/SgRhow2+hPXnqV+axsu9ZvCJIEzXPC8upe8yLm2Lkedv/CPQ8+bkaPm2vk29llGX8P/AM+3r9qHYdIl1+e4VbvFifKKnWB7Z5vt/YE4g6N3LnPtp+kQfYx9Miexf0TyzDmaZ5x2zuXZbOc8npvofeqq7jyfV91Sw/v3qzPftW059gui/bcglJaTDYJis39+GRdD8GlLuTDXJ5vdiBEKbkWc6/+rzquZh76Nyo1D4aHzo/u1O05r0ZckxMbr8xj6Do1O9O84zam7MNCsdmdjvqyTHZEidbV6tn/NSdBOHaDwY0ufcxi+7D9DxpjMkI1H808EaNv1BLSdq2kbWW3ahmz05Mh87J4rvlhyEvSfIKfaW/4fZV/vsKr82+0ENC7VNO5ebRrrUf0hFla92//ySdDwGDP676Ri6vF4wKRtzxPQ9npN217Vpu0xRlsd6h6/1/sXngTNq8zwv5vWmiccmkZVU99eVG2aVhlNdWkZkCPz3MTKlsJ/73tk8Jtidwc=
*/