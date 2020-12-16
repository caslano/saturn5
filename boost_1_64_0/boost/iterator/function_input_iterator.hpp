// Copyright 2009 (C) Dean Michael Berris <me@deanberris.com>
// Copyright 2012 (C) Google, Inc.
// Copyright 2012 (C) Jeffrey Lee Hellrung, Jr.
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_FUNCTION_INPUT_ITERATOR
#define BOOST_FUNCTION_INPUT_ITERATOR

#include <boost/config.hpp>
#include <boost/assert.hpp>
#include <boost/core/addressof.hpp>
#include <boost/mpl/if.hpp>
#include <boost/function_types/is_function_pointer.hpp>
#include <boost/function_types/result_type.hpp>
#include <boost/iterator/iterator_facade.hpp>
#include <boost/none.hpp>
#include <boost/optional/optional.hpp>
#include <boost/utility/result_of.hpp>

#ifdef BOOST_RESULT_OF_USE_TR1
#include <boost/type_traits/is_function.hpp>
#endif

namespace boost {

namespace iterators {

    namespace impl {

        // Computes the return type of an lvalue-call with an empty argument,
        // i.e. decltype(declval<F&>()()). F should be a nullary lvalue-callable
        // or function.
        template <class F>
        struct result_of_nullary_lvalue_call
        {
            typedef typename result_of<
#ifdef BOOST_RESULT_OF_USE_TR1
                typename mpl::if_<is_function<F>, F&, F>::type()
#else
                F&()
#endif
            >::type type;
        };

        template <class Function, class Input>
        class function_input_iterator
            : public iterator_facade<
            function_input_iterator<Function, Input>,
            typename result_of_nullary_lvalue_call<Function>::type,
            single_pass_traversal_tag,
            typename result_of_nullary_lvalue_call<Function>::type const &
            >
        {
        public:
            function_input_iterator() {}
            function_input_iterator(Function & f_, Input state_ = Input())
                : f(boost::addressof(f_)), state(state_) {}

            void increment() {
                if(value)
                    value = none;
                else
                    (*f)();
                ++state;
            }

            typename result_of_nullary_lvalue_call<Function>::type const &
                dereference() const {
                    return (value ? value : value = (*f)()).get();
            }

            bool equal(function_input_iterator const & other) const {
                return f == other.f && state == other.state;
            }

        private:
            Function * f;
            Input state;
            mutable optional<typename result_of_nullary_lvalue_call<Function>::type> value;
        };

        template <class Function, class Input>
        class function_pointer_input_iterator
            : public iterator_facade<
            function_pointer_input_iterator<Function, Input>,
            typename function_types::result_type<Function>::type,
            single_pass_traversal_tag,
            typename function_types::result_type<Function>::type const &
            >
        {
        public:
            function_pointer_input_iterator() {}
            function_pointer_input_iterator(Function &f_, Input state_ = Input())
                : f(f_), state(state_) {}

            void increment() {
                if(value)
                    value = none;
                else
                    (*f)();
                ++state;
            }

            typename function_types::result_type<Function>::type const &
                dereference() const {
                    return (value ? value : value = (*f)()).get();
            }

            bool equal(function_pointer_input_iterator const & other) const {
                return f == other.f && state == other.state;
            }

        private:
            Function f;
            Input state;
            mutable optional<typename function_types::result_type<Function>::type> value;
        };

    } // namespace impl

    template <class Function, class Input>
    class function_input_iterator
        : public mpl::if_<
            function_types::is_function_pointer<Function>,
            impl::function_pointer_input_iterator<Function,Input>,
            impl::function_input_iterator<Function,Input>
        >::type
    {
        typedef typename mpl::if_<
            function_types::is_function_pointer<Function>,
            impl::function_pointer_input_iterator<Function,Input>,
            impl::function_input_iterator<Function,Input>
        >::type base_type;
    public:
        function_input_iterator(Function & f, Input i)
            : base_type(f, i) {}
    };

    template <class Function, class Input>
    inline function_input_iterator<Function, Input>
        make_function_input_iterator(Function & f, Input state) {
            typedef function_input_iterator<Function, Input> result_t;
            return result_t(f, state);
    }

    template <class Function, class Input>
    inline function_input_iterator<Function*, Input>
        make_function_input_iterator(Function * f, Input state) {
            typedef function_input_iterator<Function*, Input> result_t;
            return result_t(f, state);
    }

    struct infinite {
        infinite & operator++() { return *this; }
        infinite & operator++(int) { return *this; }
        bool operator==(infinite &) const { return false; };
        bool operator==(infinite const &) const { return false; };
    };

} // namespace iterators

using iterators::function_input_iterator;
using iterators::make_function_input_iterator;
using iterators::infinite;

} // namespace boost

