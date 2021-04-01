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
ihsR4BD2nWG1SUP6dgHF98SFzzu5CbETkH1QJjqiHfgs+MfmcNJNPdijhICc2PKMK1Omkp4BXzIzubphh5EZ1HgLHLVAm2L8jAYYxNMI1BX1TBQIKCg6YTPNuuQ/Nas8iIX4vY9B/SlJcgXM7p4G8US3ly3QszGIrE6WGJmIgmSbvsajvU1rNWl5YyXuhMpIWdf2K9/JKI4GswHaGjh5DCOzJDf3fQUPOvfuaKEnMD7e4W3FJHZfSisHnk89uAGre6t7g69grg6eZUphOXe2rTiVUQm1Kt5yLKIdc1LnD3CZBWz34QccfPJCdtwdbIZo5/iGn1WzO1ibmj6qMA3EknSINef0e8ofDEWa/YmSmoWXNE24aURk+dPi1xt3sALCi3VDpVX5NzJdKcX5ET6M0NPmrYz2DESmzpvQUTXF6y+LsdpL1as33LZWgg4ku2ryzUjalASuu2r9AeFBWoJsWKkSCFgdr22Oa0mG/clmN2GINHCq3CegNPIWnvjNUxjYq6Nr4QVewrpH8wQor7tVtC3eUHYXVhw+kv18pCWLwwthgY5FH2Au+Ya3CA==
*/