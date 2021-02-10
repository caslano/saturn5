/*=============================================================================
    Copyright (c) 2011 Eric Niebler

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_SEGMENTED_FOR_EACH_HPP_INCLUDED)
#define BOOST_FUSION_SEGMENTED_FOR_EACH_HPP_INCLUDED

#include <boost/fusion/support/config.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/fusion/support/void.hpp>
#include <boost/fusion/algorithm/iteration/for_each_fwd.hpp>
#include <boost/fusion/support/segmented_fold_until.hpp>

namespace boost { namespace fusion { namespace detail
{
    template <typename Fun>
    struct segmented_for_each_fun
    {
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        explicit segmented_for_each_fun(Fun& f)
          : fun(f)
        {}

        Fun& fun;

        template <typename Sequence, typename State, typename Context>
        struct apply
        {
            typedef void_ type;
            typedef mpl::true_ continue_type;

            BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
            static type call(Sequence& seq, State const&, Context const&, segmented_for_each_fun const& fun)
            {
                fusion::for_each(seq, fun.fun);
                return void_();
            }
        };
    };

    template <typename Sequence, typename F>
    BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline void
    for_each(Sequence& seq, F& f, mpl::true_) // segmented implementation
    {
        fusion::segmented_fold_until(seq, void_(), segmented_for_each_fun<F>(f));
    }
}}}

#endif

/* segmented_for_each.hpp
9EeaoohPX568PqKjB4QVQKGT4elPeD3YvBFlIwpoSS5oEl3FwcG3twOkrYS8Rc7/o4pCvDCU4TUXVgztkwPGLL6ila43wjotyc1kOkvGyaGmj0ARfDCfguEYL42tGstZ+eRkRnFyNh/P0vF0EjCaD0St1gXy/FgWWuTG5fXABVdPqxp4udr6aHRTZzKwtZSk4T9dpOksCVm45FIy8qtzMArlk61FZv03aqUyYbFNlf6MgT/jkN49o6ZXoilsCKQUz3QWUa21PRSzdWOsx6gypgGQk0uUQw1nAtGwH5Z3cl4O5BiOrSOADde2kW7Ru17rDMiC3kdAjdeCaSVL1p3pDZKZF6psQwbL2J43mWxppxQF7cLqa8KFuz0O3a7Gu8zcrmZUio0rjtvVu63gMKstvnNxMNJaVd6RckB4MXgR9AQZrEB/Lsy67yjtEUmhO/Amu+ENQLJ0Mkk64qJSJYIlcq5bse/ZDlue+JhKK2So4QTii07dRtxLDw0UHh+lhjaF3GwpkNPHYrR8ps9IDYklZMGTBXURxIbzskkvE6r0o6yZdytUr88SGMA02RpUHDCDgrj5RAybja6ZXADjqUNw4jxf6aLQjxycFvkuiaapKl0js29QBzMaLIOlyO6bivlGPoGCWKCrVwTjICOc
*/