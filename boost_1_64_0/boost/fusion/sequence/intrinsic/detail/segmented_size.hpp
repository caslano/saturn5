/*=============================================================================
    Copyright (c) 2011 Eric Niebler

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_SEGMENTED_SIZE_08112006_1141)
#define BOOST_FUSION_SEGMENTED_SIZE_08112006_1141

#include <boost/fusion/support/config.hpp>
#include <boost/type_traits/add_const.hpp>
#include <boost/type_traits/remove_reference.hpp>
#include <boost/mpl/fold.hpp>
#include <boost/mpl/plus.hpp>
#include <boost/mpl/size_t.hpp>
#include <boost/mpl/placeholders.hpp>
#include <boost/fusion/sequence/intrinsic_fwd.hpp>
#include <boost/fusion/mpl/begin.hpp>
#include <boost/fusion/mpl/end.hpp>
#include <boost/fusion/support/is_segmented.hpp>

namespace boost { namespace fusion { namespace detail
{
    ///////////////////////////////////////////////////////////////////////////
    // calculates the size of any segmented data structure.
    template<typename Sequence>
    struct segmented_size;

    ///////////////////////////////////////////////////////////////////////////
    template<typename Sequence, bool IsSegmented = traits::is_segmented<Sequence>::value>
    struct segmented_size_impl
      : mpl::fold<
            typename remove_reference<
                typename add_const<
                    typename result_of::segments<Sequence>::type
                >::type
            >::type
          , mpl::size_t<0>
          , mpl::plus<mpl::_1, segmented_size<remove_reference<mpl::_2> > >
        >::type
    {};

    template<typename Sequence>
    struct segmented_size_impl<Sequence, false>
      : result_of::size<Sequence>::type
    {};

    template<typename Sequence>
    struct segmented_size
      : segmented_size_impl<Sequence>
    {};

}}}

#endif

/* segmented_size.hpp
vdZ8XOa5sE5hta0PzqvmxmZOxL4SzjHnniXUuTPT7dhX97gfCH4O0gbGvhrRsa8AqGNf3Vbtm3SOCRFDfsn0Z939ZpoD0CvE8b0q/1u9iNLH5Ka8g0WVp0npgcoC/hAdPjdxBQvDIMqcwmXqegi3wIadycfeaOo3XCeP07yIGUIx//ab6fgW8QVjGKpNneFUfHpJHSuWlT5k3eS5f1qG3C8Dzk5sLS1vLsnOhrkjTexkGqe+U6Uxm4fY4Jb93Vkit0oKpwiyksmNnWwUY9yep+2SiFzDSZIy+xiu63781JDmmYpDP0z9nJF7wSPol2HKz1mYFYkXhznTVuat+IS0LSOnDAuRIptYsMu2VDyX30xtdvKwSNLIx29rTiCK5wrlSWAd4mXB2ZpYUBqOpV6ffoc/kbbNM9fNQh6ypk59qnt73RvpWaPkSVzljJ5yDV3a2FtIfPawDIoMlje4edd3rRjrxsQ+oHScwnM8nzW3/Mig9Xp7CL5K0sCPHJfVWgUTj7kUAU/uJdOy8tKiYt2uEhjPA21xyLuLfPSlSFumHBUVflXhj7/FxOd55CVF6ItxVjvdIx51e6R+HiuCpIzyrNYXNXptSDUMISjVODJ1e8Mj8nJY+X/O9psAQYaujQ1LHL301nG9u+l9U0f+uxELIzwqdFzuUYNOfVpQxsyOFkYWc1DRd1r0gb4saD9yvTYPmaUQNzFOcAP9XXZdn+CsC3fi221h5dAx5O2+YRtjfVTt80OwxBcWMQu7Whgc24bv0I0IBi9jzHZ7/40tjJ4hDdyFm3Tj5Ktqe58JgrP8btAv+KZtnBoW2tY9vhlgqC0VseH/mKBfg61VfnMLp8y2sKwvS8ygvI/+LZA+MO/jly0MFoPlPPKWJga9J5B+idBtnwJ2K0IHvwcScwNoUsGE/nSafv7WSNdKNjP2yG6kUwUV0ND+8dVkXfVSBza3mcPoNSVdu3ebPA8IeRmHlRswerMIr6bWjL0mfqqqAighcOWJvJX/Y7+JPVy4mRMHOVNGQHSde6Q5fx/yYZXz8tiV2qEGithFE3v/KMjzxPUjZmqMEbtJ5Bapx8M8zBnRTuOeh2A594PUSQO5ZrXsFc6+kbZ1mbpRkVamGltyaPnnTZ5JL/cC3+VhfRK0Ymd9isqv3JRDmwTmNaol/4u0DdMkDoowUWGpaO6Xr9O6JEVUFEXEiM4R9y0mtmSpUGUXfs5sfZdun6smD2eh0FImpcuoZSjdH42/ibYpj3ynqAJGVRP0nXebPFNpkaVFxWNmXtDgO+8xsfdPK6eIyhy1GK34e4AlZ2EX+kPMC2YF0Gzt+d9Ez8GeK7b9ESPheFp3VY+m7x3HeZaUXsAMVzDcu2HsPZPncJ7wqOSRw+Si1bdso8/QMiKf8zKouBzopG334t0P8JDYe1FepDlsctuByNrxwU2+ByRJWJRB7jGRFdXUSR9V+EsmPhfqnjBy0rJm6C0ILQtt48smnjOoRpImAKAqcJob/cqb6BkwTcuwSHz+354B7wJn1ifcGtqznttmiNHK42Y3YVluMJsQV23iNQ0GRyxiDDmvFRgcFQQmzs6XbgVyXgcY9B6f29qWMeN6wM8ITcu/u6RfrOlWp0XkXSRuz+sbHPa4DlnnJIZ+fASirKE3CBz9GuY7fRp889YVBqZ3ScM96K4RceA367Ig/OyQvm3RxTqs19IfWnQa+/T4aIsu/dgw9jTSaZuJWtwdfdY7Mdb+5lUDcFAjncNmRzcGaoWYbcSQthdV0meETgzdBz1yZycGqmPkWO7GQHU0ZvJ6AtNlcGb49Y8LjDlG6Hd8qUWn33Ho+m06/Y6bFp1+xy/WdNoPZRUQw25gY2Q1sB4=
*/