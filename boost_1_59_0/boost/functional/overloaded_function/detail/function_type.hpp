
// Copyright (C) 2009-2012 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0
// (see accompanying file LICENSE_1_0.txt or a copy at
// http://www.boost.org/LICENSE_1_0.txt)
// Home at http://www.boost.org/libs/functional/overloaded_function

#ifndef BOOST_FUNCTIONAL_OVERLOADED_FUNCTION_DETAIL_FUNCTION_TYPE_HPP_
#define BOOST_FUNCTIONAL_OVERLOADED_FUNCTION_DETAIL_FUNCTION_TYPE_HPP_

#include <boost/function_types/is_function.hpp>
#include <boost/function_types/is_function_pointer.hpp>
#include <boost/function_types/is_function_reference.hpp>
#include <boost/function_types/function_type.hpp>
#include <boost/function_types/parameter_types.hpp>
#include <boost/function_types/result_type.hpp>
#include <boost/type_traits/remove_pointer.hpp>
#include <boost/type_traits/remove_reference.hpp>
#include <boost/function.hpp>
#include <boost/mpl/if.hpp>
#include <boost/mpl/identity.hpp>
#include <boost/mpl/pop_front.hpp>
#include <boost/mpl/push_front.hpp>
#include <boost/typeof/typeof.hpp>

// Do not use namespace ::detail because overloaded_function is already a class.
namespace boost { namespace overloaded_function_detail {

// Requires: F is a monomorphic functor (i.e., has non-template `operator()`).
// Returns: F's function type `result_type (arg1_type, arg2_type, ...)`.
// It does not assume F typedef result_type, arg1_type, ... but needs typeof.
template<typename F>
class functor_type {
    // NOTE: clang does not accept extra parenthesis `&(...)`.
    typedef BOOST_TYPEOF_TPL(&F::operator()) call_ptr;
public:
    typedef
        typename boost::function_types::function_type<
            typename boost::mpl::push_front<
                  typename boost::mpl::pop_front< // Remove functor type (1st).
                    typename boost::function_types::parameter_types<
                            call_ptr>::type
                  >::type
                , typename boost::function_types::result_type<call_ptr>::type
            >::type
        >::type
    type;
};

// NOTE: When using boost::function in Boost.Typeof emulation mode, the user
// has to register boost::functionN instead of boost::function in oder to
// do TYPEOF(F::operator()). That is confusing, so boost::function is handled
// separately so it does not require any Boost.Typeof registration at all.
template<typename F>
struct functor_type< boost::function<F> > {
    typedef F type;
};

// Requires: F is a function type, pointer, reference, or monomorphic functor.
// Returns: F's function type `result_type (arg1_type, arg2_type, ...)`.
template<typename F>
struct function_type {
    typedef
        typename boost::mpl::if_<boost::function_types::is_function<F>,
            boost::mpl::identity<F>
        ,
            typename boost::mpl::if_<boost::function_types::
                    is_function_pointer<F>,
                boost::remove_pointer<F>
            ,
                typename boost::mpl::if_<boost::function_types::
                        is_function_reference<F>,
                    boost::remove_reference<F>
                , // Else, requires that F is a functor.
                    functor_type<F>
                >::type
            >::type
        >::type
    ::type type;
};

} } // namespace

#endif // #include guard


/* function_type.hpp
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
*/