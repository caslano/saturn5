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
#include <boost/type_traits/conditional.hpp>
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
                typename boost::conditional<is_function<F>::value, F&, F>::type()
#else
                F&()
#endif
            >::type type;
        };

        template <class Function, class Input>
        class function_input_iterator :
            public iterator_facade<
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
        class function_pointer_input_iterator :
            public iterator_facade<
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
    class function_input_iterator :
        public boost::conditional<
            function_types::is_function_pointer<Function>::value,
            impl::function_pointer_input_iterator<Function,Input>,
            impl::function_input_iterator<Function,Input>
        >::type
    {
        typedef typename boost::conditional<
            function_types::is_function_pointer<Function>::value,
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

    struct infinite
    {
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
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
*/