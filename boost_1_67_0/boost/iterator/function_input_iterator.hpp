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
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
*/