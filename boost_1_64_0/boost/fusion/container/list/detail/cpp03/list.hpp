/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_LIST_07172005_1153)
#define FUSION_LIST_07172005_1153

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/support/void.hpp>
#include <boost/fusion/support/detail/enabler.hpp>
#include <boost/fusion/container/list/detail/cpp03/list_fwd.hpp>
#include <boost/fusion/container/list/detail/cpp03/list_to_cons.hpp>
#include <boost/fusion/support/is_sequence.hpp>
#include <boost/core/enable_if.hpp>

#if !defined(BOOST_FUSION_DONT_USE_PREPROCESSED_FILES)
#include <boost/fusion/container/list/detail/cpp03/preprocessed/list.hpp>
#else
#if defined(__WAVE__) && defined(BOOST_FUSION_CREATE_PREPROCESSED_FILES)
#pragma wave option(preserve: 2, line: 0, output: "preprocessed/list" FUSION_MAX_LIST_SIZE_STR ".hpp")
#endif

/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

    This is an auto-generated file. Do not edit!
==============================================================================*/

#if defined(__WAVE__) && defined(BOOST_FUSION_CREATE_PREPROCESSED_FILES)
#pragma wave option(preserve: 1)
#endif

namespace boost { namespace fusion
{
    struct nil_;
    struct void_;

    template <BOOST_PP_ENUM_PARAMS(FUSION_MAX_LIST_SIZE, typename T)>
    struct list
        : detail::list_to_cons<BOOST_PP_ENUM_PARAMS(FUSION_MAX_LIST_SIZE, T)>::type
    {
    private:
        typedef
            detail::list_to_cons<BOOST_PP_ENUM_PARAMS(FUSION_MAX_LIST_SIZE, T)>
        list_to_cons;
        typedef typename list_to_cons::type inherited_type;

    public:
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        list()
            : inherited_type() {}

        template <BOOST_PP_ENUM_PARAMS(FUSION_MAX_LIST_SIZE, typename U)>
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        list(list<BOOST_PP_ENUM_PARAMS(FUSION_MAX_LIST_SIZE, U)> const& rhs)
            : inherited_type(rhs) {}

        template <typename Sequence>
        BOOST_FUSION_GPU_ENABLED
        list(Sequence const& rhs
            , typename enable_if<traits::is_sequence<Sequence>, detail::enabler_>::type = detail::enabler)
            : inherited_type(rhs) {}

        //  Expand a couple of forwarding constructors for arguments
        //  of type (T0), (T0, T1), (T0, T1, T2) etc. Exanple:
        //
        //  list(
        //      typename detail::call_param<T0>::type arg0
        //    , typename detail::call_param<T1>::type arg1)
        //    : inherited_type(list_to_cons::call(arg0, arg1)) {}
        #include <boost/fusion/container/list/detail/cpp03/list_forward_ctor.hpp>

        template <BOOST_PP_ENUM_PARAMS(FUSION_MAX_LIST_SIZE, typename U)>
        BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        list&
        operator=(list<BOOST_PP_ENUM_PARAMS(FUSION_MAX_LIST_SIZE, U)> const& rhs)
        {
            inherited_type::operator=(rhs);
            return *this;
        }

        template <typename Sequence>
        BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        typename boost::enable_if<traits::is_sequence<Sequence>, list&>::type
        operator=(Sequence const& rhs)
        {
            inherited_type::operator=(rhs);
            return *this;
        }
    };
}}

#if defined(__WAVE__) && defined(BOOST_FUSION_CREATE_PREPROCESSED_FILES)
#pragma wave option(output: null)
#endif

#endif // BOOST_FUSION_DONT_USE_PREPROCESSED_FILES

#endif

