
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