
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
hShpQDQkpT0pRpHjgO1FAY6Ts+UOzC8IX7ieA6O9o30s3o6IvYoXSbwOnWh7bPwNUEsDBAoAAAAIAC1nSlKpCdboOQQAAIcJAAAzAAkAY3VybC1tYXN0ZXIvZG9jcy9saWJjdXJsL29wdHMvQ1VSTE9QVF9TU0hfS0VZREFUQS4zVVQFAAG2SCRgrVVhb6NGEP3Orxi5Ui+2OLhcqqbpRadyNqlpfIAMvtSSJbSGJWwDLGIXJ1HT/97ZBTdKzlVy0mHZi5d5b2bfvh2szQgm3+0yLEUHL16J/iZ44bgHhS3/i6byMCBJHqD/IHCD4ytS2fCIekjG8CrUAxxpVDLkOlf3SfKKdBtVpPqxFXiTqFuc6ZEDfsqb+5ZdFxKOpmM4Pjv7Bd7C+3fHpybMSM1oCZGk9Za21yacZ3rmt4Lc3VmCfjSBSiCl9YQwLpgAwXN5S1oKeF+ylNaCZkAEZFSkLdviH1aDLCjkrKQwDcK15/9uwm3B0mLguecdiIJ3ZQYF2VFoaUrZrqdpSCuB58iA/BkTEjk7yXhtYXoKkraVGGhUEaQUHMiOsJJsMR2RUEjZiF9tO+3aEldiZzwVdrqXwipk9WxVa6ymIvfAGwmSQyeoCSrehIpnLFcjSoSTTbctmSjMx7IwYZ3ZvAVB
*/