/* list.hpp
6/Ae+Du8D3YhvXXwMHg/jIYPSf0/DE+A6vocWAevho/Ca+Hj8EP4JPwKPgW3wKclX9lB0m+Q/gT54jtAu1EuyLqdePgSPBLWw1S4UfL1GjwBvg7PhG/Ac+Cb8HL4lrT79+BnsAF+Cz+A+5LGh7AX/AT2h5/D8fALac9fwjL4DTwNfgsvgd9JPn+Qdv0j/Bj+JO16K/wL/gqDydNvcAD8HcbCP2Ey/AvmQgqgKh92hSfDbnAp3BleC4PhZrgL/ALuCsMor93hILgHTIJ7wmS4l35ds/inJiPhQcZ1YptkndibcH8prxj4NhwD35FyfhcWdZI/asvtwZ3mkwpZHWz7pcQvFbs6uFN8U2mrg9vsn6pf0K3NPqoZq4P/NX6qU1YHt8tXVU38WmQTsg2JvMP2XdnBDnawgx3sYAc72MEOdrBDZ4bt5f9X3f8d4P+P150BuLuMmQEt9OjB+M9lBr/vGGeuy9WSs7cM+9R3kf9BAcXDKKj4/Dw63UanqviEgpr29xFZ8/ctucro7wsP0vx9OPzkDIigxv6+2CBrf19ikNHfp/q8gqz9pGkWfr8Mo99P881PNPkg64w+P82ferPPx+ow+/ALxc/X2Oed5bD282VAvZ8v1OBrxKWomz/ggatCVL2aTzDHwv+nzXcgvuz5bvT/dbH2/9Wv6Hz/379x/Yft//tv+P+OUf18pREVJ+cuHjj+6je3/jm1fOeRbfPz9UPk+Yp413/sBMMQJeyHeQpDfX6cIHlmyrNUuf8I776PajhA/B2R4u84DM6E/eHZMAouhQPhzTAG3gkHwVdgLHwLxsNP4RC4Rfx+OwWRlvg9EmFf8ftFi98vCQ6DqTAZThO/Xy5MgYVwJFwKR8FlcAy8DY6FtXAcfBmmiZ9vPPwOHgV/Fr+gUkDpcH84EfaBk+AgeDQ8HGbAZDgZToeZsAJOEb9fFrwMToUrxF94j/gLH4DZcL34C3+Fx8Fw2ud0eDycAW+CJ8D3oRN+AHPgDzAXdqN+ZsIeMA+GQTc8FObDKDjLv38kz8WO8bOkd5KfpbN8LP83/8qqk7rZa3+2g0+lPf6UsDuDHYnIjDttP4od7GCHloVOX/9fwvlC5R2z/v9Q3dx/3l+185p7IhORI5TO4kXa+v/U8RlpYzKdrlLOBSpqzTlyMVHqOUS8nlmcBaV7t4tV73PlOUxzsjcHsG1LANuc5aVlFW5Xp9sn4yZ0jBvbl8S9Ocs0+yaObkO5xbfQrgSjXVqdhnWxtqteb1cby6yttvnK7HKxbZ6MDcxB1vCSknKxZhujTE7vIEsLymxPsUvGZkzno5UZz8DsKmeCSNqfIY+SdoMxbXXRSGvOV9aP/5jTlzPjZPxC+RIb62qt2DRabBqBDKXsQi7RbOJYZSmPmQsUBS22S5em1ItWTh5zmxnWrbEdR2KHx2CHlE0H2EGZiR3GM+B+FDtOkbZbiaQobddrh7fRSnE480tabMPwKNWG4uba7Shpt761DAdeSrryrFA+j9Y+G8e8Vu1sbbfnUr3dxa7OsHm0yeaHxMZ4sflj7bPxu9hVurhDkT2QBBn3DblMOy8wr8idW8KJcBzM2fx5cO2Zg289Rtb5Y3PWZ8nt+GNz1mNwgcbsdvy9Wc4IU9tbVsWIi6b/csgRMZ9s/CTvw/PbNjaX5pD+j/yGekxnJMyRMy7mwghYCQfC+fAIuABOhCdBn74tTeg7XfSdJfoWib6zRd85om+xXx99jMD6Voi+GtF3vei7QfStFH036segmtB3q+hbLfruFH21ou8u0bdG9OU45Pdcfuc9prOh9pExrf1gbxgK+8BeMAX2huPgAXACDIPFsA+cAw+SdKqRBknnK0lnL7g=
*/