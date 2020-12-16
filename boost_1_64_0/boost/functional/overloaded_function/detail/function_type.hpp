
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
laQluxgCPpdNdqoH0rFDbBpca2hBjMcsknIw7en8BLqwH+7yWjSLx3gR+CjdC15wEXL5iBfo1Nwg9/wi5ymvV6zs2pHibeixUoW03ShemQh4Qbl87l9Zre+076U3SbOh7Hzlc3iWd9nXw/2ld9LTPPTd5FnfcR+RXnPJslKcyNz6ivaR2gBAXbsRr7PrgSvgxB47DCscm2iwW5PBE48/+CtJo2loxWmss/j604FjUYIBpzzx+p3i9UbveMkmQj7qj9ZIP5w9lf92MxkT6UesxizuqJDwvoB+CceQ62JEp23Dpqez7duz4X3CwkByrksefPHPGecnIJciCLIAgwLwGw0K4Y8Bzz/K4eZUwNv/AbAI+IUJAuU7/NG8CAi+/99//4j+B6W71/Pb/0X+3v4Hvv/hjX39R//n/pfPTv4vCvz7KVybrxTXLzS8WcBb+VPMLfKnlngAg96oQ58DA/2tg1h/a3t/q9OEBzoQg1zm7LpvYDA57z9ora5rYQMen2ETNEbH1BCPO3d2g3PJl4rHLBycCQaTFTfF0+x4FIWNt2gSUnSuNYyET4ccBrqlKsXTHclEXNk4fL44n0lrN+jcd6eG5XY/y2iiKjhl66R4bBF5msVK4pWoHjf4U+ntHVya4IajZH/cqhMpg+l0x/1Sz/1J5+Uki/OykMNzP5Kvh1HDbzPxAnHuzTBrjHTL0WYyYcMb3dd8Ej56M1CmBF17RYR3idXace5NNLvTBhNdE0jSYjretbHqcLIWbTChxVA2eToWFxZCP/DLayFNWdxWIuAtdr4Vwt0KukrywCea3ekkXPEb6UGdWFpJMd7VuB54mwUNSFIuVUue9iKf4sXy6eKKBiyV7se93TpGuv6hvd0eIMlispvbAw18CbEO9vyXm2qiS1KPceEs1L9RK3e/NcTdYBtuf1ESPZdvS6Z+JTIkHP0K7UBxOhERonUm5nfkcGYW8zmaR6R/4wR+TDVx2Vnv/pHREdih5lhdBr0Uk+AT8W6WmyDgaQciGts9Vo8L4QxKE9FTdalYpJBGRq/l46WiFN8lNDLK0Wy49qaOyCFIY9RijyekiOsVb08MwHfdYHdL6+vEBSAZQN5+sc7+ofhEvdnKOuR4WzRj0BsMuiT0eFie456E++LUhOcEnJbOmhKdFMmGV6xboGMhnO4+URUFOrBAOughAb81AjVkSP0gmHBtaQUbaJAjBd539SOYQYfUKPyjC2iv+DaYtwt0hGgEyTIb/K1t/HER7pqe9Hj9anHfdWrD4nTyFtdLNvyPjW8RKLLp4OiwiK50/MnSaDqm1Nh4jVXXIlBy391gShLodDgJeHqXyzm6E2zUvKRyoqIjeodQOg4Al9f3mh8/qG/xlh+LFeXjdcS51zH8BP7YyIiw0OD+sSF9O+Iwio6h2cT50puiELrbRqsi3WrRB5hio4Kj5enYsNCoaHFafo/UFKCX5MO0JB+mveZDnKCkkPbY+EC8pCKY9tZbFE93kGgV6bgQ45viqLXp6PxnleBz4xcUluApO07klkz3vrOELmSLNWKpnnSsn1U8dTurIL9tK5xvQHksRh4HFBDvXGDwjLnh6W1nb/n4BRFKtiZY9PQOYV583spBlFw8WBMcyytsAFyz6FNxG1wj3dlFuiuPPO3t/jul0zWhTBDF07aRnOKheOoh0Ru70uJ7mPL2txst2PRJRrzxKyiATtbbfVva77Ibn97Lzo9fQu1FfknSDe7x3yU0LARo6NzGWZjJbknQucvVYsvwhTdKtwaom7Z0kzJaBDay0gPbjbS6eHuSi460Jk7pdGFGJ1gvQUfXndQtWfNXH1MCFibM78zb+mmzCU9JZMqWH+CvDohxgDs=
*/