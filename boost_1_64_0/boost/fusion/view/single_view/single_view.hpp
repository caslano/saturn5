/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman
    Copyright (c) 2011 Eric Niebler

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_SINGLE_VIEW_05052005_0335)
#define BOOST_FUSION_SINGLE_VIEW_05052005_0335

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/support/detail/access.hpp>
#include <boost/fusion/support/detail/as_fusion_element.hpp>
#include <boost/fusion/support/sequence_base.hpp>
#include <boost/fusion/view/single_view/single_view_iterator.hpp>
#include <boost/fusion/view/single_view/detail/at_impl.hpp>
#include <boost/fusion/view/single_view/detail/begin_impl.hpp>
#include <boost/fusion/view/single_view/detail/end_impl.hpp>
#include <boost/fusion/view/single_view/detail/size_impl.hpp>
#include <boost/fusion/view/single_view/detail/value_at_impl.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/mpl/int.hpp>
#include <boost/config.hpp>

#if defined (BOOST_MSVC)
#  pragma warning(push)
#  pragma warning (disable: 4512) // assignment operator could not be generated.
#endif

namespace boost { namespace fusion
{
    struct single_view_tag;
    struct random_access_traversal_tag;
    struct fusion_sequence_tag;

    template <typename T>
    struct single_view : sequence_base<single_view<T> >
    {
        typedef single_view_tag fusion_tag;
        typedef fusion_sequence_tag tag; // this gets picked up by MPL
        typedef random_access_traversal_tag category;
        typedef mpl::true_ is_view;
        typedef mpl::int_<1> size;
        typedef T value_type;

        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        single_view()
            : val() {}

        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        explicit single_view(typename detail::call_param<T>::type in_val)
            : val(in_val) {}

        value_type val;
    };
    
    template <typename T>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline single_view<typename detail::as_fusion_element<T>::type>
    make_single_view(T const& v)
    {
        return single_view<typename detail::as_fusion_element<T>::type>(v);
    }
}}

#if defined (BOOST_MSVC)
#  pragma warning(pop)
#endif

#endif



/* single_view.hpp
maExsx9TTi9B9aF1ZDZnwOopNGbXzfAds8/jr1ObfjQlYr+g0e/noAXQxsZI+ydpo5HyvGWGx5G4HWiV+nTKS7XfMUNKRVq91zn2Ug13zVCA2d/jHK2Fhe6ZoQdIy5Du2Qdh7hDul1JIG1XJmygMnphhNIs71/XbpzRHaKuY3b8VU57a/AOvmaWxa2aMQzMyo2tttABaAjO6nkaD/6ibA02tPzeaWn9ejTaDGqZ7qt6fAy1eGrvufxzrQRPf+dmpPI7dlHrhCWHw3AwzmbUbmyoH2Uv8zC1G2qpKu7OQhc2QORK3C22F6dvjXw3A9Voeq3bj36Ez/1YXFniDeaaW1mRFpQpkn6PjWo+sOliY7W+sPXLutgf/YVvX1MuE6RQL6JiNfJeurLBwCgtMBmkhvbOGMF9KC3RVpG362PIS1ZDagmMtTY41gBctgZmcI4AgWjwzOQ+YZ5x6m4449TY9ceptBtCMzOQ6w1o1+tOlUe/PqWox4EUT+6y9aIZOP+4WBmktcIPZm8NNKU6XzgKlmNksK1IIc6FNUqS9mLFgszBnBgs0i5EW27h9amEOnQWqszhd5q5DhIUyW+AhSKv88a/3wiCrBTbHSqv5oXCLrxYLPqOF3i2yT4mBfwd1Oi7Mb7LAfGYb1r5PJ8xttkBBRVriEdtUYWGLBQayuLU1PiUJ81ot8FustHL1K1wU5rTJ+UOT84fmQUtgRnOEFkCLZ0brBQ1y43phRusFzYam1p8TTa0/r4YF0dRy0eWxQKeI/arEwvthyxNoG0MTn5nux7jdTQfT9m7LZ4F/QNqQJ00W01rKb6FnRw4o+PeLIbWFwTfRlun9lo7CfGglmSX+ddAsLJzMiq668EaY41sLmBVp09o9yk1tFrBAYRZHz4CghdB4m90zPfldmD3eAmWYZQv0+E2YJ5m979hhmLAgWkZm8jkWrAGtI7O6Nff+KcxdMNoME0s+oji01syu7js8luISLJCPmXy+HGtP0KgdrSizEz03t/pqCtgKyfE8iH8PLpbjqTBPYQu8Amnb//22rDB/ogVSx0gbNDl9b2GOohY4ycyQ7qVfWKCEBRqBNLpPi3/sJS1Qi+XS9Niwz8KCpSxQnMWNeuXrIExXWt2cGuZVNdyO0JwRO4RrXn6mAeAoI+MCigLyXBjAg1YvYodxG0uV9NNjYSG0OGby+gEgrGFQVt10GmbTMLuGOTTMqWEuDXNrmAftErM9H5e/E+YtFz2e195vdNOYldMYs/IaY6ZhNrR4ZvL6D+tDy8VMXuNhnhpxQY04qKAe50BTi3NrxPk14kIacbaK6nFONLU4r0ZcQCMOKqnH2dHU4twacT6NuJBGnK5ydJx81hZrr6xRe2WN2tH42u2wMC4tjbXDAhWZyet3rE/DAhqmq6JuLg3zaxhUVTenhvk0LKxhjmq4b5UWvW/VsICGQXV1c2iYR8MCGgY1NPrTMI+GBVQtBuA7Cz178JsSA8ubfPxLmA/Nw+yPdc1XCXPUtEAXZjM777ojLIA2j9l/u4+YIMxTywIDmM32960rTFfbAk0VaZs2wTxqs448b0WLugaCuhZ6v/cRrO9I4MxgGrMGeN0B0k527GwV5ktmnviBNmHQEM/dFGk9cw17IczrxOuVNNLyKb+eEBZuY4GsqaXdUarMFBbsYoHDqaQ9fGR5KMzZxwIlWA3lO2ah+mz9LOAAaZdWuFzC3GjPmCU5D5yj+vrjeR2zQondE4WF0OYzyzex0lGKG2CBPsw+jx09SJh9YHSb8rtQmAvaL8y++1inEtU3KNr2xpfrRW0OxnlPIS1nwTr9KZcRFmjP4qZfSXxD4zLSAj0UaedP/tKA5mEUXsMyyzY=
*/