#endif


/* function_input_iterator.hpp
8CHgGuCjwBuBrwJvAr4HrALuUtcGfgBcB9wHvAV4AHgr8BDw58C/AtcD1X15G7A18E5VPuDdwNOA1cBewHuAfYC/BI4B3gcsAF4HLAJuBK4A3gtcA0R9uK8t6HfefXOrfPa1/YD33W+BUUqFgE2UbgCdDHvyyThBPu8xn1rms5P57GA+O5nPSlAW8/kd84kBXcF82oKvKbAzsB0wGZgC7AocDOwGHAbsDhwDPJ362J3362nA54E9ga8BU4A7FB/boxdwjwqzPAO1zT3eIVieCJWO5bmf/iVxL0u9HqKfyUd4P20GVTP9WqaPlfPuo5XDXZ/WwHhgArA7sI3DXa9E4BnAdsCBqnzAIUD0wVK/zsCJwC7ADGAS8AKGZwI7AS9kOE/JC5iv5AUsZn5lSj7AVcAewDWMZ/lpAw5dtik/2kjK/wfuI/BHy11+6LSUf7/lLv+fuI/AUe4j8GfLXf6DfJ4d4vPsU+AFDKvyfwa8kGFV/s+5L8IXwALmVwLEvSL35ZfAGxjP8tN2GmW3Kf8xlv84y/8ty/8dy/89y++g/F2UfxjlH0n5R1H+jSj/KMq/MeUfRfk3ofybAouYX6l8G3aXuxlwNeNV+bdpm2M8w1n+eNAWln8Y9WcksCVwFFDV73xgAnA0sCNwDLAT47sCxwJ7AccD+wEnAAcBJwKHAc8FnsPwJOAk4BTgZOAM5pMFPA94B3AK8G7gNGANzz8NnAp8VsKsT5jHhlJsXqU+fE7IsQp8HYCrgX2BN1Pe64DDgbcCzwPeBrwUeAdwIfBO4BLgL4ArgHdRn+8G3gSsBt4OvAf4IPBe4GPAGNznSq73I/wS8AHgq+o+Br6r9AT4AXATcDfwUWAdsAa4D/g48HPgE8BjwF8DY1G5p4GJwM2qPsBngEnA54ApwC2qPsAXVH2AW4HTga+oegFfAy4GvgFcBnxT6QfwLeDPgG8Dfw7cDqwGvgPcAHxXyR1YC3we+D5wK3AH8GXgTlUv4C7gTuAHwP3A3wI/Be4BfgX8CGihTT4GRgHrgHHAPwDbA/cBewH3A88EfgIcCPwTcAjwgKof8FPgROBnqp7Ag8CpwEPA84GfAy8AfgGcCTwMzAEeAV4CPAq8FvgVcDnw78D1wGPAh4H/UPUFfg18HfgN8C3gceB24LeqvsDvgLXA74E7gBbafS8wHFgHVO38V6AT4a+BzYCOcLd+uIBRwHhgE2AnxvN5BVu/wM+rVD6vBvB5NYjPq8F8Xp3N59UQPq9GAscxnAEcxufVcD6vRvB5NZLPqzQ+r0ayPOke2yraaVX5+ENuAT5V/Vi+D8fxPTgemARszffhBOa3FZTG/PYxP45H5Mhk/3MJn1/zgKlA6LDUbyVwKLCI/Ugx+5Fy4HSenwlcDJwHrAAWAJcAF/B8OfBy4FqGbwZWAjcCrwH+Gnidan/gcuBHwBXAP5Bf1eOYtnGRvlbq0Q500DPPy+c4+mqRy0Ucd2VxX5xsYFvgxRyH5QLPAuYB+wHn8vmGdpd+9BLgGoZvBOYD1ym5ANcz/jbgfI7TCoD3Mf5+YBHwZeBlwNcYr+pXwv1ySoG7gAuBh8n3N/IdUfIEfsOwqn+1tutA38N2FDts1n8g9wcaBnQBhwO7AkcAewBHAYcxPBY4ms/hMdz3B3Hof0X/ZJwzns/jc/k8nkh5TAOqskxnfc8DbmSY71u0S4BO2rxvrWA7rQTGAK9nO60yxpFbmT7aZhx5I9PfxOc+zuv311qmO8Pm/fVmUTnIi9e9BdgGeCvwdODPmQ/0hd/sURbm00TqzTlyXr+S+zItZX7XUu+uAXYALlPyZ7gHw2eSzzOey+B1Gsl9V388F2PwZQXJVxIkX2U=
*/