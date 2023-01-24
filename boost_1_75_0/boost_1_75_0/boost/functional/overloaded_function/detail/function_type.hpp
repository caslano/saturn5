
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
8bGAq91mmUhXn63P8dFoEvo2VFGBpJr/Ole2pQhlGy9KkbstOUW5Plj7r5dxnhRSRAxnIgH6tYGbTJa0NlM17yLuYiSl5YJMPoWddBbq9Lm5ZKiicDwVWSYa7AoF4oSYjIVVeW5MBIKhdvJRLowP0rLX5/Vnpa7XjYNYh4NA3dVGVqdhqgJqJ/DblvbnuVfN4VPDhasUq8omtn6eCjjayAh59SKhSH1b5NDpkvJ97gdQkYS9MNwOH0Z+Gag04x6eGoZf+5HA8N4fcf0Pf677gp7WjxDjv6IDPpSXvvuFapMzXB9cgedv+iJS3QYWvLs9CgGgCpwSXrQyEDUwvmUuaFCElr3saaOWPYv2xQVdcF9M6oL74u9TsZqW/ewcvZY9aa5ey96+ALQpK7mqllS2AO17nyUtO/yGOCmkZYdfGSnf0uVWcyQGC61CI12uuqOkxi/wvzdzn56dkfBrP0RIIOL9Fdfz3bTuKTKYyQen2zzH7LNMZjc9bks3l29ANJKf2gB5CViFxjQ0Pv3TbTVljWVErLC3nSIR5MvLJpIndFEkAHCDM6QSTVcRG2vkTvdB3Gi4j+fdpvef2eLqY694t4fJRJ1cjJ0A1vI9KPersCAuwI/Ga2Bw/bD7uzzoRpPVn6ZbGInmveGRBDQblPJJ5qUzkCzVgWQpB4m6K3ZEmBD09bpK9QJuuCdW8hqVuhqVogZdufMadboadaIj
*/